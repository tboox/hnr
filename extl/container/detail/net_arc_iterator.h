/* ///////////////////////////////////////////////////////////////////////
 * File:		net_arc_iterator.h		
 *
 * Created:		08.12.04
 * Updated:		08.12.04
 *
 * Brief:		The net_arc_iterator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_NET_ARC_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_NET_ARC_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "../basic_pair.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<typename_param_k AdjMtx>
class const_net_arc_iterator
	: public const_bidirectional_iterator_base	<	const_net_arc_iterator<AdjMtx>
												,	basic_pair<typename_type_k AdjMtx::index_type, typename_type_k AdjMtx::index_type>
												,	e_ptrdiff_t
												>
{
	private:
		typedef const_bidirectional_iterator_base	<	const_net_arc_iterator<AdjMtx>
													,	basic_pair<typename_type_k AdjMtx::index_type, typename_type_k AdjMtx::index_type>
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type;
		typedef e_size_t																size_type;
		typedef size_type																index_type;
		typedef e_bool_t																bool_type;
		typedef AdjMtx																	adjmtx_type;
		typedef typename_type_k adjmtx_type::const_iterator								const_adjmtx_iterator;

	public:
		typedef const_net_arc_iterator													class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;

	private:
		const_adjmtx_iterator															m_current;
		adjmtx_type const*																m_padjmtx;

	public:
		const_net_arc_iterator() 
			: m_current() 
			, m_padjmtx(NULL)
		{}
		const_net_arc_iterator(const_adjmtx_iterator current, adjmtx_type const& atx) 
			: m_current(current)
			, m_padjmtx(&atx)
		{
			for (; m_current != adjmtx().end() && (*m_current).is_empty(); ++m_current);
		}	
		const_net_arc_iterator(class_type const& it) 
			: m_current(const_cast<class_type&>(it).current()) 
			, m_padjmtx(&const_cast<class_type&>(it).adjmtx()) 
		{}

	public:
		const_adjmtx_iterator	current() const				{ return m_current;									}
		
	private:
		adjmtx_type const&		adjmtx() const				{ EXTL_ASSERT(NULL != m_padjmtx); return *m_padjmtx;	}	

		void					next()
		{
			for (; ++m_current != adjmtx().end() && (*m_current).is_empty(); );
		}
		void					prev()
		{
			for (; --m_current != adjmtx().begin() && (*m_current).is_empty(); );
			if (m_current == adjmtx().begin() && (*m_current).is_empty())
				m_current = adjmtx().end();
			
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
			return (*current()).ids();
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return (m_padjmtx == rhs.m_padjmtx) && (current() == rhs.current());
		}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_END_NAMESPACE
EXTL_DETAIL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_NET_ARC_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
