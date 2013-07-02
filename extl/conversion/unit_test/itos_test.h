/* ///////////////////////////////////////////////////////////////////////
 * File:		itos_test.h		
 *
 * Created:		08.02.25				
 * Updated:		08.05.05
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_CONVERSION_ITOS_TEST_H
#define EXTL_CONVERSION_ITOS_TEST_H

#ifndef EXTL_CONVERSION_ITOS_H
#	error This file must be included of itos.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct itos_test
{
	itos_test()
	{
		e_uint32_t unsigned_num = 0;
		e_sint32_t signed_num = 0;

		e_tchar_t buf[100];
		e_size_t n = 100;
		e_size_t result_count = 0;
		const e_tchar_t *p = NULL;

		e_ulong_t count = 1000000;
		e_ulong_t i = 0;
		clock_counter itos_counter;

	#ifdef EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT
		
		/* unsigned (10) */
		EXTL_TEST_TRACE(_T("unsigned num (10):"));
		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MIN;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MAX;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MIN;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MAX;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MIN;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d\n"), unsigned_num, p, result_count);

		/* unsigned (2) */
		EXTL_TEST_TRACE(_T("unsigned num (2):"));
		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MIN;
		p = itos<2>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MAX;
		p = itos<2>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MIN;
		p = itos<2>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MAX;
		p = itos<2>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MIN;
		p = itos<2>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
		p = itos<2>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d\n"), unsigned_num, p, result_count);

		/* unsigned (2) */
		EXTL_TEST_TRACE(_T("unsigned num (16):"));
		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MIN;
		p = itos<16>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MAX;
		p = itos<16>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MIN;
		p = itos<16>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MAX;
		p = itos<16>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MIN;
		p = itos<16>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
		p = itos<16>(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d\n"), unsigned_num, p, result_count);

		/* signed (10) */
		EXTL_TEST_TRACE(_T("signed num (10):"));
		signed_num = EXTL_LIMIT_TRAITS_SINT8_MIN;
		p = itos<10>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT8_MAX;
		p = itos<10>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MIN;
		p = itos<10>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MAX;
		p = itos<10>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MIN;
		p = itos<10>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
		p = itos<10>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d\n"), signed_num, p, result_count);

		/* signed (2) */
		EXTL_TEST_TRACE(_T("signed num (2):"));
		signed_num = EXTL_LIMIT_TRAITS_SINT8_MIN;
		p = itos<2>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT8_MAX;
		p = itos<2>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MIN;
		p = itos<2>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MAX;
		p = itos<2>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MIN;
		p = itos<2>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
		p = itos<2>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d\n"), signed_num, p, result_count);

		/* signed (2) */
		EXTL_TEST_TRACE(_T("signed num (16):"));
		signed_num = EXTL_LIMIT_TRAITS_SINT8_MIN;
		p = itos<16>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT8_MAX;
		p = itos<16>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MIN;
		p = itos<16>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MAX;
		p = itos<16>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MIN;
		p = itos<16>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
		p = itos<16>(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d\n"), signed_num, p, result_count);

		/* 64-bit conversion */
	#if defined(EXTL_64BIT_INT_SUPPORT) && \
			defined(EXTL_PRINTF_I64_FORMAT_SUPPORT)
		e_uint64_t unsigned_num_64 = 0;
		e_sint64_t signed_num_64 = 0;

		/* unsigned (10) */
		EXTL_TEST_TRACE(_T("64bit unsigned num (10):"));

		unsigned_num_64 = EXTL_LIMIT_TRAITS_UINT64_MIN;
		p = itos<10>(unsigned_num_64, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%I64u result:%s count:%d"), unsigned_num_64, p, result_count);

		unsigned_num_64 = EXTL_LIMIT_TRAITS_UINT64_MAX;
		p = itos<2>(unsigned_num_64, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%I64u result:%s count:%d\n"), unsigned_num_64, p, result_count);

		/* signed (10) */
		EXTL_TEST_TRACE(_T("64bit signed num (10):"));

		signed_num_64 = EXTL_LIMIT_TRAITS_SINT64_MIN;
		p = itos<10>(signed_num_64, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%I64d result:%s count:%d"), signed_num_64, p, result_count);

		signed_num_64 = EXTL_LIMIT_TRAITS_SINT64_MAX;
		p = itos<10>(signed_num_64, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%I64d result:%s count:%d\n"), signed_num_64, p, result_count);

	#endif

		/* i2s<> shim */
		EXTL_TEST_TRACE(_T("i2s<e_tchar_t>(%d) test result:"), EXTL_LIMIT_TRAITS_SINT32_MAX);
		EXTL_TEST_TRACE(i2s<e_tchar_t>(EXTL_LIMIT_TRAITS_SINT32_MAX));
		EXTL_TEST_TRACE(_T("i2s<e_tchar_t, 16>(%d) test result:"), EXTL_LIMIT_TRAITS_SINT32_MAX);
		EXTL_TEST_TRACE(i2s<e_tchar_t, 16>(EXTL_LIMIT_TRAITS_SINT32_MAX));

		EXTL_TEST_TRACE(_T("i2s<e_tchar_t>(%u) test result:"), EXTL_LIMIT_TRAITS_UINT32_MAX);
		EXTL_TEST_TRACE(i2s<e_tchar_t>(EXTL_LIMIT_TRAITS_UINT32_MAX));
		EXTL_TEST_TRACE(_T("i2s<e_tchar_t, 16>(%u) test result:"), EXTL_LIMIT_TRAITS_UINT32_MAX);
		EXTL_TEST_TRACE(i2s<e_tchar_t, 16>(EXTL_LIMIT_TRAITS_UINT32_MAX));
		EXTL_TEST_TRACE(_T("\n"));

		/* static array size determination */
	#	ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

		/* unsigned (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
			p = itos<10>(unsigned_num, buf);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("itos(unsigned) test result: %u (ms)"), itos_counter.ms());

		/* signed (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
			p = itos<10>(signed_num, buf, n);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("itos(signed) test result: %u (ms)\n"), itos_counter.ms());

	#	else

		/* unsigned (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
			p = itos<10>(unsigned_num, buf, n);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("itos(unsigned) test result: %u (ms)"), itos_counter.ms());

		/* signed (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
			p = itos<10>(signed_num, buf, n);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("itos(signed) test result: %u (ms)\n"), itos_counter.ms());

	#	endif /* EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
	#elif defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) || \
			defined(EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT) /* support itos, but does'nt support itos<> */
		/* unsigned (10) */
		EXTL_TEST_TRACE(_T("unsigned num (10):"));
		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MIN;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MAX;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MIN;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MAX;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MIN;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
		p = itos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d\n"), unsigned_num, p, result_count);

		/* signed (10) */
		EXTL_TEST_TRACE(_T("signed num (10):"));
		signed_num = EXTL_LIMIT_TRAITS_SINT8_MIN;
		p = itos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT8_MAX;
		p = itos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MIN;
		p = itos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MAX;
		p = itos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MIN;
		p = itos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
		p = itos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d\n"), signed_num, p, result_count);

		/* static array size determination */
	#	ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

		/* unsigned (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
			p = itos(unsigned_num, buf);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("utos test result: %u (ms)"), itos_counter.ms());

		/* signed (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
			p = itos(signed_num, buf);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("ltos test result: %u (ms)"), itos_counter.ms());

	#	else

		/* unsigned (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
			p = itos(unsigned_num, buf, n);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("utos test result: %u (ms)"), itos_counter.ms());

		/* signed (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
			p = itos(signed_num, buf, n);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("ltos test result: %u (ms)"), itos_counter.ms());

	#	endif /* EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
	#else /* dose'nt support itos */
		/* unsigned (10) */
		EXTL_TEST_TRACE(_T("unsigned num (10):"));
		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MIN;
		p = uitos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT8_MAX;
		p = uitos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MIN;
		p = uitos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT16_MAX;
		p = uitos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MIN;
		p = uitos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d"), unsigned_num, p, result_count);

		unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
		p = uitos(unsigned_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("unsigned_num:%u result:%s count:%d\n"), unsigned_num, p, result_count);

		/* signed (10) */
		EXTL_TEST_TRACE(_T("signed num (10):"));
		signed_num = EXTL_LIMIT_TRAITS_SINT8_MIN;
		p = sitos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT8_MAX;
		p = sitos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MIN;
		p = sitos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT16_MAX;
		p = sitos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MIN;
		p = sitos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d"), signed_num, p, result_count);

		signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
		p = sitos(signed_num, buf, n, result_count);
		EXTL_TEST_TRACE(_T("signed_num:%d result:%s count:%d\n"), signed_num, p, result_count);

		/* static array size determination */
	#	ifdef EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

		/* unsigned (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
			p = uitos(unsigned_num, buf);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("utos test result: %u (ms)"), itos_counter.ms());

		/* signed (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
			p = sitos(signed_num, buf);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("ltos test result: %u (ms)"), itos_counter.ms());

	#	else

		/* unsigned (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
			p = uitos(unsigned_num, buf, n);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("utos test result: %u (ms)"), itos_counter.ms());

		/* signed (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
			p = sitos(signed_num, buf, n);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("ltos test result: %u (ms)"), itos_counter.ms());

	#	endif /* EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */

	#endif /* EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT */

		/* CRT: ltoa ultoa Testing */

		/* unsigned (10) */
		itos_counter.begin();
		for(i = 0; i < n; i++)
		{
			unsigned_num = EXTL_LIMIT_TRAITS_UINT32_MAX;
			p = ultoa_test(unsigned_num, buf, 10);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("ultoa test result: %u (ms)"), itos_counter.ms());

		/* signed (10) */
		itos_counter.begin();
		for(i = 0; i < count; i++)
		{
			signed_num = EXTL_LIMIT_TRAITS_SINT32_MAX;
			p = ltoa_test(unsigned_num, buf, 10);
		}

		itos_counter.end();
		EXTL_TEST_TRACE(_T("ltoa test result: %u (ms)\n"), itos_counter.ms());
	}

};
itos_test g_itos_test;
/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONVERSION_ITOS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */
