/* ///////////////////////////////////////////////////////////////////////
 * File:		symmetrical_sparse_matrix.h		
 *
 * Created:		08.12.05			
 * Updated:		08.12.05
 *
 * Brief:		symmetrical_sparse_matrix class - compact matrix
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_SYMMETRICAL_SPARSE_MATRIX_H
#define EXTL_CONTAINER_SYMMETRICAL_SPARSE_MATRIX_H

/*!\file symmetrical_sparse_matrix.h
 * \brief symmetrical_sparse_matrix class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "sparse_matrix_base.h"
#include "detail/symmetrical_sparse_matrix_rowcole_iterator.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: symmetrical_sparse_matrix class - compact matrix
 *
 * <pre>
 * using upper triangular matrix 
 * size = n * (n + 1) / 2
 *
 *  0   0   0   0   0   0 
 *      0   0   0   0   0
 *          0   0   0   0
 *              0   0   0 
 *                  0   0
 *                      0
 *
 * </pre>
 *
 * \param Val The element type
 *
 * \ingroup extl_group_container
 */
template<typename_param_k Val>
class symmetrical_sparse_matrix
	: public sparse_matrix_base	<	symmetrical_sparse_matrix<Val>
								,	Val
								>
{
	private:
		typedef sparse_matrix_base	<	symmetrical_sparse_matrix<Val>
									,	Val
									>												base_type;

	/// \name Types
	/// @{
	public:
		typedef symmetrical_sparse_matrix											class_type;
		typedef typename_type_k base_type::allocator_type							allocator_type;
		typedef typename_type_k base_type::value_type								value_type;
		typedef typename_type_k base_type::pointer									pointer;
		typedef typename_type_k base_type::const_pointer							const_pointer;
		typedef typename_type_k base_type::reference								reference;
		typedef typename_type_k base_type::const_reference							const_reference;
		typedef typename_type_k base_type::iterator									iterator;
		typedef typename_type_k base_type::const_iterator							const_iterator;
		typedef typename_type_k base_type::reverse_iterator							reverse_iterator;
		typedef typename_type_k base_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename_type_k base_type::size_type								size_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k base_type::difference_type							difference_type;
		typedef	typename_type_k base_type::int_type									int_type;	
		typedef typename_type_k base_type::index_type								index_type;
		class const_reduced_dimension_type
		{
			private:
				class_type const*						m_this;
				index_type								m_i;
				size_type								m_dim;

			public:
				const_reduced_dimension_type(class_type const* p, index_type i)
					: m_this(p)
					, m_i(i)
				{}
			public:
				const_reference	operator[](index_type j) const
				{
					return at_unchecked(j);
				}
				const_reference	at(index_type j) const
				{
					return m_this->at(m_i, j);
				}
				const_reference	at_unchecked(index_type j) const
				{
					return m_this->at_unchecked(m_i, j);
				}
		};
		class reduced_dimension_type
		{
			private:
				class_type const*						m_this;
				index_type								m_i;
				size_type								m_dim;

			public:
				reduced_dimension_type(class_type const* p, index_type i)
					: m_this(p)
					, m_i(i)
				{}
			public:
				reference	operator[](index_type j) 
				{
					return at_unchecked(j);
				}
				reference	at(index_type j) 
				{
					return const_cast<reference>(m_this->at(m_i, j));
				}
				reference	at_unchecked(index_type j) 
				{
					return const_cast<reference>(m_this->at_unchecked(m_i, j));
				}
		};
	/// @}

	/// \name Protected Types
	/// @{
	protected:
		typedef typename_type_k base_type::rheads_type													rheads_type;
		typedef typename_type_k base_type::cheads_type													cheads_type;
		typedef typename_type_k base_type::node_type													node_type;
	/// @}

	/// \name Iterator Types
	/// @{
	public:
		// row element iterator
		typedef EXTL_NS_DETAIL(symmetrical_sparse_matrix_rowcole_iterator)<value_type, node_type>			rowe_iterator;
		typedef EXTL_NS_DETAIL(const_symmetrical_sparse_matrix_rowcole_iterator)<value_type, node_type>	const_rowe_iterator;
		typedef reverse_bidirectional_iterator_base<const_rowe_iterator>								rowe_reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_rowe_iterator>							const_rowe_reverse_iterator;


		// column element iterator
		typedef EXTL_NS_DETAIL(symmetrical_sparse_matrix_rowcole_iterator)<value_type, node_type>			cole_iterator;
		typedef EXTL_NS_DETAIL(const_symmetrical_sparse_matrix_rowcole_iterator)<value_type, node_type>	const_cole_iterator;
		typedef reverse_bidirectional_iterator_base<const_cole_iterator>								cole_reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_cole_iterator>							const_cole_reverse_iterator;
	/// @}


	/// \name Constructors
	/// @{
	public:
		symmetrical_sparse_matrix()
			: base_type()
		{
		}
		symmetrical_sparse_matrix(class_type const& rhs)
			: base_type(rhs)
		{
		}
		explicit_k symmetrical_sparse_matrix(index_type d0, index_type /*d1*/ = 0)
			: base_type(d0, d0)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		size_type					dim() const				{ return this->dim1();	}
		bool_type					exists(index_type i0, index_type i1) const;
	/// @}

	/// \name Row Element Iterators
	/// @{
	public:
		const_rowe_iterator			rowe_begin(index_type i0) const		{ return const_rowe_iterator(this->cheads()[i0].bottom(), &(this->rheads()[i0]), &(this->cheads()[i0]));	}
		rowe_iterator				rowe_begin(index_type i0)			{ return rowe_iterator(this->cheads()[i0].bottom(), &(this->rheads()[i0]), &(this->cheads()[i0]));			}

		const_rowe_iterator			rowe_end(index_type i0) const		{ return const_rowe_iterator(&(this->rheads()[i0]), &(this->rheads()[i0]), &(this->cheads()[i0]));			}
		rowe_iterator				rowe_end(index_type i0)				{ return rowe_iterator(&(this->rheads()[i0]), &(this->rheads()[i0]), &(this->cheads()[i0]));				}
	
		const_rowe_reverse_iterator	rowe_rbegin(index_type i0) const	{ return const_rowe_reverse_iterator(rowe_end(i0));		}
		rowe_reverse_iterator		rowe_rbegin(index_type i0)			{ return rowe_reverse_iterator(rowe_end(i0));			}
	
		const_rowe_reverse_iterator	rowe_rend(index_type i0) const		{ return const_rowe_reverse_iterator(rowe_begin(i0));	}
		rowe_reverse_iterator		rowe_rend(index_type i0)			{ return rowe_reverse_iterator(rowe_begin(i0));			}
	/// @}

	/// \name Column Element Iterators
	/// @{
	public:
		const_cole_iterator			cole_begin(index_type i1) const		{ return const_cole_iterator(this->cheads()[i1].bottom(), &(this->rheads()[i1]), &(this->cheads()[i1]));	}
		cole_iterator				cole_begin(index_type i1)			{ return cole_iterator(this->cheads()[i1].bottom(), &(this->rheads()[i1]), &(this->cheads()[i1]));			}

		const_cole_iterator			cole_end(index_type i1) const		{ return const_cole_iterator(&(this->rheads()[i1]), &(this->rheads()[i1]), &(this->cheads()[i1]));			}
		cole_iterator				cole_end(index_type i1)				{ return cole_iterator(&(this->rheads()[i1]), &(this->rheads()[i1]), &(this->cheads()[i1]));				}
	
		const_cole_reverse_iterator	cole_rbegin(index_type i1) const	{ return const_cole_reverse_iterator(cole_end(i1));		}
		cole_reverse_iterator		cole_rbegin(index_type i1)			{ return cole_reverse_iterator(cole_end(i1));			}
	
		const_cole_reverse_iterator	cole_rend(index_type i1) const		{ return const_cole_reverse_iterator(cole_begin(i1));	}
		cole_reverse_iterator		cole_rend(index_type i1)			{ return cole_reverse_iterator(cole_begin(i1));			}
	/// @}

	/// \name Accessors
	/// @{
	public:
		reduced_dimension_type			at(index_type i0);
		const_reduced_dimension_type	at(index_type i0) const;

		reduced_dimension_type			at_unchecked(index_type i0);
		const_reduced_dimension_type	at_unchecked(index_type i0) const;

		reduced_dimension_type			operator[](index_type i0)		{ return at_unchecked(i0);	}
		const_reduced_dimension_type	operator[](index_type i0) const	{ return at_unchecked(i0);	}

		reference						at(index_type i0, index_type i1);
		const_reference					at(index_type i0, index_type i1) const;

		reference						at_unchecked(index_type i0, index_type i1);
		const_reference					at_unchecked(index_type i0, index_type i1) const;

		bool_type						get_if_exists(index_type i0, index_type i1, reference ret) const;
		bool_type						set_if_exists(index_type i0, index_type i1, const_reference val);
	/// @}

	/// \name Mutators
	/// @{
	public:
		const_reference					insert(index_type i0, index_type i1, const_reference value, bool_type* has_existed = NULL);
		void							erase(index_type i0, index_type i1, bool_type* has_existed = NULL);
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type&						operator=(class_type const& rhs)	{ return base_type::operator=(rhs);		}
	/// @}

	

};
/* /////////////////////////////////////////////////////////////////////////
 * Implemention
 */
// at_unchecked(i0, i1)
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
const_reference symmetrical_sparse_matrix<Val>::at_unchecked(index_type i0, index_type i1) const
{
	EXTL_MESSAGE_ASSERT(i0 < dim() && i1 < dim(), "out of range");
	return i0 < i1? static_cast<base_type const&>(*this).at_unchecked(i0, i1) 
					: static_cast<base_type const&>(*this).at_unchecked(i1, i0);
}
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
reference symmetrical_sparse_matrix<Val>::at_unchecked(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<class_type const&>(*this).at_unchecked(i0, i1));
}

// at(i0, i1)
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
reference symmetrical_sparse_matrix<Val>::at(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<class_type const&>(*this).at(i0, i1));
}
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
const_reference	symmetrical_sparse_matrix<Val>::at(index_type i0, index_type i1) const
{
	EXTL_ASSERT_THROW(i0 < dim() && i1 < dim(), index_error("out of range"));
	return at_unchecked(i0, i1);
}

// at_unchecked(i0)
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
reduced_dimension_type symmetrical_sparse_matrix<Val>::at_unchecked(index_type i0)
{
	EXTL_MESSAGE_ASSERT(i0 < dim(), "out of range");
	return reduced_dimension_type(this, i0);
}
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
const_reduced_dimension_type symmetrical_sparse_matrix<Val>::at_unchecked(index_type i0) const
{
	EXTL_MESSAGE_ASSERT(i0 < dim(), "out of range");
	return const_reduced_dimension_type(this, i0);
}

// at(i0)
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
reduced_dimension_type symmetrical_sparse_matrix<Val>::at(index_type i0)
{
	EXTL_ASSERT_THROW(i0 < dim(), index_error("out of range"));
	return at_unchecked(i0);
}
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
const_reduced_dimension_type symmetrical_sparse_matrix<Val>::at(index_type i0) const
{
	EXTL_ASSERT_THROW(i0 < dim(), index_error("out of range"));
	return at_unchecked(i0);
}
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
const_reference symmetrical_sparse_matrix<Val>::insert(index_type i0, index_type i1, const_reference value, bool_type* has_existed)
{
	return i0 < i1? static_cast<base_type&>(*this).insert(i0, i1, value, has_existed)
					: static_cast<base_type&>(*this).insert(i1, i0, value, has_existed);
}
template<typename_param_k Val>
void symmetrical_sparse_matrix<Val>::erase(index_type i0, index_type i1, bool_type* has_existed)
{
	if (i0 < i1)
		static_cast<base_type&>(*this).erase(i0, i1, has_existed);
	else static_cast<base_type&>(*this).erase(i1, i0, has_existed);
}
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
bool_type symmetrical_sparse_matrix<Val>::exists(index_type i0, index_type i1) const
{
	return i0 < i1? static_cast<base_type const&>(*this).exists(i0, i1)
					: static_cast<base_type const&>(*this).exists(i1, i0);
}

template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
bool_type symmetrical_sparse_matrix<Val>::get_if_exists(index_type i0, index_type i1, reference ret) const
{
	return i0 < i1? static_cast<base_type const&>(*this).get_if_exists(i0, i1, ret)
					: static_cast<base_type const&>(*this).get_if_exists(i1, i0, ret);
}
template<typename_param_k Val>
inline typename_type_ret_k symmetrical_sparse_matrix<Val>::
bool_type symmetrical_sparse_matrix<Val>::set_if_exists(index_type i0, index_type i1, const_reference val)
{
	return i0 < i1? static_cast<base_type&>(*this).set_if_exists(i0, i1, val)
					: static_cast<base_type&>(*this).set_if_exists(i1, i0, val);

}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_SYMMETRICAL_SPARSE_MATRIX_H */
/* //////////////////////////////////////////////////////////////////// */
