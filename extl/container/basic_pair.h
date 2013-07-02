/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_pair.h		
 *
 * Created:		08.07.21		
 * Updated:		08.07.24
 *
 * Brief: basic_pair class - compress empty type
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BASIC_PAIR_H
#define EXTL_CONTAINER_BASIC_PAIR_H

/*!\file basic_pair.h
 * \brief basic_pair class
 */
#ifndef __cplusplus
#	error basic_pair.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

#ifdef EXTL_CONTAINER_TUPLE2_SUPPORT
#	include "detail/tuple2.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template<	typename_param_k T1 = e_null_t
		,	typename_param_k T2 = e_null_t
		>
struct basic_pair;
#else
template<	typename_param_k T1
		,	typename_param_k T2
		>
struct basic_pair;
#endif

/*!\brief basic_pair class
 * 
 * \param T1 The first type
 * \param T2 The second type
 * 
 * \ingroup extl_group_container
 */
#ifdef EXTL_CONTAINER_TUPLE2_SUPPORT
template<	typename_param_k T1
		,	typename_param_k T2
		>
struct basic_pair 
	: EXTL_NS_DETAIL(tuple2)<T1, T2>
{
	private:
		typedef EXTL_NS_DETAIL(tuple2)<T1, T2>									base_type;
	/// \name Type
	/// @{
	public:
		typedef basic_pair														class_type;
		typedef T1																first_type;
		typedef T2																second_type;
		typedef typename_type_k call_traits<first_type>::param_type				first_param_type;
		typedef typename_type_k call_traits<first_type>::reference				first_reference;
		typedef typename_type_k call_traits<first_type>::const_reference		first_const_reference;
		typedef typename_type_k call_traits<second_type>::param_type			second_param_type;
		typedef typename_type_k call_traits<second_type>::reference				second_reference;
		typedef typename_type_k call_traits<second_type>::const_reference		second_const_reference;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_pair() 
			: base_type() {}

		explicit_k basic_pair(first_param_type f) 
			: base_type(f) {}

		basic_pair(first_param_type f, second_param_type s) 
			: base_type(f, s) {}

		basic_pair(class_type const& rhs) 
			: base_type(rhs) {}

	/// @}

	/// \name Accessors and Mutators
	/// @{
	public:
		void swap(class_type& rhs)
		{
			static_cast<base_type&>(*this).swap(rhs);
		}
		class_type& operator =(class_type const& rhs)
		{
			static_cast<base_type&>(*this) = rhs;
			return *this;
		}

		first_reference			first()						{ return base_type::get_head();	}
		first_const_reference	first() const				{ return base_type::get_head();	}
		void					first(first_param_type f)	{ base_type::set_head(f);		}

		second_reference		second()					{ return base_type::get_tail();	}
		second_const_reference	second() const				{ return base_type::get_tail();	}
		void					second(second_param_type s)	{ base_type::set_tail(s);		}

	/// @}
};
#else
template<	typename_param_k T1
		,	typename_param_k T2
		>
struct basic_pair 
{
	/// \name Type
	/// @{
	public:
		typedef basic_pair														class_type;
		typedef T1																first_type;
		typedef T2																second_type;
		typedef first_type const&												first_param_type;
		typedef first_type&														first_reference;
		typedef first_type const&												first_const_reference;
		typedef second_type const&												second_param_type;
		typedef second_type&													second_reference;
		typedef second_type const&												second_const_reference;
	/// @}

	/// \name Members
	/// @{
	private:
		first_type																m_first;
		second_type																m_second;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_pair() 
			: m_first(), m_second()
		{}

		explicit_k basic_pair(first_param_type f) 
			: m_first(f), m_second() 
		{}

		basic_pair(first_param_type f, second_param_type s) 
			: m_first(f), m_second(s) 
		{}

		basic_pair(class_type const& rhs) 
			: m_first(rhs.first()), m_second(rhs.second()) 
		{}

	/// @}

	/// \name Accessors and Mutators
	/// @{
	public:
		void swap(class_type& rhs)
		{
			std_swap(m_first, rhs.m_first);
			std_swap(m_second, rhs.m_second);
		}
		class_type& operator =(class_type const& rhs)
		{
			if (this == &rhs) return *this;

			m_first = rhs.first();
			m_second = rhs.second();

			return *this;
		}

		first_reference			first()						{ return m_first;	}
		first_const_reference	first() const				{ return m_first;	}
		void					first(first_param_type f)	{ m_first = f;		}

		second_reference		second()					{ return m_second;	}
		second_const_reference	second() const				{ return m_second;	}
		void					second(second_param_type s)	{ m_second = s;		}

	/// @}
};
#endif
/* ///////////////////////////////////////////////////////////////////////
 * Make basic_pair
 */

template<	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE basic_pair<T1, T2> make_pair(T1 const& t1, T2 const& t2) 
{
  return basic_pair<T1, T2>(t1, t1);
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_CONTAINER_BASIC_PAIR_H */
/* //////////////////////////////////////////////////////////////////// */
