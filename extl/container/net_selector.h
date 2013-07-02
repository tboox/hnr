/* ///////////////////////////////////////////////////////////////////////
 * File:		net_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The net selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_NET_SELECTOR_H
#define EXTL_CONTAINER_NET_SELECTOR_H

/*!\file net_selector.h
 * \brief The net selector
 */
#ifndef __cplusplus
#	error net_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_net.h"
#include "sparse_net.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief net_selector class
 *
 * \param is_dir returns \true if it's a directed net
 * \param Val the value type
 * \param Wgt the weight type
 *
 * \ingroup extl_group_memory
 */
template<	e_bool_t is_dir
		,	typename_param_k Val
		,	typename_param_k Wgt
		>
struct net_selector
{
	/// \name Types
	/// @{
	typedef basic_net<is_dir, Val, Wgt>				net_type;
	typedef sparse_net<is_dir, Val, Wgt>			sparse_net_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_NET_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


