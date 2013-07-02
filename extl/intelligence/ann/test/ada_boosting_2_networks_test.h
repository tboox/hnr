/* ///////////////////////////////////////////////////////////////////////
 * File:		ada_boosting_2_networks_test.h		
 *
 * Created:		08.12.27			
 * Updated:		09.06.07
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_2_NETWORKS_TEST_H
#define EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_2_NETWORKS_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(ada_boosting_2_networks_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int ada_boosting_2_networks_test()
{
	e_size_t i;
	/* ///////////////////////////////////////////////////////////////////////
	 * train xor
	 * note: samples size: 4 is so few, maybe no convergence
	 *
	 * 0 0 => 0
	 * 0 1 => 1
	 * 1 0 => 1
	 * 1 1 => 0
	 */
	EXTL_TEST_TRACE(_T("ada_boosting_2_networks_test: train xor\n"));
	typedef bp_network<2, 1>								xor_bp_type;
	typedef ada_boosting_2_networks<xor_bp_type>			xor_ada_boosting_type;
	typedef xor_bp_type::layers_type						xor_layers_type;
	xor_ada_boosting_type									xor_ada_boosting;
	for (i = 0; i < 10; ++i) xor_ada_boosting.push_back(xor_bp_type(xor_layers_type(10), 0.5));
	EXTL_NS_TEST(xor_tester)<xor_ada_boosting_type>			xtr;
	xtr.test(xor_ada_boosting, 50);
	

	return 0;
}
int ada_boosting_2_networks_test_ret = ada_boosting_2_networks_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(ada_boosting_2_networks_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_2_NETWORKS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

