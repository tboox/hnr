/* ///////////////////////////////////////////////////////////////////////
 * File:		varray_base.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.07
 *
 * Brief: varray_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_VARRAY_BASE_H
#define EXTL_MATH_VARRAY_BASE_H

/*!\file varray_base.h
 * \brief varray_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "..\utility\operators.h"
#include "..\container\array_base.h"
#include "..\error\error.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief varray_base
 *
 * \param D The derived type
 * \param B The buffer type
 *
 * \ingroup extl_group_math
 */
template<	typename_param_k D
		,	typename_param_k B
		>
class varray_base
	:	public array_base<D, B>
#if EXTL_WORKAROUND_MSVC(==, 1200) 
	,	private operators_arithmetic_2_noleft_<D, typename_type_k B::value_type,
					operators_arithmetic_1_<D
		> > 
	,	private operators_xor_1_2_<D, typename_type_k B::value_type,
					operators_and_1_2_<D, typename_type_k B::value_type
		> > 
	,	private operators_or_1_2_<D, typename_type_k B::value_type,
					operators_shift_2_noleft_<D, typename_type_k B::value_type,
						operators_shift_1_<D,
							operators_mod_2_<D, typename_type_k B::value_type,
								operators_mod_1_<D 
		> > > > >
#elif !defined(EXTL_COMPILER_IS_DMC) && \
		!defined(EXTL_COMPILER_IS_WATCOM)
		// VC6.0 warning: decorated name length exceeded, name was truncated
	,	private operators_arithmetic_2_noleft_<D, typename_type_k B::value_type,
					operators_arithmetic_1_<D, 
						operators_shift_2_noleft_<D, typename_type_k B::value_type,
							operators_shift_1_<D, 
								operators_mod_2_<D, typename_type_k B::value_type,
									operators_mod_1_<D, 
										operators_xor_1_2_<D, typename_type_k B::value_type,
											operators_and_1_2_<D, typename_type_k B::value_type,
												operators_or_1_2_<D, typename_type_k B::value_type
											#ifndef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
												,	operators_base_< D >
											#endif
		> > > > > > > > >
