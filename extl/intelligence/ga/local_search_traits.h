/* ///////////////////////////////////////////////////////////////////////
 * File:		local_search_traits.h		
 *
 * Created:		08.09.16
 * Updated:		08.11.07
 *
 * Brief: The local_search_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_LOCAL_SEARCH_TRAITS_H
#define EXTL_INTELLIGENCE_GA_LOCAL_SEARCH_TRAITS_H

/*!\file local_search_traits.h
 * \brief The local_search_traits class
 */
#ifndef __cplusplus
#	error local_search_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief no_local_search_traits class
 * 
 * \param Pop The population type
 * \param Rand The random type
 * \param Rt The rmake_traits_type type
 * \param Ft The fitness_traits_type type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		,	typename_param_k Rt
		,	typename_param_k Ft
		>
class no_local_search_traits
{
	/// \name Types
	/// @{
	public:
		typedef Pop													population_type;
		typedef typename_type_k population_type::individual_type	individual_type;
		typedef typename_type_k population_type::size_type			size_type;
		typedef typename_type_k population_type::bool_type			bool_type;
		typedef typename_type_k population_type::float_type			float_type;
		typedef typename_type_k population_type::index_type			index_type;
		typedef typename_type_k population_type::int_type			int_type;
		typedef Rt													rmake_traits_type;
		typedef Ft													fitness_traits_type;
		typedef Rand												random_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init	(	random_type& /*rand*/
					,	rmake_traits_type& /*rt*/
					,	fitness_traits_type& /*ft*/)
		{}

		/// local search
		void search(population_type& /*pop*/)
		{
		}
		/// invariance
		bool is_valid() const
		{
			return e_true_v;
		}
	/// @}
};

/*!\brief hill_climbing_local_search_traits class
 * 
 * \param Pop The population type
 * \param Rand The random type
 * \param Rt The rmake_traits_type type
 * \param Ft The fitness_traits_type type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		,	typename_param_k Rt
		,	typename_param_k Ft
		>
class hill_climbing_local_search_traits
{
	/// \name Types
	/// @{
	public:
		typedef Pop													population_type;
		typedef typename_type_k population_type::individual_type	individual_type;
		typedef typename_type_k population_type::size_type			size_type;
		typedef typename_type_k population_type::bool_type			bool_type;
		typedef typename_type_k population_type::float_type			float_type;
		typedef typename_type_k population_type::index_type			index_type;
		typedef typename_type_k population_type::int_type			int_type;
		typedef Rt													rmake_traits_type;
		typedef Ft													fitness_traits_type;
		typedef Rand												random_type;
	/// @}

	/// \name Members
	/// @{
	private:
		rmake_traits_type*											m_prt;
		fitness_traits_type*										m_pft;
	/// @}

	/// \name Traits
	/// @{
	private:
		rmake_traits_type const&	rmake_traits() const			{ return *m_prt;	}
		rmake_traits_type&			rmake_traits()					{ return *m_prt;	}

		fitness_traits_type const&	fitness_traits() const			{ return *m_pft;	}
		fitness_traits_type&		fitness_traits()				{ return *m_pft;	}
	/// @}

	/// \name Constructors
	/// @{
	public:
		hill_climbing_local_search_traits()
			: m_prt(NULL)
			, m_pft(NULL)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init	(	random_type& /*rand*/
					,	rmake_traits_type& rt
					,	fitness_traits_type& ft)
		{
			m_prt	= &rt;
			m_pft	= &ft;
		}

		/// local search
		void search(population_type& pop)
		{
			EXTL_ASSERT(is_valid());

			// randomly make population
			population_type new_pop = pop;
			rmake_traits().rmake_at_hand(new_pop);
			fitness_traits().fitness(new_pop);

			// search
			size_type pop_n = pop.size();
			for (size_type i = 0; i < pop_n; ++i)
			{
				float_type df = new_pop.individual(i).fitness() - pop.individual(i).fitness();
		
				if (df > 0)
				{
					pop.individual(i) = new_pop.individual(i);
				}
			}
		}
		/// invariance
		bool is_valid() const
		{
			if (NULL == m_prt) return e_false_v;
			if (NULL == m_pft) return e_false_v;

			return e_true_v;
		}
	/// @}
};

/*!\brief simulated_annealing_local_search_traits class
 * 
 * \param Pop The population type
 * \param Rand The random type
 * \param Rt The rmake_traits_type type
 * \param Ft The fitness_traits_type type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		,	typename_param_k Rt
		,	typename_param_k Ft
		>
class simulated_annealing_local_search_traits
{
	/// \name Types
	/// @{
	public:
		typedef Pop													population_type;
		typedef typename_type_k population_type::individual_type	individual_type;
		typedef typename_type_k population_type::size_type			size_type;
		typedef typename_type_k population_type::bool_type			bool_type;
		typedef typename_type_k population_type::float_type			float_type;
		typedef typename_type_k population_type::index_type			index_type;
		typedef typename_type_k population_type::int_type			int_type;
		typedef Rt													rmake_traits_type;
		typedef Ft													fitness_traits_type;
		typedef Rand												random_type;
	/// @}

	/// \name Members
	/// @{
	private:
		random_type*												m_prand;
		rmake_traits_type*											m_prt;
		fitness_traits_type*										m_pft;
		float_type													m_T;
	/// @}

	/// \name Traits
	/// @{
	private:
		random_type const&			rand() const					{ return *m_prand;	}
		random_type&				rand()							{ return *m_prand;	}

		rmake_traits_type const&	rmake_traits() const			{ return *m_prt;	}
		rmake_traits_type&			rmake_traits()					{ return *m_prt;	}

		fitness_traits_type const&	fitness_traits() const			{ return *m_pft;	}
		fitness_traits_type&		fitness_traits()				{ return *m_pft;	}
	/// @}

	/// \name Constructors
	/// @{
	public:
		simulated_annealing_local_search_traits()
			: m_prand(NULL)
			, m_prt(NULL)
			, m_pft(NULL)
			, m_T(0)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init	(	random_type& rand
					,	rmake_traits_type& rt
					,	fitness_traits_type& ft)
		{
			population_type pop(100);
			rt.rmake(pop);
			ft.fitness(pop);
			m_T = 200 * (pop.fmax() - pop.fmin());

			m_prand = &rand;
			m_prt	= &rt;
			m_pft	= &ft;
		}

		/// local search
		void search(population_type& pop)
		{
			EXTL_ASSERT(is_valid());

			// randomly make population
			population_type new_pop = pop;
			rmake_traits().rmake_at_hand(new_pop);
			fitness_traits().fitness(new_pop);

			// search
			size_type pop_n = pop.size();
			for (size_type i = 0; i < pop_n; ++i)
			{
				float_type df = new_pop.individual(i).fitness() - pop.individual(i).fitness();
		
				if (df > 0)
				{
					pop.individual(i) = new_pop.individual(i);
				}
				else
				{
					if (rand().fgenerate(0, 1) < std_exp(df / m_T))
						pop.individual(i) = new_pop.individual(i);
				}
			}

			m_T *= 0.9;
		}
		/// invariance
		bool is_valid() const
		{
			if (NULL == m_prand) return e_false_v;
			if (NULL == m_prt) return e_false_v;
			if (NULL == m_pft) return e_false_v;

			return e_true_v;
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_LOCAL_SEARCH_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
