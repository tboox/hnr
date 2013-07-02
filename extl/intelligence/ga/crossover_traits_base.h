/* ///////////////////////////////////////////////////////////////////////
 * File:		crossover_traits_base.h		
 *
 * Created:		08.11.04
 * Updated:		08.11.04
 *
 * Brief: The crossover_traits_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_CROSSOVER_TRAITS_BASE_H
#define EXTL_INTELLIGENCE_GA_CROSSOVER_TRAITS_BASE_H

/*!\file crossover_traits_base.h
 * \brief The crossover_traits_base class
 */
#ifndef __cplusplus
#	error crossover_traits_base.h need be supported by c++.
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
		,	typename_param_k Rand
		>
class crossover_traits_base
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

	protected:
		random_type const&	rand() const	{ EXTL_ASSERT(NULL != m_prand); return *m_prand;	}
		random_type&		rand()			{ EXTL_ASSERT(NULL != m_prand); return *m_prand;	}

	/// \name Constructors
	/// @{
	public:
		crossover_traits_base()
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
		/// crossover i1 & i2
		void cross	(	individual_type& i1
					,	individual_type& i2
					)
		{
			EXTL_ASSERT(derive().is_valid());
			derive().do_cross(i1, i2);
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
#endif /* EXTL_INTELLIGENCE_GA_CROSSOVER_TRAITS_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
