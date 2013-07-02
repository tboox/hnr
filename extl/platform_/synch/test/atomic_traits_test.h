/* ///////////////////////////////////////////////////////////////////////
 * File:		atomic_traits_test.h		
 *
 * Created:		08.03.27					
 * Updated:		09.01.12
 *
 * Brief:		Unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_SYNCH_ATOMIC_TRAITS_TEST_H
#define EXTL_SYNCH_ATOMIC_TRAITS_TEST_H

/* ///////////////////////////////////////////////////////////////////////
 * unit_test namespace
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE
EXTL_TEST_NAME_BEGIN_NAMESPACE(atomic_traits_test)

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
static int atomic_traits_test()
{
	atomic_traits<e_true_v>::size_type a = 10;

	atomic_traits<e_true_v>::::inc(&a);
	EXTL_ASSERT(a == 11);
	EXTL_ASSERT(atomic_traits<e_true_v>::preinc(&a) == 12);
	EXTL_ASSERT(atomic_traits<e_true_v>::postinc(&a) == 12);

	atomic_traits<e_true_v>::::dec(&a);
	EXTL_ASSERT(a == 12);
	EXTL_ASSERT(atomic_traits<e_true_v>::predec(&a) == 11);
	EXTL_ASSERT(atomic_traits<e_true_v>::postdec(&a) == 11);

	atomic_traits<e_true_v>::::write(&a, 10);
	EXTL_ASSERT(atomic_traits<e_true_v>::read(&a) == 10);
	return 0;
}
int atomic_traits_test_ret = atomic_traits_test();

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_NAME_END_NAMESPACE(atomic_traits_test)
EXTL_PLATFORM_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_ATOMIC_TRAITS_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

