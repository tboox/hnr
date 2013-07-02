/* ///////////////////////////////////////////////////////////////////////
 * File:		stoi_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_STOI_TEST_H
#define EXTL_CONVERSION_STOI_TEST_H

#ifndef EXTL_CONVERSION_STOI_H
#	error This file must be included of stoi.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct stoi_test
{
	stoi_test()
	{
		EXTL_TEST_TRACE(_T("stoi test:"));

		/* support stoi<> */
	#ifdef EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT
		stoi<e_sint_t, 10>(_T("-32768"));
		stoi<e_sint_t>(_T("-32768"));
		stoi(_T("-32768"));

		/* signed (10) */
		EXTL_TEST_TRACE(_T("stoi<e_sint8_t, 10>(\"-128\"):%d"), stoi<e_sint8_t, 10>(_T("-128")));
		EXTL_TEST_TRACE(_T("stoi<e_sint8_t, 10>(\"127\"):%d"), stoi<e_sint8_t, 10>(_T("127")));

		EXTL_TEST_TRACE(_T("stoi<e_sint16_t, 10>(\"-32768\"):%d"), stoi<e_sint16_t, 10>(_T("-32768")));
		EXTL_TEST_TRACE(_T("stoi<e_sint16_t, 10>(\"32767\"):%d"), stoi<e_sint16_t, 10>(_T("32767")));

		EXTL_TEST_TRACE(_T("stoi<e_sint32_t, 10>(\"-2147483648\"):%d"), stoi<e_sint32_t, 10>(_T("-2147483648")));
		EXTL_TEST_TRACE(_T("stoi<e_sint32_t, 10>(\"2147483647\"):%d\n"), stoi<e_sint32_t, 10>(_T("2147483647")));

	#if defined(EXTL_64BIT_INT_SUPPORT) && \
			defined(EXTL_PRINTF_I64_FORMAT_SUPPORT)
		EXTL_TEST_TRACE(_T("stoi<e_sint64_t, 10>(\"-9223372036854775808\"):%I64d"),
			stoi<e_sint64_t, 10>(_T("-9223372036854775808")));
		EXTL_TEST_TRACE(_T("stoi<e_sint64_t, 10>(\"9223372036854775807\"):%I64d\n"),
			stoi<e_sint64_t, 10>(_T("9223372036854775807")));
	#endif
		
		/* unsigned (10) */
		EXTL_TEST_TRACE(_T("stoi<e_uint8_t, 10>(\"0\"):%lu"), stoi<e_uint8_t, 10>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint8_t, 10>(\"255\"):%lu"), stoi<e_uint8_t, 10>(_T("255")));

		EXTL_TEST_TRACE(_T("stoi<e_uint16_t, 10>(\"0\"):%lu"), stoi<e_uint16_t, 10>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint16_t, 10>(\"65535\"):%lu"), stoi<e_uint16_t, 10>(_T("65535")));

		EXTL_TEST_TRACE(_T("stoi<e_uint32_t, 10>(\"0\"):%lu"), stoi<e_uint32_t, 10>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint32_t, 10>(\"4294967295\"):%lu\n"), stoi<e_uint32_t, 10>(_T("4294967295")));

	#if defined(EXTL_64BIT_INT_SUPPORT) && \
			defined(EXTL_PRINTF_I64_FORMAT_SUPPORT)
		EXTL_TEST_TRACE(_T("stoi<e_uint64_t, 10>(\"0\"):%I64u"),
			stoi<e_uint64_t, 10>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint64_t, 10>(\"18446744073709551615\"):%I64u\n"),
			stoi<e_uint64_t, 10>(_T("18446744073709551615")));
	#endif

		/* signed (16) */
		EXTL_TEST_TRACE(_T("stoi<e_sint8_t, 16>(\"80\"):%X"), stoi<e_sint8_t, 16>(_T("80")));
		EXTL_TEST_TRACE(_T("stoi<e_sint8_t, 16>(\"7F\"):%X"), stoi<e_sint8_t, 16>(_T("7F")));
		EXTL_TEST_TRACE(_T("stoi<e_sint8_t, 16>(\"7f\"):%x"), stoi<e_sint8_t, 16>(_T("7f")));

		EXTL_TEST_TRACE(_T("stoi<e_sint16_t, 16>(\"8000\"):%X"), stoi<e_sint16_t, 16>(_T("8000")));
		EXTL_TEST_TRACE(_T("stoi<e_sint16_t, 16>(\"7FFF\"):%X"), stoi<e_sint16_t, 16>(_T("7FFF")));
		EXTL_TEST_TRACE(_T("stoi<e_sint16_t, 16>(\"7fff\"):%x"), stoi<e_sint16_t, 16>(_T("7fff")));

		EXTL_TEST_TRACE(_T("stoi<e_sint32_t, 16>(\"80000000\"):%X"), stoi<e_sint32_t, 16>(_T("80000000")));
		EXTL_TEST_TRACE(_T("stoi<e_sint32_t, 16>(\"7FFFFFFF\"):%X"), stoi<e_sint32_t, 16>(_T("7FFFFFFF")));
		EXTL_TEST_TRACE(_T("stoi<e_sint32_t, 16>(\"7fffffff\"):%x\n"), stoi<e_sint32_t, 16>(_T("7fffffff")));

	#if defined(EXTL_64BIT_INT_SUPPORT) && \
			defined(EXTL_PRINTF_I64_FORMAT_SUPPORT)
		EXTL_TEST_TRACE(_T("stoi<e_sint64_t, 16>(\"8000000000000000\"):%I64X"),
			stoi<e_sint64_t, 16>(_T("8000000000000000")));
		EXTL_TEST_TRACE(_T("stoi<e_sint64_t, 16>(\"7FFFFFFFFFFFFFFF\"):%I64X"),
			stoi<e_sint64_t, 16>(_T("7FFFFFFFFFFFFFFF")));
		EXTL_TEST_TRACE(_T("stoi<e_sint64_t, 16>(\"7fffffffffffffff\"):%I64x\n"),
			stoi<e_sint64_t, 16>(_T("7fffffffffffffff")));
	#endif
		
		/* unsigned (16) */
		EXTL_TEST_TRACE(_T("stoi<e_uint8_t, 16>(\"0\"):%lX"), stoi<e_uint8_t, 16>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint8_t, 16>(\"FF\"):%lX"), stoi<e_uint8_t, 16>(_T("FF")));
		EXTL_TEST_TRACE(_T("stoi<e_uint8_t, 16>(\"ff\"):%lx"), stoi<e_uint8_t, 16>(_T("ff")));

		EXTL_TEST_TRACE(_T("stoi<e_uint16_t, 16>(\"0\"):%lX"), stoi<e_uint16_t, 16>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint16_t, 16>(\"FFFF\"):%lX"), stoi<e_uint16_t, 16>(_T("FFFF")));
		EXTL_TEST_TRACE(_T("stoi<e_uint16_t, 16>(\"ffff\"):%lx"), stoi<e_uint16_t, 16>(_T("ffff")));

		EXTL_TEST_TRACE(_T("stoi<e_uint32_t, 16>(\"0\"):%lX"), stoi<e_uint32_t, 16>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint32_t, 16>(\"FFFFFFFF\"):%lX"), stoi<e_uint32_t, 16>(_T("FFFFFFFF")));
		EXTL_TEST_TRACE(_T("stoi<e_uint32_t, 16>(\"ffffffff\"):%lx\n"), stoi<e_uint32_t, 16>(_T("ffffffff")));

	#if defined(EXTL_64BIT_INT_SUPPORT) && \
			defined(EXTL_PRINTF_I64_FORMAT_SUPPORT)
		EXTL_TEST_TRACE(_T("stoi<e_uint64_t, 16>(\"0\"):%I64X"),
			stoi<e_uint64_t, 16>(_T("0")));
		EXTL_TEST_TRACE(_T("stoi<e_uint64_t, 16>(\"FFFFFFFFFFFFFFFF\"):%I64X"),
			stoi<e_uint64_t, 16>(_T("FFFFFFFFFFFFFFFF")));
		EXTL_TEST_TRACE(_T("stoi<e_uint64_t, 16>(\"ffffffffffffffff\"):%I64x\n"),
			stoi<e_uint64_t, 16>(_T("ffffffffffffffff")));
	#endif

	#else /* dose'nt support stoi<> */

		/* signed (10) */
		EXTL_TEST_TRACE(_T("stoi(\"-128\"):%d"), stoi(_T("-128")));
		EXTL_TEST_TRACE(_T("stoi(\"127\"):%d"), stoi(_T("127")));

		EXTL_TEST_TRACE(_T("stoi(\"-32768\"):%d"), stoi(_T("-32768")));
		EXTL_TEST_TRACE(_T("stoi(\"32767\"):%d"), stoi(_T("32767")));

		EXTL_TEST_TRACE(_T("stoi(\"-2147483648\"):%d"), stoi(_T("-2147483648")));
		EXTL_TEST_TRACE(_T("stoi(\"2147483647\"):%d\n"), stoi(_T("2147483647")));
	#endif /* EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT */

		e_ulong_t n = 5000000;
		e_ulong_t i = 0;
		clock_counter stoi_counter;

		stoi_counter.begin();
		for(i = 0; i < n; i++)
		{
		#ifdef EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT
			stoi<long, 10>(_T("123456"));
		#else
			stoi(_T("123456"));
		#endif
		}
		stoi_counter.end();
		EXTL_TEST_TRACE(_T("stoi<long, 10> test result: %u (ms)"), stoi_counter.get_ms());

		stoi_counter.begin();
		for(i = 0; i < n; i++)
		{
			_ttol(_T("123456"));
		}
		stoi_counter.end();
		EXTL_TEST_TRACE(_T("atol test result: %u (ms)\n"), stoi_counter.get_ms());
	}

};
stoi_test g_stoi_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_STOI_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
