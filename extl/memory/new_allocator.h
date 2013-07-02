/* ///////////////////////////////////////////////////////////////////////
 * File:		new_allocator.h		
 *
 * Created:		08.02.20					
 * Updated:		08.04.14	
 *
 * Brief: new_allocator class - use new and delete operators
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_NEW_ALLOCATOR_H
#define EXTL_MEMORY_NEW_ALLOCATOR_H

/*!\file new_allocator.h
 * \brief new_allocator class - use new and delete operators
 */
#ifndef __cplusplus
#	error new_allocator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "allocator_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief new_allocator class
 *
 * \param T The element type
 *
 * \ingroup extl_group_memory
 */
template < typename_param_k T >
class new_allocator : public allocator_base< T, new_allocator<T> >
{
	/// \name Types
	/// @{
	public:
		typedef new_allocator< T >								class_type;			
		typedef allocator_base< T, class_type >					base_type;	
		typedef typename_type_k base_type::value_type			value_type;			
		typedef typename_type_k base_type::pointer				pointer;			
		typedef typename_type_k base_type::const_pointer		const_pointer;		
		typedef typename_type_k base_type::reference			reference;				
		typedef typename_type_k base_type::const_reference		const_reference;		
		typedef typename_type_k base_type::size_type			size_type;	
	/// @}

	public:
		/// Rebinds allocator
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef new_allocator< U >							other_type;
		};
#endif
	public:
		/// The deleter of objects 
		struct object_deleter
		{
			public:
				typedef object_deleter	class_type;
			public:
				object_deleter(){}
				object_deleter(void const* p)
				{
					EXTL_SUPPRESS_UNUSED(p);
				}
				object_deleter(class_type const& rhs)
				{
					EXTL_SUPPRESS_UNUSED(rhs);
				}
			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
					#ifdef delete
						delete p;
					#else
						::operator delete(p);
					#endif
					}
				}
		};
		/// The deleter of array 
		struct array_deleter
		{
			public:
				typedef array_deleter	class_type;
			public:
				array_deleter(){}
				array_deleter(void const* p)
				{
					EXTL_SUPPRESS_UNUSED(p);
				}
				array_deleter(class_type const& rhs)
				{
					EXTL_SUPPRESS_UNUSED(rhs);
				}
			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
					#ifdef delete
						delete [] p;
					#else
						::operator delete(p);
					#endif
					}
				}
		};

		/// The object deleter type
		typedef object_deleter								object_deleter_type;
		/// The array deleter type
		typedef array_deleter								array_deleter_type;		
		/// The deleter type
		typedef array_deleter								deleter_type;		

	/// \name Constructors
	/// @{
	public:
		new_allocator() EXTL_THROW_0() {};
		
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		new_allocator(new_allocator< U > const&){};
#else
		new_allocator(class_type const&){};
#endif
	/// @}

	private:
		friend class allocator_base< T, class_type >;

	/// \name Allocates and deallocates
	private:
		void* do_allocate(size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
		#ifdef new
			return new e_byte_t[n * sizeof(value_type)];
		#else 
			return ::operator new (n * sizeof(value_type));
		#endif
		
		}
		/// be not supported
		void* do_reallocate(void* p, size_type n, void const* hint)
		{
			EXTL_MESSAGE_ASSERT(0, "new_allocator<>::reallocate() is not supported!");
			EXTL_SUPPRESS_UNUSED(hint);
			EXTL_SUPPRESS_UNUSED(n);
			return p;
		
		}
		void do_deallocate(void* p, size_type n)
		{
			EXTL_SUPPRESS_UNUSED(n);
		#ifdef delete
			delete [] static_cast< e_byte_t* >(p);
		#else
			::operator delete (p);
		#endif
				
		}
		void do_deallocate(void* p)
		{
		#ifdef delete
			delete [] static_cast< e_byte_t* >(p);
		#else
			::operator delete (p);
		#endif
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * void specialization
 */
EXTL_TEMPLATE_SPECIALISATION
class new_allocator< void >
{
	public:
		typedef new_allocator< void >	class_type;	
		typedef void					value_type;	
		typedef void*					pointer;			
		typedef void const*				const_pointer;			
		typedef e_size_t				size_type;		

	public:
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k U>
		struct rebind
		{
			typedef new_allocator< U >					other_type;
		};
#endif

	public:
		struct object_deleter
		{
			public:
				typedef object_deleter	class_type;
			public:
				object_deleter(){}
				object_deleter(void const* p)
				{
					EXTL_SUPPRESS_UNUSED(p);
				}
				object_deleter(class_type const& rhs)
				{
					EXTL_SUPPRESS_UNUSED(rhs);
				}
			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
					#ifdef delete
						delete p;
					#else
						::operator delete(p);
					#endif
					}
				}
		};
		struct array_deleter
		{
			public:
				typedef array_deleter	class_type;
			public:
				array_deleter(){}
				array_deleter(void const* p)
				{
					EXTL_SUPPRESS_UNUSED(p);
				}
				array_deleter(class_type const& rhs)
				{
					EXTL_SUPPRESS_UNUSED(rhs);
				}
			public:
				void operator()(pointer p)
				{
					if(NULL != p)
					{
					#ifdef delete
						delete [] p;
					#else
						::operator delete(p);
					#endif
					}
				}
		};

		typedef object_deleter								object_deleter_type;	
		typedef array_deleter								array_deleter_type;		
		typedef array_deleter								deleter_type;			

	public:
		void*	do_allocate(size_type n, void const* hint);
		void*	do_reallocate(void* p, size_type n, void const* hint);
		void	do_deallocate(void* p, size_type n);
		void	do_deallocate(void* p);
};
/* //////////////////////////////////////////////////////////////////// */
template < typename_param_k T >
inline e_bool_t operator ==(new_allocator<T> const&, new_allocator<T> const &)
{
    return e_true_v;
}

template < typename_param_k T >
inline e_bool_t operator !=(new_allocator<T> const &, new_allocator<T> const &)
{
    return e_false_v;
}
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_ALLOCATOR_TEST_ENABLE
#	include "unit_test/new_allocator_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_NEW_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */


