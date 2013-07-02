/* ///////////////////////////////////////////////////////////////////////
 * File:		sparse_net.h		
 *
 * Created:		08.11.27			
 * Updated:		08.12.09
 *
 * Brief:		The sparse_net class - compact net
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_SPARSE_NET_H
#define EXTL_CONTAINER_SPARSE_NET_H

/*!\file sparse_net.h
 * \brief sparse_net class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_CONTAINER_NET_SUPPORT)
#	error sparse_net.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "net_base.h"
#include "matrix.h"
#include "../memory/buffer.h"
#include "detail/net_traits.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!brief sparse_net
 *
 * \param is_dir returns \true if it's a directed net
 * \param Val the value type
 * \param Wgt the weight type
 *
 * \ingroup extl_group_container
 */
template<	e_bool_t is_dir
		,	typename_param_k Val
		,	typename_param_k Wgt
		>
class sparse_net
	: public net_base	<	sparse_net<is_dir, Val, Wgt>
						,	is_dir
						,	typename_type_k buffer_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::node_type>::buffer_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::sparse_matrix_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::symmetrical_sparse_matrix_type
						>
{
	/// \name Private Types
	/// @{
	private:
		typedef net_base<	sparse_net<is_dir, Val, Wgt>
						,	is_dir
						,	typename_type_k buffer_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::node_type>::buffer_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::sparse_matrix_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::symmetrical_sparse_matrix_type
						>															base_type;
		typedef typename_type_k EXTL_NS_DETAIL(net_base_impl)<is_dir>::
		template_qual_k impl<	sparse_net<is_dir, Val, Wgt>
							,	typename_type_k buffer_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::node_type>::buffer_type
							,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::sparse_matrix_type
							,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::symmetrical_sparse_matrix_type
							>														next_base_type;
		typedef typename_type_k base_type::adjmtx_type								adjmtx_type;
		typedef typename_type_k base_type::node_type								node_type;
		typedef typename_type_k base_type::nodes_type								nodes_type;
		typedef typename_type_k base_type::arc_type									arc_type;
		typedef typename_type_k base_type::weight_type								weight_type;
	#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
		friend																		base_type;
		friend																		next_base_type;
	#endif
	/// @}
	
	/// \name Public Types
	/// @{
	public:
		typedef sparse_net															class_type;
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
		typedef typename_type_k base_type::const_node_iterator						const_node_iterator;
		typedef typename_type_k base_type::const_reverse_node_iterator				const_reverse_node_iterator;
		typedef typename_type_k base_type::const_arc_iterator						const_arc_iterator;
		typedef typename_type_k base_type::const_reverse_arc_iterator				const_reverse_arc_iterator;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k sparse_net(size_type max_nodes_n)
			: base_type(max_nodes_n)
		{
		}
		sparse_net(class_type const& rhs)
			: base_type(rhs)
		{
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		bool_type			arc_exists(index_type bid, index_type eid) const
		{
			if (!(bid < this->adjmtx().dim0() && eid < this->adjmtx().dim1())) 
				return e_false_v;
			return this->adjmtx().exists(bid, eid);	
		}
	/// @}

	/// \name Helpers
	/// @{
#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
	protected:
#else
	public:
#endif
		void	clear_adjmtx()
		{
			this->adjmtx().clear();	
		}
		void	unsafe_insert_arc(index_type bid, index_type eid, weight_type w)
		{
			EXTL_ASSERT(this->is_valid());

			bool_type has_existed = e_false_v;
			this->adjmtx().insert(bid, eid, arc_type(bid, eid, w), &has_existed);

			if (!has_existed)
			{
				this->inc_degree(bid, eid);
				++(this->m_arcs_n);
			}
			
			EXTL_ASSERT(this->is_valid());
		}

		void	unsafe_remove_arc(index_type bid, index_type eid)
		{
			EXTL_ASSERT(this->is_valid());

			bool_type has_existed = e_false_v;
			this->adjmtx().erase(bid, eid, &has_existed);

			if (has_existed)
			{
				this->dec_degree(bid, eid);
				--(this->m_arcs_n);
			}

			EXTL_ASSERT(!arc_exists(bid, eid));
			EXTL_ASSERT(this->is_valid());
		}
	/// @}
	

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& rhs)	{ return base_type::operator=(rhs);		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_SPARSE_NET_H */
/* //////////////////////////////////////////////////////////////////// */
