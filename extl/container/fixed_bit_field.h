/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_bit_field.h		
 *
 * Created:		08.10.04			
 * Updated:		08.10.04
 *
 * Brief: fixed_bit_field class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_FIXED_BIT_FIELD_H
#define EXTL_CONTAINER_FIXED_BIT_FIELD_H

/*!\file fixed_bit_field.h
 * \brief fixed_bit_field class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/bit_field_iterator.h"
#include "../string/string.h"
#include "../algorithm/algorithm.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief fixed_bit_field
 *
 * \param N The bit count of the field
 * \param F The field type
 *
 * \ingroup extl_group_container
 */

template<	e_size_t N
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k F = e_size_t
#else
		,	typename_param_k F
#endif
		>
class fixed_bit_field
{
	/// \name Types
	/// @{
	public:
		typedef fixed_bit_field											class_type;
		typedef e_bool_t												bool_type;
		typedef e_size_t												size_type;
		typedef e_char_t												achar_type;
		typedef e_wchar_t												wchar_type;
		typedef size_type												index_type;
		typedef bool_type												value_type;
		typedef value_type*												pointer;
		typedef value_type const*										const_pointer;
		typedef value_type&												reference;
		typedef value_type const&										const_reference;
		typedef F														field_type; 
		typedef EXTL_NS_DETAIL(const_bit_field_iterator)<field_type>	const_iterator;
	/// @}


	/// \name Members
	private:
		field_type														m_field;
	/// @}

	private:
		enum { en_max_bit_count = 8 * sizeof(field_type)	};
		enum { en_bit_count = N								};
	
	/// \name Constructors
	/// @{
	public:
		/// Default Constructor
		fixed_bit_field()
		{
			clear();
		}
		/// Copy Constructor
		fixed_bit_field(class_type const& rhs)
		{
			assign(rhs);
		}
		/// Constructs with given value
		explicit_k fixed_bit_field(const_reference value)
		{
			assign(value);
		}
		/// Constructs from bool array
		explicit_k fixed_bit_field(const_pointer p)
		{
			assign(p);
		}
		/// Constructs from ascii string
		explicit_k fixed_bit_field(achar_type const* s)
		{
			assign(s);
		}
		/// Constructs from unicode string
		explicit_k fixed_bit_field(wchar_type const* s)
		{
			assign(s);
		}
		/// Destructors
		~fixed_bit_field()
		{
			EXTL_STATIC_ASSERT(size_type(en_bit_count) <= en_max_bit_count);
			EXTL_STATIC_ASSERT(size_type(en_bit_count) >= 0);
		}
	/// @}

	/// \name Iterators
	/// @{
	public:
		/// Returns the const begin iterator
		const_iterator		begin() const		{ return const_iterator(&m_field, 0);		}
		/// Returns the const end iterator
		const_iterator		end() const			{ return const_iterator(&m_field, size());	}
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns const value at the given index
		value_type const	operator[](index_type index) const	{ return get(index);	}
		/// Returns const value at the given index and throws index_error() if index >= size() 
		value_type const	at(index_type index) const;
		/// Returns const value at the given index
		value_type const	get(index_type index) const;
		/// Returns const value at the front of field
		value_type const	front()	const	{ return at(0);				}
		/// Returns const value at the back of field
		value_type const	back()	const	{ return at(size() - 1);	}
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		/// Returns the field value
		field_type			data() const			{ return field();			}
		/// Returns the field value
		field_type			field() const			{ return m_field;			}
		/// Returns the numeric of this field
		field_type			numeric() const;
		/// Returns the bit count
		size_type			size() const			{ return en_bit_count;		}
		/// Returns the reserved bit count in the field
		size_type			capacity() const		{ return max_size();		}
		/// Return \c true if size() == 0
		bool_type			is_empty() const		{ return e_true_v;			}
		/// Return \c true if size() == 0
		bool_type			empty() const			{ return is_empty();		}
		/// Return the maximum bit count of the field
		static size_type	max_size()				{ return en_max_bit_count;	}
	/// @}

	/// \name Mutators
	/// @{
	public:
		/// Clears the field e.g. 001101 => null
		void				clear()					{ m_field = e_false_v;		}
		/// Cleans the field e.g. 001101 => 000000
		void				clean()					{ m_field = e_false_v;		}
		/// Swaps field
		void				swap(class_type& rhs)	{ std_swap(m_field, rhs.m_field);	}
		/// Sets the value at the given position
		void				set(index_type index, const_reference value);
		/// Sets the numeric of this field
		void				numeric(field_type num)	{ m_field = num;			}
	/// @}

