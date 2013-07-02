/* ///////////////////////////////////////////////////////////////////////
 * File:		process_heap_allocator.h		
 *
 * Created:		08.02.20				
 * Updated:		08.05.05
 *
 * Brief: process_heap_allocator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_MEMORY_PROCESS_HEAP_ALLOCATOR_H
#define EXTL_PLATFORM_WIN_MEMORY_PROCESS_HEAP_ALLOCATOR_H

/*!\file process_heap_allocator.h
 * \brief process_heap_allocator class 
 */
#ifndef __cplusplus
#	error process_heap_allocator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "extl/memory/allocator_base.h"
#include "process_heap.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief process_heap_allocator class
 * \param T The value type
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
class process_heap_allocator : public allocator_base< T, process_heap_allocator<T> >
{
	/// \name Types
	/// @{
	public:
		typedef process_heap_allocator< T >					class_type;			
		typedef allocator_base< T, class_type >				base_type;	
		typedef typename_type_k base_type::value_type		value_type;			
		typedef typename_type_k base_type::pointer			pointer;			
		typedef typename_type_k base_type::const_pointer	const_pointer;	
		typedef typename_type_k base_type::reference		reference;			
		typedef typename_type_k base_type::const_reference	const_reference;	
		typedef typename_type_k base_type::size_type		size_type;	
		typedef typename_type_k process_heap::handle_type	handle_type;
	/// @}

	public:
		/// Rebinds allocator
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef process_heap_allocator< U >			other_type;
		};
#endif

	public:
		/// The deleter 
		struct deleter : process_heap
		{
			public:
				typedef process_heap										base_type;
				typedef deleter												class_type;
				typedef typename_type_k process_heap::handle_type			handle_type;			

			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
						base_type::deallocate(p);
					}
				}
			
		};
		/// The deleter Type
		typedef deleter									deleter_type;			

	/// \name Types
	/// @{
	public:
		process_heap_allocator() EXTL_THROW_0()
			: m_process_heap(){};

#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		process_heap_allocator(process_heap_allocator< U > const&)
			: m_process_heap(){};
#else
		process_heap_allocator(class_type const&)
			: m_process_heap(){};
#endif
	/// @}

	private:
		friend class allocator_base< T, class_type >;

	private:
		/// Allocates memory
		void* do_allocate(size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
			return m_process_heap.allocate(n * sizeof(value_type));
		}
		/// Reallocates memory
		void* do_reallocate(void* p, size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
			return m_process_heap.reallocate(p, n * sizeof(value_type));
		}
		/// Deallocates memory
		void do_deallocate(void* p, size_type n)
		{
			EXTL_SUPPRESS_UNUSED(n);
			m_process_heap.deallocate(p);
		}
		/// Deallocates memory
		void do_deallocate(void* p)
		{
			m_process_heap.deallocate(p);
		}

	private:
		process_heap  m_process_heap;			//!< The process heap

};

/* ///////////////////////////////////////////////////////////////////////
 * void specialization
 */
EXTL_TEMPLATE_SPECIALISATION
class process_heap_allocator< void >
{
	public:
		typedef process_heap_allocator< void >	class_type;	
		typedef void							value_type;	
		typedef void*							pointer;			
		typedef void const*						const_pointer;			
		typedef e_size_t						size_type;		

	public:
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef process_heap_allocator< U >	other_type;
		};
#endif

	public:
		struct deleter : process_heap
		{
			public:
				typedef process_heap										base_type;
				typedef deleter												class_type;
				typedef process_heap::handle_type							handle_type;			

			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
						base_type::deallocate(p);
					}
				}
			
		};
		typedef deleter							deleter_type;			

	public:
		void*	do_allocate(size_type n, void const* hint);
		void*	do_reallocate(void* p, size_type n, void const* hint);
		void	do_deallocate(void* p, size_type n);
		void	do_deallocate(void* p);
};

/* //////////////////////////////////////////////////////////////////// */
template < typename_param_k T >
inline e_bool_t operator ==(process_heap_allocator<T> const&, process_heap_allocator<T> const &)
{
    return e_true_v;
}

template < typename_param_k T >
inline e_bool_t operator !=(process_heap_allocator<T> const &, process_heap_allocator<T> const &)
{
    return e_false_v;
}
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_ALLOCATOR_TEST_ENABLE
#	include "unit_test/process_heap_allocator_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_MEMORY_PROCESS_HEAP_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */


