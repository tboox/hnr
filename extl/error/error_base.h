/* ///////////////////////////////////////////////////////////////////////
 * File:		error_base.h		
 *
 * Created:		08.03.31				
 * Updated:		08.04.15	
 *
 * Brief:		The error_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ERROR_BASE_H
#define EXTL_ERROR_BASE_H

/*!\file error_base.h
 * \brief The error_base class
 */
#ifndef __cplusplus
#	error error_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../string/error_string.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief error_base class
 *
 * \ingroup extl_group_error
 */
class error_base 
{
	/// \name Types
	/// @{
	public:
		typedef error_base					class_type;
		typedef e_size_t					code_type;
		typedef error_string_a				string_type;
		typedef string_type::char_type		char_type;
	/// @}

	/// \name Members
	/// @{
	private:
		string_type const					m_reason;			//!< Error reason 
		code_type							m_error_code;		//!< Error code 
	/// @}

	private: 
		class_type& operator =(class_type const&);
	
	/// \name Constructors
	/// @{
	public: 
		explicit_k error_base(char_type const* reason = NULL , code_type error_code = 0)
			: m_reason(reason)
			, m_error_code(error_code)
		{
		}
		virtual ~error_base() EXTL_THROW_0()
		{}
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		/// what method overload
		virtual char_type const* what() const EXTL_THROW_0()
		{
			if(!m_reason.is_empty())
			{
				return m_reason.c_str();
			}
			else
			{
				return this->get_default_reason();
			}
		}

		/// gets error code
		code_type	get_error_code() const
		{
			return m_error_code;
		}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		/// gets default error reason 
		virtual char_type const* get_default_reason() const
		{
			return "unknown error";
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_ERROR_TEST_ENABLE
#	include "unit_test/error_base_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ERROR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */

