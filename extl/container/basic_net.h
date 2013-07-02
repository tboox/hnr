/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_net.h		
 *
 * Created:		08.11.27			
 * Updated:		08.12.09
 *
 * Brief:		The basic_net class - compact net
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BASIC_NET_H
#define EXTL_CONTAINER_BASIC_NET_H

/*!\file basic_net.h
 * \brief basic_net class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_CONTAINER_NET_SUPPORT)
#	error basic_net.h is not supported by the current compiler.
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


/*!brief basic_net
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
class basic_net
	: public net_base	<	basic_net<is_dir, Val, Wgt>
						,	is_dir
						,	typename_type_k buffer_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::node_type>::buffer_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::matrix_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::symmetrical_matrix_type
						>
{
	/// \name Private Types
	/// @{
	private:
		typedef net_base<	basic_net<is_dir, Val, Wgt>
						,	is_dir
						,	typename_type_k buffer_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::node_type>::buffer_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::matrix_type
						,	typename_type_k matrix_selector<typename_type_k EXTL_NS_DETAIL(net_traits)<is_dir, Val, Wgt>::arc_type>::symmetrical_matrix_type
						>															base_type;
		typedef typename_type_k base_type::adjmtx_type								adjmtx_type;
		typedef typename_type_k base_type::node_type								node_type;
		typedef typename_type_k base_type::nodes_type								nodes_type;
		typedef typename_type_k base_type::arc_type									arc_type;
		typedef typename_type_k base_type::weight_type								weight_type;
	/// @}
	
	/// \name Public Types
	/// @{
	public:
		typedef basic_net															class_type;
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
		explicit_k basic_net(size_type max_nodes_n)
			: base_type(max_nodes_n)
		{
		}
		basic_net(class_type const& rhs)
			: base_type(rhs)
		{
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
#endif	/* EXTL_CONTAINER_BASIC_NET_H */
/* //////////////////////////////////////////////////////////////////// */
