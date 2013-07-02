/* ///////////////////////////////////////////////////////////////////////
 * File:		symmetrical_sparse_matrix_rowcole_iterator.h		
 *
 * Created:		08.12.08	
 * Updated:		08.12.08
 *
 * Brief:		The Symmetrical Sparse Matrix Column Entry Iterator
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_SYMMETRICAL_SPARSE_MATRIX_ROWCOLE_ITERATOR_H
#define EXTL_CONTAINER_DETAIL_SYMMETRICAL_SPARSE_MATRIX_ROWCOLE_ITERATOR_H

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
class const_symmetrical_sparse_matrix_rowcole_iterator
	: public const_bidirectional_iterator_base	<	const_symmetrical_sparse_matrix_rowcole_iterator<Val, Nod>
												,	Val
												,	e_ptrdiff_t
												>
{
	protected:
		typedef const_bidirectional_iterator_base	<	const_symmetrical_sparse_matrix_rowcole_iterator<Val, Nod>
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
		typedef const_symmetrical_sparse_matrix_rowcole_iterator							class_type;
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
		const_node_pointer																m_prhead;
		const_node_pointer																m_pchead;
		bool_type																		m_is_col;

	public:
		const_symmetrical_sparse_matrix_rowcole_iterator() 
			: m_current(NULL) 
			, m_prhead(NULL) 
			, m_pchead(NULL) 
			, m_is_col(e_true_v)
		{}
		const_symmetrical_sparse_matrix_rowcole_iterator(const_node_pointer cur, const_node_pointer prh, const_node_pointer pch) 
			: m_current(cur) 
			, m_prhead(prh) 
			, m_pchead(pch) 
			, m_is_col(e_true_v)
		{
			// empty column
			if (current() == chead())
				m_current = rhead();	// end()
			
			// if end()
			if (current() == rhead())
				m_is_col = e_false_v;
		}	
		const_symmetrical_sparse_matrix_rowcole_iterator(class_type const& it) 
			: m_current(it.m_current) 
			, m_prhead(it.m_prhead) 
			, m_pchead(it.m_pchead) 
			, m_is_col(it.m_is_col)
		{}

	public:
		const_node_pointer		current() const				{ return m_current;	}
		const_node_pointer		rhead() const				{ return m_prhead;	}
		const_node_pointer		chead() const				{ return m_pchead;	}
		bool_type				is_col() const				{ return m_is_col;	}
		bool_type				is_valid() const
		{
			if (NULL == current()) return e_false_v;
			if (NULL == rhead()) return e_false_v;
			if (NULL == chead()) return e_false_v;
			return e_true_v;
		}

	public:
		// start: chead()->bottom() => mid => end: rhead()
		/*     
		 *                          chead->bottom()
		 *                            |
		 *                0   0   0   1   0   0 
		 *                    0   0   2   0   0
		 *                        0   3   0   0
		 *  rhead->              (mid)4   5   6 
		 *                            5   0   0
		 *                            6       0
		 */
		void do_increase()
		{
			EXTL_ASSERT(is_valid());

			if (is_col())
			{
				// switch to row
				if (current()->bottom() == chead())
				{
					m_is_col = e_false_v;
					// exclude repeat node
					const_node_pointer mid = rhead()->right();
					if (mid == current())
						m_current = current()->right();
					else m_current = mid;
				}
				else m_current = current()->bottom();
			}
			else if (current() != rhead())
				m_current = current()->right();
			else;

			EXTL_ASSERT(is_valid());
		}
		// end: rhead() => mid => start: chead()->bottom()
		void do_decrease()
		{
			EXTL_ASSERT(is_valid());

			if (!is_col())
			{
				// switch to column
				if (current()->left() == rhead())
				{
					m_is_col = e_true_v;
					const_node_pointer mid = chead()->top();
					if (current() == mid)	// exclude repeat node
						m_current = current()->top();
					else m_current = mid;
				}
				else m_current = current()->left(); 
			}
			else if (current() != chead())
				m_current = current()->top();
			else;

			EXTL_ASSERT(is_valid());
		}
		const_reference do_dereference() const
		{
			EXTL_ASSERT(is_valid());

			EXTL_ASSERT(current() != chead());
			EXTL_ASSERT(current() != rhead());

			return current()->value();
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return (current() == rhs.current())
				&& (rhead() == rhs.rhead())
				&& (chead() == rhs.chead());
		}
};
// symmetrical_sparse_matrix_rowcole_iterator can be converted to const_symmetrical_sparse_matrix_rowcole_iterator implicitly
template<	typename_param_k Val
		,	typename_param_k Nod
        >
class symmetrical_sparse_matrix_rowcole_iterator
	: public bidirectional_iterator_base<	symmetrical_sparse_matrix_rowcole_iterator<Val, Nod>
										,	const_symmetrical_sparse_matrix_rowcole_iterator<Val, Nod>
										,	Val
										,	e_ptrdiff_t
										>
{
	private:
		typedef bidirectional_iterator_base	<	symmetrical_sparse_matrix_rowcole_iterator<Val, Nod>
											,	const_symmetrical_sparse_matrix_rowcole_iterator<Val, Nod>
											,	Val
											,	e_ptrdiff_t
											>											base_type;
		typedef const_symmetrical_sparse_matrix_rowcole_iterator<Val, Nod>					const_iterator_type;
		typedef base_type																iterator_base_type;
		typedef typename_type_k base_type::node_pointer									node_pointer;
		typedef typename_type_k base_type::const_node_pointer							const_node_pointer;
		typedef typename_type_k base_type::node_reference								node_reference;
		typedef typename_type_k base_type::const_node_reference							const_node_reference;

	public:
		typedef symmetrical_sparse_matrix_rowcole_iterator									class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k base_type::bool_type									bool_type;
		

	public:
		symmetrical_sparse_matrix_rowcole_iterator() 
			: base_type() 
		{}
		explicit_k symmetrical_sparse_matrix_rowcole_iterator(const_node_pointer cur, const_node_pointer prh, const_node_pointer pch) 
			: base_type(const_iterator_type(cur, prh, pch)) 
		{}	
		symmetrical_sparse_matrix_rowcole_iterator(class_type const& it) 
			: base_type(it)
		{}
		// const_symmetrical_sparse_matrix_rowcole_iterator can be explicitly converted to symmetrical_sparse_matrix_rowcole_iterator
		// because this is an empty member class
		explicit_k symmetrical_sparse_matrix_rowcole_iterator(base_type const& it) 
			: base_type(it) 
		{}

};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_SYMMETRICAL_SPARSE_MATRIX_ROWCOLE_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
