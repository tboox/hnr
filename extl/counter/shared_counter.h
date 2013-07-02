/* ///////////////////////////////////////////////////////////////////////
 * File:		shared_counter.h		
 *
 * Created:		08.03.19				
 * Updated:		08.05.05
 *
 * Brief: shared_counter class - for shared_ptr, shared_array ...
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_SHARED_COUNTER_H
#define EXTL_SHARED_COUNTER_H

/*!\file shared_counter.h
 * \brief shared_counter class - for shared_ptr, shared_array ...
 *
 * - custom thread-safty
 * - custom resource deleter
 */

#ifndef __cplusplus
#	error shared_counter.h need be supported by c++.
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../synch/scoped_lock.h"
#include "../memory/allocator_selector.h"
#include "../algorithm/algorithm.h" /* for std_swap */
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/*!\brief shared_counter class
 * 
 * \param R The resource type
 * \param D The deleter type
 * \param ST The synchronous traits type
 * \param A The allocator type
 *
 * \ingroup extl_group_counter
 */
template<	typename_param_k R									
		,	typename_param_k D									
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT				
		,	typename_param_k ST = typename_type_def_k synch_traits_selector::synch_traits_type	
		,	typename_param_k A = typename_type_def_k allocator_selector<e_byte_t>::allocator_type 
#else
		,	typename_param_k ST
		,	typename_param_k A
#endif
		>
