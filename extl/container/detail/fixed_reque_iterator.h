/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_reque_iterator.h		
 *
 * Created:		08.09.23	
 * Updated:		08.09.23
 *
 * Brief: 9fixed_reque iterator
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_FIXED_REQUE_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_FIXED_REQUE_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<typename_param_k Val>
class const_fixed_reque_iterator
	: public const_bidirectional_iterator_base	<	const_fixed_reque_iterator<Val>
												,	Val
												,	e_ptrdiff_t
												>
{
	private:
		typedef const_bidirectional_iterator_base	<	const_fixed_reque_iterator<Val>
													,	Val
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type; 
		typedef e_bool_t																bool_type;
		typedef e_size_t																size_type;

	public:
		typedef const_fixed_reque_iterator												class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		
	private:
		size_type																		m_index;
		pointer																			m_buffer;
		size_type const*																m_phead;
		size_type																		m_max_size;

	public:
		const_fixed_reque_iterator() 
			: m_index(0)
			, m_buffer(NULL)
			, m_phead(NULL)
			, m_max_size(0) 
		{}
		const_fixed_reque_iterator(size_type index, pointer buffer, size_type const* phead, size_type max_size) 
			: m_index(index)
			, m_buffer(buffer)
			, m_phead(phead)
			, m_max_size(max_size) 
		{}
		const_fixed_reque_iterator(class_type const& it) 
			: m_index(const_cast<class_type&>(it).m_index)
			, m_buffer(const_cast<class_type&>(it).m_buffer) 
			, m_phead(const_cast<class_type&>(it).m_phead) 
			, m_max_size(const_cast<class_type&>(it).m_max_size) 
			
		{}

	public:
		void do_increase()
		{
			++m_index;
		}
		void do_decrease()
		{
			--m_index;
		}
		const_reference do_dereference() const
		{
			EXTL_ASSERT(m_buffer != NULL);
			EXTL_ASSERT(m_phead != NULL);
			EXTL_ASSERT(m_max_size > 0);

			return m_buffer[(m_max_size + *m_phead + m_index) % m_max_size];
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return m_index == rhs.m_index;
		}
};
// fixed_reque_iterator can be converted to const_fixed_reque_iterator implicitly
template<typename_param_k Val>
class fixed_reque_iterator
	: public bidirectional_iterator_base<	fixed_reque_iterator<Val>
										,	const_fixed_reque_iterator<Val>
										,	Val
										,	e_ptrdiff_t
										>
{
	private:
		typedef bidirectional_iterator_base<	fixed_reque_iterator<Val>
											,	const_fixed_reque_iterator<Val>
											,	Val
											,	e_ptrdiff_t
											>											base_type;
		typedef const_fixed_reque_iterator<Val>											const_iterator_type;
		typedef base_type																iterator_base_type;		
		typedef e_bool_t																bool_type;
		typedef e_size_t																size_type;

	public:
		typedef fixed_reque_iterator													class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;

	public:
		fixed_reque_iterator() 
			: base_type()
		{}
		fixed_reque_iterator(size_type index, pointer buffer, size_type const* phead, size_type max_size) 
			: base_type(const_iterator_type(index, buffer, phead, max_size))
		{}
		fixed_reque_iterator(class_type const& it) 
			: base_type(it)
		{}
		// const_fixed_reque_iterator can be explicitly converted to fixed_reque_iterator
		explicit_k fixed_reque_iterator(const_iterator_type const& it) 
			: base_type(it) 
		{}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_END_NAMESPACE
EXTL_DETAIL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_FIXED_REQUE_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
