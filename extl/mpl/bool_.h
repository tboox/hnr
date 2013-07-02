/* ///////////////////////////////////////////////////////////////////////
 * File:		bool_.h		
 *
 * Created:		08.03.17				
 * Updated:		08.05.05
 *
 * Brief: bool_ class - bool type wrap
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MPL_BOOL_H
#define EXTL_MPL_BOOL_H

/*!\file bool_.h
 * \brief bool_ class - logical operation 
 */
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_BEGIN_WHOLE_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#ifdef EXTL_MPL_SUPPORT

/*!\brief: bool_ class
 * 
 * \ingroup extl_group_mpl
 */
template< e_bool_t T >						
struct bool_									
{											
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = T);	
												
	typedef bool_<T>				type;				
	typedef e_bool_t				value_t;			
												
	operator e_bool_t() const						
	{											
		return static_cast<e_bool_t>(this->value);	
	}											
};

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MPL_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::mpl namespace
 */
EXTL_MPL_END_WHOLE_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MPL_BOOL_H */
/* //////////////////////////////////////////////////////////////////// */
