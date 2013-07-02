/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_vvector.h		
 *
 * Created:		08.08.07			
 * Updated:		09.01.27
 *
 * Brief:		the basic_vvector class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_BASIC_VVECTOR_H
#define EXTL_MATH_BASIC_VVECTOR_H

/*!\file basic_vvector.h
 * \brief basic_vvector class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../memory/buffer.h"
#include "vvector_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: basic_vvector class
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
class basic_vvector
	: public vvector_base<	basic_vvector<Val, Buf>
						,	Buf
						>
{
	private:
		typedef vvector_base	<	basic_vvector<Val, Buf>
							,	Buf
							>														base_type;

	/// \name Types
	/// @{
	public:
		typedef basic_vvector														class_type;
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
		{ basic_vvector<Val, Buf> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(class_type const& lhs, const_reference rhs)
		{ basic_vvector<Val, Buf> ret(lhs); ret += rhs; return ret;	}
		friend class_type operator+(const_reference lhs, class_type const& rhs)
		{ basic_vvector<Val, Buf> ret(rhs); ret += lhs; return ret;	}

		friend class_type operator-(class_type const& lhs, class_type const& rhs)
		{ basic_vvector<Val, Buf> ret(lhs); ret -= rhs; return ret;	}
		friend class_type operator-(class_type const& lhs, const_reference rhs)
		{ basic_vvector<Val, Buf> ret(lhs); ret -= rhs; return ret;	}

		friend class_type operator*(class_type const& lhs, const_reference rhs)
		{ basic_vvector<Val, Buf> ret(lhs); ret *= rhs; return ret;	}
		friend class_type operator*(const_reference lhs, class_type const& rhs)
		{ basic_vvector<Val, Buf> ret(rhs); ret *= lhs; return ret;	}

		friend class_type operator/(class_type const& lhs, const_reference rhs)
		{ basic_vvector<Val, Buf> ret(lhs); ret /= rhs; return ret;	}
	#endif

	/// \name Constructors
	/// @{
	public:
		basic_vvector()
			: base_type()
		{
		}
		basic_vvector(class_type const& rhs)
			: base_type(rhs)
		{
		}
		basic_vvector(const_pointer vv, size_type n, bool_type is_h = e_true_v)
			: base_type(vv, n, is_h)
		{
		}
		basic_vvector(const_reference value, size_type n, bool_type is_h = e_true_v)
			: base_type(value, n, is_h)
		{
		}
		explicit_k basic_vvector(size_type n, bool_type is_h = e_true_v)
			: base_type(n, is_h)
		{
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& vv)		{ return base_type::operator=(vv);		}
		class_type& operator=(const_reference value)	{ return base_type::operator=(value);	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_MATH_BASIC_VVECTOR_H */
/* //////////////////////////////////////////////////////////////////// */
