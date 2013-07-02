/* ///////////////////////////////////////////////////////////////////////
 * File:		stats.h		
 *
 * Created:		08.07.01			
 * Updated:		09.01.26	
 *
 * Brief:		the numerical statistics algorithm
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ALGORITHM_STATS_H
#define EXTL_ALGORITHM_STATS_H

/*!\file stats.h
 * \brief the numerical statistics algorithm
 */
#ifndef __cplusplus
#	error stats.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "std/algorithm.h"
#include "detail/container_traits.h"
#include "../math/arithmetic.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/// stats_max
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_max(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	InIt pos = first;
	for (; first != last; ++first)
		if (*pos < *first) pos = first;
	return (*pos); 
}
/// stats_max
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_max(C const& container)
{
	return stats_max(container.begin(), container.end()); 
}

/// stats_min
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_min(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	InIt pos = first;
	for (; first != last; ++first)
		if (*first < *pos) pos = first;
	return (*pos); 
}

/// stats_min
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_min(C const& container)
{
	return stats_min(container.begin(), container.end()); 
}

/// stats_sum
/// sum = (x1 + x2 + ... + xn);
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_sum(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	value_type ret(0);

	for (; first != last; ++first)
		ret += *first;
	return ret; 
}

/// stats_sum
/// sum = (x1 + x2 + ... + xn);
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_sum(C const& container)
{
	return stats_sum(container.begin(), container.end()); 
}

/// stats_avg
/// average = (x1 + x2 + ... + xn) / n;
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_avg(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	value_type ret(0), n(0);

	for (; first != last; ++first, ++n)
		ret += *first;
	return (ret / n); 
}

/// stats_avg
/// average = (x1 + x2 + ... + xn) / n;
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_avg(C const& container)
{
	return stats_avg(container.begin(), container.end()); 
}

/// stats_var
/// variance = ((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / (n - 1);
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_var(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	value_type ret(0), n(0);

	value_type avg = stats_avg(first, last);
	for (; first != last; ++first, ++n)
		ret += (*first - avg) * (*first - avg);

	EXTL_ASSERT(n > 1);
	return (ret / (n - 1)); 
}

/// stats_var
/// variance = ((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / (n - 1;
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_var(C const& container)
{
	return stats_var(container.begin(), container.end()); 
}

/// stats_sd
/// standard deviation = sqrt(((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / (n - 1);
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_sd(InIt first, InIt last)
{
#ifdef EXTL_COMPILER_IS_WATCOM
	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	return xtl_sqrt(static_cast<value_type>(stats_var(first, last))); 
#else // WATCOM error: function argument(s) do not match those in prototype 
	return xtl_sqrt(stats_var(first, last)); 
#endif
}

/// stats_sd
/// standard deviation = sqrt(((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / (n - 1);
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_sd(C const& container)
{
	return stats_sd(container.begin(), container.end()); 
}

/// stats_norm_1
/// first-order norm: ||x|| = |x1| + |x2| + ... + |xn|;
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_norm_1(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	value_type ret(0);

	for (; first != last; ++first)
		ret += xtl_abs(*first);
	return ret; 
}

/// stats_norm_1
/// first-order norm: ||x|| = |x1| + |x2| + ... + |xn|;
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_norm_1(C const& container)
{
	return stats_norm_1(container.begin(), container.end()); 
}

/// stats_norm_22
/// second-order norm^2: ||x|| = |x1|^2 + |x2|^2 + ... + |xn|^2;
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_norm_22(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	value_type ret(0);

	for (; first != last; ++first)
		ret += (*first) * (*first);
	return ret; 
}

/// stats_norm2
/// second-order norm: ||x|| = sqrt(|x1|^2 + |x2|^2 + ... + |xn|^2);
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_norm_22(C const& container)
{
	return stats_norm_22(container.begin(), container.end()); 
}

/// stats_norm_2
/// second-order norm: ||x|| = sqrt(|x1|^2 + |x2|^2 + ... + |xn|^2);
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_norm_2(InIt first, InIt last)
{
#ifdef EXTL_COMPILER_IS_WATCOM
	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	return xtl_sqrt(static_cast<value_type>(stats_norm_22(first, last))); 
#else // WATCOM error: function argument(s) do not match those in prototype 
	return xtl_sqrt(stats_norm_22(first, last)); 
#endif
}

/// stats_norm2
/// second-order norm: ||x|| = sqrt(|x1|^2 + |x2|^2 + ... + |xn|^2);
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_norm_2(C const& container)
{
	return stats_norm_2(container.begin(), container.end()); 
}

/// stats_norm_i
/// stats_infinite norm: ||x|| = max(|x1|, |x2|, ... , |xn|);
/// \ingroup extl_group_algorithm
template<typename_param_k InIt> 
EXTL_INLINE typename_type_ret_k xtl_iterator_traits<InIt>::
value_type stats_norm_i(InIt first, InIt last)
{
	EXTL_ITERATOR_MUST_BE_INPUT(InIt);
	EXTL_ASSERT(std_distance(first, last) >= 0);

	typedef typename_type_k xtl_iterator_traits<InIt>::value_type	value_type;
	value_type ret(xtl_abs(*first));

	for (; first != last; ++first)
		if (ret < xtl_abs(*first)) ret = xtl_abs(*first);
	return ret; 
}

/// stats_norm_i
/// stats_infinite norm: ||x|| = max(|x1|, |x2|, ... , |xn|);
/// \ingroup extl_group_algorithm
template<typename_param_k C> 
EXTL_INLINE typename_type_ret_k EXTL_NS_DETAIL(container_traits)<C>::
value_type stats_norm_i(C const& container)
{
	return stats_norm_i(container.begin(), container.end()); 
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ALGORITHM_STATS_H */
/* //////////////////////////////////////////////////////////////////// */
