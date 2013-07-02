/* ///////////////////////////////////////////////////////////////////////
 * File:		logical.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief:		The Logical Operation 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_LOGICAL_H
#define EXTL_MPL_LOGICAL_H

/*!\file logical.h
 * \brief logical class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_BEGIN_WHOLE_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_MPL_SUPPORT
/* //////////////////////////////////////////////////////////////////// */

/*!\brief: and_ class
 * 
 * \ingroup extl_group_mpl
 */
template < e_bool_t b1, e_bool_t b2, \
			e_bool_t b3 = e_true_v, e_bool_t b4 = e_true_v, e_bool_t b5 = e_true_v, e_bool_t b6 = e_true_v, e_bool_t b7 = e_true_v >
struct and_;	/* Default: binary */

template < e_bool_t b1, e_bool_t b2, e_bool_t b3, e_bool_t b4, e_bool_t b5, e_bool_t b6, e_bool_t b7 >
struct and_
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct and_< e_true_v, e_true_v, e_true_v, e_true_v, e_true_v, e_true_v, e_true_v >
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};


/*!\brief: or_ class
 * 
 * \ingroup extl_group_mpl
 */
template <e_bool_t b1, e_bool_t b2, \
			e_bool_t b3 = e_false_v, e_bool_t b4 = e_false_v, e_bool_t b5 = e_false_v, e_bool_t b6 = e_false_v, e_bool_t b7 = e_false_v>
struct or_;	/* Default: binary */

template <e_bool_t b1, e_bool_t b2, e_bool_t b3, e_bool_t b4, e_bool_t b5, e_bool_t b6, e_bool_t b7>
struct or_
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct or_<e_false_v, e_false_v, e_false_v, e_false_v, e_false_v, e_false_v, e_false_v>
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};

/*!\brief: not_ class
 * 
 * \ingroup extl_group_mpl
 */
template < e_bool_t b >
struct not_
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct not_< e_true_v >
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MPL_LOGICAL_H */
/* //////////////////////////////////////////////////////////////////// */
