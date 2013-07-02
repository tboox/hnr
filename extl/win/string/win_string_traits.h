/* ///////////////////////////////////////////////////////////////////////
 * File:		win_string_traits.h		
 *
 * Created:		08.06.13				
 * Updated:		08.06.13
 *
 * Brief: win_string_traits class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WIN_STRING_WIN_STRING_TRAITS_H
#define EXTL_PLATFORM_WIN_STRING_WIN_STRING_TRAITS_H

/*!\file win_string_traits.h
 * \brief win_string_traits class
 */

#ifndef __cplusplus
#	error win_string_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../win.h"
#include "../../string/prefix.h"
#include "../../string/std/char_traits.h"
#include "../../type/traits/is_unsigned.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE 

/*!\brief win_string_traits class
 *
 * \param C the character type
 * \param T the char_traits type
 *
 * \ingroup extl_group_string
 */
template<	typename_param_k C
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k T = std_char_traits<C>
#else
		,	typename_param_k T 
#endif
		>
struct win_string_traits
{
	public:
		typedef win_string_traits<C, T>									class_type;
		typedef T														char_traits_type;
		typedef typename_type_k char_traits_type::char_type				char_type; 
		typedef	typename_type_k char_traits_type::size_type				size_type;
		typedef	typename_type_k char_traits_type::int_type				int_type;
		typedef char_type												value_type;
		typedef value_type*												pointer;
		typedef value_type const*										const_pointer;
		typedef value_type&												reference;
		typedef value_type const&										const_reference;
	
	public:
		/// Evaluate whether c is null-terminator 
		static e_bool_t is_nt(const_reference c)
		{
			return eq(c, char_type('\0'));
		}

		/// Compare string 
		static e_bool_t eq(const_reference lhs, const_reference rhs)
		{
			return char_traits_type::eq(lhs, rhs);
		}

		/// Less than  
		static e_bool_t lt(const_reference lhs, const_reference rhs)
		{
			return char_traits_type::lt(lhs, rhs);
		}

		/// Make the lower character 
		static char_type to_lower(const_reference c)
		{
			if((char_type('A') <= c) && (c <= char_type('Z')))
				return static_cast<char_type>(static_cast<e_int_t>(c) + 32);
			else return c;
		}

		/// Make the upper character 
		static char_type to_upper(const_reference c)
		{
			if((char_type('a') <= c) && (c <= char_type('z')))
				return static_cast<char_type>(static_cast<e_int_t>(c) - 32);
			else return c;
		}

		/// Assignment 
		static const_pointer assign(pointer dest, const_reference c, size_type n)
		{
			return char_traits_type::assign(dest, n, c);
		}
		/// Copy string 
		static const_pointer copy(pointer dest, const_pointer src, size_type n)
		{
			return char_traits_type::copy(dest, src, n);
		}

		/// Copy string 
		static const_pointer copy(pointer dest, const_pointer src)
		{
			EXTL_ASSERT(NULL != dest);
			EXTL_ASSERT(NULL != src);

			pointer ret = dest;
			for(; !is_nt(*src); ++dest, ++src)
			{
				char_traits_type::assign(*dest, *src);
			}
			return ret;
		}

		/// Finds the given character with value c from the given string 
		static const_pointer find(const_pointer s, size_type n, const_reference c)
		{
			return char_traits_type::find(s, n, c);
		}

