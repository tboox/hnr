/* ///////////////////////////////////////////////////////////////////////
 * File:		func_base.h		
 *
 * Created:		08.11.20			
 * Updated:		08.11.20
 *
 * Brief:		the func_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_FUNC_BASE_H
#define EXTL_FUNCTIONAL_FUNC_BASE_H

/*!\file func_base.h
 * \brief func_base class
 */
#ifndef __cplusplus
#	error func_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template<	e_size_t PN					
		,	typename_param_k RT			
		,	typename_param_k P1			= e_null_t
		,	typename_param_k P2			= e_null_t
		,	typename_param_k P3			= e_null_t
		,	typename_param_k P4			= e_null_t
		,	typename_param_k P5			= e_null_t
		,	typename_param_k P6			= e_null_t
		,	typename_param_k P7			= e_null_t
		,	typename_param_k P8			= e_null_t
		,	typename_param_k P9			= e_null_t
		>
#else
template<	e_size_t PN		
		,	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2			
		,	typename_param_k P3			
		,	typename_param_k P4			
		,	typename_param_k P5			
		,	typename_param_k P6			
		,	typename_param_k P7			
		,	typename_param_k P8			
		,	typename_param_k P9			
		>
#endif
struct func_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;				
	typedef P3	param3_type;				
	typedef P4	param4_type;				
	typedef P5	param5_type;				
	typedef P6	param6_type;				
	typedef P7	param7_type;				
	typedef P8	param8_type;				
	typedef P9	param9_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = PN);				
};

template<	typename_param_k RT			
		>
struct func0_base
{
	typedef RT	return_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 0);				
};

template<	typename_param_k RT			
		,	typename_param_k P1			
		>
struct func1_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 1);				
};

template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2				
		>
struct func2_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 2);				
};

template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2		
		,	typename_param_k P3
		>
struct func3_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;	
	typedef P3	param3_type;
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 3);				
};

template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2			
		,	typename_param_k P3			
		,	typename_param_k P4			
		>
struct func4_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;				
	typedef P3	param3_type;				
	typedef P4	param4_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 4);				
};


template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2			
		,	typename_param_k P3			
		,	typename_param_k P4			
		,	typename_param_k P5			
		>
struct func5_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;				
	typedef P3	param3_type;				
	typedef P4	param4_type;				
	typedef P5	param5_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 5);				
};

template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2			
		,	typename_param_k P3			
		,	typename_param_k P4			
		,	typename_param_k P5			
		,	typename_param_k P6			
		>
struct func6_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;				
	typedef P3	param3_type;				
	typedef P4	param4_type;				
	typedef P5	param5_type;				
	typedef P6	param6_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 6);				
};


template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2			
		,	typename_param_k P3			
		,	typename_param_k P4			
		,	typename_param_k P5			
		,	typename_param_k P6			
		,	typename_param_k P7			
		>
struct func7_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;				
	typedef P3	param3_type;				
	typedef P4	param4_type;				
	typedef P5	param5_type;				
	typedef P6	param6_type;				
	typedef P7	param7_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 7);				
};

template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2			
		,	typename_param_k P3			
		,	typename_param_k P4			
		,	typename_param_k P5			
		,	typename_param_k P6			
		,	typename_param_k P7			
		,	typename_param_k P8			
		>
struct func8_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;				
	typedef P3	param3_type;				
	typedef P4	param4_type;				
	typedef P5	param5_type;				
	typedef P6	param6_type;				
	typedef P7	param7_type;				
	typedef P8	param8_type;																
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 8);				
};

template<	typename_param_k RT			
		,	typename_param_k P1			
		,	typename_param_k P2			
		,	typename_param_k P3			
		,	typename_param_k P4			
		,	typename_param_k P5			
		,	typename_param_k P6			
		,	typename_param_k P7			
		,	typename_param_k P8			
		,	typename_param_k P9			
		>
struct func9_base
{
	typedef RT	return_type;				
	typedef P1	param1_type;				
	typedef P2	param2_type;				
	typedef P3	param3_type;				
	typedef P4	param4_type;				
	typedef P5	param5_type;				
	typedef P6	param6_type;				
	typedef P7	param7_type;				
	typedef P8	param8_type;				
	typedef P9	param9_type;															
																							
	EXTL_STATIC_MEMBER_CONST(e_size_t, param_num = 9);				
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_FUNCTIONAL_FUNC_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
