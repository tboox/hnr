/* ///////////////////////////////////////////////////////////////////////
 * File:		stack_buffer.h		
 *
 * Created:		08.06.06				
 * Updated:		08.06.06
 *
 * Brief:		stack_buffer class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_STACK_BUFFER_H
#define EXTL_MEMORY_STACK_BUFFER_H

/*!\file stack_buffer.h
 * \brief stack_buffer class
 */

#ifndef __cplusplus
#	error stack_buffer.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "buffer_base.h"
#include "memory_traits_selector.h"
#include "allocator_selector.h"
#include "../error/error.h"

/// The maximum number of the stack storage space 
#define EXTL_MEMORY_STACK_BUFFER_MAX_SPACE	256

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief: stack_buffer class
 * 
 * \param T The element type
 * \param MAX_SPACE The static storage space
 * \param M The memory traits type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t MAX_SPACE = EXTL_MEMORY_STACK_BUFFER_MAX_SPACE
		,	typename_param_k M = typename_type_def_k memory_traits_selector<T>::memory_traits_type
#else
		,	e_size_t MAX_SPACE
		,	typename_param_k M
#endif
		>
class stack_buffer
	: public buffer_base<	stack_buffer< T, MAX_SPACE, M >
						,	typename_type_k allocator_selector<T>::allocator_type
						,	M
						>
{
	/// \name Types
	/// @{
	public:
		typedef stack_buffer											class_type;		
		typedef buffer_base<	class_type
							,	typename_type_k allocator_selector<T>::allocator_type
							,	M
							>											base_type;	
		typedef typename_type_k base_type::value_type					value_type;		
		typedef typename_type_k base_type::memory_traits_type			memory_traits_type;	
		typedef	typename_type_k base_type::allocator_type				allocator_type;		
		typedef typename_type_k base_type::pointer						pointer;			
		typedef typename_type_k base_type::const_pointer				const_pointer;		
		typedef typename_type_k base_type::reference					reference;			
		typedef typename_type_k base_type::const_reference				const_reference;	
		typedef typename_type_k base_type::size_type					size_type;			
		typedef typename_type_k base_type::difference_type				difference_type;
		typedef typename_type_k base_type::iterator						iterator;
		typedef typename_type_k base_type::const_iterator				const_iterator;
		typedef typename_type_k base_type::reverse_iterator				reverse_iterator;
		typedef typename_type_k base_type::const_reverse_iterator		const_reverse_iterator;
		typedef typename_type_k base_type::bool_type					bool_type;
		typedef typename_type_k base_type::index_type					index_type;
		typedef typename_type_k memory_traits_type::initialiser_type	initialiser_type;
	/// @}


	/// \name Members
	/// @{
	private:
		/// The data type
		struct data_type
		{
			value_type	data[MAX_SPACE];		//!< The static memory storage 
		};
		data_type	m_data;					//!< The static memory storage 
		size_type	m_size;					//!< The size of the used storage 
	/// @}

	private:
		friend class buffer_base<	class_type
								,	typename_type_k allocator_selector<T>::allocator_type
								,	M
								>;

	/// \name Constructors
	/// @{
	public:
		/// Constructs a stack_buffer with the given number of elements
		explicit_k stack_buffer(size_type const& n = 0)
			: base_type(), m_size(0)
		{
			resize(n);
		}

		/// Constructs a stack_buffer with n values from the given buffer at the specified position 
		stack_buffer(const_pointer buf, size_type n, size_type pos = 0)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(buf, n, pos);
		}

		/// Constructs a stack_buffer from the given buffer 
		stack_buffer(class_type const& buf)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(buf, buf.size());
		}

		/// Constructs a stack_buffer with n values from the given buffer at the specified position 
		stack_buffer(class_type const& buf, size_type n, size_type pos = 0)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(buf, n, pos);
		}

		/// Constructs with n values
		explicit_k stack_buffer(const_reference v, size_type n)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(v, n);
		}

		/// Constructs from range [first, last) with the const pointer
		stack_buffer(const_pointer first, const_pointer last)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(first, last);
		}
		/// Constructs from range [first, last) with the const iterator
		stack_buffer(const_iterator first, const_iterator last)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(first, last);
		}
		/// Constructs from range [first, last) with the const reverse iterator
		stack_buffer(const_reverse_iterator first, const_reverse_iterator last)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(first, last);
		}
	#if defined(EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT) \
			&& !defined(EXTL_COMPILER_IS_DMC)
		/// Constructs from range [first, last) with the input iterator
		template < typename_param_k _InIt >
		stack_buffer(_InIt first, _InIt last)
			: base_type(), m_size(0)
		{
			this->clear();
			base_type::assign(first, last);
		}
	#endif

		/// Destructor
		~stack_buffer() EXTL_THROW_0() 
		{
			EXTL_STATIC_ASSERT(0 != MAX_SPACE);
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns the pointer to the buffer
		pointer data()					
		{ 
			if(0 == m_size) return NULL;
			return m_data.data;	
		}
		/// Returns the const pointer to the buffer
		const_pointer data()	const	
		{ 
			if(0 == m_size) return NULL;
			return m_data.data;	
		}
		/// Returns the size of the buffer
		size_type size()		const	{ return m_size;	}
		/// Returns the capacity size of the buffer
		size_type capacity()	const	{ return MAX_SPACE;		}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& buf)	{ return base_type::operator=(buf);	}
		class_type& operator=(const_reference v)		{ return base_type::operator=(v);	}
	/// @}
		
	/// \name Mutators
	/// @{
	public:
		/*!\brief Resizes the size of buffer
		 *
		 * \note Only resize the capacity of the storage when is_update_size is e_false_v
		 */
		void resize(size_type size, bool_type is_update_size = e_true_v)
		{
			EXTL_ASSERT(is_valid());
			EXTL_MESSAGE_ASSERT(size <= MAX_SPACE, "the buffer is too long");
			EXTL_ASSERT_THROW(size <= MAX_SPACE, std_length_error("the buffer is too long"));
			if (is_update_size) m_size = size;
			EXTL_ASSERT(is_valid());
		}

		/// Swaps storage
		void swap(class_type& rhs) EXTL_THROW_0()
		{
			EXTL_ASSERT(is_valid());

			if (this == &rhs) return ;

			std_swap(m_data, rhs.m_data);
			std_swap(m_size, rhs.m_size);

			EXTL_ASSERT(is_valid());
		}
	/// @}

	/// \name Others
	/// @{
	private:
		/// Invariance 
		bool_type is_valid() const
		{
			if (capacity() < size())
				return e_false_v;
			
			if ((0 < size()) && (NULL == data()))
			{
				return e_false_v;
			}
		
			return e_true_v;
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_STACK_BUFFER_H */
/* //////////////////////////////////////////////////////////////////// */
