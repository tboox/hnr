/* ///////////////////////////////////////////////////////////////////////
 * File:		bit_array.h		
 *
 * Created:		08.10.02			
 * Updated:		08.10.02
 *
 * Brief:		The bit_array class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BIT_ARRAY_H
#define EXTL_CONTAINER_BIT_ARRAY_H

/*!\file bit_array.h
 *
 * \brief bit_array class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../algorithm/algorithm.h"
#include "detail/bit_array_iterator.h"
#include "../memory/buffer.h"
#include "../string/string.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief bit_array
 *
 * \param Fld The field type
 * \param Buf The buffer type
 *
 * \ingroup extl_group_container
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template<	typename_param_k Fld = e_size_t
		,	typename_param_k Buf = typename_type_def_k buffer_selector<Fld>::buffer_type
		>
#else
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
#endif
class bit_array
{
	/// \name Types
	/// @{
	public:
		typedef bit_array															class_type;
		typedef e_bool_t															bool_type;
		typedef e_size_t															size_type;
		typedef e_char_t															achar_type;
		typedef e_wchar_t															wchar_type;
		typedef size_type															index_type;
		typedef bool_type															value_type;
		typedef value_type*															pointer;
		typedef value_type const*													const_pointer;
		typedef value_type&															reference;
		typedef value_type const&													const_reference;
		typedef Fld																	field_type;	
		typedef Buf																	buffer_type;
		typedef typename_type_k buffer_type::allocator_type							allocator_type;
		typedef EXTL_NS_DETAIL(const_bit_array_iterator)<field_type, buffer_type>	const_iterator;
	/// @}

	/// \name Members
	private:
		buffer_type																	m_buffer;
		size_type																	m_size;
	/// @}

	private:
		enum { en_field_bit_count = 8 * sizeof(field_type) };

	/// \name Constructors
	/// @{
	public:
		/// Default Constructor
		bit_array()
		{
			clear();
		}
		/// Copy Constructor
		bit_array(class_type const& rhs)
		{
			assign(rhs);
		}
		/// Constructs with n-bits values from the given array
		bit_array(class_type const& rhs, size_type n)
		{
			assign(rhs, n);
		}
		/// Constructs with n-bits default values
		explicit_k bit_array(size_type n)
		{
			assign(value_type(), n);
		}
		/// Constructs with n-bits given values
		bit_array(const_reference value, size_type n)
		{
			assign(value, n);
		}
		/// Constructs with n-bits values from bool array
		bit_array(const_pointer p, size_type n)
		{
			assign(p, n);
		}
		/// Constructs from ascii string with null-terminator
		explicit_k bit_array(achar_type const* s)
		{
			assign(s);
		}
		/// Constructs from unicode string with null-terminator
		explicit_k bit_array(wchar_type const* s)
		{
			assign(s);
		}
		/// Constructs with n-bits values from ascii string
		bit_array(achar_type const* s, size_type n)
		{
			assign(s, n);
		}
		/// Constructs with n-bits values from unicode string
		bit_array(wchar_type const* s, size_type n)
		{
			assign(s, n);
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// Returns the allocator of the array
		allocator_type		allocator() const		{ return buffer().allocator();								}
		/// Returns the bit count
		size_type			size() const			{ return m_size;											}
		/// Returns the reserved bit count in the array
		size_type			capacity() const		{ return (buffer().capacity() * en_field_bit_count);		}
		/// Return \c true if size() == 0
		bool_type			is_empty() const		{ return 0 == m_size;										}
		/// Return \c true if size() == 0
		bool_type			empty() const			{ return is_empty();										}
		/// Return the maximum bit count of the array
		size_type			max_size()				{ return (buffer().max_size() * en_field_bit_count);		}
	/// @}

	/// \name Iterators
	/// @{
	public:
		/// Returns the const begin iterator
		const_iterator		begin() const			{ return const_iterator(&buffer(), 0);		}
		/// Returns the const end iterator
		const_iterator		end() const				{ return const_iterator(&buffer(), size());	}
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns the field value
		field_type const*	data() const			{ return buffer().data();	}
		/// Returns the field value
		field_type const*	fields() const			{ return buffer().data();	}
		/// Returns the numeric of this field
		field_type			numeric() const;
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

	/// \name Mutators
	/// @{
	public:
		/// Clears the field e.g. 001101 => null
		void				clear()					{ buffer().clear(); m_size = 0;	}
		/// Cleans the field e.g. 001101 => 000000
		void				clean()					{ buffer().clean();				}
		/// Swaps the content of array
		void				swap(class_type& rhs)	{ buffer().swap(rhs.buffer()); std_swap(m_size, rhs.m_size);	}
		/// Sets the value at the given position
		void				set(index_type index, const_reference value);
		/// Resizes the bit count of the array
		void				resize(size_type n, const_reference new_value = value_type());
		/// Pushes back the given value
		void				push_back(const_reference value)	{ resize(size() + 1, value);	}
		/// Pops back from this array
		void				pop_back()							{ resize(size() - 1);			}
		/// Sets the numeric
		void				numeric(field_type num)				{ buffer().assign(num, 1u); xtl_min(size_type(en_field_bit_count), size());		}
	/// @}

	/// \name Assignments
	/// @{
	public:
		/// Assigns from the given value
		class_type&			assign(const_reference value)				{ return assign(value, 1u);	}
		/// Assigns with n-bits given values
		class_type&			assign(const_reference value, size_type n);
		/// Assigns with n-bits values from bool array
		class_type&			assign(const_pointer p, size_type n);	
		/// Assigns with n-bits values from ascii string
		class_type&			assign(achar_type const* s, size_type n);
		/// Assigns with n-bits values from unicode string
		class_type&			assign(wchar_type const* s, size_type n);
		/// Assigns from ascii string with null-terminator
		class_type&			assign(achar_type const* s)					{ return assign(s, (NULL != s)? std_strlen(s) : 0);	}
		/// Assigns from unicode string with null-terminator
		class_type&			assign(wchar_type const* s)					{ return assign(s, (NULL != s)? std_strlen(s) : 0);	}
		/// Assigns from the given field
		class_type&			assign(class_type const& rhs, size_type n);
		/// Assigns from the given field
		class_type&			assign(class_type const& rhs)				{ return assign(rhs, rhs.size());	}
		/// Assigns from the given field
		class_type&			operator =(class_type const& rhs)			{ return assign(rhs);				}
		/// Assigns from the given value(fill all)
		class_type&			operator =(const_reference value)			{ return assign(value);				}
		/// Assigns from ascii string with null-terminator
		class_type&			operator =(achar_type const* s)				{ return assign(s);					}
		/// Assigns from unicode string with null-terminator
		class_type&			operator =(wchar_type const* s)				{ return assign(s);					}
	/// @}

	/// \name Appends
	/// @{
	public:
		/// Appends from the given value
		class_type&			append(const_reference value)				{ return append(value, 1);	}
		/// Appends with n-bits given values
		class_type&			append(const_reference value, size_type n);
		/// Appends with n-bits values from bool array
		class_type&			append(const_pointer p, size_type n);	
		/// Appends with n-bits values from ascii string
		class_type&			append(achar_type const* s, size_type n);
		/// Appends with n-bits values from unicode string
		class_type&			append(wchar_type const* s, size_type n);
		/// Appends from ascii string with null-terminator
		class_type&			append(achar_type const* s)					{ return append(s, (NULL != s)? std_strlen(s) : 0);	}
		/// Appends from unicode string with null-terminator
		class_type&			append(wchar_type const* s)					{ return append(s, (NULL != s)? std_strlen(s) : 0);	}
		/// Appends from the given field
		class_type&			append(class_type const& rhs, size_type n);
		/// Appends from the given field
		class_type&			append(class_type const& rhs)				{ return append(rhs, rhs.size());	}
		/// Appends from the given field
		class_type&			operator +=(class_type const& rhs)			{ return append(rhs);				}
		/// Appends from the given value
		class_type&			operator +=(const_reference value)			{ return append(value);				}
		/// Appends from ascii string with null-terminator
		class_type&			operator +=(achar_type const* s)			{ return append(s);					}
		/// Appends from unicode string with null-terminator
		class_type&			operator +=(wchar_type const* s)			{ return append(s);					}
	/// @}

	/// \name Replacements
	/// @{
	public:
		/// Replaces the given range [pos, pos + old_n) with the given bool array with n characters
		class_type&			replace(size_type pos, size_type old_n, const_pointer p, size_type n);
		/// Replaces the given range [pos, pos + old_n) with the given n values
		class_type&			replace(size_type pos, size_type old_n, const_reference value, size_type n);
		/// Replaces the given range [pos, pos + old_n) with the given ascii string with n characters
		class_type&			replace(size_type pos, size_type old_n, achar_type const* s, size_type n);
		/// Replaces the given range [pos, pos + old_n) with the given unicode string with n characters
		class_type&			replace(size_type pos, size_type old_n, wchar_type const* s, size_type n);
		/// Replaces the given range [pos, pos + old_n) with the given value
		class_type&			replace(size_type pos, size_type old_n, const_reference value)				{ return replace(pos, old_n, value, 1u);	}
		/// Replaces the given range [pos, pos + old_n) with the given ascii string 
		class_type&			replace(size_type pos, size_type old_n, achar_type const* s)				{ return replace(pos, old_n, s, (NULL != s)? std_strlen(s) : 0);	}
		/// Replaces the given range [pos, pos + old_n) with the given unicode string 
		class_type&			replace(size_type pos, size_type old_n, wchar_type const* s)				{ return replace(pos, old_n, s, (NULL != s)? std_strlen(s) : 0);	}
	/// @}

	/// \name Inserts
	/// @{
	public:
		/// Inserts the given bool array with n characters into the given position *this[pos] 
		class_type&			insert(size_type pos, const_pointer p, size_type n)			{ return replace(pos, 0, p, n);		}
		/// Inserts the given n values into the given position *this[pos] 
		class_type&			insert(size_type pos, const_reference value, size_type n)	{ return replace(pos, 0, value, n);	}
		/// Inserts the given ascii string with n characters into the given position *this[pos] 
		class_type&			insert(size_type pos, achar_type const* s, size_type n)		{ return replace(pos, 0, s, n);		}
		/// Inserts the given unicode string with n characters into the given position *this[pos] 
		class_type&			insert(size_type pos, wchar_type const* s, size_type n)		{ return replace(pos, 0, s, n);		}
		/// Inserts the given value into the given position *this[pos] 
		class_type&			insert(size_type pos, const_reference value)				{ return replace(pos, 0, value);	}
		/// Inserts the given ascii string  into the given position *this[pos] 
		class_type&			insert(size_type pos, achar_type const* s)					{ return replace(pos, 0, s);		}
		/// Inserts the given unicode string  into the given position *this[pos] 
		class_type&			insert(size_type pos, wchar_type const* s)					{ return replace(pos, 0, s);		}
	/// @}

	/// \name Erases
	/// @{
	public:
		/// Erases the given range [pos, pos + n)
		class_type&			erase(size_type pos, size_type n = 1u);
	/// @}

	/// \name Reverses
	/// @{
	public:
		/// Reverses this bit array with the given range [pos, pos + n)
		class_type&			reverse(size_type pos, size_type n);
		/// Reverses the whole bit array
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

	/// \name Helper
	/// @{
	private:
		buffer_type const&	buffer() const		{ return m_buffer;	}
		buffer_type&		buffer()			{ return m_buffer;	}
	/// @}

};
/* ///////////////////////////////////////////////////////////////////////
 * Implementation
 */

