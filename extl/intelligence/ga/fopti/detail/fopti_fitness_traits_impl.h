/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_fitness_traits_impl.h		
 *
 * Created:		08.09.09
 * Updated:		08.09.09
 *
 * Brief: The fopti_fitness_traits_impl class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FITNESS_TRAITS_H
#define EXTL_INTELLIGENCE_GA_FITNESS_TRAITS_H

#ifndef __cplusplus
#	error fopti_fitness_traits_impl.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<e_bool_t for_max>
struct for_max_type_wrap{};

template<typename_param_k T>
struct fopti_fitness_traits_impl
{
	typedef T								float_type;
	typedef for_max_type_wrap<e_true_v>		for_max_selector_type;
	typedef for_max_type_wrap<e_false_v>	for_min_selector_type;

	// for maximum
	static float_type impl(float_type fvalue, float_type fmin, float_type /*fmax*/, for_max_selector_type)
	{
		return (fvalue < fmin)? 0 : (fvalue - fmin);
	}

	// for minimum
	static float_type impl(float_type fvalue, float_type /*fmin*/, float_type fmax, for_min_selector_type)
	{
		return (fvalue > fmax)? 0 : (fmax - fvalue);
	}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FITNESS_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
