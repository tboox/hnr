/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_reque.h		
 *
 * Created:		08.08.21		
 * Updated:		08.08.21
 *
 * Brief: fixed_reque class - fixed-size recurring queue
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_FIXED_REQUE_H
#define EXTL_CONTAINER_FIXED_REQUE_H

/*!\file fixed_reque.h
 * \brief fixed_reque class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../algorithm/algorithm.h"
#include "../memory/buffer.h"
#include "detail/fixed_reque_iterator.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define EXTL_FIXED_REQUE_DEFAULT_MAX_SIZE	256

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief fixed_reque
 *
 * \param T The element type
 * \param MAX_SIZE The maximum size of the storage
 * \param B The buffer type
 *
 * \ingroup extl_group_container
 *
 * buffer: |--------/////////////////////////---------|
 *                 |                         |
 *               head      <- size ->       tail
 */
template<	typename_param_k T
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t MAX_SIZE	= EXTL_FIXED_REQUE_DEFAULT_MAX_SIZE
		,	typename_param_k B	= typename_type_def_k buffer_selector<T>::buffer_type
	#else
		,	e_size_t MAX_SIZE	
		,	typename_param_k B	
	#endif
		>
class fixed_reque
{
	/// \name Types
	/// @{
	public:
		typedef fixed_reque															class_type;
		typedef B																	buffer_type;
		typedef typename_type_k buffer_type::allocator_type							allocator_type;
		typedef typename_type_k buffer_type::value_type								value_type;
		typedef typename_type_k buffer_type::pointer								pointer;
		typedef typename_type_k buffer_type::const_pointer							const_pointer;
		typedef typename_type_k buffer_type::reference								reference;
		typedef typename_type_k buffer_type::const_reference						const_reference;
		typedef typename_type_k buffer_type::size_type								size_type;
		typedef typename_type_k buffer_type::bool_type								bool_type;
		typedef typename_type_k buffer_type::difference_type						difference_type;
		typedef size_type															index_type;
		typedef EXTL_NS_DETAIL(fixed_reque_iterator)<value_type>					iterator;
		typedef EXTL_NS_DETAIL(const_fixed_reque_iterator)<value_type>				const_iterator;
		typedef reverse_bidirectional_iterator_base<const_iterator>					reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_iterator>			const_reverse_iterator;
	/// @}

	/// \name Members
	/// @{
	private:
		buffer_type																	m_buffer;
		size_type																	m_head;
		size_type																	m_size;
	/// @}

	/// \name Constructors
	/// @{
	public:
		fixed_reque()
			: m_buffer(max_size()), m_head(0), m_size(0)
		{
			EXTL_ASSERT(is_valid());
		}
		fixed_reque(class_type const& rhs)
			: m_buffer(rhs.get_buffer())
			, m_head(rhs.m_head)
			, m_size(rhs.m_size)

