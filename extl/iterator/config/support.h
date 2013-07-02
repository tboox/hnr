/* ///////////////////////////////////////////////////////////////////////
 * File:		support.h		
 *
 * Created:		08.11.20					
 * Updated:		08.11.20	
 *
 * Brief:		The Iterator Library Support
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_ITERATOR_CONFIG_SUPPORT_H
#define EXTL_ITERATOR_CONFIG_SUPPORT_H

#ifndef EXTL_ITERATOR_CONFIG_H
#	error This file must be included of extl\iterator\config\config.h
#endif

#ifndef EXTL_TYPE_CONFIG_H
#	include "../type/config/config.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */

/* ///////////////////////////////////////////////////////////////////////
 * raw pointer iterator traits support
 * eg: iterator_traits<T*>::...
 */
#ifdef EXTL_ITERATOR_RAW_POINTER_ITERATOR_TRAITS_SUPPORT
#	undef EXTL_ITERATOR_RAW_POINTER_ITERATOR_TRAITS_SUPPORT
#endif

#if defined(EXTL_MEMBER_TEMPLATE_CLASS_SUPPORT) && \
		defined(EXTL_TYPE_TRAITS_IS_PTR_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_IS_CONST_SUPPORT) && \
				defined(EXTL_TYPE_TRAITS_IS_REF_SUPPORT) && \
					defined(EXTL_TYPE_TRAITS_REMOVE_PTR_SUPPORT) && \
						defined(EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT) && \
							defined(EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT) && \
								defined(EXTL_TYPE_TRAITS_ADD_REF_SUPPORT) && \
									defined(EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT) && \
										defined(EXTL_MPL_IF_SUPPORT)
#	define EXTL_ITERATOR_RAW_POINTER_ITERATOR_TRAITS_SUPPORT
#endif

/* pointer as iterator support */
#ifdef EXTL_ITERATOR_POINTER_AS_ITERATOR_SUPPORT
#	undef EXTL_ITERATOR_POINTER_AS_ITERATOR_SUPPORT
#endif

#if defined(EXTL_ITERATOR_RAW_POINTER_ITERATOR_TRAITS_SUPPORT)
#	define EXTL_ITERATOR_POINTER_AS_ITERATOR_SUPPORT
#endif
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_CONFIG_SUPPORT_H */
/* //////////////////////////////////////////////////////////////////// */
