/* ///////////////////////////////////////////////////////////////////////
 * File:		float_mutation_impl.h		
 *
 * Created:		08.11.04
 * Updated:		08.11.07
 *
 * Brief: The float_mutation_impl class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FLOAT_MUTATION_IMPL_H
#define EXTL_INTELLIGENCE_GA_FLOAT_MUTATION_IMPL_H

#ifndef __cplusplus
#	error float_mutation_impl.h need be supported by c++.
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

template<typename_param_k Rand>
class float_mutation_impl
{
	public:
		typedef e_size_t					size_type;
		typedef e_float_t					float_type;
		typedef Rand						random_type;

	public:
		static float_type mutate(float_type old_value, float_type sp_size, random_type& rand)
		{
			float_type aj;
			float_type dt = 0, m = 20, p2j = 1;
			for (size_type j = 0; j < m; ++j)
			{
				aj = static_cast<float_type>(rand.fgenerate(0, 1) <= (1 / m));
				dt += aj / p2j;
				p2j *= 2;	// p2 = pow2(j);
			}

			return old_value + 0.5 * sp_size * dt * (rand.generate(0, 2)? 1 : -1);
		}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FLOAT_MUTATION_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
