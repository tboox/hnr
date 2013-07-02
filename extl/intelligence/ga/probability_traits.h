/* ///////////////////////////////////////////////////////////////////////
 * File:		probability_traits.h		
 *
 * Created:		08.09.09
 * Updated:		08.09.11
 *
 * Brief: The probability_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_PROBABILITY_TRAITS_H
#define EXTL_INTELLIGENCE_GA_PROBABILITY_TRAITS_H

/*!\file probability_traits.h
 * \brief The probability_traits class
 */
#ifndef __cplusplus
#	error probability_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief proportional_probability_traits
 * 
 * \param Pop The population type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Pop>
class proportional_probability_traits
{
	/// \name Types
	/// @{
	public:
		typedef Pop													population_type;
		typedef typename_type_k population_type::individual_type	individual_type;
		typedef typename_type_k population_type::size_type			size_type;
		typedef typename_type_k population_type::bool_type			bool_type;
		typedef typename_type_k population_type::float_type			float_type;
		typedef typename_type_k population_type::index_type			index_type;
		typedef typename_type_k population_type::int_type			int_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// p = fit_i / fit_sum
		void probability(population_type& pop)
		{
			EXTL_ASSERT(pop.size() > 0);
			
			size_type n = pop.size();

			// pop.fsum() != 0
			if (pop.fsum())
			{
				for (size_type i = 0; i < n; ++i)
				{ 
					pop.individual(i).probability(pop.individual(i).fitness() / pop.fsum());
				}
			}
			else
			{
				for (size_type i = 0; i < n; ++i)
				{ 
					pop.individual(i).probability(1);
				}
			}
		}
	/// @}
};

/*!\brief proportional_probability_traits
 * 
 * \param Pop The population type
 * \param SP The selection pressure(SP%)
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	e_size_t SP/* = 30*/
		>
struct rank_based_probability_traits
{
	/// \name Types
	/// @{
	public:
		typedef Pop															population_type;
		typedef typename_type_k population_type::individual_type			individual_type;
		typedef typename_type_k population_type::size_type					size_type;
		typedef typename_type_k population_type::bool_type					bool_type;
		typedef typename_type_k population_type::float_type					float_type;
		typedef typename_type_k population_type::index_type					index_type;
		typedef typename_type_k population_type::int_type					int_type;
		typedef typename_type_k buffer_selector<index_type>::buffer_type	index_buffer_type;
	/// @}

	private:
		class pred
		{
			private:
				population_type& m_pop;

			public:
				pred(population_type& pop)
					: m_pop(pop)
				{
				}

			public:
				bool_type operator()(index_type lhs, index_type rhs)
				{
					return m_pop.individual(lhs).fitness() > m_pop.individual(rhs).fitness();
				}
		};

	/// \name Methods
	/// @{
	public:
		/// fitness sort => p = q * (1 - q)^i
		void probability(population_type& pop)
		{
			size_type pop_n = pop.size();
			EXTL_ASSERT(pop_n > 0);

			// init indices
			index_buffer_type indices(pop.size());

			size_type i;
			for (i = 0; i < pop_n; ++i) indices[i] = i;

			// fitness sort in descending order
			//std_sort(indices.data(), indices.data() + indices.size(), pred(pop));
			std_sort(indices.begin(), indices.end(), pred(pop));
			
			// calculate probability
			float_type q = float_type(SP) / 100;	// selection pressure
			//float_type q = pop.fsum() > 0? (pop.individual(indices[0]).fitness() / pop.fsum()) : 0.9;
			float_type p = q * (1 - q);
			for (i = 0; i < pop_n; ++i)
			{
				pop.individual(indices[i]).probability(p);
				p *= (1 - q);
			}
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_PROBABILITY_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
