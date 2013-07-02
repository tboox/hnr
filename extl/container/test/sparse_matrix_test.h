/* ///////////////////////////////////////////////////////////////////////
 * File:		sparse_matrix_test.h		
 *
 * Created:		08.12.08		
 * Updated:		08.12.08
 *
 * Brief:		Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONTAINER_SPARSE_MATRIX_TEST_H
#define EXTL_CONTAINER_SPARSE_MATRIX_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_BEGIN_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(sparse_matrix_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int sparse_matrix_test()
{
	typedef sparse_matrix<int>			sparse_matrix_type;
	sparse_matrix_type					sm(5);
	e_size_t							i;

	sm.at(0, 0) = 1;
	sm.at(0, 1) = 2;
	sm.at(0, 2) = 3;
	sm.at(1, 0) = 4;
	sm.at(1, 1) = 5;
	sm.at(1, 2) = 6;
	sm.at(2, 0) = 7;
	sm.at(2, 1) = 8;
	sm.at(2, 2) = 9;

	EXTL_TEST_TRACE(_T("sparse_matrix test:"));
	EXTL_TEST_TRACE(_T("\nelement:"));
	for (sparse_matrix_type::const_iterator p = sm.begin(); p != sm.end(); ++p)
	{
		EXTL_TEST_TRACE(_T("%d "), *p);
	}

	EXTL_TEST_TRACE(_T("\nrow(0):"));
	for (sparse_matrix_type::const_rowe_iterator prowe = sm.rowe_begin(0); prowe != sm.rowe_end(0); ++prowe)
	{
		EXTL_TEST_TRACE(_T("%d "), *prowe);
	}

	EXTL_TEST_TRACE(_T("\nreverse row(0):"));
	for (sparse_matrix_type::const_rowe_reverse_iterator rprowe = sm.rowe_rbegin(0); rprowe != sm.rowe_rend(0); ++rprowe)
	{
		EXTL_TEST_TRACE(_T("%d "), *rprowe);
	}

	EXTL_TEST_TRACE(_T("\ncol(0):"));
	for (sparse_matrix_type::const_cole_iterator pcole = sm.cole_begin(0); pcole != sm.cole_end(0); ++pcole)
	{
		EXTL_TEST_TRACE(_T("%d "), *pcole);
	}

	EXTL_TEST_TRACE(_T("\nreverse col(0):"));
	for (sparse_matrix_type::const_cole_reverse_iterator rpcole = sm.cole_rbegin(0); rpcole != sm.cole_rend(0); ++rpcole)
	{
		EXTL_TEST_TRACE(_T("%d "), *rpcole);
	}
	EXTL_TEST_TRACE(_T("sparse matrix:"));
	for (i = 0; i < sm.dim0(); ++i)
	{
		EXTL_TEST_TRACE(_T("%d %d %d %d %d "), sm[i][0], sm[i][1], sm[i][2], sm[i][3], sm[i][4]);
	}
	EXTL_TEST_TRACE(_T(""));

	sm.erase(1, 1);
	EXTL_TEST_TRACE(_T("erase(1, 1) sparse matrix:"));
	for (i = 0; i < sm.dim0(); ++i)
	{
		EXTL_TEST_TRACE(_T("%d %d %d %d %d "), sm[i][0], sm[i][1], sm[i][2], sm[i][3], sm[i][4]);
	}
	EXTL_TEST_TRACE(_T(""));

	sm.erase_row(1);
	EXTL_TEST_TRACE(_T("erase_row(1) sparse matrix:"));
	for (i = 0; i < sm.dim0(); ++i)
	{
		EXTL_TEST_TRACE(_T("%d %d %d %d %d "), sm[i][0], sm[i][1], sm[i][2], sm[i][3], sm[i][4]);
	}
	EXTL_TEST_TRACE(_T(""));

	sm.erase_col(1);
	EXTL_TEST_TRACE(_T("erase_col(1) sparse matrix:"));
	for (i = 0; i < sm.dim0(); ++i)
	{
		EXTL_TEST_TRACE(_T("%d %d %d %d %d "), sm[i][0], sm[i][1], sm[i][2], sm[i][3], sm[i][4]);
	}
	EXTL_TEST_TRACE(_T(""));

	return 0;
}
int sparse_matrix_test_ret = sparse_matrix_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(sparse_matrix_test)
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONTAINER_SPARSE_MATRIX_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

