/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_func_traits_impl.h		
 *
 * Created:		08.09.09
 * Updated:		08.10.23
 *
 * Brief: The fopti_func_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_DETAIL_FUNC_TRAITS_IMPL_H
#define EXTL_INTELLIGENCE_GA_FOPTI_DETAIL_FUNC_TRAITS_IMPL_H

#ifndef __cplusplus
#	error fopti_func_traits_impl.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_1	idl.value(0)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_2	idl.value(0), idl.value(1)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_3	idl.value(0), idl.value(1), idl.value(2)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_4	idl.value(0), idl.value(1), idl.value(2), idl.value(3)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_5	idl.value(0), idl.value(1), idl.value(2), idl.value(3), idl.value(4)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_6	idl.value(0), idl.value(1), idl.value(2), idl.value(3), idl.value(4), idl.value(5)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_7	idl.value(0), idl.value(1), idl.value(2), idl.value(3), idl.value(4), idl.value(5), idl.value(6)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_8	idl.value(0), idl.value(1), idl.value(2), idl.value(3), idl.value(4), idl.value(5), idl.value(6), idl.value(7)
#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_9	idl.value(0), idl.value(1), idl.value(2), idl.value(3), idl.value(4), idl.value(5), idl.value(6), idl.value(7), idl.value(8)

#define EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(num)												\
EXTL_TEMPLATE_SPECIALISATION																		\
struct fopti_func_traits_impl<num>																	\
{																									\
	template<	typename_param_k D																	\
			,	typename_param_k Idl																\
			,	typename_param_k Func																\
			>																						\
	struct impl																						\
	{																								\
		typedef D												derived_type;						\
		typedef Func												func_type;						\
		typedef Idl												individual_type;					\
		typedef typename_type_k individual_type::float_type		float_type;							\
																									\
		float_type fvalue(individual_type const& idl)												\
		{																							\
			return derive().func()( EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_##num );					\
		}																							\
																									\
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}	\
		derived_type&		derive() 		{ return static_cast<derived_type&>(*this);			}	\
	};																								\
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<e_size_t N>
struct fopti_func_traits_impl
{
	template<	typename_param_k D
			,	typename_param_k Idl
			,	typename_param_k Func
			>
	struct impl;
};

EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(1)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(2)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(3)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(4)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(5)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(6)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(7)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(8)
EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC(9)



template<	typename_param_k Idl
		,	typename_param_k Func
		>
struct fopti_func_traits
#if EXTL_WORKAROUND_BORLAND(==, 0x551)
	: fopti_func_traits_impl<(Idl::variable_count)>::template_qual_k 
#else
	: fopti_func_traits_impl<Idl::variable_count>::template_qual_k 
#endif
	impl<fopti_func_traits<Idl, Func>, Idl, Func>
{
	public:
		typedef Func											func_type;				
		typedef Idl												individual_type;		
		typedef typename_type_k individual_type::float_type		float_type;
	
	private:
		func_type												m_func;

	public:
		func_type const&	func() const						{ return m_func;	}
		func_type&			func()								{ return m_func;	}
		void				func(func_type const& func)			{ m_func = func;	}
};


/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_SPEC
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_1
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_2
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_3
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_4
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_5
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_6
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_7
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_8
#undef EXTL_FOPTI_DETAIL_FUNC_TRAITS_IMPL_IDL_9

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_DETAIL_FUNC_TRAITS_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
