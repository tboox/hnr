/* ///////////////////////////////////////////////////////////////////////
 * File:		malloc_allocator.h		
 *
 * Created:		08.02.20					
 * Updated:		08.04.14	
 *
 * Brief: new_allocator class - use malloc & free & realloc methods
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_MALLOC_ALLOCATOR_H
#define EXTL_MEMORY_MALLOC_ALLOCATOR_H

/*!\file malloc_allocator.h
 * \brief new_allocator class - use malloc & free & realloc methods
 */
#ifndef __cplusplus
#	error malloc_allocator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "allocator_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief malloc_allocator class
 * 
 * \param T The element type
 *
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
class malloc_allocator : public allocator_base< T, malloc_allocator<T> >
{
	/// \name Types
	/// @{
	public:
		typedef malloc_allocator< T >							class_type;				
		typedef allocator_base< T, class_type >					base_type;		
		typedef typename_type_k base_type::value_type			value_type;				
		typedef typename_type_k base_type::pointer				pointer;				
		typedef typename_type_k base_type::const_pointer		const_pointer;		
		typedef typename_type_k base_type::reference			reference;				
		typedef typename_type_k base_type::const_reference		const_reference;		
		typedef typename_type_k base_type::size_type			size_type;			
	/// @}

		/// Rebinds allocator 
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef malloc_allocator< U >					other_type;
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
						::free(p);
					}
				}
		};
		/// The deleter type
		typedef deleter										deleter_type;		

	/// \name Constructors
	/// @{
	public:
		malloc_allocator() EXTL_THROW_0(){};

#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		malloc_allocator(malloc_allocator< U > const&){};
#else
		malloc_allocator(class_type const&){};
#endif
	/// @}

	private:
		friend class allocator_base< T, class_type >;

	/// \name Allocates and deallocates
	/// @{
	private:
		void* do_allocate(size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
			return ::malloc(n * sizeof(value_type));
		}
		void* do_reallocate(void* p, size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
			return ::realloc(p, n * sizeof(value_type));
		}
		void do_deallocate(void* p, size_type n)
		{
			EXTL_SUPPRESS_UNUSED(n);
			::free(p);
		}
		void do_deallocate(void* p)
		{
			::free(p);
		}
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * void specialization
 */
EXTL_TEMPLATE_SPECIALISATION
class malloc_allocator< void >
{
	public:
		typedef malloc_allocator< void >	class_type;	
		typedef void						value_type;	
		typedef void*						pointer;			
		typedef void const*					const_pointer;			
		typedef e_size_t					size_type;		

	public:
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef malloc_allocator< U >					other_type;
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
						::free(p);
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
inline e_bool_t operator ==(malloc_allocator<T> const&, malloc_allocator<T> const &)
{
    return e_true_v;
}

template < typename_param_k T >
inline e_bool_t operator !=(malloc_allocator<T> const &, malloc_allocator<T> const &)
{
    return e_false_v;
}
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_ALLOCATOR_TEST_ENABLE
#	include "unit_test/malloc_allocator_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_MALLOC_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */


