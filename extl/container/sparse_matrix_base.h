/* ///////////////////////////////////////////////////////////////////////
 * File:		sparse_matrix_base.h		
 *
 * Created:		08.12.07			
 * Updated:		08.12.08
 *
 * Brief:		sparse_matrix_base class - fixed-size
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_SPARSE_MATRIX_BASE_H
#define EXTL_CONTAINER_SPARSE_MATRIX_BASE_H

/*!\file sparse_matrix_base.h
 * \brief sparse_matrix_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "../algorithm/algorithm.h"
#include "list.h"
#include "detail/sparse_matrix_rowe_iterator.h"
#include "detail/sparse_matrix_cole_iterator.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief sparse_matrix_base
 *
 * <pre>
 *                                                          (empty node: point to self)
 *                           ---   ---               ---   ---        --   --
 *        (dim1)            |   | |   |             |   | |   |      |  | |  |
 *        cheads:   [0]     |   [1]   |     [2]     |   [3]   |      |->[4]<-|
 * rheads                   |   | |   |             |   | |   |      |  | |  |
 * (dim0)                   |   | |   |             |   | |   |      '--' '--'
 *  [0] --------------------|->(val)--|-            |   | |   |
 *   | `--------------------|--'| |   | |           |   | |   |
 *   '----------------------|---|-|---|-'           |   | |   |
 *                          |   | |   |             |   | |   |
 *                          |   | |   |             |   | |   |
 *  [1]                     |   | |   |             |   | |   |
 *                          |   | |   |             |   | |   |
 *                          |   | |   |             |   | |   |
 *                          |   | |   |             |   | |   |
 *                          |   | |   |             |   | |   |
 *  [2] --------------------|->(val)--|-------------|->(val)--|-
 *   | `--------------------|--'| |`--|-------------|--'| |   | |
 *   |                      '---' '---'             '---' '---' |
 *   '----------------------------------------------------------'
 *
 * </pre>
 *
 * \param Dev The derived type
 * \param Val The value type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k Dev
		,	typename_param_k Val
		>
class sparse_matrix_base
{
	/// \name Types
	/// @{
	public:
		typedef sparse_matrix_base														class_type;
		typedef Dev																		derived_type;
		typedef Val																		value_type;
		typedef Val*																	pointer;
		typedef Val const*																const_pointer;
		typedef Val&																	reference;
		typedef Val const&																const_reference;
		typedef e_size_t																size_type;
		typedef e_bool_t																bool_type;
		typedef e_ptrdiff_t																difference_type;
		typedef	e_int_t																	int_type;	
		typedef size_type																index_type;
		typedef typename_type_k list_selector<value_type>::list_type					list_type;
		typedef typename_type_k list_type::allocator_type								allocator_type;
		typedef typename_type_k list_type::iterator										iterator;
		typedef typename_type_k list_type::const_iterator								const_iterator;
		typedef typename_type_k list_type::reverse_iterator								reverse_iterator;
		typedef typename_type_k list_type::const_reverse_iterator						const_reverse_iterator;
		class const_reduced_dimension_type
		{
			private:
				derived_type const*						m_this;
				index_type								m_i;
				size_type								m_dim;

			public:
				const_reduced_dimension_type(derived_type const* p, index_type i)
					: m_this(p)
					, m_i(i)
				{}
			public:
				const_reference	operator[](index_type j) const
				{
					return at_unchecked(j);
				}
			#if EXTL_WORKAROUND_DMC(<, 0x0850)
				const_reference	at(index_type j) const
				{
					return static_cast<class_type const*>(m_this)->at(m_i, j);
				}
				const_reference	at_unchecked(index_type j) const
				{
					return static_cast<class_type const*>(m_this)->at_unchecked(m_i, j);
				}
			#else
				const_reference	at(index_type j) const
				{
					return m_this->at(m_i, j);
				}
				const_reference	at_unchecked(index_type j) const
				{
					return m_this->at_unchecked(m_i, j);
				}
			#endif
		};
		class reduced_dimension_type
		{
			private:
				derived_type const*						m_this;
				index_type								m_i;
				size_type								m_dim;

			public:
				reduced_dimension_type(derived_type const* p, index_type i)
					: m_this(p)
					, m_i(i)
				{}
			public:
				reference	operator[](index_type j) 
				{
					return at_unchecked(j);
				}
			#if EXTL_WORKAROUND_DMC(<, 0x0850)
				reference	at(index_type j) 
				{
					return const_cast<reference>(static_cast<class_type const*>(m_this)->at(m_i, j));
				}
				reference	at_unchecked(index_type j) 
				{
					return const_cast<reference>(static_cast<class_type const*>(m_this)->at_unchecked(m_i, j));
				}
			#else
				reference	at(index_type j) 
				{
					return const_cast<reference>(m_this->at(m_i, j));
				}
				reference	at_unchecked(index_type j) 
				{
					return const_cast<reference>(m_this->at_unchecked(m_i, j));
				}
			#endif
		};
	/// @}

	/// \name Protected Types
	/// @{
	protected:
		/// node_type
		struct node_type
		{
			/// \name Members
			/// @{
			private:
				index_type					m_i0;	//!< row
				index_type					m_i1;	//!< col

				node_type const*			m_top;
				node_type const*			m_bottom;
				node_type const*			m_left;
				node_type const*			m_right;

				const_iterator				m_pos;
			/// @}
			
			/// \name Attributes
			/// @{
			public:
				index_type					row() const						{ return m_i0;	}
				void						row(index_type i0)				{ m_i0 = i0;	}

				index_type					col() const						{ return m_i1;	}
				void						col(index_type i1)				{ m_i1 = i1;	}

				iterator					pos()							{ return iterator(m_pos);	}
				const_iterator				pos() const						{ return m_pos;				}
				void						pos(const_iterator p)			{ m_pos = p;				}

				const_reference				value() const					{ return *(pos());	}
				reference					value()							{ return *(pos());	}
				void						value(const_reference v)		{ *(pos()) = v;		}

				node_type const*			top() const						{ return m_top;								}
				node_type*					top()							{ return const_cast<node_type*>(m_top);		}
				void						top(node_type const* node)		{ m_top = node;								}
			
				node_type const*			bottom() const					{ return m_bottom;							}
				node_type*					bottom()						{ return const_cast<node_type*>(m_bottom);	}
				void						bottom(node_type const* node)	{ m_bottom = node;							}

				node_type const*			left() const					{ return m_left;							}
				node_type*					left()							{ return const_cast<node_type*>(m_left);	}
				void						left(node_type const* node)		{ m_left = node;							}

				node_type const*			right() const					{ return m_right;							}
				node_type*					right()							{ return const_cast<node_type*>(m_right);	}
				void						right(node_type const* node)	{ m_right = node;							}
			
				bool_type					is_empty() const				{ return (top() == this) && (bottom() == this) && (left() == this) && (right() == this);	}
			/// @}

			/// \name Mutators
			/// @{
			public:
				void						init()							{ clear();	}
				void						clear()	
				{
					m_i0		= 0;
					m_i1		= 0;

					/*!point to self:
					 * <pre>
					 * self-reference:
					 *                      --------
					 *                     |        |
					 *                -----------  -
					 *               |    top    |
					 *       ----------------------------
					 *    --| left      value      right |---
					 *   |   ----------------------------    |
					 *   |    |      |  bottom  |       |    |
					 *    ----     -- ----------         ----
					 *            |       |
					 *             -------
					 *
					 * </pre>
					 */
					m_top		= this;
					m_bottom	= this;
					m_left		= this;
					m_right		= this;

					m_pos		= const_iterator();
				}
			/// @}

		};
		typedef node_type*																	node_pointer;
		typedef node_type const*															const_node_pointer;
		typedef node_type&																	node_reference;
		typedef node_type const&															const_node_reference;
		typedef typename_type_k buffer_selector<node_type>::buffer_type						buffer_type;
		typedef typename_type_k buffer_type::allocator_type									node_allocator_type;
		typedef buffer_type																	rheads_type;
		typedef buffer_type																	cheads_type;
	/// @}

	/// \name Iterator Types
	/// \note cannot insert and erase nodes in the iteration 
	/// @{
	public:
		// row element iterator
		typedef EXTL_NS_DETAIL(sparse_matrix_rowe_iterator)<value_type, node_type>			rowe_iterator;
		typedef EXTL_NS_DETAIL(const_sparse_matrix_rowe_iterator)<value_type, node_type>	const_rowe_iterator;
		typedef reverse_bidirectional_iterator_base<const_rowe_iterator>					rowe_reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_rowe_iterator>				const_rowe_reverse_iterator;

		// column element iterator
		typedef EXTL_NS_DETAIL(sparse_matrix_cole_iterator)<value_type, node_type>			cole_iterator;
		typedef EXTL_NS_DETAIL(const_sparse_matrix_cole_iterator)<value_type, node_type>	const_cole_iterator;
		typedef reverse_bidirectional_iterator_base<const_cole_iterator>					cole_reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_cole_iterator>				const_cole_reverse_iterator;
	/// @}

	public:
		/// The dimension of the matrix
		EXTL_STATIC_MEMBER_CONST(size_type, dimension = 2);

	/// \name Members
	/// @{
	private:
		list_type																			m_nodes;	//!< nodes list
		rheads_type																			m_rheads;	//!< row heads
		cheads_type																			m_cheads;	//!< col heads
	/// @}

	private:
		/*!\brief Prohibit the following case:
		 * 
		 * \code
			Dev da, db;
			B &ba = da, &bb = db;
			ba = bb;
			B b(ba);
		 * \endcode
		 */
		sparse_matrix_base(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		sparse_matrix_base()
			: m_nodes()
			, m_rheads()
			, m_cheads()
		{
			derive().init();
			EXTL_ASSERT(derive().is_valid());
		}
		explicit_k sparse_matrix_base(derived_type const& rhs)
			: m_nodes()
			, m_rheads()
			, m_cheads()
		{
			EXTL_ASSERT(rhs.is_valid());
			derive().assign(rhs);
			EXTL_ASSERT(derive().is_valid());
		}
		// d0 * d1
		sparse_matrix_base(index_type d0, index_type d1)
			: m_nodes()
			, m_rheads(d0)
			, m_cheads(d1)
		{
			derive().init();
			EXTL_ASSERT(derive().is_valid());
		}
		~sparse_matrix_base()
		{
			destroy();
		}
	/// @}
	

	/// \name Attributes
	/// @{
	public:
		allocator_type		allocator() const		{ return nodes().allocator();		}
		size_type			dim0() const			{ return cheads().size();			}
		size_type			dim1() const			{ return rheads().size();			}
		size_type			row() const				{ return derive().dim0();			}
		size_type			col() const				{ return derive().dim1();			}
		size_type			size() const			{ return dim0() * dim1();			}
		size_type			nodes_size() const		{ return nodes().size();			}
		bool_type			is_empty() const		{ return nodes().is_empty();		}
		bool_type			empty() const			{ return nodes().is_empty();		}
		size_type			max_size()				{ return dim0() * dim1();			}
		bool_type			exists(index_type i0, index_type i1) const;
		bool_type			is_valid() const;
	/// @}

	/// \name Mutators
	/// @{
	public:
		/// swap *this & rhs
		void				swap(derived_type& rhs);
		/// clear *this
		void				clear();

		/// insert an element
		const_reference		insert(index_type i0, index_type i1, const_reference value, bool_type* has_existed = NULL);
		/// erase an element
		void				erase(index_type i0, index_type i1, bool_type* has_existed = NULL);

		/// erase the whole row 
		/// \note non-exception-safe, please use it carefully
		size_type			erase_row(index_type i0);
		/// erase the whole column
		/// \note non-exception-safe, please use it carefully
		size_type			erase_col(index_type i1);

		/// assigment
		/// \note non-exception-safe, please use it carefully
		derived_type&		assign(derived_type const& rhs);
		/// assigment
		derived_type&		operator =(derived_type const& rhs);
		/// assigment
		derived_type&		operator =(const_reference value);
	/// @}

	/// \name Accessors
	/// @{
	public:
		// note: insert an empty node if not exists 
		reference						at(index_type i0, index_type i1);
		const_reference					at(index_type i0, index_type i1) const;

		reference						at_unchecked(index_type i0, index_type i1);
		const_reference					at_unchecked(index_type i0, index_type i1) const;

		reduced_dimension_type			at(index_type i0);
		const_reduced_dimension_type	at(index_type i0) const;

		reduced_dimension_type			at_unchecked(index_type i0);
		const_reduced_dimension_type	at_unchecked(index_type i0) const;

		reduced_dimension_type			operator[](index_type i0)		{ return at_unchecked(i0);	}
		const_reduced_dimension_type	operator[](index_type i0) const	{ return at_unchecked(i0);	}

		bool_type						get_if_exists(index_type i0, index_type i1, reference ret) const;
		bool_type						set_if_exists(index_type i0, index_type i1, const_reference val);
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator				begin() const			{ return nodes().begin();	}
		iterator					begin()					{ return nodes().begin();	}

		const_iterator				end() const				{ return nodes().end();		}
		iterator					end()					{ return nodes().end();		}
	
		const_reverse_iterator		rbegin() const			{ return nodes().rbegin();	}
		reverse_iterator			rbegin()				{ return nodes().rbegin();	}
	
		const_reverse_iterator		rend() const			{ return nodes().rend();	}
		reverse_iterator			rend()					{ return nodes().rend();	}
	/// @}

	/// \name Row Element Iterators
	/// \note cannot insert and erase nodes in the iteration 
	/// @{
	public:
		const_rowe_iterator			rowe_begin(index_type i0) const		{ return const_rowe_iterator(rheads()[i0].right());				}
		rowe_iterator				rowe_begin(index_type i0)			{ return rowe_iterator(rheads()[i0].right());					}

		const_rowe_iterator			rowe_end(index_type i0) const		{ return const_rowe_iterator(&(rheads()[i0]));					}
		rowe_iterator				rowe_end(index_type i0)				{ return rowe_iterator(&(rheads()[i0]));						}
	
		const_rowe_reverse_iterator	rowe_rbegin(index_type i0) const	{ return const_rowe_reverse_iterator(rowe_end(i0));				}
		rowe_reverse_iterator		rowe_rbegin(index_type i0)			{ return rowe_reverse_iterator(rowe_end(i0));					}
	
		const_rowe_reverse_iterator	rowe_rend(index_type i0) const		{ return const_rowe_reverse_iterator(rowe_begin(i0));			}
		rowe_reverse_iterator		rowe_rend(index_type i0)			{ return rowe_reverse_iterator(rowe_begin(i0));					}
	/// @}

	/// \name Column Element Iterators
	/// \note cannot insert and erase nodes in the iteration 
	/// @{
	public:
		const_cole_iterator			cole_begin(index_type i1) const		{ return const_cole_iterator(cheads()[i1].bottom());			}
		cole_iterator				cole_begin(index_type i1)			{ return cole_iterator(cheads()[i1].bottom());					}

		const_cole_iterator			cole_end(index_type i1) const		{ return const_cole_iterator(&(cheads()[i1]));					}
		cole_iterator				cole_end(index_type i1)				{ return cole_iterator(&(cheads()[i1]));						}
	
		const_cole_reverse_iterator	cole_rbegin(index_type i1) const	{ return const_cole_reverse_iterator(cole_end(i1));				}
		cole_reverse_iterator		cole_rbegin(index_type i1)			{ return cole_reverse_iterator(cole_end(i1));					}
	
		const_cole_reverse_iterator	cole_rend(index_type i1) const		{ return const_cole_reverse_iterator(cole_begin(i1));			}
		cole_reverse_iterator		cole_rend(index_type i1)			{ return cole_reverse_iterator(cole_begin(i1));					}
	/// @}

	/// \name Others
	/// @{
	protected:
		derived_type&		derive()				{ return static_cast<derived_type&>(*this);			}
		derived_type const&	derive() const			{ return static_cast<derived_type const&>(*this);	}

		buffer_type&		rheads()				{ return m_rheads;									}
		buffer_type const&	rheads() const			{ return m_rheads;									}

		buffer_type&		cheads()				{ return m_cheads;									}
		buffer_type const&	cheads() const			{ return m_cheads;									}

		list_type&			nodes()					{ return m_nodes;									}
		list_type const&	nodes()	const			{ return m_nodes;									}

		node_allocator_type	node_allocator() const	{ return node_allocator_type();						}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		void				init();
		void				destroy();

		node_pointer		create_node(index_type i0, index_type i1, const_reference value = value_type());
		void				destroy_node(node_pointer node);
		void				destroy_nodes();

		node_pointer		erase_from_row(index_type i0, index_type i1, bool_type* has_existed);
		node_pointer		erase_from_col(index_type i0, index_type i1, bool_type* has_existed);

		void				insert_into_row(node_pointer node, bool_type* has_existed);
		void				insert_into_col(node_pointer node, bool_type* has_existed);
	/// @}
};
/* Template declaration */
#ifdef EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
#	undef EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
#endif

