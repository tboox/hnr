/* ///////////////////////////////////////////////////////////////////////
 * File:		windows_synch_error.h		
 *
 * Created:		08.03.31				
 * Updated:		08.11.20	
 *
 * Brief:		The windows_synch_error class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_PLATFORM_WINDOWS_SYNCH_ERROR_H
#define EXTL_PLATFORM_PLATFORM_WINDOWS_SYNCH_ERROR_H

/*!\file windows_synch_error.h
 * \brief The windows_synch_error class
 */
#ifndef __cplusplus
#	error windows_synch_error.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace 
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE 

/*!\brief windows_synch_error class
 *
 * \ingroup extl_group_error
 */
class windows_synch_error 
	: public windows_error_base 
{
	/// \name Types
	/// @{
	public:
		typedef windows_error_base					base_type;
		typedef windows_synch_error					class_type;
		typedef base_type::code_type				code_type;
		typedef base_type::string_type				string_type;
		typedef base_type::char_type				char_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k windows_synch_error(char_type const* reason = NULL , code_type error_code = 0)
			: base_type(reason, error_code)
		{}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		virtual char_type const* get_default_reason() const
		{
			return "unknown windows synchronous error";
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_PLATFORM_WINDOWS_SYNCH_ERROR_H */
/* //////////////////////////////////////////////////////////////////// */

