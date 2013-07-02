/* ///////////////////////////////////////////////////////////////////////
 * File:		fitness_traits_base.h		
 *
 * Created:		08.10.07
 * Updated:		08.11.07
 *
 * Brief: The fitness_traits_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FITNESS_TRAITS_BASE_H
#define EXTL_INTELLIGENCE_GA_FITNESS_TRAITS_BASE_H

/*!\file fitness_traits_base.h
 * \brief The fitness_traits_base class
 */
#ifndef __cplusplus
#	error fitness_traits_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fitness_traits_base class
 * 
 * \param D The derived type
 * \param Pop The population type
 * \param Pen The penalty_traits type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k D
		,	typename_param_k Pop
		,	typename_param_k Pen
		>
class fitness_traits_base
{
	/// \name Types
	/// @{
	public:
		typedef D														derived_type;
		typedef fitness_traits_base										class_type;
		typedef Pop														population_type;
		typedef typename_type_k population_type::individual_type		individual_type;
		typedef typename_type_k individual_type::size_type				size_type;
		typedef typename_type_k individual_type::bool_type				bool_type;
		typedef typename_type_k individual_type::index_type				index_type;
		typedef typename_type_k individual_type::int_type				int_type;
		typedef typename_type_k individual_type::float_type				float_type;
		typedef Pen														penalty_traits_type;
	/// @}

	/// \name Members
	/// @{
	private:
		bool_type														m_is_valid;
		penalty_traits_type												m_pt;
	/// @}

	/// \name Traits
	/// @{
	public:
		penalty_traits_type const&	penalty_traits() const	{ return m_pt;	}
		penalty_traits_type&		penalty_traits()		{ return m_pt;	}
	/// @}

	/// \name Constructors
	/// @{
	public:
		fitness_traits_base()
			: m_is_valid(e_false_v), m_pt()
		{}
	/// @}

	private:
		void fitness_impl(individual_type& idl)
		{
			derive().do_fitness(idl);
			penalty_traits().penalty(idl);
		}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init()
		{
			m_is_valid = e_true_v;
		}
		/// calculate the fitness of individuals
		void fitness(population_type& pop)
		{
			EXTL_ASSERT(pop.size() > 0);
			EXTL_ASSERT(derive().is_valid());

			// init
			fitness_impl(pop.individual(0));
			pop.fsum(pop.individual(0).fitness());
			pop.fmin(pop.individual(0).fitness());
			pop.fmax(pop.individual(0).fitness());

			size_type best_index = 0;
			size_type worst_index = 0;
			pop.individual(0).is_best(e_false_v);
			pop.individual(0).is_worst(e_false_v);
			
			size_type n = pop.size();
			size_type i;
			for (i = 1; i < n; ++i)
			{
				// calculate fitness
				fitness_impl(pop.individual(i));

				// fitness minimum, maximum, sum
				pop.fmin(pop.individual(i).fitness() < pop.fmin()? (worst_index = i, pop.individual(i).fitness()) : pop.fmin());
				pop.fmax(pop.individual(i).fitness() > pop.fmax()? (best_index = i, pop.individual(i).fitness()) : pop.fmax());
				pop.fsum(pop.fsum() + pop.individual(i).fitness());

				pop.individual(i).is_best(e_false_v);
				pop.individual(i).is_worst(e_false_v);
			}

			// fitness average
			pop.favg(pop.fsum() / n);

			// best/worst individual
			pop.individual(best_index).is_best(e_true_v);
			pop.individual(worst_index).is_worst(e_true_v);
		}
		/// invariance
		bool is_valid() const
		{
			return m_is_valid;
		}
	/// @}

	private:
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		derived_type&		derive() 		{ return static_cast<derived_type&>(*this);			}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FITNESS_TRAITS_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
