 /* ///////////////////////////////////////////////////////////////////////
 * File:		string_base.h		
 *
 * Created:		08.05.11					
 * Updated:		08.05.11	
 *
 * Brief: The implementation of string operation
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_STRING_STRING_BASE_H
#define EXTL_STRING_STRING_BASE_H

/*!\file scoped_string.h
 * \brief The implementation of string operation
 */

#ifndef __cplusplus
#	error string_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "string_traits.h"
#include "../algorithm/algorithm.h" 
#include "../math/math.h" 
#include "../utility/operators.h"
#include "../utility/element_num.h"
#include "../iterator/iterator.h"
#include "../utility/suppress_unused.h"
#include "../conversion/conversion.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief The implementation of string operation 
 *
 * \param D The derived type
 * \param T The traits type of character string. Default param is string_traits<C, std_char_traits<C> > 
 * \param B The buffer type
 *
 * \ingroup extl_group_string
 */
template<	typename_param_k	D
		,	typename_param_k	T 
		,	typename_param_k	B 
		>
class string_base
#ifndef EXTL_COMPILER_IS_DMC 
/* operators: > >= <= != + */
	: private operators_cmp_1_2_<D, typename_type_k B::const_pointer,
					operators_add_1_2_<	D, typename_type_k B::const_pointer
						#ifndef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
							,operators_base_< D >
						#endif
			> > 
#endif
{
	/// \name Types
	/// @{
	public:
		typedef string_base<D, T, B>												class_type;
		typedef D																	derived_type;
		typedef B																	buffer_type;
		typedef typename_type_k buffer_type::allocator_type							allocator_type;
		typedef T																	string_traits_type;
		typedef typename_type_k buffer_type::value_type								char_type;
		typedef typename_type_k buffer_type::value_type								value_type;
		typedef typename_type_k buffer_type::pointer								pointer;
		typedef typename_type_k buffer_type::const_pointer							const_pointer;
		typedef typename_type_k buffer_type::reference								reference;
		typedef typename_type_k buffer_type::const_reference						const_reference;
		typedef typename_type_k buffer_type::iterator								iterator;
		typedef typename_type_k buffer_type::const_iterator							const_iterator;
		typedef typename_type_k buffer_type::reverse_iterator						reverse_iterator;
		typedef typename_type_k buffer_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename_type_k buffer_type::size_type								size_type;
		typedef typename_type_k buffer_type::bool_type								bool_type;
		typedef typename_type_k buffer_type::difference_type						difference_type;
		typedef	e_int_t																int_type;
	/// @}

	/// \name Members
	/// @{
	private:
		buffer_type																	m_buffer;
	/// @}

	/// \name Constructors
	/// @{
	public:
		/// Default Constructor 
		string_base()
			: m_buffer()	
		{
			EXTL_ASSERT(0 == length());
			EXTL_ASSERT(derive().is_valid());
		}
		/// Constructs from the given c-style string
		explicit_k string_base(const_pointer s)
			: m_buffer(s, (NULL != s)? (string_traits_type::length(s) + 1) : 0)
		{
			set_eos(length());
			EXTL_ASSERT(derive().is_valid());
		}
		/// Constructs with n characters from the given c-style string at the specified position 
		string_base(const_pointer s, size_type n, size_type pos = 0)
			: m_buffer(s, n + 1, pos)
		{
			EXTL_ASSERT(n == length());
			set_eos(length());
			EXTL_ASSERT(derive().is_valid());
		}

		/// Constructs from the given string 
		string_base(derived_type const& s) 
			: m_buffer(s.c_str(), s.length() + 1)
		{
			EXTL_ASSERT(s.length() == length());
			set_eos(length());
			EXTL_ASSERT(derive().is_valid());
		}

		/// Constructs with n characters from the given string at the specified position 
		string_base(derived_type const& s, size_type n, size_type pos = 0)
			: m_buffer(s.c_str(), n + 1, pos)
		{
			EXTL_ASSERT(n == length());
			set_eos(length());
			EXTL_ASSERT(derive().is_valid());
		}

		/// Constructs with n characters
		/*explicit_k string_base(const_reference ch, size_type n = 1)
			: m_buffer(ch, n + 1)
		{
			EXTL_ASSERT(n == length());
			set_eos(length());
			EXTL_ASSERT(derive().is_valid());
		}*/
		/// Constructs from range [first, last) with the const pointer
		string_base(const_pointer first, const_pointer last)
			: m_buffer(first, ++last)
		{
		}
		/// Constructs from range [first, last) with the const iterator
		string_base(const_iterator first, const_iterator last)
			: m_buffer(first, ++last)
		{
		}
		/// Constructs from range [first, last) with the const reverse iterator
		string_base(const_reverse_iterator first, const_reverse_iterator last)
			: m_buffer(first, ++last)
		{
		}
	#if defined(EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT) \
			&& !defined(EXTL_COMPILER_IS_DMC)
		/// Constructs from range [first, last) with the input iterator
		template < typename_param_k _InIt >
		string_base(_InIt first, _InIt last)
			: m_buffer(first, ++last)
		{
		}
	#endif

		/*!\brief Prohibit the following case:
		 * 
		 * \code
			D da, db;
			B &ba = da, &bb = db;
			B b(ba);
		 * \endcode
		 */
	private:
		string_base(class_type const&);
	/// @}

	/// \name Acccessors
	/// @{
	public:
		/// Returns the pointer to the storage in the string
		pointer			data() 					{ return buffer().data();	}
		/// Returns the pointer to the storage in the string
		const_pointer	data() const			{ return buffer().data();	}
		/// Returns the pointer to the c-style string with null-terminator
		const_pointer	c_str() const			{ return buffer().data();	}
		/// Returns the length of string
		size_type		size() const			{ return (buffer().size() > 0)? buffer().size() - 1 : 0;		}
		/// Returns the size of reserved storage in the string
		size_type		capacity() const		{ return (buffer().size() > 0)? buffer().capacity() - 1 : 0;	}
		/// Returns the length of string
		size_type		length() const			{ return derive().size();	}
		/// Indicates whether the string is empty
		bool_type		is_empty() const		{ return (derive().size() > 0)? e_false_v : e_true_v;	}
		/// Indicates whether the string is empty for comparability
		bool_type		empty() const			{ return derive().is_empty() ;	}
		/// Gets the substring with n characters from the left direction at the specified position: pos ==> 
		derived_type	left(size_type n, size_type pos = 0)			{ return derived_type(derive(), n, pos);					}
		/// Gets the substring with n characters from the left direction at the specified position: pos ==> 
		derived_type	left(size_type n, size_type pos = 0) const		{ return derived_type(derive(), n, pos);					}
		/// Gets the substring with n characters from the reverse direction at the specified position: <== rpos 
		derived_type	right(size_type n, size_type rpos = 0)			{ return derived_type(derive(), n, derive().length() - n - rpos);	}
		/// Gets the substring with n characters from the reverse direction at the specified position: <== rpos 
		derived_type	right(size_type n, size_type rpos = 0) const	{ return derived_type(derive(), n, derive().length() - n - rpos);	}
		// Returns the first element of the buffer
		reference		front()			{ return buffer().front();	}
		// Returns the first element of the buffer
		const_reference	front()	const	{ return buffer().front();	}
		// Returns the last element of the buffer
		reference		back()			{ return derive().at(derive().size() - 1);	}
		// Returns the last element of the buffer
		const_reference	back() const	{ return derive().at(derive().size() - 1);	}
		
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns reference at the given index
		reference operator[](size_type index)
		{
			return const_cast<reference>(static_cast<derived_type const&>(*this).operator[](index));
		}
		/// Returns const reference at the given index
		const_reference operator[](size_type index) const
		{
			EXTL_ASSERT(derive().is_valid());
			EXTL_ASSERT(NULL != data());
			EXTL_ASSERT(index < length());
			return derive().data()[index];
		}
		/// Returns reference at the given index and throws index_error() if index >= length() 
		reference at(size_type index)
		{
			return const_cast<reference>(static_cast<derived_type const&>(*this).at(index));
		}
		/// Returns const reference at the given index and throws index_error() if index >= length() 
		const_reference at(size_type index) const
		{
			EXTL_ASSERT(derive().is_valid());
			EXTL_ASSERT(NULL != data());
			EXTL_ASSERT(index < length());
			EXTL_ASSERT_THROW(index < length(), index_error("out of range"));
			return derive().data()[index];
		}
	/// @}

	/// \name Others
	/// @{
	public:
		/// Swaps operation 
		void swap(class_type& other)	{ buffer().swap(other.m_buffer);	}
		/// Reserves at least newcap size memory storage
		void reserve(size_type newcap)	{ if (capacity() < newcap) derive().resize(newcap);	}
		/// Clears the memory of the string
		void clear()					{ buffer().clear(); set_eos(0);	}
		/// Fills zero in the whole string
		void clean()					{ buffer().clean();	}
		/// Makes the lowercase string 
		derived_type& to_lower()		{ if(derive().length() != 0) string_traits_type::to_lower(data()); return derive();	}
		/// Makes the uppercase string 
		derived_type& to_upper()		{ if(derive().length() != 0) string_traits_type::to_upper(data()); return derive();	}
		/// Returns the allocator
		allocator_type allocator() const	{ return buffer().allocator();	}
		/// The maximum possible value of length
		size_type max_length() const		{ return derive().max_size();	}
		/// The maximum possible value of length
		size_type max_size() const			
		{ 
			size_type size = buffer().max_size(); 
			/* Considers a null-terminator */
			return (size <= 1? 1 : size - 1);	
		}
		/// Resizes the length of string
		void resize(size_type length)	
		{ 
			if(length > 0)
			{
				buffer().resize(length + 1); 
				set_eos(length);
			}
			else clear();
		}
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const			{ return buffer().begin();							}
		iterator				begin()					{ return buffer().begin();							}

		const_iterator			end() const				{ return --buffer().end(); 							}
		iterator				end()					{ return --buffer().end();							}
		
		const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(derive().end());	}
		reverse_iterator		rbegin()				{ return reverse_iterator(derive().end());			}
	
		const_reverse_iterator	rend() const			{ return const_reverse_iterator(derive().begin());	}	
		reverse_iterator		rend()					{ return reverse_iterator(derive().begin());		}
	/// @}

	/// \name Finds
	/// @{
	public:
		/// Finds the given c-style string with n characters at the specified position of this from this and return its position 
		size_type find(size_type pos, const_pointer s, size_type n) const; 
		/// Finds the given c-style string at the specified position of this from this and return its position 
		size_type find(size_type pos, const_pointer s) const							{ return derive().find(pos, s, (NULL != s)? string_traits_type::length(s) : 0);	}
		/// Finds the given c-style string from this and return its position 
		size_type find(const_pointer s) const											{ return derive().find(0, s);	} 
		/// Finds the given string with n characters at the specified position of this from this and return its position 
		size_type find(size_type pos, derived_type const& s, size_type n) const			{ return derive().find(pos, s.c_str(), n);	}
		/// Finds the given string at the specified position of this from this and return its position 
		size_type find(size_type pos, derived_type const& s) const						{ return derive().find(pos, s.c_str(), s.length());	}
		/// Finds the given string from this and return its position 
		size_type find(derived_type const& s) const										{ return derive().find(0, s.c_str(), s.length());	}
		/// Finds the given character with value ch at the specified position of this and return its position 
		size_type find(size_type pos, const_reference ch) const							{ return derive().find(pos, static_cast<const_pointer>(&ch), 1);	}
		/// Finds the given character with value ch and return its position 
		size_type find(const_reference ch) const										{ return derive().find(0, static_cast<const_pointer>(&ch), 1);	}
		
		/// Reversely Finds the given c-style string with n characters at the specified position of this from this and return its position 
		size_type rfind(size_type pos, const_pointer s, size_type n) const; 
		/// Reversely Finds the given c-style string at the specified position of this from this and return its position 
		size_type rfind(size_type pos, const_pointer s) const							{ return derive().rfind(pos, s, (NULL != s)? string_traits_type::length(s) : 0);	}
		/// Reversely Finds the given c-style string from this and return its position 
		size_type rfind(const_pointer s) const											{ return derive().rfind(0, s);	} 
		/// Reversely Finds the given string with n characters at the specified position of this from this and return its position 
		size_type rfind(size_type pos, derived_type const& s, size_type n) const			{ return derive().rfind(pos, s.c_str(), n);	}
		/// Reversely Finds the given string at the specified position of this from this and return its position 
		size_type rfind(size_type pos, derived_type const& s) const						{ return derive().rfind(pos, s.c_str(), s.length());	}
		/// Reversely Finds the given string from this and return its position 
		size_type rfind(derived_type const& s) const										{ return derive().rfind(0, s.c_str(), s.length());	}
		/// Reversely Finds the given character with value ch at the specified position of this and return its position 
		size_type rfind(size_type pos, const_reference ch) const						{ return derive().rfind(pos, static_cast<const_pointer>(&ch), 1);	}
		/// Reversely Finds the given character with value ch and return its position 
		size_type rfind(const_reference ch) const										{ return derive().rfind(0, static_cast<const_pointer>(&ch), 1);	}

		/// The failure to find 
		static size_type fof()		{ return string_traits_type::fof();	}
	/// @}

	/// \name Replacements
	/// @{
	public:
		/// Replaces the old string with the given new string in the whole context and return the number of the substring replaced 
		size_type replace_all(const_pointer old_str, const_pointer new_str);
		/// Replaces the old string with the given new string in the whole context and return the number of the substring replaced 
		size_type replace_all(derived_type const& old_str, derived_type const& new_str)					{	return derive().replace_all(old_str.c_str(), new_str.c_str());	}
		/// Replaces the old character with the given new charactor in the whole context and return the number of the substring replaced 
		size_type replace_all(const_reference old_ch, const_reference new_ch);

		/// Replaces the given range [pos, pos + old_n) with the given new c-style string with new_n characters 
		derived_type& replace(size_type pos, size_type old_n, const_pointer new_str, size_type new_n)			
		{ 
			/* Avoids covering null-terminator */
			buffer().replace(pos, old_n, new_str, ((pos + old_n) > length() || is_empty())? ++new_n : new_n); 
			set_eos(derive().length()); 
			return derive();				
		}
		/// Replaces the given range [pos, pos + old_n) with the given new c-style string 
		derived_type& replace(size_type pos, size_type old_n, const_pointer new_str)								{ return derive().replace(pos, old_n, new_str, (NULL != new_str)? string_traits_type::length(new_str) : 0);	}
		/// Replaces the given range [pos, pos + old_n) with the given new string
		derived_type& replace(size_type pos, size_type old_n, derived_type const& new_str)						{ return derive().replace(pos, old_n, new_str.c_str(), new_str.length());	}
		/// Replaces the given range [pos, pos + old_n) with the given new string with new_n characters 
		derived_type& replace(size_type pos, size_type old_n, derived_type const& new_str, size_type new_n)		{ return derive().replace(pos, old_n, new_str.c_str(), new_n);	}
		
		/// Replaces the given range [pos, pos + old_n) with the given new_n character with the character new_ch 
		derived_type& replace(size_type pos, size_type old_n, const_reference new_ch, size_type new_n = 1)		
		{
			/* Avoids covering null-terminator */
			buffer().replace(pos, old_n, new_ch, ((pos + old_n) > length() || is_empty())? ++new_n : new_n); 
			set_eos(derive().length()); 
			return derive();
		}	
		/// Replaces the given position [pos, pos + 1) with the given new_n character with the character new_ch 
		derived_type& replace(size_type pos, const_reference new_ch, size_type new_n = 1)						{ return derive().replace(pos, 1, new_ch, new_n);	}
	
		/// Replaces the given range [first, last) with the input const_iterator with the given new string
		derived_type& replace(const_iterator first, const_iterator last, const_pointer new_str)							{ return derive().replace(first, last, new_str, (NULL != new_str)? string_traits_type::length(new_str) : 0);	}
		/// Replaces the given range [first, last) with the input const_iterator with the given new string with new_n character 
		derived_type& replace(const_iterator first, const_iterator last, const_pointer new_str, size_type new_n)			{ return derive().replace(ptr_diff(derive().begin(), first), ptr_diff(first, last), new_str, new_n);	}
		/// Replaces the given range [first, last) with the input const_iterator with the given new string
		derived_type& replace(const_iterator first, const_iterator last, derived_type const& new_str)						{ return derive().replace(first, last, new_str.c_str(), new_str.length());	}
		/// Replaces the given range [first, last) with the input const_iterator with the given new string with new_n character 
		derived_type& replace(const_iterator first, const_iterator last, derived_type const& new_str, size_type new_n)	{ return derive().replace(first, last, new_str.c_str(), new_n);	}
		/// Replaces the given range [first, last) with the input const_iterator with the given new_n character with the character new_ch 
		derived_type& replace(const_iterator first, const_iterator last, const_reference new_ch, size_type new_n = 1)	{ return derive().replace(ptr_diff(derive().begin(), first), ptr_diff(first, last), new_ch, new_n);	}
		/// Replaces the given position [pos, pos + 1) with the input const_iterator with the given new string with new_n character 
		derived_type& replace(const_iterator pos, const_reference new_ch, size_type new_n = 1)							{ return derive().replace(pos, pos + 1, new_ch, new_n);						}
	
		/// Replaces the given range [first, last) with the input iterator with the given range [first2, last2) 
		derived_type& replace(const_iterator first, const_iterator last, const_pointer first2, const_pointer last2)		{ return derive().replace(ptr_diff(derive().begin(), first), ptr_diff(first, last), first2, ptr_diff(first2, last2));	}
		/// Replaces the given range [first, last) with the input iterator with the given range [first2, last2) with the input iterator 
		derived_type& replace(const_iterator first, const_iterator last, const_iterator first2, const_iterator last2)	{ return derive().replace(first, last, get_ptr(first2), get_ptr(last2));	}
		/// Replaces the given range [first, last) with the input iterator with the given range [first2, last2) with the input reverse iterator 
		derived_type& replace(const_iterator first, const_iterator last, const_reverse_iterator first2, const_reverse_iterator last2)	
		{ 
			/* Avoids covering null-terminator 
			 * Note: ++last2 return std::reverse_iterator rather than const_reverse_iterator when EXTL_USE_STL_DISABLE is undefined
			 */
			buffer().replace(first, last, first2, (last > end() || is_empty())? (++last2, last2): last2); 
			set_eos(derive().length()); 
			return derive();
		}
	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		/// Replaces the given range [first, last) with the input iterator with the given new string with new_n values 
		template < typename_param_k _InIt >
		derived_type& replace(const_iterator first, const_iterator last, _InIt first2, _InIt last2 )	
		{ 
			/* Avoids covering null-terminator 
			 * Note: ++last2 return std::reverse_iterator rather than const_reverse_iterator when EXTL_USE_STL_DISABLE is undefined
			 */
			buffer().replace(first, last, first2, (last > end() || is_empty())? (++last2, last2) : last2); 
			set_eos(derive().length()); 
			return derive();
		}
	#endif /* EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT */
	/// @}

	/// \name Assignments
	/// @{
	public:
		/// Assigns with n values from the given string at the specified position 
		derived_type& assign(const_pointer s, size_type n, size_type pos = 0)		{ return derive().replace(0, derive().length(), s + pos, n);	}
		/// Assigns from the given string 
		derived_type& assign(const_pointer s)										{ return derive().assign(s, (NULL != s)? string_traits_type::length(s) : 0, 0);	}
		
		/// Assigns from the given string
		derived_type& assign(derived_type const& s)									{ return derive().assign(s.c_str(), s.length(), 0);	}
		/// Assigns with n values from the given string at the specified position 
		derived_type& assign(derived_type const& s, size_type n, size_type pos = 0)	{ return derive().assign(s.c_str(), n, pos);	}
		/// Assigns with n values 
		derived_type& assign(const_reference v, size_type n = 1)						{ return derive().replace(0, derive().length(), v, n);	}

		/// Assigns from range [first, last) with the const pointer iterator  
		derived_type& assign(const_pointer first, const_pointer last)					{ return derive().assign(first, ptr_diff(first, last));	}
		/// Assigns from range [first, last) with the const input iterator  
		derived_type& assign(const_iterator first, const_iterator last)					{ return derive().assign(get_ptr(first), get_ptr(last));	}
		/// Assigns from range [first, last) with the const reverse input iterator  
		derived_type& assign(const_reverse_iterator first, const_reverse_iterator last)	{ return derive().replace(derive().begin(), derive().end(), first, last);	}

	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT) \
			&& !defined(EXTL_COMPILER_IS_DMC)
		/// Assigns from range [first, last) with the input iterator  
		template < typename_param_k _InIt >
		derived_type& assign(_InIt first, _InIt last) { return derive().replace(begin(), end(), first, last);	}
	#endif /* EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT */

		/// Assigns with the given format string 
		derived_type& EXTL_CDECL format(const_pointer format_str, ...);

		derived_type& operator=(derived_type const& s)	{ return derive().assign(s);	}
		derived_type& operator=(const_pointer s)			{ return derive().assign(s);	}
		derived_type& operator=(const_reference v)		{ return derive().assign(v);	}

		/*!\brief Prohibit the following case:
		 * 
		 * \code
			D da, db;
			B &ba = da, &bb = db;
			ba = bb;
		 * \endcode
		 */
	private:
		class_type& operator=(class_type const&);
	/// @}

	/// \name Appends
	/// @{
	public:
		/// Appends with n characters from the given string at the specified position 
		derived_type& append(const_pointer s, size_type n, size_type pos = 0)		{ return derive().replace(derive().length(), 1, s + pos, n);	}
		/// Appends from the given string
		derived_type& append(const_pointer s)										{ return derive().replace(derive().length(), 1, s, (NULL != s)? string_traits_type::length(s) : 0);	}
		/// Appends with n characters from the given string at the specified position 
		derived_type& append(derived_type const& s, size_type n, size_type pos = 0)	{ return derive().append(s.c_str(), n, pos);	}
		/// Appends from the given string
		derived_type& append(derived_type const& s)									{ return derive().append(s.c_str(), s.length(), 0);	}
		/// Appends with n characters with the character v 
		derived_type& append(const_reference v, size_type n = 1)						{ return derive().replace(derive().length(), v, n);	}
		
		/// Appends from range [first, last) with the const pointer  
		derived_type& append(const_pointer first, const_pointer last)				{ return derive().append(first, ptr_diff(first, last), 0);	}
		/// Appends from range [first, last) with the const input iterator  
		derived_type& append(const_iterator first, const_iterator last)				{ return derive().append(get_ptr(first), get_ptr(last));	}
		/// Appends from range [first, last) with the const reverse input iterator  
		derived_type& append(const_reverse_iterator first, const_reverse_iterator last)	
		{ 
			std_copy(first, last, extl_back_inserter(derive()));
			return derive();			
		}

	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		template < typename_param_k _InIt >
		derived_type& append(_InIt first, _InIt last) /* optimization */
		{
			std_copy(first, last, extl_back_inserter(derive()));
			return derive();
		}
	#endif /* defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT) */

		/// Appends from the given format string 
		derived_type& EXTL_CDECL append_format(const_pointer format_str, ...);

	public: 
		derived_type& operator+=(derived_type const& s)		{ return derive().append(s);	}
		derived_type& operator+=(const_pointer s)			{ return derive().append(s);	}
		derived_type& operator+=(const_reference v)			{ return derive().append(v);	}

		derived_type& operator<<(derived_type const& s)		{ return derive().append(s);	}
		derived_type& operator<<(const_pointer s)			{ return derive().append(s);	}
		derived_type& operator<<(const_reference v)			{ return derive().append(v);	}
	
	public:
		/// Pushes a character
		void push_back(const_reference v)					{ derive().append(v);		}
		/// Pushes a character if character \c v doesn't exist
		void ensure_push_back(const_reference v)			{ if(!string_traits_type::eq(*--derive().end(), v)) derive().append(v);	}
		/// Pops a character
		void pop_back()										{ derive().resize(derive().length() - 1); set_eos(derive().length()); }
		/// Pops a character if character \c v exists
		void ensure_pop_back(const_reference v)				{ if(string_traits_type::eq(*--derive().end(), v)) derive().pop_back();	}
	/// @}

	/// \name Inserts
	/// @{
	public:
		/// Inserts the given new string with new_n characters into the given position *this[pos] 
		derived_type& insert(size_type pos, const_pointer new_str, size_type new_n)				{ return derive().replace(pos, 0, new_str, new_n);	}
		/// Inserts the given new string into the given position *this[pos] 
		derived_type& insert(size_type pos, const_pointer new_str)								{ return derive().replace(pos, 0, new_str, (NULL != new_str)? string_traits_type::length(new_str) : 0);	}
		/// Inserts the given new string into the given position *this[pos] 
		derived_type& insert(size_type pos, derived_type const& new_str)							{ return derive().insert(pos, new_str.c_str(), new_str.length());	}
		/// Inserts the given new string with new_n characters into the given position *this[pos] 
		derived_type& insert(size_type pos, derived_type const& new_str, size_type new_n)			{ return derive().insert(pos, new_str.c_str(), new_n);	}
		/// Inserts the given new_n character with the character new_ch into the given position *this[pos]
		derived_type& insert(size_type pos, const_reference new_ch, size_type new_n = 1)			{ return derive().replace(pos, 0, new_ch, new_n);	}

		/// Inserts the given new string with new_n characters into the given position *pos with the input iterator 
		derived_type& insert(const_iterator pos, const_pointer new_str, size_type new_n)			{ return derive().insert(ptr_diff(derive().begin(), pos), new_str, new_n);	}
		/// Inserts the given new string into the given position *pos with the input iterator 
		derived_type& insert(const_iterator pos, const_pointer new_str)							{ return derive().insert(ptr_diff(derive().begin(), pos), new_str);	}
		/// Inserts the given new string into the given position *pos with the input const_iterator 
		derived_type& insert(const_iterator pos, derived_type const& new_str)						{ return derive().insert(ptr_diff(derive().begin(), pos), new_str, new_str.size());	}
		/// Inserts the given new string with new_n characters into the given position *pos with the input const_iterator 
		derived_type& insert(const_iterator pos, derived_type const& new_str, size_type new_n)	{ return derive().insert(ptr_diff(derive().begin(), pos), new_str, new_n);	}
		/// Inserts the given new_n character with the character new_ch into the given position *pos with the input const_iterator 
		derived_type& insert(const_iterator pos, const_reference new_ch, size_type new_n = 1)	{ return derive().insert(ptr_diff(derive().begin(), pos), new_ch, new_n);	}
	/// @}

	/// \name Reverses 
	/// @{
	public:
		/// Reverses the given range [first, last] of the string
		derived_type& reverse(const_iterator first, const_iterator last)			{ return derive().replace(first, last, const_reverse_iterator(last), const_reverse_iterator(first));	}
		/// Reverses the given range [pos, pos + n] of the string
		derived_type& reverse(size_type pos, size_type n)						{ return derive().reverse(derive().begin() + pos, derive().begin() + pos + n);	}
		/// Reverses the whole string
		derived_type& reverse()													{ return derive().reverse(derive().begin(), derive().end());	}
	/// @}

	/// \name Erases
	/// @{
	public:
		/// Erases the given range [pos, pos + n) from this 
		derived_type& erase(size_type pos, size_type n = 1)
		{
			if(NULL == derive().c_str()) return derive();
		#if 0
			buffer().erase(pos, n + pos > derive().length()? derive().length() - pos : n);
		#else
			if (n + pos >= length())
			{
				++n;
				++pos;
			}
			buffer().erase(pos, n);
			set_eos(derive().length()); 
		#endif
			return derive();
		}
		/// Erases the given position *pos with the input iterator from this 
		derived_type& erase(const_iterator pos)							{	return derive().erase(ptr_diff(derive().begin(), pos), 1);							}
		/// Erases the given range [first, last) with the input iterator from this 
		derived_type& erase(const_iterator first, const_iterator last)	{	return derive().erase(ptr_diff(derive().begin(), first), ptr_diff(first, last));		}
	/// @}

	/// \name Comparison
	/// @{
	public:
		/// Compares this at the specified position from the given c-style string with n characters
		int_type compare(size_type pos, const_pointer s, size_type n) const;
		/// Compares this with the given c-style string with n characters
		int_type compare(const_pointer s, size_type n) const						{ return derive().compare(0, s, n);											}
		/// Compares this with the given c-style string
		int_type compare(const_pointer s) const										{ return derive().compare(s, (NULL != s)? string_traits_type::length(s) : 0);	}
		/// Compares this at the specified position from the given string with n characters
		int_type compare(size_type pos, derived_type const& s, size_type n) const	{ return derive().compare(pos, s.c_str(), n);								}		
		/// Compares this from the given string with n characters
		int_type compare(derived_type const& s, size_type n) const					{ return derive().compare(0, s.c_str(), n);									}		
		/// Compares this with the given string
		int_type compare(derived_type const& s) const								{ return derive().compare(s, s.length());									}		
		/// Compares this with the given range with the const pointe
		int_type compare(const_pointer first, const_pointer last) const				{ return derive().compare(first, ptr_diff(first, last));						}
		/// Compares this with the given range with the const iterator 
		int_type compare(const_iterator first, const_iterator last) const			{ return derive().compare(get_ptr(first), get_ptr(last));						}
		/// Compares this with the given range with the const reverse iterator 
		int_type compare(const_reverse_iterator first, const_reverse_iterator last) const	
		{ 
			const_pointer p = derive().data();
			for(; first != last || !string_traits_type::is_nt(*p); ++first, ++p)
			{
				if(!string_traits_type::eq(*first, *p))
				{
					return string_traits_type::lt(*first, *p)? -1 : + 1;
				}
			}
			return 0; 
		}

	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		/// Compares this with the given range with the input iterator 
		template < typename_param_k _InIt >
		int_type compare(_InIt first, _InIt last) const
		{
			const_pointer p = derive().data();
			for(; first != last || !string_traits_type::is_nt(*p); ++first, ++p)
			{
				if(!string_traits_type::eq(*first, *p))
				{
					return string_traits_type::lt(*first, *p)? -1 : + 1;
				}
			}
			return 0;
		}
	#endif /* EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT */

		/// Compares this at the specified position from the given c-style string with n characters in a case-insensitive
		int_type compare_nocase(size_type pos, const_pointer s, size_type n) const;
		/// Compares this with the given c-style string with n characters in a case-insensitive
		int_type compare_nocase(const_pointer s, size_type n) const						{ return derive().compare_nocase(0, s, n);											}
		/// Compares this with the given c-style string in a case-insensitive
		int_type compare_nocase(const_pointer s) const									{ return derive().compare_nocase(s, (NULL != s)? string_traits_type::length(s) : 0);	}
		/// Compares this at the specified position from the given string with n characters in a case-insensitive
		int_type compare_nocase(size_type pos, derived_type const& s, size_type n) const	{ return derive().compare_nocase(pos, s.c_str(), n);									}		
		/// Compares this from the given string with n characters in a case-insensitive
		int_type compare_nocase(derived_type const& s, size_type n) const				{ return derive().compare_nocase(0, s.c_str(), n);									}		
		/// Compares this with the given string in a case-insensitive
		int_type compare_nocase(derived_type const& s) const								{ return derive().compare_nocase(s, s.length());										}		
		/// Compares this with the given range with the const pointer in a case-insensitive
		int_type compare_nocase(const_pointer first, const_pointer last) const			{ return derive().compare_nocase(first, ptr_diff(first, last));						}
		/// Compares this with the given range with the const iterator  in a case-insensitive
		int_type compare_nocase(const_iterator first, const_iterator last) const		{ return derive().compare_nocase(get_ptr(first), get_ptr(last));							}
		/// Compares this with the given range with the const reverse iterator  in a case-insensitive
		int_type compare_nocase(const_reverse_iterator first, const_reverse_iterator last) const	
		{ 
			const_pointer p = derive().data();
			for(; first != last || !string_traits_type::is_nt(*p); ++first, ++p)
			{
				char_type lch = string_traits_type::to_lower(*first);
				char_type rch = string_traits_type::to_lower(*p);
				if(!string_traits_type::eq(lch, rch))
				{
					return string_traits_type::lt(*first, *p)? -1 : + 1;
				}
			}
			return 0; 
		}

	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		/// Compares this with the given range with the input iterator  in a case-insensitive
		template < typename_param_k _InIt >
		int_type compare_nocase(_InIt first, _InIt last) const
		{
			const_pointer p = derive().data();
			for(; first != last || !string_traits_type::is_nt(*p); ++first, ++p)
			{
				char_type lch = string_traits_type::to_lower(*first);
				char_type rch = string_traits_type::to_lower(*p);
				if(!string_traits_type::eq(lch, rch))
				{
					return string_traits_type::lt(*first, *p)? -1 : + 1;
				}
			}
			return 0; 
		}
	#endif /* EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT */

	public:
		bool_type operator==(derived_type const& rhs) const	{ return derive().compare(rhs) == 0;	}
		bool_type operator==(const_pointer rhs) const		{ return derive().compare(rhs) == 0;	}

		bool_type operator<(derived_type const& rhs) const	{ return derive().compare(rhs) < 0;	}
		bool_type operator<(const_pointer rhs) const			{ return derive().compare(rhs) < 0;	}
		bool_type operator>(const_pointer rhs) const			{ return derive().compare(rhs) > 0;	}
	/// @}

	/// \name Conversion
	/// @{
	public:
		/// Converts an integer to a string
		derived_type& from_integer(int_type integer)
		{
			derive().resize(EXTL_ITOS_MAX_CHAR_NUM);
		#if defined(EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT)
			return derive().assign(itos<>(integer, derive().data(), derive().length()));
		#else
			return derive().assign(sitos(integer, derive().data(), derive().length()));
		#endif
		}

	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		/// Converts an integer to a string
		template < typename_param_k I >
		derived_type& from_integer(I integer)
		{
		#if defined(EXTL_CONVERSION_ITOS_WITH_PARAM_SUPPORT)
			return derive().assign(itos<>(integer, derive().data(), derive().length()));
		#else
			return derive().assign(sitos(integer, derive().data(), derive().length()));
		#endif
		}
	#endif

		/// Converts a string to an integer
		int_type to_integer()
		{
		#if defined(EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT)
			return stoi<int_type>(derive().c_str());
		#else
			return static_cast<int_type>(stoi(derive().c_str()));
		#endif
		}
	/// @}

	/// \name Helpers
	/// @{
	protected:
	#ifdef EXTL_COMPILER_IS_VECTORC
		/// Gets the const reference of the derived string
		derived_type const& derive() const	{ return (derived_type const&)(*this);	}
		/// Gets the reference of the derived string
		derived_type&		derive()		{ return (derived_type&)(*this);		}
	#else
		/// Gets the const reference of the derived string
		derived_type const&	derive() const	{ return reinterpret_cast<derived_type const&>(*this);	}
		/// Gets the reference of the derived string
		derived_type&		derive()		{ return reinterpret_cast<derived_type&>(*this);		}
	#endif

		/// Gets the const reference of the buffer
		buffer_type const&	buffer() const		{ return m_buffer;	}
		/// Gets the reference of the derived string
		buffer_type&		buffer()			{ return m_buffer;	}

		/// Returns the difference between two pointers, last >= first 
		size_type			ptr_diff(const_pointer first, const_pointer last) const									{ EXTL_ASSERT(first <= last); return last - first;		}
		/// Returns the difference between two iterators, last >= first 
		size_type			ptr_diff(const_iterator const& first, const_iterator const& last) const					{ EXTL_ASSERT(first <= last); return last - first;		}
		/// Returns the difference between two reverse iterators, rfirst >= rlast 
		size_type			ptr_diff(const_reverse_iterator const& rfirst, const_reverse_iterator const& rlast) const	{ EXTL_ASSERT(rfirst <= rlast); return rlast - rfirst;	}
	
		/// Returns the maximum size of the formatted string
		size_type			get_format_max_size(const_pointer format_str, va_list arglist) const;

		/// Sets the end of the string by null-terminator
		void				set_eos(size_type index)			{ if(NULL != derive().data() && index <= derive().length()) derive().data()[index] = char_type('\0'); }
	
		/// Returns the const pointer of the given the const pointer iterator
		const_pointer		get_ptr(const_iterator const& it) const	{ return it.current();	}
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_STRING_BASE_TEMPLATE_DECL
#	undef EXTL_STRING_BASE_TEMPLATE_DECL
#endif

