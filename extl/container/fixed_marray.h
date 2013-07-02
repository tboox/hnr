/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_marray.h		
 *
 * Created:		08.08.05			
 * Updated:		08.08.05
 *
 * Brief: fixed_marray class - fixed-size
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_FIXED_MARRAY_H
#define EXTL_CONTAINER_FIXED_MARRAY_H

/*!\file fixed_marray.h
 * \brief fixed_marray class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_CONTAINER_FIXED_MARRAY_SUPPORT)  
#	error extl::fixed_marray is not supported by current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "../iterator/iterator.h"
#include "detail/fixed_marray_impl.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

template<	e_size_t N
		,	typename_param_k T
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k B = typename_type_def_k buffer_selector<T>::buffer_type 
	#else
		,	typename_param_k B 
	#endif
		>
class fixed_marray;

/* ///////////////////////////////////////////////////////////////////////
 * fixed_reduced_dimension_traits class
 * Only for supporting Watcom 1.7
 * Watcom 1.7 need template specialization 
 */
template<	e_size_t N
		,	typename_param_k T
		,	typename_param_k B
		>
struct fixed_reduced_dimension_traits
{
	typedef fixed_marray	<	N - 1
								,	T
								,	attached_buffer	<	T
													,	EXTL_MEMORY_ATTACHED_BUFFER_INFINITY_SPACE
													,	typename_type_k B::memory_traits_type
													>
								>	reduced_dimension_type;
};

// Only for stop recursion
#ifdef EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT
template<	typename_param_k T
		,	typename_param_k B
		>
struct fixed_reduced_dimension_traits<1, T, B>
{
	typedef T&						reduced_dimension_type;
};
#endif