		/// Finds the given string from the given string at the specified position 
		static size_type find(const_pointer s, size_type n, size_type pos, const_pointer sub, size_type sub_n)
		{
			EXTL_ASSERT(NULL != s);
			EXTL_ASSERT(NULL != sub);
			if(NULL == s) return fof();
			if(NULL == sub || 0 == sub_n) return (pos <= n)? pos : n;

			size_type num = n - pos;
			if(pos < n && sub_n <= num)
			{
				num -= sub_n - 1;
				const_pointer p1 = s + pos;

				/* Finds the position of the first character of the string sub in the s */
				const_pointer p2;
				while(p2 = find(p1, num, *sub), p2 !=NULL)
				{
					num -= p2 - p1 + 1;
					p1 = p2 + 1;

					/* Compares the whole string */
					if(!compare(p1, sub + 1, sub_n - 1)) /* optimization */
					/* if(!traits_type::compare(p2, sub, sub_n)) */
						return (p2 - s);
				}
			}
			return fof();
		}
		/// Reversely finds the given string from the given string at the specified position 
		static size_type rfind(const_pointer s, size_type n, size_type rpos, const_pointer sub, size_type sub_n)
		{
			EXTL_ASSERT(NULL != s);
			EXTL_ASSERT(NULL != sub);
			if(NULL == s) return fof();

			/* compute position from the given reverse position */
			size_type pos = n - rpos;
			if(NULL == sub || 0 == sub_n) return (pos < n)? pos : n;
		
			if(sub_n <= n)
			{
				const_pointer p = s + ((pos < n - sub_n)? pos : (n - sub_n));
				while(p != s)
				{
					if(eq(*p, *sub) && 
						/* compare(p + 1, sub + 1, sub_n - 1)) */
						!compare(p, sub, sub_n))
						return p - s;
					--p;
				}
			}
			return fof();
		}

		/// Compare string 
		static e_int_t compare(const_pointer lhs, const_pointer rhs, size_type n)
		{
			return char_traits_type::compare(lhs, rhs, n);
		}

		/// Compare string 
		static e_int_t compare(const_pointer lhs, const_pointer rhs)
		{
			EXTL_ASSERT(NULL != lhs);
			EXTL_ASSERT(NULL != rhs);

			for(; !is_nt(*lhs) || !is_nt(*rhs); ++lhs, ++rhs)
			{
				if(!eq(*lhs, *rhs))
				{
					return lt(*lhs, *rhs)? -1 : + 1;
				}
			}
			return 0;
		}

		/// Compare the given n characters string(case-insensitive) 
		static e_int_t compare_nocase(const_pointer lhs, const_pointer rhs, size_type n)
		{
			EXTL_ASSERT(NULL != lhs);
			EXTL_ASSERT(NULL != rhs);

			for(size_type i = 0; i < n; ++i, ++lhs, ++rhs)
			{
				char_type lch = to_lower(*lhs);
				char_type rch = to_lower(*rhs);
				if(!eq(lch, rch))
				{
					return lt(lch, rch)? -1 : + 1;
				}
			}
			return 0;
		}

		/// Compare string(case-insensitive) 
		static e_int_t compare_nocase(const_pointer lhs, const_pointer rhs)
		{
			EXTL_ASSERT(NULL != lhs);
			EXTL_ASSERT(NULL != rhs);

			for(; !is_nt(*lhs) || !is_nt(*rhs); ++lhs, ++rhs)
			{
				char_type lch = to_lower(*lhs);
				char_type rch = to_lower(*rhs);
				if(!eq(lch, rch))
				{
					return lt(lch, rch)? -1 : + 1;
				}
			}
			return 0;
		}

		/// Move string 
		static const_pointer move(pointer dest, const_pointer src, size_type n)
		{
			return char_traits_type::move(dest, src, n);
		}
		
		/// Get the length of the given string 
		static size_type length(const_pointer s)
		{
			return char_traits_type::length(s);
		}

		/// Make lower string 
		static const_pointer to_lower(pointer s)
		{
			pointer p = s;
			while(*p != char_type('\0'))
			{
				*p = to_lower(*p);
				++p;
			}
			return s;
		}

		/// Make upper string 
		static const_pointer to_upper(pointer s)
		{
			C* p = s;
			while(*p != char_type('\0'))
			{
				*p = to_upper(*p);
				++p;
			}
			return s;
		}

		/// Evaluate whether the given string is empty 
		static e_bool_t is_empty(const_pointer s)
		{
			return eq(s[0], char_type('\0'));
		}

		/// The maximum length of character string 
		static size_type max_length()								
		{	
			EXTL_MUST_BE_UNSIGNED(size_type);
			return static_cast<size_type>(-1);						
		}
		
		/// The failure to find 
		static size_type fof()																		
		{	
			return max_length();					
		}

		/// Returns the empty strig
		static const_pointer empty()
		{
			static const char_type empty_str[1] = { '\0' };
			return empty_str;
		}
}; 

/* ///////////////////////////////////////////////////////////////////////
 * Optimization
 */
#if !defined(EXTL_COMPILER_IS_DMC) && \
		!defined(EXTL_COMPILER_IS_WATCOM)

EXTL_TEMPLATE_SPECIALISATION
inline e_char_t const* win_string_traits<e_char_t>::copy(e_char_t* dest, e_char_t const* src)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(NULL != src);
	return ::lstrcpyA(dest, src);
}

EXTL_TEMPLATE_SPECIALISATION
inline e_wchar_t const* win_string_traits<e_wchar_t>::copy(e_wchar_t* dest, e_wchar_t const* src)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(NULL != src);
	return ::lstrcpyW(dest, src);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_char_t const* win_string_traits<e_char_t>::copy(e_char_t* dest, e_char_t const* src, size_type n)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(NULL != src);
	return ::strncpy(dest, src, n);
}

EXTL_TEMPLATE_SPECIALISATION
inline e_wchar_t const* win_string_traits<e_wchar_t>::copy(e_wchar_t* dest, e_wchar_t const* src, size_type n)
{
	EXTL_ASSERT(NULL != dest);
	EXTL_ASSERT(NULL != src);
	return ::wcsncpy(dest, src, n);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_int_t win_string_traits<e_char_t>::compare(e_char_t const* lhs, e_char_t const* rhs)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);
	return ::lstrcmpA(lhs, rhs);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_int_t win_string_traits<e_wchar_t>::compare(e_wchar_t const* lhs, e_wchar_t const* rhs)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);
	return ::lstrcmpW(lhs, rhs);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_int_t win_string_traits<e_char_t>::compare(e_char_t const* lhs, e_char_t const* rhs, size_type n)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);
	return ::strncmp(lhs, rhs, n);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_int_t win_string_traits<e_wchar_t>::compare(e_wchar_t const* lhs, e_wchar_t const* rhs, size_type n)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);
	return ::wcsncmp(lhs, rhs, n);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_int_t win_string_traits<e_char_t>::compare_nocase(e_char_t const* lhs, e_char_t const* rhs)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);
	return ::lstrcmpiA(lhs, rhs);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_int_t win_string_traits<e_wchar_t>::compare_nocase(e_wchar_t const* lhs, e_wchar_t const* rhs)
{
	EXTL_ASSERT(NULL != lhs);
	EXTL_ASSERT(NULL != rhs);
	return ::lstrcmpiW(lhs, rhs);
}
EXTL_TEMPLATE_SPECIALISATION
inline win_string_traits<e_char_t>::
size_type win_string_traits<e_char_t>::length(e_char_t const* s)
{
	EXTL_ASSERT(NULL != s);
	return static_cast<size_type>(::lstrlenA(s));
}
EXTL_TEMPLATE_SPECIALISATION
inline win_string_traits<e_wchar_t>::
size_type win_string_traits<e_wchar_t>::length(e_wchar_t const* s)
{
	EXTL_ASSERT(NULL != s);
	return static_cast<size_type>(::lstrlenW(s));
}
#endif /* !defined(EXTL_COMPILER_IS_DMC) && \
			!defined(EXTL_COMPILER_IS_WATCOM) */

/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_STRING_STRING_TRAITS_TEST_ENABLE
#	include "unit_test/string_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_STRING_WIN_STRING_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
