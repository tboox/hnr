/* ///////////////////////////////////////////////////////////////////////
 * File:		standardized_converter.h		
 *
 * Created:		09.04.05	
 * Updated:		09.04.05
 *
 * Brief:		The standardized_converter class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_STANDARDIZED_CONVERTER_H
#define EXTL_INTELLIGENCE_ANN_STANDARDIZED_CONVERTER_H

/*!\file standardized_converter.h
 * \brief standardized_converter class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error standardized_converter.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE


/*!brief standardized_converter
 *
 * \param InN the input demension
 * \param OutN the output demension
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		>
class standardized_converter
{
	/// \name Types
	/// @{
	public:
		typedef standardized_converter												class_type;
		typedef e_size_t															size_type;
		typedef e_bool_t															bool_type;
		typedef e_size_t															index_type;
		typedef e_float_t															float_type;
		typedef typename_type_k vvector_selector<float_type>::vvector_type			vector_type;
		typedef vector_type															floats_type;
		typedef typename_type_k sample_selector<InN, OutN>::float_sample_type		sample_type;
		typedef typename_type_k buffer_selector<sample_type>::large_buffer_type		samples_type;
	/// @}

	/// \name Members
	/// @{
	private:
		vector_type																	m_avgs;
		vector_type																	m_sds;
	/// @}

	/// \name Accessors
	/// @{
	public:
		vector_type&			avgs()			{	return m_avgs;	}
		vector_type const&		avgs() const	{	return m_avgs;	}

		vector_type&			sds()			{	return m_sds;	}
		vector_type const&		sds() const		{	return m_sds;	}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// standardize samples: (x - avg) / sd
		/// \note only convert the input data of samples
		void	convert_input(samples_type& sps) 
		{
			size_type input_n = sample_type::en_input_size;
			// (x - avg) / sd
			index_type i = 0, j = 0;
			size_type sps_n = sps.size();
			EXTL_ASSERT(sps_n > 1);

			// averages
			vector_type avgs(0.0, input_n);
			for (i = 0; i < sps_n; ++i)
				avgs += sps[i].input();
			avgs /= sps_n;

			// standard deviation
			vector_type sds(0.0, input_n);
			for (i = 0; i < sps_n; ++i)
				sds += (sps[i].input() - avgs).dot_pow2();
			sds /= sps_n - 1;

			for (j = 0; j < input_n; ++j)
			{
				sds[j] = xtl_sqrt(sds[j]);
				if (xtl_abs(sds[j]) < 1e-10) sds[j] = 1e-10;
			}

			// standardize
			for (i = 0; i < sps_n; ++i)
				sps[i].input() = (sps[i].input() - avgs).dot_div(sds);

			// updates averages and standard deviation
			m_avgs = avgs;
			m_sds = sds;
		}

		/// standardize sample: (x - avg) / sd
		/// \note only convert the input data of sample
		void	convert_input(sample_type& sp) 
		{
			sp.input() = (sp.input() - m_avgs).dot_div(m_sds);
		}
		/// restore standardized sample: x * sd + avg
		/// \note only convert the input data of sample
		void	restore_input(sample_type& sp) 
		{
			sp.input() = sp.input().dot_mul(m_sds) + m_avgs;
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_STANDARDIZED_CONVERTER_H */
/* //////////////////////////////////////////////////////////////////// */
