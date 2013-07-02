/* ///////////////////////////////////////////////////////////////////////
 * File:		ada_boosting_n_networks_test.h		
 *
 * Created:		09.06.07			
 * Updated:		09.06.07
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_N_NETWORKS_TEST_H
#define EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_N_NETWORKS_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(ada_boosting_n_networks_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int ada_boosting_n_networks_test()
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
	/*EXTL_TEST_TRACE(_T("ada_boosting_n_networks_test: train xor\n"));
	typedef bp_network<2, 1>								xor_bp_type;
	typedef ada_boosting_n_networks<xor_bp_type>				xor_ada_boosting_type;
	typedef xor_bp_type::layers_type						xor_layers_type;
	xor_bp_type												xor_bp_0(xor_layers_type(2), 0.2);
	xor_bp_type												xor_bp_1(xor_layers_type(3), 0.3);
	xor_bp_type												xor_bp_2(xor_layers_type(4), 0.4);
	xor_bp_type												xor_bp_3(xor_layers_type(5), 0.5);
	xor_bp_type												xor_bp_4(xor_layers_type(6), 0.6);
	xor_ada_boosting_type									xor_ada_boosting(&xor_bp_0, &xor_bp_1, &xor_bp_2, &xor_bp_3, &xor_bp_4);
	EXTL_NS_TEST(xor_tester)<xor_ada_boosting_type>			xtr;
	xtr.test(xor_ada_boosting, 50);*/
	
	/* ///////////////////////////////////////////////////////////////////////
	 * train not
	 * note: samples size: 4 is so few, maybe no convergence
	 *
	 * 0 0 => 1 1
	 * 0 1 => 1 0
	 * 1 0 => 0 1
	 * 1 1 => 0 0
	 */
	EXTL_TEST_TRACE(_T("ada_boosting_n_networks_test: train not\n"));
	typedef bp_network<2, 2>								not_bp_type;
	typedef ada_boosting_n_networks<not_bp_type>				not_ada_boosting_type;
	typedef not_bp_type::layers_type						not_layers_type;
	not_ada_boosting_type									not_ada_boosting;

	for (i = 0; i < 10; ++i) 
		not_ada_boosting.push_back(not_bp_type(not_layers_type(10), 0.5));

	EXTL_NS_TEST(not_tester)<not_ada_boosting_type>			ntr;
	ntr.test(not_ada_boosting, 50);

	/* ///////////////////////////////////////////////////////////////////////
	 * train sin
	 * [0, 2 * pi]
	 */
	EXTL_TEST_TRACE(_T("ada_boosting_n_networks_test: train sin(0, 2 * pi)\n"));
	typedef bp_network<8, 8>								sin_bp_type;
	typedef ada_boosting_n_networks<sin_bp_type>			sin_ada_boosting_type;
	typedef sin_bp_type::layers_type						sin_layers_type;
	typedef sin_bp_type::sample_type						sin_sample_type;
	typedef sin_bp_type::samples_type						sin_samples_type;
	sin_ada_boosting_type									sin_ada_boosting;
	
	// now exists VC6.0 scoped_buffer<> bug
	for (i = 0; i < 10; ++i) 
		sin_ada_boosting.push_back(sin_bp_type(sin_layers_type(10), 0.5));

	EXTL_NS_TEST(sin_tester)<sin_ada_boosting_type>			str;
	str.test(sin_ada_boosting, 200, 16);

	return 0;
}
int ada_boosting_n_networks_test_ret = ada_boosting_n_networks_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(ada_boosting_n_networks_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_N_NETWORKS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

