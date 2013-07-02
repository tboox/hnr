/* ///////////////////////////////////////////////////////////////////////
 * File:		mem_func_ptr.h		
 *
 * Created:		08.06.09			
 * Updated:		08.07.18
 *
 * Brief: mem_func_ptr class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_FUNCTIONAL_MEM_FUNC_PTR_H
#define EXTL_FUNCTIONAL_MEM_FUNC_PTR_H

/*!\file mem_func_ptr.h
 * \brief mem_func_ptr class
 */
#ifndef __cplusplus
#	error mem_func_ptr.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../type/traits/mem_func_ptr_traits.h"
#include "../type/traits/is_void.h"
#include "../algorithm/algorithm.h"
#include "../utility/operator_bool.h"

#ifdef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#	include "../type/traits/call_traits.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_FUNCTIONAL_MEM_FUNC_PTR_SUPPORT) 
#	error extl::mem_func_ptr is not supported by current compiler.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_MEM_FUNC_PTR_PARAM_TYPE(T)		typename_type_k call_traits<T>::param_type

#define EXTL_MEM_FUNC_PTR_OPERATOR_0		

#define EXTL_MEM_FUNC_PTR_OPERATOR_1							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1			

#define EXTL_MEM_FUNC_PTR_OPERATOR_2							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2			

#define EXTL_MEM_FUNC_PTR_OPERATOR_3							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param3_type) a3			

#define EXTL_MEM_FUNC_PTR_OPERATOR_4							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param3_type) a3				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param4_type) a4			

#define EXTL_MEM_FUNC_PTR_OPERATOR_5							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param3_type) a3				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param4_type) a4				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param5_type) a5			

#define EXTL_MEM_FUNC_PTR_OPERATOR_6							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param3_type) a3				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param4_type) a4				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param5_type) a5				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param6_type) a6			

#define EXTL_MEM_FUNC_PTR_OPERATOR_7							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param3_type) a3				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param4_type) a4				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param5_type) a5				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param6_type) a6				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param7_type) a7			

#define EXTL_MEM_FUNC_PTR_OPERATOR_8							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param3_type) a3				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param4_type) a4				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param5_type) a5				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param6_type) a6				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param7_type) a7				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param8_type) a8			

#define EXTL_MEM_FUNC_PTR_OPERATOR_9							\
	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param1_type) a1				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param2_type) a2				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param3_type) a3				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param4_type) a4				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param5_type) a5				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param6_type) a6				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param7_type) a7				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param8_type) a8				\
,	EXTL_MEM_FUNC_PTR_PARAM_TYPE(param9_type) a9

#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_0	
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_1	a1
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_2	a1, a2
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_3	a1, a2, a3
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_4	a1, a2, a3, a4
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_5	a1, a2, a3, a4, a5
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_6	a1, a2, a3, a4, a5, a6
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_7	a1, a2, a3, a4, a5, a6, a7
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_8	a1, a2, a3, a4, a5, a6, a7, a8
#define EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_9	a1, a2, a3, a4, a5, a6, a7, a8, a9

