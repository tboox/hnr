/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_list.h		
 *
 * Created:		08.08.23	
 * Updated:		08.08.27
 *
 * Brief: basic linked list - bidirectional linked list
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BASIC_LIST_H
#define EXTL_CONTAINER_BASIC_LIST_H

/*!\file basic_list.h
 * \brief basic linked list - bidirectional linked list
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/memory_traits_selector.h"
#include "../memory/allocator_selector.h"
#include "detail/list_iterator.h"
#include "../algorithm/algorithm.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief basic_list
 *
 * \param T The element type
 * \param A The allocator type
 * \param M The memory traits type
 * \param I The initialiser type
 *
 * \ingroup extl_group_container
 *
 * <pre>
 *     -------------------------------------------------------------------
 *    |   ----------         ---------                        ---------   |
 *     - |   head   | <= => |         | <= =>  ... ... <= => |         | -
 *    |   ----------         ---------                        ---------   |
 *     -------------------------------------------------------------------
 * </pre>
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k A	= typename_type_def_k allocator_selector<T>::allocator_type 
		,	typename_param_k M	= typename_type_def_k memory_traits_selector<T>::memory_traits_type
		,	typename_param_k I	= typename_type_def_k initialiser_selector<T>::initialiser_type
#else
		,	typename_param_k A	
		,	typename_param_k M
		,	typename_param_k I
#endif
		>
class basic_list
	: protected I // EXTL_EBO_FORM_7_SUPPORT 
{
	/// \name Types
	/// @{
	public:
		typedef basic_list															class_type;
		typedef A																	allocator_type;
		typedef typename_type_k allocator_type::value_type							value_type;	
		typedef typename_type_k allocator_type::pointer								pointer;			
		typedef typename_type_k allocator_type::const_pointer						const_pointer;		
		typedef typename_type_k allocator_type::reference							reference;			
		typedef typename_type_k allocator_type::const_reference						const_reference;	
		typedef typename_type_k allocator_type::size_type							size_type;	
		typedef e_ptrdiff_t															difference_type;
		typedef e_bool_t															bool_type;
		typedef M																	memory_traits_type;
		typedef I																	initialiser_type;
		struct node_type
		{
			node_type*		next;
			node_type*		prev;
			T				value;
		};
		friend struct																node_type;
		typedef node_type*															node_pointer;
		typedef node_type const*													const_node_pointer;
		typedef node_type&															node_reference;
		typedef node_type const&													const_node_reference;
		typedef EXTL_NS_DETAIL(list_iterator)	<	value_type
												,	node_type
												>									iterator;
		typedef EXTL_NS_DETAIL(const_list_iterator)	<	value_type
													,	node_type
													>								const_iterator;
		typedef reverse_bidirectional_iterator_base<const_iterator>					reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_iterator>			const_reverse_iterator;

		
	#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		typedef typename_type_k allocator_type::template_qual_k 
												rebind<node_type>::other_type		node_allocator_type;				
	#else
		typedef typename_type_k allocator_selector<node_type>::allocator_type		node_allocator_type;		
	#endif
	/// @}

	/// \name Members
	/// @{
		node_pointer																m_head;
		size_type																	m_size;
	/// @}

	/// \name Constructors
	/// @{
	public:
	#if EXTL_WORKAROUND_MSVC(==, 1200)
		basic_list()
			: initialiser_type(), m_head(create_node()), m_size(0)
		{
			EXTL_ASSERT(is_valid());
		}
		explicit_k basic_list(initialiser_type intr/* = initialiser_type()*/)
			: initialiser_type(intr), m_head(create_node()), m_size(0)
		{
			EXTL_ASSERT(is_valid());
		}
	#else // VC60 generate fatal error: INTERNAL COMPILER ERROR when list_type lt;
		explicit_k basic_list(initialiser_type intr = initialiser_type())
			: initialiser_type(intr), m_head(create_node()), m_size(0)
		{
			EXTL_ASSERT(is_valid());
		}
	#endif
		explicit_k basic_list(size_type n, initialiser_type intr = initialiser_type())
			: initialiser_type(intr), m_head(create_node()), m_size(0)
		{
			assign(value_type(), n);
		}
		basic_list(const_reference value, size_type n, initialiser_type intr = initialiser_type())
			: initialiser_type(intr), m_head(create_node()), m_size(0)
		{
			assign(value, n);
		}
		basic_list(class_type const& rhs, initialiser_type intr = initialiser_type())
			: initialiser_type(intr), m_head(create_node()), m_size(0)
		{
			assign(rhs);
		}
		~basic_list()
		{
			destroy();
		}
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const	{ return const_iterator(m_head->next);		}
		iterator				begin()			{ return iterator(m_head->next);			}
		const_iterator			end() const		{ return const_iterator(m_head);			}
		iterator				end()			{ return iterator(m_head);					}

		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end());		}
		reverse_iterator		rbegin()		{ return reverse_iterator(end());			}
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin());	}
		reverse_iterator		rend()			{ return reverse_iterator(begin());			}
	/// @}

	/// \name Attributes
	/// @{
	public:
		size_type			max_size() const	{ return node_allocator().max_size();	}
		size_type			size() const		{ return m_size;						}
		
		bool_type			is_empty() const	{ return size() == 0;	}
		bool_type			empty() const		{ return is_empty();	}

		reference			front()				{ return *begin();		}
		const_reference		front() const		{ return *begin();		}

		reference			back()				{ return *(--end());	}
		const_reference		back() const		{ return *(--end());	}
	/// @}

	/// \name Insertments
	/// @{
	public:
		iterator insert(const_iterator pos, class_type const& rhs);
		iterator insert(const_iterator pos, const_reference value);
		iterator insert(const_iterator pos, const_reference value, size_type n);
		iterator insert(const_iterator pos, const_iterator first, const_iterator last);
	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		template < typename_param_k _InIt >
		iterator insert(const_iterator pos, _InIt first, _InIt last)
		{
			EXTL_ASSERT(is_valid());

			const_iterator p = first;
			EXTL_TRY
				for (; first != last; ++first)
				{
					insert(pos, *first);
				}
				return make_iter(p);
			EXTL_CATCH_ALL
				// undo
				for (; p != first; ++p)
				{	
					const_iterator tmp = pos;
					erase(--tmp);
				}

				// reraise
				EXTL_THROW;
			EXTL_CATCH_END

			EXTL_ASSERT(is_valid());
			return make_iter(pos);
		}
	#endif
	/// @}

	/// \name Assignments
	/// @{
	public:
		class_type& assign(class_type const& rhs);
		class_type& assign(const_reference value);
		class_type& assign(const_reference value, size_type n);
		class_type& assign(const_iterator first, const_iterator last);
	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		template < typename_param_k _InIt >
		class_type& assign(_InIt first, _InIt last)
		{
			EXTL_ASSERT(is_valid());
			
			clear();
			insert(begin(), first, last);

			EXTL_ASSERT(is_valid());
			return *this;
		}
	#endif
		class_type& operator=(class_type const& rhs)	{ return assign(rhs);	}
	/// @}

	/// \name Erasements
	/// @{
	public:
		iterator erase(const_iterator pos);
		iterator erase(const_iterator pos, size_type n);
		iterator erase(const_iterator first, const_iterator last);
	/// @}

	/// \name Mutators
	/// @{
	public:
		void clear();
		void swap(class_type& rhs);
		void resize(size_type new_size, const_reference value = value_type());

		void push_front(const_reference value)	{ insert(begin(), value);	}
		void pop_front()						{ erase(begin());			}

		void push_back(const_reference value)	{ insert(end(), value);		}
		void pop_back()							{ erase(--end());			}
	/// @}

	/// \name Allocator & Initialiser
	/// @{
	public:
		allocator_type			allocator() const			{ return allocator_type();			}
		node_allocator_type		node_allocator() const		{ return node_allocator_type();		}
		initialiser_type const&	initialiser() const			{ return *this;						}
		initialiser_type&		initialiser() 				{ return *this;						}
	/// @}

	/// \name Helper
	/// @{
	public:
		static iterator			make_iter(const_iterator it) 	{ return iterator(it);			}
	/// @}

	/// \name Others
	/// @{
	private:
		void			destroy();
		bool_type		is_valid() const;

		node_pointer	create_node(const_reference value = value_type());
		void			destroy_node(node_pointer node);
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_BASIC_LIST_TEMPLATE_DECL
#	undef EXTL_BASIC_LIST_TEMPLATE_DECL
#endif

