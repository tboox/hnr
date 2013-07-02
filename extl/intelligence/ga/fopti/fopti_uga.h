/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_uga.h		
 *
 * Created:		08.09.14
 * Updated:		08.10.14
 *
 * Brief:		The Micro-population Genetic Algoritm for Function Optimization
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_UGA_H
#define EXTL_INTELLIGENCE_GA_FOPTI_UGA_H

/*!\file fopti_uga.h
 * \brief The Genetic Algoritm Class
 */
#ifndef __cplusplus
#	error fopti_uga.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "fopti_ga.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_uga class
 * 
 * \param Func The function type
 * \param for_max Set \true for maximum 
 * \param C The configuration type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Func
		,	e_bool_t for_max	= e_true_v	
		,	typename_param_k C	= fopti_test_ga_config<for_max, Func>
		>
class fopti_uga
	: public uga_base<fopti_uga<Func, for_max, C>, fopti_ga<Func, for_max, C> >
{
	/// \name Types
	/// @{
	public:
		typedef uga_base<fopti_uga<Func, for_max, C>, fopti_ga<Func, for_max, C> >	base_type;
		typedef typename_type_k base_type::ga_type								ga_type;
		typedef typename_type_k base_type::ga_traits_type						ga_traits_type;
		typedef typename_type_k base_type::size_type							size_type;
		typedef typename_type_k base_type::bool_type							bool_type;
		typedef typename_type_k base_type::float_type							float_type;
		typedef typename_type_k base_type::index_type							index_type;
		typedef typename_type_k base_type::int_type								int_type;
		typedef typename_type_k base_type::population_type						population_type;
		typedef typename_type_k base_type::individual_type						individual_type;
		typedef typename_type_k ga_type::random_type							random_type;
		typedef typename_type_k ga_type::scopes_type							scopes_type;
		typedef typename_type_k ga_type::scope_type								scope_type;
		typedef typename_type_k ga_type::func_type								func_type;
		typedef typename_type_k ga_type::constraints_type						constraints_type;
	/// @}

	private:
		ga_type																	m_ga;
		
	/// \name Constructors
	/// @{
	public:
		fopti_uga(	func_type const& func
				,	scopes_type const& sps
				,	constraints_type const& cons
				,	size_type pop_size		= 10
				,	size_type max_g			= 500
				,	size_type in_max_g		= 10
				,	float_type cross_p		= 0.65
				,	float_type mutate_p		= 0.001
				,	random_type const& rand	= random_type()
				)
			: base_type(), m_ga(func, sps,cons, pop_size, in_max_g, cross_p, mutate_p, rand)
		{
			this->ga_traits() = ga().ga_traits();
			this->ga_traits().max_g(max_g);
			this->ga_traits().init_traits();
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		ga_type const&	ga() const	{ return m_ga;	}
		ga_type&		ga()		{ return m_ga;	}
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
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_UGA_H */
/* //////////////////////////////////////////////////////////////////// */
