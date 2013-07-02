/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_pool_allocator.h		
 *
 * Created:		08.04.28					
 * Updated:		08.04.28
 *
 * Brief: basic_pool_allocator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_BASIC_POOL_ALLOCATOR_H
#define EXTL_MEMORY_BASIC_POOL_ALLOCATOR_H

/*!\file basic_pool_allocator.h
 * \brief basic_pool_allocator class 
 */
#ifndef __cplusplus
#	error basic_pool_allocator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "singleton_pool.h"
#include "basic_pool.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

struct default_basic_pool_allocator_tag{};
/*\brief basic_pool_allocator class
 *
 * \param T The element type
 * \param ST The synchronous traits type
 * \param Tag The allocator tag type
 *
 * \ingroup extl_group_memory
 */
template <	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k ST = typename_type_def_k synch_traits_selector::synch_traits_type	
		,	typename_param_k Tag = default_basic_pool_allocator_tag
#else
		,	typename_param_k ST 
		,	typename_param_k Tag
#endif
		>
class basic_pool_allocator 
	: public allocator_base<T, basic_pool_allocator<T, ST, Tag> >
{
	/// \name Types
	/// @{
	public:
		typedef ST																synch_traits_type;
		typedef typename_type_k synch_traits_type::lock_type					lock_type;
		typedef basic_pool_allocator< T, ST, Tag >								class_type;	
		typedef allocator_base< T, class_type >									base_type;
		typedef default_basic_pool												pool_type;
		typedef typename_type_k base_type::value_type							value_type;	
		typedef typename_type_k base_type::pointer								pointer;				
		typedef typename_type_k base_type::const_pointer						const_pointer;			
		typedef typename_type_k base_type::size_type							size_type;	
		typedef singleton_pool<Tag, pool_type, ST>								singleton_pool_type;
	/// @}

		/// Rebinds allocator 
#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template<typename_param_k T2>
		struct rebind
		{
			typedef basic_pool_allocator<T2, ST, Tag>							other_type;
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
					singleton_pool_type::deallocate(p);
				}
		};
		/// The deleter type
		typedef deleter										deleter_type;			

	/// \name Constructors
	/// @{
	public:
		basic_pool_allocator() EXTL_THROW_0() {};

#ifdef EXTL_MEMORY_ALLOCATOR_REBIND_SUPPORT
		template <typename_param_k T1, typename_param_k ST1, typename_param_k Tag1>
		basic_pool_allocator(basic_pool_allocator< T1, ST1, Tag1 > const&){};
#else
		basic_pool_allocator(class_type const&){};
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
			EXTL_SUPPRESS_UNUSED(n);
			return static_cast<void*>(singleton_pool_type::allocate(n * sizeof(value_type)));
		}
		void* do_reallocate(void* p, size_type n, void const* hint)
		{
			EXTL_SUPPRESS_UNUSED(hint);
			EXTL_SUPPRESS_UNUSED(n);
			return static_cast<void*>(singleton_pool_type::reallocate(p, n * sizeof(value_type)));
		}
		void do_deallocate(void* p, size_type n)
		{
			EXTL_SUPPRESS_UNUSED(n);
			singleton_pool_type::deallocate(p);
		}
		void do_deallocate(void* p)
		{
			singleton_pool_type::deallocate(p);
		}
	/// @}
	
	public:
		/// Gets the pool
		static pool_type& get_pool()
		{
			return singleton_pool_type::get_pool();
		}
};

/* //////////////////////////////////////////////////////////////////// */
#ifdef EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT
template < typename_param_k T, typename_param_k ST, typename_param_k Tag >
inline e_bool_t operator ==(basic_pool_allocator<T, ST, Tag> const&, basic_pool_allocator<T, ST, Tag> const &)
{
    return e_true_v;
}

template < typename_param_k T, typename_param_k ST, typename_param_k Tag >
inline e_bool_t operator !=(basic_pool_allocator<T, ST, Tag> const &, basic_pool_allocator<T, ST, Tag> const &)
{
    return e_false_v;
}
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_ALLOCATOR_TEST_ENABLE
#	include "unit_test/basic_pool_allocator_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_BASIC_POOL_ALLOCATOR_H */
/* //////////////////////////////////////////////////////////////////// */


