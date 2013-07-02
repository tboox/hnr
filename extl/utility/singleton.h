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
#include "prefix.h" 
#include "../synch/synch_traits_selector.h"
#include "../synch/scoped_lock.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

template<	typename_param_k T 
		,	typename_param_k L
		>
struct singleton_tag{};

/*!\brief singleton class
 *
 * \param T The object type
 * \param L The lock type
 * \param Tag The Tag type
 *
 * \ingroup extl_group_synch
 */
template<	typename_param_k T 
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k L		= typename_type_def_k synch_traits_selector::synch_traits_type::lock_type
		,	typename_param_k Tag	= singleton_tag<T, L>
#else
		,	typename_param_k L
		,	typename_param_k Tag
#endif
		>
class singleton
	: private Tag
{
	/// \name Types
	/// @{
	public:
		typedef singleton						class_type;
		typedef T								object_type;
		typedef Tag								tag_type;
		typedef L								lock_type;
		typedef e_bool_t						bool_type;

		// binds object and lock
		typedef struct scoped_type_
			: lock_type
		{
			private:
				object_type						m_object;

			public:
				scoped_type_()
					: lock_type(), m_object()
				{}

			public:
				object_type&	object()	{ return m_object;	}

		}										scoped_type;
	/// @}

	/// \name Members
	/// @{
	private:
		static class_type						s_self;
		static scoped_type*						s_scope;
		static bool_type						s_is_expired;
	/// @}

	/// \name Constructors
	/// @{
	public:
		// Ensure the instance() is called before main() begins 
		singleton()
		{
			object_type& obj = class_type::instance();
			EXTL_SUPPRESS_UNUSED(obj);
		}
		~singleton()
		{
			uninit();
		}
	/// @}

	/// \name Helpers
	/// @{
	private:
		// Initializes the object 
		static void init()
		{
			if(NULL == scope())
			{
				scope() = new scoped_type();
			}

			// checks whether the object has been expired
			EXTL_MESSAGE_ASSERT(!s_is_expired, "This object has been expired");
		}

		// Uninitializes the object 
		static void uninit()
		{
			if(NULL != scope())
			{
				delete scope();
				scope() = NULL;
				
				s_is_expired = e_true_v;
			}
		}

		// Returns the pointer reference to static object 
		static scoped_type*& scope()
		{
		#ifdef EXTL_COMPILER_IS_DMC
			static scoped_type* p = NULL;
			return p;
		#else /* DMC: Link error */
			return s_scope;
		#endif
		}

		void do_nothing() const {}
	/// @}
	
	/// \name Methods
	/// @{
	public:
		/// Returns a reference of a object 
		static object_type& instance()
		{
			// Initializes the object and allows multiple initialization 
			init();

			/* Force the instantiation of singleton<>,
			 * whose constructor is called before main() begins
			 */
			s_self.do_nothing();

			EXTL_MESSAGE_ASSERT(NULL != scope(), "The singleton is not existed!");

			// for synchronization 
			scoped_lock<lock_type> guard(*scope());
			return scope()->object();
		}
	/// @}
};

template<	typename_param_k T 
		,	typename_param_k L
		,	typename_param_k Tag
		>
typename_type_k singleton<T, L, Tag>::scoped_type* singleton<T, L, Tag>::s_scope = NULL;

template<	typename_param_k T 
		,	typename_param_k L
		,	typename_param_k Tag
		>
typename_type_k singleton<T, L, Tag>::bool_type singleton<T, L, Tag>::s_is_expired = e_false_v;

template<	typename_param_k T 
		,	typename_param_k L
		,	typename_param_k Tag
		>
singleton<T, L, Tag> singleton<T, L, Tag>::s_self;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_SINGLETON_H */
/* //////////////////////////////////////////////////////////////////// */
