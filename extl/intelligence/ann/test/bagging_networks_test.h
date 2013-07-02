/* ///////////////////////////////////////////////////////////////////////
 * File:		bagging_networks_test.h		
 *
 * Created:		08.12.27			
 * Updated:		08.12.27
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_TEST_H
#define EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(bagging_networks_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int bagging_networks_test()
{
	/* ///////////////////////////////////////////////////////////////////////
	 * train xor
	 * note: samples size: 4 is so few, maybe no convergence
	 *
	 * 0 0 => 0
	 * 0 1 => 1
	 * 1 0 => 1
	 * 1 1 => 0
	 */
	EXTL_TEST_TRACE(_T("bagging_networks_test: train xor\n"));
	typedef bp_network<2, 1>								xor_bp_type;
	typedef bagging_networks<xor_bp_type>					xor_bagging_type;
	typedef xor_bp_type::layers_type						xor_layers_type;
	xor_bp_type												xor_bp_0(xor_layers_type(5), 0.5);
	xor_bp_type												xor_bp_1(xor_layers_type(6), 0.5);
	xor_bp_type												xor_bp_2(xor_layers_type(7), 0.5);
	xor_bp_type												xor_bp_3(xor_layers_type(8), 0.5);
	xor_bp_type												xor_bp_4(xor_layers_type(9), 0.5);
	xor_bagging_type										xor_bagging(&xor_bp_0, &xor_bp_1, &xor_bp_2, &xor_bp_3, &xor_bp_4);
	EXTL_NS_TEST(xor_tester)<xor_bagging_type>				xtr;
	xtr.test(xor_bagging, 50);
	
	/* ///////////////////////////////////////////////////////////////////////
	 * train not
	 * note: samples size: 4 is so few, maybe no convergence
	 *
	 * 0 0 => 1 1
	 * 0 1 => 1 0
	 * 1 0 => 0 1
	 * 1 1 => 0 0
	 */
	EXTL_TEST_TRACE(_T("bagging_networks_test: train not\n"));
	typedef bp_network<2, 2>								not_bp_type;
	typedef bagging_networks<not_bp_type>					not_bagging_type;
	typedef not_bp_type::layers_type						not_layers_type;
	not_bp_type												not_bp_0(not_layers_type(5), 0.5);
	not_bp_type												not_bp_1(not_layers_type(6), 0.5);
	not_bp_type												not_bp_2(not_layers_type(7), 0.5);
	not_bp_type												not_bp_3(not_layers_type(8), 0.5);
	not_bp_type												not_bp_4(not_layers_type(9), 0.5);
	not_bagging_type										not_bagging(&not_bp_0, &not_bp_1, &not_bp_2, &not_bp_3, &not_bp_4);
	EXTL_NS_TEST(not_tester)<not_bagging_type>				ntr;
	ntr.test(not_bagging, 50);

	/* ///////////////////////////////////////////////////////////////////////
	 * train sin
	 * [0, 2 * pi]
	 */
	EXTL_TEST_TRACE(_T("bagging_networks_test: train sin(0, 2 * pi)\n"));
	typedef bp_network<8, 8>								sin_bp_type;
	typedef bagging_networks<sin_bp_type>					sin_bagging_type;
	typedef sin_bp_type::layers_type						sin_layers_type;
	typedef sin_bp_type::sample_type						sin_sample_type;
	typedef sin_bp_type::samples_type						sin_samples_type;
	sin_bp_type												sin_bp_0(sin_layers_type(5), 0.5);
	sin_bp_type												sin_bp_1(sin_layers_type(6), 0.5);
	sin_bp_type												sin_bp_2(sin_layers_type(7), 0.5);
	sin_bp_type												sin_bp_3(sin_layers_type(8), 0.5);
	sin_bp_type												sin_bp_4(sin_layers_type(9), 0.5);
	sin_bagging_type										sin_bagging(&sin_bp_0, &sin_bp_1, &sin_bp_2, &sin_bp_3, &sin_bp_4);
	EXTL_NS_TEST(sin_tester)<sin_bagging_type>				str;
	str.test(sin_bagging, 200, 10);

	return 0;
}
int bagging_networks_test_ret = bagging_networks_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(bagging_networks_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

