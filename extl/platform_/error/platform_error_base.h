/* ///////////////////////////////////////////////////////////////////////
 * File:		platform_error_base.h		
 *
 * Created:		08.03.31				
 * Updated:		08.11.20	
 *
 * Brief:		The platform_error_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_ERROR_BASE_H
#define EXTL_PLATFORM_ERROR_BASE_H

/*!\file platform_error_base.h
 * \brief The platform_error_base class
 */
#ifndef __cplusplus
#	error platform_error_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace 
 */
EXTL_PLATFORM_BEGIN_WHOLE_NAMESPACE 

/*!\brief platform_error_base class
 *
 * \ingroup extl_group_error
 */
class platform_error_base 
	: public error_base 
{
	/// \name Types
	/// @{
	public:
		typedef error_base							base_type;
		typedef platform_error_base					class_type;
		typedef base_type::code_type				code_type;
		typedef base_type::string_type				string_type;
		typedef base_type::char_type				char_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k platform_error_base(char_type const* reason = NULL, code_type error_code = 0)
			: base_type(reason, error_code)
		{}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		virtual char_type const* get_default_reason() const
		{
			return "unknown platform error";
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform namespace
 */
EXTL_PLATFORM_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_ERROR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */

