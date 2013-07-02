/* ///////////////////////////////////////////////////////////////////////
 * File:		mutation_traits_base.h		
 *
 * Created:		08.11.04
 * Updated:		08.11.07
 *
 * Brief: The mutation_traits_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_MUTATION_TRAITS_BASE_H
#define EXTL_INTELLIGENCE_GA_MUTATION_TRAITS_BASE_H

/*!\file mutation_traits_base.h
 * \brief The mutation_traits_base class
 */
#ifndef __cplusplus
#	error mutation_traits_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief mutation_traits_base class
 * 
 * \param D The derived type
 * \param Pop The population type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k D
		,	typename_param_k Pop
		,	typename_param_k Rand
		>
class mutation_traits_base
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
		random_type const&	rand() const	{ EXTL_ASSERT(NULL != m_prand); return *m_prand;	}
		random_type&		rand()			{ EXTL_ASSERT(NULL != m_prand); return *m_prand;	}
	/// @}

	/// \name Constructors
	/// @{
	public:
		mutation_traits_base()
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
		/// Mutates the whole popualtion
		population_type& mutate(population_type& pop)
		{
			EXTL_ASSERT(derive().is_valid());

			size_type pop_n = pop.size();
			for (index_type i = 0; i < pop_n; ++i)
			{
				mutate(pop.individual(i));
			}
			return pop;
		}
		/// Mutates the individual
		individual_type& mutate(individual_type& idl)
		{
			EXTL_ASSERT(derive().is_valid());
			return derive().do_mutate(idl);
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
#endif /* EXTL_INTELLIGENCE_GA_MUTATION_TRAITS_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
