/* ///////////////////////////////////////////////////////////////////////
 * File:		max_min.h		
 *
 * Created:		08.03.14			
 * Updated:		09.01.26
 *
 * Brief:		The maximum and minimum value
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_MAX_MIN_H
#define EXTL_MATH_MAX_MIN_H

/*!\file max_min.h
 * \brief The maximum and minimum value
 */
#ifndef __cplusplus
#	error max_min.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
#	include "../type/traits/promotion_traits.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT
// maximum 
template<typename_param_k T1, typename_param_k T2>
EXTL_INLINE typename_type_ret_k promotion_traits_2_<T1, T2>::type const 
xtl_max(T1 const v1, T2 const v2)
{
	return (v1 < v2)? v2 : v1;
}

template<typename_param_k T1, typename_param_k T2, typename_param_k T3>
EXTL_INLINE typename_type_ret_k promotion_traits_3_<T1, T2, T3>::type const
xtl_max(T1 const v1, T2 const v2, T3 const v3)
{
	return xtl_max(xtl_max(v1, v2), v3);
}

template<typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4>
EXTL_INLINE typename_type_ret_k promotion_traits_4_<T1, T2, T3, T4>::type const
xtl_max(T1 const v1, T2 const v2, T3 const v3, T4 const v4)
{
	return xtl_max(xtl_max(v1, v2), xtl_max(v3, v4));
}

// minimum 
template<typename_param_k T1, typename_param_k T2>
EXTL_INLINE typename_type_ret_k promotion_traits_2_<T1, T2>::type const 
xtl_min(T1 const v1, T2 const v2)
{
	return (v1 < v2)? v1 : v2;
}

template<typename_param_k T1, typename_param_k T2, typename_param_k T3>
EXTL_INLINE typename_type_ret_k promotion_traits_3_<T1, T2, T3>::type const
xtl_min(T1 const v1, T2 const v2, T3 const v3)
{
	return xtl_min(xtl_min(v1, v2), v3);
}

template<typename_param_k T1, typename_param_k T2, typename_param_k T3, typename_param_k T4>
EXTL_INLINE typename_type_ret_k promotion_traits_4_<T1, T2, T3, T4>::type const
xtl_min(T1 const v1, T2 const v2, T3 const v3, T4 const v4)
{
	return xtl_min(xtl_min(v1, v2), xtl_min(v3, v4));
}

#else
// maximum 
template<typename_param_k T>
EXTL_INLINE T const& xtl_max(T const& v1, T const& v2)
{
	return (v1 < v2)? v2 : v1;
}

template<typename_param_k T>
EXTL_INLINE T const& xtl_max(T const& v1, T const& v2, T const& v3)
{
	return xtl_max(xtl_max(v1, v2), v3);
}

template<typename_param_k T>
EXTL_INLINE T const& xtl_max(T const& v1, T const& v2, T const& v3, T const& v4)
{
	return xtl_max(xtl_max(v1, v2), xtl_max(v3, v4));
}

// minimum 
template<typename_param_k T>
EXTL_INLINE T const& xtl_min(T const& v1, T const& v2)
{
	return (v1 < v2)? v1 : v2;
}

template<typename_param_k T>
EXTL_INLINE T const& xtl_min(T const& v1, T const& v2, T const& v3)
{
	return xtl_min(xtl_min(v1, v2), v3);
}

template<typename_param_k T>
EXTL_INLINE T const& xtl_min(T const& v1, T const& v2, T const& v3, T const& v4)
{
	return xtl_min(xtl_min(v1, v2), xtl_min(v3, v4));
}
#endif /* EXTL_TYPE_TRAITS_PROMOTION_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_MAX_MIN_H */
/* //////////////////////////////////////////////////////////////////// */