#endif
{
	/// \name Types
	/// @{
	public:
		typedef	array_base<D, B>													base_type;
		typedef varray_base															class_type;
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
			D da, db;
			B &ba = da, &bb = db;
			ba = bb;
			B b(ba);
		 * \endcode
		 */
		varray_base(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		varray_base()
			: base_type()
		{
		}
		varray_base(derived_type const& rhs)
			: base_type(rhs)
		{
		}
		varray_base(const_pointer ar, size_type n)
			: base_type(ar, n)
		{
		}
		varray_base(const_reference value, size_type n)
			: base_type(value, n)
		{
		}
		explicit_k varray_base(size_type n)
			: base_type(value_type(), n)
		{
		}
	/// @}

	/// \name Algorithms
	/// @{
	public:
		value_type	min_() const;
		value_type	max_() const;
		value_type	sum_() const;
	/// @}

	/// \name Operators overload
	/// @{
	public:
		derived_type& operator =(const_reference value);
		derived_type& operator +=(const_reference value);
		derived_type& operator -=(const_reference value);
		derived_type& operator *=(const_reference value);
		derived_type& operator /=(const_reference value);
		derived_type& operator ^=(const_reference value);
		derived_type& operator &=(const_reference value);
		derived_type& operator |=(const_reference value);
		derived_type& operator %=(const_reference value);
		derived_type& operator >>=(const_reference value);
		derived_type& operator <<=(const_reference value);

		derived_type& operator =(derived_type const& rhs);
		derived_type& operator +=(derived_type const& rhs);
		derived_type& operator -=(derived_type const& rhs);
		derived_type& operator ^=(derived_type const& rhs);
		derived_type& operator &=(derived_type const& rhs);
		derived_type& operator |=(derived_type const& rhs);
		derived_type& operator %=(derived_type const& rhs);
		derived_type& operator >>=(derived_type const& rhs);
		derived_type& operator <<=(derived_type const& rhs);

		derived_type&		operator ++();
		derived_type const	operator ++(int);
		derived_type&		operator --();
		derived_type const	operator --(int);

		derived_type const	operator +() const;	// +ar
		derived_type const	operator -() const;	// -ar
		derived_type const	operator ~() const;	// ~ar
		derived_type const	operator !() const;	// !ar

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

		friend derived_type operator>>(const_reference lhs, derived_type const& rhs)
		{ 
			derived_type ret(static_cast<derived_type const&>(rhs));
			
			pointer p = ret.data();
			EXTL_ASSERT(NULL != p);

			size_type n = rhs.size();
			for (size_type i = 0; i < n; ++i) p[i] = lhs >> p[i]; 
			return ret;
		}
		friend derived_type operator<<(const_reference lhs, derived_type const& rhs)
		{ 
			derived_type ret(static_cast<derived_type const&>(rhs));
			
			pointer p = ret.data();
			EXTL_ASSERT(NULL != p);

			size_type n = rhs.size();
			for (size_type i = 0; i < n; ++i) p[i] = lhs << p[i]; 
			return ret;
		}
		friend derived_type operator%(const_reference lhs, derived_type const& rhs)
		{ 
			derived_type ret(static_cast<derived_type const&>(rhs));
			
			pointer p = ret.data();
			EXTL_ASSERT(NULL != p);

			size_type n = rhs.size();
			for (size_type i = 0; i < n; ++i) p[i] = lhs % p[i]; 
			return ret;
		}
	#endif
	/// @}

	/// \name Others
	/// @{
	protected:
		derived_type& get_derive()				{ return static_cast<derived_type&>(*this);			}
		derived_type const& get_derive() const	{ return static_cast<derived_type const&>(*this);	}
	
		buffer_type& get_buffer()				{ return base_type::get_buffer();					}
		buffer_type const& get_buffer() const	{ return base_type::get_buffer();					}
	/// @}
};
/* /////////////////////////////////////////////////////////////////////////
 * Implemention
 */
// =
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator =(derived_type const& rhs)
{
	return base_type::operator =(rhs);
}
// =
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator =(const_reference value)
{
	return base_type::operator =(value);
}
// +=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator +=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] += pr[i]; 
	return get_derive();
}
// +=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator +=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] += value; 
	return get_derive();
}
// -=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator -=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] -= pr[i]; 
	return get_derive();
}
// -=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator -=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] -= value; 
	return get_derive();
}
// *=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator *=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] *= value; 
	return get_derive();
}
// /=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator /=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] /= value; 
	return get_derive();
}
// ^=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator ^=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] ^= pr[i]; 
	return get_derive();
}
// ^=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator ^=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] ^= value; 
	return get_derive();
}
// &=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator &=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] &= pr[i]; 
	return get_derive();
}
// &=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator &=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] &= value; 
	return get_derive();
}
// |=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator |=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] |= pr[i]; 
	return get_derive();
}
// |=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator |=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] |= value; 
	return get_derive();
}
// %=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator %=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] %= pr[i]; 
	return get_derive();
}
// %=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator %=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] %= value; 
	return get_derive();
}
// >>=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator >>=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] >>= pr[i]; 
	return get_derive();
}
// >>=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator >>=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] >>= value; 
	return get_derive();
}

// <<=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator <<=(const_reference value)
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) p[i] <<= value; 
	return get_derive();
}
// <<=
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator <<=(derived_type const& rhs)
{
	pointer pl = get_buffer().data();
	const_pointer pr = rhs.data();
	EXTL_ASSERT(pl != NULL && pr != NULL);

	size_type n = get_buffer().size();
	EXTL_ASSERT(n == rhs.size());

	for (size_type i = 0; i < n; ++i) pl[i] <<= pr[i]; 
	return get_derive();
}
// ++i
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator ++()
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) ++p[i]; 
	return get_derive();
}
// i++
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type const varray_base<D, B>::operator ++(int)
{
	derived_type ret(get_derive());

	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) ++p[i]; 

	return ret;
}
// --i
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type& varray_base<D, B>::operator --()
{
	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) --p[i]; 
	return get_derive();
}
// i--
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type const varray_base<D, B>::operator --(int)
{
	derived_type ret(get_derive());

	pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);

	size_type n = get_buffer().size();
	for (size_type i = 0; i < n; ++i) --p[i]; 

	return ret;
}
#if !defined(EXTL_COMPILER_IS_WATCOM)
// value - class
template<	typename_param_k T
		,	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type operator-(T const& lhs, varray_base<D, B> const& rhs)
{
	typedef typename_type_k varray_base<D, B>::derived_type derived_type;
	typedef typename_type_k varray_base<D, B>::pointer		pointer;
	typedef typename_type_k varray_base<D, B>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs - p[i]; 
	return ret;
}
// value / class
template<	typename_param_k T
		,	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type operator/(T const& lhs, varray_base<D, B> const& rhs)
{
	typedef typename_type_k varray_base<D, B>::derived_type derived_type;
	typedef typename_type_k varray_base<D, B>::pointer		pointer;
	typedef typename_type_k varray_base<D, B>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs / p[i]; 
	return ret;
}