		{
			EXTL_ASSERT(is_valid());
		}
		fixed_reque(const_pointer p, size_type n)
			: m_buffer(p, n), m_head(0), m_size(n)
		{
			get_buffer().resize(max_size());
			EXTL_ASSERT(is_valid());
		}
		fixed_reque(const_reference value, size_type n)
			: m_buffer(value, n), m_head(0), m_size(n)
		{
			get_buffer().resize(max_size());
			EXTL_ASSERT(is_valid());
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		allocator_type		allocator() const	{ return get_buffer().allocator();	}
		size_type			size() const			{ return m_size;						}
		size_type			capacity() const		{ return get_buffer().size();			}
		bool_type			is_empty() const		{ return m_size == 0;					}
		bool_type			empty() const			{ return is_empty();					}
		bool_type			is_full() const			{ return m_size == max_size();			}
		static size_type	max_size()				{ return MAX_SIZE;						}
	/// @}

	/// \name Accessors
	/// @{
	public:
		reference			front()					{ EXTL_ASSERT(!is_empty()); return get_buffer()[m_head];	}
		const_reference		front()	const			{ EXTL_ASSERT(!is_empty()); return get_buffer()[m_head];	}

		reference			back()					{ EXTL_ASSERT(!is_empty()); return get_buffer()[(max_size() + m_head + m_size - 1) % max_size()];	}
		const_reference		back()	const			{ EXTL_ASSERT(!is_empty()); return get_buffer()[(max_size() + m_head + m_size - 1) % max_size()];	}
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const	{ return const_iterator(0, get_buffer().data(), &m_head, max_size());			}
		iterator				begin()			{ return iterator(0, get_buffer().data(), &m_head, max_size());					}
		const_iterator			end() const		{ return const_iterator(m_size, get_buffer().data(), &m_head, max_size());		}
		iterator				end()			{ return iterator(m_size, get_buffer().data(), &m_head, max_size());			}
		
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end());		}
		reverse_iterator		rbegin()		{ return reverse_iterator(end());			}
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin());	}
		reverse_iterator		rend()			{ return reverse_iterator(begin());			}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void push_front(const_reference value)		
		{ 
			EXTL_ASSERT(is_valid()); 
			EXTL_ASSERT(!is_full());
			if (!is_full())
			{
				m_head = (max_size() + m_head - 1) % max_size();
				get_buffer()[m_head] = value;	
				++m_size;
			}
			
			EXTL_ASSERT(is_valid()); 
		}
		void pop_front()								
		{ 
			EXTL_ASSERT(is_valid()); 
			EXTL_ASSERT(!is_empty());

			if (!is_empty()) 
			{
				m_head = (m_head + 1) % max_size();
				--m_size;
			}
			
			EXTL_ASSERT(is_valid()); 
		}

		void push_back(const_reference value)		
		{ 
			EXTL_ASSERT(is_valid()); 
			EXTL_ASSERT(!is_full());
			if (!is_full())
			{
				get_buffer()[(m_head + m_size) % max_size()] = value;	
				++m_size;
			}
			
			EXTL_ASSERT(is_valid()); 
		}
		void pop_back()								
		{ 
			EXTL_ASSERT(is_valid()); 
			EXTL_ASSERT(!is_empty());

			if (!is_empty()) --m_size;
			
			EXTL_ASSERT(is_valid()); 
		}

		void swap(class_type& rhs)				
		{ 
			get_buffer().swap(rhs.get_buffer());	
			std_swap(m_head, rhs.m_head);
			std_swap(m_size, rhs.m_size);
		}

		void clear()
		{
			m_head = 0;
			m_size = 0;
			EXTL_ASSERT(is_valid()); 
		}

		class_type& operator=(class_type const& rhs)
		{
			class_type(rhs).swap(*this);
			return *this;
		}
	/// @}


	/// \name Others
	/// @{
	protected:
		buffer_type& get_buffer()				{ return m_buffer;									}
		buffer_type const& get_buffer() const	{ return m_buffer;									}

		bool_type is_valid() const
		{
			if (capacity() != max_size()) 
				return e_false_v;

			if (size() > max_size())
				return e_false_v;

			if (m_head >= max_size())
				return e_false_v;

			if ((is_empty() || is_full()) != (m_head == ((m_head + m_size) % max_size())))
				return e_false_v;

			return e_true_v;
		}
	/// @}
};
#ifdef EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k T
		,	e_size_t MAX_SIZE
		,	typename_param_k B
		>
EXTL_INLINE void swap(fixed_reque<T, MAX_SIZE, B>& lhs, fixed_reque<T, MAX_SIZE, B>& rhs)
{
	lhs.swap(rhs);
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k T
		,	e_size_t MAX_SIZE
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k fixed_reque<T, MAX_SIZE, B>::
size_type get_size(fixed_reque<T, MAX_SIZE, B> const& q)
{
	return q.size();
}
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE) && \
			!defined(EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	typename_param_k T
		,	EXTL_NS(e_size_t) MAX_SIZE
		,	typename_param_k B
		>
EXTL_INLINE void swap(EXTL_NS(fixed_reque)<T, MAX_SIZE, B>& lhs, 
						EXTL_NS(fixed_reque)<T, MAX_SIZE, B>& rhs)
{
	lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_FIXED_REQUE_H */
/* //////////////////////////////////////////////////////////////////// */
