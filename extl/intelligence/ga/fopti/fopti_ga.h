/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_ga.h		
 *
 * Created:		08.09.14
 * Updated:		08.10.14
 *
 * Brief:		The Genetic Algoritm for Function Optimization - using Simple Genetic Algoritm
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_GA_H
#define EXTL_INTELLIGENCE_GA_FOPTI_GA_H

/*!\file fopti_ga.h
 * \brief The Genetic Algoritm Class
 */
#ifndef __cplusplus
#	error fopti_ga.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "fopti_ga_traits.h"
#include "fopti_ga_config.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_ga class
 * 
 * \param Func The function type
 * \param for_max Set \true for maximum 
 * \param C The configuration type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Func
		,	e_bool_t for_max	= e_true_v	
		,	typename_param_k C	= fopti_default_ga_config<for_max, Func>
		>
class fopti_ga
	: public ga_base<fopti_ga_traits<C> >
{
	/// \name Types
	/// @{
	public:
		typedef ga_base<fopti_ga_traits<C> >						base_type;
		typedef fopti_ga											class_type;
		typedef typename_type_k base_type::ga_traits_type			ga_traits_type;
		typedef typename_type_k ga_traits_type::size_type			size_type;
		typedef typename_type_k ga_traits_type::bool_type			bool_type;
		typedef typename_type_k ga_traits_type::float_type			float_type;
		typedef typename_type_k ga_traits_type::index_type			index_type;
		typedef typename_type_k ga_traits_type::int_type			int_type;
		typedef typename_type_k ga_traits_type::population_type		population_type;
		typedef typename_type_k ga_traits_type::individual_type		individual_type;
		typedef typename_type_k ga_traits_type::random_type			random_type;
		typedef typename_type_k ga_traits_type::scopes_type			scopes_type;
		typedef typename_type_k ga_traits_type::scope_type			scope_type;
		typedef typename_type_k ga_traits_type::func_type			func_type;
		typedef typename_type_k ga_traits_type::constraints_type	constraints_type;
	/// @}
		
	/// \name Constructors
	/// @{
	public:
		fopti_ga(	func_type const& func
				,	scopes_type const& sps
				,	constraints_type const& cons
				,	size_type pop_size		= 63
				,	size_type max_g			= 1000
				,	float_type cross_p		= 0.65
				,	float_type mutate_p		= 0.001
				,	random_type const& rand	= random_type()
				)
			: base_type()
		{
			this->ga_traits().func(func);
			this->ga_traits().scopes(sps);
			this->ga_traits().constraints(cons);
			this->ga_traits().pop_size(pop_size);
			this->ga_traits().max_g(max_g);
			this->ga_traits().cross_p(cross_p);
			this->ga_traits().mutate_p(mutate_p);
			this->ga_traits().rand(rand);
			this->ga_traits().init_traits();
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		float_type				fvalue(individual_type const& idl)	{ return this->ga_traits().fvalue(idl);	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_GA_H */
/* //////////////////////////////////////////////////////////////////// */
