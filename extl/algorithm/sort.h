/* ///////////////////////////////////////////////////////////////////////
 * File:		sort.h		
 *
 * Created:		08.11.09			
 * Updated:		08.11.09
 *
 * Brief: The sort algorithm
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_SORT_H
#define EXTL_ALGORITHM_SORT_H

/*!\file sort.h
 * \brief The sort algorithm
 */
#ifndef __cplusplus
#	error sort.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "std/algorithm.h"
#include "detail/sort_impl.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * bubble_sort
 * time: O(n^2)
 */

/*!bubble_sort - using operator < for ascending
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt> 
EXTL_INLINE void bubble_sort(InIt first, InIt last)
{	
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(bubble_sort_impl)(first, last); 
}

/*!bubble_sort - using pred
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k InIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void bubble_sort(InIt first, InIt last, Pr pred)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(bubble_sort_impl)(first, last, pred); 
}

/*!insertion_sort - using operator < for ascending
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k BidIt>
EXTL_INLINE void insertion_sort(BidIt first, BidIt last)
{	
	EXTL_ITERATOR_MUST_BE_BIDIRECTIONAL(BidIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(insertion_sort_impl)(first, last); 
}

/*!insertion_sort - using pred
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k BidIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void insertion_sort(BidIt first, BidIt last, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_BIDIRECTIONAL(BidIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(insertion_sort_impl)(first, last, pred); 
}

/* ///////////////////////////////////////////////////////////////////////
 * heap_sort
 * time: O(nlg(n))
 */

/*!heap_sort - using operator < for ascending
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k RanIt> 
EXTL_INLINE void heap_sort(RanIt first, RanIt last)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(heap_sort_impl)(first, last);
}

/*!heap_sort - using pred
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k RanIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void heap_sort(RanIt first, RanIt last, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(heap_sort_impl)(first, last, pred);
}

/*!heap_sort_top_n - using operator < for descending 
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k RanIt
		,	typename_param_k Diff
		> 
EXTL_INLINE void heap_sort_top_n(RanIt first, RanIt last, Diff n)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(heap_sort_top_n_impl)(first, last, n);
}

/*!heap_sort_top_n - using pred
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k RanIt
		,	typename_param_k Diff
		,	typename_param_k Pr
		> 
EXTL_INLINE void heap_sort_top_n(RanIt first, RanIt last, Diff n, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_NS_DETAIL(heap_sort_top_n_impl)(first, last, n, pred);
}

/*!xtl_sort - using operator < for ascending
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k RanIt> 
EXTL_INLINE void xtl_sort(RanIt first, RanIt last)
{
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	std_sort(first, last);
}

/*!xtl_sort - using pred
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k RanIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void xtl_sort(RanIt first, RanIt last, Pr pred)
{
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	std_sort(first, last, pred);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_SORT_H */
/* //////////////////////////////////////////////////////////////////// */
