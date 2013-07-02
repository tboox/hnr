/* ///////////////////////////////////////////////////////////////////////
 * File:		cross_p_traits.h		
 *
 * Created:		08.09.16
 * Updated:		08.11.07
 *
 * Brief: The Crossover Probability Tratis
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_CROSS_P_TRAITS_H
#define EXTL_INTELLIGENCE_GA_CROSS_P_TRAITS_H

/*!\file cross_p_traits.h
 * \brief The cross_p_traits class
 */
#ifndef __cplusplus
#	error cross_p_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief simple_cross_p_traits class
 * 
 * \param Pop The population type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Pop>
class simple_cross_p_traits
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
		float_type													m_cp;
	/// @}

	/// \name Constructors
	/// @{
	public:
		simple_cross_p_traits()
			: m_cp(0)
		{}
	/// @}

	/// \name Members
	/// @{
	public:
		/// initialize the traits
		void init(float_type cp)
		{
			m_cp = cp;
		}
		/// prepare
		void prepare(population_type const& /*pop*/)
		{}
		/// need not modifiy the probability of crossover 
		float_type cross_p(individual_type const& /*p1*/, individual_type const& /*p2*/)
		{
			EXTL_ASSERT(is_valid());
			return m_cp;
		}
		/// invariance
		bool_type is_valid() const
		{
			if (m_cp <= 0) return e_false_v;
			return e_true_v;
		}
	/// @}
};

/*!\brief adaptive_cross_p_traits class
 * 
 * \param Pop The population type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Pop>
class adaptive_cross_p_traits
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
		float_type													m_cp1;
		float_type													m_cp2;
		float_type													m_cdp;
		float_type													m_fmax;
		float_type													m_favg;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		adaptive_cross_p_traits()
			: m_cp1(0), m_cp2(0), m_cdp(0), m_fmax(0), m_favg(0)
		{}
	/// @}

	/// \name Members
	/// @{
	public:
		/// initialize the traits
		void init(float_type /* cross_p */ = 0)
		{
			m_cp1 = 0.9;
			m_cp2 = 0.6;
			m_cdp = m_cp1 - m_cp2;
		}
		/// prepare
		void prepare(population_type const& pop)
		{
			m_fmax = pop.fmax();
			m_favg = pop.favg();
		}
		/// adaptively adjust the probability of crossover
		float_type cross_p(individual_type const& p1, individual_type const& p2)
		{
			EXTL_ASSERT(is_valid());

			float_type df = m_fmax - m_favg;
			if (df <= 0) return 0;

			float_type cf = xtl_max(p1.fitness(), p2.fitness());
			float_type cp = cf < m_favg? m_cp1 : (m_cp1 - m_cdp * (cf - m_favg) / df);
		
			return cp;
		}
		/// invariance
		bool_type is_valid() const
		{
			if (m_cp1 == 0) return e_false_v;
			if (m_cp2 == 0) return e_false_v;
			if (m_cdp == 0) return e_false_v;

			return e_true_v;
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_CROSS_P_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
