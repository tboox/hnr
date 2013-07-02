/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_func_traits_impl.h		
 *
 * Created:		08.09.09
 * Updated:		08.11.07
 *
 * Brief: The fopti_func_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_FUNC_TRAITS_H
#define EXTL_INTELLIGENCE_GA_FOPTI_FUNC_TRAITS_H

/*!\file fopti_func_traits.h
 * \brief The fopti_func_traits class
 */
#ifndef __cplusplus
#	error fopti_func_traits.h need be supported by c++.
#endif

#ifndef EXTL_FOPTI_FUNC_TRAITS_SUPPORT
#	error fopti_func_traits_impl.h is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "detail/fopti_func_traits_impl.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_func_traits class
 * 
 * \param Idl The individual type
 * \param Func The function type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Idl
		,	typename_param_k Func
		>
struct fopti_func_traits
#if EXTL_WORKAROUND_BORLAND(==, 0x551)
	: EXTL_NS_DETAIL(fopti_func_traits_impl)<(Idl::variable_count)>::template_qual_k
#else
	: EXTL_NS_DETAIL(fopti_func_traits_impl)<Idl::variable_count>::template_qual_k 
#endif
	impl<fopti_func_traits<Idl, Func>, Idl, Func>
{
	/// \name Types
	/// @{
	public:
		typedef Func											func_type;				
		typedef Idl												individual_type;		
		typedef typename_type_k individual_type::float_type		float_type;
		typedef typename_type_k individual_type::scopes_type	scopes_type;
		typedef typename_type_k individual_type::scope_type		scope_type;
		typedef typename_type_k individual_type::size_type		size_type;
		typedef typename_type_k individual_type::bool_type		bool_type;
		typedef typename_type_k individual_type::index_type		index_type;
		typedef typename_type_k individual_type::int_type		int_type;
	/// @}
	
	/// \name Members
	/// @{
	private:
		scopes_type												m_scopes;
		func_type												m_func;
	/// @}

	/// \name Constructors
	/// @{
	public:
		fopti_func_traits()
		{}
		explicit_k fopti_func_traits(func_type const& func)
			: m_func(func)
		{}
	/// @}

	/// \name Attributes
	/// @{
	public:
		func_type const&	func() const						{ return m_func;	}
		func_type&			func()								{ return m_func;	}
		void				func(func_type const& func)			{ m_func = func;	}

		scopes_type const&	scopes() const						{ return m_scopes;	}
		scopes_type&		scopes()							{ return m_scopes;	}
		void				scopes(scopes_type const& sps)		{ m_scopes = sps;	}
	/// @}
};



/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_FUNC_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