#define EXTL_STRING_BASE_TEMPLATE_DECL			\
template<	typename_param_k		D			\
		,	typename_param_k		T			\
		,	typename_param_k		B			\
		>

/* Class qualification */
#ifdef EXTL_STRING_BASE_QUAL
#	undef EXTL_STRING_BASE_QUAL
#endif

#define EXTL_STRING_BASE_QUAL	string_base<D, T, B>

/* Class qualification */
#ifdef EXTL_STRING_BASE_RET_QUAL
#	undef EXTL_STRING_BASE_RET_QUAL
#endif

#define EXTL_STRING_BASE_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_STRING_BASE_QUAL::ret_type \
					EXTL_STRING_BASE_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Class implemention
 */
/* Compares this at the specified position from the given c-style string with n characters */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(int_type)::compare(size_type pos, const_pointer s, size_type n) const
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != s);
	if(0 == n || NULL == s) return 1; /* this > s */
	return string_traits_type::compare(derive().c_str() + pos, s, n);
}
/* Compares this at the specified position from the given c-style string with n characters in a case-insensitive */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(int_type)::compare_nocase(size_type pos, const_pointer s, size_type n) const
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != s);
	if(0 == n || NULL == s) return 1; /* this > s */
	return string_traits_type::compare_nocase(derive().c_str() + pos, s, n);
}
/* Finds the given string with n characters at the specified position of this from this and return its position */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(size_type)::find(size_type pos, const_pointer s, size_type n) const
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != s);
	EXTL_ASSERT(!(max_length() < pos + n));
	return string_traits_type::find(derive().c_str(), derive().length(), pos, s, n);
}
/* Reversely finds the given string with n characters at the specified reverse position of this from this and return its position */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(size_type)::rfind(size_type rpos, const_pointer s, size_type n) const
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != s);
	EXTL_ASSERT(!(derive().max_length() < derive().length() - rpos + n));
	return string_traits_type::rfind(derive().c_str(), derive().length(), rpos, s, n);
}
/* Replaces the old string to the given new string in the whole context and return the number of the substring replaced */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(size_type)::replace_all(const_pointer old_str, const_pointer new_str)
{
	if(NULL == old_str || NULL == new_str)
		return 0;

	EXTL_ASSERT(derive().is_valid());
	if(NULL == derive().data()) return 0;

	size_type new_n = string_traits_type::length(new_str);
	size_type old_n = string_traits_type::length(old_str);
	if(0 == new_n || 0 == old_n) return 0;

	size_type pos = 0, count = 0;
	while((pos = derive().find(pos, old_str, old_n)) != fof())
	{
		derive().replace(pos, old_n, new_str, new_n);
		pos += new_n;
		++count;
	}
	EXTL_ASSERT(derive().is_valid());
	return count;
}
/* Replaces the old character to the given new charactor in the whole context and return the number of the substring replaced */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(size_type)::replace_all(const_reference old_ch, const_reference new_ch)
{
	/* Note: return replace_all(static_cast<char_type *>(&old_ch), static_cast<char_type *>(&new_ch));	
	 * May be not null-termianted with some compilers (eg: GCC, BCC) 
	 */
	EXTL_ASSERT(derive().is_valid());
	if(NULL == derive().data()) return 0;
	size_type pos = 0, count = 0;
	while((pos = derive().find(pos, old_ch)) != fof())
	{
		derive().data()[pos] = new_ch;
		++pos;
		++count;
	}
	EXTL_ASSERT(derive().is_valid());
	return count;
}
/* Returns the maximum size of the formatted string */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(size_type)::get_format_max_size(const_pointer format_str, va_list arglist) const
{
	EXTL_ASSERT(NULL != format_str);
	size_type max_size = 0;

	for (const_pointer p = format_str; !string_traits_type::is_nt(*p); ++p)
	{
		/* Handles '%' character, but watches out for '%%' */
		if (!string_traits_type::eq(*p, '%') || string_traits_type::eq(*++p, '%'))
		{
			max_size += string_traits_type::length(p);
			continue;
		}

		/* Handles '%' character with format */
		size_type width = 0;
		for (; !string_traits_type::is_nt(*p); ++p)
		{
			if (string_traits_type::eq(*p, '#'))
				max_size += 2;	/* "%#..." for 0x */
			else if (string_traits_type::eq(*p, '*'))
				width += va_arg(arglist, e_int_t); /* eg: printf("%*.*d\n",10,10,123456789) */
			else if (string_traits_type::eq(*p, '-') || string_traits_type::eq(*p, '+') || 
							string_traits_type::eq(*p, '0') || string_traits_type::eq(*p, ' '))
				;
			else break;
		}

		/* Gets width and skips it */
		if (0 == width)
		{
		#if defined(EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT)
			width =  stoi<size_type>(p);
		#else
			width =  static_cast<size_type>(stoi(p));
		#endif

			for (; !string_traits_type::is_nt(*p) && e_t_isdigit(*p); ++p)
				;
		}
		EXTL_ASSERT(width >= 0);

		/* Gets precision */
		size_type precision = 0;
		if (string_traits_type::eq(*p, '.'))
		{
			++p;
			if (string_traits_type::eq(*p, '*'))
			{
				precision = va_arg(arglist, e_int_t);
				++p;
			}
			else
			{
				#if defined(EXTL_CONVERSION_STOI_WITH_PARAM_SUPPORT)
					precision =  stoi<size_type>(p);
				#else
					precision =  static_cast<size_type>(stoi(p));
				#endif

				for (; !string_traits_type::is_nt(*p) && e_t_isdigit(*p); ++p)
				;
			}
			EXTL_ASSERT(precision >= 0);
		}

		/* Should be on type modifier or specifier */
		enum { en_force_ansi = 0x10000 };
		enum { en_force_unicode = 0x20000 };
		enum { en_force_int64 = 0x40000 };

		size_type modifier = 0;

		if (string_traits_type::eq(*p, 'I') && 
			string_traits_type::eq(*++p, '6') &&
			string_traits_type::eq(*++p, '4'))
		{
			++p;
			modifier = en_force_int64;

			/* __int64 is only available on X86 and ALPHA platforms */
		#if !defined(EXTL_64BIT_INT_SUPPORT) || \
				!defined(EXTL_PRINTF_I64_FORMAT_SUPPORT)
			EXTL_MESSAGE_ASSERT(0, "flag I64 is not support");
		#endif
		}
		else
		{
			switch (*p)
			{
			/* modifiers that affect size */
			case 'h':
				modifier = en_force_ansi;
				++p;
				break;
			case 'l':
				modifier = en_force_unicode;
				++p;
				break;

			/* modifiers that do not affect size */
			case 'F':
			case 'N':
			case 'L':
				++p;
				break;
			}
		}

	#if defined(EXTL_COMPILER_IS_GCC)
		typedef e_int_t				format_char_type;
		typedef e_uint_t			format_wchar_type;
	#	ifdef EXTL_UNICODE 
		typedef format_wchar_type	format_tchar_type;
	#	else
		typedef format_char_type	format_tchar_type;
	#	endif
	#else
		typedef e_tchar_t			format_tchar_type;
		typedef e_char_t			format_char_type;
		typedef e_wchar_t			format_wchar_type;
	#endif

		/* now should be on specifier */
		size_type item_size = 0;
		switch (*p | modifier)
		{
		/* single characters */
		case 'c':
		case 'C':
			{
				item_size = 2;
				format_tchar_type ret = va_arg(arglist, format_tchar_type);
				EXTL_SUPPRESS_UNUSED(ret);
			}
			break;
		case 'c'|en_force_ansi:
		case 'C'|en_force_ansi:
			{
				item_size = 2;
				format_char_type ret = va_arg(arglist, format_char_type);
				EXTL_SUPPRESS_UNUSED(ret);
			}
			break;
		case 'c'|en_force_unicode:
		case 'C'|en_force_unicode:
			{
				item_size = 2;
				format_wchar_type ret = va_arg(arglist, format_wchar_type);
				EXTL_SUPPRESS_UNUSED(ret);
			}
			break;

		/* strings */
		case 's':
			{
				const_pointer next_arg_str = va_arg(arglist, const_pointer);
				if (next_arg_str == NULL)
				   item_size = 6;  /* "(null)" */
				else
				{
				   item_size = string_traits_type::length(next_arg_str);
				   item_size = xtl_max(1u, item_size);
				}
			}
			break;

		case 'D':
			{
			#ifndef EXTL_UNICODE
				e_wchar_t const* next_arg_str = va_arg(arglist, e_wchar_t const*);
				if (next_arg_str == NULL)
				   item_size = 6;  /* "(null)" */
				else
				{
				   item_size = std_strlen_w(next_arg_str);
				   item_size = xtl_max(1u, item_size);
				}
			#else
				e_char_t const* next_arg_str = va_arg(arglist, e_char_t const*);
				if (next_arg_str == NULL)
				   item_size = 6; /* "(null)" */
				else
				{
				   item_size = std_strlen_a(next_arg_str);
				   item_size = xtl_max(1u, item_size);
				}
			#endif
			}
			break;

		case 's'|en_force_ansi:
		case 'D'|en_force_ansi:
			{
				e_char_t const* next_arg_str = va_arg(arglist, e_char_t const*);
				if (next_arg_str == NULL)
				   item_size = 6; /* "(null)" */
				else
				{
				   item_size = std_strlen_a(next_arg_str);
				   item_size = xtl_max(1u, item_size);
				}
			}
			break;

		case 's'|en_force_unicode:
		case 'D'|en_force_unicode:
			{
				e_wchar_t const* next_arg_str = va_arg(arglist, e_wchar_t const*);
				if (next_arg_str == NULL)
				   item_size = 6; /* "(null)" */
				else
				{
				   item_size = std_strlen_w(next_arg_str);
				   item_size = xtl_max(1u, item_size);
				}
			}
			break;
		}

		/* Adjusts item_size for strings */
		if (item_size != 0)
		{
			if (precision != 0)
				item_size = xtl_min(item_size, precision);
			item_size = xtl_max(item_size, width);
		}
		else
		{
			switch (*p)
			{
			/* integers */
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				if (modifier & en_force_int64) 
				{
					e_int64_t ret = va_arg(arglist, e_int64_t);
					EXTL_SUPPRESS_UNUSED(ret);
				}
				else 
				{
					e_int_t ret = va_arg(arglist, e_int_t);
					EXTL_SUPPRESS_UNUSED(ret);
				}
				item_size = 32;
				item_size = xtl_max(item_size, width + precision);
				break;

			case 'e':
			case 'g':
			case 'G':
				{
					double ret = va_arg(arglist, double);
					item_size = 128;
					item_size = xtl_max(item_size, width + precision);
					EXTL_SUPPRESS_UNUSED(ret);
				}
				break;

			case 'f':
				{
					double ret = va_arg(arglist, double);
					item_size = 128; /* width isn't truncated */
					
					/* 312 == strlen("-1+(309 zeroes).")
					 * 309 zeroes == max precision of a double
					 */
					item_size = xtl_max(item_size, 312 + precision);
					EXTL_SUPPRESS_UNUSED(ret);
				}
				break;

			case 'p':
				{
					void* ret = va_arg(arglist, void*);
					item_size = 32;
					item_size = xtl_max(item_size, width + precision);
					EXTL_SUPPRESS_UNUSED(ret);
				}
				break;

			/* no output */
			case 'n':
				{
					e_int_t* ret = va_arg(arglist, e_int_t*);
					EXTL_SUPPRESS_UNUSED(ret);
				}
				break;

			default:
				EXTL_MESSAGE_ASSERT(0, "Unknown formatting option");  /* Unknown formatting option */
			}
		}

		/* adjust nMaxLen for output item_size */
		max_size += item_size;
	}
	return max_size;
}
/* Assigns with the given format string */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(derived_type&)::format(const_pointer format_str, ...)
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != format_str);

	va_list arglist;
	va_start(arglist, format_str);

	/* Returns the maximum size of the formatted string */
	size_type max_size = get_format_max_size(format_str, arglist);

	/* Reserve enough storage */
	derive().reserve(max_size);
	/* Formats string */
	size_type res_size = std_vsnprintf(data(), max_size, format_str, arglist);
	/* Adjust size */
	derive().resize(res_size);

	va_end(arglist);

	EXTL_ASSERT(derive().is_valid());
	return derive();
}
/* Appends from the given format string */
EXTL_STRING_BASE_TEMPLATE_DECL
inline EXTL_STRING_BASE_RET_QUAL(derived_type&)::append_format(const_pointer format_str, ...)
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != format_str);

	va_list arglist;
	va_start(arglist, format_str);

	/* Returns the maximum size of the formatted string */
	size_type max_size = get_format_max_size(format_str, arglist);

	/* Reserve enough storage */
	derive().reserve(length() + max_size);
	/* Formats string */
	size_type res_size = std_vsnprintf(data() + length(), length() + max_size, format_str, arglist);
	/* Adjust size */
	derive().resize(derive().length() + res_size);

	va_end(arglist);

	EXTL_ASSERT(derive().is_valid());
	return derive();
}

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
EXTL_STRING_BASE_TEMPLATE_DECL
EXTL_INLINE void swap(EXTL_STRING_BASE_QUAL &lhs, EXTL_STRING_BASE_QUAL &rhs)
{
	static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}

