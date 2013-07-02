/* ///////////////////////////////////////////////////////////////////////
 * File:		windows_error_base.h		
 *
 * Created:		08.03.31				
 * Updated:		08.11.20	
 *
 * Brief:		The windows_error_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_PLATFORM_WINDOWS_ERROR_BASE_H
#define EXTL_PLATFORM_PLATFORM_WINDOWS_ERROR_BASE_H

/*!\file windows_error_base.h
 * \brief The windows_error_base class
 */
#ifndef __cplusplus
#	error windows_error_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace 
 */
EXTL_WINDOWS_BEGIN_WHOLE_NAMESPACE 

/*!\brief windows_error_base class
 *
 * \ingroup extl_group_error
 */
class windows_error_base 
	: public platform_error_base 
{
	/// \name Types
	/// @{
	public:
		typedef platform_error_base					base_type;
		typedef windows_error_base					class_type;
		typedef base_type::code_type				code_type;
		typedef base_type::string_type				string_type;
		typedef base_type::char_type				char_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k windows_error_base(char_type const* reason = NULL , code_type error_code = 0)
			: base_type(reason, error_code)
		{}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		virtual char_type const* get_default_reason() const
		{
			return "unknown windows error";
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::windows namespace
 */
EXTL_WINDOWS_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_PLATFORM_WINDOWS_ERROR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */

