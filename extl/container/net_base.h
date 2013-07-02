/* ///////////////////////////////////////////////////////////////////////
 * File:		net_base.h		
 *
 * Created:		08.11.27			
 * Updated:		08.11.27
 *
 * Brief:		The net_base class - compact net
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_NET_BASE_H
#define EXTL_CONTAINER_NET_BASE_H

/*!\file net_base.h
 * \brief net_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/net_base_impl.h"
#include "detail/net_node_iterator.h"
#include "detail/net_arc_iterator.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!brief net_base
 *
 * \param is_dir returns \true if it's a directed net
 * \param Nods the nodes type
 * \param Mtx1 the adjacent matrix type for directed net
 * \param Mtx2 the adjacent matrix type for indirected net - symmetrical matrix
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k Dev
		,	e_bool_t is_dir
		,	typename_param_k Nods
		,	typename_param_k Mtx1	
		,	typename_param_k Mtx2	
		>
class net_base
	: public EXTL_NS_DETAIL(net_base_impl)<is_dir>::template_qual_k impl<	Dev
																		,	Nods
																		,	Mtx1
																		,	Mtx2
																		>
{
	/// \name Protected Types
	/// @{
	protected:
		typedef typename_type_k EXTL_NS_DETAIL(net_base_impl)<is_dir>::
		template_qual_k impl<	Dev
							,	Nods
							,	Mtx1
							,	Mtx2
							>														base_type;
		typedef Dev																	derived_type;
		typedef typename_type_k base_type::adjmtx_type								adjmtx_type;
		typedef typename_type_k base_type::node_type								node_type;
		typedef typename_type_k base_type::nodes_type								nodes_type;
		typedef typename_type_k base_type::arc_type									arc_type;
		typedef typename_type_k base_type::weight_type								weight_type;
	#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
		friend																		base_type;
	#endif
	/// @}
	
	/// \name Public Types
	/// @{
	public:
		typedef net_base															class_type;
		typedef typename_type_k base_type::value_type								value_type;
		typedef typename_type_k base_type::pointer									pointer;
		typedef typename_type_k base_type::const_pointer							const_pointer;
		typedef typename_type_k base_type::reference								reference;
		typedef typename_type_k base_type::const_reference							const_reference;
		typedef typename_type_k base_type::size_type								size_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k base_type::difference_type							difference_type;
		typedef typename_type_k base_type::int_type									int_type;
		typedef typename_type_k base_type::index_type								index_type;

		// const_node_iterator
		typedef EXTL_NS_DETAIL(const_net_node_iterator)<nodes_type>					const_node_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_node_iterator>		const_reverse_node_iterator;

		// const_arc_iterator
		typedef EXTL_NS_DETAIL(const_net_arc_iterator)<adjmtx_type>					const_arc_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_arc_iterator>		const_reverse_arc_iterator;
	/// @}

	/// \name Constants
	/// @{
	public:
		EXTL_STATIC_MEMBER_CONST(bool_type, is_directed = is_dir);
	/// @}

	/// \name Members
	/// @{
	protected:
		nodes_type																	m_nodes;
		adjmtx_type																	m_adjmtx;
		size_type																	m_arcs_n;
		size_type																	m_nodes_n;
	/// @}

	private:
		net_base(class_type const& rhs);
		class_type&	operator =(class_type& rhs);

	/// \name Constructors
	/// @{
	public:
		explicit_k net_base(size_type max_nodes_n)
			: m_nodes(max_nodes_n)
			, m_adjmtx(max_nodes_n, max_nodes_n)
			, m_arcs_n(0)
			, m_nodes_n(0)
		{
			derive().clear();
			EXTL_ASSERT(derive().is_valid());
		}
		net_base(derived_type const& rhs)
			: m_nodes(rhs.nodes())
			, m_adjmtx(rhs.adjmtx())
			, m_arcs_n(rhs.arcs_size())
			, m_nodes_n(rhs.nodes_size())
		{
			EXTL_ASSERT(derive().is_valid());
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		size_type			nodes_size() const		{ return m_nodes_n;						}
		size_type			size() const			{ return derive().nodes_size();			}
		size_type			arcs_size() const		{ return m_arcs_n;						}
		bool_type			is_empty() const		{ return nodes().is_empty();			}
		bool_type			empty() const			{ return derive().is_empty();			}
		size_type			max_nodes_size() const	{ return nodes().size();				}
		size_type			max_size() const		{ return derive().max_nodes_size();		}
		size_type			max_arcs_size() const	{ return derive().max_arcs_size_impl();	}
		bool_type			is_valid() const;
	/// @}

	/// \name Mutators
	/// @{
	public:
		void				clear();
		void				swap(derived_type& rhs);
		derived_type&		operator =(derived_type& rhs);

		derived_type&		insert_arc(index_type bid, index_type eid, weight_type w = weight_type());
		derived_type&		remove_arc(index_type bid, index_type eid);

		derived_type&		insert_node(index_type id, const_reference val = value_type());
		derived_type&		remove_node(index_type id);
	/// @}

	/// \name Accessors
	/// @{
	public:
		bool_type			node_exists(index_type id) const;
		bool_type			arc_exists(index_type bid, index_type eid) const;

		const_reference		at(index_type id) const							{ return node_at(id).value();						}
		reference			at(index_type id)								{ return node_at(id).value();						}

		weight_type const&	weight(index_type bid, index_type eid) const	{ return derive().adjmtx_at(bid, eid).weight();		}
		weight_type&		weight(index_type bid, index_type eid)			{ return derive().adjmtx_at(bid, eid).weight();		}
	
		size_type			degree(index_type id) const						{ return node_at(id).degree();						}
	/// @}

	/// \name Node Iterators
	/// \note cannot insert and erase nodes in the iteration 
	/// @{
	public:
		const_node_iterator			node_begin() const	{ return const_node_iterator(nodes().begin(), nodes());		}
		const_node_iterator			node_end() const	{ return const_node_iterator(nodes().end(), nodes());		}

		const_reverse_node_iterator	node_rbegin() const	{ return const_reverse_node_iterator(node_end());			}
		const_reverse_node_iterator	node_rend() const	{ return const_reverse_node_iterator(node_begin());			}
	/// @}

	/// \name Arc Iterators
	/// \note cannot insert and erase arcs in the iteration 
	/// @{
	public:
		const_arc_iterator			arc_begin() const	{ return const_arc_iterator(adjmtx().begin(), adjmtx());	}
		const_arc_iterator			arc_end() const		{ return const_arc_iterator(adjmtx().end(), adjmtx());		}

		const_reverse_arc_iterator	arc_rbegin() const	{ return const_reverse_arc_iterator(arc_end());				}
		const_reverse_arc_iterator	arc_rend() const	{ return const_reverse_arc_iterator(arc_begin());			}
	/// @}

	/// \name Protected Accessors
	/// @{
#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
	protected:
#else
	public:
#endif
		nodes_type&			nodes()			{ return m_nodes;	}
		nodes_type const&	nodes() const	{ return m_nodes;	}

		adjmtx_type&		adjmtx()		{ return m_adjmtx;	}
		adjmtx_type const&	adjmtx() const	{ return m_adjmtx;	}
	/// @}

	/// \name Protected Unsafe Mutators
	/// @{
#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
	protected:
#else
	public:
#endif
		void				unsafe_insert_arc(index_type bid, index_type eid, weight_type w);
		void				unsafe_remove_arc(index_type bid, index_type eid);
		void				unsafe_insert_node(index_type id, const_reference val);
		void				unsafe_remove_node(index_type id);
	/// @}

	/// \name Helpers
	/// @{
#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
	protected:
#else
	public:
#endif
		void				clear_nodes();
		void				clear_adjmtx();

		node_type&			node_at(index_type id);
		node_type const&	node_at(index_type id) const;
		
		node_type&			node_at_uncheck(index_type id);
		node_type const&	node_at_uncheck(index_type id) const;
		
		arc_type&			adjmtx_at(index_type bid, index_type eid);
		arc_type const&		adjmtx_at(index_type bid, index_type eid) const;

		arc_type&			adjmtx_at_uncheck(index_type bid, index_type eid);
		arc_type const&		adjmtx_at_uncheck(index_type bid, index_type eid) const;

		derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */
// Template declaration 
#ifdef EXTL_NET_BASE_TEMPLATE_DECL
#	undef EXTL_NET_BASE_TEMPLATE_DECL
#endif

#define EXTL_NET_BASE_TEMPLATE_DECL			\
template<	typename_param_k Dev			\
		,	e_bool_t is_dir					\
		,	typename_param_k Nods			\
		,	typename_param_k Mtx1			\
		,	typename_param_k Mtx2			\
		>

// Class qualification 
#ifdef EXTL_NET_BASE_QUAL
#	undef EXTL_NET_BASE_QUAL
#endif

#define EXTL_NET_BASE_QUAL	net_base<Dev, is_dir, Nods, Mtx1, Mtx2>

// Class qualification 
#ifdef EXTL_NET_BASE_RET_QUAL
#	undef EXTL_NET_BASE_RET_QUAL
#endif

#define EXTL_NET_BASE_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_NET_BASE_QUAL::ret_type \
					EXTL_NET_BASE_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Implementation
 */

EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::unsafe_insert_node(index_type id, const_reference val)
{
	// note: too slowly
	//EXTL_ASSERT(derive().is_valid());
	if (!derive().node_exists(id)) // insert node if not exists
	{
		derive().node_at_uncheck(id) = node_type(id, val);
		++m_nodes_n;
	}
	else // update node if exists
	{
		EXTL_ASSERT(id == derive().node_at_uncheck(id).id());
		derive().node_at_uncheck(id) = node_type(id, val);
	}

	//EXTL_ASSERT(derive().is_valid());
}
EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::unsafe_remove_node(index_type id)
{
	if (!derive().node_exists(id)) return;

	//EXTL_ASSERT(derive().is_valid());

	derive().node_at_uncheck(id).clear();
	--m_nodes_n;

	EXTL_ASSERT(!derive().node_exists(id));
	//EXTL_ASSERT(derive().is_valid());
}
EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::unsafe_insert_arc(index_type bid, index_type eid, weight_type w)
{
	//EXTL_ASSERT(derive().is_valid());

	if (!derive().arc_exists(bid, eid))	// insert arc if not exists
	{
		derive().adjmtx_at_uncheck(bid, eid) = arc_type(bid, eid, w);
		derive().inc_degree(bid, eid);
		++m_arcs_n;
	}
	else	 // update arc if exists
	{
		derive().adjmtx_at_uncheck(bid, eid) = arc_type(bid, eid, w);
	}
	
	//EXTL_ASSERT(derive().is_valid());
}
EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::unsafe_remove_arc(index_type bid, index_type eid)
{
	if (!derive().arc_exists(bid, eid)) return ;

	//EXTL_ASSERT(derive().is_valid());

	derive().adjmtx_at_uncheck(bid, eid).clear();
	derive().dec_degree(bid, eid);
	--m_arcs_n;

	EXTL_ASSERT(!derive().arc_exists(bid, eid));
	//EXTL_ASSERT(derive().is_valid());
}

EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(derived_type&)::insert_arc(index_type bid, index_type eid, weight_type w)
{
	EXTL_ASSERT(derive().is_valid());
	size_type step = 0;

	EXTL_TRY
		// insert it at first if node not exist
		if (derive().node_at_uncheck(bid).is_empty())
		{
			derive().unsafe_insert_node(bid, value_type());
			step = 1;
		}
		
		if (derive().node_at_uncheck(eid).is_empty())
		{
			derive().unsafe_insert_node(eid, value_type());
			step = 2;
		}
		// insert arc
		unsafe_insert_arc(bid, eid, w);
	EXTL_CATCH_ALL
		switch (step)
		{
		case 2:
			derive().unsafe_remove_node(eid);
		case 1:
			derive().unsafe_remove_node(bid);
		default:
			break;
		}
		// reraise
		EXTL_THROW;
	EXTL_CATCH_END
	
	EXTL_ASSERT(derive().is_valid());
	return derive();
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(derived_type&)::remove_arc(index_type bid, index_type eid)
{
	EXTL_ASSERT(derive().is_valid());
	derive().unsafe_remove_arc(bid, eid);
	EXTL_ASSERT(derive().is_valid());
	return derive();
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(derived_type&)::insert_node(index_type id, const_reference val)
{
	EXTL_ASSERT(derive().is_valid());
	derive().unsafe_insert_node(id, val);
	EXTL_ASSERT(derive().is_valid());
	return derive();
}

EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(derived_type&)::remove_node(index_type id)
{
	EXTL_ASSERT(derive().is_valid());
#ifdef EXTL_EXCEPTION_ENABLE
	// need erase arcs in the vicinity of the node at first
	derived_type tmp(derive());
	tmp.safe_remove_node(id);
	tmp.swap(derive());
#else
	derive().safe_remove_node(id);
#endif
	EXTL_ASSERT(derive().is_valid());
	return derive();
}

EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::clear_nodes()
{
	typedef typename_type_k nodes_type::iterator	node_iterator_;
	for (node_iterator_ pn = nodes().begin(); pn != nodes().end(); ++pn)
		(*pn).clear();	
}

EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::clear_adjmtx()
{
	typedef typename_type_k adjmtx_type::iterator	arc_iterator_;
	for (arc_iterator_ pa = adjmtx().begin(); pa != adjmtx().end(); ++pa)
		(*pa).clear();	
}

EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::clear()
{
	derive().clear_nodes();	
	derive().clear_adjmtx();

	m_arcs_n = 0;
	m_nodes_n = 0;

	EXTL_ASSERT(derive().is_valid());
}

EXTL_NET_BASE_TEMPLATE_DECL
inline void EXTL_NET_BASE_QUAL::swap(derived_type& rhs)
{
	EXTL_ASSERT(derive().is_valid());
	nodes().swap(static_cast<class_type&>(rhs).m_nodes);
	adjmtx().swap(static_cast<class_type&>(rhs).m_adjmtx);
	std_swap(m_arcs_n, static_cast<class_type&>(rhs).m_arcs_n);
	std_swap(m_nodes_n, static_cast<class_type&>(rhs).m_nodes_n);
	EXTL_ASSERT(derive().is_valid());
}

EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(derived_type&)::operator =(derived_type& rhs)
{
	EXTL_ASSERT(derive().is_valid());
	derived_type(rhs).swap(derive());
	EXTL_ASSERT(derive().is_valid());
	return derive();
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(node_type const&)::node_at(index_type id) const
{
	EXTL_MESSAGE_ASSERT(id < nodes().size(), "out of range");
	EXTL_ASSERT_THROW(id < nodes().size(), "out of range");

	EXTL_MESSAGE_ASSERT(!nodes()[id].is_empty(), "node not exists");
	EXTL_ASSERT_THROW(!nodes()[id].is_empty(), "node not exists");

	return nodes()[id];
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(node_type&)::node_at(index_type id)
{
	return const_cast<node_type&>(static_cast<derived_type const&>(*this).node_at(id));
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(node_type const&)::node_at_uncheck(index_type id) const
{
	EXTL_MESSAGE_ASSERT(id < nodes().size(), "out of range");
	return nodes()[id];
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(node_type&)::node_at_uncheck(index_type id)
{
	return const_cast<node_type&>(static_cast<derived_type const&>(*this).node_at_uncheck(id));
}

EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(arc_type&)::adjmtx_at(index_type bid, index_type eid)
{
	return const_cast<arc_type&>(static_cast<derived_type const&>(*this).adjmtx_at(bid, eid));
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(arc_type const&)::adjmtx_at(index_type bid, index_type eid) const
{
	EXTL_MESSAGE_ASSERT	(	bid < adjmtx().dim0()
						&&	eid < adjmtx().dim1()
						,	"adjmtx_at: out of range");

	EXTL_ASSERT_THROW	(	bid < adjmtx().dim0()
						&&	eid < adjmtx().dim1()
						,	"adjmtx_at: out of range");

	EXTL_MESSAGE_ASSERT	(	derive().arc_exists(bid, eid)
						,	"adjmtx_at: arc not exist");

	EXTL_ASSERT_THROW	(	derive().arc_exists(bid, eid)
						,	"adjmtx_at: arc not exist");


	return adjmtx().at(bid, eid);
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(arc_type&)::adjmtx_at_uncheck(index_type bid, index_type eid)
{
	return const_cast<arc_type&>(static_cast<derived_type const&>(*this).adjmtx_at_uncheck(bid, eid));
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(arc_type const&)::adjmtx_at_uncheck(index_type bid, index_type eid) const
{
	EXTL_MESSAGE_ASSERT	(	bid < adjmtx().dim0()
						&&	eid < adjmtx().dim1()
						,	"adjmtx_at: out of range");

	// note: can not call arc_exists(bid, eid) at this.
	// note: can not call is_valid() at this.

	return adjmtx().at(bid, eid);
}

EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(bool_type)::node_exists(index_type id) const	
{ 
	if (!(id < nodes().size())) return e_false_v;
	return !node_at_uncheck(id).is_empty();		
}
EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(bool_type)::arc_exists(index_type bid, index_type eid) const
{ 
	// note: can not call is_valid() at this.
	if (!(bid < adjmtx().dim0() && eid < adjmtx().dim1())) 
		return e_false_v;
	return !this->adjmtx_at_uncheck(bid, eid).is_empty();	
}

EXTL_NET_BASE_TEMPLATE_DECL
inline EXTL_NET_BASE_RET_QUAL(bool_type)::is_valid() const
{
	size_type n0 = adjmtx().dim0();
	size_type n1 = adjmtx().dim1();

	if (n0 != n1) return e_false_v;
	if (derive().nodes_size() > derive().max_nodes_size()) return e_false_v;
	if (derive().arcs_size() > derive().max_arcs_size()) return e_false_v;

	for (index_type i = 0; i < n0; ++i)
	{
		for (index_type j = 0; j < n1; ++j)
		{
			if (!derive().arc_exists(i, j)) continue;

			// invariance of arc
			if (!adjmtx().at(i, j).is_valid())
				return e_false_v;

			// out of range
			if (	adjmtx().at(i, j).begin_id() >= nodes().size() 
				||	adjmtx().at(i, j).end_id() >= nodes().size())
				return e_false_v;

			// non-consistency
			if (is_directed)
			{
				if (adjmtx().at(i, j).begin_id() != i || adjmtx().at(i, j).end_id() != j)
					return e_false_v;
			}
			else
			{
				if ((adjmtx().at(i, j).begin_id() != i && adjmtx().at(i, j).begin_id() != j)
					|| (adjmtx().at(i, j).end_id() != i && adjmtx().at(i, j).end_id() != j))
					return e_false_v;
			}
			
			// null ----> end
			if (nodes()[adjmtx().at(i, j).begin_id()].is_empty())
				return e_false_v;

			// start ---> null
			if (nodes()[adjmtx().at(i, j).end_id()].is_empty())
				return e_false_v;
		}
	}

	return e_true_v;
}

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_NET_BASE_TEMPLATE_DECL
#undef EXTL_NET_BASE_QUAL
#undef EXTL_NET_BASE_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_NET_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
