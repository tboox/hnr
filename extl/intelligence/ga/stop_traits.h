/* ///////////////////////////////////////////////////////////////////////
 * File:		stop_traits.h		
 *
 * Created:		08.09.23
 * Updated:		08.11.07
 *
 * Brief: The stop_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_STOP_TRAITS_H
#define EXTL_INTELLIGENCE_GA_STOP_TRAITS_H

/*!\file stop_traits.h
 * \brief The stop_traits class
 */
#ifndef __cplusplus
#	error stop_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief internal_minimal_residual_stop_traits class
 * 
 * \param Pop The population type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Pop>
struct internal_minimal_residual_stop_traits
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
	/// @}

	/// \name Members
	/// @{
	private:
		float_type													m_precision;
	/// @}

	/// \name Constructors
	/// @{
	public:
		internal_minimal_residual_stop_traits()
			: m_precision(0)
		{
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// Initialization
		void init(float_type precision)
		{
			m_precision = precision;
		}
		/// Returns \true if have generated the best individual
		/// Would be stoped if the difference of the individual fitness is too small in the population
		bool_type is_stop(population_type const& pop)
		{
			size_type individual_n = pop.size();
			float_type r = 0;
			for (size_type i = 0; i < individual_n; ++i)
			{
				r += (pop.individual(i).fitness() - pop.favg()) * (pop.individual(i).fitness() - pop.favg());
			}

			r /= individual_n * individual_n;

			if (r < m_precision) return e_true_v;
			else return e_false_v;
		}
	/// @}
};

/*!\brief internal_minimal_residual_stop_traits class
 * 
 * \param Pop The population type
 * \param N the number of the generation of the population
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	e_size_t N 
		>
struct external_minimal_residual_stop_traits
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
		typedef basic_queue	<	float_type
							,	fixed_reque	<	float_type
												,	N
												,	stack_buffer<	float_type
																,	N
																,	typename_type_k memory_traits_selector<float_type>::memory_traits_type
																>				
												>			
							>										queue_type;
		typedef typename_type_k queue_type::const_iterator			queue_iterator;
	/// @}

	/// \name Members
	/// @{
	private:
		float_type													m_precision;
		queue_type													m_qfitness;
	/// @}

	/// \name Constructors
	/// @{
	public:
		external_minimal_residual_stop_traits()
			: m_precision(0), m_qfitness()
		{
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(float_type precision)
		{
			m_precision = precision;
			m_qfitness.clear();
		}
		/// Returns \true if have generated the best individual
		/// Would be stoped if the difference of the best individual fitness is too small in N generation
		bool_type is_stop(population_type const& pop)
		{
			EXTL_ASSERT(is_valid());
			EXTL_ASSERT(N == m_qfitness.max_size());
			EXTL_ASSERT(m_qfitness.size() <= m_qfitness.max_size());

			// updates the queue
			if (m_qfitness.size() < m_qfitness.max_size())
			{
				m_qfitness.push(pop.best().fitness());
			}
			else 
			{
				m_qfitness.pop();
				m_qfitness.push(pop.best().fitness());
			}

			// stats
			EXTL_ASSERT(m_qfitness.size() > 0);
			queue_iterator p = m_qfitness.begin();
			float_type favg = *p;
			float_type fmin = favg;
			float_type fmax = favg;
			float_type fsum = 0;
			for (; p != m_qfitness.end(); ++p)
			{
				fmin = (*p < fmin)? *p : fmin;
				fmax = (*p > fmax)? *p : fmax;
				fsum += *p;
			}
			favg = fsum / m_qfitness.size();

			// calcuate the minimal residual of the fitnesses of the best individuals in N generation
			float_type r = 0;
			for (p = m_qfitness.begin(); p != m_qfitness.end(); ++p)
			{
				r += (*p - favg) * (*p - favg);
			}
			r /= m_qfitness.size() * m_qfitness.size();

			if (m_qfitness.size() == m_qfitness.max_size() && r < m_precision) return e_true_v;
			else return e_false_v;
		}
		/// invariance
		bool_type is_valid() const
		{
			if (m_precision <= 0) return e_false_v;
			return e_true_v;
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_STOP_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
