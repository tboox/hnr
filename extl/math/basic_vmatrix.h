/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_vmatrix.h		
 *
 * Created:		08.08.10		
 * Updated:		08.08.10
 *
 * Brief:		basic_vmatrix class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_BASIC_VMATRIX_H
#define EXTL_MATH_BASIC_VMATRIX_H

/*!\file basic_vmatrix.h
 * \brief basic_vmatrix class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "vmatrix_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: basic_vmatrix class
 *
 * \param Val The element type
 * \param Buf The buffer type
 *
 * \ingroup extl_group_math
 */
template<	typename_param_k Val
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k Buf = typename_type_def_k buffer_selector<Val>::buffer_type
#else
		,	typename_param_k Buf
#endif
		>
class basic_vmatrix
	: public vmatrix_base	<	basic_vmatrix<Val, Buf>
							,	Buf
							>
{
	private:
		typedef vmatrix_base	<	basic_vmatrix<Val, Buf>
								,	Buf
								>													base_type;

	/// \name Types
	/// @{
	public:
		typedef basic_vmatrix														class_type;
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
		{ basic_vmatrix<Val, Buf> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(class_type const& lhs, const_reference rhs)
		{ basic_vmatrix<Val, Buf> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(const_reference lhs, class_type const& rhs)
		{ basic_vmatrix<Val, Buf> ret(rhs); ret += lhs; return ret;	}

		friend class_type operator-(class_type const& lhs, class_type const& rhs)
		{ basic_vmatrix<Val, Buf> ret(lhs); ret -= rhs; return ret;	}
		friend class_type operator-(class_type const& lhs, const_reference rhs)
		{ basic_vmatrix<Val, Buf> ret(lhs); ret -= rhs; return ret;	}

		friend class_type operator*(class_type const& lhs, const_reference rhs)
		{ basic_vmatrix<Val, Buf> ret(lhs); ret *= rhs; return ret;	}
		friend class_type operator*(const_reference lhs, class_type const& rhs)
		{ basic_vmatrix<Val, Buf> ret(rhs); ret *= lhs; return ret;	}

		friend class_type operator/(class_type const& lhs, const_reference rhs)
		{ basic_vmatrix<Val, Buf> ret(lhs); ret /= rhs; return ret;	}
	#endif

	/// \name Constructors
	/// @{
	public:
		basic_vmatrix()
			: base_type()
		{
		}
		basic_vmatrix(class_type const& rhs)
			: base_type(rhs)
		{
		}
		// d0 * d1
		basic_vmatrix(index_type d0, index_type d1)
			: base_type(d0, d1)
		{
		}
		basic_vmatrix(const_reference value, index_type d0, index_type d1)
			: base_type(value, d0, d1)
		{
		}
		basic_vmatrix(const_pointer p, index_type d0, index_type d1)
			: base_type(p, d0, d1)
		{
		}
	#if defined(EXTL_MEMBER_TEMPLATE_CTOR_SUPPORT) && \
			defined(EXTL_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT)
		template<typename_param_k U, size_type D0, size_type D1>
		basic_vmatrix(U (&p)[D0][D1])
			: base_type(reinterpret_cast<U const*>(p), D0, D1)
		{
		}
	#endif
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
#endif	/* EXTL_MATH_BASIC_VMATRIX_H */
/* //////////////////////////////////////////////////////////////////// */
