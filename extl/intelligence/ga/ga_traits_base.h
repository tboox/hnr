/* ///////////////////////////////////////////////////////////////////////
 * File:		ga_traits_base.h		
 *
 * Created:		08.10.07
 * Updated:		08.11.07
 *
 * Brief: The ga_traits_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_TRAITS_BASE_H
#define EXTL_INTELLIGENCE_GA_TRAITS_BASE_H

/*!\file ga_traits_base.h
 * \brief The ga_traits_base class
 */
#ifndef __cplusplus
#	error ga_traits_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief ga_traits_base class
 * 
 * \param D The derived type
 * \param C The ga_config type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k D
		,	typename_param_k C
		>
class ga_traits_base
{
	/// \name Types
	/// @{
	public:
		typedef D														derived_type;
		typedef ga_traits_base											class_type;
		typedef C														config_type;
		typedef typename_type_k config_type::population_type			population_type;
		typedef typename_type_k population_type::individual_type		individual_type;
		typedef typename_type_k individual_type::size_type				size_type;
		typedef typename_type_k individual_type::bool_type				bool_type;
		typedef typename_type_k individual_type::index_type				index_type;
		typedef typename_type_k individual_type::int_type				int_type;
		typedef typename_type_k individual_type::float_type				float_type;
		typedef typename_type_k config_type::random_type				random_type;
		typedef typename_type_k config_type::selection_traits_type		selection_traits_type;
		typedef typename_type_k config_type::crossover_traits_type		crossover_traits_type;
		typedef typename_type_k config_type::cross_p_traits_type		cross_p_traits_type;
		typedef typename_type_k config_type::mutation_traits_type		mutation_traits_type;
		typedef typename_type_k config_type::mutate_p_traits_type		mutate_p_traits_type;
		typedef typename_type_k config_type::stop_traits_type			stop_traits_type;
		typedef typename_type_k config_type::rmake_traits_type			rmake_traits_type;
		typedef typename_type_k config_type::fitness_traits_type		fitness_traits_type;
		typedef typename_type_k config_type::local_search_traits_type	local_search_traits_type;
	/// @}

	/// \name Members
	/// @{
	private:
		size_type														m_max_g;
		size_type														m_pop_size;
		random_type														m_rand;
		float_type														m_cross_p;
		float_type														m_mutate_p;
		selection_traits_type											m_selection_traits;
		crossover_traits_type											m_crossover_traits;
		mutation_traits_type											m_mutation_traits;
		stop_traits_type												m_stop_traits;
		rmake_traits_type												m_rmake_traits;
		fitness_traits_type												m_fitness_traits;
		cross_p_traits_type												m_cross_p_traits;
		mutate_p_traits_type											m_mutate_p_traits;
		local_search_traits_type										m_local_search_traits;
	/// @}
		
	/// name Attributes
	/// @{
	public:
		random_type const&		rand() const				{ return m_rand;			}
		random_type&			rand()						{ return m_rand;			}
		void					rand(random_type const& rand){ m_rand = rand;			}
	
		size_type const			pop_size() const			{ return m_pop_size;		}
		void					pop_size(size_type n)		{ m_pop_size = n;			}

		size_type const			max_g() const				{ return m_max_g;			}
		void					max_g(size_type n)			{ m_max_g = n;				}

		float_type const		cross_p() const				{ return m_cross_p;			}
		void					cross_p(float_type p)		{ m_cross_p = p;			}

		float_type const		mutate_p() const			{ return m_mutate_p;		}
		void					mutate_p(float_type p)		{ m_mutate_p = p;			}
	/// @}

	/// \name Traits
	/// @{
	protected:
		selection_traits_type const&	selection_traits() const	{ return m_selection_traits;	}
		selection_traits_type&			selection_traits()			{ return m_selection_traits;	}

		crossover_traits_type const&	crossover_traits() const	{ return m_crossover_traits;	}
		crossover_traits_type&			crossover_traits()			{ return m_crossover_traits;	}

		mutation_traits_type const&		mutation_traits() const		{ return m_mutation_traits;		}
		mutation_traits_type&			mutation_traits()			{ return m_mutation_traits;		}

		stop_traits_type const&			stop_traits() const			{ return m_stop_traits;			}
		stop_traits_type&				stop_traits()				{ return m_stop_traits;			}

		rmake_traits_type const&		rmake_traits() const		{ return m_rmake_traits;		}
		rmake_traits_type&				rmake_traits()				{ return m_rmake_traits;		}

		fitness_traits_type const&		fitness_traits() const		{ return m_fitness_traits;		}
		fitness_traits_type&			fitness_traits()			{ return m_fitness_traits;		}

		cross_p_traits_type const&		cross_p_traits() const		{ return m_cross_p_traits;		}
		cross_p_traits_type&			cross_p_traits()			{ return m_cross_p_traits;		}

