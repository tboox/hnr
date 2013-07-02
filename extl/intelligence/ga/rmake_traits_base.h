/* ///////////////////////////////////////////////////////////////////////
 * File:		rmake_traits_base.h		
 *
 * Created:		08.09.13
 * Updated:		08.11.02
 *
 * Brief: The rmake_traits_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_RMAKE_TRAITS_BASE_H
#define EXTL_INTELLIGENCE_GA_RMAKE_TRAITS_BASE_H

/*!\file rmake_traits_base.h
 * \brief The rmake_traits_base class
 */
#ifndef __cplusplus
#	error rmake_traits_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief rmake_traits_base class
 * 
 * \param Pop The population type
 * \param Rand The random type
 * \param Pt The probability_traits type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k D
		,	typename_param_k Pop
		,	typename_param_k Rand
		>
class rmake_traits_base
{
	/// \name Types
	/// @{
	public:
		typedef D													derived_type;
		typedef Pop													population_type;
		typedef typename_type_k population_type::individual_type	individual_type;
		typedef typename_type_k individual_type::size_type			size_type;
		typedef typename_type_k individual_type::bool_type			bool_type;
		typedef typename_type_k individual_type::float_type			float_type;
		typedef typename_type_k individual_type::index_type			index_type;
		typedef typename_type_k individual_type::int_type			int_type;
		typedef Rand												random_type;
	/// @}

	/// \name Members
	/// @{
	private:
		random_type*												m_prand;
	/// @}

	/// \name Attributes
	/// @{
	protected:
		random_type const&	rand() const	{ return *m_prand;	}
		random_type&		rand()			{ return *m_prand;	}
	/// @}

	/// \name Constructors
	/// @{
	public:
		rmake_traits_base()
			: m_prand(NULL)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(random_type& rand)
		{
			m_prand = &rand;
		}
		/// randomly make population
		population_type& rmake(population_type& pop)
		{
			EXTL_ASSERT(derive().is_valid());

			size_type pop_n = pop.size();
			for (index_type i = 0; i < pop_n; ++i)
			{
				rmake(pop.individual(i));
			}
			return pop;
		}
		/// randomly make population at hand
		population_type& rmake_at_hand(population_type& pop)
		{
			EXTL_ASSERT(derive().is_valid());

			size_type pop_n = pop.size();
			for (index_type i = 0; i < pop_n; ++i)
			{
				rmake_at_hand(pop.individual(i));
			}
			return pop;
		}
		/// randomly make individual
		individual_type& rmake(individual_type& idl)
		{
			EXTL_ASSERT(derive().is_valid());
			return derive().do_rmake(idl);
		}
		/// randomly make individual at hand
		individual_type& rmake_at_hand(individual_type& idl)
		{
			EXTL_ASSERT(derive().is_valid());
			return derive().do_rmake_at_hand(idl);
		}
		/// invariance
		bool_type is_valid() const
		{
			if (NULL == m_prand) return e_false_v;
			return e_true_v;
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
#endif /* EXTL_INTELLIGENCE_GA_RMAKE_TRAITS_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
