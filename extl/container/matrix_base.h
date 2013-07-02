/* ///////////////////////////////////////////////////////////////////////
 * File:		matrix_base.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.08
 *
 * Brief: matrix_base class - fixed-size
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_MATRIX_BASE_H
#define EXTL_CONTAINER_MATRIX_BASE_H

/*!\file matrix_base.h
 * \brief matrix_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "basic_array.h"
#include "../algorithm/algorithm.h"
#include "detail/matrix_cole_iterator.h"
#include "detail/matrix_rowe_iterator.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief matrix_base
 *
 * 0 1 2
 * 3 4 5 dim0
 * 6 7 9
 * dim1
 *
 * \param D The derived type
 * \param B The buffer type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k D
		,	typename_param_k B
		>
class matrix_base
{
	/// \name Types
	/// @{
	public:
		typedef matrix_base																class_type;
		typedef D																		derived_type;
		typedef B																		buffer_type;
		typedef typename_type_k buffer_type::allocator_type								allocator_type;
		typedef typename_type_k buffer_type::value_type									value_type;
		typedef typename_type_k buffer_type::pointer									pointer;
		typedef typename_type_k buffer_type::const_pointer								const_pointer;
		typedef typename_type_k buffer_type::reference									reference;
		typedef typename_type_k buffer_type::const_reference							const_reference;
		typedef typename_type_k buffer_type::iterator									iterator;
		typedef typename_type_k buffer_type::const_iterator								const_iterator;
		typedef typename_type_k buffer_type::reverse_iterator							reverse_iterator;
		typedef typename_type_k buffer_type::const_reverse_iterator						const_reverse_iterator;
		typedef typename_type_k buffer_type::size_type									size_type;
		typedef typename_type_k buffer_type::bool_type									bool_type;
		typedef typename_type_k buffer_type::difference_type							difference_type;
		typedef typename_type_k buffer_type::memory_traits_type							memory_traits_type;
		typedef	e_int_t																	int_type;	
		typedef size_type																index_type;
		typedef basic_array	<	value_type
							,	attached_buffer	<	value_type
												,	EXTL_MEMORY_ATTACHED_BUFFER_INFINITY_SPACE
												,	memory_traits_type
												>	
							>															reduced_dimension_type;
		typedef reduced_dimension_type const											const_reduced_dimension_type;

		// row element iterators
		typedef EXTL_NS_DETAIL(matrix_rowe_iterator)<value_type, derived_type>			rowe_iterator;
		typedef EXTL_NS_DETAIL(const_matrix_rowe_iterator)<value_type, derived_type>	const_rowe_iterator;
		typedef reverse_bidirectional_iterator_base<const_rowe_iterator>				rowe_reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_rowe_iterator>			const_rowe_reverse_iterator;
		
		// col element iterators
		typedef EXTL_NS_DETAIL(matrix_cole_iterator)<value_type, derived_type>			cole_iterator;
		typedef EXTL_NS_DETAIL(const_matrix_cole_iterator)<value_type, derived_type>	const_cole_iterator;
		typedef reverse_bidirectional_iterator_base<const_cole_iterator>				cole_reverse_iterator;
		typedef const_reverse_bidirectional_iterator_base<const_cole_iterator>			const_cole_reverse_iterator;
	/// @}

	public:
		/// The dimension of the matrix
		EXTL_STATIC_MEMBER_CONST(size_type, dimension = 2);

	/// \name Members
	/// @{
	private:
		buffer_type																		m_buffer;
		
		/* note: vc6.0 bug - for dim0()
		 * e.g. scoped_buffer<basic_matrix<int> > xxx;
		 * will generate fatal error C1001: INTERNAL COMPILER ERROR
		 *
		 * maybe inappropriate optimization
		 */
	#if EXTL_WORKAROUND_MSVC(==, 1200)
		size_type volatile																m_d1;
	#else
		size_type																		m_d1;
	#endif
	/// @}

	private:
		/*!\brief Prohibit the following case:
		 * 
		 * \code
			D da, db;
			B &ba = da, &bb = db;
			ba = bb;
			B b(ba);
		 * \endcode
		 */
		matrix_base(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		matrix_base()
			: m_buffer(), m_d1(0)
		{
			EXTL_ASSERT(is_valid());
		}
		explicit_k matrix_base(derived_type const& rhs)
			: m_buffer(static_cast<class_type const&>(rhs).buffer())
			, m_d1(static_cast<class_type const&>(rhs).m_d1)
		{
			EXTL_ASSERT(is_valid());
		}
		// d0 * d1
		matrix_base(index_type d0, index_type d1)
			: m_buffer(value_type(), d0 * d1), m_d1(d1)
		{
			EXTL_ASSERT(is_valid());
		}
		// d0 * d1
		matrix_base(const_reference value, index_type d0, index_type d1)
			: m_buffer(value, d0 * d1), m_d1(d1)
		{
			EXTL_ASSERT(is_valid());
		}
		// d0 * d1
		matrix_base(const_pointer p, index_type d0, index_type d1)
			: m_buffer(p, d0 * d1), m_d1(d1)
		{
			EXTL_ASSERT(NULL != p);
			EXTL_ASSERT(is_valid());
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		allocator_type		allocator() const		{ return buffer().allocator();					}
		size_type			dim0() const			{ return ((size() > 0)? (size() / dim1()) : 0);	}
		size_type			dim1() const			{ return ((size() > 0)? m_d1 : 0);				}
		size_type			row() const				{ return derive().dim0();						}
		size_type			col() const				{ return derive().dim1();						}
		size_type			size() const			{ return buffer().size();						}
		bool_type			is_empty() const		{ return buffer().is_empty();					}
		bool_type			empty() const			{ return buffer().is_empty();					}
		size_type			max_size()				{ return derive().dim0() * derive().dim1();		}
		bool_type			is_valid() const;
	/// @}

	/// \name Accessors
	/// @{
	public:
		pointer				data()							{ return buffer().data();			}
		const_pointer		data() const					{ return buffer().data();			}

		reference			front()							{ return buffer().front();			}
		const_reference		front()	const					{ return buffer().front();			}

		reference			back()							{ return buffer().back();			}
		const_reference		back() const					{ return buffer().back();			}
	
	#if !EXTL_WORKAROUND_MSVC(>, 1200) && \
			!defined(EXTL_COMPILER_IS_BORLAND)
		reduced_dimension_type			at(index_type i0);
		const_reduced_dimension_type	at(index_type i0) const;

		reduced_dimension_type			at_unchecked(index_type i0);
		const_reduced_dimension_type	at_unchecked(index_type i0) const;
	#else
		reduced_dimension_type			at(index_type i0);
		const_reduced_dimension_type	at(index_type i0) const
		{
			EXTL_ASSERT(derive().is_valid());
			EXTL_ASSERT(NULL != derive().data());
			EXTL_ASSERT(i0 < derive().dim0());
			return const_reduced_dimension_type(derive().data() + i0 * derive().dim1(), derive().dim1());
		}

		reduced_dimension_type			at_unchecked(index_type i0);
		const_reduced_dimension_type	at_unchecked(index_type i0) const
		{
			EXTL_ASSERT(derive().is_valid());
			EXTL_ASSERT(NULL != derive().data());
			EXTL_ASSERT(i0 < derive().dim0());
			return const_reduced_dimension_type(derive().data() + i0 * derive().dim1(), derive().dim1());
		}
	#endif

		// note: not derive().at_unchecked(i0);
		reduced_dimension_type			operator[](index_type i0)		{ return at_unchecked(i0);	}
		const_reduced_dimension_type	operator[](index_type i0) const	{ return at_unchecked(i0);	}

		reference						at(index_type i0, index_type i1);
		const_reference					at(index_type i0, index_type i1) const;

		reference						at_unchecked(index_type i0, index_type i1);
		const_reference					at_unchecked(index_type i0, index_type i1) const;
	/// @}

	/// \name Mutators
	/// @{
	public:
		void					swap(derived_type& rhs);
		derived_type&			operator =(derived_type const& rhs);
		derived_type&			operator =(const_reference value);
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const			{ return const_iterator(derive().data());							}
		iterator				begin()					{ return iterator(derive().data());									}

		const_iterator			end() const				{ return const_iterator(derive().data() + buffer().size());			}
		iterator				end()					{ return iterator(derive().data() + buffer().size());				}
	
		const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(derive().end());					}
		reverse_iterator		rbegin()				{ return reverse_iterator(derive().end());							}
	
		const_reverse_iterator	rend() const			{ return const_reverse_iterator(derive().begin());					}
		reverse_iterator		rend()					{ return reverse_iterator(derive().begin());						}
	/// @}

	/// \name Row Element Iterators
	/// @{
	public:
		const_rowe_iterator			rowe_begin(index_type i0) const		{ return const_rowe_iterator(i0, 0, derive());					}
		rowe_iterator				rowe_begin(index_type i0)			{ return rowe_iterator(i0, 0, derive());						}

		const_rowe_iterator			rowe_end(index_type i0) const		{ return const_rowe_iterator(i0, derive().dim1(), derive());	}
		rowe_iterator				rowe_end(index_type i0)				{ return rowe_iterator(i0, derive().dim1(), derive());			}
	
		const_rowe_reverse_iterator	rowe_rbegin(index_type i0) const	{ return const_rowe_reverse_iterator(derive().rowe_end(i0));	}
		rowe_reverse_iterator		rowe_rbegin(index_type i0)			{ return rowe_reverse_iterator(derive().rowe_end(i0));			}
	
		const_rowe_reverse_iterator	rowe_rend(index_type i0) const		{ return const_rowe_reverse_iterator(derive().rowe_begin(i0));	}
		rowe_reverse_iterator		rowe_rend(index_type i0)			{ return rowe_reverse_iterator(derive().rowe_begin(i0));		}
	/// @}

	/// \name Column Element Iterators
	/// @{
	public:
		const_cole_iterator			cole_begin(index_type i1) const		{ return const_cole_iterator(i1, 0, derive());					}
		cole_iterator				cole_begin(index_type i1)			{ return cole_iterator(i1, 0, derive());						}

		const_cole_iterator			cole_end(index_type i1) const		{ return const_cole_iterator(i1, derive().dim0(), derive());	}
		cole_iterator				cole_end(index_type i1)				{ return cole_iterator(i1, derive().dim0(), derive());			}
	
		const_cole_reverse_iterator	cole_rbegin(index_type i1) const	{ return const_cole_reverse_iterator(derive().cole_end(i1));	}
		cole_reverse_iterator		cole_rbegin(index_type i1)			{ return cole_reverse_iterator(derive().cole_end(i1));			}
	
		const_cole_reverse_iterator	cole_rend(index_type i1) const		{ return const_cole_reverse_iterator(derive().cole_begin(i1));	}
		cole_reverse_iterator		cole_rend(index_type i1)			{ return cole_reverse_iterator(derive().cole_begin(i1));		}
	/// @}

	/// \name Others
	/// @{
	protected:
		derived_type&		derive()				{ return static_cast<derived_type&>(*this);			}
		derived_type const&	derive() const			{ return static_cast<derived_type const&>(*this);	}

		buffer_type&		buffer()				{ return m_buffer;									}
		buffer_type const&	buffer() const			{ return m_buffer;									}
	/// @}
};
/* /////////////////////////////////////////////////////////////////////////
 * Implemention
 */
