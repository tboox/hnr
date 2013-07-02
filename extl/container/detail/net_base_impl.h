/* ///////////////////////////////////////////////////////////////////////
 * File:		net_base_impl.h		
 *
 * Created:		08.11.26			
 * Updated:		08.11.29
 *
 * Brief:		The net_base_impl class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_NET_BASE_IMPL_H
#define EXTL_CONTAINER_DETAIL_NET_BASE_IMPL_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "net_out_adjnode_iterator.h"
#include "net_in_adjnode_iterator.h"
#include "indirected_net_adjnode_iterator.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<e_bool_t is_dir>
struct net_base_impl
{
	template<	typename_param_k Dev
			,	typename_param_k Nods
			,	typename_param_k Mtx1	
			,	typename_param_k Mtx2	
			>
	struct impl;
};

EXTL_TEMPLATE_SPECIALISATION
struct net_base_impl<e_true_v>	// directed net 
{
	template<	typename_param_k Dev
			,	typename_param_k Nods
			,	typename_param_k Mtx1	
			,	typename_param_k Mtx2	
			>
	struct impl
	{
		/// \name Types
		/// @{
		public:
			typedef Dev																		derived_type;
			typedef impl																	class_type;
			typedef Nods																	nodes_type;
			typedef typename_type_k nodes_type::value_type									node_type;
			typedef Mtx1																	adjmtx_type;
			typedef typename_type_k adjmtx_type::value_type									arc_type;
			typedef typename_type_k node_type::value_type									value_type;
			typedef value_type*																pointer;
			typedef value_type const*														const_pointer;
			typedef value_type&																reference;
			typedef value_type const&														const_reference;
			typedef typename_type_k arc_type::weight_type									weight_type;
			typedef e_size_t																size_type;
			typedef e_bool_t																bool_type;
			typedef e_ptrdiff_t																difference_type;
			typedef	e_int_t																	int_type;	
			typedef size_type																index_type;
			typedef const_net_out_adjnode_iterator<nodes_type, adjmtx_type>					const_out_adjnode_iterator;
			typedef const_reverse_bidirectional_iterator_base<const_out_adjnode_iterator>	const_reverse_out_adjnode_iterator;
			typedef const_net_in_adjnode_iterator<nodes_type, adjmtx_type>					const_in_adjnode_iterator;
			typedef const_reverse_bidirectional_iterator_base<const_in_adjnode_iterator>	const_reverse_in_adjnode_iterator;
			typedef typename_type_k adjmtx_type::const_rowe_iterator						const_adjmtx_rowe_iterator;
			typedef typename_type_k adjmtx_type::const_cole_iterator						const_adjmtx_cole_iterator;
		/// @}

		private:
			impl(class_type const&);
			class_type& operator=(class_type const&);

		/// \name Constructors
		/// @{
		public:
			impl()
			{}
		/// @}

		/// \name Attributes
		/// @{
		public:
			size_type in_degree(index_type id) const	{ return derive().node_at(id).in_degree();	}
			size_type out_degree(index_type id) const	{ return derive().node_at(id).out_degree();	}
		/// @}

		/// \name Out-Adjacent Node Iterators
		/// \note cannot insert and erase nodes in the iteration 
		/// @{
		public:
			const_out_adjnode_iterator			out_adjnode_begin(index_type id) const	{ return const_out_adjnode_iterator(id, derive().adjmtx().rowe_begin(id), derive().nodes(), derive().adjmtx());	}
			const_out_adjnode_iterator			out_adjnode_end(index_type id) const	{ return const_out_adjnode_iterator(id, derive().adjmtx().rowe_end(id), derive().nodes(), derive().adjmtx());	}

			const_reverse_out_adjnode_iterator	out_adjnode_rbegin(index_type id) const	{ return const_reverse_out_adjnode_iterator(out_adjnode_end(id));	}
			const_reverse_out_adjnode_iterator	out_adjnode_rend(index_type id) const	{ return const_reverse_out_adjnode_iterator(out_adjnode_begin(id));	}
		/// @}

		/// \name In-Adjacent Node Iterators
		/// \note cannot insert and erase nodes in the iteration 
		/// @{
		public:
			const_in_adjnode_iterator			in_adjnode_begin(index_type id) const	{ return const_in_adjnode_iterator(id, derive().adjmtx().cole_begin(id), derive().nodes(), derive().adjmtx());	}
			const_in_adjnode_iterator			in_adjnode_end(index_type id) const		{ return const_in_adjnode_iterator(id, derive().adjmtx().cole_end(id), derive().nodes(), derive().adjmtx());	}

			const_reverse_in_adjnode_iterator	in_adjnode_rbegin(index_type id) const	{ return const_reverse_in_adjnode_iterator(in_adjnode_end(id));		}
			const_reverse_in_adjnode_iterator	in_adjnode_rend(index_type id) const	{ return const_reverse_in_adjnode_iterator(in_adjnode_begin(id));	}
		/// @}

		/// \name Implementions
		/// @{
		protected:
			// note: need optimization for spase_net
			void safe_remove_node(index_type id)
			{
				if (!derive().node_exists(id)) return;

				adjmtx_type& adjmtx = derive().adjmtx();
				size_type n0 = adjmtx.dim0();
				size_type n1 = adjmtx.dim1();

				EXTL_ASSERT(n0 == n1);
				for (index_type i = 0; i < n0; ++i)
				{
					// erase adjacency out-arc
					derive().unsafe_remove_arc(id, i);
					// erase adjacency in-arc
					derive().unsafe_remove_arc(i, id);
				}
				// erase node at last
				derive().unsafe_remove_node(id);
			}
			size_type			max_arcs_size_impl() const	
			{ 
				return derive().adjmtx().size();				
			}

			void				inc_degree(index_type bid, index_type eid)
			{
				derive().node_at_uncheck(bid).out_degree(derive().node_at_uncheck(bid).out_degree() + 1);
				derive().node_at_uncheck(eid).in_degree(derive().node_at_uncheck(eid).in_degree() + 1);
			}

			void				dec_degree(index_type bid, index_type eid)
			{
				if (derive().node_at_uncheck(bid).out_degree() > 0)
					derive().node_at_uncheck(bid).out_degree(derive().node_at_uncheck(bid).out_degree() - 1);
				if (derive().node_at_uncheck(eid).in_degree() > 0)
					derive().node_at_uncheck(eid).in_degree(derive().node_at_uncheck(eid).in_degree() - 1);
			}
		/// @}

		/// \name Helpers
		/// @{
		private:																							
			derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
			derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		/// @}
	
	};
};


EXTL_TEMPLATE_SPECIALISATION
struct net_base_impl<e_false_v>	// indirected net 
{
	template<	typename_param_k Dev
			,	typename_param_k Nods
			,	typename_param_k Mtx1	
			,	typename_param_k Mtx2	
			>
	struct impl
	{
		/// \name Types
		/// @{
		public:
			typedef Dev																	derived_type;
			typedef impl																class_type;
			typedef Nods																nodes_type;
			typedef typename_type_k nodes_type::value_type								node_type;
			typedef Mtx2																adjmtx_type;
			typedef typename_type_k adjmtx_type::value_type								arc_type;	
			typedef typename_type_k node_type::value_type								value_type;
			typedef value_type*															pointer;
			typedef value_type const*													const_pointer;
			typedef value_type&															reference;
			typedef value_type const&													const_reference;
			typedef typename_type_k arc_type::weight_type								weight_type;
			typedef e_size_t															size_type;
			typedef e_bool_t															bool_type;
			typedef e_ptrdiff_t															difference_type;
			typedef	e_int_t																int_type;	
			typedef size_type															index_type;
			typedef const_indirected_net_adjnode_iterator<nodes_type, adjmtx_type>		const_adjnode_iterator;
			typedef const_reverse_bidirectional_iterator_base<const_adjnode_iterator>	const_reverse_adjnode_iterator;
			typedef typename_type_k adjmtx_type::const_rowe_iterator					const_adjmtx_rowe_iterator;
			typedef typename_type_k adjmtx_type::const_cole_iterator					const_adjmtx_cole_iterator;
		/// @}

		/// \name Constructors
		/// @{
		public:
			impl()
			{}
		/// @}

		private:
			impl(class_type const&);
			class_type& operator=(class_type const&);

		/// \name Implementions
		/// @{
		protected:
			// note: need optimization for spase_net
			void safe_remove_node(index_type id)
			{
				if (!derive().node_exists(id)) return;

				adjmtx_type& adjmtx = derive().adjmtx();
				size_type n0 = adjmtx.dim0();
				size_type n1 = adjmtx.dim1();

				EXTL_ASSERT(n0 == n1);
				for (index_type i = 0; i < n0; ++i)
				{
					// erase adjacency arc
					derive().unsafe_remove_arc(id, i);
				}
				// erase node
				derive().unsafe_remove_node(id);
			}
			size_type			max_arcs_size_impl() const	
			{ 
				return (derive().adjmtx().dim0() * (derive().adjmtx().dim0() + 1)) >> 1;	
			}

			void				inc_degree(index_type bid, index_type eid)
			{
				derive().node_at_uncheck(bid).degree(derive().node_at_uncheck(bid).degree() + 1);
				derive().node_at_uncheck(eid).degree(derive().node_at_uncheck(eid).degree() + 1);
			}

			void				dec_degree(index_type bid, index_type eid)
			{
				if (derive().node_at_uncheck(bid).degree() > 0)
					derive().node_at_uncheck(bid).degree(derive().node_at_uncheck(bid).degree() - 1);
				if (derive().node_at_uncheck(eid).degree() > 0)
					derive().node_at_uncheck(eid).degree(derive().node_at_uncheck(eid).degree() - 1);
			}
		/// @}

		/// \name Adjacent Node Iterators
		/// \note cannot insert and erase nodes in the iteration 
		/// @{
		public:
			const_adjnode_iterator			adjnode_begin(index_type id) const	{ return const_adjnode_iterator(id, derive().adjmtx().rowe_begin(id), derive().nodes(), derive().adjmtx());	}
			const_adjnode_iterator			adjnode_end(index_type id) const	{ return const_adjnode_iterator(id, derive().adjmtx().rowe_end(id), derive().nodes(), derive().adjmtx());		}

			const_reverse_adjnode_iterator	adjnode_rbegin(index_type id) const	{ return const_reverse_adjnode_iterator(adjnode_end(id));		}
			const_reverse_adjnode_iterator	adjnode_rend(index_type id) const	{ return const_reverse_adjnode_iterator(adjnode_begin(id));		}
		/// @}

		/// \name Helpers
		/// @{
		private:																							
			derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
			derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		/// @}
	
	};
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_NET_BASE_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