// value >> class
template<	typename_param_k T
		,	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type operator>>(T const& lhs, varray_base<D, B> const& rhs)
{
	typedef typename_type_k varray_base<D, B>::derived_type derived_type;
	typedef typename_type_k varray_base<D, B>::pointer		pointer;
	typedef typename_type_k varray_base<D, B>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs >> p[i]; 
	return ret;
}

// value << class
template<	typename_param_k T
		,	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type operator<<(T const& lhs, varray_base<D, B> const& rhs)
{
	typedef typename_type_k varray_base<D, B>::derived_type derived_type;
	typedef typename_type_k varray_base<D, B>::pointer		pointer;
	typedef typename_type_k varray_base<D, B>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs << p[i]; 
	return ret;
}
// value % class
template<	typename_param_k T
		,	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type operator%(T const& lhs, varray_base<D, B> const& rhs)
{
	typedef typename_type_k varray_base<D, B>::derived_type derived_type;
	typedef typename_type_k varray_base<D, B>::pointer		pointer;
	typedef typename_type_k varray_base<D, B>::size_type	size_type;

	derived_type ret(static_cast<derived_type const&>(rhs));
	
	pointer p = ret.data();
	EXTL_ASSERT(NULL != p);

	size_type n = rhs.size();
	for (size_type i = 0; i < n; ++i) p[i] = lhs % p[i]; 
	return ret;
}
#endif
// min
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
value_type varray_base<D, B>::min_() const
{
	const_pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);
	size_type n = get_buffer().size();

	value_type min_value = p[0];
	for (size_type i = 1; i < n; ++i)
		min_value = p[i] < min_value? p[i] : min_value;
	return min_value;
}
// max
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
value_type varray_base<D, B>::max_() const
{
	const_pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);
	size_type n = get_buffer().size();

	value_type max_value = p[0];
	for (size_type i = 1; i < n; ++i)
		max_value = p[i] > max_value? p[i] : max_value;
	return max_value;
}
// sum
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
value_type varray_base<D, B>::sum_() const
{
	const_pointer p = get_buffer().data();
	EXTL_ASSERT(p != NULL);
	size_type n = get_buffer().size();

	value_type sum_value = p[0];
	for (size_type i = 1; i < n; ++i) sum_value += p[i];
	return sum_value;
}
// +ar
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type const varray_base<D, B>::operator +() const
{
	derived_type ret(get_derive());

	pointer p = ret.data();
	EXTL_ASSERT(p != NULL);

	size_type n = ret.size();
	for (size_type i = 0; i < n; ++i) p[i] = +p[i]; 

	return ret;
}
// -ar
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type const varray_base<D, B>::operator -() const
{
	derived_type ret(get_derive());

	pointer p = ret.data();
	EXTL_ASSERT(p != NULL);

	size_type n = ret.size();
	for (size_type i = 0; i < n; ++i) p[i] = -p[i]; 

	return ret;
}
// ~ar
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type const varray_base<D, B>::operator ~() const
{
	derived_type ret(get_derive());

	pointer p = ret.data();
	EXTL_ASSERT(p != NULL);

	size_type n = ret.size();
	for (size_type i = 0; i < n; ++i) p[i] = ~p[i]; 

	return ret;
}
// !ar
template<	typename_param_k D
		,	typename_param_k B
		>
inline typename_type_ret_k varray_base<D, B>::
derived_type const varray_base<D, B>::operator !() const
{
	derived_type ret(get_derive());

	pointer p = ret.data();
	EXTL_ASSERT(p != NULL);

	size_type n = ret.size();
	for (size_type i = 0; i < n; ++i) p[i] = !p[i]; 

	return ret;
}
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE void swap(varray_base<D, B>& lhs, varray_base<D, B>& rhs)
{
	static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k varray_base<D, B>::
const_pointer get_ptr(varray_base<D, B> const& ar)
{
	return static_cast<D const&>(ar).data();
}

template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k varray_base<D, B>::
size_type get_size(varray_base<D, B> const& ar)
{
	return static_cast<D const&>(ar).size();
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
EXTL_INLINE void swap(EXTL_NS(varray_base)<D, B>& lhs, 
						EXTL_NS(varray_base)<D, B>& rhs)
{
	static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_VARRAY_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
