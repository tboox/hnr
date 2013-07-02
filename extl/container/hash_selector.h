/* ///////////////////////////////////////////////////////////////////////
 * File:		hash_selector.h		
 *
 * Created:		08.12.07				
 * Updated:		08.12.07	
 *
 * Brief:		The hash selector
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_HASH_SELECTOR_H
#define EXTL_CONTAINER_HASH_SELECTOR_H

/*!\file hash_selector.h
 * \brief The hash selector
 */
#ifndef __cplusplus
#	error hash_selector.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "fixed_hash.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief hash_selector class
 *
 * \param Key The key type
 * \param Map The mapped type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k Key
		,	typename_param_k Map
		>
struct hash_selector
{
	/// \name Types
	/// @{
#if defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) && \
			!defined(EXTL_COMPILER_IS_DMC)
	typedef fixed_hash<Key, Map>				hash_type;
#else
	typedef fixed_hash	<	Key, Map
						,	EXTL_FIXED_HASH_DEFAULT_TABLE_SIZE
						,	hash_key_traits<Key, TABLE_SIZE>
						,	typename_type_k allocator_selector<Map>::allocator_type 
						>						hash_type;
#endif /* EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT */
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_HASH_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */


