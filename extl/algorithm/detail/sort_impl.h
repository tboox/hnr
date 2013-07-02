/* ///////////////////////////////////////////////////////////////////////
 * File:		sort_impl.h		
 *
 * Created:		08.11.09			
 * Updated:		08.11.09
 *
 * Brief: The sort_impl algorithm
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_SORT_IMPL_H
#define EXTL_ALGORITHM_SORT_IMPL_H

/*!\file sort_impl.h
 * \brief The sort_impl algorithm
 */
#ifndef __cplusplus
#	error sort_impl.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

// swap_impl
template<typename_param_k T>
EXTL_INLINE void swap_impl(T& lhs, T& rhs)
{
	T temp = rhs;
	rhs = lhs;
	lhs = temp;
}

/* ///////////////////////////////////////////////////////////////////////
 * bubble_sort
 * time: O(n^2)
 */

// bubble_sort_impl - using operator < for ascending
template<typename_param_k InIt> 
EXTL_INLINE void bubble_sort_impl(InIt first, InIt last)
{	
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	InIt p2;
	for (InIt p1 = first; p1 != last; ++p1)
		for (p2 = p1, ++p2; p2 != last; ++p2)
			if (*p2 < *p1) swap_impl(*p1, *p2);
}
// bubble_sort_impl - using pred
template<	typename_param_k InIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void bubble_sort_impl(InIt first, InIt last, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	InIt p2;
	for (InIt p1 = first; p1 != last; ++p1)
		for (p2 = p1, ++p2; p2 != last; ++p2)
			if (pred(*p2, *p1)) swap_impl(*p1, *p2);
}

/* ///////////////////////////////////////////////////////////////////////
 * insertion_sort
 * time: O(n^2)
 */

/* insertion_sort_impl - using operator< for ascending
 *
 * old:     5       2       6       2       8       6       1
 *
 *        (hole)
 * step1: ((5))     2       6       2       8       6       1
 *        (next)
 *
 *        (hole)  
 * step2: ((2))    (5)      6       2       8       6       1
 *                (next)
 *
 *                        (hole)
 * step3:   2       5     ((6))     2       8       6       1
 *                        (next)
 *
 *                 (hole)       
 * step4:   2      ((2))   (5)     (6)      8       6       1
 *                                (next)
 *
 *                                        (hole)
 * step5:   2       2       5       6     ((8))     6       1
 *                                        (next)
 *
 *                                        (hole) 
 * step6:   2       2       5       6     ((6))    (8)       1
 *                                                (next)
 *
 *        (hole)                                         
 * step7: ((1))    (2)     (2)     (5)     (6)     (6)      (8)       
 *                                                        (next)
 */