class shared_counter 
:	protected D				
{
	/// \name Types
	/// @{
	public:
		typedef shared_counter<R, D, ST, A>								class_type;
		typedef A														allocator_type;
		typedef ST														synch_traits_type;
		typedef typename_type_k synch_traits_type::lock_type			lock_type;
		typedef typename_type_k synch_traits_type::atomic_traits_type	atomic_traits_type;
		typedef typename_type_k atomic_traits_type::atomic_type			atomic_type;
		typedef typename_type_k allocator_type::size_type				size_type;
		typedef R														resource_type;			
		typedef D														deleter_type;	
	/// @}

	private:
		/// The Shared info type
		struct shared_info_type : lock_type
		{
			shared_info_type(size_type c, resource_type* r)
				: lock_type(), sc(c), res(r)
			{}
			size_type									sc;			//!< the shared count 
			resource_type*								res;		//!< the resource 
		};

		/// The Shared info
		shared_info_type*												m_shared_info;

	private:
		/// Member template friend 
	#ifdef EXTL_MEMBER_TEMPLATE_FRIEND_SUPPORT
		template< typename_param_k R1, typename_param_k D1, typename_param_k L1, typename_param_k A1>
		friend class shared_counter;
	#endif

	/// \name Constructors
	/// @{
	public:
		shared_counter()
			: m_shared_info(NULL), deleter_type()
		{
			EXTL_ASSERT(is_valid());
		}
		explicit_k shared_counter(resource_type* res)
			: m_shared_info(init_shared_info(1, res)), deleter_type()
		{
			EXTL_ASSERT(is_valid());
		}

		shared_counter(resource_type* res, deleter_type const& del)
			: m_shared_info(init_shared_info(1, res)), deleter_type(del)
		{
			EXTL_ASSERT(is_valid());
		}

		shared_counter(class_type const& rhs)
			: m_shared_info(rhs.m_shared_info)
		{
			EXTL_ASSERT(is_valid());

			/* Increase the counter */
			if(NULL != m_shared_info) 
				atomic_traits_type::inc(reinterpret_cast<atomic_type*>(&(m_shared_info->sc)));

			EXTL_ASSERT(is_valid());
		}
	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template< typename_param_k R1>
		explicit_k shared_counter(R1* res)
			: m_shared_info(init_shared_info(1, res)), deleter_type()
		{
			EXTL_ASSERT(is_valid());
		}

		template< typename_param_k R1, typename_param_k D1, typename_param_k ST1, typename_param_k A1>
		shared_counter(shared_counter<R1, D1, ST1, A1> const& rhs)
			: m_shared_info(reinterpret_cast<shared_info_type*>(rhs.m_shared_info))
		{
			EXTL_ASSERT(is_valid());

			/* Increase the counter */
			if(NULL != m_shared_info) 
				atomic_traits_type::inc(reinterpret_cast<atomic_type*>(&(m_shared_info->sc)));

			EXTL_ASSERT(is_valid());
		}
	#endif

		~shared_counter() EXTL_THROW_0()
		{
			EXTL_ASSERT(is_valid());

			/* Decrease the counter */
			decrease_count();
	
			EXTL_ASSERT(is_valid());
		}
	/// @}

	public:
		/// operator=() overload
		class_type& operator=(class_type const& rhs)
		{
			EXTL_ASSERT(is_valid());
			if(this != &rhs)
			{
				/* Increase the counter */
				if(NULL != rhs.m_shared_info) 
				{ 
					atomic_traits_type::inc(reinterpret_cast<atomic_type*>(&(rhs.m_shared_info->sc)));
				}
				/* Decrease the counter */
				decrease_count();
				m_shared_info = rhs.m_shared_info;
			}

			EXTL_ASSERT(is_valid());
			return *this;
		}
		/// Swap
		void swap(class_type& other)
		{
			EXTL_ASSERT(is_valid());

			std_swap(m_shared_info, other.m_shared_info);

			EXTL_ASSERT(is_valid());
		}
		/// Gets the shared count
		size_type count() const
		{
			return (NULL != m_shared_info)? 
				atomic_traits_type::read(reinterpret_cast<atomic_type*>(&(m_shared_info->sc))) : 0;
		}
		/// Indicates whether the count is unique
		e_bool_t is_unique() const		{ return (1 == count());	}
		/// Indicates whether the count is unique
		e_bool_t is_zero() const		{ return (0 == count());	}

	private:
		/// Returns the allocator
		allocator_type allocator() const	{ return allocator_type();	}
		/// Returns the deleter
		deleter_type& deleter()				{ return *this;				}
		/// Returns the deleter
		deleter_type const& deleter() const { return *this;				}

		/// Initializes the shared_info 
		shared_info_type* init_shared_info(size_type sc, resource_type* res)
		{
		#ifdef EXTL_COMPILER_IS_DMC
			enum { en_shared_info_size = sizeof(shared_info_type) };
			shared_info_type* p = reinterpret_cast<shared_info_type*>(allocator().allocate(en_shared_info_size));
		#else
			shared_info_type* p = reinterpret_cast<shared_info_type*>(allocator().allocate(sizeof(shared_info_type)));
		#endif
			
			EXTL_ASSERT(NULL != p);
			if(NULL == p) 
			{
				/* Deletes resource */
				deleter()(res);

				/* Throws alloc_error() */
				EXTL_THROW_E(alloc_error());
			}
			else
			{
				/* Constructs m_shared_info */
				new (p) shared_info_type(sc, res);
			}
			return p;
		}
		/// Decrease the counter 
		void decrease_count()
		{
			if (NULL == m_shared_info) return ;
			EXTL_ASSERT(is_valid());

			{
				/* Lock and unlock*/
				scoped_lock<lock_type> guard(*m_shared_info);

				--m_shared_info->sc;
				/* Destroys the resource if count() == 0  */
				if (count() == 0 && NULL != m_shared_info) 
					deleter()(m_shared_info->res);
			}

			if (count() == 0 && NULL != m_shared_info) 
			{
				/* Destroys counter and lock */
				allocator().deallocate(reinterpret_cast<e_byte_t*>(m_shared_info));
				m_shared_info = NULL;
			}

			EXTL_ASSERT(is_valid());
		}
		/// Invariance
		e_bool_t is_valid() const
		{
			/* The allocation of bytes of memory */
			typedef typename_type_k allocator_type::value_type	value_type;
			EXTL_STATIC_ASSERT(sizeof(value_type) == 1);

			if ((NULL != m_shared_info) && (count() < 1))
			{
				return e_false_v;
			}
			return e_true_v;
		}
};

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k R
		,	typename_param_k D
		,	typename_param_k ST
		,	typename_param_k A 
		>
EXTL_INLINE void swap(shared_counter<R, D, ST, A>& lhs, shared_counter<R, D, ST, A>& rhs)
{
    lhs.swap(rhs);
}

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_COUNTER_SHARED_COUNTER_TEST_ENABLE
#	include "unit_test/shared_counter_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	typename_param_k R
		,	typename_param_k D
		,	typename_param_k ST
		,	typename_param_k A 
		>
EXTL_INLINE void swap(EXTL_NS(shared_counter)<R, D, ST, A>& lhs, EXTL_NS(shared_counter)<R, D, ST, A>& rhs)
{
	lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SHARED_COUNTER_H */
/* //////////////////////////////////////////////////////////////////// */
