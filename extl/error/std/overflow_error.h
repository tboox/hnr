/* ///////////////////////////////////////////////////////////////////////
 * File:		overflow_error.h		
 *
 * Created:		08.04.30				
 * Updated:		08.11.24
 *
 * Brief:		The Overflow Error 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ERROR_STD_OVERFLOW_ERROR_H
#define EXTL_ERROR_STD_OVERFLOW_ERROR_H

/*!\file overflow_error.h
 * \brief The Overflow Error 
 */
#ifndef __cplusplus
#	error overflow_error.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief std_overflow_error class
 *
 * \ingroup extl_group_error
 */
class std_overflow_error
	: public error_base
{
	/// \name Types
	/// @{
	public:
		typedef error_base							base_type;
		typedef std_overflow_error					class_type;
		typedef base_type::code_type				code_type;
		typedef base_type::string_type				string_type;
		typedef base_type::char_type				char_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k std_overflow_error(char_type const* reason = NULL , code_type error_code = 0)
			: base_type(reason, error_code)
		{}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		virtual char_type const* get_default_reason() const
		{
			return "overflow error";
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ERROR_STD_OVERFLOW_ERROR_H */
/* //////////////////////////////////////////////////////////////////// */

