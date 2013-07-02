/* ///////////////////////////////////////////////////////////////////////
 * File:		individual_base.h		
 *
 * Created:		08.10.07
 * Updated:		08.11.07
 *
 * Brief: The individual_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_INDIVIDUAL_BASE_H
#define EXTL_INTELLIGENCE_GA_INDIVIDUAL_BASE_H

/*!\file individual_base.h
 * \brief The individual_base class
 */
#ifndef __cplusplus
#	error individual_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief individual_base class
 * 
 * \param D The derived type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k D>
class individual_base
{
	/// \name Types
	/// @{
	public:
		typedef D														derived_type;
		typedef individual_base											class_type;
		typedef e_size_t												size_type;
		typedef e_bool_t												bool_type;
		typedef e_float_t												float_type;
		typedef size_type												index_type;
		typedef e_int_t													int_type;
	/// @}

	/// \name Members
	/// @{
	private:
		float_type														m_fitness;
		float_type														m_probability;
		bool_type														m_is_best;
		bool_type														m_is_worst;
	/// @}

	/// \name Constructors
	/// @{
	public:
		individual_base()
			: m_fitness(0)
			, m_probability(0)
			, m_is_best(e_false_v)
			, m_is_worst(e_false_v)
		{}
	/// @}

	/// \name Attributes
	/// @{
	public:
		float_type			fitness() const					{ return m_fitness;				}
		void				fitness(float_type f)			{ m_fitness = f;				}

		float_type			probability() const				{ return m_probability;			}
		void				probability(float_type p)		{ m_probability = p;			}

		bool_type			is_best() const					{ return m_is_best;				}
		void				is_best(bool_type b)			{ m_is_best = b;				}

		bool_type			is_worst() const				{ return m_is_worst;			}
		void				is_worst(bool_type b)			{ m_is_worst = b;				}
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
#endif /* EXTL_INTELLIGENCE_GA_INDIVIDUAL_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
