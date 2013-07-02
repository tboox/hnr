/* ///////////////////////////////////////////////////////////////////////
 * File:		symmetrical_matrix.h		
 *
 * Created:		08.12.05			
 * Updated:		08.12.05
 *
 * Brief:		symmetrical_matrix class - compact matrix
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_SYMMETRICAL_MATRIX_H
#define EXTL_CONTAINER_SYMMETRICAL_MATRIX_H

/*!\file symmetrical_matrix.h
 * \brief symmetrical_matrix class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "matrix_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: symmetrical_matrix class - compact matrix
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
 * \param Buf The buffer type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k Val
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k Buf = typename_type_def_k buffer_selector<Val>::buffer_type 
#else
		,	typename_param_k Buf	
#endif
		>
class symmetrical_matrix
	: public matrix_base	<	symmetrical_matrix<Val, Buf>
							,	Buf
							>
{
	private:
		typedef matrix_base	<	symmetrical_matrix<Val, Buf>
							,	Buf
							>														base_type;

	/// \name Types
	/// @{
	public:
		typedef symmetrical_matrix													class_type;
		typedef typename_type_k base_type::buffer_type								buffer_type;
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
				const_pointer							m_p;
				index_type								m_i;
				size_type								m_dim;

			public:
				const_reduced_dimension_type(const_pointer p, index_type i, size_type dim)
					: m_p(p)
					, m_i(i)
					, m_dim(dim)
				{}
			public:
				const_reference	operator[](index_type j) const
				{
					return at(j);
				}
				const_reference	at(index_type j) const
				{
					EXTL_ASSERT(NULL != m_p);
					EXTL_ASSERT(j < m_dim);
					EXTL_ASSERT(m_i < m_dim);
					return (m_i < j)? m_p[m_i * (m_dim * 2 + 1 - m_i) / 2 + j - m_i] 
										: m_p[j * (m_dim * 2 + 1 - j) / 2 + m_i - j];
				}
		};
		class reduced_dimension_type
		{
			private:
				pointer									m_p;
				index_type								m_i;
				size_type								m_dim;

			public:
				reduced_dimension_type(pointer p, index_type i, size_type dim)
					: m_p(p)
					, m_i(i)
					, m_dim(dim)
				{}
			public:
				reference	operator[](index_type j) 
				{
					return at(j);
				}
				reference	at(index_type j)
				{
					EXTL_ASSERT(NULL != m_p);
					EXTL_ASSERT(j < m_dim);
					EXTL_ASSERT(m_i < m_dim);
					return (m_i < j)? m_p[m_i * (m_dim * 2 + 1 - m_i) / 2 + j - m_i] 
										: m_p[j * (m_dim * 2 + 1 - j) / 2 + m_i - j];
				}
		};
	/// @}

	/// \name Constructors
	/// @{
	public:
		symmetrical_matrix()
			: base_type()
		{
		}
		symmetrical_matrix(class_type const& rhs)
			: base_type(rhs)
		{
		}
		explicit_k symmetrical_matrix(index_type d0, index_type /*d1*/ = 0)
			: base_type(d0, d0)
		{
			this->buffer().resize((d0 * (d0 + 1)) >> 1);
		}
		symmetrical_matrix(const_reference value, index_type d0, index_type /*d1*/ = 0)
			: base_type(value, d0, d0)
		{
			this->buffer().resize((d0 * (d0 + 1)) >> 1);
		}
		
	/// @}

	/// \name Attributes
	/// @{
	public:
		size_type			dim0() const			{ return dim1();											}
		size_type			dim1() const			{ return static_cast<base_type const&>(*this).dim1();		}
		size_type			dim() const				{ return dim1();											}
		size_type			size() const			{ return dim0() * dim0();									}
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

	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& rhs)	{ return base_type::operator=(rhs);		}
		class_type& operator=(const_reference value)	{ return base_type::operator=(value);	}
	/// @}

	

};
/* /////////////////////////////////////////////////////////////////////////
 * Implemention
 */
// at_unchecked(i0, i1)
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
const_reference symmetrical_matrix<Val, Buf>::at_unchecked(index_type i0, index_type i1) const
{
	/* matrix[i][j]
	 * buffer[i * (2 * n + 1 - i) / 2 + j - i]
	 */
	EXTL_ASSERT(this->is_valid());
	EXTL_ASSERT(NULL != this->data());
	EXTL_ASSERT(i0 < dim());
	EXTL_ASSERT(i1 < dim());
	return i0 < i1? this->data()[i0 * (dim() * 2 + 1 - i0) / 2 + i1 - i0] 
						: this->data()[i1 * (dim() * 2 + 1 - i1) / 2 + i0 - i1];
}
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
reference symmetrical_matrix<Val, Buf>::at_unchecked(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<class_type const&>(*this).at_unchecked(i0, i1));
}

// at(i0, i1)
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
reference symmetrical_matrix<Val, Buf>::at(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<class_type const&>(*this).at(i0, i1));
}
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
const_reference	symmetrical_matrix<Val, Buf>::at(index_type i0, index_type i1) const
{
	EXTL_ASSERT_THROW(i0 < dim() && i1 < dim(), index_error("out of range"));
	return at_unchecked(i0, i1);
}

// at_unchecked(i0)
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
reduced_dimension_type symmetrical_matrix<Val, Buf>::at_unchecked(index_type i0)
{
	EXTL_ASSERT(this->is_valid());
	EXTL_ASSERT(NULL != this->data());
	EXTL_ASSERT(i0 < dim());
	return reduced_dimension_type(this->data(), i0, dim());
}
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
const_reduced_dimension_type symmetrical_matrix<Val, Buf>::at_unchecked(index_type i0) const
{
	EXTL_ASSERT(this->is_valid());
	EXTL_ASSERT(NULL != this->data());
	EXTL_ASSERT(i0 < dim());
	return const_reduced_dimension_type(this->data(), i0, dim());
}

// at(i0)
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
reduced_dimension_type symmetrical_matrix<Val, Buf>::at(index_type i0)
{
	EXTL_ASSERT_THROW(i0 < dim(), index_error("out of range"));
	return at_unchecked(i0);
}
template<	typename_param_k Val
		,	typename_param_k Buf
		>
inline typename_type_ret_k symmetrical_matrix<Val, Buf>::
const_reduced_dimension_type symmetrical_matrix<Val, Buf>::at(index_type i0) const
{
	EXTL_ASSERT_THROW(i0 < dim(), index_error("out of range"));
	return at_unchecked(i0);
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_SYMMETRICAL_MATRIX_H */
/* //////////////////////////////////////////////////////////////////// */