		mutate_p_traits_type const&		mutate_p_traits() const		{ return m_mutate_p_traits;		}
		mutate_p_traits_type&			mutate_p_traits()			{ return m_mutate_p_traits;		}

		local_search_traits_type const&	local_search_traits() const	{ return m_local_search_traits;	}
		local_search_traits_type&		local_search_traits()		{ return m_local_search_traits;	}
	/// @}

	/// \name Initialization
	/// @{
	protected:
		void init_rmake_traits();
		void init_fitness_traits();
		void init_crossover_traits();
		void init_mutation_traits();
		void init_local_search_traits();
		void init_individual(individual_type& idl)
		{
			idl.fitness(0);
			idl.probability(0);
			idl.is_best(e_false_v);
			idl.is_worst(e_false_v);
		}
		void init_cross_p_traits()
		{
			cross_p_traits().init(cross_p());
		}
		void init_mutate_p_traits()
		{
			mutate_p_traits().init(mutate_p());
		}
		void init_stop_traits()
		{
			stop_traits().init(0.00000001);
		}
	/// @}
		
	/// \name Methods
	/// @{
	public:
		// initialize ga_traits
		void init_traits()
		{
			// initialize rmake_traits
			derive().init_rmake_traits();

			// initialize fitness_traits
			derive().init_fitness_traits();

			// initialize cross_p_traits
			derive().init_cross_p_traits();

			// initialize crossover_traits
			derive().init_crossover_traits();

			// initialize mutate_p_traits
			derive().init_mutate_p_traits();

			// initialize mutation_traits
			derive().init_mutation_traits();

			// initialize local_search_traits
			derive().init_local_search_traits();

			// initialize stop_traits
			derive().init_stop_traits();
		}

		/// initialize the given population
		void init_pop(population_type& pop)
		{
			// initialize population
			EXTL_ASSERT(pop.size() > 0);
			pop.generation(0);
			pop.fsum(0);
			pop.fmin(0);
			pop.fmax(0);
			pop.favg(0);

			// initialize individuals
			size_type n = pop.size();
			for (index_type i = 0; i < n; ++i)
			{
				derive().init_individual(pop.individual(i));
			}

			// randomly makes individuals in the population
			derive().rmake(pop);
		}

		/// randomly makes individuals in the population
		void rmake(population_type& pop)
		{
			rmake_traits().rmake(pop);
		}

		/// prepare ga_traits for internal recurrence
		void prepare(population_type& pop)
		{
			// prepare to select
			selection_traits().prepare(pop);

			// prepare cross_p_traits for selection
			cross_p_traits().prepare(pop);

			// prepare mutate_p_traits for selection
			mutate_p_traits().prepare(pop);
		}

		/// select a individual from the population
		individual_type& select(population_type& pop)
		{
			return selection_traits().select(pop, rand());
		}

		/// cross i1 & i2
		void cross(individual_type& i1, individual_type& i2)
		{
			float_type cp = cross_p_traits().cross_p(i1, i2);
			if (rand().fgenerate(0, 1) <= cp)
			{
				crossover_traits().cross(i1, i2);
			}
		}

		/// mutate this individual
		void mutate(individual_type& idl)
		{
			float_type mp = mutate_p_traits().mutate_p(idl);
			if (rand().fgenerate(0, 1) <= mp)
			{
				mutation_traits().mutate(idl);
			}
		}

		/// stopped condition
		bool_type is_stop(population_type const& pop)
		{
			return stop_traits().is_stop(pop);
		}

		// calculate the individual fitness of the population
		void fitness(population_type& pop)
		{
			fitness_traits().fitness(pop);
		}

		/// local_search
		void local_search(population_type& pop)
		{
			local_search_traits().search(pop);
		}

		/// invariance
		bool_type is_valid() const
		{
			if (max_g() <= 0) return e_false_v;
			if (cross_p() <= 0) return e_false_v;
			if (mutate_p() <= 0) return e_false_v;
			if (!crossover_traits().is_valid()) return e_false_v;
			if (!mutation_traits().is_valid()) return e_false_v;
			if (!fitness_traits().is_valid()) return e_false_v;
			if (!rmake_traits().is_valid()) return e_false_v;
			if (!selection_traits().is_valid()) return e_false_v;
			if (!cross_p_traits().is_valid()) return e_false_v;
			if (!mutate_p_traits().is_valid()) return e_false_v;
			if (!stop_traits().is_valid()) return e_false_v;
			if (!local_search_traits().is_valid()) return e_false_v;

			return e_true_v;
		}
	/// @}

	private:
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		derived_type&		derive() 		{ return static_cast<derived_type&>(*this);			}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_TRAITS_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
