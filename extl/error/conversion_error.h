/* ///////////////////////////////////////////////////////////////////////
 * File:		conversion_error.h		
 *
 * Created:		08.04.30				
 * Updated:		08.11.24
 *
 * Brief:		The Conversion Error 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ERROR_CONVERSION_ERROR_H
#define EXTL_ERROR_CONVERSION_ERROR_H

/*!\file conversion_error.h
 * \brief The Conversion Error 
 */
#ifndef __cplusplus
#	error conversion_error.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "error_base.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief conversion_error class
 *
 * \ingroup extl_group_error
 */
class conversion_error
	: public error_base
{
	/// \name Types
	/// @{
	public:
		typedef error_base							base_type;
		typedef conversion_error					class_type;
		typedef base_type::code_type				code_type;
		typedef base_type::string_type				string_type;
		typedef base_type::char_type				char_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k conversion_error(char_type const* reason = NULL , code_type error_code = 0)
			: base_type(reason, error_code)
		{}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		virtual char_type const* get_default_reason() const
		{
			return "invalid conversion error";
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ERROR_CONVERSION_ERROR_H */
/* //////////////////////////////////////////////////////////////////// */

