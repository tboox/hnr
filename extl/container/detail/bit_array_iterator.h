/* ///////////////////////////////////////////////////////////////////////
 * File:		bit_array_iterator.h		
 *
 * Created:		08.10.04	
 * Updated:		08.10.04
 *
 * Brief: bit_array iterator
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_BIT_ARRAY_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_BIT_ARRAY_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	typename_param_k F
		,	typename_param_k B
		>
class const_bit_array_iterator
	: public const_iterator_base<	std_bidirectional_iterator_tag
								,	e_bool_t
								,	e_ptrdiff_t
								>
{
	private:
		typedef const_iterator_base	<	std_bidirectional_iterator_tag
									,	e_bool_t
									,	e_ptrdiff_t
									>													base_type;
		typedef base_type																iterator_base_type;
		typedef e_bool_t																bool_type;
		typedef e_size_t																size_type;
		typedef F																		field_type;
		typedef B																		buffer_type;
		typedef size_type																index_type;

	public:
		typedef const_bit_array_iterator												class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		
	private:
		enum { en_field_bit_count = 8 * sizeof(field_type) };

	private:
		buffer_type const*																m_buffer;
		index_type																		m_index;

	public:
		const_bit_array_iterator() 
			: m_buffer(NULL)
			, m_index(0)
		{}

		const_bit_array_iterator(buffer_type const* buffer, index_type index) 
			: m_buffer(buffer)
			, m_index(index)
		{}

	public:
		value_type const operator*() const
		{
			EXTL_ASSERT((m_index / en_field_bit_count) < (*m_buffer).size());
			return (field_type(0x1) == (((*m_buffer)[m_index / en_field_bit_count] >> (m_index % en_field_bit_count)) & field_type(0x1)));
		}
		class_type& operator++()
		{
			++m_index;
			return (*this);
		}
		class_type operator++(int)
		{
			class_type tmp = *this;
			++*this;
			return (tmp);
		}
		class_type& operator--()
		{
			--m_index;
			return (*this);
		}
		class_type operator--(int)
		{
			class_type tmp = *this;
			--*this;
			return (tmp);
		}
		bool_type operator==(class_type const& rhs) const
		{
			return (m_index == rhs.m_index);
		}
		bool_type operator!=(class_type const& rhs) const
		{
			return !(*this == rhs);
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE


/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_BIT_ARRAY_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
