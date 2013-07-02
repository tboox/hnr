/* ///////////////////////////////////////////////////////////////////////
 * File:		null_allocator.h		
 *
 * Created:		08.02.20					
 * Updated:		08.04.14	
 *
 * Brief: null_allocator class - doesn't allocate
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_NULL_ALLOCATOR_H
#define EXTL_MEMORY_NULL_ALLOCATOR_H

/*!\file null_allocator.h
 * \brief null_allocator class - doesn't allocate
 */
#ifndef __cplusplus
#	error null_allocator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "allocator_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief: null_allocator class
 *
 * \param T The element type
 *
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
class null_allocator : public allocator_base< T, null_allocator<T> >
{
	/// \name Types
	/// @{
	public:
		typedef null_allocator< T >								class_type;				
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
			typedef null_allocator< U >					other_type;
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
					EXTL_SUPPRESS_UNUSED(p);
				}
		};
		/// The deleter type
		typedef deleter										deleter_type;			

	/// \name Constructors
	/// @{
	public:
		null_allocator() EXTL_THROW_0() {};

#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		null_allocator(null_allocator< U > const&){};
#else
		null_allocator(class_type const&){};
#endif
	/// @}

	private:
		friend class allocator_base< T, class_type >;

	/// \name Allocates and deallocates
	/// @{
	private:
		void* do_allocate(size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(n);
			EXTL_SUPPRESS_UNUSED(hint);
			return NULL;
		}
		void* do_reallocate(void* p, size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(p);
			EXTL_SUPPRESS_UNUSED(n);
			EXTL_SUPPRESS_UNUSED(hint);
			return NULL;
		}
		void do_deallocate(void* p, size_type n)
		{
			EXTL_SUPPRESS_UNUSED(p);
			EXTL_SUPPRESS_UNUSED(n);
		}
		void do_deallocate(void* p)
		{
			EXTL_SUPPRESS_UNUSED(p);
		}
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * void specialization
 */
EXTL_TEMPLATE_SPECIALISATION
class null_allocator< void >
{
	public:
		typedef null_allocator< void >	class_type;	
		typedef void					value_type;	
		typedef void*					pointer;			
		typedef void const*				const_pointer;			
		typedef e_size_t				size_type;		

	public:
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef null_allocator< U >					other_type;
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
					EXTL_SUPPRESS_UNUSED(p);
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
inline e_bool_t operator ==(null_allocator<T> const&, null_allocator<T> const &)
{
    return e_true_v;
}

template < typename_param_k T >
inline e_bool_t operator !=(null_allocator<T> const &, null_allocator<T> const &)
{
    return e_false_v;
}


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_NULL_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */


