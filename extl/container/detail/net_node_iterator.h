/* ///////////////////////////////////////////////////////////////////////
 * File:		net_node_iterator.h		
 *
 * Created:		08.12.04	
 * Updated:		08.12.04
 *
 * Brief:		The net_node_iterator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_NET_NODE_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_NET_NODE_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<typename_param_k NodBuf>
class const_net_node_iterator
	: public const_bidirectional_iterator_base	<	const_net_node_iterator<NodBuf>
												,	typename_type_k NodBuf::index_type
												,	e_ptrdiff_t
												>
{
	private:
		typedef const_bidirectional_iterator_base	<	const_net_node_iterator<NodBuf>
													,	typename_type_k NodBuf::index_type
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type;
		typedef e_size_t																size_type;
		typedef size_type																index_type;
		typedef e_bool_t																bool_type;
		typedef NodBuf																	nodes_type;
		typedef typename_type_k nodes_type::const_iterator								const_nodes_iterator;

	public:
		typedef const_net_node_iterator													class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;

	private:
		const_nodes_iterator															m_current;
		nodes_type const*																m_pnodes;

	public:
		const_net_node_iterator() 
			: m_current() 
			, m_pnodes(NULL)
		{}
		const_net_node_iterator(const_nodes_iterator current, nodes_type const& ns) 
			: m_current(current)
			, m_pnodes(&ns)
		{
			for (; m_current != nodes().end() && (*m_current).is_empty(); ++m_current);
		}	
		const_net_node_iterator(class_type const& it) 
			: m_current(const_cast<class_type&>(it).current()) 
			, m_pnodes(&const_cast<class_type&>(it).nodes()) 
		{}

	public:
		const_nodes_iterator 		current() const				{ return m_current;									}
		
	private:
		nodes_type const&			nodes() const				{ EXTL_ASSERT(NULL != m_pnodes); return *m_pnodes;	}	
		void						next()
		{
			for (; ++m_current != nodes().end() && (*m_current).is_empty(); );
		}
		void						prev()
		{
			for (; --m_current != nodes().begin() && (*m_current).is_empty(); );
			if (m_current == nodes().begin() && (*m_current).is_empty())
				m_current = nodes().end();
			
		}

	public:
		void do_increase()
		{
			next();
		}
		void do_decrease()
		{
			prev();
		}
		const_reference do_dereference() const
		{
			return (*current()).id();
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return (m_pnodes == rhs.m_pnodes) && (current() == rhs.current());
		}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_NET_NODE_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
