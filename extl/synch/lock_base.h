/* ///////////////////////////////////////////////////////////////////////
 * File:		lock_base.h		
 *
 * Created:		08.03.20					
 * Updated:		08.12.13	
 *
 * Brief:		The lock_base class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SYNCH_LOCK_BASE_H
#define EXTL_SYNCH_LOCK_BASE_H

/*!\file lock_base.h
 * \brief The lock_base class 
 */
#ifndef __cplusplus
#	error lock_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../utility/uncopyable.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief lock_base class
 *
 * \param Dev The derived type
 *
 * \ingroup extl_group_synch
 */
template<typename_param_k Dev>
class lock_base 
	: private uncopyable<lock_base<Dev> >
{
	/// \name Types
	/// @{
	public:
		typedef lock_base			class_type;
		typedef Dev					derived_type;
		typedef e_bool_t			bool_type;
		typedef e_size_t			size_type;
	/// @}

	/// \name Members
	/// @{
	private:
		size_type					m_lock_n;
	/// @}

	/// \name Constructors
	/// @{
	public:
		lock_base()
			: m_lock_n(0)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		void				lock();		//!< Lock
		bool_type			trylock();	//!< Try lock
		void				unlock();	//!< Unlock
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// Returns the lock count
		size_type			count() const		{ return m_lock_n;			}
		/// Indicates whether is locked
		bool_type			is_locked() const	{ return (count() != 0);	}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		derived_type&		derive()			{ return static_cast<derived_type&>(*this);			}
		derived_type const&	derive() const		{ return static_cast<derived_type const&>(*this);	}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
template<typename_param_k Dev>
inline void lock_base<Dev>::lock()
{
	EXTL_MESSAGE_ASSERT(0 == count(), "lock repeatly"); 
	EXTL_ASSERT_THROW(0 == count(), lock_error("lock_error: repeat lock"));

	derive().do_lock();
	++m_lock_n;
}
template<typename_param_k Dev>
inline typename_type_ret_k lock_base<Dev>::bool_type
lock_base<Dev>::trylock()
{
	EXTL_MESSAGE_ASSERT(0 == count(), "lock repeatly"); 
	EXTL_ASSERT_THROW(0 == count(), lock_error("lock_error: repeat trylock"));

	bool_type ret = derive().do_trylock();
	// lock successfully
	if (ret) ++m_lock_n;
	return ret;

}
template<typename_param_k Dev>
inline void lock_base<Dev>::unlock()
{
	EXTL_MESSAGE_ASSERT(0 != count(), "unlock repeatly"); 
	EXTL_ASSERT_THROW(0 != count(), lock_error("lock_error: repeat unlock"));

	derive().do_unlock();
	--m_lock_n;
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_LOCK_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
