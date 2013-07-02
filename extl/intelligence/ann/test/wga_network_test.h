/* ///////////////////////////////////////////////////////////////////////
 * File:		wga_network_test.h		
 *
 * Created:		08.12.17			
 * Updated:		09.01.13
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_WGA_NETWORK_TEST_H
#define EXTL_INTELLIGENCE_ANN_WGA_NETWORK_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(wga_network_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int wga_network_test()
{
	/* ///////////////////////////////////////////////////////////////////////
	 * train xor
	 *
	 * 0 0 => 0
	 * 0 1 => 1
	 * 1 0 => 1
	 * 1 1 => 0
	 */
	EXTL_TEST_TRACE(_T("wga_network_test: train xor\n"));
	typedef bp_network<2, 1>								xor_bp_type;
	typedef xor_bp_type::layers_type						xor_layers_type;
	xor_bp_type												xor_bp(xor_layers_type(10), 0.5);
	EXTL_NS_TEST(xor_tester)<wga_network<xor_bp_type> >		xtr;
	wga_network<xor_bp_type>								xga(xor_bp);
	xtr.test(xga, 20);
	
	/* ///////////////////////////////////////////////////////////////////////
	 * train not
	 *
	 * 0 0 => 1 1
	 * 0 1 => 1 0
	 * 1 0 => 0 1
	 * 1 1 => 0 0
	 */
	EXTL_TEST_TRACE(_T("wga_network_test: train not\n"));
	typedef bp_network<2, 2>								not_bp_type;
	typedef not_bp_type::layers_type						not_layers_type;
	typedef not_bp_type::sample_type						not_sample_type;
	typedef not_bp_type::samples_type						not_samples_type;
	not_bp_type												not_bp(not_layers_type(10), 0.5);
	EXTL_NS_TEST(not_tester)<wga_network<not_bp_type> >		ntr;
	wga_network<not_bp_type>								nga(not_bp);
	ntr.test(nga, 20);

	/* ///////////////////////////////////////////////////////////////////////
	 * train sin
	 * [0, 2 * pi]
	 */
	EXTL_TEST_TRACE(_T("wga_network_test: train sin(0, 2 * pi)\n"));
	typedef bp_network<8, 8>								sin_bp_type;
	typedef sin_bp_type::layers_type						sin_layers_type;
	typedef sin_bp_type::sample_type						sin_sample_type;
	typedef sin_bp_type::samples_type						sin_samples_type;
	sin_bp_type												sin_bp(sin_layers_type(10), 0.5);
	EXTL_NS_TEST(sin_tester)<wga_network<sin_bp_type> >		str;
	wga_network<sin_bp_type>								sga(sin_bp);
	str.test(sga, 100);

	return 0;
}
int wga_network_test_ret = wga_network_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(wga_network_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_WGA_NETWORK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

