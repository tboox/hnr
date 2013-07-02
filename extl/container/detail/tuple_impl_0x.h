/* ///////////////////////////////////////////////////////////////////////
 * File:		tuple_impl_0x.h.h		
 *
 * Created:		08.07.21		
 * Updated:		08.07.24
 *
 * Brief: tuple class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_TUPLE_IMPL_0x_H
#define EXTL_CONTAINER_DETAIL_TUPLE_IMPL_0x_H

#ifndef __cplusplus
#	error tuple_impl_0x.h.h need be supported by c++.
#endif

#if !defined(EXTL_0x_VARIADIC_TEMPLATE_SUPPORT) 
#	error tuple_impl_0x.h.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../../algorithm/algorithm.h"

#ifdef EXTL_TYPE_TRAITS_CALL_TRAITS_SUPPORT
#	include "../../type/traits/call_traits.h"
#endif

#ifdef EXTL_MPL_IF_SUPPORT
#	include "../../mpl/if_.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT
#	include "../../type/traits/add_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#	include "../../type/traits/is_const.h"
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * Forward declaration
 */
template<typename_param_k... Ts> 
class tuple;

template<typename_param_k T>
struct tuple_elements_size;

template<	e_size_t N
		,	typename_param_k T
		>
struct tuple_element_traits;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_BEGIN_NAMESPACE

template<e_size_t N, typename_param_k... Ts>
class tuple_impl; 

template<e_size_t N>
class tuple_impl<N>{};

template<e_size_t N, typename_param_k H, typename_param_k... T>
class tuple_impl<N, H, T...>
	: public tuple_impl<N + 1, T...>
{
	public:
		typedef tuple_impl<N + 1, T...>									base_type;
		typedef tuple_impl												class_type;
		typedef H														head_type;
		typedef typename_type_k call_traits<head_type>::param_type		head_param_type;
		typedef typename_type_k call_traits<head_type>::reference		head_reference;
		typedef typename_type_k call_traits<head_type>::const_reference	head_const_reference;

	private:
		head_type														m_head;

	public:
		tuple_impl()
			: base_type(), m_head()
		{}
		explicit_k tuple_impl(head_param_type h, typename_type_k call_traits<T>::param_type... t)
			: base_type(t...), m_head(h) 
		{}
		tuple_impl(class_type const& rhs)
			: base_type(rhs.tail()), m_head(rhs.m_head) 
		{}
	public:
		head_reference head()				{ return m_head;	}
		head_const_reference head() const	{ return m_head;	}

		base_type& tail()					{ return *this;		}
		base_type const& tail() const		{ return *this;		}

	public:
		class_type& operator =(class_type const& rhs)
		{
			m_head = rhs.head();
			tail() = rhs.tail();
			return *this;
		}

		void swap(class_type& rhs)
		{
			std_swap(m_head, rhs.m_head);
			std_swap(tail(), rhs.tail());
		}

};
template<	e_size_t N
		,	typename_param_k T
		>
struct tuple_element_traits_impl;

template<e_size_t N, typename_param_k H, typename_param_k... T>
struct tuple_element_traits_impl<N, tuple<H, T...> >
	: tuple_element_traits_impl<N - 1, tuple<T...> > 
{};

template<typename_param_k H, typename_param_k... T>
struct tuple_element_traits_impl<0, tuple<H, T...> > 
{
	typedef H				type;
};

template<e_size_t N, typename_param_k H, typename_param_k... T>
EXTL_INLINE typename_type_ret_k call_traits<H>::reference
get_tuple_element_impl(tuple_impl<N, H, T...>& t)
{
  return t.head();
}

template<e_size_t N, typename_param_k H, typename_param_k... T>
EXTL_INLINE typename_type_ret_k call_traits<H>::const_reference
get_tuple_element_impl(tuple_impl<N, H, T...> const& t)
{
  return t.head();
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE

template<typename_param_k... Ts>
struct tuple_elements_size<tuple<Ts...> >
{
	EXTL_STATIC_MEMBER_CONST(e_size_t, value = sizeof...(Ts));
};

/*!\brief tuple_element_traits class
 * 
 * \param N The sequence number of elements
 * \param T The tuple<> type
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k T
		>
struct tuple_element_traits 
{
	private:
		typedef typename_type_k EXTL_NS_DETAIL(tuple_element_traits_impl)<N, T>::type	old_type_;

	/// \name Types
	/// @{
	public:
		// The element type will be added const-qualified if tuple<> is const-qualified
	#if defined(EXTL_MPL_IF_SUPPORT) && \
			defined(EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT) && \
				defined(EXTL_TYPE_TRAITS_IS_CONST_SUPPORT)
		/// The element type
		typedef typename_type_k EXTL_NS_MPL(if_)<	(is_const<T>::value)
												,	typename_type_k add_const<old_type_>::type
												,	old_type_
												>::type									type;
	#else
		typedef old_type_																type;
	#endif
		/// The return type of element 
		typedef typename_type_k call_traits<type>::reference							reference;
		/// The const return type of element 
		typedef typename_type_k call_traits<type>::const_reference						const_reference;
		/// The parameter type of element 
		typedef typename_type_k call_traits<type>::param_type							param_type;
	/// @}
};

/*!\brief Gets the const element of tuple
 * 
 * \param N The sequence number of elements
 * \param Ts The elements type
 * \param t	tuple<Ts...> const&
 *
 * \code
	tuple<int, void*, double> t(1, NULL, 1.5);
	int a = get_tuple_element<0>(t);
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k... Ts
		>
EXTL_INLINE 
typename_type_ret_k 
tuple_element_traits<	N
					,	tuple<Ts...>
					>::const_reference
get_tuple_element(tuple<Ts...> const& t EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
{ 
	EXTL_STATIC_ASSERT(N < (tuple_elements_size<tuple<Ts...> >::value));
	return EXTL_NS_DETAIL(get_tuple_element_impl)<N>(t); 
}

/*!\brief Gets the element of tuple
 * 
 * \param N The sequence number of elements
 * \param Ts The elements type
 * \param t	tuple<Ts...>&
 *
 * \code
	tuple<int, void*, double> t(1, NULL, 1.5);
	int a = get_tuple_element<0>(t);
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k... Ts
		>
EXTL_INLINE 
typename_type_ret_k 
tuple_element_traits<	N
					,	tuple<Ts...>
					>::reference
get_tuple_element(tuple<Ts...>& t EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
{ 
	EXTL_STATIC_ASSERT(N < (tuple_elements_size<tuple<Ts...> >::value));
	return EXTL_NS_DETAIL(get_tuple_element_impl)<N>(t); 
}

/*!\brief Sets the element of tuple
 * 
 * \param N The sequence number of elements
 * \param Ts The elements type
 * \param t	tuple<Ts...>& 
 * \param e The new element
 *
 * \code
	tuple<int, void*, double> t(1, NULL, 1.5);
	set_tuple_element<0>(t, 10);
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k... Ts
		>
EXTL_INLINE 
void set_tuple_element(tuple<Ts...>& t
				,	typename_type_k tuple_element_traits<	N
														,	tuple<Ts...>
														>::param_type e 
				EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N)
				)
{
	EXTL_STATIC_ASSERT(N < (tuple_elements_size<tuple<Ts...> >::value));
	get_tuple_element<N>(t) = e;
}

/*!\brief tuple class
 * 
 * \ingroup extl_group_container
 */
template<typename_param_k... Ts> 
class tuple 
	: public EXTL_NS_DETAIL(tuple_impl)<0, Ts...>
{
	/// \name Types
	/// @{
	public:
		typedef EXTL_NS_DETAIL(tuple_impl)<0, Ts...>				base_type;
		typedef tuple												class_type;
		typedef e_size_t											size_type;
	/// @}

	/// \name Constructor
	/// @{
	public:
		tuple()
			: base_type()
		{}
		explicit_k tuple(typename_type_k call_traits<Ts>::param_type... ts)
			: base_type(ts...)
		{}
		tuple(class_type const& rhs)
			: base_type(rhs)
		{}

	/// @}

	/// \name Accessors nad Mutators
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

		static size_type size()	
		{
			return (tuple_elements_size<class_type>::value);
		}

	#ifdef EXTL_MEMBER_TEMPLATE_FUNCTION_SUPPORT
		template <e_size_t N>
		typename_type_ret_k 
		tuple_element_traits<	N
							,	class_type
							>::reference 
		get(EXTL_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
		{
			EXTL_STATIC_ASSERT(N < (tuple_elements_size<class_type>::value));
			return get_tuple_element<N>(*this);
		}

		template <e_size_t N>
		typename_type_ret_k 
		tuple_element_traits<	N
							,	class_type
							>::const_reference 
		get(EXTL_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N)) const
		{
			EXTL_STATIC_ASSERT(N < (tuple_elements_size<class_type>::value));
			return get_tuple_element<N>(*this);
		}

		template <e_size_t N>
		void set(typename_type_ret_k 
				tuple_element_traits<	N
									,	class_type
									>::param_type e 
				EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
		{
			EXTL_STATIC_ASSERT(N < (tuple_elements_size<class_type>::value));
			set_tuple_element<N>(*this, e);
		}
	#endif
	/// @}
};

EXTL_TEMPLATE_SPECIALISATION
class tuple<>{};

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<typename_param_k... Ts> 
EXTL_INLINE void swap(tuple<Ts...> &lhs, tuple<Ts...> &rhs)
{
	lhs.swap(rhs);
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

template<typename_param_k... Ts> 
EXTL_INLINE void swap(EXTL_NS(tuple)<Ts...>& lhs, EXTL_NS(tuple)<Ts...>& rhs)
{
    lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_CONTAINER_DETAIL_TUPLE_IMPL_0x_H */
/* //////////////////////////////////////////////////////////////////// */
