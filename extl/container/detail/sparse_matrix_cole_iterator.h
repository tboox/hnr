/* ///////////////////////////////////////////////////////////////////////
 * File:		sparse_matrix_cole_iterator.h		
 *
 * Created:		08.12.08	
 * Updated:		08.12.08
 *
 * Brief:		The Sparse Matrix Column Entry Iterator
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_SPARSE_MATRIX_COLE_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_SPARSE_MATRIX_COLE_ITERATOR_H

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
		,	typename_param_k Nod
		>
class const_sparse_matrix_cole_iterator
	: public const_bidirectional_iterator_base	<	const_sparse_matrix_cole_iterator<Val, Nod>
												,	Val
												,	e_ptrdiff_t
												>
{
	protected:
		typedef const_bidirectional_iterator_base	<	const_sparse_matrix_cole_iterator<Val, Nod>
													,	Val
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type;
		typedef Nod																		node_type;
		typedef node_type*																node_pointer;
		typedef node_type const*														const_node_pointer;
		typedef node_type&																node_reference;
		typedef node_type const&														const_node_reference;

	public:
		typedef const_sparse_matrix_cole_iterator										class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k base_type::bool_type									bool_type;

	private:
		const_node_pointer																m_current;

	public:
		const_sparse_matrix_cole_iterator() 
			: m_current(NULL) 
		{}
		const_sparse_matrix_cole_iterator(const_node_pointer cur) 
			: m_current(cur) 
		{}	
		const_sparse_matrix_cole_iterator(class_type const& it) 
			: m_current(it.m_current) 
		{}

	public:
		const_node_pointer		current() const				{ return m_current;	}

	public:
		void do_increase()
		{
			EXTL_ASSERT(NULL != current());
			m_current = current()->bottom(); 
		}
		void do_decrease()
		{
			EXTL_ASSERT(NULL != current());
			m_current = current()->top(); 
		}
		const_reference do_dereference() const
		{
			EXTL_ASSERT(NULL != current());
			return current()->value();
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return (current() == rhs.current());
		}
};
// sparse_matrix_cole_iterator can be converted to const_sparse_matrix_cole_iterator implicitly
template<	typename_param_k Val
		,	typename_param_k Nod
		>
class sparse_matrix_cole_iterator
	: public bidirectional_iterator_base<	sparse_matrix_cole_iterator<Val, Nod>
										,	const_sparse_matrix_cole_iterator<Val, Nod>
										,	Val
										,	e_ptrdiff_t
										>
{
	private:
		typedef bidirectional_iterator_base	<	sparse_matrix_cole_iterator<Val, Nod>
											,	const_sparse_matrix_cole_iterator<Val, Nod>
											,	Val
											,	e_ptrdiff_t
											>											base_type;
		typedef const_sparse_matrix_cole_iterator<Val, Nod>								const_iterator_type;
		typedef base_type																iterator_base_type;
		typedef typename_type_k base_type::node_pointer									node_pointer;
		typedef typename_type_k base_type::const_node_pointer							const_node_pointer;
		typedef typename_type_k base_type::node_reference								node_reference;
		typedef typename_type_k base_type::const_node_reference							const_node_reference;

	public:
		typedef sparse_matrix_cole_iterator												class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k base_type::bool_type									bool_type;
		

	public:
		sparse_matrix_cole_iterator() 
			: base_type() 
		{}
		explicit_k sparse_matrix_cole_iterator(const_node_pointer cur) 
			: base_type(const_iterator_type(cur)) 
		{}	
		sparse_matrix_cole_iterator(class_type const& it) 
			: base_type(it)
		{}
		// const_sparse_matrix_cole_iterator can be explicitly converted to sparse_matrix_cole_iterator
		// because this is an empty member class
		explicit_k sparse_matrix_cole_iterator(base_type const& it) 
			: base_type(it) 
		{}

};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_SPARSE_MATRIX_COLE_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
