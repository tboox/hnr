/* ///////////////////////////////////////////////////////////////////////
 * File:		perceptron_network_test.h		
 *
 * Created:		08.12.17			
 * Updated:		08.12.17
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_TEST_H
#define EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(perceptron_network_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int perceptron_network_test()
{
	/* ///////////////////////////////////////////////////////////////////////
	 * train and
	 *
	 * 0 0 => 0
	 * 0 1 => 0
	 * 1 0 => 0
	 * 1 1 => 1
	 */
	EXTL_TEST_TRACE(_T("perceptron_network_test: train and\n"));
	typedef perceptron_network<2, 1>						and_perceptron_type;
	typedef and_perceptron_type::layers_type				and_layers_type;
	and_perceptron_type										and_perceptron(10, 0.5);
	EXTL_NS_TEST(and_tester)<and_perceptron_type>			atr;
	atr.test(and_perceptron, 1000);
	
	return 0;
}
int perceptron_network_test_ret = perceptron_network_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(perceptron_network_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