// at(checked)
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
value_type const bit_array<Fld, Buf>::at(index_type index) const
{
	EXTL_ASSERT_THROW((index / en_field_bit_count) < size(), index_error("out of range"));
	return get(index);
}
// get(unchecked)
template<	typename_param_k Fld
		,	typename_param_k Buf
		>inline typename_type_ret_k bit_array<Fld, Buf>::
value_type const bit_array<Fld, Buf>::get(index_type index) const
{
	// low bit => high bit
	EXTL_ASSERT((index / en_field_bit_count) < buffer().size());
	return (field_type(0x1) == ((buffer()[index / en_field_bit_count] >> (index % en_field_bit_count)) & field_type(0x1)));
}
// set 
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline void bit_array<Fld, Buf>::set(index_type index, const_reference value)
{
	index_type i = index / en_field_bit_count;
	index_type n = index % en_field_bit_count;

	EXTL_ASSERT(i < size());

	// low bit => high bit
	buffer()[i] &= ~(field_type(0x1) << n);
	buffer()[i] |= (static_cast<field_type>(value) << n);
}

// replace
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::replace(size_type pos, size_type old_n, const_pointer p, size_type n)
{
	EXTL_ASSERT(NULL != p);
	EXTL_ASSERT(pos >= 0 && pos < size());

	if (old_n == n)
	{
		EXTL_ASSERT((pos + n) <= size());
		for (index_type i = 0; i < n; ++i)
			set(pos + i, p[i]);
	}
	else
	{
		class_type tmp(*this);

		if (pos + old_n > size()) old_n = size() - pos;

		size_type new_n = size() - (old_n - n);
		EXTL_ASSERT(new_n <= max_size());

		resize(new_n);
		for (index_type i = 0; i < n; ++i)
			set(pos + i, p[i]);

		size_type left_n = tmp.size() - pos - old_n;
		for (index_type j = 0; j < left_n; ++j)
			set(pos + n + j, tmp[pos + old_n + j]);
	}

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::replace(size_type pos, size_type old_n, const_reference value, size_type n)
{
	EXTL_ASSERT(pos >= 0 && pos < size());
	if (old_n == n)
	{
		EXTL_ASSERT((pos + n) <= size());
		for (index_type i = 0; i < n; ++i)
			set(pos + i, value);
	}
	else
	{
		class_type tmp(*this);

		if (pos + old_n > size()) old_n = size() - pos;

		size_type new_n = size() - (old_n - n);
		EXTL_ASSERT(new_n <= max_size());

		resize(new_n);
		for (index_type i = 0; i < n; ++i)
			set(pos + i, value);

		size_type left_n = tmp.size() - pos - old_n;
		for (index_type j = 0; j < left_n; ++j)
			set(pos + n + j, tmp[pos + old_n + j]);
	}

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::replace(size_type pos, size_type old_n, achar_type const* s, size_type n)
{
	EXTL_ASSERT(NULL != s);
	EXTL_ASSERT(pos >= 0 && pos < size());

	if (old_n == n)
	{
		EXTL_ASSERT((pos + n) <= size());
		for (index_type i = 0; i < n; ++i)
			set(pos + i, s[i] != '0');
	}
	else
	{
		class_type tmp(*this);

		if (pos + old_n > size()) old_n = size() - pos;

		size_type new_n = size() - (old_n - n);
		EXTL_ASSERT(new_n <= max_size());

		resize(new_n);
		for (index_type i = 0; i < n; ++i)
			set(pos + i, s[i] != '0');

		size_type left_n = tmp.size() - pos - old_n;
		for (index_type j = 0; j < left_n; ++j)
			set(pos + n + j, tmp[pos + old_n + j]);
	}

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::replace(size_type pos, size_type old_n, wchar_type const* s, size_type n)
{
	EXTL_ASSERT(NULL != s);
	EXTL_ASSERT(pos >= 0 && pos < size());

	if (old_n == n)
	{
		EXTL_ASSERT((pos + n) <= size());
		for (index_type i = 0; i < n; ++i)
			set(pos + i, s[i] != L'0');
	}
	else
	{
		class_type tmp(*this);

		if (pos + old_n > size()) old_n = size() - pos;

		size_type new_n = size() - (old_n - old_n);
		EXTL_ASSERT(new_n <= max_size());

		resize(new_n);
		for (index_type i = 0; i < n; ++i)
			set(pos + i, s[i] != L'0');

		size_type left_n = tmp.size() - pos - old_n;
		for (index_type j = 0; j < left_n; ++j)
			set(pos + n + j, tmp[pos + old_n + j]);
	}

	return *this;
}

// assign
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::assign(const_reference value, size_type n)
{
	EXTL_ASSERT(n <= max_size());

	resize(n);
	for (index_type i = 0; i < n; ++i) 
		set(i, value);

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::assign(const_pointer p, size_type n)
{
	EXTL_ASSERT(n <= max_size());
	EXTL_ASSERT(NULL != p);

	resize(n);
	for (index_type i = 0; i < n; ++i) 
		set(i, p[i]);

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::assign(achar_type const* s, size_type n)
{
	EXTL_ASSERT(n <= max_size());
	EXTL_ASSERT(NULL != s);

	resize(n);
	for (index_type i = 0; i < n; ++i) 
		set(i, s[i] != '0');

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::assign(wchar_type const* s, size_type n)
{
	EXTL_ASSERT(n <= max_size());
	EXTL_ASSERT(NULL != s);

	resize(n);
	for (index_type i = 0; i < n; ++i) 
		set(i, s[i] != L'0');
	
	return *this;
}
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::assign(class_type const& rhs, size_type n)
{
	EXTL_ASSERT(n <= max_size());
	EXTL_ASSERT(n <= rhs.size());

	if (this != &rhs)
	{
		buffer().assign(rhs.buffer(), EXTL_ALIGN(n, en_field_bit_count) / en_field_bit_count);
		m_size = n;
	}
	return *this;
}
// append
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::append(const_reference value, size_type n)
{
	size_type bit_n = size() + n;
	EXTL_ASSERT(bit_n <= max_size());

	resize(bit_n, value);
	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::append(const_pointer p, size_type n)
{
	size_type bit_n = size();
	EXTL_ASSERT((bit_n + n) <= max_size());
	EXTL_ASSERT(NULL != p);

	resize(bit_n + n);
	for (index_type i = 0; i < n; ++i) 
		set(bit_n + i, p[i]);

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::append(achar_type const* s, size_type n)
{
	size_type bit_n = size();
	EXTL_ASSERT((bit_n + n) <= max_size());
	EXTL_ASSERT(NULL != s);

	resize(bit_n + n);
	for (index_type i = 0; i < n; ++i) 
		set(bit_n + i, s[i] != '0');

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::append(wchar_type const* s, size_type n)
{
	size_type bit_n = size();
	EXTL_ASSERT((bit_n + n) <= max_size());
	EXTL_ASSERT(NULL != s);

	resize(bit_n + n);
	for (index_type i = 0; i < n; ++i) 
		set(bit_n + i, s[i] != L'0');
	
	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::append(class_type const& rhs, size_type n)
{
	size_type bit_n = size();
	EXTL_ASSERT((bit_n + n) <= max_size());
	EXTL_ASSERT(n <= rhs.size());

	resize(bit_n + n);
	for (index_type i = 0; i < n; ++i)  
		set(bit_n + i, rhs[i]);

	return *this;
}

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::erase(size_type pos, size_type n)
{
	EXTL_ASSERT(n > 0);
	EXTL_ASSERT(pos >= 0 && pos < size());

	if (pos + n > size()) n = size() - pos;

	if ((0 == pos) && (n == size()))
	{
		clear();
	}
	else if (!(pos % en_field_bit_count) && !(n % en_field_bit_count))
	{
		buffer().erase(pos / en_field_bit_count, n / en_field_bit_count);
		m_size -= n;
	}
	else
	{
		class_type tmp(*this);
		resize(size() - n);
		size_type left_n = tmp.size() - pos - n;
		for (index_type i = 0; i < left_n; ++i)
			set(pos + i, tmp[pos + n + i]);
	}
	return *this;
}
// resize
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline void bit_array<Fld, Buf>::resize(size_type n, const_reference new_value)
{
	EXTL_ASSERT(n <= max_size());

	if (n <= size())
	{
		m_size = n;
		buffer().resize((n / en_field_bit_count) + 1);
	}
	else
	{
		index_type i = m_size;
		m_size = n;
		buffer().resize((n / en_field_bit_count) + 1);
		for (; i < n; ++i) 
			set(i, new_value);
	}
}
// reverse
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::reverse(size_type pos, size_type n)
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
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
field_type bit_array<Fld, Buf>::numeric() const
{
	field_type num = 0;
	field_type p2 = 1;

	size_type n = xtl_min(size_type(en_field_bit_count), size());
	for (index_type i = 0; i < n; ++i)
	{
		num += get(i) * p2;
		p2 <<= 1;
	}

	return num;
}
// make_numeric
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
field_type bit_array<Fld, Buf>::make_numeric(const_pointer p, size_type n, bool_type is_left_low)
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

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
field_type bit_array<Fld, Buf>::make_numeric(achar_type const* s, size_type n, bool_type is_left_low)
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

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
field_type bit_array<Fld, Buf>::make_numeric(wchar_type const* s, size_type n, bool_type is_left_low)
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
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type bit_array<Fld, Buf>::operator ~()
{
	class_type tmp(*this);
	size_type n = tmp.buffer().size();
	for (index_type i = 0; i < n; ++i)
	{
		tmp.buffer()[i] = ~tmp.buffer()[i];
	}
	return tmp;
}
// operator ==
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
bool_type bit_array<Fld, Buf>::operator ==(class_type const& rhs) const
{
	size_type bit_n = size();
	if (bit_n != rhs.size()) return e_false_v;

	size_type n = buffer().size();
	for (index_type i = 0; i < (n - 1); ++i)
	{
		if (buffer()[i] != rhs.buffer()[i])
			return e_false_v;
	}

	for (index_type j = (n - 1) * en_field_bit_count; j < bit_n; ++j)
	{
		if (get(j) != rhs.get(j))
			return e_false_v;
	}

	return e_true_v;
}
// operator &=
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::operator &=(class_type const& rhs)
{
	EXTL_ASSERT(size() == rhs.size());

	size_type n = buffer().size();
	for (index_type i = 0; i < n; ++i)
	{
		buffer()[i] &= rhs.buffer()[i];
	}

	return *this;
}
// operator &
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type const bit_array<Fld, Buf>::operator &(class_type const& rhs) const
{
	return (class_type(rhs) &= rhs);
}
// operator |=
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::operator |=(class_type const& rhs)
{
	EXTL_ASSERT(size() == rhs.size());

	size_type n = buffer().size();
	for (index_type i = 0; i < n; ++i)
	{
		buffer()[i] |= rhs.buffer()[i];
	}

	return *this;
}
// operator |
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type const bit_array<Fld, Buf>::operator |(class_type const& rhs) const
{
	return (class_type(rhs) |= rhs);
}
// operator ^=
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type& bit_array<Fld, Buf>::operator ^=(class_type const& rhs)
{
	EXTL_ASSERT(size() == rhs.size());

	size_type n = buffer().size();
	for (index_type i = 0; i < n; ++i)
	{
		buffer()[i] ^= rhs.buffer()[i];
	}

	return *this;
}
// operator ^
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
inline typename_type_ret_k bit_array<Fld, Buf>::
class_type const bit_array<Fld, Buf>::operator ^(class_type const& rhs) const
{
	return (class_type(rhs) ^= rhs);
}

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k Fld
		,	typename_param_k Buf
		>
EXTL_INLINE void swap(bit_array<Fld, Buf>& lhs, bit_array<Fld, Buf>& rhs)
{
	lhs.swap(rhs);
}

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

template<	typename_param_k Fld
		,	typename_param_k Buf
		>
EXTL_INLINE void swap(EXTL_NS(bit_array)<Fld, Buf>& lhs, EXTL_NS(bit_array)<Fld, Buf>& rhs)
{
    lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_BIT_ARRAY_H */
/* //////////////////////////////////////////////////////////////////// */
