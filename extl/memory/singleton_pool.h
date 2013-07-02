/* ///////////////////////////////////////////////////////////////////////
 * File:		singleton_pool.h		
 *
 * Created:		08.04.14					
 * Updated:		08.04.15	
 *
 * Brief: singleton_pool class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_SINGLETON_POOL_H
#define EXTL_MEMORY_SINGLETON_POOL_H

/*!\file singleton_pool.h
 * \brief singleton_pool class
 */
#ifndef __cplusplus
#	error singleton_pool.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../utility/singleton.h"
#include "../utility/uncopyable.h"
#include "../synch/synch_traits_selector.h"
//#include "../synch/scoped_lock.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief singleton_pool class
 *
 * \param Tag The tag of the different singleton pool class
 * \param P The pool type
 * \param ST The synchronous traits type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k Tag
		,	typename_param_k P
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k ST = typename_type_def_k synch_traits_selector::synch_traits_type	
#else
		,	typename_param_k ST
#endif
		>
class singleton_pool
	: private uncopyable< singleton_pool<Tag, P, ST> > /* Prohibit copying constructor and copy assignment */
{
	/// \name Types
	/// @{
	public:	
		typedef singleton_pool<Tag, P, ST>						class_type;
		typedef ST												synch_traits_type;
		typedef typename_type_k synch_traits_type::lock_type	lock_type;
		typedef typename_type_k P::pointer						pointer;
		typedef typename_type_k P::const_pointer				const_pointer;
		typedef typename_type_k P::reference					reference;
		typedef typename_type_k P::const_reference				const_reference;
		typedef typename_type_k P::value_type					value_type;
		typedef typename_type_k P::size_type					size_type;
		typedef Tag												tag_type;
	/// @}

	private:
		/* Prohibit create an instance */
		singleton_pool(){}
	
	private:
		/* old singleton
		/// Bind pool and lock as a singleton 
		struct pool_type 
			: P, lock_type
		{
			pool_type():P(), lock_type(){}
		};
		/// The singleton type
		typedef singleton<pool_type>							singleton_type;
		*/
		
		// new singleton

		typedef P												pool_type;
		/// The singleton type
		typedef singleton<pool_type, lock_type, tag_type>		singleton_type;

	public:
		/// Allocates memory
		static pointer allocate(size_type n)
		{
			pool_type& pool = singleton_type::instance();
			//scoped_lock<lock_type> guard(pool);
			return pool.allocate(n);
		}
		/// Deallocates memory
		static void deallocate(pointer p)
		{
			pool_type& pool = singleton_type::instance();
			//scoped_lock<lock_type> guard(pool);
			pool.deallocate(p);
		}
		/// Reallocates memory
		static void* reallocate(pointer p, size_type n)
		{
			pool_type& pool = singleton_type::instance();
			//scoped_lock<lock_type> guard(pool);
			return pool.reallocate(p, n);
		}
		/// Gets the pool
		static pool_type& get_pool()
		{
			return singleton_type::instance();
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	
/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_SINGLETON_POOL_H */
/* //////////////////////////////////////////////////////////////////// */
