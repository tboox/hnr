/* ///////////////////////////////////////////////////////////////////////
 * File:		heap.h		
 *
 * Created:		08.05.22			
 * Updated:		08.05.22
 *
 * Brief: heap class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_MEMORY_HEAP_H
#define EXTL_PLATFORM_WIN_MEMORY_HEAP_H

/*!\file heap.h
 * \brief heap class 
 */
#ifndef __cplusplus
#	error heap.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../memory/prefix.h"
#include "../../utility/uncopyable.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief heap class
 * \ingroup extl_group_memory
 */
class heap : private uncopyable<heap>
{
	/// \name Types
	/// @{
	public:
		typedef heap				class_type;
		typedef HANDLE				handle_type;
		typedef DWORD				size_type;
	/// @}

	private:
		/// The handle of the heap 
		handle_type					m_hheap;
		/// Indicates whether is the owner of the heap
		e_bool_t					m_is_owner;

	private:
		enum { en_default_page_size = 8 * 1024 };

	/// \name Constructors
	/// @{
	public:
		/// Creates a private heap
		heap(	size_type initial_size = en_default_page_size
			,	size_type max_size = 0
			,	size_type option = HEAP_GENERATE_EXCEPTIONS)
			: m_hheap(NULL), m_is_owner(e_true_v)
		{
			create(initial_size, max_size, option);
		}
		/// Attach a heap handle
		heap(handle_type hheap)
			: m_hheap(hheap), m_is_owner(e_false_v)
		{
		}
		~heap()
		{
			destroy();
		}
	/// @}

	public:
		/// Creates a private heap
		e_bool_t create	(	size_type initial_size = en_default_page_size
						,	size_type max_size = 0
						,	size_type option = HEAP_GENERATE_EXCEPTIONS)
		{
			m_hheap = ::HeapCreate(option, initial_size, max_size);
			if (NULL == m_hheap) return e_false_v;
			return e_true_v;
		}
		/// Allocates a memory block from the heap
		void* allocate(size_type n, size_type flag = HEAP_ZERO_MEMORY)
		{
			return (NULL != m_hheap)? ::HeapAlloc(m_hheap, flag, n) : NULL;
		}
		/// Reallocates a memory block from the heap
		void* reallocate(void* p, size_type n, size_type flag = HEAP_ZERO_MEMORY)
		{
			EXTL_ASSERT(NULL != p);
			if (NULL == p) return NULL;
			return (NULL != m_hheap)? ::HeapReAlloc(m_hheap, flag, p, n) : p;
		}
		/// Deallocates a memory block to the heap
		void deallocate(void* p, size_type flag = 0)
		{
			EXTL_ASSERT(NULL != p);
			if (NULL == p) return ;
			if (NULL != m_hheap) ::HeapFree(m_hheap, flag, p);
		}
		/// Return the size of the given memory block
		size_type get_size(void* p, size_type flag = 0)
		{
			EXTL_ASSERT(NULL == p || NULL != m_hheap);
			return ::HeapSize(m_hheap, flag, p);
		}
		/// Destroys the heap
		void destroy()
		{
			if (NULL != m_hheap && m_is_owner) 
			{
				::HeapDestroy(m_hheap);
				m_hheap = NULL;
				m_is_owner = e_false_v;
			}
		}
		/// Returns the heap handle 
		handle_type handle() const
		{
			return m_hheap;
		}

};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_MEMORY_HEAP_H */
/* //////////////////////////////////////////////////////////////////// */