template<typename_param_k BidIt>
EXTL_INLINE void insertion_sort_impl(BidIt first, BidIt last)
{	
	EXTL_ITERATOR_MUST_BE_BIDIRECTIONAL(BidIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	typedef typename_type_k xtl_iterator_traits<BidIt>::value_type		value_type;

	if (first != last)
	{
		for (BidIt next = first; ++next != last; )
		{	
			value_type val = *next;

			// look for hole and move elements[hole, next - 1] => [hole + 1, next]
			for (BidIt last2 = next; last2 != first && val < *--last2; next = last2)
					*next = *last2;
			
			*next = val;	// val => hole
		}
	}
}

// insertion_sort_impl - using pred
template<	typename_param_k BidIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void insertion_sort_impl(BidIt first, BidIt last, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_BIDIRECTIONAL(BidIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	typedef typename_type_k xtl_iterator_traits<BidIt>::value_type		value_type;

	if (first != last)
	{
		for (BidIt next = first; ++next != last; )
		{	
			value_type val = *next;

			// look for hole and move elements[hole, next - 1] => [hole + 1, next]
			for (BidIt last2 = next; last2 != first && pred(val, *--last2); next = last2)
					*next = *last2;
			
			*next = val;	// val => hole
		}
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * heap_sort(max-heap)
 * time: O(nlg(n))
 */

// returns \true if the given range is a valid heap - using operator < for ascending
template<typename_param_k RanIt> 
EXTL_INLINE e_bool_t is_valid_heap(RanIt first, RanIt last)
{	
	if (first != last)
	{
		for (RanIt root = first; ++first != last; ++root)
		{
			if (*root < *first)			// *root < left child
				return e_false_v;
			else if (++first == last)
				break;
			else if (*root < *first)	// *root < right child
				return e_false_v;
		}
	}
	return e_true_v;
}

// returns \true if the given range is a valid heap - using pred
template<	typename_param_k RanIt
		,	typename_param_k Pr
		> 
EXTL_INLINE e_bool_t is_valid_heap(RanIt first, RanIt last, Pr pred)
{	
	if (first != last)
	{
		for (RanIt root = first; ++first != last; ++root)
		{
			if (pred(*root, *first))		
				return e_false_v;
			else if (++first == last)
				break;
			else if (pred(*root, *first))	
				return e_false_v;
		}
	}
	return e_true_v;
}
/* push_heap_impl - using operator < for ascending
 *
 * hole: bottom => top
 * init:
 *                                          16(top)
 *                               -------------------------
 *                              |                         |
 *                              14                        10
 *                        --------------             -------------
 *                       |              |           |             |
 *                       8(parent)      7           9             3
 *                   ---------      
 *                  |         |     
 *                  2      (hole) <= 11(val)
 * after:
 *                                          16(top)
 *                               -------------------------
 *                              |                         |
 *                              14(parent)                10
 *                        --------------             -------------
 *                       |              |           |             |
 *                       11(hole)       7           9             3
 *                   ---------      
 *                  |         |    
 *                  2         8  
 */     
template<	typename_param_k RanIt
		,	typename_param_k Diff
		,	typename_param_k Val
		> 
EXTL_INLINE void push_heap_impl(RanIt first, Diff hole, Diff top, Val val)
{	
	// (hole - 1) / 2: the parent node of the hole
	// finds the final hole
	for (Diff i = (hole - 1) / 2; hole > top && *(first + i) < val; i = (hole - 1) / 2)
	{	
		// copy value: parent => hole
		*(first + hole) = *(first + i);

		// move node: hole => parent
		hole = i;
	}

	// set value
	*(first + hole) = val;	
}

// push_heap_impl - using pred
template<	typename_param_k RanIt
		,	typename_param_k Diff
		,	typename_param_k Val
		,	typename_param_k Pr
		> 
EXTL_INLINE void push_heap_impl(RanIt first, Diff hole, Diff top, Val val, Pr pred)
{	
	// (hole - 1) / 2: the parent node of the hole
	// finds the final hole
	for (Diff i = (hole - 1) / 2; hole > top && pred(*(first + i), val); i = (hole - 1) / 2)
	{	
		// copy value: parent => hole
		*(first + hole) = *(first + i);

		// move node: hole => parent
		hole = i;
	}

	// set value
	*(first + hole) = val;	
}

/* adjust_heap_impl - using operator < for ascending
 * 
 * hole: top => bottom
 * init:
 *                                          16(first)
 *                               -------------------------
 *                              |                         |
 *                           (hole)                       10
 *                        --------------             -------------
 *                       |              |           |             |
 *                       8(larger)      7           9             3
 *                   ---------       ----
 *                  |         |     |
 *                  2         4     1(bottom - 1)
 *
 * after:
 *                                          16(first)
 *                               -------------------------
 *                              |                         |
 *                              8                        10
 *                        --------------             -------------
 *                       |              |           |             |
 *                      (hole)          7           9             3
 *                   ---------       ----
 *                  |         |     |
 *                  2 (larger)4     1(bottom - 1)
 *
 * after:
 *                                          16(first)
 *                               -------------------------
 *                              |                         |
 *                              8                        10
 *                        --------------             -------------
 *                       |              |           |             |
 *                       4              7           9             3
 *                   ---------       ----
 *                  |         |     |
 *                  2      (hole)   1(bottom - 1)
 */   
template<	typename_param_k RanIt
		,	typename_param_k Diff
		,	typename_param_k Val
		>
EXTL_INLINE void adjust_heap_impl(RanIt first, Diff hole, Diff bottom, Val val)
{	
	// save top position
	Diff top = hole;

	// 2 * hole + 2: the right child node of hole
	Diff i = 2 * hole + 2;

	for (; i < bottom; i = 2 * i + 2)
	{	
		// gets the larger child node
		if (*(first + i) < *(first + (i - 1))) --i;

		// larger child => hole
		*(first + hole) = *(first + i);

		// move the hole down to it's larger child node 
		hole = i;
	}

	if (i == bottom)
	{	
		// bottom child => hole
		*(first + hole) = *(first + (bottom - 1));

		// move hole down to bottom
		hole = bottom - 1;
	}

	// push val into the hole
	push_heap_impl(first, hole, top, val);
}

// adjust_heap_impl - using pred
template<	typename_param_k RanIt
		,	typename_param_k Diff
		,	typename_param_k Val
		,	typename_param_k Pr
		>
EXTL_INLINE void adjust_heap_impl(RanIt first, Diff hole, Diff bottom, Val val, Pr pred)
{	
	// save top position
	Diff top = hole;

	// 2 * hole + 2: the right child node of hole
	Diff i = 2 * hole + 2;

	for (; i < bottom; i = 2 * i + 2)
	{	
		// gets the larger child node
		if (pred(*(first + i), *(first + (i - 1)))) --i;

		// larger child => hole
		*(first + hole) = *(first + i);

		// move the hole down to it's larger child node 
		hole = i;
	}

	if (i == bottom)
	{	
		// bottom child => hole
		*(first + hole) = *(first + (bottom - 1));

		// move hole down to bottom
		hole = bottom - 1;
	}

	// push val into the hole
	push_heap_impl(first, hole, top, val, pred);
}

// error: there are no arguments to `invariance_error' that depend on a template parameter, so a declaration of `invariance_error' must be available
/*#ifdef EXTL_COMPILER_IS_GCC
class invariance_error;
#endif*/
/* pop_heap_impl - using operator < for ascending
 * 
 * pop *first to *dest and reheap
 *                                          16 
 *                               -------------------------
 *                              |                         |
 *                              14(first)----             10
 *                        --------------     |       -------------
 *                       |              |    |      |             |
 *                       8              7    |      9             3
 *                   ---------       ----    |
 *                  |         |     |        |
 *                  2         4     1(dest)<-
 *
 */   
template<	typename_param_k RanIt
		,	typename_param_k Val
		> 
EXTL_INLINE void pop_heap_impl(RanIt first, RanIt last, RanIt dest, Val val)
{	
	EXTL_MESSAGE_ASSERT(is_valid_heap(first, last), "invalid heap");
	//EXTL_ASSERT_THROW(is_valid_heap(first, last), invariance_error("invalid heap"));

	typedef typename_type_k xtl_iterator_traits<RanIt>::difference_type	difference_type;
	*dest = *first;
	adjust_heap_impl(first, difference_type(0), difference_type(last - first), val);

	EXTL_MESSAGE_ASSERT(is_valid_heap(first, last), "invalid heap");
	//EXTL_ASSERT_THROW(is_valid_heap(first, last), invariance_error("invalid heap"));
}

// pop_heap_impl - using pred
template<	typename_param_k RanIt
		,	typename_param_k Val
		,	typename_param_k Pr
		> 
EXTL_INLINE void pop_heap_impl(RanIt first, RanIt last, RanIt dest, Val val, Pr pred)
{	
	EXTL_MESSAGE_ASSERT(is_valid_heap(first, last, pred), "invalid heap");
	//EXTL_ASSERT_THROW(is_valid_heap(first, last, pred), invariance_error("invalid heap"));

	typedef typename_type_k xtl_iterator_traits<RanIt>::difference_type	difference_type;
	*dest = *first;
	adjust_heap_impl(first, difference_type(0), difference_type(last - first), val, pred);

	EXTL_MESSAGE_ASSERT(is_valid_heap(first, last, pred), "invalid heap");
	//EXTL_ASSERT_THROW(is_valid_heap(first, last, pred), invariance_error("invalid heap"));
}
/* pop_heap_0_impl - using operator < for ascending
 * 
 * pop the top of heap to *(last - 1) and reheap
 *                                          16(first) 
 *                               ----------------|--------
 *                              |                |        |
 *                              14               |        10
 *                        --------------         |   -------------
 *                       |              |        |  |             |
 *                       8              7        |  9             3
 *                   ---------       ----        |
 *                  |         |     |            |
 *                  2         4     1(last - 1)<-
 *                                (hole)
 */   
template<typename_param_k RanIt> 
EXTL_INLINE void pop_heap_0_impl(RanIt first, RanIt last)
{	
	typedef typename_type_k xtl_iterator_traits<RanIt>::value_type			value_type;

	if (last - first > 1) 
		pop_heap_impl(first, last - 1, last - 1, value_type(*(last - 1)));
}

// pop_heap_0_impl - using pred
template<	typename_param_k RanIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void pop_heap_0_impl(RanIt first, RanIt last, Pr pred)
{	
	typedef typename_type_k xtl_iterator_traits<RanIt>::value_type			value_type;

	if (last - first > 1) 
		pop_heap_impl(first, last - 1, last - 1, value_type(*(last - 1)), pred);
}

/* make_heap_impl: - using operator < for ascending
 * heap:    16      14      10      8       7       9       3       2       4       1
 *
 *                                          16(first)
 *                               -------------------------
 *                              |                         |
 *                              14                        10
 *                        --------------             -------------
 *                       |              |           |             |
 *                       8       (bottom / 2 - 1)7  9             3
 *                   ---------       ----
 *                  |         |     |
 *                  2         4     1(bottom - 1)
 */
template<typename_param_k RanIt>
EXTL_INLINE void make_heap_impl(RanIt first, RanIt last)
{	
	typedef typename_type_k xtl_iterator_traits<RanIt>::difference_type	difference_type;
	typedef typename_type_k xtl_iterator_traits<RanIt>::value_type			value_type;

	// adjust heap[0, bottom / 2 - 1]
	// hole = (bottom / 2 - 1) ... 0
	difference_type bottom = last - first;
	for (difference_type hole = bottom / 2; hole > 0; )
	{	
		// reheap top half, bottom to top
		--hole;
		adjust_heap_impl(first, hole, bottom, value_type(*(first + hole)));
	}

	EXTL_MESSAGE_ASSERT(is_valid_heap(first, last), "invalid heap");
	//EXTL_ASSERT_THROW(is_valid_heap(first, last), invariance_error("invalid heap"));
}
// make_heap_impl: - using pred
template<	typename_param_k RanIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void make_heap_impl(RanIt first, RanIt last, Pr pred)
{	
	typedef typename_type_k xtl_iterator_traits<RanIt>::difference_type	difference_type;
	typedef typename_type_k xtl_iterator_traits<RanIt>::value_type			value_type;

	// adjust heap[0, bottom / 2 - 1]
	// hole = (bottom / 2 - 1) ... 0
	difference_type bottom = last - first;
	for (difference_type hole = bottom / 2; hole > 0; )
	{	
		// reheap top half, bottom to top
		--hole;
		adjust_heap_impl(first, hole, bottom, value_type(*(first + hole)), pred);
	}

	EXTL_MESSAGE_ASSERT(is_valid_heap(first, last, pred), "invalid heap");
	//EXTL_ASSERT_THROW(is_valid_heap(first, last, pred), invariance_error("invalid heap"));
}
/* heap_sort_impl(max-heap) - using operator < for ascending
 * 
 * init:
 *
 *                                           16(first)
 *                               -------------------------
 *                              |                         |
 *                              4                         10
 *                        --------------             -------------
 *                       |              |           |             |
 *                       14             7           9             3
 *                   ---------       ----
 *                  |         |     |
 *                  2         8     1(last - 1)
 * 
 * make_heap:
 *
 *                                           16(first)
 *                               -------------------------
 *                              |                         |
 *                              14                        10
 *                        --------------             -------------
 *                       |              |           |             |
 *                       8              7           9             3
 *                   ---------       ----
 *                  |         |     |
 *                  2         4     1(last - 1)
 * pop_heap:
 *
 *                                          16(first)--------------------------
 *                               -------------------------                     |
 *                              |                         |                    |
 *                              4                         10                   |
 *                        --------------             -------------             |
 *                       |              |           |             |            | 
 *                       14             7           9             3            |
 *                   ---------       ----                                      |
 *                  |         |     |                                          |
 *                  2         8     1(last - 1) <------------------------------ 
 *
 *                                          (hole)(first)
 *                               -------------------------               
 *                              |                         |                  
 *                              4                         10                 
 *                        --------------             -------------           
 *                       |              |           |             |          (val = 1)
 *                       14             7           9             3         
 *                   ---------       ----                                    
 *                  |         |     |                                       
 *                  2         8     16(last - 1)
 *                           
 * adjust_heap:
 *                                          14(first)
 *                               -------------------------               
 *                              |                         |                  
 *                              8                        10                 
 *                        --------------             -------------           
 *                       |              |           |             |           (val = 1)         
 *                       4              7           9             3         
 *                   ---------                                         
 *                  |         |                                            
 *                  2      (hole)(last - 1)   16
 *
 *
 * push_heap:
 *                                          14(first)
 *                               -------------------------               
 *                              |                         |                  
 *                              8                        10                 
 *                        --------------             -------------           
 *                       |              |           |             |           (val = 1)         
 *                       4              7           9             3              |
 *                   ---------                                                   |
 *                  |         | /-----------------------------------------------
 *                  2      (hole)(last - 1)   16
 *
 *                                          14(first)
 *                               -------------------------               
 *                              |                         |                  
 *                              8                        10                 
 *                        --------------             -------------           
 *                       |              |           |             |           (val = 1)         
 *                       4              7           9             3            
 *                   ---------                                                   
 *                  |         |  
 *                  2       1(last - 1)   16
 *
 * pop_heap adjust_heap push_heap ...
 *
 * final_heap:
 *                                           1(first)
 *                            
 *                         
 *                              2                         3               
 *                               
 *                              
 *                       4              7           8             9           
 *                                                            
 *             
 *                  10       14      16
 *     
 * result: 1 2 3 4 7 8 9 10 14 16
 */
template<typename_param_k RanIt> 
EXTL_INLINE void heap_sort_impl(RanIt first, RanIt last)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	make_heap_impl(first, last);

	for (; 1 < last - first; --last)
		pop_heap_0_impl(first, last);
}
// heap_sort_impl(max-heap) - using pred
template<	typename_param_k RanIt
		,	typename_param_k Pr
		> 
EXTL_INLINE void heap_sort_impl(RanIt first, RanIt last, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	make_heap_impl(first, last, pred);

	for (; 1 < last - first; --last)
		pop_heap_0_impl(first, last, pred);
}
// heap_sort_top_n - using operator < for descending 
template<	typename_param_k RanIt
		,	typename_param_k Diff
		> 
EXTL_INLINE void heap_sort_top_n_impl(RanIt first, RanIt last, Diff n)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_ASSERT(n >= 0);

	typedef typename_type_k xtl_iterator_traits<RanIt>::value_type		value_type;
	typedef reverse_iterator_base<RanIt>								reverse_iterator_type;
	reverse_iterator_type												rfirst(last);
	reverse_iterator_type												rlast(first);

	make_heap_impl(rfirst, rlast);

	for (; 1 < rlast - rfirst && n--; --rlast)
		pop_heap_0_impl(rfirst, rlast);
}

// heap_sort_top_n - using pred
template<	typename_param_k RanIt
		,	typename_param_k Diff
		,	typename_param_k Pr
		> 
EXTL_INLINE void heap_sort_top_n_impl(RanIt first, RanIt last, Diff n, Pr pred)
{	
	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(RanIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);
	EXTL_ASSERT(n >= 0);

	typedef typename_type_k xtl_iterator_traits<RanIt>::value_type		value_type;
	typedef reverse_iterator_base<RanIt>								reverse_iterator_type;
	reverse_iterator_type												rfirst(last);
	reverse_iterator_type												rlast(first);

	make_heap_impl(rfirst, rlast, pred);

	for (; 1 < rlast - rfirst && n--; --rlast)
		pop_heap_0_impl(rfirst, rlast, pred);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_SORT_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
