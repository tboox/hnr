/* ///////////////////////////////////////////////////////////////////////
 * File:		vmatrix_base.h		
 *
 * Created:		08.08.10		
 * Updated:		08.08.10
 *
 * Brief: vmatrix_base class - fixed-size
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_VMATRIX_BASE_H
#define EXTL_MATH_VMATRIX_BASE_H

/*!\file vmatrix_base.h
 * \brief vmatrix_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../utility/operators.h"
#include "../container/matrix_base.h"
#include "../error/error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief vmatrix_base
 *
 * \param Dev The derived type
 * \param Buf The buffer type
 *
 * \ingroup extl_group_math
 */
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
class vmatrix_base
	:	public matrix_base<Dev, Buf>
#if !defined(EXTL_COMPILER_IS_DMC) && \
		!defined(EXTL_COMPILER_IS_WATCOM) 
	,	private operators_arithmetic_2_noleft_<Dev, typename_type_k Buf::value_type,
					operators_arithmetic_1_<Dev
		> > 
#endif
{
	/// \name Types
	/// @{
	public:
		typedef	matrix_base<Dev, Buf>													base_type;
		typedef vmatrix_base													class_type;
		typedef typename_type_k base_type::derived_type								derived_type;
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
	/// @}

	private:
		/*!\brief Prohibit the following case:
		 * 
		 * \code
			Dev da, db;
			Buf &ba = da, &bb = db;
			ba = bb;
			Buf b(ba);
		 * \endcode
		 */
		vmatrix_base(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		vmatrix_base()
			: base_type()
		{
		}
		vmatrix_base(derived_type const& rhs)
			: base_type(rhs)
		{
		}
		// d0 * d1
		vmatrix_base(const_pointer p, index_type d0, index_type d1)
			: base_type(p, d0, d1)
		{
		}
		vmatrix_base(const_reference value, index_type d0, index_type d1)
			: base_type(value, d0, d1)
		{
		}
		vmatrix_base(index_type d0, index_type d1)
			: base_type(value_type(), d0, d1)
		{
		}
	/// @}

	/// \name Statistics Algorithms
	/// @{
	public:
		/// min
		value_type	find_min() const	{ return stats_min(*this); }
		/// max
		value_type	find_max() const	{ return stats_max(*this); }
		/// sum
		value_type	sum() const			{ return stats_sum(*this); }
		/// average = (x1 + x2 + ... + xn) / n;
		value_type	avg() const			{ return stats_avg(*this); }
		/// variance = ((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / n;
		value_type	var() const			{ return stats_var(*this); }
		/// standard deviation = sqrt(((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / n);
		value_type	sd() const			{ return stats_sd(*this); }
	/// @}

	/// \name Operators overload
	/// @{
	public:
		derived_type& operator =(const_reference value);
		derived_type& operator +=(const_reference value);
		derived_type& operator -=(const_reference value);
		derived_type& operator *=(const_reference value);
		derived_type& operator /=(const_reference value);
		

		derived_type& operator =(derived_type const& rhs);
		derived_type& operator +=(derived_type const& rhs);
		derived_type& operator -=(derived_type const& rhs);

		derived_type&		operator ++();
		derived_type const	operator ++(int);
		derived_type&		operator --();
		derived_type const	operator --(int);

		derived_type const	operator +() const;	// +ma
		derived_type const	operator -() const;	// -ma

	#if defined(EXTL_COMPILER_IS_WATCOM)
		friend derived_type operator-(const_reference lhs, derived_type const& rhs)
		{ 
			derived_type ret(static_cast<derived_type const&>(rhs));
			
			pointer p = ret.data();
			EXTL_ASSERT(NULL != p);

			size_type n = rhs.size();
			for (size_type i = 0; i < n; ++i) p[i] = lhs - p[i]; 
			return ret;
		}
		friend derived_type operator/(const_reference lhs, derived_type const& rhs)
		{ 
			derived_type ret(static_cast<derived_type const&>(rhs));
			
			pointer p = ret.data();
			EXTL_ASSERT(NULL != p);

			size_type n = rhs.size();
			for (size_type i = 0; i < n; ++i) p[i] = lhs / p[i]; 
			return ret;
		}
	#endif
	/// @}

	/// \name Others
	/// @{
	protected:
		derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
	
		buffer_type&		buffer()		{ return base_type::buffer();						}
		buffer_type const&	buffer() const	{ return base_type::buffer();						}
	/// @}
};
/* /////////////////////////////////////////////////////////////////////////
 * Implemention
 */
// =
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator =(derived_type const& rhs)
{
	return base_type::operator =(rhs);
}
// =
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator =(const_reference value)
{
	return base_type::operator =(value);
}
// +=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator +=(derived_type const& rhs)
{
	pointer pl = buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] += pr[i]; 
	return derive();
}
// +=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator +=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] += value; 
	return derive();
}
// -=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator -=(derived_type const& rhs)
{
	pointer pl = buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] -= pr[i]; 
	return derive();
}
// -=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator -=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] -= value; 
	return derive();
}
// *=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator *=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] *= value; 
	return derive();
}
// /=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator /=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] /= value; 
	return derive();
}

