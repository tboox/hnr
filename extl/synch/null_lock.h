/* ///////////////////////////////////////////////////////////////////////
 * File:		null_lock.h		
 *
 * Created:		08.03.20					
 * Updated:		08.12.13		
 *
 * Brief:		The null_lock class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_SYNCH_NULL_LOCK_H
#define EXTL_SYNCH_NULL_LOCK_H

/*!\file null_lock.h
 * \brief null_lock class
 */
#ifndef __cplusplus
#	error null_lock.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "lock_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 
/*\brief null_lock class
 *
 * \ingroup extl_group_synch
 */
class null_lock 
	: public lock_base<null_lock>
{
	/// \name Types
	/// @{
	public:
		typedef lock_base<null_lock>				base_type;
		typedef null_lock							class_type;
		typedef base_type::size_type				size_type;
		typedef base_type::bool_type				bool_type;
	#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
		friend										base_type;
	#endif
	/// @}
	
	/// \name Implemetions
	/// @{
#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
	protected:
#else
	public:
#endif
		void		do_lock()		{};
		bool_type	do_trylock()	{ return e_false_v;	}
		void		do_unlock()		{};
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_SYNCH_NULL_LOCK_H */
/* //////////////////////////////////////////////////////////////////// */
