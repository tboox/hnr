/* ///////////////////////////////////////////////////////////////////////
 * File:		xor_tester.h		
 *
 * Created:		08.12.17			
 * Updated:		08.12.17
 *
 * Brief:		Unit-testing tester
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_TEST_XOR_TESTER_H
#define EXTL_INTELLIGENCE_ANN_TEST_XOR_TESTER_H

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::test namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_BEGIN_NAMESPACE

/* xor_tester
 *
 * 0 0 => 0
 * 0 1 => 1
 * 1 0 => 1
 * 1 1 => 0
 */
template<typename_param_k Net>
struct xor_tester
{
	public:
		typedef Net												network_type;
		typedef typename_type_k network_type::sample_type		sample_type;
		typedef typename_type_k network_type::samples_type		samples_type;
		typedef typename_type_k network_type::size_type			size_type;
		typedef typename_type_k network_type::float_type		float_type;
		typedef basic_network_validator<network_type>			validator_type;

	public:
		void test(network_type& network, size_type n)
		{
			sample_type											sp;
			samples_type										sps(4);
			validator_type										validator;

			sps[0].binput("00");
			sps[0].breal("0");

			sps[1].binput("01");
			sps[1].breal("1");

			sps[2].binput("10");
			sps[2].breal("1");

			sps[3].binput("11");
			sps[3].breal("0");

			network.train(sps, n);
			
			sp.binput("00");
			network.run(sp);
			EXTL_TEST_TRACE(_T("input:%d %d output:%d foutput:%f"), sp.get_binput(0), sp.get_binput(1), sp.get_boutput(0), network.foutput(0));

			sp.binput("01");
			network.run(sp);
			EXTL_TEST_TRACE(_T("input:%d %d output:%d foutput:%f"), sp.get_binput(0), sp.get_binput(1), sp.get_boutput(0), network.foutput(0));

			sp.binput("10");
			network.run(sp);
			EXTL_TEST_TRACE(_T("input:%d %d output:%d foutput:%f"), sp.get_binput(0), sp.get_binput(1), sp.get_boutput(0), network.foutput(0));

			sp.binput("11");
			network.run(sp);
			EXTL_TEST_TRACE(_T("input:%d %d output:%d foutput:%f"), sp.get_binput(0), sp.get_binput(1), sp.get_boutput(0), network.foutput(0));
			
			validator.validate(network, sps);
			EXTL_TEST_TRACE(_T("n:%d mse:%f erate:%f\n"), sps.size() * n, validator.mse(), validator.erate());
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::test namespace 
 */
EXTL_TEST_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_TEST_XOR_TESTER_H */
/* //////////////////////////////////////////////////////////////////// */

