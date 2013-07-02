/* ///////////////////////////////////////////////////////////////////////
 * File:		null_converter.h		
 *
 * Created:		09.04.05	
 * Updated:		09.04.05
 *
 * Brief:		The null_converter class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_NULL_CONVERTER_H
#define EXTL_INTELLIGENCE_ANN_NULL_CONVERTER_H

/*!\file null_converter.h
 * \brief null_converter class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error null_converter.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE


/*!brief null_converter
 *
 * \param InN the input demension
 * \param OutN the output demension
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		>
class null_converter
{
	/// \name Types
	/// @{
	public:
		typedef null_converter														class_type;
		typedef e_size_t															size_type;
		typedef e_bool_t															bool_type;
		typedef e_size_t															index_type;
		typedef e_float_t															float_type;
		typedef typename_type_k vvector_selector<float_type>::vvector_type			vector_type;
		typedef vector_type															floats_type;
		typedef typename_type_k sample_selector<InN, OutN>::float_sample_type		sample_type;
		typedef typename_type_k buffer_selector<sample_type>::large_buffer_type		samples_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		void	convert_input(samples_type& /*sps*/) {}
		void	convert_input(sample_type& /*sp*/) {}
		void	restore_input(sample_type& /*sp*/) {}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_NULL_CONVERTER_H */
/* //////////////////////////////////////////////////////////////////// */