#define EXTL_MEM_FUNC_PTR_OPERATION_IMPL(num)																	\
return_type operator()(EXTL_MEM_FUNC_PTR_OPERATOR_##num)														\
{																												\
	EXTL_ASSERT(!get_derive().is_empty());																		\
	return (get_derive().container()->*(get_derive().get_ptr()))(EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_##num);	\
}

#define EXTL_MEM_FUNC_PTR_VOID_RET_OPERATION_IMPL(num)															\
return_type operator()(EXTL_MEM_FUNC_PTR_OPERATOR_##num)														\
{																												\
	EXTL_ASSERT(!get_derive().is_empty());																		\
	(get_derive().container()->*(get_derive().get_ptr()))(EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_##num);			\
}

#define EXTL_MEM_FUNC_PTR_IMPL_SPEC_(is_void_return, operation_impl, param_num)									\
EXTL_TEMPLATE_SPECIALISATION																					\
class mem_func_ptr_impl<is_void_return, param_num>																\
{																												\
	public:																										\
		template<typename_param_k D, typename_param_k FP>														\
		class result																							\
		{																										\
		public:																									\
			typedef D														derived_type;						\
			typedef result													class_type;							\
			typedef FP														mem_func_ptr_type;					\
			typedef mem_func_ptr_traits<mem_func_ptr_type>					mem_func_ptr_traits_type;			\
																												\
		public:																									\
			typedef typename_type_k mem_func_ptr_traits_type::container_type	container_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::return_type		return_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param1_type		param1_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param2_type		param2_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param3_type		param3_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param4_type		param4_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param5_type		param5_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param6_type		param6_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param7_type		param7_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param8_type		param8_type;					\
			typedef typename_type_k mem_func_ptr_traits_type::param9_type		param9_type;					\
																												\
		private:																								\
			derived_type& get_derive()				{ return static_cast<derived_type&>(*this);			}		\
			derived_type const& get_derive() const	{ return static_cast<derived_type const&>(*this);	}		\
																												\
		public:																									\
			operation_impl																						\
																												\
		public:																									\
			result(){};																							\
		private:																								\
			result(class_type const&);																			\
			class_type& operator =(class_type const&);															\
		};																										\
};

#define EXTL_MEM_FUNC_PTR_IMPL_SPEC(num)			EXTL_MEM_FUNC_PTR_IMPL_SPEC_(e_false_v, EXTL_MEM_FUNC_PTR_OPERATION_IMPL(num), num)
#define EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(num)	EXTL_MEM_FUNC_PTR_IMPL_SPEC_(e_true_v, EXTL_MEM_FUNC_PTR_VOID_RET_OPERATION_IMPL(num), num)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	e_bool_t is_void_return
		,	e_size_t param_num
		>
class mem_func_ptr_impl{};

EXTL_MEM_FUNC_PTR_IMPL_SPEC(0)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(1)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(2)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(3)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(4)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(5)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(6)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(7)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(8)
EXTL_MEM_FUNC_PTR_IMPL_SPEC(9)

EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(0)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(1)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(2)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(3)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(4)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(5)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(6)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(7)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(8)
EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC(9)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Macros 
 */
#undef EXTL_MEM_FUNC_PTR_OPERATOR_0
#undef EXTL_MEM_FUNC_PTR_OPERATOR_1
#undef EXTL_MEM_FUNC_PTR_OPERATOR_2
#undef EXTL_MEM_FUNC_PTR_OPERATOR_3
#undef EXTL_MEM_FUNC_PTR_OPERATOR_4
#undef EXTL_MEM_FUNC_PTR_OPERATOR_5
#undef EXTL_MEM_FUNC_PTR_OPERATOR_6
#undef EXTL_MEM_FUNC_PTR_OPERATOR_7
#undef EXTL_MEM_FUNC_PTR_OPERATOR_8
#undef EXTL_MEM_FUNC_PTR_OPERATOR_9

#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_0
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_1
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_2
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_3
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_4
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_5
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_6
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_7
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_8
#undef EXTL_MEM_FUNC_PTR_OPERATOR_PARAM_9

#undef EXTL_MEM_FUNC_PTR_OPERATION_IMPL
#undef EXTL_MEM_FUNC_PTR_VOID_RET_OPERATION_IMPL
#undef EXTL_MEM_FUNC_PTR_IMPL_SPEC_
#undef EXTL_MEM_FUNC_PTR_IMPL_SPEC
#undef EXTL_MEM_FUNC_PTR_IMPL_VOID_RET_SPEC
#undef EXTL_MEM_FUNC_PTR_PARAM_TYPE
/*!\brief mem_func_ptr class
 * 
 * \param FP The member function pointer type
 *
 * \ingroup extl_group_functional
 */
template<typename_param_k FP>
class mem_func_ptr
	: public EXTL_NS_DETAIL(mem_func_ptr_impl)	<	(is_void< typename_type_k mem_func_ptr_traits<FP>::return_type >::value)
											#if EXTL_WORKAROUND_MSVC(==, 1200) // need not bracket at VC6.0
												,	mem_func_ptr_traits<FP>::param_num
											#else
												,	(mem_func_ptr_traits<FP>::param_num) // need bracket at BCC 5.51
											#endif
												>::template_qual_k result<mem_func_ptr<FP>, FP>
{
	/// \name Types
	/// @{
	public:
		typedef mem_func_ptr<FP>												class_type;
		typedef FP																mem_func_ptr_type;
		typedef mem_func_ptr_traits<FP>											mem_func_ptr_traits_type;
		typedef e_size_t														size_type;
		typedef e_bool_t														bool_type;
	/// @}

	/// \name The parameter type
	/// @{
	public:
		typedef typename_type_k mem_func_ptr_traits_type::container_type	container_type;
		typedef typename_type_k mem_func_ptr_traits_type::return_type		return_type;
		typedef typename_type_k mem_func_ptr_traits_type::param1_type		param1_type;
		typedef typename_type_k mem_func_ptr_traits_type::param2_type		param2_type;
		typedef typename_type_k mem_func_ptr_traits_type::param3_type		param3_type;
		typedef typename_type_k mem_func_ptr_traits_type::param4_type		param4_type;
		typedef typename_type_k mem_func_ptr_traits_type::param5_type		param5_type;
		typedef typename_type_k mem_func_ptr_traits_type::param6_type		param6_type;
		typedef typename_type_k mem_func_ptr_traits_type::param7_type		param7_type;
		typedef typename_type_k mem_func_ptr_traits_type::param8_type		param8_type;
		typedef typename_type_k mem_func_ptr_traits_type::param9_type		param9_type;
	/// @

	public:
		/// The number of parameter
		EXTL_STATIC_MEMBER_CONST(size_type, param_num = mem_func_ptr_traits_type::param_num);

	/// \name Members
	/// @{
	private:
		container_type*						m_container;
		mem_func_ptr_type					m_fp;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k mem_func_ptr(container_type* container = NULL, mem_func_ptr_type fp = NULL)
			: m_container(container), m_fp(fp)
		{
		}
		mem_func_ptr(class_type const& rhs)
			: m_container(rhs.m_container), m_fp(rhs.m_fp)
		{
		}
		~mem_func_ptr()
		{
			clear();
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		container_type* container()				{ return m_container;							}
		container_type const* container() const	{ return m_container;							}
		mem_func_ptr_type get_ptr()					{ return m_fp;									}
		mem_func_ptr_type const get_ptr() const		{ return m_fp;									}
		bool_type is_empty() const					{ return NULL == m_fp || NULL == m_container;	}
		bool_type empty() const						{ return is_empty();							}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void swap(class_type& rhs)			{ std_swap(m_container, rhs.m_container); std_swap(m_fp, rhs.m_fp);	}
		void clear()						{ m_container = NULL; m_fp = NULL;									}
		void reset(mem_func_ptr_type fp)	{ m_fp = fp;														}
		void reset(class_type const& rhs)	{ class_type(rhs).swap(*this);										}
		void reset(container_type* container = NULL, mem_func_ptr_type fp = NULL)	
		{ 
			m_container = container; 
			m_fp = fp;	
		}

		class_type& operator =(class_type const& rhs)
		{
			class_type(rhs).swap(*this);
			return *this;
		}
		class_type& operator =(mem_func_ptr_type fp)
		{
			reset(fp);
			return *this;
		}
	/// @}

	/// \name Operators Overload
	/// @{
	public:
		/// safe implicit conversion to the bool type 
		EXTL_OPERATOR_BOOL_DEFINE_TYPE_T(class_type, safe_bool_type);
		operator safe_bool_type() const
		{
			return EXTL_OPERATOR_BOOL_RETURN_RESULT(!is_empty());
		}
		/// operator!() overload
		bool_type operator !() const		{ return is_empty();	}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_FUNCTIONAL_MEM_FUNC_PTR_TEST_ENABLE
#	include "unit_test/mem_func_ptr_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_FUNCTIONAL_MEM_FUNC_PTR_H */
/* //////////////////////////////////////////////////////////////////// */
