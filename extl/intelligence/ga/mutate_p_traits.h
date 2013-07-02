/* ///////////////////////////////////////////////////////////////////////
 * File:		mutate_p_traits.h		
 *
 * Created:		08.09.16
 * Updated:		08.11.07
 *
 * Brief: The mutate_p_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_MUTATE_P_TRAITS_H
#define EXTL_INTELLIGENCE_GA_MUTATE_P_TRAITS_H

/*!\file mutate_p_traits.h
 * \brief The mutate_p_traits class
 */
#ifndef __cplusplus
#	error mutate_p_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief simple_mutate_p_traits class
 * 
 * \param Pop The population type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Pop>
class simple_mutate_p_traits
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
		float_type													m_mp;
	/// @}

	/// \name Constructors
	/// @{
	public:
		simple_mutate_p_traits()
			: m_mp(0)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(float_type mp)
		{
			m_mp = mp;
		}
		/// prepare
		void prepare(population_type const& /*pop*/)
		{}
		/// need not modifiy the probability of mutation 
		float_type mutate_p(individual_type const& /*idl*/)
		{
			EXTL_ASSERT(is_valid());
			return m_mp;
		}
		/// invariance
		bool_type is_valid() const
		{
			if (m_mp <= 0) return e_false_v;
			return e_true_v;
		}
	/// @}
};

/*!\brief adaptive_mutate_p_traits class
 * 
 * \param Pop The population type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Pop>
class adaptive_mutate_p_traits
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
		float_type													m_mp1;
		float_type													m_mp2;
		float_type													m_mdp;
		float_type													m_fmax;
		float_type													m_favg;
	/// @}

	/// \name Constructors
	/// @{
	public:
		adaptive_mutate_p_traits()
			: m_mp1(0), m_mp2(0), m_mdp(0), m_fmax(0), m_favg(0)
		{
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(float_type /* mutate_p */ = 0)
		{
			m_mp1 = 0.1;
			m_mp2 = 0.001;
			m_mdp = m_mp1 - m_mp2;
		}
		/// prepare
		void prepare(population_type const& pop)
		{
			m_fmax = pop.fmax();
			m_favg = pop.favg();
		}
		/// adaptively adjust the probability of mutation
		float_type mutate_p(individual_type const& idl)
		{
			EXTL_ASSERT(is_valid());

			float_type df = m_fmax - m_favg;
			if (df <= 0) return 0;

			float_type mp = idl.fitness() < m_favg? m_mp1 : (m_mp1 - m_mdp * (m_fmax - idl.fitness()) / df);
		
			return mp;
		}
		/// invariance
		bool_type is_valid() const
		{
			if (m_mp1 == 0) return e_false_v;
			if (m_mp2 == 0) return e_false_v;
			if (m_mdp == 0) return e_false_v;

			return e_true_v;
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_MUTATE_P_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
