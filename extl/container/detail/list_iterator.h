/* ///////////////////////////////////////////////////////////////////////
 * File:		list_iterator.h		
 *
 * Created:		08.08.23	
 * Updated:		08.12.07
 *
 * Brief:		The linked list iterator
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_LIST_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_LIST_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	typename_param_k Val
		,	typename_param_k Node
        >
class const_list_iterator
	: public const_bidirectional_iterator_base	<	const_list_iterator<Val, Node>
												,	Val
												,	e_ptrdiff_t
												>
{
	private:
		typedef const_bidirectional_iterator_base	<	const_list_iterator<Val, Node>
													,	Val
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type;
		typedef Node																	node_type;
		typedef node_type*																node_pointer;
		typedef node_type const*														const_node_pointer;
		typedef node_type&																node_reference;
		typedef node_type const&														const_node_reference;
		typedef e_bool_t																bool_type;

	public:
		typedef const_list_iterator														class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;

	private:
		const_node_pointer																m_current;

	public:
		const_list_iterator() 
			: m_current(NULL) 
		{}
		explicit_k const_list_iterator(const_node_pointer p) 
			: m_current(p) 
		{}	
		const_list_iterator(class_type const& it) 
			: m_current(it.current()) 
		{}

	public:
		const_node_pointer	current() const				{ return m_current;								}
		node_pointer		current() 					{ return const_cast<node_pointer>(m_current);	}
		const_node_pointer	node() const				{ return m_current;								}
		node_pointer		node() 						{ return const_cast<node_pointer>(m_current);	}

	public:
		void do_increase()
		{
			EXTL_ASSERT(current() != NULL);
			m_current = current()->next;
		}
		void do_decrease()
		{
			EXTL_ASSERT(m_current != NULL);
			m_current = current()->prev;
		}
		const_reference do_dereference() const
		{
			EXTL_ASSERT(current() != NULL);
			return current()->value;
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return current() == rhs.current();
		}
};
// list_iterator can be converted to const_list_iterator implicitly
template<	typename_param_k Val
		,	typename_param_k Node
        >
class list_iterator
	: public bidirectional_iterator_base<	list_iterator<Val, Node>
										,	const_list_iterator<Val, Node>
										,	Val
										,	e_ptrdiff_t
										>
{
	private:
		typedef bidirectional_iterator_base<	list_iterator<Val, Node>
											,	const_list_iterator<Val, Node>
											,	Val
											,	e_ptrdiff_t
											>											base_type;
		typedef const_list_iterator<Val, Node>											const_iterator_type;
		typedef base_type																iterator_base_type;
		typedef Node																	node_type;
		typedef node_type*																node_pointer;
		typedef node_type const*														const_node_pointer;
		typedef node_type&																node_reference;
		typedef node_type const&														const_node_reference;
		typedef e_bool_t																bool_type;

	public:
		typedef list_iterator															class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;

	public:
		list_iterator() 
			: base_type() 
		{}
		explicit_k list_iterator(const_node_pointer p) 
			: base_type(const_iterator_type(p)) 
		{}	
		list_iterator(class_type const& it) 
			: base_type(it) 
		{}
		// const_list_iterator can be explicitly converted to list_iterator
		explicit_k list_iterator(const_iterator_type const& it) 
			: base_type(it) 
		{}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE


/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_LIST_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
