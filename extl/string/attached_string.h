/* ///////////////////////////////////////////////////////////////////////
 * File:		attached_string.h		
 *
 * Created:		08.06.14					
 * Updated:		08.06.14
 *
 * Brief: attached_string class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_ATTACHED_STRING_H
#define EXTL_STRING_ATTACHED_STRING_H

/*!\file attached_string.h
 * \brief attached_string class
 */

#ifndef __cplusplus
#	error attached_string.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "string_base.h"
#include "../memory/attached_buffer.h"

/* ///////////////////////////////////////////////////////////////////////
 * The maximum value of the storage space in the attached_string
 */
#define EXTL_STRING_ATTACHED_STRING_MAX_SPACE	256

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief basic_attached_string class
 *
 * \param C		The character type
 * \param MAX_SPACE The maximum size of the storage space of the attached string
 * \param T		The traits type of character string. Default param is string_traits<C, std_char_traits<C> > 
 *
 * \ingroup extl_group_string
 */
template<	typename_param_k	C
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t MAX_SPACE = EXTL_STRING_ATTACHED_STRING_MAX_SPACE
		,	typename_param_k	T		= string_traits<C> 
#else	
		,	e_size_t MAX_SPACE
		,	typename_param_k	T
#endif
		>
class basic_attached_string
	: public string_base<	basic_attached_string<C, MAX_SPACE, T>
						,	T
						,	attached_buffer	<	C
											,	MAX_SPACE + 1
											,	typename_type_k memory_traits_selector<C>::memory_traits_type
											>
						>	
{
	
	/// \name Types
	/// @{
	public:
		typedef basic_attached_string<C, MAX_SPACE, T>						class_type;
		typedef attached_buffer	<	C
								,	MAX_SPACE + 1
								,	typename_type_k memory_traits_selector<C>::memory_traits_type
								>											buffer_type;
		typedef string_base< class_type, T, buffer_type >					base_type;
		typedef typename_type_k buffer_type::allocator_type					allocator_type;
		typedef typename_type_k base_type::value_type						value_type;
		typedef typename_type_k base_type::string_traits_type				string_traits_type;
		typedef typename_type_k base_type::char_type						char_type;
		typedef typename_type_k base_type::pointer							pointer;
		typedef typename_type_k base_type::const_pointer					const_pointer;
		typedef typename_type_k base_type::reference						reference;
		typedef typename_type_k base_type::const_reference					const_reference;
		typedef typename_type_k base_type::iterator							iterator;
		typedef typename_type_k base_type::const_iterator					const_iterator;
		typedef typename_type_k base_type::reverse_iterator					reverse_iterator;
		typedef typename_type_k base_type::const_reverse_iterator			const_reverse_iterator;
		typedef typename_type_k base_type::size_type						size_type;
		typedef typename_type_k base_type::bool_type						bool_type;
		typedef typename_type_k base_type::difference_type					difference_type;
		typedef typename_type_k base_type::int_type							int_type;
	/// @}

	public:
	#if defined(EXTL_COMPILER_IS_DMC) 
		EXTL_OPERATORS_CMP_1_2_(class_type const&, const_pointer)
		/* EXTL_OPERATORS_ADD_1_2_(class_type, const_pointer) */
		friend class_type operator+(class_type const& lhs, class_type const& rhs)
		{ basic_attached_string<C, MAX_SPACE, T> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(class_type const& lhs, const_pointer rhs)
		{ basic_attached_string<C, MAX_SPACE, T> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(const_pointer lhs, class_type const& rhs)
		{ basic_attached_string<C, MAX_SPACE, T> ret(rhs); ret += lhs; return ret;	}
	#endif

	/// \name Friends
	/// @{
	private:
		friend class string_base< class_type, T, buffer_type >;
	/// @}

	/// \name Construction
	/// @{
	public:
		/// The Default Constructor
		basic_attached_string()
			: base_type()
		{
		}
		/// Constructs from the given c-style string
		explicit_k basic_attached_string(const_pointer s)
			: base_type()
		{
			attach(s);
		}
		/// Attaches a given c-style string with n characters at the specified position
		basic_attached_string(const_pointer s, size_type n, size_type pos = 0)
			: base_type()
		{
			attach(s, n, pos);
		}
		/// Attaches a given string
		basic_attached_string(class_type const& s)
			: base_type()
		{
			attach(s);
		}
		/// Attaches a given string with n characters at the specified position
		basic_attached_string(class_type const& s, size_type n, size_type pos = 0)
			: base_type()
		{
			attach(s, n, pos);
		}

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

	/// \name Attach and Detach
	/// @{
	public:
		/// Attaches a given string
		void attach(const_pointer s)
		{
			EXTL_ASSERT(is_valid());
			if (NULL == s) this->buffer().detach();

			size_type n = string_traits_type::length(s);
			this->buffer().attach(s, n > 0? n + 1 : 0);
			this->set_eos(base_type::length());

			EXTL_ASSERT(is_valid());
		}
		/// Attaches a given string with n characters at the specified position
		void attach(const_pointer s, size_type n, size_type pos = 0)
		{
			EXTL_ASSERT(is_valid());
			this->buffer().attach(s + pos, n > 0? n + 1 : 0);
			this->set_eos(base_type::length());
			EXTL_ASSERT(is_valid());
		}
		/// Attaches a given string
		void attach(class_type const& s)
		{
			EXTL_ASSERT(is_valid());
			this->buffer().attach(s.c_str(), s.size() > 0? s.size() + 1 : 0);
			this->set_eos(base_type::length());
			EXTL_ASSERT(is_valid());
		}
		/// Attaches a given string with n characters at the specified position
		void attach(class_type const& s, size_type n, size_type pos = 0)
		{
			EXTL_ASSERT(is_valid());
			this->buffer().attach(s.c_str(), n > 0? n + 1 : 0, n > 0? pos : 0);
			this->set_eos(base_type::length());
			EXTL_ASSERT(is_valid());
		}
		/// Detaches the current buffer
		const_pointer detach()
		{
			EXTL_ASSERT(is_valid());
			const_pointer p = this->buffer().detach();
			EXTL_ASSERT(is_valid());
			return p;
		}
	/// @}

	/// \name Others
	/// @{
	private:
		/// Invariance
		bool_type is_valid() const
		{
			size_type length = this->length();
			const_pointer data = this->data();

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
typedef basic_attached_string< e_char_t > attached_string_a;
typedef basic_attached_string< e_wchar_t > attached_string_w;
typedef basic_attached_string< e_tchar_t > attached_string;
#else
typedef basic_attached_string	<	e_char_t
								,	EXTL_STRING_ATTACHED_STRING_MAX_SPACE
								,	string_traits<e_char_t, std_char_traits<e_char_t> >
								>	attached_string_a;
typedef basic_attached_string	<	e_wchar_t
								,	EXTL_STRING_ATTACHED_STRING_MAX_SPACE
								,	string_traits<e_wchar_t, std_char_traits<e_wchar_t> >
								>	attached_string_w;
typedef basic_attached_string	<	e_tchar_t
								,	EXTL_STRING_ATTACHED_STRING_MAX_SPACE
								,	string_traits<e_tchar_t, std_char_traits<e_tchar_t> >
								>	attached_string;
#endif
/// @}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_ATTACHED_STRING_H */
/* //////////////////////////////////////////////////////////////////// */