#define EXTL_BASIC_LIST_TEMPLATE_DECL			\
template<	typename_param_k T					\
		,	typename_param_k A					\
		,	typename_param_k M					\
		,	typename_param_k I					\
		>

/* Class qualification */
#ifdef EXTL_BASIC_LIST_QUAL
#	undef EXTL_BASIC_LIST_QUAL
#endif

#define EXTL_BASIC_LIST_QUAL	basic_list<T, A, M, I>

/* Class qualification */
#ifdef EXTL_BASIC_LIST_RET_QUAL
#	undef EXTL_BASIC_LIST_RET_QUAL
#endif

#define EXTL_BASIC_LIST_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_BASIC_LIST_QUAL::ret_type \
					EXTL_BASIC_LIST_QUAL
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */

EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(iterator)::insert(const_iterator pos, const_reference value)
{
	EXTL_ASSERT(is_valid());

	// create a new node
	node_pointer new_node = create_node(value);
	EXTL_ASSERT(new_node != NULL);

	/*!insert into this list
	 * <pre>
	 * list: 
	 *      -----------                   -----------
	 *     |    prev   |     <= | =>     |  pos_node |
	 *      -----------                   -----------
	 *                 \ \             / /
	 *                    ------------
	 *                   |  new_node  |
	 *                    ------------
	 * </pre>
	 */
	node_pointer pos_node = pos.node();
	EXTL_ASSERT(pos_node != NULL);

	pos_node->prev->next = new_node;
	new_node->prev = pos_node->prev;
	pos_node->prev = new_node;
	new_node->next = pos_node;
	
	// ++m_size
	++m_size;

	EXTL_ASSERT(is_valid());
	return make_iter(--pos);
}
EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(iterator)::insert(const_iterator pos, const_reference value, size_type n)
{
	EXTL_ASSERT(is_valid());

	size_type old_n = n;

	EXTL_TRY
		if (n > 0)
		{
			iterator start = insert(pos, value); 
			while (--n)
			{
				insert(pos, value); 
			}
			return start;
		}
	EXTL_CATCH_ALL
		// undo
		for (; n < old_n; ++n)
		{
			const_iterator tmp = pos;
			erase(--tmp);
		}

		// reraise
		EXTL_THROW;
	EXTL_CATCH_END

	EXTL_ASSERT(is_valid());
	return make_iter(pos);
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(iterator)::insert(const_iterator pos, const_iterator first, const_iterator last)
{
	EXTL_ASSERT(is_valid());

	const_iterator p = first;
	EXTL_TRY
		for (; first != last; ++first)
		{
			insert(pos, *first);
		}
		return make_iter(p);
	EXTL_CATCH_ALL
		// undo
		for (; p != first; ++p)
		{	
			const_iterator tmp = pos;
			erase(--tmp);
		}

		// reraise
		EXTL_THROW;
	EXTL_CATCH_END

	EXTL_ASSERT(is_valid());
	return make_iter(pos);
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(iterator)::insert(const_iterator pos, class_type const& rhs)
{
	return insert(pos, rhs.begin(), rhs.end());
}
EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(iterator)::erase(const_iterator pos)
{
	EXTL_ASSERT(is_valid());

	node_pointer pos_node = (pos++).node();
	EXTL_ASSERT(pos_node != NULL);

	if (pos_node && pos_node != m_head)
	{
		pos_node->prev->next = pos_node->next;
		pos_node->next->prev = pos_node->prev;

		destroy_node(pos_node);
		--m_size;
	}

	EXTL_ASSERT(is_valid());
	return make_iter(pos);
}
EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(iterator)::erase(const_iterator pos, size_type n)
{
	EXTL_ASSERT(is_valid());

	if (pos == begin() && n == size())
	{
		clear();
		EXTL_ASSERT(is_valid());
		return end();
	}
	else
	{
		for (; n > 0; --n) pos = erase(pos);

		EXTL_ASSERT(is_valid());
		return make_iter(pos);
	}
}


EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(iterator)::erase(const_iterator first, const_iterator last)
{
	EXTL_ASSERT(is_valid());

	if (first == begin() && last == end())
	{
		clear();
		EXTL_ASSERT(is_valid());
		return end();
	}
	else
	{
		while (first != last) first = erase(first);
		EXTL_ASSERT(is_valid());
		return make_iter(first);
	}
}
EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(class_type&)::assign(const_reference value)
{
	EXTL_ASSERT(is_valid());
	
	value_type tmp = value;	// in case value is in the list
	clear();
	insert(begin(), tmp);

	EXTL_ASSERT(is_valid());
	return *this;
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(class_type&)::assign(const_reference value, size_type n)
{
	EXTL_ASSERT(is_valid());
	
	value_type tmp = value;	// in case value is in the list
	clear();
	insert(begin(), tmp, n);

	EXTL_ASSERT(is_valid());
	return *this;
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(class_type&)::assign(const_iterator first, const_iterator last)
{
	EXTL_ASSERT(is_valid());
	
	clear();
	insert(begin(), first, last);

	EXTL_ASSERT(is_valid());
	return *this;
}
EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(class_type&)::assign(class_type const& rhs)
{
	if (this != &rhs) assign(rhs.begin(), rhs.end());
	return *this;
}
EXTL_BASIC_LIST_TEMPLATE_DECL
inline void EXTL_BASIC_LIST_QUAL::clear()
{
	EXTL_ASSERT(is_valid());

	if (m_head)
	{
		node_pointer node = m_head->next;
		m_head->prev = m_head;
		m_head->next = m_head;
		m_size = 0;

		EXTL_ASSERT(node != NULL);
		while (node != m_head)
		{
			node_pointer old_node = node;
			node = node->next;

			// destroy the old_node
			destroy_node(old_node);
		}
	}
	
	EXTL_ASSERT(is_valid());
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline void EXTL_BASIC_LIST_QUAL::destroy()
{
	EXTL_ASSERT(is_valid());

	clear();
	if (m_head)
	{
		node_allocator().deallocate(m_head);
		m_head = NULL;
	}
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(node_pointer)::create_node(const_reference value)
{
	/// allocate a new node
	node_pointer new_node = node_allocator().allocate(1);
	EXTL_ASSERT(new_node != NULL);
	if (NULL == new_node) return NULL;

	/*!new node:
	 * <pre>
	 * self-reference:
	 *       ----------------------------
	 *    --| prev      value       next |---
	 *   |   ----------------------------    |
	 *   |           |          |            |
	 *    -----------            ------------
	 * </pre>
	 */
	EXTL_TRY
		new_node->next = new_node;
		new_node->prev = new_node;
		initialiser().construct(&(new_node->value), value);
	EXTL_CATCH_ALL
		node_allocator().deallocate(new_node);
		// reraise
		EXTL_THROW;
	EXTL_CATCH_END

	return new_node;
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline void EXTL_BASIC_LIST_QUAL::destroy_node(node_pointer node)
{
	EXTL_ASSERT(node != NULL);
	if (NULL == node) return ;
	initialiser().destruct(&(node->value));
	node_allocator().deallocate(node);
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline EXTL_BASIC_LIST_RET_QUAL(bool_type)::is_valid() const
{
	if (m_head == NULL) return e_false_v;
	if (
			(m_head->next == m_head && m_head->prev == m_head)
		!=	(0 == size())
		) 
		return e_false_v;

	size_type n = 1;
	for (const_iterator p = begin(); p != end(); ++p, ++n)
	{
		if (n > size()) return e_false_v;
	}

	return e_true_v;
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline void EXTL_BASIC_LIST_QUAL::resize(size_type new_size, const_reference value)
{
	if (size() < new_size) insert(end(), value, new_size - size()); 
	else while (new_size < size()) pop_back();
}

EXTL_BASIC_LIST_TEMPLATE_DECL
inline void EXTL_BASIC_LIST_QUAL::swap(class_type& rhs)
{
	if (this != &rhs) 
	{
		std_swap(m_head, rhs.m_head);
		std_swap(m_size, rhs.m_size);
	}
}

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
EXTL_BASIC_LIST_TEMPLATE_DECL
EXTL_INLINE void swap(EXTL_BASIC_LIST_QUAL& lhs, EXTL_BASIC_LIST_QUAL& rhs)
{
	lhs.swap(rhs);
}

EXTL_BASIC_LIST_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_BASIC_LIST_QUAL::
size_type get_size(EXTL_BASIC_LIST_QUAL const& lt)
{
	return lt.size();
}

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_BASIC_LIST_TEMPLATE_DECL
#undef EXTL_BASIC_LIST_QUAL
#undef EXTL_BASIC_LIST_RET_QUAL


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	typename_param_k T					
		,	typename_param_k A					
		,	typename_param_k M					
		,	typename_param_k I					
		>
EXTL_INLINE void swap(EXTL_NS(basic_list)<T, A, M, I>& lhs, 
						EXTL_NS(basic_list)<T, A, M, I>& rhs)
{
	lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_BASIC_LIST_H */
/* //////////////////////////////////////////////////////////////////// */