	/// \name Assignments
	/// @{
	public:
		/// Assigns from the given value(fill all)
		class_type&			assign(const_reference value);
		/// Assigns from bool array
		class_type&			assign(const_pointer p);	
		/// Assigns from ascii string
		class_type&			assign(achar_type const* s);
		/// Assigns from unicode string
		class_type&			assign(wchar_type const* s);
		/// Assigns from the given field
		class_type&			assign(class_type const& rhs);
		/// Assigns from the given field
		class_type&			operator =(class_type const& rhs)			{ return assign(rhs);		}
		/// Assigns from the given value(fill all)
		class_type&			operator =(const_reference value)			{ return assign(value);		}
	/// @}

	/// \name Reverses
	/// @{
	public:
		/// Reverses this bit field with the given range [pos, pos + n)
		class_type&			reverse(size_type pos, size_type n);
		/// Reverses the whole bit field
		class_type&			reverse()		{ return reverse(0, size());	}
	/// @}

	/// \name Static Methods
	/// @{
	public:
		/// Makes numeric from bool array
		/// \param is_left_low true: low bit=> high bit & false: high bit <= low bit
		static field_type	make_numeric(const_pointer p, size_type n, bool_type is_left_low = e_false_v);
		/// Makes numeric from ascii string with n-characters
		/// \param is_left_low true: low bit=> high bit & false: high bit <= low bit
		static field_type	make_numeric(achar_type const* s, size_type n, bool_type is_left_low = e_false_v);
		/// Makes numeric from unicode string with n-characters
		/// \param is_left_low true: low bit=> high bit & false: high bit <= low bit
		static field_type	make_numeric(wchar_type const* s, size_type n, bool_type is_left_low = e_false_v);
		/// Makes numeric from ascii string with null-terminator
		/// \param is_left_low true: low bit=> high bit & false: high bit <= low bit
		static field_type	make_numeric(achar_type const* s, bool_type is_left_low = e_false_v)		{ return make_numeric(s, (NULL != s)? std_strlen(s) : 0, is_left_low);	}
		/// Makes numeric from unicode string with null-terminator
		/// \param is_left_low true: low bit=> high bit & false: high bit <= low bit
		static field_type	make_numeric(wchar_type const* s, bool_type is_left_low = e_false_v)		{ return make_numeric(s, (NULL != s)? std_strlen(s) : 0, is_left_low);	}
	/// @}

