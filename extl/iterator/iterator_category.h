/* ///////////////////////////////////////////////////////////////////////
 * File:		iterator_category.h		
 *
 * Created:		08.04.07				
 * Updated:		08.04.15	
 *
 * Brief: Iterator categories
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_ITERATOR_CATEGORY_H
#define EXTL_ITERATOR_ITERATOR_CATEGORY_H

/*!\file iterator_category.h
 * \brief iterator_category class
 */
#ifndef __cplusplus
#	error iterator_category.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/* ///////////////////////////////////////////////////////////////////////
 * Five kind of iterator categories
 */
#if defined(EXTL_NO_STL)
/// input_iterator_tag
struct std_input_iterator_tag {};
/// output_iterator_tag
struct std_output_iterator_tag {};
/// forward_iterator_tag
struct std_forward_iterator_tag
	: public std_input_iterator_tag {};
/// bidirectional_iterator_tag
struct std_bidirectional_iterator_tag
	: public std_forward_iterator_tag {};
/// random_access_iterator_tag
struct std_random_access_iterator_tag
	: public std_bidirectional_iterator_tag {};
#else
/// input_iterator_tag
typedef EXTL_NS_STD(input_iterator_tag)			std_input_iterator_tag;
/// output_iterator_tag
typedef EXTL_NS_STD(output_iterator_tag)		std_output_iterator_tag;
/// forward_iterator_tag
typedef EXTL_NS_STD(forward_iterator_tag)		std_forward_iterator_tag;
/// bidirectional_iterator_tag
typedef EXTL_NS_STD(bidirectional_iterator_tag)	std_bidirectional_iterator_tag;
/// random_access_iterator_tag
typedef EXTL_NS_STD(random_access_iterator_tag)	std_random_access_iterator_tag;
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_ITERATOR_CATEGORY_H */
/* //////////////////////////////////////////////////////////////////// */
