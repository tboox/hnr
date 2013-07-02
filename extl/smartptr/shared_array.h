/* ///////////////////////////////////////////////////////////////////////
 * File:		shared_array.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.06
 *
 * Brief: shared_array class - shared array
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SMART_PTR_SHARED_ARRAY_H
#define EXTL_SMART_PTR_SHARED_ARRAY_H

/*!\file shared_array.h
 * \brief shared_array class - shared array
 *
 * - custom thread-safe reference count
 * - safe implicit conversion to the bool type
 * - custom deleter
 *   - default deleter: new_allocator<T>::array_deleter_type
 *   - custom deleter function object:
 *     struct deleter
 *     {
 *         void operator()(int *p)
 *         {
 *           delete[] p;
 *         }
 *     };
 *   - usage: 
 *     - shared_array<int, deleter > p(new int[10]); - using default deleter 
 *     - shared_array<int, deleter > p(new int[10], deleter());
 *     - shared_array<int, deleter > p(new int[10], deleter(...));
 *
 */
#ifndef __cplusplus
#	error shared_array.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../utility/operator_bool.h"
#include "../algorithm/algorithm.h" /* for std_swap */
#include "../counter/shared_counter.h"
#include "../memory/allocator_selector.h"

/* ///////////////////////////////////////////////////////////////////////
 * Warnings
 */
#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER <= 1200)
#	pragma warning(push)
#	pragma warning(disable:4284) /* odd return type for operator-> */
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!\brief shared_array class
 * 
 * \param T The value type 
 * \param D The deleter type
 *
 * \ingroup extl_group_smart_ptr
 */
template<	typename_param_k T
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT	
		,	typename_param_k D = typename_type_def_k new_allocator<T>::array_deleter_type	
	#else
		,	typename_param_k D												
	#endif
		>
class shared_array
{
	/// \name Types
	/// @{
	public:
		typedef shared_array<T, D>								class_type;			
		typedef T												value_type;			
		typedef value_type*										pointer;			
		typedef value_type const*								const_pointer;		
		typedef value_type&										reference;			
		typedef value_type const&								const_reference;	
		typedef e_long_t										index_type;		
		typedef D												deleter_type;	
		
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT	
		typedef shared_counter< value_type, deleter_type >		shared_counter_type;	
	#else
		typedef shared_counter	<	value_type
								,	deleter_type
								,	typename_type_k synch_traits_selector::synch_traits_type
								,	typename_type_k allocator_selector<	e_byte_t >::allocator_type
								>								shared_counter_type;	
	#endif
		typedef typename_type_k shared_counter_type::size_type	size_type;			
	/// @}

	/// \name Members
	/// @{
	private:
		pointer													m_ptr;				
		shared_counter_type										m_shared_counter;	
	/// @}

	/// \name Constructors
	/// @{
	public:
		/* Constructor and destructor */
		shared_array()
			: m_ptr(NULL), m_shared_counter()
		{
		}

		explicit_k shared_array(pointer p)
			: m_ptr(p), m_shared_counter(p)
		{
			EXTL_ASSERT(is_valid());
		}

		shared_array(pointer p, deleter_type const& del)
			: m_ptr(p), m_shared_counter(p, del)
		{
			EXTL_ASSERT(is_valid());
		}
		
		shared_array(class_type const& rhs)
			: m_ptr(rhs.m_ptr), m_shared_counter(rhs.m_shared_counter)
		{
			EXTL_ASSERT(is_valid());
		}
		~shared_array() EXTL_THROW_0()
		{
		}
	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template < typename_param_k T1 >
		explicit_k shared_array(T1* p)
			: m_ptr(p), m_shared_counter(p)
		{
			EXTL_ASSERT(is_valid());
		}

		template < typename_param_k T1, typename_param_k D1 >
		shared_array(shared_array<T1, D1> const& rhs)
			: m_ptr(rhs.m_ptr), m_shared_counter(rhs.m_shared_counter)
		{
			EXTL_ASSERT(is_valid());
		}
	#endif
	/// @}

	public:
		/// operator=() overload 
		class_type& operator=(class_type const& rhs)
		{
			EXTL_ASSERT(is_valid());
			if(this != &rhs) /* Prevent self-assigment */
			{
				m_ptr = rhs.m_ptr;
				m_shared_counter = rhs.m_shared_counter;
			}
			EXTL_ASSERT(is_valid());
			return *this;
		}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		/// operator=() overload 
		template < typename_param_k T1, typename_param_k D1 >
		class_type& operator=(shared_array<T1, D1> const& rhs)
		{
			EXTL_ASSERT(is_valid());
			if(this != &rhs) /* Prevent self-assigment */
			{
				m_ptr = rhs.m_ptr;
				m_shared_counter = rhs.m_shared_counter;
			}
			EXTL_ASSERT(is_valid());
			return *this;
		}
	#endif

