/* ///////////////////////////////////////////////////////////////////////
 * File:		singleton.h		
 *
 * Created:		08.04.17					
 * Updated:		08.04.17
 *
 * Brief: Create an instance only before main() begins
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_UTILITY_SINGLETON_H
#define EXTL_UTILITY_SINGLETON_H

/*!\file singleton.h
 * \brief Create an instance only before main() begins
 */
#ifndef __cplusplus
#	error singleton.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h" 
#include "../synch/synch_traits_selector.h"
#include "../synch/scoped_lock.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief singleton class
 *
 * \param T The object type
 *
 * \ingroup extl_group_synch
 */
template< typename_param_k T >
class singleton
{
	public:
		typedef singleton<T>					class_type;
		typedef T								object_type;

	private:
		static class_type						s_self;
		static object_type*						s_object;

	private:
		void do_nothing() const {}

	public:
		/* Ensure the instance() is called before main() begins */
		singleton()
		{
			object_type& obj = class_type::instance();
		}
		~singleton()
		{
			uninit();
		}
		/* Initializes the object and allows multiple initialization */
		static void init()
		{
			if(NULL == object())
			{
				object() = new object_type();
			}
		}

		/* Uninitializes the object */
		static void uninit()
		{
			if(NULL != object())
			{
				delete object();
				object() = NULL;
			}
		}

		/* Returns the pointer reference to static object */
		static object_type*& object()
		{
		#ifdef EXTL_COMPILER_IS_DMC
			static object_type* p = NULL;
			return p;
		#else /* DMC: Link error */
			return s_object;
		#endif
		}
	
	public:
		/* Returns a reference of the object */
		static object_type& instance()
		{
			/* Initializes the object and allows multiple initialization */
			init();

			/* Force the instantiation of singleton<T>,
			 * whose constructor is called before main() begins
			 */
			s_self.do_nothing();

			EXTL_MESSAGE_ASSERT(NULL != object(), "The singleton is not existed!");
			return *object();
		}
};
template < typename_param_k T >
typename_type_k singleton<T>::object_type* singleton<T>::s_object = NULL;

template < typename_param_k T >
singleton<T> singleton<T>::s_self;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_SINGLETON_H */
/* //////////////////////////////////////////////////////////////////// */
