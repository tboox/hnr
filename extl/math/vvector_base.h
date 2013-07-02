/* ///////////////////////////////////////////////////////////////////////
 * File:		vvector_base.h		
 *
 * Created:		08.08.07			
 * Updated:		09.01.27
 *
 * Brief:		vvector_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_VVECTOR_BASE_H
#define EXTL_MATH_VVECTOR_BASE_H

/*!\file vvector_base.h
 * \brief vvector_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../utility/operators.h"
#include "../container/array_base.h"
#include "../error/error.h"
#include "../algorithm/stats.h"
#include "../math/math.h"
#include "vmatrix_selector.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief vvector_base
 *
 * \param Dev The derived type
 * \param Buf The buffer type
 *
 * \ingroup extl_group_math
 */
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
class vvector_base
	:	public array_base<Dev, Buf>
#if !defined(EXTL_COMPILER_IS_DMC) && \
		!defined(EXTL_COMPILER_IS_WATCOM)
		// VC6.0 warning: decorated name length exceeded, name was truncated
	,	private operators_arithmetic_2_noleft_<Dev, typename_type_k Buf::value_type,
					operators_add_1_<Dev, 
						operators_sub_1_<Dev 
		> > >
#endif
{
	/// \name Types
	/// @{
	public:
		typedef	array_base<Dev, Buf>												base_type;
		typedef vvector_base														class_type;
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
		typedef typename_type_k vmatrix_selector<value_type>::vmatrix_type			vmatrix_type;
	/// @}

	/// \name Members
	/// @{
	private:
		bool_type																	m_is_col;
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
		vvector_base(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		vvector_base()
			: base_type()
			, m_is_col(e_true_v)
		{
		}
		vvector_base(derived_type const& rhs)
			: base_type(rhs)
			, m_is_col(rhs.is_col())
		{
		}
		vvector_base(const_pointer vv, size_type n, bool_type is_col = e_true_v)
			: base_type(vv, n)
			, m_is_col(is_col)
		{
		}
		vvector_base(const_reference value, size_type n, bool_type is_col = e_true_v)
			: base_type(value, n)
			, m_is_col(is_col)
		{
		}
		explicit_k vvector_base(size_type n, bool_type is_col = e_true_v)
			: base_type(value_type(), n)
			, m_is_col(is_col)
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
		/// variance = ((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / (n - 1);
		value_type	var() const			{ return stats_var(*this); }
		/// standard deviation = sqrt(((x1 - avg)^2 + (x2 - avg)^2 + ... + (xn - avg)^2) / (n - 1);
		value_type	sd() const			{ return stats_sd(*this); }
		/// first-order norm: ||x|| = |x1| + |x2| + ... + |xn|;
		value_type	norm_1() const		{ return stats_norm_1(*this); }
		/// second-order norm: ||x|| = sqrt(|x1|^2 + |x2|^2 + ... + |xn|^2);
		value_type	norm_2() const		{ return stats_norm_2(*this); }
		/// second-order norm^2: ||x|| = |x1|^2 + |x2|^2 + ... + |xn|^2;
		value_type	norm_22() const		{ return stats_norm_22(*this); }
		/// stats_infinite norm: ||x|| = max(|x1|, |x2|, ... , |xn|);
		value_type	norm_i() const		{ return stats_norm_i(*this); }
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// returns \true if the direction of vector is column vector
		bool_type		is_col() const		{ return m_is_col;	}
		/// sets the direction of vector 
		void			is_col(bool_type b)	{ m_is_col = b;		}
	/// @}

	/// \name Algebraic operation
	/// @{
	public:
		/// returns vector transpose
		derived_type const	tr() const			{ derived_type tmp(derive()); tmp.is_col(!tmp.is_col()); return tmp;	}

		/// return inner product of vector
		/// (x, y) = x1 * y1 + x2 * y2 + ... + xn * yn;
		value_type const	dot(derived_type const& rhs) const;

		/// return inner product of vector
		/// (x, x) = x1 * x1 + x2 * x2 + ... + xn * xn;
		value_type const	dot() const			{ return dot(derive());	}

		/// return (x1 * y1, x2 * y2, ... , xn * yn)
		derived_type const	dot_mul(derived_type const& rhs) const;

		/// return (x1 / y1, x2 / y2, ... , xn / yn)
		derived_type const	dot_div(derived_type const& rhs) const;

		/// return (x1^2, x2^2, ... , xn^2)
		derived_type const	dot_pow2() const	{ return derive().dot_mul(derive());	}

		/// returns \true if this vector is orthogonal with rhs
		bool_type			is_orthogonal(derived_type const& rhs) const	{ return (xtl_abs(dot(rhs) - 1) < 1e-10);	}

		/// returns \true if this vector is orthogonal
		bool_type			is_orthogonal() const	{ return is_orthogonal(derive());	}
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

		derived_type const	operator +() const;	// +vv
		derived_type const	operator -() const;	// -vv

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
		// matrix = vector * vector
		vmatrix_type operator *(derived_type const& rhs) const
		{
			size_type lhs_n = derive().size();
			size_type rhs_n = rhs.size();

			// - * |
			if (!derive().is_col() && rhs.is_col() && lhs_n == rhs_n)
			{
				vmatrix_type vm(1, 1);
				vm.at(0, 0) = value_type();
				for (index_type i = 0; i < lhs_n; ++i)
					vm.at(0, 0) += derive().at(i) * rhs.at(i);

				return vm;
			}
			// | * -
			else if (derive().is_col() && !rhs.is_col())
			{
				vmatrix_type vm(lhs_n, rhs_n);

				for (index_type i = 0; i < lhs_n; ++i)
					for (index_type j = 0; j < rhs_n; ++j)
						vm.at(i, j) = derive().at(i) * rhs.at(j);

				return vm;
			}
			else 
			{
				EXTL_MESSAGE_ASSERT(0, "the vectors can be not multiplied");
				return vmatrix_type();
			}
		}
	/// @}

	/// \name Others
	/// @{
	protected:
		derived_type&		derive()			{ return static_cast<derived_type&>(*this);			}
		derived_type const&	derive() const		{ return static_cast<derived_type const&>(*this);	}
	
		buffer_type&		buffer()			{ return base_type::buffer();					}
		buffer_type const&	buffer() const		{ return base_type::buffer();					}
	/// @}
};
/* /////////////////////////////////////////////////////////////////////////
 * Implemention
 */
// =
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator =(derived_type const& rhs)
{
	return base_type::operator =(rhs);
}
// =
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator =(const_reference value)
{
	return base_type::operator =(value);
}
// +=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator +=(derived_type const& rhs)
{
	pointer pl = buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = derive().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] += pr[i]; 
	return derive();
}
// +=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator +=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) p[i] += value; 
	return derive();
}
// -=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator -=(derived_type const& rhs)
{
	pointer pl = buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = derive().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] -= pr[i]; 
	return derive();
}
// -=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator -=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) p[i] -= value; 
	return derive();
}
// *=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator *=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) p[i] *= value; 
	return derive();
}
// /=
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator /=(const_reference value)
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) p[i] /= value; 
	return derive();
}

