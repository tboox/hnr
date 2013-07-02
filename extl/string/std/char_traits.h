/* ///////////////////////////////////////////////////////////////////////
 * File:		char_traits.h		
 *
 * Created:		08.03.21					
 * Updated:		08.04.14	
 *
 * Brief: std_char_traits class which is compatible with std
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_STD_CHAR_TRAITS_H
#define EXTL_STRING_STD_CHAR_TRAITS_H

/*!\file char_traits.h
 * \brief std_char_traits class which is compatible with std
 */
#ifndef __cplusplus
#	error error_string.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

#ifndef EXTL_NO_STL
#	if EXTL_WORKAROUND_BORLAND(<=, 0x551)
#		include <traits.h>
#	else
#		include <string>
#	endif
#endif

#include "../../memory/prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

#if defined(EXTL_NO_STL)

/*!\brief std_char_traits class which is compatible with std
 *
 * \param C the character type
 *
 * \ingroup extl_group_string
 */
template < typename_param_k C >
struct std_char_traits
{
	/// \name Types
	/// @{
	public:
		typedef std_char_traits<C>		class_type;
		typedef C						char_type; 
		typedef	e_size_t				size_type;
		typedef	e_int_t					int_type;
	/// @}

	public:
		/// assignment 
		static void assign(char_type &lhs, char_type const& rhs)
		{
			lhs = rhs;
		}

		/// assignment without the null-terminator 
		static char_type const* assign(char_type *dest, size_type n, char_type const& c)
		{
			char_type* ret = dest;
			EXTL_ASSERT(NULL != dest);

			for(; n > 0; --n, ++dest)
			{
				assign(*dest, c);
			}

			return ret;
		}

		/// equal than 
		static e_bool_t eq(char_type const& lhs, char_type const& rhs)
		{
			return lhs == rhs;
		}

		/// less than 
		static e_bool_t lt(char_type const& lhs, char_type const& rhs)
		{
			return lhs < rhs;
		}

		/// compare string 
		static e_int_t compare(char_type const* lhs, char_type const* rhs, size_type n)
		{
			EXTL_ASSERT(NULL != lhs);
			EXTL_ASSERT(NULL != rhs);

			for(size_type i = 0; i < n; ++i, ++lhs, ++rhs)
			{
				if(!eq(*lhs, *rhs))
				{
					return lt(*lhs, *rhs)? -1 : + 1;
				}
			}
			return 0;
		}

		/// get the length of s 
		static size_type length(char_type const* s)
		{
			EXTL_ASSERT(NULL != s);

			size_type	n = 0;

			while(!is_nt(*s))
			{
				++n;
				++s;
			}
			return n;
		}

		/// copy string without the null-terminator 
		static char_type const* copy(char_type* dest, char_type const* src, size_type n)
		{
			EXTL_ASSERT(NULL != dest);
			EXTL_ASSERT(NULL != src);

			char_type* ret = dest;
			for(; n > 0; --n, ++dest, ++src)
			{
				assign(*dest, *src);
			}

			return ret;
		}

		/// find 
		static char_type const* find(char_type const* s, size_type n, char_type const& c)
		{
		    EXTL_ASSERT(0 == n || NULL != s);

			for(; 0 < n; --n, ++s)
			{
				if(eq(*s, c))
				{
					break;
				}
			}
			return (0 < n) ? s : NULL;
		}

		/// move string 
		static char_type const* move(char_type* dest, char_type const* src, size_type n)
		{
			char_type *p = dest;
			if (src < p && p < src + n) /* overlap */
				for (p += n, src += n; 0 < n; --n)
					assign(*--p, *--src);
			else
				for (; 0 < n; --n, ++p, ++src)
					assign(*p, *src);
			return dest;
		}

		/// conversion:e_int_t ==> char_type 
		static char_type to_char_type(e_int_t	const& c)
		{
			return static_cast<char_type>(c);
		}

		/// conversion:char_type ==> e_int_t 
		static e_int_t to_int_type(char_type	const& c)
		{
			return static_cast<e_int_t>(c);
		}

		/// compare int type 
		static e_bool_t eq_int_type(int_type const& lhs, int_type const& rhs)
		{
		   return lhs == rhs;
		}

		/// the end of file 
		static e_int_t eof()
		{
			return static_cast<e_int_t>(-1);
		}

		/// evaluate whether c is the end of file 
		static e_int_t not_eof(e_int_t	const& c)
		{
			return (c != eof() ? c : !eof());
		}

	private:
		/// evaluate whether c is null-terminator  
		static e_bool_t is_nt(char_type const& c)
		{
			return eq(c, static_cast<char_type>(0));
		}
}; 

/* ///////////////////////////////////////////////////////////////////////
 * optimize e_char_t,e_wchar_t 
 */
#	if !defined(EXTL_COMPILER_IS_DMC) && \
			!defined(EXTL_COMPILER_IS_WATCOM)

EXTL_TEMPLATE_SPECIALISATION
inline e_char_t const* std_char_traits<e_char_t>::assign(e_char_t *dest, size_type n, e_char_t const& c)
{
	return static_cast<e_char_t*>(mem_fill(&dest[0], c, n * sizeof(e_char_t)));
}
EXTL_TEMPLATE_SPECIALISATION
inline std_char_traits<e_char_t>::
size_type std_char_traits<e_char_t>::length(e_char_t const* str)
{
	return std_strlen_a(str);
}
EXTL_TEMPLATE_SPECIALISATION
inline std_char_traits<e_wchar_t>::
size_type std_char_traits<e_wchar_t>::length(e_wchar_t const* str)
{
	return std_strlen_w(str);
}

EXTL_TEMPLATE_SPECIALISATION
inline e_char_t const* std_char_traits<e_char_t>::copy(e_char_t* dest, e_char_t const* src, size_type n)
{
	return pod_copy_n(dest, src, n);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_wchar_t const* std_char_traits<e_wchar_t>::copy(e_wchar_t* dest, e_wchar_t const* src, size_type n)
{
	return pod_copy_n(dest, src, n);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_char_t const* std_char_traits<e_char_t>::move(e_char_t* dest, e_char_t const* src, size_type n)
{
	return pod_move_n(&dest[0], &src[0], n);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_wchar_t const* std_char_traits<e_wchar_t>::move(e_wchar_t* dest, e_wchar_t const* src, size_type n)
{
	return pod_move_n(&dest[0], &src[0], n);
}
EXTL_TEMPLATE_SPECIALISATION
inline e_int_t std_char_traits<e_char_t>::compare(e_char_t const* lhs, e_char_t const* rhs, size_type n)
{
	return mem_cmp(&lhs[0], &rhs[0], n * sizeof(e_char_t));
}

#	endif /* !defined(EXTL_COMPILER_IS_DMC) && \
				!defined(EXTL_COMPILER_IS_WATCOM) */

/* //////////////////////////////////////////////////////////////////// */
#else 
/*!\brief std_char_traits class which is compatible with std
 *
 * \param C the character type
 *
 * \ingroup extl_group_string
 */
template < typename_param_k C >
struct std_char_traits
	: public EXTL_NS_STD(char_traits)<C>
{
	private:
		typedef EXTL_NS_STD(char_traits)<C>								base_type;
	public:
		typedef std_char_traits<C>										class_type;
		typedef typename_type_k base_type::char_type					char_type; 
		typedef e_size_t												size_type; 
		typedef typename_type_k base_type::char_type					int_type; 
};
#endif /* defined(EXTL_NO_STL) */
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_STRING_STD_CHAR_TRAITS_TEST_ENABLE
#	include "unit_test/char_traits_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_STD_CHAR_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
