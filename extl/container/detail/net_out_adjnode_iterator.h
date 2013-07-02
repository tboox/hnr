/* ///////////////////////////////////////////////////////////////////////
 * File:		net_out_adjnode_iterator.h		
 *
 * Created:		08.12.04	
 * Updated:		08.12.04
 *
 * Brief:		The net_out_adjnode_iterator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_NET_OUT_ADJNODE_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_NET_OUT_ADJNODE_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	typename_param_k NodBuf
		,	typename_param_k AdjMtx
		>
class const_net_out_adjnode_iterator
	: public const_bidirectional_iterator_base	<	const_net_out_adjnode_iterator<NodBuf, AdjMtx>
												,	typename_type_k NodBuf::index_type
												,	e_ptrdiff_t
												>
{	private:
		typedef const_bidirectional_iterator_base	<	const_net_out_adjnode_iterator<NodBuf, AdjMtx>
													,	typename_type_k NodBuf::index_type
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type;
		typedef e_size_t																size_type;
		typedef size_type																index_type;
		typedef e_bool_t																bool_type;
		typedef NodBuf																	nodes_type;
		typedef AdjMtx																	adjmtx_type;
		typedef typename_type_k adjmtx_type::const_rowe_iterator						const_rowe_iterator;

	public:
		typedef const_net_out_adjnode_iterator											class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;

	private:
		const_rowe_iterator																m_current;
		nodes_type const*																m_pnodes;
		adjmtx_type const*																m_padjmtx;
		index_type																		m_id;

	public:
		const_net_out_adjnode_iterator() 
			: m_current() 
			, m_pnodes(NULL)
		{}
		const_net_out_adjnode_iterator(index_type id, const_rowe_iterator current, nodes_type const& ns, adjmtx_type const& atx) 
			: m_current(current)
			, m_pnodes(&ns)
			, m_padjmtx(&atx)
			, m_id(id)
		{
			for (; m_current != adjmtx().rowe_end(m_id) && (*m_current).is_empty(); ++m_current);
		}	
		const_net_out_adjnode_iterator(class_type const& it) 
			: m_current(it.m_current) 
			, m_pnodes(it.m_pnodes) 
			, m_padjmtx(it.m_padjmtx)
			, m_id(it.m_id)
		{}

	public:	
		const_rowe_iterator 		current() const				{ return m_current;										}
		
	private:
		nodes_type const&			nodes() const				{ EXTL_ASSERT(NULL != m_pnodes); return *m_pnodes;		}
		adjmtx_type const&			adjmtx() const				{ EXTL_ASSERT(NULL != m_padjmtx); return *m_padjmtx;	}

		void						next()
		{
			for (; ++m_current != adjmtx().rowe_end(m_id) && (*m_current).is_empty(); );
		}
		void						prev()
		{
			for (; --m_current != adjmtx().rowe_begin(m_id) && (*m_current).is_empty(); );
			if (m_current == adjmtx().rowe_begin(m_id) && (*m_current).is_empty())
				m_current = adjmtx().rowe_end(m_id);
			
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
			return (*current()).end_id();
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return (m_pnodes == rhs.m_pnodes) 
				&& (m_padjmtx == rhs.m_padjmtx)
				&& (m_id == rhs.m_id)
				&& (current() == rhs.current());
		}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_NET_OUT_ADJNODE_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