/*!brief fixed_marray
 *
 * \param N The dimension of the array
 * \param T The element type
 * \param B The buffer type
 *
 * Use it when the size of the array is larger 
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k T
		,	typename_param_k B
		>
class fixed_marray
	: public EXTL_NS_DETAIL(fixed_marray_impl)	<	N
												>::template_qual_k impl	<	T
																		,	fixed_marray<N, T, B>
																		,	typename_type_k fixed_reduced_dimension_traits<N, T, B>::reduced_dimension_type // for Watcom 1.7
																		>
{
	private:
	#if defined(EXTL_COMPILER_IS_WATCOM)
		typedef 
	#else
		typedef typename_type_k
	#endif
				EXTL_NS_DETAIL(fixed_marray_impl)	<	N
												>::template_qual_k impl	<	T
																		,	fixed_marray<N, T, B>
																		,	typename_type_k fixed_reduced_dimension_traits<N, T, B>::reduced_dimension_type // for Watcom 1.7
																		>			base_type;
	/// \name Types
	/// @{
	public:
		typedef fixed_marray														class_type;
		typedef B																	buffer_type;
		typedef typename_type_k buffer_type::memory_traits_type						memory_traits_type;
		typedef typename_type_k buffer_type::initialiser_type						initialiser_type;
		typedef	typename_type_k buffer_type::allocator_type							allocator_type;	
		typedef typename_type_k base_type::value_type								value_type;
		typedef typename_type_k base_type::pointer									pointer;
		typedef typename_type_k base_type::const_pointer							const_pointer;
		typedef typename_type_k base_type::reference								reference;
		typedef typename_type_k base_type::const_reference							const_reference;
		typedef typename_type_k base_type::size_type								size_type;
		typedef typename_type_k base_type::index_type								index_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k base_type::int_type									int_type;
		typedef typename_type_k base_type::difference_type							difference_type;
		typedef typename_type_k base_type::reduced_dimension_type					reduced_dimension_type;
		typedef typename_type_k base_type::const_reduced_dimension_type				const_reduced_dimension_type;
		typedef pointer_iterator<value_type>										iterator;
		typedef const_pointer_iterator<value_type>									const_iterator;
		typedef reverse_iterator_base<const_iterator>								reverse_iterator;
		typedef const_reverse_iterator_base<const_iterator>							const_reverse_iterator;
	/// @}

	public:
		/// The dimension of the array
		EXTL_STATIC_MEMBER_CONST(size_type, dimension = N);

	/// \name Members
	/// @{
	private:
		buffer_type																	m_data;
	/// @}

	/// \name Constructors
	/// @{
	public:
	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_SUPPORT
		template<typename_param_k U>
		fixed_marray(U const& data, index_type d0, index_type d1 = 1, index_type d2 = 1, index_type d3 = 1)
			: m_data(data, d0 * d1 * d2 * d3), base_type(d0, d1, d2, d3)
		{
		}
	#else // Will generate ambiguity at VC 6.0 when value_type is int
		fixed_marray(const_reference value, index_type d0, index_type d1 = 1, index_type d2 = 1, index_type d3 = 1)
			: m_data(value, d0 * d1 * d2 * d3), base_type(d0, d1, d2, d3)
		{
		}

		// const_pointer: buffer_type::construstor has used const_cast<> 
		fixed_marray(const_pointer data, index_type d0, index_type d1 = 1, index_type d2 = 1, index_type d3 = 1)
			: m_data(data, d0 * d1 * d2 * d3), base_type(d0, d1, d2, d3)
		{
		}
	#endif
		fixed_marray(class_type const& rhs)
			: m_data(rhs.m_data), base_type(static_cast<base_type const&>(rhs))
		{
		}
		~fixed_marray()
		{
			EXTL_STATIC_ASSERT(N > 0 && N <= EXTL_FIXED_MARRAY_CURRENT_MAX_DIM);
		}
	/// @}

	/// \name Attributes
	/// \note public base_type::dim0(), dim1, ... dimN()		
	/// @{
		bool_type is_empty() const		{ return m_data.is_empty();	}
		bool_type empty() const			{ return m_data.is_empty();	}

		size_type size() const			{ return m_data.size();		}
		static size_type max_size()		{ return buffer_type::max_size();	}
	/// @}

	/// \name Accessors
	/// \note 
	/// public base_type::at(index_type i0, index_type i1, ... index_type iN)				\n
	/// public base_type::at_unchecked(index_type i0, index_type i1, ... index_type iN)		\n
	/// public base_type::at(index_type i0)				<=>	operator [](index_type i0)		\n
	/// public base_type::at_unchecked(index_type i0)	<=> operator [](index_type i0)		
	/// @{
	public:
		pointer				data()			{ return m_data.data();	}
		const_pointer		data() const	{ return m_data.data(); }

		reference			front()			{ return m_data.front();	}
		const_reference		front()	const	{ return m_data.front();	}

		reference			back()			{ return m_data.back();		}
		const_reference		back() const	{ return m_data.back();		}

		reduced_dimension_type			operator [](index_type i0)			{ return this->at_unchecked(i0);	}
		const_reduced_dimension_type	operator [](index_type i0) const	{ return this->at_unchecked(i0);	}

		allocator_type		allocator() const	{ return m_data.allocator();	}
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const		{ return const_iterator(data());			}
		iterator				begin()				{ return iterator(data());					}

		const_iterator			end() const			{ return const_iterator(data() + size());	}
		iterator				end()				{ return iterator(data() + size());			}
	
		const_reverse_iterator	rbegin() const		{ return const_reverse_iterator(end());		}
		reverse_iterator		rbegin()			{ return reverse_iterator(end());			}
	
		const_reverse_iterator	rend() const		{ return const_reverse_iterator(begin());	}
		reverse_iterator		rend()				{ return reverse_iterator(begin());			}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void swap(class_type& rhs)
		{
			m_data.swap(rhs.m_data);
			base_type::swap(static_cast<base_type&>(rhs));
		}
		class_type& operator =(class_type const& rhs)
		{
			class_type(rhs).swap(*this);
			return *this;
		}
	/// @}
};
#ifndef EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	e_size_t N
		,	typename_param_k T
		,	typename_param_k B
		>
EXTL_INLINE void swap(fixed_marray<N, T, B>& lhs, fixed_marray<N, T, B>& rhs)
{
	lhs.swap(rhs);
}

/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	e_size_t N
		,	typename_param_k T
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k fixed_marray<N, T, B>::
const_pointer get_ptr(fixed_marray<N, T, B> const& ar)
{
	return ar.data();
}

template<	e_size_t N
		,	typename_param_k T
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k fixed_marray<N, T, B>::
size_type get_size(fixed_marray<N, T, B> const& ar)
{
	return ar.size();
}
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE) && \
			!defined(EXTL_TEMPLATE_TYPE_REQUIRED_IN_ARGLIST)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	EXTL_NS(e_size_t) N
		,	typename_param_k T
		,	typename_param_k B
		>
EXTL_INLINE void swap(EXTL_NS(fixed_marray)<N, T, B>& lhs, 
						EXTL_NS(fixed_marray)<N, T, B>& rhs)
{
	lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_FIXED_MARRAY_H */
/* //////////////////////////////////////////////////////////////////// */
