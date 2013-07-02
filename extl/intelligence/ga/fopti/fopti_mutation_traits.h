/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_mutation_traits.h		
 *
 * Created:		08.09.13
 * Updated:		08.10.13
 *
 * Brief: The fopti_mutation_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_MUTATION_TRAITS_H
#define EXTL_INTELLIGENCE_GA_FOPTI_MUTATION_TRAITS_H

/*!\file fopti_mutation_traits.h
 * \brief The fopti_mutation_traits class
 */
#ifndef __cplusplus
#	error fopti_mutation_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/float_mutation_impl.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_mutation_traits
 * 
 * \param Pop The population type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		>
class fopti_mutation_traits
	: public mutation_traits_base<fopti_mutation_traits<Pop, Rand>, Pop, Rand>
{
	/// \name Types
	/// @{
	public:
		typedef mutation_traits_base<fopti_mutation_traits<Pop, Rand>, Pop, Rand>		base_type;
		typedef Pop																		population_type;
		typedef typename_type_k population_type::individual_type						individual_type;
		typedef typename_type_k individual_type::size_type								size_type;
		typedef typename_type_k individual_type::bool_type								bool_type;
		typedef typename_type_k individual_type::float_type								float_type;
		typedef typename_type_k individual_type::index_type								index_type;
		typedef typename_type_k individual_type::int_type								int_type;
		typedef typename_type_k individual_type::scopes_type							scopes_type;
		typedef typename_type_k scopes_type::scope_type									scope_type;
		typedef Rand																	random_type;
		typedef EXTL_NS_DETAIL(float_mutation_impl)<Rand>								mutation_impl_type;
	/// @}

	private:
		scopes_type const*																m_psps;
	
	private:
		scopes_type const&	sps() const		{ EXTL_ASSERT(NULL != m_psps); return *m_psps;		}

	/// \name Constructors
	/// @{
	public:
		fopti_mutation_traits()
			: base_type(), m_psps(NULL)
		{
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(random_type& rand, scopes_type const& sps)
		{
			base_type::init(rand);
			m_psps = &sps;
		}
		/// invariance
		bool_type is_valid() const
		{
			if (NULL == m_psps) return e_false_v;
			return base_type::is_valid();
		}
	/// @}

	/// \name Implemention
	/// @{
	public:
		/// mutate idl
		individual_type& do_mutate(individual_type& idl)
		{
			size_type n = idl.size();
			EXTL_ASSERT(n > 0);

			for (size_type i = 0; i < n; ++i)
			{
				idl.value(i, mutation_impl_type::mutate(idl.value(i), sps()[i].size(), this->rand()));
			}

			return idl;
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_MUTATION_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
