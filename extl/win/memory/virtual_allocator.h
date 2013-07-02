/* ///////////////////////////////////////////////////////////////////////
 * File:		virtual_allocator.h		
 *
 * Created:		08.02.20				
 * Updated:		08.05.05
 *
 * Brief: virtual_allocator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_MEMORY_VIRTUAL_ALLOCATOR_H
#define EXTL_PLATFORM_WIN_MEMORY_VIRTUAL_ALLOCATOR_H

/*!\file virtual_allocator.h
 * \brief virtual_allocator class 
 */
#ifndef __cplusplus
#	error virtual_allocator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "extl/memory/allocator_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief virtual_allocator class
 * \param T The value type
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
class virtual_allocator : public allocator_base< T, virtual_allocator<T> >
{
	/// \name Types
	/// @{
	public:
		typedef virtual_allocator< T >						class_type;				
		typedef allocator_base< T, class_type >				base_type;		
		typedef typename_type_k base_type::value_type		value_type;				
		typedef typename_type_k base_type::pointer			pointer;				
		typedef typename_type_k base_type::const_pointer	const_pointer;			
		typedef typename_type_k base_type::reference		reference;			
		typedef typename_type_k base_type::const_reference	const_reference;		
		typedef typename_type_k base_type::size_type		size_type;				
	/// @}

		/// Rebinds allocator
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef virtual_allocator< U >				other_type;
		};
#endif
	public:
		/// The deleter 
		struct deleter
		{
			public:
				typedef deleter	class_type;
			public:
				deleter(){}
				deleter(void const* p)
				{
					EXTL_SUPPRESS_UNUSED(p);
				}
				deleter(class_type const& rhs)
				{
					EXTL_SUPPRESS_UNUSED(rhs);
				}
			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
						::VirtualFree(p, 0, MEM_RELEASE);
					}
				}
		};
		/// The deleter type
		typedef deleter										deleter_type;		

	/// \name Constructors
	/// @{
	public:
		virtual_allocator()  {};

#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		virtual_allocator(virtual_allocator< U > const&){};
#else
		virtual_allocator(class_type const&){};
#endif
	/// @}

	private:
		friend class allocator_base< T, class_type >;

	private:
		/// Allocates memory
		void* do_allocate(size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
			return ::VirtualAlloc(NULL, n * sizeof(value_type), MEM_COMMIT, PAGE_READWRITE);
		}
		/// Realocates memory
		void* do_reallocate(void* p, size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
			return ::VirtualAlloc(p, n * sizeof(value_type), MEM_COMMIT, PAGE_READWRITE);
		}
		/// Deallocates memory
		void do_deallocate(void* p, size_type n)
		{
			EXTL_SUPPRESS_UNUSED(n);
			::VirtualFree(p, 0, MEM_RELEASE);
		}
		/// Deallocates memory
		void do_deallocate(void* p)
		{
			::VirtualFree(p, 0, MEM_RELEASE);
		}

};
/* ///////////////////////////////////////////////////////////////////////
 * void specialization
 */
EXTL_TEMPLATE_SPECIALISATION
class virtual_allocator< void >
{
	public:
		typedef virtual_allocator< void >	class_type;	
		typedef void						value_type;	
		typedef void*						pointer;			
		typedef void const*					const_pointer;			
		typedef e_size_t						size_type;		

	public:
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef virtual_allocator< U >	other_type;
		};
#endif
	
	public:
		struct deleter
		{
			public:
				typedef deleter	class_type;
			public:
				deleter(){}
				deleter(void const* p)
				{
					EXTL_SUPPRESS_UNUSED(p);
				}
				deleter(class_type const& rhs)
				{
					EXTL_SUPPRESS_UNUSED(rhs);
				}
			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
						::VirtualFree(p, 0, MEM_RELEASE);
					}
				}
		};
		typedef deleter										deleter_type;			

	public:
		void*	do_allocate(size_type n, void const* hint);
		void*	do_reallocate(void* p, size_type n, void const* hint);
		void	do_deallocate(void* p, size_type n);
		void	do_deallocate(void* p);
};

/* //////////////////////////////////////////////////////////////////// */
template < typename_param_k T >
inline e_bool_t operator ==(virtual_allocator<T> const&, virtual_allocator<T> const &)
{
    return e_true_v;
}

template < typename_param_k T >
inline e_bool_t operator !=(virtual_allocator<T> const &, virtual_allocator<T> const &)
{
    return e_false_v;
}
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_ALLOCATOR_TEST_ENABLE
#	include "unit_test/virtual_allocator_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_MEMORY_VIRTUAL_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */


