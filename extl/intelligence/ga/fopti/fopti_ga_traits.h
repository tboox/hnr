/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_ga_traits.h		
 *
 * Created:		08.10.07
 * Updated:		08.11.07
 *
 * Brief: The fopti_ga_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_FOPTI_GA_TRAITS_H
#define EXTL_INTELLIGENCE_FOPTI_GA_TRAITS_H

/*!\file fopti_ga_traits.h
 * \brief The fopti_ga_traits class
 */
#ifndef __cplusplus
#	error fopti_ga_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_ga_traits class
 * 
 * \param C The ga_config type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k C>
class fopti_ga_traits
	: public ga_traits_base<fopti_ga_traits<C>, C>
{
	/// \name Types
	/// @{
	public:
		typedef ga_traits_base<fopti_ga_traits<C>, C>						base_type;
		typedef fopti_ga_traits												class_type;
		typedef typename_type_k base_type::config_type						config_type;
		typedef typename_type_k base_type::size_type						size_type;
		typedef typename_type_k base_type::bool_type						bool_type;
		typedef typename_type_k base_type::index_type						index_type;
		typedef typename_type_k base_type::int_type							int_type;
		typedef typename_type_k base_type::float_type						float_type;
		typedef typename_type_k base_type::random_type						random_type;
		typedef typename_type_k base_type::population_type					population_type;
		typedef typename_type_k base_type::individual_type					individual_type;
		typedef typename_type_k base_type::selection_traits_type			selection_traits_type;
		typedef typename_type_k base_type::crossover_traits_type			crossover_traits_type;
		typedef typename_type_k base_type::fitness_traits_type				fitness_traits_type;
		typedef typename_type_k base_type::rmake_traits_type				rmake_traits_type;
		typedef typename_type_k individual_type::scopes_type				scopes_type;
		typedef typename_type_k individual_type::scope_type					scope_type;
		typedef typename_type_k fitness_traits_type::penalty_traits_type	penalty_traits_type;
		typedef typename_type_k penalty_traits_type::constraints_type		constraints_type;
		typedef typename_type_k fitness_traits_type::func_traits_type		func_traits_type;
		typedef typename_type_k func_traits_type::func_type					func_type;
	/// @}

	/// \name Members
	/// @{
	private:
		scopes_type															m_scopes;
	/// @}

	/// \name Attributes
	/// @{
	public:
		float_type				fvalue(individual_type const& idl)			{ return func_traits().fvalue(idl);	}

		func_type const&		func() const								{ return func_traits().func();		}
		func_type&				func()										{ return func_traits().func();		}
		void					func(func_type const& func)					{ func_traits().func(func);			}

		scopes_type const&		scopes() const								{ return m_scopes;					}
		scopes_type&			scopes()									{ return m_scopes;					}
		void					scopes(scopes_type const& sps)				{ m_scopes = sps;					}

		constraints_type const&	constraints() const							{ return penalty_traits().constraints();	}
		constraints_type&		constraints()								{ return penalty_traits().constraints();	}
		void					constraints(constraints_type const& cons)	{ penalty_traits().constraints(cons);		}
	/// @}

	/// \name Traits
	/// @{
	private:
		func_traits_type const&		func_traits() const				{ return this->fitness_traits().func_traits();	}
		func_traits_type&			func_traits()					{ return this->fitness_traits().func_traits();	}

		penalty_traits_type const&	penalty_traits() const			{ return this->fitness_traits().penalty_traits();	}
		penalty_traits_type&		penalty_traits()				{ return this->fitness_traits().penalty_traits();	}
	/// @}

	/// \name Initialization
	/// @{
	public:
		/// initialize individual
		void init_individual(individual_type& idl)
		{
			base_type::init_individual(idl);
		}
		/// initialize rmake_traits
		void init_rmake_traits()
		{
			this->rmake_traits().init(this->rand(), scopes());
		}
		/// initialize fitness_traits
		void init_fitness_traits()
		{
			if (!(this->rmake_traits().is_valid()))
				init_rmake_traits();
			this->fitness_traits().init(this->rmake_traits());
		}
		/// initialize crossover_traits
		void init_crossover_traits()
		{
			this->crossover_traits().init(this->rand());
		}
		/// initialize mutation_traits
		void init_mutation_traits()
		{
			this->mutation_traits().init(this->rand(), scopes());
		}
		/// initialize local_search_traits
		void init_local_search_traits()
		{
			if (!(this->rmake_traits().is_valid())) 
				init_rmake_traits();
			if (!(this->fitness_traits().is_valid())) 
				init_fitness_traits();

			this->local_search_traits().init(this->rand(), this->rmake_traits(), this->fitness_traits());
		}
	/// @}
	
	/// \name Methods
	/// @{
	public:
		/// invariance
		bool_type is_valid() const
		{
			return base_type::is_valid();
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_FOPTI_GA_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
