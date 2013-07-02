/* ///////////////////////////////////////////////////////////////////////
 * File:		lock_error.h		
 *
 * Created:		08.04.30				
 * Updated:		08.11.24
 *
 * Brief:		The Lock Error 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ERROR_LOCK_ERROR_H
#define EXTL_ERROR_LOCK_ERROR_H

/*!\file lock_error.h
 * \brief The Lock Error 
 */
#ifndef __cplusplus
#	error lock_error.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "synch_error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief lock_error class
 *
 * \ingroup extl_group_error
 */
class lock_error
	: public synch_error
{
	/// \name Types
	/// @{
	public:
		typedef synch_error							base_type;
		typedef lock_error							class_type;
		typedef base_type::code_type				code_type;
		typedef base_type::string_type				string_type;
		typedef base_type::char_type				char_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k lock_error(char_type const* reason = NULL , code_type error_code = 0)
			: base_type(reason, error_code)
		{}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		virtual char_type const* get_default_reason() const
		{
			return "invalid lock error";
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ERROR_LOCK_ERROR_H */
/* //////////////////////////////////////////////////////////////////// */

