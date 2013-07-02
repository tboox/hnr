/* ///////////////////////////////////////////////////////////////////////
 * File:		global_allocator.h		
 *
 * Created:		08.02.20				
 * Updated:		08.05.05
 *
 * Brief: global_allocator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_MEMORY_GLOBAL_ALLOCATOR_H
#define EXTL_PLATFORM_WIN_MEMORY_GLOBAL_ALLOCATOR_H

/*!\file global_allocator.h
 * \brief global_allocator class 
 */
#ifndef __cplusplus
#	error global_allocator.h need be supported by c++.
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

/*!\brief global_allocator class
 * \param T The value type
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
class global_allocator : public allocator_base< T, global_allocator<T> >
{
	/// \name Types
	/// @{
	public:
		typedef global_allocator< T >									class_type;			
		typedef allocator_base< T, class_type >							base_type;	
		typedef typename_type_k base_type::value_type					value_type;			
		typedef typename_type_k base_type::pointer						pointer;			
		typedef typename_type_k base_type::const_pointer				const_pointer;		
		typedef typename_type_k base_type::reference					reference;			
		typedef typename_type_k base_type::const_reference				const_reference;	
		typedef typename_type_k base_type::size_type					size_type;			
	/// @}

		/// Rebinds allocator
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef global_allocator< U >								other_type;
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
						::GlobalFree(p);
					}
				}
		};
		/// The deleter type
		typedef deleter										deleter_type;		

	/// \name Constructors
	/// @{
	public:
		global_allocator() EXTL_THROW_0(){};

#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		global_allocator(global_allocator< U > const&){};
#else
		global_allocator(class_type const&){};
#endif
	/// @}

	private:
		friend class allocator_base< T, class_type >;

	private:
		/// *hint: Flag, Default: GPTR 
		void* do_allocate(size_type n, void const* hint)
		{
			UINT flag = GPTR;
			if(hint != NULL)
			{
				flag = *(static_cast< UINT const* >(hint));
			}

			return static_cast<void*>(::GlobalAlloc(flag, n * sizeof(value_type)));
		}
		/// *hint: Flag, Default: GMEM_MOVEABLE 
		void* do_reallocate(void* p, size_type n, void const* hint)
		{
			UINT flag = GMEM_MOVEABLE;
			if(hint != NULL)
			{
				flag = *(static_cast< UINT const* >(hint));
			}

			return static_cast<void*>(::GlobalReAlloc(static_cast<HGLOBAL>(p), n * sizeof(value_type), flag));
		}
		/// Deallocates memory
		void do_deallocate(void* p, size_type n)
		{
			EXTL_SUPPRESS_UNUSED(n);
			::GlobalFree(static_cast<HGLOBAL>(p));
		}
		/// Deallocates memory
		void do_deallocate(void* p)
		{
			::GlobalFree(static_cast<HGLOBAL>(p));
		}

};

/* ///////////////////////////////////////////////////////////////////////
 * void specialization
 */
EXTL_TEMPLATE_SPECIALISATION
class global_allocator< void >
{
	public:
		typedef global_allocator< void >		class_type;	
		typedef void							value_type;	
		typedef void*							pointer;			
		typedef void const*						const_pointer;			
		typedef e_size_t						size_type;		

	public:
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef global_allocator< U >	other_type;
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
						::GlobalFree(p);
					}
				}
		};
		typedef deleter						deleter_type;			

	public:
		void*	do_allocate(size_type n, void const* hint);
		void*	do_reallocate(void* p, size_type n, void const* hint);
		void	do_deallocate(void* p, size_type n);
		void	do_deallocate(void* p);
};

/* //////////////////////////////////////////////////////////////////// */
template < typename_param_k T >
inline e_bool_t operator ==(global_allocator<T> const&, global_allocator<T> const &)
{
    return e_true_v;
}

template < typename_param_k T >
inline e_bool_t operator !=(global_allocator<T> const &, global_allocator<T> const &)
{
    return e_false_v;
}
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_ALLOCATOR_TEST_ENABLE
#	include "unit_test/global_allocator_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_MEMORY_GLOBAL_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */


