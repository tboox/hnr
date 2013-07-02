/* ///////////////////////////////////////////////////////////////////////
 * File:		error_string.h		
 *
 * Created:		08.04.29				
 * Updated:		08.04.29
 *
 * Brief: error_string class - The simple string used to handle exception error
 *
 * Note:		
 * Generally not more than 256 characters.
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_ERROR_STRING_H
#define EXTL_STRING_ERROR_STRING_H

/*!\file error_string.h
 * \brief error_string class
 *
 * The simple string used to handle exception error
 */

#ifndef __cplusplus
#	error error_string.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "string_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
#define	EXTL_STRING_ERROR_STRING_MAXLENGTH	256
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*! \brief error_string class
 *
 * \param C The character type
 * \param MAX_LENGTH The maximum number of characters in the string
 * \param T The traits type of character string. Default param is string_traits<C, std_char_traits<C> > 
 *
 * \ingroup extl_group_string
 */
template<	typename_param_k		C
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t				MAX_LENGTH = EXTL_STRING_ERROR_STRING_MAXLENGTH
#else
		,	e_size_t				MAX_LENGTH 
#endif
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k		T = string_traits<C> 
#else
		,	typename_param_k		T
#endif
		>
class basic_error_string
{
	/// \name Types
	/// @{
	public:
		typedef basic_error_string<C, MAX_LENGTH, T>								class_type;
		typedef C																	value_type;
		typedef T																	traits_type;
		typedef typename_type_k traits_type::char_type								char_type;
		typedef value_type*															pointer;
		typedef value_type const*													const_pointer;
		typedef value_type&															reference;
		typedef value_type const&													const_reference;
		typedef e_size_t															size_type;
		typedef e_ptrdiff_t															difference_type;
	/// @}

	/// \name Members
	/// @{
	private:
		value_type																	m_buffer[MAX_LENGTH + 1];
		size_type																	m_length;
	/// @}

	private:
		enum {internal_max_length = MAX_LENGTH};	

	/// \name Construtors
	// @{
	public:
		/// Default constructor 
		basic_error_string() 
			: m_length(0)																			
		{	
			m_buffer[m_length] = char_type('\0');	
		}								
		/// Constructs with n characters from the given string at the specified position 
		basic_error_string(class_type const& s) 
			: m_length(s.length())
		{	
			EXTL_ASSERT(length() <= max_length());
			traits_type::copy(m_buffer, s.c_str(), m_length);	
			m_buffer[m_length] = char_type('\0');
		}
		/// Constructs with n characters from the given c-style string at the specified position 
		basic_error_string(char_type const* s)
			: m_length((NULL != s)? traits_type::length(s) : 0)			
		{	
			EXTL_ASSERT(length() <= max_length());
			if((NULL != s))traits_type::copy(m_buffer, s, m_length);	
			m_buffer[m_length] = char_type('\0');
		}

		/// Destructor
		virtual ~basic_error_string() EXTL_THROW_0() {}
	/// @}

	public:
		
		/// Returns c-style string with the null-terminator 
		value_type const* c_str() const								
		{
			return m_buffer;									
		}

		/// Returns the length of the string 
		size_type length() const								
		{
			return m_length;									
		}
		
		/// Indicates whether the string is empty 
		e_bool_t is_empty() const									
		{	
			return traits_type::is_empty(m_buffer);		
		}
		e_bool_t empty() const									
		{	
			return is_empty();		
		}
		/// The maximum number of elements in the string 
		static size_type max_length()								
		{
			return internal_max_length;					
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * basic_error_string
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
typedef basic_error_string< e_char_t > error_string_a;
typedef basic_error_string< e_wchar_t > error_string_w;
typedef basic_error_string< e_tchar_t > error_string;
#else
typedef basic_error_string< e_char_t, EXTL_STRING_ERROR_STRING_MAXLENGTH, string_traits<e_char_t, std_char_traits<e_char_t> > > error_string_a;
typedef basic_error_string< e_wchar_t, EXTL_STRING_ERROR_STRING_MAXLENGTH, string_traits<e_wchar_t, std_char_traits<e_wchar_t> > > error_string_w;
typedef basic_error_string< e_tchar_t, EXTL_STRING_ERROR_STRING_MAXLENGTH, string_traits<e_tchar_t, std_char_traits<e_tchar_t> > > error_string;
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_ERROR_STRING_H */
/* //////////////////////////////////////////////////////////////////// */