	/// \name Accessors
	/// @{
	public:
		reference operator[](index_type const& index) const
		{
			EXTL_ASSERT(NULL != m_ptr);
			EXTL_ASSERT(index >= 0);
			EXTL_ASSERT(is_valid());

			return m_ptr[index];
		}
		const_pointer get_ptr() const
		{
			EXTL_ASSERT(is_valid());
			return m_ptr;
		}

		pointer get_ptr()
		{
			EXTL_ASSERT(is_valid());
			return m_ptr;
		}
		/* Returns the reference count */
		size_type count() const
		{
			EXTL_ASSERT(is_valid());
			return m_shared_counter.count();
		}		
		e_bool_t is_unique() const
		{
			return m_shared_counter.is_unique();
		}
	/// @}

	/// \name Mutators
	/// @{
	public:
		/* swap */
		void swap(class_type& other)
		{
			EXTL_ASSERT(is_valid());
			std_swap(m_ptr, other.m_ptr);
			m_shared_counter.swap(other.m_shared_counter);
			EXTL_ASSERT(is_valid());
		}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template < typename_param_k T1, typename_param_k D1 >
		void swap(shared_array<T1, D1>& other)
		{
			EXTL_ASSERT(is_valid());
			std_swap(m_ptr, other.m_ptr);
			m_shared_counter.swap(other.m_shared_counter);
			EXTL_ASSERT(is_valid());
		}
	#endif
		
		/* Reset the pointer */
		void reset()
		{
			class_type().swap(*this);
		}	
		void reset(pointer p)
		{
			EXTL_ASSERT(p != m_ptr); 
			class_type(p).swap(*this);
		}

	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template < typename_param_k T1 >
		void reset(T1* p)
		{
			EXTL_ASSERT(p != m_ptr); 
			class_type(p).swap(*this);
		}
	#endif
	/// @}

	public:
		/// safe implicit conversion to the bool type 
		EXTL_OPERATOR_BOOL_DEFINE_TYPE_T(class_type, safe_bool_type);
		operator safe_bool_type() const
		{
			return EXTL_OPERATOR_BOOL_RETURN_RESULT(m_ptr != NULL);
		}

		e_bool_t operator !() const							{ return (m_ptr == NULL);	}
	
		/// less than 
		e_bool_t lt(class_type const & rhs) const			{ return m_ptr < rhs.m_ptr;	}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		/// less than 
		template < typename_param_k T1, typename_param_k D1 >
		e_bool_t lt(shared_array<T1, D1> const & rhs) const	{ return m_ptr < rhs.m_ptr;	}
	#endif

	private:
		inline e_bool_t is_valid() const
		{
			if((NULL == m_ptr) != m_shared_counter.is_zero())
			{
				return e_false_v;
			}
			if((NULL != m_ptr) && (m_shared_counter.count() < 1))
			{
				return e_false_v;
			}
			return e_true_v;
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * Operators overload
 */
template< typename_param_k T, typename_param_k D >
inline e_bool_t operator==(shared_array<T, D> const& lhs, shared_array<T, D> const& rhs)
{
    return lhs.get_ptr() == rhs.get_ptr();
}

template< typename_param_k T, typename_param_k D >
inline e_bool_t operator!=(shared_array<T, D> const& lhs, shared_array<T, D> const& rhs)
{
    return lhs.get_ptr() != rhs.get_ptr();
}

/* VC6.0: p != NULL */
#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER == 1200)
template< typename_param_k T, typename_param_k D >
inline e_bool_t operator==(shared_array<T, D> const& lhs, void* rhs)
{
    return lhs.get_ptr() == static_cast<T*>(rhs);
}

template< typename_param_k T, typename_param_k D >
inline e_bool_t operator!=(shared_array<T, D> const& lhs, void* rhs)
{
    return lhs.get_ptr() != static_cast<T*>(rhs);
}
#endif

template< typename_param_k T, typename_param_k D >
inline e_bool_t operator<(shared_array<T, D> const& lhs, shared_array<T, D> const& rhs)
{
    return lhs.lt(rhs);
}
/// swap 
template< typename_param_k T, typename_param_k D >
inline void swap(shared_array<T, D>& lhs, shared_array<T, D>& rhs)
{
    lhs.swap(rhs);
}
/// get pointer shim 
template< typename_param_k T, typename_param_k D >
inline T const* get_ptr(shared_array<T, D> const& p)
{
    return p.get_ptr();
}

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_SHARED_ARRAY_TEST_ENABLE
#	include "unit_test/shared_array_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Warnings
 */
#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER <= 1200)
#	pragma warning(pop)
#endif  

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template< typename_param_k T, typename_param_k D >
inline void swap(EXTL_NS(shared_array)<T, D>& lhs, EXTL_NS(shared_array)<T, D>& rhs)
{
    lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SMART_PTR_SHARED_ARRAY_H */
/* //////////////////////////////////////////////////////////////////// */

