/* ///////////////////////////////////////////////////////////////////////
 * File:		afunc_traits.h		
 *
 * Created:		08.12.14		
 * Updated:		08.12.14
 *
 * Brief:		The afunc_traits struct 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_AFUNC_TRAITS_H
#define EXTL_INTELLIGENCE_ANN_AFUNC_TRAITS_H

/*!\file afunc_traits.h
 * \brief afunc_traits struct
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief hreshold_afunc_traits
 *
 * \ingroup extl_group_intelligence
 */
struct hreshold_afunc_traits
{
	/// \name Types
	/// @{
	public:
		typedef hreshold_afunc_traits							class_type;
		typedef e_float_t										float_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// calculate value, range: 0 or 1
		float_type	calc(float_type val)
		{
			return (val >= 0? 1 : 0);
		}
		/// calculate first order derivative 
		float_type	calc_1d(float_type /*val*/)
		{
			return 0;
		}
	/// @}
};
/*!brief sgn_afunc_traits
 *
 * \ingroup extl_group_intelligence
 */
struct sgn_afunc_traits
{
	/// \name Types
	/// @{
	public:
		typedef sgn_afunc_traits								class_type;
		typedef e_float_t										float_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/// calculate value, range: -1 or 1
		float_type	calc(float_type val)
		{
			return (val >= 0? 1 : -1);
		}
		/// calculate first order derivative 
		float_type	calc_1d(float_type /*val*/)
		{
			return 0;
		}
	/// @}
};
/*!brief piecewise_linear_afunc_traits
 *
 * \ingroup extl_group_intelligence
 */
struct piecewise_linear_afunc_traits
{
	/// \name Types
	/// @{
	public:
		typedef piecewise_linear_afunc_traits					class_type;
		typedef e_float_t										float_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		/*!calculate value, range: [0, 1]
		 * <pre>
		 * f(x) = 1					x >= 1
		 * f(x) = 0.5 * (1 + x)     -1 < x & x < 1
		 * f(x) = 0					x <= -1
		 * </pre>
		 */
		float_type	calc(float_type val)
		{
			return ((val >= 1)? 1 : (val <= -1? 0 : ((1 + val) / 2)));
		}
		/*!calculate first order derivative 
		 * <pre>
		 * f(x) = 0					x >= 1
		 * f(x) = 0.5			    -1 < x & x < 1
		 * f(x) = 0					x <= -1
		 * </pre>
		 */
		float_type	calc_1d(float_type val)
		{
			return ((val >= 1)? 0 : (val <= -1? 0 : 0.5));
		}
	/// @}
};

/*!brief sigmoid_afunc_traits
 *
 * \ingroup extl_group_intelligence
 */
struct sigmoid_afunc_traits
{
	/// \name Types
	/// @{
	public:
		typedef sigmoid_afunc_traits							class_type;
		typedef e_float_t										float_type;
	/// @}

	/// \name Members
	/// @{
	private:
		float_type												m_a;
	/// @}

	/// \name Methods
	/// @{
	public:
		explicit_k sigmoid_afunc_traits(float_type a = 1)	// slope
			: m_a(a)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		/*!calculate value, range: [0, 1]
		 * f(x) = 1 / (1 + exp(-ax))
		 */
		float_type calc(float_type val)
		{
			return (1 / (1 + std_exp(m_a * val * -1)));
		}
		/*!calculate first order derivative 
		 * f(x) = ep / (1 + exp(-ax))^2
		 */
		float_type	calc_1d(float_type val)
		{
			float_type ep = std_exp(m_a * val * -1);
			return (ep / ((1 + ep) * (1 + ep)));
		}
	/// @}
};

/*!brief tanh_sigmoid_afunc_traits
 *
 * \ingroup extl_group_intelligence
 */
struct tanh_sigmoid_afunc_traits
{
	/// \name Types
	/// @{
	public:
		typedef tanh_sigmoid_afunc_traits						class_type;
		typedef e_float_t										float_type;
	/// @}

	/// \name Members
	/// @{
	private:
		float_type												m_a;
		float_type												m_b;
	/// @}

	/// \name Methods
	/// @{
	public:
		explicit_k tanh_sigmoid_afunc_traits(float_type a = 1, float_type b = 1)
			: m_a(a), m_b(b)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		/*!calculate value, range: [-a, a]
		 * f(x) = atanh(bx) = a * (1 - exp(-bx)) / (1 + exp(-bx))
		 *
		 * a = d(real_ouptput) - e(error)
		 * so: d = 1 & e = 0 => a = 1
		 * so: d = 0 & e = 0 => a = 0
		 */
		float_type	calc(float_type val)
		{
			float_type ep = std_exp(m_b * val * -1);
			return (m_a * (1 - ep) / (1 + ep));
		}
		/*!calculate first order derivative 
		 * f(x) = exp(x) / (1 + exp(x)) + (1 - exp(x)) * exp(x) / (1 + exp(x))^2
		 */
		float_type	calc_1d(float_type val)
		{
			float_type ep = std_exp(m_b * val * -1);
			float_type lhs = ep / (1 + ep);
			float_type rhs = ((1 - ep) * ep) / ((1 + ep) * (1 + ep));
			return (m_a * (lhs + rhs));
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_AFUNC_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
