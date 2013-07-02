/* ///////////////////////////////////////////////////////////////////////
 * File:		operator_bool.h		
 *
 * Created:		08.03.01				
 * Updated:		08.05.05	
 *
 * Brief: The safe implicit conversion to bool type - operator bool() const
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/*!\file operator_bool.h
 * \brief The safe implicit conversion to bool type - operator bool() const
 *
 * Note: Overloads operators !, == and != if possible
 */
#ifndef EXTL_UTILITY_OPERATOR_BOOL_H
#define EXTL_UTILITY_OPERATOR_BOOL_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

/// Using in non-template class 
#define EXTL_OPERATOR_BOOL_DEFINE_TYPE(class_type, bool_type) \
			typedef EXTL_NS(operator_bool)< class_type > operator_bool_impl_t; \
			typedef operator_bool_impl_t::return_type bool_type


/// Using in template class 
#define EXTL_OPERATOR_BOOL_DEFINE_TYPE_T(class_type, bool_type) \
			typedef EXTL_NS(operator_bool)< class_type > operator_bool_impl_t; \
			typedef typename_type_k operator_bool_impl_t::return_type bool_type

/// Returns the result of the given expression 
#define EXTL_OPERATOR_BOOL_RETURN_RESULT(expr) \
				operator_bool_impl_t::return_result(expr)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE
/*!\brief operator_bool<> class
 *
 * \param Tag The tag type 
 *
 * \ingroup extl_group_utility
 */
template < typename_param_k Tag > 
class operator_bool
{
	public:
		typedef operator_bool<Tag>	class_type;

#ifdef EXTL_MEM_PTR_AS_BOOL_RET_SUPPORT

		typedef int class_type::*return_type;
		static return_type true_value()
		{
			return &class_type::i;
		}
#else
#	if defined(EXTL_COMPILER_IS_VECTORC)
		typedef class_type const *return_type; /* VC6.0: pointer to array decay implicitly (p[]) */
#	else
		typedef class_type const (*return_type)(); /* ambiguous: when overloading operator[] */
#	endif
		static return_type true_value()
		{
			class_type t;
			void *p = static_cast<void*>(&t);
			return reinterpret_cast<return_type>(p);
		}
#endif
		static return_type false_value()
		{
			return static_cast<return_type>(0);
		}

	private:
		int i;

	public:
#ifdef EXTL_MEMBER_TEMPLATE_FUNCTION_SUPPORT
		template < typename_param_k U >
		static return_type return_result(U expr)
#else
		static return_type return_result(e_bool_t expr)
#endif
		{
			return expr ? true_value() : false_value();
		}

	private:
		void operator delete(void*);

};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_UTILITY_OPERATOR_BOOL_TEST_ENABLE
#	include "unit_test/operator_bool_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_OPERATOR_BOOL_H */
/* //////////////////////////////////////////////////////////////////// */

