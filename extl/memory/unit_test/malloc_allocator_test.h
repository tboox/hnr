/* ///////////////////////////////////////////////////////////////////////
 * File:		malloc_allocator_test.h		
 *
 * Created:		08.02.20				
 * Updated:		08.04.14	
 *
 * Brief: malloc_allocator class unit testing
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_MALLOC_ALLOCATOR_TEST_H
#define EXTL_MEMORY_MALLOC_ALLOCATOR_TEST_H

#ifndef EXTL_MEMORY_MALLOC_ALLOCATOR_H
#	error This file must be included of malloc_allocator.h
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
	template < typename_param_k T, typename_param_k A = malloc_allocator<T> >
#else
	template < typename_param_k T, typename_param_k A >
#endif
struct malloc_allocator_test
{
	malloc_allocator_test()
	{
		A allocator;
		e_uint_t n=100;
		T *p = allocator.allocate(n);
		EXTL_ASSERT(p != NULL);

		allocator.construct(p, 1987);
		EXTL_ASSERT(*p == 1987);
		
		
		T *pnew = allocator.reallocate(p, 1000, &n);
		EXTL_ASSERT(pnew != NULL);
		EXTL_ASSERT(*pnew == 1987);

		allocator.destroy(pnew);
		//EXTL_ASSERT(*pnew != 1987);

		EXTL_ASSERT(!(allocator != allocator));

		allocator.deallocate(pnew);

		/* Rebind allocator */
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
		malloc_allocator_test< e_uint_t > g_malloc_allocator_test;
#	else
		malloc_allocator_test< e_uint_t, malloc_allocator< e_uint_t > > g_malloc_allocator_test;
#	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::unit_test namespace
 */
EXTL_TEST_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_MALLOC_ALLOCATOR_TEST_H */
/* //////////////////////////////////////////////////////////////////// */