#define EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL		\
template<	typename_param_k Dev					\
		,	typename_param_k Val					\
		>

/* Class qualification */
#ifdef EXTL_SPARSE_MATRIX_BASE_QUAL
#	undef EXTL_SPARSE_MATRIX_BASE_QUAL
#endif

#define EXTL_SPARSE_MATRIX_BASE_QUAL	sparse_matrix_base<Dev, Val>

/* Class qualification */
#ifdef EXTL_SPARSE_MATRIX_BASE_RET_QUAL
#	undef EXTL_SPARSE_MATRIX_BASE_RET_QUAL
#endif

#define EXTL_SPARSE_MATRIX_BASE_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_SPARSE_MATRIX_BASE_QUAL::ret_type \
					EXTL_SPARSE_MATRIX_BASE_QUAL
/* /////////////////////////////////////////////////////////////////////////
 * Implemention
 */
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(node_pointer)::create_node(index_type i0, index_type i1, const_reference value)
{
	/// allocate a new node
	node_pointer node = node_allocator().allocate(1);
	EXTL_ASSERT(node != NULL);
	if (NULL == node) return NULL;
	
	const_iterator pos;
	EXTL_TRY
		node->init();
		node->row(i0);
		node->col(i1);
		pos = nodes().insert(nodes().end(), value);
		node->pos(pos);
	EXTL_CATCH_ALL
		nodes().erase(pos);
		node_allocator().deallocate(node);
		// reraise
		EXTL_THROW;
	EXTL_CATCH_END

	return node;

}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::destroy_node(node_pointer node)
{
	EXTL_ASSERT(node != NULL);
	if (NULL == node) return ;
	nodes().erase(node->pos());
	node->clear();
	node_allocator().deallocate(node);
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::insert_into_row(node_pointer node, bool_type* has_existed)
{
	EXTL_ASSERT(NULL != node);
	index_type row = node->row();
	index_type col = node->col();

	// insert node after rheads()[row]
	if (rheads()[row].is_empty())
	{
		rheads()[row].right(node);
		node->right(&(rheads()[row]));
		rheads()[row].left(node);
		node->left(&(rheads()[row]));

		if (NULL != has_existed) *has_existed = e_false_v;
		return ;
	}

	// find insertion point
	node_pointer rp = rheads()[row].right();
	EXTL_ASSERT(NULL != rp);
	for (; &(rheads()[row]) != rp && rp->col() < col; rp = rp->right());
	
	if (rp != &(rheads()[row]))
	{
		if (rp->col() != col)	// insert node if node not exists
		{
			EXTL_ASSERT(rp->col() > col);
			rp->left()->right(node);
			node->left(rp->left());
			rp->left(node);
			node->right(rp);

			if (NULL != has_existed) *has_existed = e_false_v;
		}
		else	// update node if node already exists
		{
			rp->value(node->value());
			if (NULL != has_existed) *has_existed = e_true_v;
		}
	}
	else	// insert node before rheads()[row], that is at last position
	{
		rp->left()->right(node);
		node->left(rp->left());
		rp->left(node);
		node->right(rp);

		if (NULL != has_existed) *has_existed = e_false_v;
	}
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(node_pointer)::erase_from_row(index_type i0, index_type i1, bool_type* has_existed)
{
	index_type row = i0;
	index_type col = i1;

	if (rheads()[row].is_empty()) 
	{
		if (NULL != has_existed) *has_existed = e_false_v;
		return NULL;
	}

	// find position
	node_pointer rp = rheads()[row].right();
	EXTL_ASSERT(NULL != rp);
	for (; &(rheads()[row]) != rp && rp->col() < col; rp = rp->right());

	// node not exists
	if (rp == &(rheads()[row]) || rp->col() != col) 
	{
		if (NULL != has_existed) *has_existed = e_false_v;
		return NULL;
	}
	
	// erase node
	rp->left()->right(rp->right());
	rp->right()->left(rp->left());

	if (NULL != has_existed) *has_existed = e_true_v;
	return rp;
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::insert_into_col(node_pointer node, bool_type* has_existed)
{
	EXTL_ASSERT(NULL != node);
	index_type row = node->row();
	index_type col = node->col();

	// insert node after cheads()[col]
	if (cheads()[col].is_empty())
	{
		cheads()[col].bottom(node);
		node->bottom(&(cheads()[col]));
		cheads()[col].top(node);
		node->top(&(cheads()[col]));
		if (NULL != has_existed) *has_existed = e_false_v;
		return ;
	}

	// find insertion point
	node_pointer cp = cheads()[col].bottom();
	EXTL_ASSERT(NULL != cp);
	for (; &(cheads()[col]) != cp && cp->row() < row; cp = cp->bottom());

	if (cp != &(cheads()[col]))
	{
		if (cp->row() != row)	// insert node if node not exists
		{
			EXTL_ASSERT(cp->row() > row);
			cp->top()->bottom(node);
			node->top(cp->top());
			cp->top(node);
			node->bottom(cp);
			if (NULL != has_existed) *has_existed = e_false_v;
		}
		else	// update node if node already exists
		{
			cp->value(node->value());
			if (NULL != has_existed) *has_existed = e_true_v;
		}
	}
	else	// insert node before cheads()[col], that is at last position
	{
		cp->top()->bottom(node);
		node->top(cp->top());
		cp->top(node);
		node->bottom(cp);
		if (NULL != has_existed) *has_existed = e_false_v;
	}
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(node_pointer)::erase_from_col(index_type i0, index_type i1, bool_type* has_existed)
{
	index_type row = i0;
	index_type col = i1;

	if (cheads()[col].is_empty()) 
	{
		if (NULL != has_existed) *has_existed = e_false_v;
		return NULL;
	}

	// find position
	node_pointer cp = cheads()[col].bottom();
	EXTL_ASSERT(NULL != cp);
	for (; &(cheads()[col]) != cp && cp->row() < row; cp = cp->bottom());

	// node not exists
	if (cp == &(cheads()[col]) || cp->row() != row) 
	{
		if (NULL != has_existed) *has_existed = e_false_v;
		return NULL;
	}
	
	// erase node
	cp->top()->bottom(cp->bottom());
	cp->bottom()->top(cp->top());

	if (NULL != has_existed) *has_existed = e_true_v;

	return cp;
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(const_reference)::insert(index_type i0, index_type i1, const_reference value, bool_type* has_existed)
{
	EXTL_MESSAGE_ASSERT(i0 < dim0() && i1 < dim1(), "out of range");
	EXTL_ASSERT(derive().is_valid());
	
	// create node
	node_pointer node = create_node(i0, i1, value);
	EXTL_ASSERT(NULL != node);

	size_type step = 0;
	EXTL_TRY
		derive().insert_into_row(node, has_existed);
		step = 1;
		derive().insert_into_col(node, has_existed);
	EXTL_CATCH_ALL
		switch (step)
		{
		case 1:
			derive().erase_from_row(i0, i1, has_existed);
		case 0:
			destroy_node(node);
		}
		// reraise
		EXTL_THROW;
	EXTL_CATCH_END

	EXTL_ASSERT(derive().is_valid());

	return *(node->pos());
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::erase(index_type i0, index_type i1, bool_type* has_existed)
{
	EXTL_MESSAGE_ASSERT(i0 < dim0() && i1 < dim1(), "out of range");
	EXTL_ASSERT(derive().is_valid());
	
	if (!(i0 < dim0())) return ;
	if (!(i1 < dim1())) return ;
	
	node_pointer node = NULL;
	size_type step = 0;
	EXTL_TRY
		node = derive().erase_from_row(i0, i1, has_existed);
		step = 1;
		node = derive().erase_from_col(i0, i1, has_existed);
		step = 2;
		if (NULL != node) destroy_node(node);
	EXTL_CATCH_ALL
		switch (step)
		{
			case 2:
			{
				EXTL_ASSERT(NULL != node);
				if (NULL != node) 
					derive().insert_into_col(node, has_existed);
			}
			case 1:
			{
				EXTL_ASSERT(NULL != node);
				if (NULL != node) 
					derive().insert_into_row(node, has_existed);
			}
		}
		// reraise
		EXTL_THROW;
	EXTL_CATCH_END

	EXTL_ASSERT(derive().is_valid());
}

// note: non-exception-safe
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(size_type)::erase_row(index_type i0)
{
	if (rheads()[i0].is_empty()) return 0;

	size_type n = 0;
	node_pointer rp = rheads()[i0].right();
	EXTL_ASSERT(NULL != rp);
	for (; &(rheads()[i0]) != rp; ++n)
	{
		node_pointer old = rp;

		// erase node
		rp->top()->bottom(rp->bottom());
		rp->bottom()->top(rp->top());

		// destroy node
		rp = rp->right();
		if (NULL != old) destroy_node(old);
	}
	rheads()[i0].clear();

	return n;
}
// note: non-exception-safe
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(size_type)::erase_col(index_type i1)
{
	if (cheads()[i1].is_empty()) return 0;

	size_type n = 0;
	node_pointer cp = cheads()[i1].bottom();
	EXTL_ASSERT(NULL != cp);
	for (; &(cheads()[i1]) != cp; ++n)
	{
		node_pointer old = cp;

		// erase node
		cp->left()->right(cp->right());
		cp->right()->left(cp->left());

		// destroy node
		cp = cp->bottom();
		if (NULL != old) destroy_node(old);
	}
	cheads()[i1].clear();

	return n;
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::init()
{
	// clear nodes
	nodes().clear();

	// clear rheads
	size_type rn = rheads().size();
	EXTL_ASSERT(rn == dim0());
	for (index_type i = 0; i < rn; ++i)
		rheads()[i].clear();

	// clear cheads
	size_type cn = cheads().size();
	EXTL_ASSERT(cn == dim1());
	for (index_type j = 0; j < cn; ++j)
		cheads()[j].clear();

	EXTL_ASSERT(derive().is_valid());
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::destroy()
{
	derive().clear();
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::destroy_nodes()
{
	// destroy nodes
	size_type rn = rheads().size();
	EXTL_ASSERT(rn == dim0());
	for (index_type i = 0; i < rn; ++i)
	{
		for (node_pointer rp = rheads()[i].right(); &(rheads()[i]) != rp; )
		{
			if (NULL != rp)
			{
				node_pointer node = rp;
				rp = rp->right();
				destroy_node(node);
			}
		}
	}

	EXTL_ASSERT(nodes().size() == 0);
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::clear()
{
	EXTL_ASSERT(derive().is_valid());

	// destroy nodes
	destroy_nodes();

	// clear nodes
	nodes().clear();

	// clear rheads
	size_type rn = rheads().size();
	EXTL_ASSERT(rn == dim0());
	for (index_type i = 0; i < rn; ++i)
		rheads()[i].clear();

	// clear cheads
	size_type cn = cheads().size();
	EXTL_ASSERT(cn == dim1());
	for (index_type j = 0; j < cn; ++j)
		cheads()[j].clear();

	EXTL_ASSERT(derive().is_valid());
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(bool_type)::exists(index_type i0, index_type i1) const
{
	if (!(i0 < dim0())) return e_false_v;
	if (!(i1 < dim1())) return e_false_v;
	
	if (rheads()[i0].is_empty()) return e_false_v;
	if (cheads()[i1].is_empty()) return e_false_v;
	
	// find i1(col) from i0(row)
	const_node_pointer rp = rheads()[i0].right();
	EXTL_ASSERT(NULL != rp);
	for (; &(rheads()[i0]) != rp && rp->col() < i1; rp = rp->right());
	if (rp == &(rheads()[i0]) || rp->col() != i1) return e_false_v;

	// find i0(row) from i1(col)
	/*const_node_pointer cp = cheads()[i1].bottom();
	EXTL_ASSERT(NULL != cp);
	for (; &(cheads()[i1]) != cp && cp->row() < i0; cp = cp->bottom());
	if (cp == &(cheads()[i1]) || cp->row() != i0) return e_false_v;*/

	return e_true_v;
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(bool_type)::is_valid() const
{
	size_type rn = rheads().size();
	if (rn != dim0()) return e_false_v;

	size_type cn = cheads().size();
	if (cn != dim1()) return e_false_v;

	// check invariance from rheads
	for (index_type i = 0; i < rn; ++i)
	{
		const_node_pointer rp = rheads()[i].right();
		if (NULL == rp->right()) return e_false_v;
		for (; &(rheads()[i]) != rp; rp = rp->right())
		{
			if (NULL == rp->right()) return e_false_v;
			if (NULL == rp->left()) return e_false_v;
			if (NULL == rp->top()) return e_false_v;
			if (NULL == rp->bottom()) return e_false_v;

			if (!(rp->row() == i)) return e_false_v;
			if (&(cheads()[rp->col()]) != rp->top() && !(rp->top()->row() < i)) return e_false_v;
			if (&(cheads()[rp->col()]) != rp->bottom() && !(rp->bottom()->row() > i)) return e_false_v;
			if (&(rheads()[i]) != rp->left() && !(rp->left()->col() < rp->col())) return e_false_v;
		}
	}

	// check invariance from cheads
	for (index_type j = 0; j < cn; ++j)
	{
		const_node_pointer cp = cheads()[j].bottom();
		if (NULL == cp->bottom()) return e_false_v;
		for (; &(cheads()[j]) != cp; cp = cp->bottom())
		{
			if (NULL == cp->right()) return e_false_v;
			if (NULL == cp->left()) return e_false_v;
			if (NULL == cp->top()) return e_false_v;
			if (NULL == cp->bottom()) return e_false_v;

			if (!(cp->col() == j)) return e_false_v;
			if (&(rheads()[cp->row()]) != cp->left() && !(cp->left()->col() < j)) return e_false_v;
			if (&(rheads()[cp->row()]) != cp->right() && !(cp->right()->col() > j)) return e_false_v;
			if (&(cheads()[j]) != cp->top() && !(cp->top()->row() < cp->row())) return e_false_v;
		}
	}

	return e_true_v;
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline void EXTL_SPARSE_MATRIX_BASE_QUAL::swap(derived_type& rhs)
{
	derived_type tmp(derive());
	derive().assign(rhs);
	rhs.assign(tmp);
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(derived_type&)::operator =(derived_type const& rhs)
{
	derive().assign(rhs);
	return derive();
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(derived_type&)::assign(derived_type const& rhs)
{
	EXTL_ASSERT(rhs.is_valid());
	if (&derive() == &rhs) return derive();

	derive().clear();
	rheads().resize(rhs.dim0());
	cheads().resize(rhs.dim1());
	derive().init();

	size_type rn = rheads().size();
	EXTL_ASSERT(rn == derive().dim0());

	class_type const* prhs = static_cast<class_type const*>(&rhs);
	EXTL_ASSERT(NULL != prhs);

	// insert nodes
	for (index_type i = 0; i < rn; ++i)
	{
		if (prhs->rheads()[i].is_empty())
			continue;

		const_node_pointer rp = prhs->rheads()[i].right();
		EXTL_ASSERT(NULL != rp->right());
		for (; &(prhs->rheads()[i]) != rp; rp = rp->right())
		{
			EXTL_ASSERT(NULL != rp);

		#ifdef EXTL_COMPILER_IS_DMC
			const_reference val = derive().insert(i, rp->col(), rp->value());
			EXTL_SUPPRESS_UNUSED(val);
		#else
			derive().insert(i, rp->col(), rp->value());
		#endif
		}
	}
	return derive();
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(reference)::at(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<derived_type const&>(*this).at(i0, i1));
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(const_reference)::at(index_type i0, index_type i1) const
{
	EXTL_MESSAGE_ASSERT(i0 < dim0() && i1 < dim1(), "out of range");
	EXTL_ASSERT_THROW(i0 < dim0() && i1 < dim1(), index_type("out of range"));
	return at_unchecked(i0, i1);
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(reference)::at_unchecked(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<derived_type const&>(*this).at_unchecked(i0, i1));
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(const_reference)::at_unchecked(index_type i0, index_type i1) const
{
	EXTL_MESSAGE_ASSERT(i0 < dim0() && i1 < dim1(), "out of range");

	index_type row = i0;
	index_type col = i1;

	// find insertion point
	const_node_pointer rp = rheads()[row].right();
	EXTL_ASSERT(NULL != rp);
	for (; &(rheads()[row]) != rp && rp->col() < col; rp = rp->right());
	
	if (rp != &rheads()[row] && rp->col() == col)
		return rp->value();

	/*const_node_pointer cp = cheads()[col].bottom();
	EXTL_ASSERT(NULL != cp);
	for (; &(cheads()[col]) != cp && cp->row() < row; cp = cp->bottom());
	
	if (cp != &cheads()[col] && cp->row() == row)
		return cp->value();*/

	// insert node if not exists
	return const_cast<derived_type&>(derive()).insert(i0, i1, value_type());
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(reduced_dimension_type)::at(index_type i0)
{
	EXTL_MESSAGE_ASSERT(i0 < dim0(), "out of range");
	EXTL_ASSERT_THROW(i0 < dim0(), index_type("out of range"));
	return reduced_dimension_type(&derive(), i0);
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(const_reduced_dimension_type)::at(index_type i0) const
{
	EXTL_MESSAGE_ASSERT(i0 < dim0(), "out of range");
	EXTL_ASSERT_THROW(i0 < dim0(), index_type("out of range"));
	return const_reduced_dimension_type(&derive(), i0);
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(reduced_dimension_type)::at_unchecked(index_type i0)
{
	return reduced_dimension_type(&derive(), i0);
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(const_reduced_dimension_type)::at_unchecked(index_type i0) const
{
	return const_reduced_dimension_type(&derive(), i0);
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(bool_type)::get_if_exists(index_type i0, index_type i1, reference ret) const
{
	EXTL_MESSAGE_ASSERT(i0 < dim0() && i1 < dim1(), "out of range");

	index_type row = i0;
	index_type col = i1;

	// find insertion point
	const_node_pointer rp = rheads()[row].right();
	EXTL_ASSERT(NULL != rp);
	for (; &(rheads()[row]) != rp && rp->col() < col; rp = rp->right());
	
	// if exists
	if (rp != &rheads()[row] && rp->col() == col)
	{
		ret = rp->value();
		return e_true_v;
	}

	return e_false_v;
}
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
inline EXTL_SPARSE_MATRIX_BASE_RET_QUAL(bool_type)::set_if_exists(index_type i0, index_type i1, const_reference val)
{
	EXTL_MESSAGE_ASSERT(i0 < dim0() && i1 < dim1(), "out of range");

	index_type row = i0;
	index_type col = i1;

	// find insertion point
	node_pointer rp = rheads()[row].right();
	EXTL_ASSERT(NULL != rp);
	for (; &(rheads()[row]) != rp && rp->col() < col; rp = rp->right());
	
	// if exists
	if (rp != &rheads()[row] && rp->col() == col)
	{
		rp->value(val);
		return e_true_v;
	}

	return e_false_v;
}
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
EXTL_INLINE void swap(EXTL_SPARSE_MATRIX_BASE_QUAL& lhs, EXTL_SPARSE_MATRIX_BASE_QUAL& rhs)
{
	static_cast<Dev&>(lhs).swap(static_cast<Dev&>(rhs));
}

EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_SPARSE_MATRIX_BASE_QUAL::
size_type get_size(EXTL_SPARSE_MATRIX_BASE_QUAL const& mx)
{
	return static_cast<Dev const&>(mx).size();
}

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_SPARSE_MATRIX_BASE_TEMPLATE_DECL
#undef EXTL_SPARSE_MATRIX_BASE_QUAL
#undef EXTL_SPARSE_MATRIX_BASE_RET_QUAL
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

template<	typename_param_k Dev
		,	typename_param_k Val
		>
EXTL_INLINE void swap(EXTL_NS(sparse_matrix_base)<Dev, Val>& lhs, 
						EXTL_NS(sparse_matrix_base)<Dev, Val>& rhs)
{
	static_cast<Dev&>(lhs).swap(static_cast<Dev&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_SPARSE_MATRIX_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