// ++i
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator ++()
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) ++p[i]; 
	return derive();
}
// i++
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type const vmatrix_base<Dev, Buf>::operator ++(int)
{
	derived_type ret(derive());

	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) ++p[i]; 

	return ret;
}
// --i
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type& vmatrix_base<Dev, Buf>::operator --()
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) --p[i]; 
	return derive();
}
// i--
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type const vmatrix_base<Dev, Buf>::operator --(int)
{
	derived_type ret(derive());

	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = buffer().size();
	for (size_type i = 0; i < n; ++i) --p[i]; 

	return ret;
}
#if !defined(EXTL_COMPILER_IS_WATCOM)
// value - class
template<	typename_param_k T
		,	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type operator-(T const& lhs, vmatrix_base<Dev, Buf> const& rhs)
{
	typedef typename_type_k vmatrix_base<Dev, Buf>::derived_type derived_type;
	typedef typename_type_k vmatrix_base<Dev, Buf>::pointer		pointer;
	typedef typename_type_k vmatrix_base<Dev, Buf>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs - p[i]; 
	return ret;
}
// value / class
template<	typename_param_k T
		,	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vmatrix_base<Dev, Buf>::
derived_type operator/(T const& lhs, vmatrix_base<Dev, Buf> const& rhs)
{
	typedef typename_type_k vmatrix_base<Dev, Buf>::derived_type derived_type;
	typedef typename_type_k vmatrix_base<Dev, Buf>::pointer		pointer;
	typedef typename_type_k vmatrix_base<Dev, Buf>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs / p[i]; 
	return ret;
}
#endif
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
EXTL_INLINE void swap(vmatrix_base<Dev, Buf>& lhs, vmatrix_base<Dev, Buf>& rhs)
{
	static_cast<Dev&>(lhs).swap(static_cast<Dev&>(rhs));
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
EXTL_INLINE typename_type_ret_k vmatrix_base<Dev, Buf>::
const_pointer get_ptr(vmatrix_base<Dev, Buf> const& mx)
{
	return static_cast<Dev const&>(mx).data();
}

template<	typename_param_k Dev
		,	typename_param_k Buf
		>
EXTL_INLINE typename_type_ret_k vmatrix_base<Dev, Buf>::
size_type get_size(vmatrix_base<Dev, Buf> const& mx)
{
	return static_cast<Dev const&>(mx).size();
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

template<	typename_param_k Dev
		,	typename_param_k Buf
		>
EXTL_INLINE void swap(EXTL_NS(vmatrix_base)<Dev, Buf>& lhs, 
						EXTL_NS(vmatrix_base)<Dev, Buf>& rhs)
{
	static_cast<Dev&>(lhs).swap(static_cast<Dev&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_VMATRIX_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
