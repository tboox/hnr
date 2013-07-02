/* ///////////////////////////////////////////////////////////////////////
 * File:		alloc_error.h		
 *
 * Created:		08.04.30				
 * Updated:		08.11.23	
 *
 * Brief:		The Allocate Memory Error
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ERROR_ALLOC_ERROR_H
#define EXTL_ERROR_ALLOC_ERROR_H

/*!\file alloc_error.h
 * \brief The Allocate Memory Error
 */
#ifndef __cplusplus
#	error alloc_error.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "memory_error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief alloc_error class
 *
 * \ingroup extl_group_error
 */
class alloc_error 
	: public memory_error
{
	/// \name Types
	/// @{
	public:
		typedef memory_error						base_type;
		typedef alloc_error							class_type;
		typedef base_type::code_type				code_type;
		typedef base_type::string_type				string_type;
		typedef base_type::char_type				char_type;
	/// @}

	/// \name Constructors
	/// @{
	public: 
		explicit_k alloc_error(char_type const* reason = NULL , code_type error_code = 0)
			: base_type(reason, error_code)
		{}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		virtual char_type const* get_default_reason() const
		{
			return "Unknown Allocate Memory Error";
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ERROR_ALLOC_ERROR_H */
/* //////////////////////////////////////////////////////////////////// */

