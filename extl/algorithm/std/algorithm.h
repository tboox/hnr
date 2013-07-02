/* ///////////////////////////////////////////////////////////////////////
 * File:		algorithm.h		
 *
 * Created:		08.04.08			
 * Updated:		08.04.15	
 *
 * Brief:		The standard library algorithms
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_STD_ALGORITHM_H
#define EXTL_ALGORITHM_STD_ALGORITHM_H

/*!\file algorithm.h
 * \brief The standard library algorithms
 * \defgroup extl_group_algorithm
 */
#ifndef __cplusplus
#	error algorithm.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "../detail/sort_impl.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
// the maximum number of insertion_sort
#define EXTL_ALGORITHM_ISORT_MAX	(32)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!std_swap
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k T>
EXTL_INLINE void std_swap(T& lhs, T& rhs)
{
	T temp = rhs;
	rhs = lhs;
	lhs = temp;
}

/*!std_copy
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt, typename_param_k OutIt>
EXTL_INLINE OutIt std_copy(InIt first, InIt last, OutIt dest)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
    for(; first != last; ++first, ++dest)
    {
        *dest = *first;
    }
    return dest;
}

/*!std_distance
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k InIt
		,	typename_param_k Diff
		>
EXTL_INLINE void _distance_helper(InIt first, InIt last, Diff& offset, std_input_iterator_tag)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	for (; first != last; ++first)
			++offset;
}
// optimization 
template<	typename_param_k InIt
		,	typename_param_k Diff
		>
EXTL_INLINE void _distance_helper(InIt first, InIt last, Diff& offset, std_random_access_iterator_tag)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	offset += last - first;
}
template<typename_param_k InIt>
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
difference_type std_distance(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	typedef typename_type_k xtl_iterator_traits<InIt>::iterator_category	iterator_category; 
	typedef typename_type_k xtl_iterator_traits<InIt>::difference_type		difference_type;
	difference_type offset = 0;
	_distance_helper(first, last, offset, iterator_category());
	return offset;
}
/*!std_foreach
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt, typename_param_k Pr>
EXTL_INLINE Pr std_foreach(InIt first, InIt last, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	for (; first != last; ++first)
		pred(*first);
	return pred;
}
/*!std_find
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt, typename_param_k Val> 
EXTL_INLINE InIt std_find(InIt first, InIt last, Val const& value)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	for (; first != last; ++first)
		if (*first == value) break;
	return first;
}
/*!std_find_if
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k InIt, typename_param_k Pr> 
EXTL_INLINE InIt std_find_if(InIt first, InIt last, Pr pred)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	for (; first != last; ++first)
		if (pred(*first)) break;
	return first; 
}

/*!std_sort - using operator < for ascending
 *
 * \ingroup extl_group_algorithm
 */
template<typename_param_k RanIt> 
EXTL_INLINE void std_sort(RanIt first, RanIt last)
{
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	
	typedef typename_type_k xtl_iterator_traits<RanIt>::difference_type		difference_type;
	difference_type offset = last - first;
	EXTL_ASSERT(offset >= 0);

	if (EXTL_ALGORITHM_ISORT_MAX < offset)
		EXTL_NS_DETAIL(heap_sort_impl)(first, last);
	else EXTL_NS_DETAIL(insertion_sort_impl)(first, last); 
}

/*!std_sort - using pred
 *
 * \ingroup extl_group_algorithm
 */
template<	typename_param_k RanIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void std_sort(RanIt first, RanIt last, Pr pred)
{
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	typedef typename_type_k xtl_iterator_traits<RanIt>::difference_type		difference_type;
	difference_type offset = last - first;
	EXTL_ASSERT(offset >= 0);

	if (EXTL_ALGORITHM_ISORT_MAX < offset)
		EXTL_NS_DETAIL(heap_sort_impl)(first, last, pred);
	else EXTL_NS_DETAIL(insertion_sort_impl)(first, last, pred); 
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_STD_ALGORITHM_H */
/* //////////////////////////////////////////////////////////////////// */
