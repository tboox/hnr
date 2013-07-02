/* ///////////////////////////////////////////////////////////////////////
 * File:		_func_def.h		
 *
 * Created:		08.07.18		
 * Updated:		08.07.18
 *
 * Brief: func_..._traits specialization macro definition
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_FUNC_PARAM_T_0	\
	typename_param_k RT			

#define EXTL_FUNC_PARAM_T_1	\
	typename_param_k RT					\
,	typename_param_k P1			

#define EXTL_FUNC_PARAM_T_2	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2			

#define EXTL_FUNC_PARAM_T_3	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2					\
,	typename_param_k P3			

#define EXTL_FUNC_PARAM_T_4	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2					\
,	typename_param_k P3					\
,	typename_param_k P4			

#define EXTL_FUNC_PARAM_T_5	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2					\
,	typename_param_k P3					\
,	typename_param_k P4					\
,	typename_param_k P5			

#define EXTL_FUNC_PARAM_T_6	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2					\
,	typename_param_k P3					\
,	typename_param_k P4					\
,	typename_param_k P5					\
,	typename_param_k P6			

#define EXTL_FUNC_PARAM_T_7	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2					\
,	typename_param_k P3					\
,	typename_param_k P4					\
,	typename_param_k P5					\
,	typename_param_k P6					\
,	typename_param_k P7			

#define EXTL_FUNC_PARAM_T_8	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2					\
,	typename_param_k P3					\
,	typename_param_k P4					\
,	typename_param_k P5					\
,	typename_param_k P6					\
,	typename_param_k P7					\
,	typename_param_k P8			

#define EXTL_FUNC_PARAM_T_9	\
	typename_param_k RT					\
,	typename_param_k P1					\
,	typename_param_k P2					\
,	typename_param_k P3					\
,	typename_param_k P4					\
,	typename_param_k P5					\
,	typename_param_k P6					\
,	typename_param_k P7					\
,	typename_param_k P8					\
,	typename_param_k P9


#define EXTL_FUNC_PARAM_0	
#define EXTL_FUNC_PARAM_1	P1
#define EXTL_FUNC_PARAM_2	P1, P2
#define EXTL_FUNC_PARAM_3	P1, P2, P3
#define EXTL_FUNC_PARAM_4	P1, P2, P3, P4
#define EXTL_FUNC_PARAM_5	P1, P2, P3, P4, P5
#define EXTL_FUNC_PARAM_6	P1, P2, P3, P4, P5, P6
#define EXTL_FUNC_PARAM_7	P1, P2, P3, P4, P5, P6, P7
#define EXTL_FUNC_PARAM_8	P1, P2, P3, P4, P5, P6, P7, P8
#define EXTL_FUNC_PARAM_9	P1, P2, P3, P4, P5, P6, P7, P8, P9

#define EXTL_FUNC_PARAM_WITH_RET_0	RT
#define EXTL_FUNC_PARAM_WITH_RET_1	RT, P1
#define EXTL_FUNC_PARAM_WITH_RET_2	RT, P1, P2
#define EXTL_FUNC_PARAM_WITH_RET_3	RT, P1, P2, P3
#define EXTL_FUNC_PARAM_WITH_RET_4	RT, P1, P2, P3, P4
#define EXTL_FUNC_PARAM_WITH_RET_5	RT, P1, P2, P3, P4, P5
#define EXTL_FUNC_PARAM_WITH_RET_6	RT, P1, P2, P3, P4, P5, P6
#define EXTL_FUNC_PARAM_WITH_RET_7	RT, P1, P2, P3, P4, P5, P6, P7
#define EXTL_FUNC_PARAM_WITH_RET_8	RT, P1, P2, P3, P4, P5, P6, P7, P8
#define EXTL_FUNC_PARAM_WITH_RET_9	RT, P1, P2, P3, P4, P5, P6, P7, P8, P9

#define EXTL_FUNC_PARAM_TYPE_DEF_0	\
typedef RT			return_type;				\
typedef e_null_t	param1_type;				\
typedef e_null_t	param2_type;				\
typedef e_null_t	param3_type;				\
typedef e_null_t	param4_type;				\
typedef e_null_t	param5_type;				\
typedef e_null_t	param6_type;				\
typedef e_null_t	param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_1	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef e_null_t	param2_type;				\
typedef e_null_t	param3_type;				\
typedef e_null_t	param4_type;				\
typedef e_null_t	param5_type;				\
typedef e_null_t	param6_type;				\
typedef e_null_t	param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_2	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef e_null_t	param3_type;				\
typedef e_null_t	param4_type;				\
typedef e_null_t	param5_type;				\
typedef e_null_t	param6_type;				\
typedef e_null_t	param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_3	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef P3			param3_type;				\
typedef e_null_t	param4_type;				\
typedef e_null_t	param5_type;				\
typedef e_null_t	param6_type;				\
typedef e_null_t	param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_4	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef P3			param3_type;				\
typedef P4			param4_type;				\
typedef e_null_t	param5_type;				\
typedef e_null_t	param6_type;				\
typedef e_null_t	param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_5	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef P3			param3_type;				\
typedef P4			param4_type;				\
typedef P5			param5_type;				\
typedef e_null_t	param6_type;				\
typedef e_null_t	param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_6	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef P3			param3_type;				\
typedef P4			param4_type;				\
typedef P5			param5_type;				\
typedef P6			param6_type;				\
typedef e_null_t	param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_7	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef P3			param3_type;				\
typedef P4			param4_type;				\
typedef P5			param5_type;				\
typedef P6			param6_type;				\
typedef P7			param7_type;				\
typedef e_null_t	param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_8	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef P3			param3_type;				\
typedef P4			param4_type;				\
typedef P5			param5_type;				\
typedef P6			param6_type;				\
typedef P7			param7_type;				\
typedef P8			param8_type;				\
typedef e_null_t	param9_type;

#define EXTL_FUNC_PARAM_TYPE_DEF_9	\
typedef RT			return_type;				\
typedef P1			param1_type;				\
typedef P2			param2_type;				\
typedef P3			param3_type;				\
typedef P4			param4_type;				\
typedef P5			param5_type;				\
typedef P6			param6_type;				\
typedef P7			param7_type;				\
typedef P8			param8_type;				\
typedef P9			param9_type;

