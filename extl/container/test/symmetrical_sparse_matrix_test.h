/* ///////////////////////////////////////////////////////////////////////
 * File:		symmetrical_sparse_matrix_test.h		
 *
 * Created:		08.12.08			
 * Updated:		08.12.08
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_SYMMETRICAL_SPARSE_MATRIX_TEST_H
#define EXTL_CONTAINER_SYMMETRICAL_SPARSE_MATRIX_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(symmetrical_sparse_matrix_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int symmetrical_sparse_matrix_test()
{
	typedef symmetrical_sparse_matrix<int>	symmetrical_sparse_matrix_type;

	symmetrical_sparse_matrix_type sma(3);

	/* 0 1 2
	 * 1 1 3
	 * 2 3 2
	 */
	sma.at(0, 0) = 0;
	sma.at(0, 1) = 1;
	sma.at(0, 2) = 2;
	sma.at(1, 1) = 1;
	sma.at(1, 2) = 3;
	sma.at(2, 2) = 2;

	EXTL_ASSERT(sma.dim0() == 3);
	EXTL_ASSERT(sma.dim1() == 3);
	EXTL_ASSERT(sma.size() == 9);

	EXTL_ASSERT(sma.at(1, 0) == 1);
	EXTL_ASSERT(sma.at(2, 0) == 2);
	EXTL_ASSERT(sma.at(2, 1) == 3);

	EXTL_ASSERT(sma[1][0] == 1);
	EXTL_ASSERT(sma[2][0] == 2);
	EXTL_ASSERT(sma[2][1] == 3);

	
	EXTL_TEST_TRACE(_T("symmetrical_sparse_matrix test:"));
	for (e_size_t i = 0; i < sma.dim(); ++i)
	{
		EXTL_TEST_TRACE(_T("%d %d %d"), sma[i][0], sma[i][1], sma[i][2]);
	}

	EXTL_TEST_TRACE(_T("\nelement:"));
	for (symmetrical_sparse_matrix_type::const_iterator p = sma.begin(); p != sma.end(); ++p)
	{
		EXTL_TEST_TRACE(_T("%d "), *p);
	}

	EXTL_TEST_TRACE(_T("\nrow(1):"));
	for (symmetrical_sparse_matrix_type::const_rowe_iterator prowe = sma.rowe_begin(1); prowe != sma.rowe_end(1); ++prowe)
	{
		EXTL_TEST_TRACE(_T("%d "), *prowe);
	}

	EXTL_TEST_TRACE(_T("\nreverse row(1):"));
	for (symmetrical_sparse_matrix_type::const_rowe_reverse_iterator rprowe = sma.rowe_rbegin(1); rprowe != sma.rowe_rend(1); ++rprowe)
	{
		EXTL_TEST_TRACE(_T("%d "), *rprowe);
	}

	EXTL_TEST_TRACE(_T("\ncol(1):"));
	for (symmetrical_sparse_matrix_type::const_cole_iterator pcole = sma.cole_begin(1); pcole != sma.cole_end(1); ++pcole)
	{
		EXTL_TEST_TRACE(_T("%d "), *pcole);
	}

	EXTL_TEST_TRACE(_T("\nreverse col(1):"));
	for (symmetrical_sparse_matrix_type::const_cole_reverse_iterator rpcole = sma.cole_rbegin(1); rpcole != sma.cole_rend(1); ++rpcole)
	{
		EXTL_TEST_TRACE(_T("%d "), *rpcole);
	}
	EXTL_TEST_TRACE(_T(""));

	EXTL_ASSERT(sma.exists(1, 0));
	EXTL_ASSERT(sma.exists(2, 0));
	EXTL_ASSERT(sma.exists(2, 1));

	return 0;
}
int symmetrical_sparse_matrix_test_ret = symmetrical_sparse_matrix_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(symmetrical_sparse_matrix_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_SYMMETRICAL_SPARSE_MATRIX_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