// at_unchecked(i0, i1)
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
const_reference matrix_base<D, B>::at_unchecked(index_type i0, index_type i1) const
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != derive().data());
	EXTL_ASSERT(i0 < derive().dim0());
	EXTL_ASSERT(i1 < derive().dim1());
	return derive().data()[i0 * derive().dim1() + i1];
}
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
reference matrix_base<D, B>::at_unchecked(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<derived_type const&>(*this).at_unchecked(i0, i1));
}

// at_unchecked(i0)
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
reduced_dimension_type matrix_base<D, B>::at_unchecked(index_type i0)
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != derive().data());
	EXTL_ASSERT(i0 < derive().dim0());
	return reduced_dimension_type(derive().data() + i0 * derive().dim1(), derive().dim1());
}
// at(i0)
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
reduced_dimension_type matrix_base<D, B>::at(index_type i0)
{
	EXTL_ASSERT_THROW(i0 < derive().dim0(), index_error("out of range"));
	return at_unchecked(i0);
}


#if !EXTL_WORKAROUND_MSVC(>, 1200) && \
			!defined(EXTL_COMPILER_IS_BORLAND)
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
const_reduced_dimension_type matrix_base<D, B>::at(index_type i0) const
{
	EXTL_ASSERT_THROW(i0 < derive().dim0(), index_error("out of range"));
	return at_unchecked(i0);
}

