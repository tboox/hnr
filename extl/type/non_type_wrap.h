/* ///////////////////////////////////////////////////////////////////////
 * File:		non_type_wrap.h		
 *
 * Created:		08.07.21				
 * Updated:		08.07.21	
 *
 * Brief:  A simple envelope for non-type template parameters
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_NON_TYPE_WRAP_H
#define EXTL_TYPE_NON_TYPE_WRAP_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

#ifdef EXTL_NON_TYPE_WRAP_SUPPORT

template<typename_param_k T, T N>
struct non_type_wrap{};

#endif

template<e_bool_t B>
struct bool_type_wrap{};

template<e_int_t B>
struct int_type_wrap{};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_NON_TYPE_WRAP_H */
/* //////////////////////////////////////////////////////////////////// */
