/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_matrix_test.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.10
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_BASIC_MATRIX_TEST_H
#define EXTL_CONTAINER_BASIC_MATRIX_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(basic_matrix_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int basic_matrix_test()
{
	typedef basic_matrix<int, buffer_selector<int>::buffer_type>	basic_matrix_type;

	int buf1[] = {	1, 2, 3, 4 , 
					5, 6, 7, 8,  
					9, 10, 11, 12	};
	basic_matrix_type ma1(buf1, 3, 4);

	EXTL_ASSERT(ma1.dim0() == 3);
	EXTL_ASSERT(ma1.dim1() == 4);
	EXTL_ASSERT(ma1[0].dim0() == 4);
	EXTL_ASSERT(ma1.size() == 12);

	EXTL_ASSERT(ma1[1][0] == 5);
	EXTL_ASSERT(ma1.front() == 1);
	EXTL_ASSERT(ma1.back() == 12);

	int buf2[3][4] = {	{1, 1, 1, 1}, 
						{1, 1, 1, 1},  
						{1, 1, 1, 1}	};
	
	basic_matrix_type ma2(reinterpret_cast<int const*>(buf2), 3, 4);

	EXTL_ASSERT(ma2[1][0] == 1);
	EXTL_ASSERT(ma2.at(1, 0) == 1);
	EXTL_ASSERT(ma2.front() == 1);
	EXTL_ASSERT(ma2.back() == 1);
	EXTL_ASSERT(ma2.dim0() == 3);
	EXTL_ASSERT(ma2.dim1() == 4);

	ma2.swap(ma1);

	EXTL_ASSERT(ma2.at(1, 0) == 5);
	EXTL_ASSERT(ma2.front() == 1);
	EXTL_ASSERT(ma2.back() == 12);

	ma2[1][0] = 6;
	EXTL_ASSERT(ma2[1][0] == 6);

	EXTL_TEST_TRACE(_T("basic_matrix test:"));
	for (e_size_t i = 0; i < ma2.dim0(); ++i)
	{
		EXTL_TEST_TRACE(_T("%d %d %d %d"), ma2[i][0], ma2[i][1], ma2[i][2], ma2[i][3]);
	}

	EXTL_TEST_TRACE(_T("\nelement:"));
	for (basic_matrix_type::const_iterator p = ma2.begin(); p != ma2.end(); ++p)
	{
		EXTL_TEST_TRACE(_T("%d "), *p);
	}

	EXTL_TEST_TRACE(_T("\nrow(0):"));
	for (basic_matrix_type::const_rowe_iterator prowe = ma2.rowe_begin(0); prowe != ma2.rowe_end(0); ++prowe)
	{
		EXTL_TEST_TRACE(_T("%d "), *prowe);
	}

	EXTL_TEST_TRACE(_T("\nreverse row(0):"));
	for (basic_matrix_type::const_rowe_reverse_iterator rprowe = ma2.rowe_rbegin(0); rprowe != ma2.rowe_rend(0); ++rprowe)
	{
		EXTL_TEST_TRACE(_T("%d "), *rprowe);
	}

	EXTL_TEST_TRACE(_T("\ncol(0):"));
	for (basic_matrix_type::const_cole_iterator pcole = ma2.cole_begin(0); pcole != ma2.cole_end(0); ++pcole)
	{
		EXTL_TEST_TRACE(_T("%d "), *pcole);
	}

	EXTL_TEST_TRACE(_T("\nreverse col(0):"));
	for (basic_matrix_type::const_cole_reverse_iterator rpcole = ma2.cole_rbegin(0); rpcole != ma2.cole_rend(0); ++rpcole)
	{
		EXTL_TEST_TRACE(_T("%d "), *rpcole);
	}
	EXTL_TEST_TRACE(_T(""));
	return 0;
}
int basic_matrix_test_ret = basic_matrix_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(basic_matrix_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_BASIC_MATRIX_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

