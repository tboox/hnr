/* ///////////////////////////////////////////////////////////////////////
 * File:		bit_op.h		
 *
 * Created:		09.02.06				
 * Updated:		09.02.06	
 *
 * Brief:		bit operators
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_UTILITY_BIT_OP_H
#define EXTL_UTILITY_BIT_OP_H

/*!\file bit_op.h
 * \brief bit operators
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h" 

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_BIT_OP_GET_FROM_8(p, i, n)		((((e_byte_t*)(p))[(i) / 8] >> ((i) % 8)) & ~((~0) << ((n) % 8)))
#define EXTL_BIT_OP_GET_FROM_16(p, i, n)	((EXTL_BIT_OP_GET_FROM_8(p, i, ((n) % 8)) << 8) | (EXTL_BIT_OP_GET_FROM_8(&(((e_byte_t*)(p))[1]), (i) + 8, (n) - ((n) % 8))))

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_BIT_OP_H */
/* //////////////////////////////////////////////////////////////////// */
