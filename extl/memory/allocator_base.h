/* ///////////////////////////////////////////////////////////////////////
 * File:		allocator_base.h		
 *
 * Created:		08.02.20					
 * Updated:		08.04.14	
 *
 * Brief: Memory allocator base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_ALLOCATOR_BASE_H
#define EXTL_MEMORY_ALLOCATOR_BASE_H

/*!\file allocator_base.h
 * \brief Memory allocator base class
 */
#ifndef __cplusplus
#	error allocator_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_COMPILER_IS_BORLAND
#	include "new.h"
#else
#	include "new"
#endif

#include "../utility/suppress_unused.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief allocator_base
 * 
 * \param T The element type
 * \param A The allocator type
 *
 * \ingroup extl_group_memory
 */
template < typename_param_k T, typename_param_k A >
class allocator_base 
{
	/// \name Types
	/// @{
	public:
		typedef allocator_base< T, A >		class_type;			
		typedef A							allocator_type;		
		typedef T							value_type;		
		typedef value_type*					pointer;		
		typedef value_type const*			const_pointer;		
		typedef value_type&					reference;			
		typedef value_type const&			const_reference;	
		typedef e_size_t					size_type;		
	/// @}

	#ifndef  EXTL_CRTP_SUPPORT
	private:
		virtual void*	do_allocate(size_type n, void const* hint) = 0;
		virtual void*	do_reallocate(void* p, size_type n, void const* hint) = 0;
		virtual void	do_deallocate(void* p, size_type n) = 0;
		virtual void	do_deallocate(void* p) = 0;
	#endif

	protected:
		allocator_base(){};	

	/* Memory allocate counter */
	#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	private:
		static size_type					s_allocateCount;		
		static size_type					s_reallocateCount;		
		static size_type					s_deallocate_count;		
		static size_type					s_construct_count;		
		static size_type					s_destroy_count;		

	public:
		static size_type get_allocate_count()	{return class_type::s_allocateCount;	}
		static size_type get_reallocate_count()	{return class_type::s_reallocateCount;	}
		static size_type get_deallocate_count()	{return class_type::s_deallocate_count;	}
		static size_type get_construct_count()	{return class_type::s_construct_count;	}
		static size_type get_destroy_count()	{return class_type::s_destroy_count;	}
	#endif
		
	public:
		/// Allocates a memory block of size n
		pointer allocate(size_type n, void const* hint = NULL);
		/// Reallocates a memory block of size n 
		pointer reallocate(pointer p, size_type n, void const* hint = NULL);
		/// Releases the memory block 
		void deallocate(pointer p);
		/// Deallocates a memory block of size n 
		void deallocate(pointer p, size_type n);

		
	#ifdef EXTL_ALLOCATOR_CHARALLOC_METHOD
		/// For compatibility
		char *_Charalloc(size_type n)	{ return reinterpret_cast<char*>(allocate(n, NULL));	}
	#endif

		/// Returns the maximum number of allocatable entities 
		size_type max_size() const EXTL_THROW_0();

	public:
		/// In-place constructs a instance with the given value 
		void construct(pointer p, const_reference value);
		/// In-place constructs a instance 
		void construct(pointer p);
		/// In-place destroys a instance 
		void destroy(pointer p);
		/// Returns the address of the corresponding to the given reference 
		pointer address(reference value) EXTL_THROW_0();
		/// Returns the address of the corresponding to the given reference 
		const_pointer address(const_reference value) const EXTL_THROW_0();

	private:
		enum { en_overflow_signature = 0xDEADBEEF };
};

// Initialize counter 
#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
template < typename_param_k T, typename_param_k A >
typename_type_k allocator_base< T, A >::size_type allocator_base< T, A >::s_allocateCount = 0;		
template < typename_param_k T, typename_param_k A >
typename_type_k allocator_base< T, A >::size_type allocator_base< T, A >::s_reallocateCount = 0;		
template < typename_param_k T, typename_param_k A >
typename_type_k allocator_base< T, A >::size_type allocator_base< T, A >::s_deallocate_count = 0;		
template < typename_param_k T, typename_param_k A >
typename_type_k allocator_base< T, A >::size_type allocator_base< T, A >::s_construct_count = 0;		
template < typename_param_k T, typename_param_k A >
typename_type_k allocator_base< T, A >::size_type allocator_base< T, A >::s_destroy_count = 0;		
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
#	undef EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
#endif

