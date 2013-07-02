/* ///////////////////////////////////////////////////////////////////////
 * File:		sin_tester.h		
 *
 * Created:		08.12.17			
 * Updated:		08.12.17
 *
 * Brief:		Unit-testing tester
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_ANN_TEST_SIN_TESTER_H
#define EXTL_INTELLIGENCE_ANN_TEST_SIN_TESTER_H

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::test namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_BEGIN_NAMESPACE

/* sin_tester
 */
template<typename_param_k Net>
struct sin_tester
{
	public:
		typedef Net														network_type;
		typedef typename_type_k network_type::sample_type				sample_type;
		typedef typename_type_k network_type::samples_type				samples_type;
		typedef typename_type_k network_type::size_type					size_type;
		typedef typename_type_k network_type::index_type				index_type;
		typedef typename_type_k network_type::float_type				float_type;
		typedef basic_network_validator<network_type>					validator_type;
		typedef kfold_cross_validator<network_type, validator_type>		cross_validator_type;

	public:
		float_type input_i2f(index_type i)
		{
			// [0, 2 * pi]
			return (0 + i * 2 * 3.14159265358 / 256);
		}
		index_type input_f2i(float_type val)
		{
			// [0, 2 * pi]
			index_type idx = xtl_round45((val - 0) * 256 / (2 * 3.14159265358));
			return idx > 255? 255 : idx;
		}

		float_type output_i2f(index_type i)
		{
			// [-1, 1]
			return (-1 + float_type(i) * 2 / 256);
		}
		index_type output_f2i(float_type val)
		{
			// [-1, 1]
			index_type idx = xtl_round45((val + 1) * 256 / 2);
			return idx > 255? 255 : idx;
		}

		void test(network_type& network, size_type n, size_type sps_n = 10)
		{
			sample_type											sp;
			samples_type										sps(sps_n);
			validator_type										validator;
			cross_validator_type								cross_validator;
	
			size_type i;
			EXTL_TEST_TRACE(_T("\nbefore training"));
			for (i = 0; i < sps_n; ++i)
			{
				sps[i].dinput(i);
				sps[i].dreal(output_f2i(std_sin(input_i2f(i))));

				EXTL_TEST_TRACE(_T("sps: input:%f output:%f"), input_i2f(sps[i].dinput()), output_i2f(sps[i].dreal()));			
			}

			network.train(sps, n);

			EXTL_TEST_TRACE(_T("\nafter training"));
			for (i = 0; i < sps_n; ++i)
			{
				sp.dinput(i);
				network.run(sp);
				EXTL_TEST_TRACE(_T("sps: input:%f output:%f"), input_i2f(sp.dinput()), output_i2f(sp.doutput()));			
			}

			validator.validate(network, sps);
			EXTL_TEST_TRACE(_T("\nn:%d mse:%f erate:%f"), sps_n * n, validator.mse(), validator.erate());

			//cross_validator.validate(network, sps, n);
			EXTL_TEST_TRACE(_T("cross_validator mse:%f erate:%f"), cross_validator.mse(), cross_validator.erate());
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::test namespace 
 */
EXTL_TEST_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_ANN_TEST_SIN_TESTER_H */
/* //////////////////////////////////////////////////////////////////// */