	/// \name Operators
	/// @{
	public:
		/// Return the copy of ~(*this)
		class_type			operator ~();
		/// Return \c true if *this == rhs
		bool_type			operator ==(class_type const& rhs) const;
		/// Return \c true if *this != rhs
		bool_type			operator !=(class_type const& rhs) const	{ return !((*this) == rhs);	}
		/// *this &= rhs
		class_type&			operator &=(class_type const& rhs);
		/// *this & rhs
		class_type const	operator &(class_type const& rhs) const;
		/// *this |= rhs
		class_type&			operator |=(class_type const& rhs);
		/// *this | rhs
		class_type const	operator |(class_type const& rhs) const;
		/// *this ^= rhs
		class_type&			operator ^=(class_type const& rhs);
		/// *this ^ rhs
		class_type const	operator ^(class_type const& rhs) const;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Implementation
 */
// at(checked)
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
value_type const fixed_bit_field<N, F>::at(index_type index) const
{
	EXTL_ASSERT_THROW(index < size(), index_error("out of range"));
	return get(index);
}
// get(unchecked)
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
value_type const fixed_bit_field<N, F>::get(index_type index) const
{
	// low bit => high bit
	EXTL_ASSERT(index < size());
	return (field_type(0x1) == ((m_field >> index) & field_type(0x1)));
}
// set 
template<	e_size_t N
		,	typename_param_k F
		>
inline void fixed_bit_field<N, F>::set(index_type index, const_reference value)
{
	EXTL_ASSERT(index < size());

	// low bit => high bit
	m_field &= ~(field_type(0x1) << index);
	m_field |= (static_cast<field_type>(value) << index);
}

// assign
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::assign(const_reference value)
{
	size_type n = size();
	for (index_type i = 0; i < n; ++i) 
		set(i, value);

	return *this;
}
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::assign(const_pointer p)
{
	EXTL_ASSERT(NULL != p);

	size_type n = size();
	for (index_type i = 0; i < n; ++i) 
		set(i, p[i]);

	return *this;
}
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::assign(achar_type const* s)
{
	EXTL_ASSERT(NULL != s);
	EXTL_ASSERT(std_strlen(s) >= size());

	size_type n = size();
	for (index_type i = 0; i < n; ++i) 
		set(i, s[i] != '0');

	return *this;
}
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::assign(wchar_type const* s)
{
	EXTL_ASSERT(NULL != s);
	EXTL_ASSERT(std_strlen(s) >= size());

	size_type n = size();
	for (index_type i = 0; i < n; ++i) 
		set(i, s[i] != L'0');
	
	return *this;
}
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::assign(class_type const& rhs)
{
	if (this != &rhs)
	{
		m_field = rhs.field();
	}
	return *this;
}
// reverse
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::reverse(size_type pos, size_type n)
{
	EXTL_ASSERT(pos >= 0 && (pos + n) <= size());
	EXTL_ASSERT(n > 0);

	index_type begin = 0;
	index_type end = n - 1;

	while (begin < end)
	{
		value_type tmp = get(begin);
		set(begin++, get(end));
		set(end--, tmp);
	}

	return *this;
}

// numeric
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
field_type fixed_bit_field<N, F>::numeric() const
{
	field_type num = 0;
	field_type p2 = 1;

	size_type n = size();
	for (index_type i = 0; i < n; ++i)
	{
		num += get(i) * p2;
		p2 <<= 1;
	}

	return num;
}
// make_numeric
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
field_type fixed_bit_field<N, F>::make_numeric(const_pointer p, size_type n, bool_type is_left_low)
{
	EXTL_ASSERT(NULL != p);

	field_type num = 0;
	field_type p2 = 1;

	if (is_left_low)
	{
		for (index_type i = 0; i < n; ++i)
		{
			num += p[i] * p2;
			p2 <<= 1;
		}
	}
	else
	{
		for (index_type i = 0; i < n; ++i)
		{
			num += p[n - i - 1] * p2;
			p2 <<= 1;
		}
	}
	return num;
}

template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
field_type fixed_bit_field<N, F>::make_numeric(achar_type const* s, size_type n, bool_type is_left_low)
{
	EXTL_ASSERT(NULL != s);

	field_type num = 0;
	field_type p2 = 1;

	if (is_left_low)
	{
		for (index_type i = 0; i < n; ++i)
		{
			num += (s[i] != '0') * p2;
			p2 <<= 1;
		}
	}
	else
	{
		for (index_type i = 0; i < n; ++i)
		{
			num += (s[n - i - 1] != '0') * p2;
			p2 <<= 1;
		}
	}
	return num;
}

template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
field_type fixed_bit_field<N, F>::make_numeric(wchar_type const* s, size_type n, bool_type is_left_low)
{
	EXTL_ASSERT(NULL != s);

	field_type num = 0;
	field_type p2 = 1;

	if (is_left_low)
	{
		for (index_type i = 0; i < n; ++i)
		{
			num += (s[i] != L'0') * p2;
			p2 <<= 1;
		}
	}
	else
	{
		for (index_type i = 0; i < n; ++i)
		{
			num += (s[n - i - 1] != L'0') * p2;
			p2 <<= 1;
		}
	}
	return num;
}
// operator ~
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type fixed_bit_field<N, F>::operator ~()
{
	class_type tmp(*this);
	tmp.m_field = ~field();
	return tmp;
}
// operator ==
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
bool_type fixed_bit_field<N, F>::operator ==(class_type const& rhs) const
{
	return (field() == rhs.field());
}
// operator &=
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::operator &=(class_type const& rhs)
{
	m_field &= rhs.field();
	return *this;
}
// operator &
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type const fixed_bit_field<N, F>::operator &(class_type const& rhs) const
{
	return (class_type(rhs) &= rhs);
}
// operator |=
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::operator |=(class_type const& rhs)
{
	m_field |= rhs.field();
	return *this;
}
// operator |
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type const fixed_bit_field<N, F>::operator |(class_type const& rhs) const
{
	return (class_type(rhs) |= rhs);
}
// operator ^=
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type& fixed_bit_field<N, F>::operator ^=(class_type const& rhs)
{
	m_field ^= rhs.field();
	return *this;
}
// operator ^
template<	e_size_t N
		,	typename_param_k F
		>
inline typename_type_ret_k fixed_bit_field<N, F>::
class_type const fixed_bit_field<N, F>::operator ^(class_type const& rhs) const
{
	return (class_type(rhs) ^= rhs);
}
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
#if defined(EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT)
template<	e_size_t N
		,	typename_param_k F
		>
EXTL_INLINE void swap(fixed_bit_field<N, F>& lhs, fixed_bit_field<N, F>& rhs)
{
	lhs.swap(rhs);
}
#endif


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE) && \
			defined(EXTL_FUNCTION_TEMPLATE_NON_TYPE_PARAM_SUPPORT)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	EXTL_NS(e_size_t) N
		,	typename_param_k F
		>
EXTL_INLINE void swap(EXTL_NS(fixed_bit_field)<N, F>& lhs, EXTL_NS(fixed_bit_field)<N, F>& rhs)
{
    lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_FIXED_BIT_FIELD_H */
/* //////////////////////////////////////////////////////////////////// */