// ++i
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator ++()
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) ++p[i]; 
	return derive();
}
// i++
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type const vvector_base<Dev, Buf>::operator ++(int)
{
	derived_type ret(derive());

	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) ++p[i]; 

	return ret;
}
// --i
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type& vvector_base<Dev, Buf>::operator --()
{
	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) --p[i]; 
	return derive();
}
// i--
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type const vvector_base<Dev, Buf>::operator --(int)
{
	derived_type ret(derive());

	pointer p = buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = derive().size();
	for (size_type i = 0; i < n; ++i) --p[i]; 

	return ret;
}
#if !defined(EXTL_COMPILER_IS_WATCOM)
// value - class
template<	typename_param_k T
		,	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type operator-(T const& lhs, vvector_base<Dev, Buf> const& rhs)
{
	typedef typename_type_k vvector_base<Dev, Buf>::derived_type derived_type;
	typedef typename_type_k vvector_base<Dev, Buf>::pointer		pointer;
	typedef typename_type_k vvector_base<Dev, Buf>::size_type	size_type;

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
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type operator/(T const& lhs, vvector_base<Dev, Buf> const& rhs)
{
	typedef typename_type_k vvector_base<Dev, Buf>::derived_type derived_type;
	typedef typename_type_k vvector_base<Dev, Buf>::pointer		pointer;
	typedef typename_type_k vvector_base<Dev, Buf>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs / p[i]; 
	return ret;
}

#endif
// +vv
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type const vvector_base<Dev, Buf>::operator +() const
{
	derived_type ret(derive());

	pointer p = ret.data();
	EXTL_ASSERT(p != NULL);

	size_type n = ret.size();
	for (size_type i = 0; i < n; ++i) p[i] = +p[i]; 

	return ret;
}
// -vv
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type const vvector_base<Dev, Buf>::operator -() const
{
	derived_type ret(derive());

	pointer p = ret.data();
	EXTL_ASSERT(p != NULL);

	size_type n = ret.size();
	for (size_type i = 0; i < n; ++i) p[i] = -p[i]; 

	return ret;
}
/// return inner product of vector
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
value_type const vvector_base<Dev, Buf>::dot(derived_type const& rhs) const
{
	EXTL_ASSERT(derive().size() == rhs.size());

	value_type ret = value_type();
	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) ret += derive()[i] * rhs[i];
	return ret;
}

/// return (x1 * y1, x2 * y2, ... , xn * yn)
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type const vvector_base<Dev, Buf>::dot_mul(derived_type const& rhs) const
{
	EXTL_ASSERT(derive().size() == rhs.size());

	derived_type ret(derive().size());
	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) ret[i] = derive()[i] * rhs[i];
	return ret;
}

/// return (x1 / y1, x2 / y2, ... , xn / yn)
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
inline typename_type_ret_k vvector_base<Dev, Buf>::
derived_type const vvector_base<Dev, Buf>::dot_div(derived_type const& rhs) const
{
	EXTL_ASSERT(derive().size() == rhs.size());

	derived_type ret(derive().size());
	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) ret[i] = derive()[i] / rhs[i];
	return ret;
}
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
EXTL_INLINE void swap(vvector_base<Dev, Buf>& lhs, vvector_base<Dev, Buf>& rhs)
{
	static_cast<Dev&>(lhs).swap(static_cast<Dev&>(rhs));
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k Dev
		,	typename_param_k Buf
		>
EXTL_INLINE typename_type_ret_k vvector_base<Dev, Buf>::
const_pointer get_ptr(vvector_base<Dev, Buf> const& vv)
{
	return static_cast<Dev const&>(vv).data();
}

template<	typename_param_k Dev
		,	typename_param_k Buf
		>
EXTL_INLINE typename_type_ret_k vvector_base<Dev, Buf>::
size_type get_size(vvector_base<Dev, Buf> const& vv)
{
	return static_cast<Dev const&>(vv).size();
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
EXTL_INLINE void swap(EXTL_NS(vvector_base)<Dev, Buf>& lhs, 
						EXTL_NS(vvector_base)<Dev, Buf>& rhs)
{
	static_cast<Dev&>(lhs).swap(static_cast<Dev&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_VVECTOR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
