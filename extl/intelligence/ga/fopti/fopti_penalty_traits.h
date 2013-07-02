/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_penalty_traits.h		
 *
 * Created:		08.10.23
 * Updated:		08.10.23
 *
 * Brief: The fopti_penalty_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_PENALTY_TRAITS_H
#define EXTL_INTELLIGENCE_GA_FOPTI_PENALTY_TRAITS_H

/*!\file fopti_penalty_traits.h
 * \brief The fopti_penalty_traits class
 */
#ifndef __cplusplus
#	error fopti_penalty_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "fopti_constraints.h"
#include "fopti_func_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_penalty_traits class
 * 
 * \param Idl The individual type
 * \param Func The function type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Idl
		,	typename_param_k Func
		>
class fopti_penalty_traits
	: public penalty_traits_base<fopti_penalty_traits<Idl, Func>, Idl >
{
	/// \name Types
	/// @{
	public:
		typedef penalty_traits_base<fopti_penalty_traits<Idl, Func>, Idl >		base_type;
		typedef fopti_penalty_traits											class_type;
		typedef typename_type_k base_type::individual_type						individual_type;
		typedef typename_type_k base_type::size_type							size_type;
		typedef typename_type_k base_type::bool_type							bool_type;
		typedef typename_type_k base_type::index_type							index_type;
		typedef typename_type_k base_type::int_type								int_type;
		typedef typename_type_k base_type::float_type							float_type;
		typedef Func															func_type;
		typedef fopti_func_traits<individual_type, func_type>					func_traits_type;
		typedef fopti_constraints<func_traits_type>								constraints_type;
	/// @}
		
	/// \name Constructors
	/// @{
	private:
		constraints_type														m_cons;
	/// @}

	/// \name Attributes
	/// @{
	public:
		constraints_type const&	constraints() const							{ return m_cons;	}
		constraints_type&		constraints()								{ return m_cons;	}
		void					constraints(constraints_type const& cons)	{ m_cons = cons;	}
	/// @}

	private: 
		// unfitness >= 0
		float_type unfitness(index_type i, individual_type const& idl)
		{
			float_type unfit = constraints()[i].fvalue(idl);
			return (unfit < 0)? 0 : unfit;
		}
	
	public:
		// pena = 1 - avg(unfit_i / (unfit_max + 1))
		// fit = fit * pena
		void do_penalty(individual_type& idl)
		{
			size_type n = constraints().size();
			if (n == 0) return ;

			// calculates the maximum
			EXTL_ASSERT(n > 0);
			index_type i = 0;
			float_type no_max = unfitness(i, idl);
			for (i = 1; i < n; ++i)
			{
				float_type no = unfitness(i, idl);
				no_max = (no > no_max)? no : no_max;
			}
			if (no_max == 0) return ;

			float_type sum = 0;
			for (i = 0; i < n; ++i)
			{
				// If only one individual need penalty 
				// then (unfitness(i, idl) / no_max) always is one and pena will be unchanged.
				// But pena will be decreased with the unfitness if using (no_max + 1).
				sum += unfitness(i, idl) / (no_max + 1);
			}

			// pena is in range: [0, 1]
			float_type pena = 1 - sum / n;

			//printf("%f %f %f %f\n", idl.value(0), pena, idl.fitness(), idl.fitness() * pena);

			// the penalty of the fitness
			idl.fitness(idl.fitness() * pena);
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_PENALTY_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
