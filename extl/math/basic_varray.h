/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_varray.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.21
 *
 * Brief: basic_varray class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_BASIC_VARRAY_H
#define EXTL_MATH_BASIC_VARRAY_H

/*!\file basic_varray.h
 * \brief basic_varray class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "..\memory\buffer.h"
#include "varray_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: basic_varray class
 *
 * \param T The element type
 * \param B The buffer type
 *
 * \ingroup extl_group_math
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k B = typename_type_def_k buffer_selector<T>::buffer_type 
#else
		,	typename_param_k B
#endif
		>
class basic_varray
	: public varray_base<	basic_varray<T, B>
						,	B
						>
{
	private:
		typedef varray_base	<	basic_varray<T, B>
							,	B
							>														base_type;

	/// \name Types
	/// @{
	public:
		typedef basic_varray														class_type;
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

	public:
	#if defined(EXTL_COMPILER_IS_DMC) || \
			defined(EXTL_COMPILER_IS_WATCOM)
		friend class_type operator+(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(const_reference lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(rhs); ret += lhs; return ret;	}

		friend class_type operator-(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret -= rhs; return ret;	}
		friend class_type operator-(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret -= rhs; return ret;	}

		friend class_type operator*(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret *= rhs; return ret;	}
		friend class_type operator*(const_reference lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(rhs); ret *= lhs; return ret;	}

		friend class_type operator/(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret /= rhs; return ret;	}

		friend class_type operator^(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret ^= rhs; return ret;	}
		friend class_type operator^(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret ^= rhs; return ret;	}
		friend class_type operator^(const_reference lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(rhs); ret ^= lhs; return ret;	}

		friend class_type operator&(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret &= rhs; return ret;	}
		friend class_type operator&(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret &= rhs; return ret;	}
		friend class_type operator&(const_reference lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(rhs); ret &= lhs; return ret;	}

		friend class_type operator|(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret |= rhs; return ret;	}
		friend class_type operator|(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret |= rhs; return ret;	}
		friend class_type operator|(const_reference lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(rhs); ret |= lhs; return ret;	}

		friend class_type operator>>(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret >>= rhs; return ret;	}
		friend class_type operator>>(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret >>= rhs; return ret;	}

		friend class_type operator<<(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret <<= rhs; return ret;	}
		friend class_type operator<<(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret <<= rhs; return ret;	}

		friend class_type operator%(class_type const& lhs, class_type const& rhs)
		{ basic_varray<T, B> ret(lhs); ret %= rhs; return ret;	}
		friend class_type operator%(class_type const& lhs, const_reference rhs)
		{ basic_varray<T, B> ret(lhs); ret %= rhs; return ret;	}
	#endif

	/// \name Constructors
	/// @{
	public:
		basic_varray()
			: base_type()
		{
		}
		basic_varray(class_type const& rhs)
			: base_type(rhs)
		{
		}
		basic_varray(const_pointer ar, size_type n)
			: base_type(ar, n)
		{
		}
		basic_varray(const_reference value, size_type n)
			: base_type(value, n)
		{
		}
		explicit_k basic_varray(size_type n)
			: base_type(n)
		{
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& ar)		{ return base_type::operator=(ar);		}
		class_type& operator=(const_reference value)	{ return base_type::operator=(value);	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_BASIC_VARRAY_H */
/* //////////////////////////////////////////////////////////////////// */
