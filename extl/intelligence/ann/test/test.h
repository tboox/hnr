/* ///////////////////////////////////////////////////////////////////////
 * File:		test.h		
 *
 * Created:		08.12.17		
 * Updated:		08.12.17
 *
 * Brief:		The Container Library Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_TEST_H
#define EXTL_INTELLIGENCE_ANN_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../ann.h"
#include "xor_tester.h"
#include "and_tester.h"
#include "not_tester.h"
#include "sin_tester.h"

#ifdef EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT

#	ifdef EXTL_INTELLIGENCE_ANN_BP_NETWORK_TEST_ENABLE
#		include "bp_network_test.h"
#	endif

#	ifdef EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_TEST_ENABLE
#		include "perceptron_network_test.h"
#	endif

#	ifdef EXTL_INTELLIGENCE_ANN_WGA_NETWORK_TEST_ENABLE
#		include "wga_network_test.h"
#	endif

#	ifdef EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_TEST_ENABLE
#		include "bagging_networks_test.h"
#	endif

#	ifdef EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_NETWORKS_TEST_ENABLE
#		include "ada_boosting_2_networks_test.h"
#		include "ada_boosting_n_networks_test.h"
#	endif

#	ifdef EXTL_INTELLIGENCE_ANN_PCA_NETWORK_TEST_ENABLE
#		include "pca_network_test.h"
#	endif

#	ifdef EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_TEST_ENABLE
#		include "pca_mixed_network_test.h"
#	endif
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

