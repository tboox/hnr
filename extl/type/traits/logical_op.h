/* ///////////////////////////////////////////////////////////////////////
 * File:		logical_op.h		
 *
 * Created:		08.02.07					
 * Updated:		08.07.09
 *
 * Brief: logical operation
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_TRAITS_LOGICAL_OP_H
#define EXTL_TYPE_TRAITS_LOGICAL_OP_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TYPE_TRAITS_SUPPORT

// equal
template <e_uint_t b1, e_uint_t b2>
struct op_eq
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (b1 == b2));
};

template <e_uint_t b1, e_uint_t b2>
struct op_ne
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = (b1 != b2));
};

// and

#ifndef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
#	define EXTL_OP_AND_DEF_ARG_2	e_true_v, e_true_v, e_true_v, e_true_v, e_true_v
#else
#	define EXTL_OP_AND_DEF_ARG_2	e_true_v
#endif

template <e_bool_t b1, e_bool_t b2, \
			e_bool_t b3 = e_true_v, e_bool_t b4 = e_true_v, e_bool_t b5 = e_true_v, e_bool_t b6 = e_true_v, e_bool_t b7 = e_true_v>
struct op_and	// default: binary 
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct op_and<e_true_v, e_true_v, e_true_v, e_true_v, e_true_v, e_true_v, e_true_v>
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};

// or
#ifndef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
#	define EXTL_OP_OR_DEF_ARG_2	e_false_v, e_false_v, e_false_v, e_false_v, e_false_v
#else
#	define EXTL_OP_OR_DEF_ARG_2 e_false_v
#endif

template <e_bool_t b1, e_bool_t b2, \
			e_bool_t b3 = e_false_v, e_bool_t b4 = e_false_v, e_bool_t b5 = e_false_v, e_bool_t b6 = e_false_v, e_bool_t b7 = e_false_v>
struct op_or	// default: binary 
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct op_or<e_false_v, e_false_v, e_false_v, e_false_v, e_false_v, e_false_v, e_false_v>
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};

// not
template <e_bool_t b>
struct op_not
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct op_not<e_true_v>
{
    EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_SUPPORT */
/* //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_TRAITS_LOGICAL_OP_H */
/* //////////////////////////////////////////////////////////////////// */
