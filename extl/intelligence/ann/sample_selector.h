/* ///////////////////////////////////////////////////////////////////////
 * File:		sample_selector.h		
 *
 * Created:		09.03.15
 * Updated:		09.03.15
 *
 * Brief:		The sample_selector class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_SAMPLE_SELECTOR_H
#define EXTL_INTELLIGENCE_ANN_SAMPLE_SELECTOR_H

/*!\file sample_selector.h
 * \brief sample_selector class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "bool_sample.h"
#include "float_sample.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief sample_selector
 *
 * \param InN the input demension
 * \param OutN the output demension
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		>
class sample_selector
{
	/// \name Types
	/// @{
	public:
		typedef bool_sample<InN, OutN>	bool_sample_type;
		typedef float_sample<InN, OutN>	float_sample_type;
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_SAMPLE_SELECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
