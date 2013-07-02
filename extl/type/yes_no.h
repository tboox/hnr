/* ///////////////////////////////////////////////////////////////////////
 * File:		yes_no.h		
 *
 * Created:		08.03.17				
 * Updated:		08.07.30
 *
 * Brief: yes_no class - result type wrap
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_YES_NO_H
#define EXTL_TYPE_YES_NO_H

/*!\file yes_no.h
 * \brief yes_no class - logical operation 
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * bool ret = (sizeof(yes_type/no_type) == 1)? true : false
 */
// yes_type
typedef struct 	/* sizeof(yes_type) == 1 */
{
   e_byte_t padding[1];
   EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);

}yes_type;

// no_type
typedef struct 	/* sizeof(no_type) !=1 */
{
   e_byte_t padding[8];
   EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);

}no_type;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_YES_NO_H */
/* //////////////////////////////////////////////////////////////////// */
