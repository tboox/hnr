/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_string.h		
 *
 * Created:		08.05.11					
 * Updated:		08.05.11	
 *
 * Brief: scoped_string class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_SCOPED_STRING_H
#define EXTL_STRING_SCOPED_STRING_H

/*!\file scoped_string.h
 * \brief scoped_string class
 */

#ifndef __cplusplus
#	error scoped_string.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "string_base.h"
#include "../memory/scoped_buffer.h"

/* ///////////////////////////////////////////////////////////////////////
 * The grow size in the scoped_string
 */
#ifdef EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE
#	define EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE		EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE
#else
#	define EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE		(32)
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief basic_scoped_string class
 *
 * \param C		The character type
 * \param GrowN	The grow size
 * \param T		The traits type of character string. Default param is string_traits<C, std_char_traits<C> > 
 * \param A		The allocator type. 
 *
 * \ingroup extl_group_string
 */
template<	typename_param_k	C
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t			GrowN	= EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE
		,	typename_param_k	T		= string_traits<C> 
		,	typename_param_k	A		= typename_type_def_k allocator_selector<C>::allocator_type
#else
		,	e_size_t			GrowN 
		,	typename_param_k	T
		,	typename_param_k	A
#endif
		>
class basic_scoped_string
	: public string_base<	basic_scoped_string<C, GrowN, T, A>
						,	T
						,	scoped_buffer	<	C
											,	GrowN
											,	A
											,	typename_type_k memory_traits_selector<C>::memory_traits_type
											,	typename_type_k initialiser_selector<C>::initialiser_type 
											>
						>	
{
	
	/// \name Types
	/// @{
	public:
		typedef scoped_buffer	<	C
								,	GrowN
								,	A
								,	typename_type_k memory_traits_selector<C>::memory_traits_type
								,	typename_type_k initialiser_selector<C>::initialiser_type
								>													buffer_type;
		typedef basic_scoped_string<C, GrowN, T, A>									class_type;
		typedef string_base<class_type, T, buffer_type>								base_type;
		typedef typename_type_k buffer_type::allocator_type							allocator_type;
		typedef typename_type_k base_type::value_type								value_type;
		typedef typename_type_k base_type::string_traits_type						string_traits_type;
		typedef typename_type_k base_type::char_type								char_type;
		typedef typename_type_k base_type::pointer									pointer;
		typedef typename_type_k base_type::const_pointer							const_pointer;
		typedef typename_type_k base_type::reference								reference;
		typedef typename_type_k base_type::const_reference							const_reference;
		typedef typename_type_k base_type::iterator									iterator;
		typedef typename_type_k base_type::const_iterator							const_iterator;
		typedef typename_type_k base_type::reverse_iterator							reverse_iterator;
		typedef typename_type_k base_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename_type_k base_type::size_type								size_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k base_type::difference_type							difference_type;
		typedef typename_type_k base_type::int_type									int_type;
	/// @}

	public:
	#if defined(EXTL_COMPILER_IS_DMC) 
		EXTL_OPERATORS_CMP_1_2_(class_type const&, const_pointer)
		/* EXTL_OPERATORS_ADD_1_2_(class_type, const_pointer) */
		friend class_type operator+(class_type const& lhs, class_type const& rhs)
		{ basic_scoped_string<C, GrowN, T, A> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(class_type const& lhs, const_pointer rhs)
		{ basic_scoped_string<C, GrowN, T, A> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(const_pointer lhs, class_type const& rhs)
		{ basic_scoped_string<C, GrowN, T, A> ret(rhs); ret += lhs; return ret;	}
	#endif

	/// \name Friends
	/// @{
	private:
		friend class string_base< class_type, T, buffer_type >;
	/// @}

	/// \name Construction
	/// @{
	public:
		/// Default Constructor 
		basic_scoped_string()
			: base_type()
		{
		}
		/// Constructs from the given c-style string
		explicit_k basic_scoped_string(const_pointer s)
			: base_type(s)
		{
		}
		/// Constructs with n characters from the given c-style string at the specified position 
		basic_scoped_string(const_pointer s, size_type n, size_type pos = 0)
			: base_type(s, n, pos)
		{
		}

		/// Constructs from the given string 
		basic_scoped_string(class_type const& s)
			: base_type(s)
		{
		}

		/// Constructs with n characters from the given string at the specified position 
		basic_scoped_string(class_type const& s, size_type n, size_type pos = 0)
			: base_type(s, n, pos)
		{
		}
		/// Constructs with n characters
		/*explicit_k basic_scoped_string(const_reference ch, size_type n = 1)
			: base_type(ch, n)
		{
		}*/

		/// Constructs from range [first, last) with the const pointer
		basic_scoped_string(const_pointer first, const_pointer last)
			: base_type(first, last)
		{
		}
		/// Constructs from range [first, last) with the const iterator
		basic_scoped_string(const_iterator first, const_iterator last)
			: base_type(first, last)
		{
		}
		/// Constructs from range [first, last) with the const reverse iterator
		basic_scoped_string(const_reverse_iterator first, const_reverse_iterator last)
			: base_type(first, last)
		{
		}
	#if defined(EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT) \
			&& !defined(EXTL_COMPILER_IS_DMC)
		/// Constructs from range [first, last) with the input iterator
		template < typename_param_k _InIt >
		basic_scoped_string(_InIt first, _InIt last)
			: base_type(first, last)
		{
		}
	#endif

	/// @}

	/// \name Operators
	/// @{
	public:
	#if defined(EXTL_COMPILER_IS_MSVC) && _MSC_VER == 1200
		using base_type::operator==;
	#endif
		class_type& operator=(class_type const& s)		{ return base_type::operator=(s);	}
		class_type& operator=(const_pointer s)			{ return base_type::operator=(s);	}
		class_type& operator=(const_reference v)		{ return base_type::operator=(v);	}
	/// @}

	/// \name Others
	/// @{
	private:
		/// Invariance
		bool_type is_valid() const
		{
			size_type length = base_type::length();
			const_pointer data = base_type::data();

			if (length < 0) return e_false_v;

			if (NULL != data)
			{
				/* The string is cut off */
				for (size_type i = 0; i < length; ++i)
				{
					if(char_type('\0') == data[i])
						return e_false_v;
				}
				/* The string is not null-terminated */
				if (char_type('\0') != data[length]) 
				{
					return e_false_v;
				}
			}
			return e_true_v;
		}
	/// @}

};

/// \name Types
/// @{
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
typedef basic_scoped_string< e_char_t > scoped_string_a;
typedef basic_scoped_string< e_wchar_t > scoped_string_w;
typedef basic_scoped_string< e_tchar_t > scoped_string;
#else
typedef basic_scoped_string	<	e_char_t
							,	EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE
							,	string_traits<e_char_t, std_char_traits<e_char_t> >
							,	allocator_selector<e_char_t>::allocator_type 
							>	scoped_string_a;
typedef basic_scoped_string	<	e_wchar_t
							,	EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE
							,	string_traits<e_wchar_t, std_char_traits<e_wchar_t> >
							,	allocator_selector<e_wchar_t>::allocator_type
							>	scoped_string_w;
typedef basic_scoped_string	<	e_tchar_t
							,	EXTL_STRING_SCOPED_STRING_DEFAULT_GROW_SIZE
							,	string_traits<e_tchar_t, std_char_traits<e_tchar_t> >
							,	allocator_selector<e_tchar_t>::allocator_type
							>	scoped_string;
#endif
/// @}


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_SCOPED_STRING_H */
/* //////////////////////////////////////////////////////////////////// */