template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
const_reduced_dimension_type matrix_base<D, B>::at_unchecked(index_type i0) const
{
	EXTL_ASSERT(derive().is_valid());
	EXTL_ASSERT(NULL != derive().data());
	EXTL_ASSERT(i0 < derive().dim0());
	return const_reduced_dimension_type(derive().data() + i0 * derive().dim1(), derive().dim1());
}
#endif
// at(i0, i1)
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
reference matrix_base<D, B>::at(index_type i0, index_type i1)
{
	return const_cast<reference>(static_cast<derived_type const&>(*this).at(i0, i1));
}
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
const_reference	matrix_base<D, B>::at(index_type i0, index_type i1) const
{
	EXTL_ASSERT_THROW(i0 < derive().dim0() && i1 < derive().dim1(), index_error("out of range"));
	return derive().at_unchecked(i0, i1);
}
// is_valid
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
bool_type matrix_base<D, B>::is_valid() const
{
	if ((derive().dim0() == 0) != (derive().dim1() == 0))
	{
		return e_false_v;
	}
	else if ((derive().dim0() * derive().dim1()) != derive().size())
	{
		return e_false_v;
	}
	return e_true_v;
}
// swap
template<	typename_param_k D
		,	typename_param_k B
		>
inline void matrix_base<D, B>::swap(derived_type& rhs)				
{
	std_swap(m_d1, static_cast<class_type&>(rhs).m_d1);
	buffer().swap(static_cast<class_type&>(rhs).buffer());		
}
// operator =
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
derived_type& matrix_base<D, B>::operator =(derived_type const& rhs)
{
	if (this != static_cast<class_type const*>(&rhs)) 
	{
		m_d1 = static_cast<class_type const&>(rhs).m_d1;
		buffer().assign(static_cast<class_type const&>(rhs).buffer());
	}

	return derive();
}
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k matrix_base<D, B>::
derived_type& matrix_base<D, B>::operator =(const_reference value)
{
	buffer().assign(value, buffer().size());
	return derive();
}
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE void swap(matrix_base<D, B>& lhs, matrix_base<D, B>& rhs)
{
	static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k matrix_base<D, B>::
const_pointer get_ptr(matrix_base<D, B> const& mx)
{
	return static_cast<D const&>(mx).data();
}

template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k matrix_base<D, B>::
size_type get_size(matrix_base<D, B> const& mx)
{
	return static_cast<D const&>(mx).size();
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

template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE void swap(EXTL_NS(matrix_base)<D, B>& lhs, 
						EXTL_NS(matrix_base)<D, B>& rhs)
{
	static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_MATRIX_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
