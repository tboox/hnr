/* ///////////////////////////////////////////////////////////////////////
 * File:		pca_mixed_network_test.h		
 *
 * Created:		08.12.17			
 * Updated:		08.12.17
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_TEST_H
#define EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(pca_mixed_network_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int pca_mixed_network_test()
{
	/* ///////////////////////////////////////////////////////////////////////
	 * train xor
	 *
	 * 0 0 => 0
	 * 0 1 => 1
	 * 1 0 => 1
	 * 1 1 => 0
	 */
	EXTL_TEST_TRACE(_T("pca_mixed_network_test: train xor\n"));
	typedef bp_network	<	2, 1
						,	sample_selector<2, 1>::float_sample_type
						>										xor_bp_type;
	typedef xor_bp_type::layers_type							xor_layers_type;
	typedef ghia_network<2, 2>									xor_pca_type;
	typedef pca_mixed_network<xor_pca_type, xor_bp_type>		xor_pca_mixed_type;
	xor_pca_mixed_type											xor_pca_mixed(xor_pca_type(), xor_bp_type(xor_layers_type(10), 0.5));
	EXTL_NS_TEST(xor_tester)<xor_pca_mixed_type>				xtr;
	xtr.test(xor_pca_mixed, 50);
	
	/* ///////////////////////////////////////////////////////////////////////
	 * train not
	 *
	 * 0 0 => 1 1
	 * 0 1 => 1 0
	 * 1 0 => 0 1
	 * 1 1 => 0 0
	 */
	EXTL_TEST_TRACE(_T("pca_mixed_network_test: train not\n"));
	typedef bp_network	<	2, 2
						,	sample_selector<2, 2>::float_sample_type
						>										not_bp_type;
	typedef not_bp_type::layers_type							not_layers_type;
	typedef ghia_network<2, 2>									not_pca_type;
	typedef pca_mixed_network<not_pca_type, not_bp_type>		not_pca_mixed_type;
	not_pca_mixed_type											not_pca_mixed(not_pca_type(), not_bp_type(not_layers_type(10), 0.5));
	EXTL_NS_TEST(not_tester)<not_pca_mixed_type>				ntr;
	ntr.test(not_pca_mixed, 50);

	/* ///////////////////////////////////////////////////////////////////////
	 * train sin
	 * [0, 2 * pi]
	 */
	EXTL_TEST_TRACE(_T("pca_mixed_network_test: train sin(0, 2 * pi)\n"));
	typedef bp_network	<	4, 8
						,	sample_selector<4, 8>::float_sample_type
						>										sin_bp_type;
	typedef sin_bp_type::layers_type							sin_layers_type;
	typedef ghia_network<8, 4>									sin_pca_type;
	typedef pca_mixed_network<sin_pca_type, sin_bp_type>		sin_pca_mixed_type;
	sin_pca_mixed_type											sin_pca_mixed(sin_pca_type(), sin_bp_type(sin_layers_type(10), 0.5));
	EXTL_NS_TEST(sin_tester)<sin_pca_mixed_type>				str;

	clock_counter t;
	t.begin();
	str.test(sin_pca_mixed, 100);
	t.end();
	printf("%d\n", t.ms());

	return 0;
}
int pca_mixed_network_test_ret = pca_mixed_network_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(pca_mixed_network_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

