/* ///////////////////////////////////////////////////////////////////////
 * File:		bit_field_iterator.h		
 *
 * Created:		08.10.02	
 * Updated:		08.10.02
 *
 * Brief:		bit_field_iterator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_BIT_FIELD_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_BIT_FIELD_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<typename_param_k F>
class const_bit_field_iterator
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
		typedef size_type																index_type;

	public:
		typedef const_bit_field_iterator												class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		
	private:
		field_type const*																m_field;
		index_type																		m_index;

	public:
		const_bit_field_iterator() 
			: m_field(NULL)
			, m_index(0)
		{}

		const_bit_field_iterator(field_type const* field, index_type index) 
			: m_field(field)
			, m_index(index)
		{}

	public:
		value_type const operator*() const
		{
			// low bit => high bit
			EXTL_ASSERT(m_index < 8 * sizeof(field_type));
			return (field_type(0x1) == (((*m_field) >> m_index) & field_type(0x1)));
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
#endif	/* EXTL_CONTAINER_DETAIL_BIT_FIELD_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
