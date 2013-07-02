/* ///////////////////////////////////////////////////////////////////////
 * File:		matrix_rowe_iterator.h		
 *
 * Created:		08.12.05	
 * Updated:		08.12.05
 *
 * Brief:		The Matrix Row Entry Iterator
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_MATRIX_ROWE_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_MATRIX_ROWE_ITERATOR_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

template<	typename_param_k Val
		,	typename_param_k Mtx
        >
class const_matrix_rowe_iterator
	: public const_bidirectional_iterator_base	<	const_matrix_rowe_iterator<Val, Mtx>
												,	Val
												,	e_ptrdiff_t
												>
{
	private:
		typedef const_bidirectional_iterator_base	<	const_matrix_rowe_iterator<Val, Mtx>
													,	Val
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type;

	public:
		typedef const_matrix_rowe_iterator												class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k base_type::bool_type									bool_type;
		typedef Mtx																		matrix_type;
		typedef e_size_t																size_type;
		typedef size_type																index_type;

	private:
		index_type																		m_row;
		index_type																		m_current;
		matrix_type const*																m_pmatrix;

	public:
		const_matrix_rowe_iterator() 
			: m_row(0) 
			, m_current(0) 
			, m_pmatrix(NULL) 
		{}
		const_matrix_rowe_iterator(index_type row, index_type cur, matrix_type const& mx) 
			: m_row(row) 
			, m_current(cur) 
			, m_pmatrix(&mx) 
		{}	
		const_matrix_rowe_iterator(class_type const& it) 
			: m_row(it.m_row) 
			, m_current(it.m_current) 
			, m_pmatrix(it.m_pmatrix) 
		{}

	public:
		index_type				current() const				{ return m_current;										}
		index_type				current() 					{ return m_current;										}
		matrix_type const&		matrix() const				{ EXTL_ASSERT(NULL != m_pmatrix); return *m_pmatrix;	}

	public:
		void do_increase()
		{
			m_current = (m_current + 1) % (matrix().dim1() + 1);
		}
		void do_decrease()
		{
			m_current = (m_current + matrix().dim1() + 1 - 1) % (matrix().dim1() + 1);
		}
		const_reference do_dereference() const
		{
			return matrix().at(m_row, m_current);
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return (m_pmatrix == rhs.m_pmatrix) && current() == rhs.current();
		}
};
// matrix_rowe_iterator can be converted to const_matrix_rowe_iterator implicitly
template<	typename_param_k Val
		,	typename_param_k Mtx
        >
class matrix_rowe_iterator
	: public bidirectional_iterator_base<	matrix_rowe_iterator<Val, Mtx>
										,	const_matrix_rowe_iterator<Val, Mtx>
										,	Val
										,	e_ptrdiff_t
										>
{
	private:
		typedef bidirectional_iterator_base	<	matrix_rowe_iterator<Val, Mtx>
											,	const_matrix_rowe_iterator<Val, Mtx>
											,	Val
											,	e_ptrdiff_t
											>											base_type;
		typedef const_matrix_rowe_iterator<Val, Mtx>									const_iterator_type;
		typedef base_type																iterator_base_type;

	public:
		typedef matrix_rowe_iterator													class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k base_type::bool_type									bool_type;
		typedef typename_type_k base_type::index_type									index_type;
		typedef typename_type_k base_type::size_type									size_type;
		typedef typename_type_k base_type::matrix_type									matrix_type;

	public:
		matrix_rowe_iterator() 
			: base_type() 
		{}
		explicit_k matrix_rowe_iterator(index_type row, index_type cur, matrix_type const& mx) 
			: base_type(const_iterator_type(row, cur, mx)) 
		{}	
		matrix_rowe_iterator(class_type const& it) 
			: base_type(it)
		{}
		// const_matrix_rowe_iterator can be explicitly converted to matrix_rowe_iterator
		// because this is an empty member class
		explicit_k matrix_rowe_iterator(base_type const& it) 
			: base_type(it) 
		{}

};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_MATRIX_ROWE_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
