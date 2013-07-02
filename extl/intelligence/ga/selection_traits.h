/* ///////////////////////////////////////////////////////////////////////
 * File:		selection_traits.h		
 *
 * Created:		08.09.09
 * Updated:		08.09.11
 *
 * Brief: The selection_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_SELECTION_TRAITS_H
#define EXTL_INTELLIGENCE_GA_SELECTION_TRAITS_H

/*!\file selection_traits.h
 * \brief The selection_traits class
 */
#ifndef __cplusplus
#	error selection_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "probability_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief roulette_wheel_selection_traits
 * 
 * \param Pop The population type
 * \param Rand The random type
 * \param Pt The probability_traits type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		,	typename_param_k Pt
		>
struct roulette_wheel_selection_traits
{
	/// \name Types
	/// @{
	public:
		typedef Pt													probability_traits_type;
		typedef Pop													population_type;
		typedef typename_type_k population_type::individual_type	individual_type;
		typedef typename_type_k population_type::size_type			size_type;
		typedef typename_type_k population_type::bool_type			bool_type;
		typedef typename_type_k population_type::float_type			float_type;
		typedef typename_type_k population_type::index_type			index_type;
		typedef typename_type_k population_type::int_type			int_type;
		typedef Rand												random_type;
	/// @}

	private:
		probability_traits_type										m_pt;

	/// \name Methods
	/// @{
	public:
		/// Prepares selection
		void prepare(population_type& pop)
		{
			// calculate probabilities
			probability_traits().probability(pop);
		}
		/// Selects a individual
		individual_type& select(population_type& pop, random_type& rand)
		{
			// select
			float_type p = rand.fgenerate(0, 1);
			EXTL_ASSERT(p >= 0 && p < 1);

			size_type i;
			size_type n = pop.size();
			float_type sum = 0;
			for (i = 0; (sum <= p) && (i < n); ++i)
			{
				sum += pop.individual(i).probability();
			}
			
			EXTL_ASSERT(i > 0);
			return pop.individual(i - 1);
		}
		/// invariance
		bool_type is_valid() const	{ return e_true_v;	}
	/// @}
	
	private:
		probability_traits_type const&		probability_traits() const	{ return m_pt;	}
		probability_traits_type&			probability_traits()		{ return m_pt;	}

};

/*!\brief tournament_selection_traits
 * 
 * \param Pop The population type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		>
struct tournament_selection_traits
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
		typedef Rand												random_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// Prepares selection
		void prepare(population_type& /*pop*/){}

		/// Selects a individual
		individual_type& select(population_type& pop, random_type& rand)
		{
			// select
			size_type pop_n = pop.size();
			size_type select_n = 2;

			index_type best_index = rand.generate(0, pop_n);
			float_type fbest = pop.individual(best_index).fitness();

			for (size_type i = 1; i < select_n; ++i)
			{
				index_type index = rand.generate(0, pop_n);
				if (pop.individual(index).fitness() > fbest)
				{
					fbest = pop.individual(index).fitness();
					best_index = index;
				}
			}
			EXTL_ASSERT(best_index >= 0);
			return pop.individual(best_index);
		}
		/// invariance
		bool_type is_valid() const	{ return e_true_v;	}
	/// @}

};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_SELECTION_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
