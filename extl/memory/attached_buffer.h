/* ///////////////////////////////////////////////////////////////////////
 * File:		attached_buffer.h		
 *
 * Created:		08.06.14			
 * Updated:		08.06.14
 *
 * Brief: attached_buffer class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_ATTACHED_BUFFER_H
#define EXTL_MEMORY_ATTACHED_BUFFER_H

/*!\file attached_buffer.h
 * \brief attached_buffer class
 */

#ifndef __cplusplus
#	error attached_buffer.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "buffer_base.h"
#include "memory_traits_selector.h"
#include "allocator_selector.h"
#include "../utility/uncopyable.h"

/// The maximum number of the storage space of the attached buffer
#define EXTL_MEMORY_ATTACHED_BUFFER_INFINITY_SPACE	-1
#define EXTL_MEMORY_ATTACHED_BUFFER_MAX_SPACE		256

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief Attaches a buffer
 *
 * \param T The element type
 * \param MAX_SPACE The maximum size of the attached buffer
 * \param M The memory traits type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t MAX_SPACE = EXTL_MEMORY_ATTACHED_BUFFER_MAX_SPACE
		,	typename_param_k M = typename_type_def_k memory_traits_selector<T>::memory_traits_type
#else
		,	e_size_t MAX_SPACE
		,	typename_param_k M
#endif
		>
class attached_buffer
	: public buffer_base<	attached_buffer<T, MAX_SPACE, M>
						,	typename_type_k allocator_selector<T>::allocator_type
						,	M
						>
	, private uncopyable<attached_buffer<T, MAX_SPACE, M> >
{
	/// \name Types
	/// @{
	public:
		typedef attached_buffer											class_type;		
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
		pointer			m_data;					//!< The pointer to memory storage 
		size_type		m_size;					//!< The size of the used storage 
	/// @}

	private:
		friend class buffer_base<	class_type
								,	typename_type_k allocator_selector<T>::allocator_type
								,	M
								>;

	/// \name Constructors
	/// @{
	public:
		/// The Default Constructor
		attached_buffer()
			: base_type(), m_data(NULL), m_size(0)
		{
			EXTL_ASSERT(is_valid());
		}
		/// Attaches a given buffer with n values at the specified position
		attached_buffer(const_pointer buf, size_type n, size_type pos = 0)
			: base_type(), m_data(const_cast<pointer>(buf) + pos), m_size(n)
		{
			EXTL_ASSERT(is_valid());
		}

		/// Attaches a given buffer 
		attached_buffer(class_type const& buf)
			: base_type(), m_data(const_cast<pointer>(buf.data())), m_size(buf.size())
		{
			EXTL_ASSERT(is_valid());
		}

		/// Attaches a given buffer with n values at the specified position
		attached_buffer(class_type const& buf, size_type n, size_type pos = 0)
			: base_type(), m_data(const_cast<pointer>(buf.data()) + pos), m_size(n)
		{
			EXTL_ASSERT(is_valid());
		}

		/// Destructor
		~attached_buffer() EXTL_THROW_0() 
		{
			detach();
		}
	/// @}

	/// \name Unused Constructors
	/// @{
	public:
		explicit_k attached_buffer(const_reference /*v*/, size_type /*n*/);
		attached_buffer(const_pointer /*first*/, const_pointer /*last*/);
		attached_buffer(const_iterator /*first*/, const_iterator /*last*/);
		attached_buffer(const_reverse_iterator /*first*/, const_reverse_iterator /*last*/);
	#if defined(EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT) \
			&& !defined(EXTL_COMPILER_IS_DMC)
		template < typename_param_k _InIt >
		attached_buffer(_InIt /*first*/, _InIt /*last*/);
	#endif
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns the pointer to the buffer
		pointer data()					{ if(0 == m_size) return NULL; return m_data;	}
		/// Returns the const pointer to the buffer
		const_pointer data()	const	{ if(0 == m_size) return NULL; return m_data;	}
		/// Returns the size of the buffer
		size_type size()		const	{ return m_size;	}
		/// Returns the capacity size of the buffer
		size_type capacity()	const	{ return MAX_SPACE;	}
	/// @}

	/// \name Attach and Detach
	/// @{
	public:
		/// Attaches a given buffer with n values at the specified position
		void attach(const_pointer buf, size_type n, size_type pos = 0)
		{
			EXTL_ASSERT(is_valid());
			m_size = n;
			m_data = const_cast<pointer>(buf) + pos;
			EXTL_ASSERT(is_valid());
		}
		/// Attaches a given buffer
		void attach(class_type const& buf)
		{
			EXTL_ASSERT(is_valid());
			m_size = buf.size();
			m_data = const_cast<pointer>(buf.data());
			EXTL_ASSERT(is_valid());
		}
		/// Attaches a given buffer with n values at the specified position
		void attach(class_type const& buf, size_type n, size_type pos = 0)
		{
			EXTL_ASSERT(is_valid());
			m_size = n;
			m_data = const_cast<pointer>(buf.data()) + pos;
			EXTL_ASSERT(is_valid());
		}
		/// Detaches the current buffer
		const_pointer detach()
		{
			const_pointer p = m_data;
			EXTL_ASSERT(is_valid());
			m_data = NULL;
			m_size = 0;
			EXTL_ASSERT(is_valid());
			return p;
		}
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
			EXTL_ASSERT(size <= MAX_SPACE);
			EXTL_ASSERT(is_valid());
			if (is_update_size) m_size = size;
			EXTL_ASSERT(is_valid());
		}
		/// Swaps storage
		void swap(class_type& rhs) EXTL_THROW_0()
		{
			EXTL_ASSERT(is_valid());
			std_swap(m_size, rhs.m_size);
			std_swap(m_data, rhs.m_data);
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

			return e_true_v;
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_ATTACHED_BUFFER_H */
/* //////////////////////////////////////////////////////////////////// */
