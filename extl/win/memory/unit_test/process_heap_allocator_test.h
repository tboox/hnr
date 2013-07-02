/* ///////////////////////////////////////////////////////////////////////
 * File:		process_heap_allocator_test.h		
 *
 * Created:		08.02.20				
 * Updated:		08.05.06
 *
 * Brief: Unit-testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_MEMORY_PROCESS_HEAP_ALLOCATOR_TEST_H
#define EXTL_MEMORY_PROCESS_HEAP_ALLOCATOR_TEST_H

#ifndef EXTL_PLATFORM_WIN_MEMORY_PROCESS_HEAP_ALLOCATOR_H
#	error This file must be included of process_heap_allocator.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	template < typename_param_k T, typename_param_k A = process_heap_allocator<T> >
#else
	template < typename_param_k T, typename_param_k A >
#endif
struct process_heap_allocator_test
{
	process_heap_allocator_test()
	{
		process_heap_allocator<void> void_allocator;

		A allocator;
		e_uint_t n=100;
		T *p = allocator.allocate(n);
		EXTL_ASSERT(p != NULL);

		allocator.construct(p, 1987);
		EXTL_ASSERT(*p == 1987);
		
		T *pnew = allocator.reallocate(p, 1000);
		EXTL_ASSERT(pnew != NULL);
		EXTL_ASSERT(*pnew == 1987);

		allocator.destroy(pnew);

		EXTL_ASSERT((void_allocator == void_allocator));
		EXTL_ASSERT(!(allocator != allocator));

		allocator.deallocate(pnew);

#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		typedef typename_type_k A::template_qual_k rebind<e_char_t>::other_type	CA;
		CA char_allocator;
		e_char_t *pc = char_allocator.allocate(n);
		char_allocator.construct(pc, 'C');
		EXTL_ASSERT(*pc == 'C');
		char_allocator.deallocate(pc);
#endif

	}
};
#if !defined(EXTL_COMPILER_IS_BORLAND) && !defined(EXTL_COMPILER_IS_DMC)
#	ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		process_heap_allocator_test< e_uint_t > g_process_heap_allocator_test;
#	else
		process_heap_allocator_test< e_uint_t, process_heap_allocator< e_uint_t > > g_process_heap_allocator_test;
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_PROCESS_HEAP_ALLOCATOR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

