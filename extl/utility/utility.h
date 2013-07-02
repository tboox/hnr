/* ///////////////////////////////////////////////////////////////////////
 * File:		utility.h		
 *
 * Created:		08.02.17				
 * Updated:		08.11.20
 *
 * Brief:		The Utility Library
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_UTILITY_H
#define EXTL_UTILITY_H

#ifndef __cplusplus
#	error utility.h need be supported by c++.
#endif

/*!\file utility.h
 * \brief The utility library
 * \defgroup extl_group_utility
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "address_of.h"
#include "element_num.h"
#include "offset_of.h"
#include "operator_bool.h"
#include "operators.h"
#include "singleton.h"
#include "static_assert.h"
#include "static_message_assert.h"
#include "suppress_unused.h"
#include "uncopyable.h"
#include "bit_op.h"

#ifdef EXTL_UTILITY_PROPERTIES_SUPPORT
#	include "properties.h"
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_H */
/* //////////////////////////////////////////////////////////////////// */
