/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_uga_test.h		
 *
 * Created:		08.11.13			
 * Updated:		08.11.13
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_INTELLIGENCE_GA_FOPTI_UGA_TEST_H
#define EXTL_INTELLIGENCE_GA_FOPTI_UGA_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(fopti_uga_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
struct fopti_uga_test
{
	// for maximum optimization
	// [-1, 20]
	// x=19.850052 
	// max f(x)=21.850026 
	static double uga1_func(double x)
	{
		return x * sin(10 * 3.1415926 * x) + 2.0;
	}

	// x >= -1 => -1 * (x + 1) <= 0
	static double uga1_cons_1(double x)
	{
		return -1 *(x + 1);
	}

	// x <= 20 => (x - 20) <= 0
	static double uga1_cons_2(double x)
	{
		return (x - 20);
	}

	// for minimum optimization
	// [-100, 100]
	// (x, y): (-0.0898, 0.7126) or (0.0898, -0.7126)
	// min f(x, y)=-1.031628
	static double uga2_func(double x, double y)
	{
		return (4 - 2.1 * x * x + x * x * x * x / 3) * x * x + x * y + (-4 + 4 * y * y) * y * y;
	}

	// x >= -100 => -1 * (x + 100) <= 0
	static double uga2_cons_1(double x, double /*y*/)
	{
		return -1 *(x + 100);
	}

	// x <= 100 => (x - 100) <= 0
	static double uga2_cons_2(double x, double /*y*/)
	{
		return (x - 100);
	}

	// y >= -100 => -1 * (y + 100) <= 0
	static double uga2_cons_3(double /*x*/, double y)
	{
		return -1 *(y + 100);
	}

	// y <= 100 => (y - 100) <= 0
	static double uga2_cons_4(double /*x*/, double y)
	{
		return (y - 100);
	}

	// for maximum optimization
	// [-100, 100]
	// (x, y): (0, 0)
	// min f(x, y)=1
	static double uga3_func(double x, double y)
	{
		double a = sin(sqrt(x * x + y * y));
		double b = (1 + 0.001 * (x * x + y * y));
		return 0.5 - (a * a - 0.5) / (b * b);
	}

	// x >= -100 => -1 * (x + 100) <= 0
	static double uga3_cons_1(double x, double /*y*/)
	{
		return -1 *(x + 100);
	}

	// x <= 100 => (x - 100) <= 0
	static double uga3_cons_2(double x, double /*y*/)
	{
		return (x - 100);
	}

	// y >= -100 => -1 * (y + 100) <= 0
	static double uga3_cons_3(double /*x*/, double y)
	{
		return -1 *(y + 100);
	}

	// y <= 100 => (y - 100) <= 0
	static double uga3_cons_4(double /*x*/, double y)
	{
		return (y - 100);
	}

	// for minimum optimization
	// [0, ...]
	// (x, y): (1, 1)
	// min f(x, y)=10
	static double uga4_func(double x, double y)
	{
		return x * x + y * y + 8;
	}
	// x >= 0 => -1 * (x) <= 0
	static double uga4_cons_1(double x, double /*y*/)
	{
		return -1 * x;
	}

	// y >= 0 => -1 * (y) <= 0
	static double uga4_cons_2(double /*x*/, double y)
	{
		return -1 * y ;
	}

	// x * x - y >= 0 => -1 * (x * x - y) <= 0
	static double uga4_cons_3(double x, double y)
	{
		return -1 * (x * x - y);
	}

	// -x - y * y + 2 = 0 => (-x - y * y + 2)^2 = 0
	static double uga4_cons_4(double x, double y)
	{
		return (2 - x - y * y) * (2 - x - y * y);
	}

	fopti_uga_test()
	{
		EXTL_TEST_TRACE(_T("\nfopti_uga_test:"));

		typedef func_ptr<double (*)(double)>			uga1_func_type;
		typedef fopti_uga<uga1_func_type>				uga1_ga_type;
		typedef uga1_ga_type::scopes_type				uga1_scopes_type;
		typedef uga1_scopes_type::scope_type			uga1_scope_type;
		typedef uga1_ga_type::constraints_type			uga1_constraints_type;

		uga1_ga_type uga1_ga(	uga1_func_type(&uga1_func)
							,	uga1_scopes_type(uga1_scope_type(-1, 20))
							,	uga1_constraints_type(uga1_func_type(&uga1_cons_1), uga1_func_type(&uga1_cons_2))
							);
		uga1_ga.generate();

		typedef func_ptr<double (*)(double, double)>	uga2_func_type;
		typedef fopti_uga<uga2_func_type, e_false_v>	uga2_ga_type;
		typedef uga2_ga_type::scopes_type				uga2_scopes_type;
		typedef uga2_scopes_type::scope_type			uga2_scope_type;
		typedef uga2_ga_type::constraints_type			uga2_constraints_type;

		uga2_ga_type uga2_ga(	uga2_func_type(&uga2_func)
							,	uga2_scopes_type(uga2_scope_type(-100, 100), uga2_scope_type(-100, 100))
							,	uga2_constraints_type(uga2_func_type(&uga2_cons_1), uga2_func_type(&uga2_cons_2), uga2_func_type(&uga2_cons_3), uga2_func_type(&uga2_cons_4))
							);
		uga2_ga.generate();

		typedef func_ptr<double (*)(double, double)>	uga3_func_type;
		typedef fopti_uga<uga3_func_type>				uga3_ga_type;
		typedef uga3_ga_type::scopes_type				uga3_scopes_type;
		typedef uga3_scopes_type::scope_type			uga3_scope_type;
		typedef uga3_ga_type::constraints_type			uga3_constraints_type;

		uga3_ga_type uga3_ga(uga3_func_type(&uga3_func)
							,	uga3_scopes_type(uga3_scope_type(-100, 100), uga3_scope_type(-100, 100))
							,	uga3_constraints_type(uga3_func_type(&uga3_cons_1), uga3_func_type(&uga3_cons_2), uga3_func_type(&uga3_cons_3), uga3_func_type(&uga3_cons_4))
							);
		uga3_ga.generate();

		typedef func_ptr<double (*)(double, double)>	uga4_func_type;
		typedef fopti_uga<uga4_func_type, e_false_v>	uga4_ga_type;
		typedef uga4_ga_type::scopes_type				uga4_scopes_type;
		typedef uga4_scopes_type::scope_type			uga4_scope_type;
		typedef uga4_ga_type::constraints_type			uga4_constraints_type;

		uga4_ga_type uga4_ga(	uga4_func_type(&uga4_func)
							,	uga4_scopes_type(uga4_scope_type(0, 100), uga4_scope_type(0, 100))
							,	uga4_constraints_type(uga4_func_type(&uga4_cons_1), uga4_func_type(&uga4_cons_2), uga4_func_type(&uga4_cons_3), uga4_func_type(&uga4_cons_4))
							);
		uga4_ga.generate();
	}
};

fopti_uga_test g_fopti_uga_test;

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(fopti_uga_test)
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_UGA_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

