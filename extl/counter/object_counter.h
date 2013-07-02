/* ///////////////////////////////////////////////////////////////////////
 * File:		object_counter.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: object_counter class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_OBJECT_COUNTER_H
#define EXTL_OBJECT_COUNTER_H

/*!\file object_counter.h
 * \brief object_counter class
 */
#ifndef __cplusplus
#	error object_counter.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!\brief object_counter class
 *
 * \param T The object type
 *
 * \ingroup extl_group_counter
 */
template < typename_param_k T >
class object_counter
{
	/// \name Types
	/// @{
	public:
		typedef T					value_type;
		typedef object_counter<T>	class_type;
		typedef e_size_t			size_type;
	/// @}

	/// \name Members
	/// @{
	private:
		static size_type			s_object_count;		
		static size_type			s_construct_count;	
		static size_type			s_destruct_count;	
		static size_type			s_copy_count;		
	/// @}
	
	/// \name Constructors
	/// @{
	protected:
		object_counter()
		{
			++class_type::s_construct_count;
		}
		~object_counter()
		{
			++class_type::s_destruct_count;
		}
		object_counter(class_type const&)
		{
			++class_type::s_copy_count;
			++class_type::s_construct_count;
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		static size_type get_object_count()
		{
			EXTL_ASSERT(!(class_type::s_construct_count < class_type::s_destruct_count));
			return (class_type::s_construct_count - class_type::s_destruct_count);
		}
		static size_type get_construct_count()
		{
			return class_type::s_construct_count;
		}
		static size_type get_destruct_count()
		{
			return class_type::s_destruct_count;
		}
		static size_type get_copy_count()
		{
			return class_type::s_copy_count;
		}
	/// @}
};

template < typename_param_k T >
typename_type_k object_counter<T>::size_type object_counter<T>::s_object_count = 0;
template < typename_param_k T >
typename_type_k object_counter<T>::size_type object_counter<T>::s_construct_count = 0;
template < typename_param_k T >
typename_type_k object_counter<T>::size_type object_counter<T>::s_destruct_count = 0;
template < typename_param_k T >
typename_type_k object_counter<T>::size_type object_counter<T>::s_copy_count = 0;

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_OBJECT_COUNTER_TEST_ENABLE
#	include "unit_test/object_counter_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_OBJECT_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