#define EXTL_ALLOCATOR_BASE_TEMPLATE_DECL		\
template<	typename_param_k		T			\
		,	typename_param_k		A			\
		>

/* Class qualification */
#ifdef EXTL_ALLOCATOR_BASE_QUAL
#	undef EXTL_ALLOCATOR_BASE_QUAL
#endif

#define EXTL_ALLOCATOR_BASE_QUAL	allocator_base<T, A>

/* Class qualification */
#ifdef EXTL_ALLOCATOR_BASE_RET_QUAL
#	undef EXTL_ALLOCATOR_BASE_RET_QUAL
#endif

#define EXTL_ALLOCATOR_BASE_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_ALLOCATOR_BASE_QUAL::ret_type \
					EXTL_ALLOCATOR_BASE_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */

EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline EXTL_ALLOCATOR_BASE_RET_QUAL(pointer)::allocate(size_type n, void const* hint)
{
	// Allocate
	void *p = static_cast<allocator_type*>(this)->do_allocate(n, hint);

	/* Throw alloc_error() */
	EXTL_ASSERT_THROW(p != NULL, alloc_error());

#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	++class_type::s_allocateCount;
#endif

	return static_cast<pointer>(p);
}

EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline EXTL_ALLOCATOR_BASE_RET_QUAL(pointer)::reallocate(pointer p, size_type n, void const* hint)
{
	// Rellocate
	void *pnew = static_cast<allocator_type*>(this)->do_reallocate(static_cast<void*>(p), n, hint);

	/* Throw alloc_error() */
	EXTL_ASSERT_THROW(pnew != NULL, alloc_error());

#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	++class_type::s_reallocateCount;
#endif
	return static_cast<pointer>(pnew);
}

EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline void EXTL_ALLOCATOR_BASE_QUAL::deallocate(pointer p)
{
	// Dellocate
	static_cast<allocator_type*>(this)->do_deallocate(static_cast<void*>(p));

#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	++class_type::s_deallocate_count;
#endif
}

EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline void EXTL_ALLOCATOR_BASE_QUAL::deallocate(pointer p, size_type n)
{
	// Dellocate
	static_cast<allocator_type*>(this)->do_deallocate(static_cast<void*>(p), n);

#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	++class_type::s_deallocate_count;
#endif
}
EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline EXTL_ALLOCATOR_BASE_RET_QUAL(size_type)::max_size() const EXTL_THROW_0()
{
	return static_cast< size_type >(-1) / sizeof(value_type);
}

EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline void EXTL_ALLOCATOR_BASE_QUAL::construct(pointer p, const_reference value)
{
	EXTL_ASSERT( p != NULL );
	new(p) value_type(value);

#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	++class_type::s_construct_count;
#endif
}
EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline void EXTL_ALLOCATOR_BASE_QUAL::construct(pointer p)
{
	EXTL_ASSERT( p != NULL );
	new(p) value_type();

#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	++class_type::s_construct_count;
#endif
}
EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline void EXTL_ALLOCATOR_BASE_QUAL::destroy(pointer p)
{
	EXTL_ASSERT( p != NULL );
	p->~T();

#ifdef EXTL_MEMORY_ALLOCATOR_COUNTER_ENABLE
	++class_type::s_destroy_count;
#endif
}
EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline EXTL_ALLOCATOR_BASE_RET_QUAL(pointer)::address(reference value) EXTL_THROW_0()
{
	return &value;
}
EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
inline EXTL_ALLOCATOR_BASE_RET_QUAL(const_pointer)::address(const_reference value) const EXTL_THROW_0()
{
	return &value;
}
/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_ALLOCATOR_BASE_TEMPLATE_DECL
#undef EXTL_ALLOCATOR_BASE_QUAL
#undef EXTL_ALLOCATOR_BASE_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_ALLOCATOR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */


