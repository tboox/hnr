/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_ga_test.h		
 *
 * Created:		08.11.13			
 * Updated:		08.11.13
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_GA_FOPTI_GA_TEST_H
#define EXTL_INTELLIGENCE_GA_FOPTI_GA_TEST_H
#include "../fopti.h"
/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(fopti_ga_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct fopti_ga_test
{
	// for maximum optimization
	// [-1, 20]
	// x=19.850052 
	// max f(x)=21.850026 
	static double ga1_func(double x)
	{
		return x * sin(10 * 3.1415926 * x) + 2.0;
	}

	// x >= -1 => -1 * (x + 1) <= 0
	static double ga1_cons_1(double x)
	{
		return -1 *(x + 1);
	}

	// x <= 20 => (x - 20) <= 0
	static double ga1_cons_2(double x)
	{
		return (x - 20);
	}

	// for minimum optimization
	// [-100, 100]
	// (x, y): (-0.0898, 0.7126) or (0.0898, -0.7126)
	// min f(x, y)=-1.031628
	static double ga2_func(double x, double y)
	{
		return (4 - 2.1 * x * x + x * x * x * x / 3) * x * x + x * y + (-4 + 4 * y * y) * y * y;
	}

	// x >= -100 => -1 * (x + 100) <= 0
	static double ga2_cons_1(double x, double /*y*/)
	{
		return -1 *(x + 100);
	}

	// x <= 100 => (x - 100) <= 0
	static double ga2_cons_2(double x, double /*y*/)
	{
		return (x - 100);
	}

	// y >= -100 => -1 * (y + 100) <= 0
	static double ga2_cons_3(double /*x*/, double y)
	{
		return -1 *(y + 100);
	}

	// y <= 100 => (y - 100) <= 0
	static double ga2_cons_4(double /*x*/, double y)
	{
		return (y - 100);
	}

	// for maximum optimization
	// [-100, 100]
	// (x, y): (0, 0)
	// min f(x, y)=1
	static double ga3_func(double x, double y)
	{
		double a = sin(sqrt(x * x + y * y));
		double b = (1 + 0.001 * (x * x + y * y));
		return 0.5 - (a * a - 0.5) / (b * b);
	}

	// x >= -100 => -1 * (x + 100) <= 0
	static double ga3_cons_1(double x, double /*y*/)
	{
		return -1 *(x + 100);
	}

	// x <= 100 => (x - 100) <= 0
	static double ga3_cons_2(double x, double /*y*/)
	{
		return (x - 100);
	}

	// y >= -100 => -1 * (y + 100) <= 0
	static double ga3_cons_3(double /*x*/, double y)
	{
		return -1 *(y + 100);
	}

	// y <= 100 => (y - 100) <= 0
	static double ga3_cons_4(double /*x*/, double y)
	{
		return (y - 100);
	}

	// for minimum optimization
	// [0, ...]
	// (x, y): (1, 1)
	// min f(x, y)=10
	static double ga4_func(double x, double y)
	{
		return x * x + y * y + 8;
	}
	// x >= 0 => -1 * (x) <= 0
	static double ga4_cons_1(double x, double /*y*/)
	{
		return -1 * x;
	}

	// y >= 0 => -1 * (y) <= 0
	static double ga4_cons_2(double /*x*/, double y)
	{
		return -1 * y ;
	}

	// x * x - y >= 0 => -1 * (x * x - y) <= 0
	static double ga4_cons_3(double x, double y)
	{
		return -1 * (x * x - y);
	}

	// -x - y * y + 2 = 0 => (-x - y * y + 2)^2 = 0
	static double ga4_cons_4(double x, double y)
	{
		return (2 - x - y * y) * (2 - x - y * y);
	}

	fopti_ga_test()
	{
		EXTL_TEST_TRACE(_T("\nfopti_ga_test:"));

		typedef func_ptr<double (*)(double)>			ga1_func_type;
		typedef fopti_ga<ga1_func_type>					ga1_ga_type;
		typedef ga1_ga_type::scopes_type				ga1_scopes_type;
		typedef ga1_scopes_type::scope_type				ga1_scope_type;
		typedef ga1_ga_type::constraints_type			ga1_constraints_type;

		ga1_ga_type ga1_ga	(	ga1_func_type(&ga1_func)
							,	ga1_scopes_type(ga1_scope_type(-1, 20))
							,	ga1_constraints_type(ga1_func_type(&ga1_cons_1), ga1_func_type(&ga1_cons_2))
							);
		ga1_ga.generate();

		typedef func_ptr<double (*)(double, double)>	ga2_func_type;
		typedef fopti_ga<ga2_func_type, e_false_v>		ga2_ga_type;
		typedef ga2_ga_type::scopes_type				ga2_scopes_type;
		typedef ga2_scopes_type::scope_type				ga2_scope_type;
		typedef ga2_ga_type::constraints_type			ga2_constraints_type;

		ga2_ga_type ga2_ga	(	ga2_func_type(&ga2_func)
							,	ga2_scopes_type(ga2_scope_type(-100, 100), ga2_scope_type(-100, 100))
							,	ga2_constraints_type(ga2_func_type(&ga2_cons_1), ga2_func_type(&ga2_cons_2), ga2_func_type(&ga2_cons_3), ga2_func_type(&ga2_cons_4))
							);
		ga2_ga.generate();

		typedef func_ptr<double (*)(double, double)>	ga3_func_type;
		typedef fopti_ga<ga3_func_type>					ga3_ga_type;
		typedef ga3_ga_type::scopes_type				ga3_scopes_type;
		typedef ga3_scopes_type::scope_type				ga3_scope_type;
		typedef ga3_ga_type::constraints_type			ga3_constraints_type;

		ga3_ga_type ga3_ga	(	ga3_func_type(&ga3_func)
							,	ga3_scopes_type(ga3_scope_type(-100, 100), ga3_scope_type(-100, 100))
							,	ga3_constraints_type(ga3_func_type(&ga3_cons_1), ga3_func_type(&ga3_cons_2), ga3_func_type(&ga3_cons_3), ga3_func_type(&ga3_cons_4))
							);
		ga3_ga.generate();

		typedef func_ptr<double (*)(double, double)>	ga4_func_type;
		typedef fopti_ga<ga4_func_type, e_false_v>		ga4_ga_type;
		typedef ga4_ga_type::scopes_type				ga4_scopes_type;
		typedef ga4_scopes_type::scope_type				ga4_scope_type;
		typedef ga4_ga_type::constraints_type			ga4_constraints_type;

		ga4_ga_type ga4_ga	(	ga4_func_type(&ga4_func)
							,	ga4_scopes_type(ga4_scope_type(0, 100), ga4_scope_type(0, 100))
							,	ga4_constraints_type(ga4_func_type(&ga4_cons_1), ga4_func_type(&ga4_cons_2), ga4_func_type(&ga4_cons_3), ga4_func_type(&ga4_cons_4))
							);
		ga4_ga.generate();
	}
};

fopti_ga_test g_fopti_ga_test;

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(fopti_ga_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_GA_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

