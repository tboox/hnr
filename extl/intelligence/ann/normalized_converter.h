/* ///////////////////////////////////////////////////////////////////////
 * File:		normalized_converter.h		
 *
 * Created:		09.04.05	
 * Updated:		09.04.05
 *
 * Brief:		The normalized_converter class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_NORMALIZED_CONVERTER_H
#define EXTL_INTELLIGENCE_ANN_NORMALIZED_CONVERTER_H

/*!\file normalized_converter.h
 * \brief normalized_converter class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error normalized_converter.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE


/*!brief normalized_converter
 *
 * \param InN the input demension
 * \param OutN the output demension
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		>
class normalized_converter
{
	/// \name Types
	/// @{
	public:
		typedef normalized_converter												class_type;
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
		vector_type																	m_maxs;
		vector_type																	m_mins;
	/// @}

	/// \name Accessors
	/// @{
	public:
		vector_type&			maxs()			{	return m_maxs;	}
		vector_type const&		maxs() const	{	return m_maxs;	}

		vector_type&			mins()			{	return m_mins;	}
		vector_type const&		mins() const	{	return m_mins;	}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// normalize samples [-0.9, 0.9]: 1.8 * (x - min) / (max - min) - 0.9
		/// \note only convert the input data of samples
		void	convert_input(samples_type& sps) 
		{
			size_type input_n = sample_type::en_input_size;

			// [-0.9, 0.9]
			index_type i = 0, j = 0;
			size_type sps_n = sps.size();
			EXTL_ASSERT(sps_n > 1);

			// m_mins & m_maxs
			m_mins = sps[0].input();
			m_maxs = sps[0].input();
			for (i = 0; i < sps_n; ++i)
			{
				for (j = 0; j < input_n; ++j)
				{
					m_mins[j] = sps[i].get_finput(j) < m_mins[j]? sps[i].get_finput(j) : m_mins[j];
					m_maxs[j] = sps[i].get_finput(j) > m_maxs[j]? sps[i].get_finput(j) : m_maxs[j];
				}
			}

			// normalize
			for (i = 0; i < sps_n; ++i)
			{
				for (j = 0; j < input_n; ++j)
				{
					double dt = m_maxs[j] - m_mins[j];
					if (xtl_abs(dt) < 1e-10) dt = 1e-10;
					sps[i].set_finput(j, (1.8 * (sps[i].get_finput(j) - m_mins[j]) / dt) - 0.9);
				}
			}
		}

		/// normalize sample [-0.9, 0.9]: 1.8 * (x - min) / (max - min) - 0.9
		/// \note only convert the input data of sample
		void	convert_input(sample_type& sp) 
		{
			size_type input_n = sample_type::en_input_size;
			for (index_type i = 0; i < input_n; ++i)
			{
				double dt = m_maxs[i] - m_mins[i];
				if (xtl_abs(dt) < 1e-10) dt = 1e-10;
				sp.set_finput(i, (1.8 * (sp.get_finput(i) - m_mins[i]) / dt) - 0.9);
			}
		}
		/// restore normalized sample: (x + 0.9) * (max - min) / 1.8 + min
		/// \note only convert the input data of sample
		void	restore_input(sample_type& sp) 
		{
			size_type input_n = sample_type::en_input_size;
			for (index_type i = 0; i < input_n; ++i)
			{
				double dt = m_maxs[i] - m_mins[i];
				sp.set_finput(i, ((sp.get_finput(i) + 0.9) * dt / 1.8) + m_mins[i]);
			}
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_NORMALIZED_CONVERTER_H */
/* //////////////////////////////////////////////////////////////////// */
