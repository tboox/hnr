/* ///////////////////////////////////////////////////////////////////////
 * File:		win_synch_error.h		
 *
 * Created:		08.03.21				
 * Updated:		08.05.05
 *
 * Brief: win_synch_error class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_WIN_ERROR_WIN_SYNCH_ERROR_H
#define EXTL_WIN_ERROR_WIN_SYNCH_ERROR_H

/*!\file win_synch_error.h
 * \brief win_synch_error class
 */
#ifndef __cplusplus
#	error win_synch_error.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "win_error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief win_synch_error class
 * \ingroup extl_group_error
 */
class win_synch_error : public win_error
{
	public:
		typedef win_error										base_type;
		typedef win_synch_error									class_type;
		typedef base_type::code_type							code_type;
		typedef base_type::string_type							string_type;


	public: 
		explicit_k win_synch_error(char const* reason = NULL , code_type error_code = 0)
		:	base_type(reason, error_code)
		{
		}
	protected:
		virtual char const* get_default_reason() const
		{
			return "Unknown Windows Error";
		}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_WIN_ERROR_WIN_SYNCH_ERROR_H */
/* //////////////////////////////////////////////////////////////////// */

