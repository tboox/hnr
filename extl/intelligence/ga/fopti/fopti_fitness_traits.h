/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_fitness_traits.h		
 *
 * Created:		08.10.07
 * Updated:		08.10.07
 *
 * Brief: The fopti_fitness_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_FITNESS_TRAITS_H
#define EXTL_INTELLIGENCE_GA_FOPTI_FITNESS_TRAITS_H

/*!\file fopti_fitness_traits.h
 * \brief The fopti_fitness_traits class
 */
#ifndef __cplusplus
#	error fopti_fitness_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/fopti_fitness_traits_impl.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_fitness_traits class
 * 
 * \param for_max Set \true for maximum 
 * \param Pop The population type
 * \param Pen The penalty_traits type
 * \param Rt The rmake_traits type
 *
 * \note There is a problem that the precision is not enough if the function value is too large.
 *
 * \ingroup extl_group_intelligence
 */
template<	e_bool_t for_max
		,	typename_param_k Pop
		,	typename_param_k Pen
		,	typename_param_k Rt
		>
class fopti_fitness_traits
	: public fitness_traits_base<fopti_fitness_traits<for_max, Pop, Pen, Rt>, Pop, Pen >
{
	/// \name Types
	/// @{
	public:
		typedef fitness_traits_base<fopti_fitness_traits<for_max, Pop, Pen, Rt>, Pop, Pen >	base_type;
		typedef fopti_fitness_traits														class_type;
		typedef typename_type_k base_type::population_type									population_type;
		typedef typename_type_k base_type::individual_type									individual_type;
		typedef typename_type_k base_type::size_type										size_type;
		typedef typename_type_k base_type::bool_type										bool_type;
		typedef typename_type_k base_type::index_type										index_type;
		typedef typename_type_k base_type::int_type											int_type;
		typedef typename_type_k base_type::float_type										float_type;
		typedef typename_type_k base_type::penalty_traits_type								penalty_traits_type;
		typedef typename_type_k penalty_traits_type::func_traits_type						func_traits_type;
		typedef EXTL_NS_DETAIL(for_max_type_wrap)<for_max>									impl_selector_type;	
		typedef EXTL_NS_DETAIL(fopti_fitness_traits_impl)<float_type>						traits_impl_type;
		typedef Rt																			rmake_traits_type;
	/// @}

	/// \name Members
	/// @{
	private:
		float_type																			m_fmin;
		float_type																			m_fmax;
		func_traits_type																	m_ft;
	/// @}
		
	/// \name Traits
	/// @{
	public:
		func_traits_type const&	func_traits() const	{ return m_ft;	}
		func_traits_type&		func_traits()		{ return m_ft;	}
	/// @}

	/// \name Methods
	/// @{
	public:
		void init(rmake_traits_type& rt)
		{
			individual_type idl;
			float_type fmin_ = func_traits().fvalue(rt.rmake(idl));
			float_type fmax_ = fmin_;

			for (size_type i = 0; i < 100; ++i)
			{
				float_type fvalue_ = func_traits().fvalue(rt.rmake(idl));
				fmin_ = fvalue_ < fmin_? fvalue_ : fmin_;
				fmax_ = fvalue_ > fmax_? fvalue_ : fmax_;
			}

			m_fmin = (fmin_ - (fmax_ - fmin_));
			m_fmax = (fmax_ + (fmax_ - fmin_));

			base_type::init();
		}
	/// @}

	/// \name Implemention
	/// @{
	public:
		void do_fitness(individual_type& idl)
		{
			idl.fitness(traits_impl_type::impl(func_traits().fvalue(idl), m_fmin, m_fmax, impl_selector_type()));
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_FITNESS_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
