/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_lock.h		
 *
 * Created:		08.03.20					
 * Updated:		08.04.28	
 *
 * Brief:		scoped_lock class - lock and unlock automaticly
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SYNCH_SCOPED_LOCK_H
#define EXTL_SYNCH_SCOPED_LOCK_H

/*!\file scoped_lock.h
 * \brief scoped_lock class
 */
#ifndef __cplusplus
#	error scoped_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "lock_base.h"
#include "null_lock.h"
#include "../utility/uncopyable.h"
#include "../utility/suppress_unused.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief scoped_lock class
 *
 * \param L The lock type
 *
 * \ingroup extl_group_synch
 */
template<typename_param_k L>
class scoped_lock 
	: private uncopyable<scoped_lock<L> >
{
	/// \name Types
	/// @{
	public:
		typedef scoped_lock<L>								class_type;
		typedef	L											lock_type;
		typedef typename_type_k lock_type::size_type		size_type;
		typedef typename_type_k lock_type::bool_type		bool_type;
	/// @}
	
	/// \name Members
	/// @{
	private:
		/// note: reference type
		lock_type&											m_lock;		
	/// @}

	/// \name Constructors
	public:
		explicit_k scoped_lock(lock_type& lock)
			: m_lock(lock)
		{
			m_lock.lock();
		}
		~scoped_lock()
		{
			m_lock.unlock();
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		bool_type is_locked() const	{ return m_lock.is_locked();	}
	/// @}
};
/*!\brief scoped_lock<null_lock> specialisation 
 *
 * \param L The lock type
 *
 * \ingroup extl_group_synch
 */
EXTL_TEMPLATE_SPECIALISATION
class scoped_lock<null_lock> 
	: private uncopyable< scoped_lock<null_lock> >
{
	/// \name Types
	/// @{
	public:
		typedef scoped_lock<null_lock>						class_type;
		typedef	null_lock									lock_type;
		typedef lock_type::size_type						size_type;
		typedef lock_type::bool_type						bool_type;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		explicit_k scoped_lock(lock_type& /*lock*/)
		{
			//EXTL_SUPPRESS_UNUSED(lock);
		}
		~scoped_lock(){}
	/// @}

	/// \name Attributes
	/// @{
	public:
		bool_type is_locked() const	{ return e_false_v; }
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_SCOPED_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
