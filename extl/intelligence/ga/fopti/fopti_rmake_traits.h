/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_rmake_traits.h		
 *
 * Created:		08.09.13
 * Updated:		08.11.07
 *
 * Brief: The fopti_rmake_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_RMAKE_TRAITS_H
#define EXTL_INTELLIGENCE_GA_FOPTI_RMAKE_TRAITS_H

/*!\file fopti_rmake_traits.h
 * \brief The fopti_rmake_traits class
 */
#ifndef __cplusplus
#	error fopti_rmake_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_rmake_traits
 * 
 * \param Pop The population type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		>
class fopti_rmake_traits
	: public rmake_traits_base<fopti_rmake_traits<Pop, Rand>, Pop, Rand>
{
	/// \name Types
	/// @{
	public:
		typedef rmake_traits_base<fopti_rmake_traits<Pop, Rand>, Pop, Rand>		base_type;
		typedef Pop																population_type;
		typedef typename_type_k population_type::individual_type				individual_type;
		typedef typename_type_k individual_type::size_type						size_type;
		typedef typename_type_k individual_type::bool_type						bool_type;
		typedef typename_type_k individual_type::float_type						float_type;
		typedef typename_type_k individual_type::index_type						index_type;
		typedef typename_type_k individual_type::int_type						int_type;
		typedef typename_type_k individual_type::scopes_type					scopes_type;
		typedef Rand															random_type;
	/// @}

	/// \name Members
	/// @{
	private:
		scopes_type const*														m_psps;
	//// @}
	
	private:
		scopes_type const&	sps() const	{ return *m_psps;	}

	/// \name Constructors
	/// @{
	public:
		fopti_rmake_traits()
			: base_type(), m_psps(NULL)
		{}
	/// @}

	/// \name Methods
	// @{
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
	///@}

	/// \name Implemention
	/// @{
	public:
		individual_type& do_rmake(individual_type& idl)
		{
			size_type var_n = idl.size();
			for (index_type i = 0; i < var_n; ++i)
			{
				idl.value(i, this->rand().fgenerate(sps()[i].lower(), sps()[i].upper()));
			}
			return idl;
		}

		individual_type& do_rmake_at_hand(individual_type& idl)
		{
			size_type var_n = idl.size();
			for (index_type i = 0; i < var_n; ++i)
			{
				float_type len = sps()[i].size() * 0.0001;
				idl.value(i, this->rand().fgenerate(idl.value(i) - len, idl.value(i) + len));
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
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_RMAKE_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