/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
EXTL_STRING_BASE_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_STRING_BASE_QUAL::
const_pointer get_ptr(EXTL_STRING_BASE_QUAL const& s)
{
	return static_cast<D const&>(s).data();
}

EXTL_STRING_BASE_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_STRING_BASE_QUAL::
size_type get_size(EXTL_STRING_BASE_QUAL const& s)
{
	return static_cast<D const&>(s).size();
}

EXTL_STRING_BASE_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_STRING_BASE_QUAL::
size_type c_strlen(EXTL_STRING_BASE_QUAL const& s)
{
	return static_cast<D const&>(s).length();
}

EXTL_STRING_BASE_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_STRING_BASE_QUAL::
const_pointer c_strptr(EXTL_STRING_BASE_QUAL const& s)
{
	return static_cast<D const&>(s).c_str();
}

template<	typename_param_k	St			
		,	typename_param_k	D			
		,	typename_param_k	T			
		,	typename_param_k	B			
		>
EXTL_INLINE St& operator <<(St& s, EXTL_STRING_BASE_QUAL const& str)
{
	return s << static_cast<D const&>(str).c_str();
}

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_STRING_BASE_TEMPLATE_DECL
#undef EXTL_STRING_BASE_QUAL
#undef EXTL_STRING_BASE_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	typename_param_k	D			
		,	typename_param_k	T			
		,	typename_param_k	B			
		>
EXTL_INLINE void swap(EXTL_NS(string_base)<D, T, B>& lhs, EXTL_NS(string_base)<D, T, B>& rhs)
{
    static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_STRING_STRING_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
