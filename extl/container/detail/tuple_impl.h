/* ///////////////////////////////////////////////////////////////////////
 * File:		tuple_impl.h		
 *
 * Created:		08.07.21		
 * Updated:		08.07.24
 *
 * Brief: tuple class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_TUPLE_IMPL_H
#define EXTL_CONTAINER_DETAIL_TUPLE_IMPL_H

#ifndef __cplusplus
#	error tuple_impl.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "tuple2.h"

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
template<	typename_param_k T0 = e_null_t
		,	typename_param_k T1 = e_null_t
		,	typename_param_k T2 = e_null_t
		,	typename_param_k T3 = e_null_t
		,	typename_param_k T4 = e_null_t
		,	typename_param_k T5 = e_null_t
		,	typename_param_k T6 = e_null_t
		,	typename_param_k T7 = e_null_t
		,	typename_param_k T8 = e_null_t
		,	typename_param_k T9 = e_null_t
		>
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

// tuple_element_traits implemention
#if defined(EXTL_TEMPLATE_PARTIAL_SPEC_SUPPORT) && \
	!EXTL_WORKAROUND_BORLAND(==, 0x551)

template<	e_size_t N
		,	typename_param_k T
		>
struct tuple_element_traits_impl
{
	private:
		typedef typename_type_k T::tail_type										next_type;
	public:
		typedef typename_type_k tuple_element_traits_impl<N - 1, next_type>::type	type;
};

template<typename_param_k T>
struct tuple_element_traits_impl<0, T>
{
	typedef typename_type_k T::head_type	type;
};
#else
template<e_size_t N>
struct tuple_element_traits_impl_helper
{
	template<typename_param_k T>
	struct result
	{
		private:
			typedef typename_type_k T::tail_type																		next_type;
		public:
			typedef typename_type_k tuple_element_traits_impl_helper<N - 1>::template_qual_k result<next_type>::type	type;
	};
};
EXTL_TEMPLATE_SPECIALISATION
struct tuple_element_traits_impl_helper<0>
{
	template<typename_param_k T>
	struct result
	{
		typedef typename_type_k T::head_type	type;
	};
};
template<	e_size_t N
		,	typename_param_k T
		>
struct tuple_element_traits_impl
	: tuple_element_traits_impl_helper<N>::template_qual_k result<T>
{
	
};
#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE

/*!\brief tuple_element_traits class
 * 
 * \param N The sequence number of elements
 * \param T The tuple<>/EXTL_NS_DETAIL(tuple2)<> type
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

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_BEGIN_NAMESPACE

// get_tuple_element implemention
template <e_size_t N>
struct get_tuple_element_impl
{
#if EXTL_WORKAROUND_MSVC(==, 1200)

	template<	typename_param_k T1
			,	typename_param_k T2
			>
	inline static typename_type_ret_k 
	tuple_element_traits<	N
						,	tuple2<T1, T2> 
						>::reference
	get(tuple2<T1, T2>& t)
	{
		return get_tuple_element_impl<N - 1>::get(t.get_tail());
	}

	template<	typename_param_k T1
			,	typename_param_k T2
			>
	inline static typename_type_ret_k 
	tuple_element_traits<	N
						,	tuple2<T1, T2> 
						>::const_reference
	get(tuple2<T1, T2> const& t)
	{
		return get_tuple_element_impl<N - 1>::get(t.get_tail());
	}

#else

	template<	typename_param_k RT
			,	typename_param_k T1
			,	typename_param_k T2
			>
	inline static RT get(tuple2<T1, T2> const& t)
	{
		return get_tuple_element_impl<N - 1>::template_qual_k get<RT>(t.get_tail());
	}

	template<	typename_param_k RT
			,	typename_param_k T1
			,	typename_param_k T2
			>
	inline static RT get(tuple2<T1, T2>& t)
	{
		return get_tuple_element_impl<N - 1>::template_qual_k get<RT>(t.get_tail());
	}
#endif
};
EXTL_TEMPLATE_SPECIALISATION
struct get_tuple_element_impl<0>
{
#if EXTL_WORKAROUND_MSVC(==, 1200)

	template<	typename_param_k T1
			,	typename_param_k T2
			>
	inline static typename_type_ret_k 
	tuple_element_traits<	0
						,	tuple2<T1, T2> 
						>::reference
	get(tuple2<T1, T2>& t)
	{
		return t.get_head();
	}

	template<	typename_param_k T1
			,	typename_param_k T2
			>
	inline static typename_type_ret_k 
	tuple_element_traits<	0
						,	tuple2<T1, T2> 
						>::const_reference
	get(tuple2<T1, T2> const& t)
	{
		return t.get_head();
	}
#else
	template<	typename_param_k RT
			,	typename_param_k T1
			,	typename_param_k T2
			>
	inline static RT get(tuple2<T1, T2> const& t)
	{
		return t.get_head();
	}

	template<	typename_param_k RT
			,	typename_param_k T1
			,	typename_param_k T2
			>
	inline static RT get(tuple2<T1, T2>& t)
	{
		return t.get_head();
	}
#endif
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace
 */
EXTL_DETAIL_END_NAMESPACE

#if EXTL_WORKAROUND_MSVC(==, 1200)
/*!\brief Gets the element of tuple/EXTL_NS_DETAIL(tuple2)
 * 
 * \param N The sequence number of elements
 * \param T1 The head type of EXTL_NS_DETAIL(tuple2)
 * \param T2 The tail type of EXTL_NS_DETAIL(tuple2)
 * \param t	EXTL_NS_DETAIL(tuple2)<T1, T2> const& 
 *
 * \code
	tuple<int, void*, double> t(1, NULL, 1.5);
	int a = get_tuple_element<0>(t);
	get_tuple_element<0>(t) = 10;
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE 
typename_type_ret_k 
tuple_element_traits<	N
					,	EXTL_NS_DETAIL(tuple2)<T1, T2> 
					>::reference 
get_tuple_element(EXTL_NS_DETAIL(tuple2)<T1, T2>& t EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
{
	return EXTL_NS_DETAIL(get_tuple_element_impl)<N>::get(t);
}
/*!\brief Gets the const element of tuple/EXTL_NS_DETAIL(tuple2)
 * 
 * \param N The sequence number of elements
 * \param T1 The head type of EXTL_NS_DETAIL(tuple2)
 * \param T2 The tail type of EXTL_NS_DETAIL(tuple2)
 * \param t	EXTL_NS_DETAIL(tuple2)<T1, T2> const& 
 *
 * \code
	tuple<int, void*, double> t(1, NULL, 1.5);
	int a = get_tuple_element<0>(t);
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE 
typename_type_ret_k 
tuple_element_traits<	N
					,	EXTL_NS_DETAIL(tuple2)<T1, T2> 
					>::const_reference 
get_tuple_element(EXTL_NS_DETAIL(tuple2)<T1, T2> const& t EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
{
	return EXTL_NS_DETAIL(get_tuple_element_impl)<N>::get(t);
}
#else
/*!\brief Gets the element of tuple/EXTL_NS_DETAIL(tuple2)
 * 
 * \param N The sequence number of elements
 * \param T1 The head type of EXTL_NS_DETAIL(tuple2)
 * \param T2 The tail type of EXTL_NS_DETAIL(tuple2)
 * \param t	EXTL_NS_DETAIL(tuple2)<T1, T2> const& 
 *
 * \code
	tuple<int, void*, double> t(1, NULL, 1.5);
	int a = get_tuple_element<0>(t);
	get_tuple_element<0>(t) = 10;
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE 
typename_type_ret_k 
tuple_element_traits<	N
					,	EXTL_NS_DETAIL(tuple2)<T1, T2> 
					>::reference 
get_tuple_element(EXTL_NS_DETAIL(tuple2)<T1, T2>& t EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
{
	EXTL_STATIC_ASSERT(N < (tuple_elements_size<EXTL_NS_DETAIL(tuple2)<T1, T2> >::value));
	return EXTL_NS_DETAIL(get_tuple_element_impl)<N>::template_qual_k 
												get	<	typename_type_k 
														tuple_element_traits<	N
																			,	EXTL_NS_DETAIL(tuple2)<T1, T2>
																			>::reference
													,	T1
													,	T2
													>(t);
}
/*!\brief Gets the const element of tuple/EXTL_NS_DETAIL(tuple2)
 * 
 * \param N The sequence number of elements
 * \param T1 The head type of EXTL_NS_DETAIL(tuple2)
 * \param T2 The tail type of EXTL_NS_DETAIL(tuple2)
 * \param t	EXTL_NS_DETAIL(tuple2)<T1, T2> const& 
 *
 * \code
	tuple<int, void*, double> t(1, NULL, 1.5);
	int a = get_tuple_element<0>(t);
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<	e_size_t N
		,	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE 
typename_type_ret_k 
tuple_element_traits<	N
					,	EXTL_NS_DETAIL(tuple2)<T1, T2> 
					>::const_reference 
get_tuple_element(EXTL_NS_DETAIL(tuple2)<T1, T2> const& t EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
{
	EXTL_STATIC_ASSERT(N < (tuple_elements_size<EXTL_NS_DETAIL(tuple2)<T1, T2> >::value));
	return EXTL_NS_DETAIL(get_tuple_element_impl)<N>::template_qual_k 
												get	<	typename_type_k 
														tuple_element_traits<	N
																			,	EXTL_NS_DETAIL(tuple2)<T1, T2> 
																			>::const_reference
													,	T1
													,	T2
													>(t);
}
#endif

/*!\brief Sets the element of tuple/EXTL_NS_DETAIL(tuple2)
 * 
 * \param N The sequence number of elements
 * \param T1 The head type of EXTL_NS_DETAIL(tuple2)
 * \param T2 The tail type of EXTL_NS_DETAIL(tuple2)
 * \param t	EXTL_NS_DETAIL(tuple2)<T1, T2>& 
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
		,	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE 
void set_tuple_element(	EXTL_NS_DETAIL(tuple2)<T1, T2>& t
				,	typename_type_k tuple_element_traits<	N
														,	EXTL_NS_DETAIL(tuple2)<T1, T2>
														>::param_type e 
				EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N)
				)
{
	EXTL_STATIC_ASSERT(N < (tuple_elements_size<EXTL_NS_DETAIL(tuple2)<T1, T2> >::value));
	get_tuple_element<N>(t) = e;
}

/*!\brief Gets the number of the elements of tuple/EXTL_NS_DETAIL(tuple2)
 * 
 * \param T The tuple/EXTL_NS_DETAIL(tuple2) type
 *
 * \code
	int num = tuple_elements_size< tuple<int, int> >::value;	// num == 2
 * \endcode
 *
 * \ingroup extl_group_container
 */
template<typename_param_k T>
struct tuple_elements_size 
{
	EXTL_STATIC_MEMBER_CONST(e_size_t, value = 1 + tuple_elements_size< typename_type_k T::tail_type >::value);
};

EXTL_TEMPLATE_SPECIALISATION
struct tuple_elements_size<tuple<> > 
{
	EXTL_STATIC_MEMBER_CONST(e_size_t, value = 0);
};

EXTL_TEMPLATE_SPECIALISATION
struct tuple_elements_size<e_null_t> 
{
	EXTL_STATIC_MEMBER_CONST(e_size_t, value = 0);
};

/*!\brief tuple class
 * 
 * \ingroup extl_group_container
 */
template<	typename_param_k T0
		,	typename_param_k T1 
		,	typename_param_k T2 
		,	typename_param_k T3 
		,	typename_param_k T4 
		,	typename_param_k T5
		,	typename_param_k T6
		,	typename_param_k T7
		,	typename_param_k T8
		,	typename_param_k T9
		>
class tuple 
	: public EXTL_NS_DETAIL(tuple2)	<	T0
									,	typename_type_k tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, e_null_t>::base_type
									>
{
	private:
		typedef typename_type_k call_traits<T0>::param_type			param0_type;
		typedef typename_type_k call_traits<T1>::param_type			param1_type;
		typedef typename_type_k call_traits<T2>::param_type			param2_type;
		typedef typename_type_k call_traits<T3>::param_type			param3_type;
		typedef typename_type_k call_traits<T4>::param_type			param4_type;
		typedef typename_type_k call_traits<T5>::param_type			param5_type;
		typedef typename_type_k call_traits<T6>::param_type			param6_type;
		typedef typename_type_k call_traits<T7>::param_type			param7_type;
		typedef typename_type_k call_traits<T8>::param_type			param8_type;
		typedef typename_type_k call_traits<T9>::param_type			param9_type;

	/// \name Types
	/// @{
	public:
		typedef EXTL_NS_DETAIL(tuple2)	<	T0
										,	typename_type_k 
											tuple	<	T1
													,	T2
													,	T3
													,	T4
													,	T5	
													,	T6
													,	T7
													,	T8
													,	T9
													,	e_null_t
													>::base_type
										>							base_type;
		typedef tuple												class_type;
		typedef e_size_t											size_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		tuple()
			: base_type()
			{}
		tuple(param0_type t0)
			: base_type(t0, cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1)
			: base_type(t0, t1, cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2)
			: base_type(t0, t1, t2, cnull(), cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2, param3_type t3)
			: base_type(t0, t1, t2, t3, cnull(), cnull(), cnull(), cnull(), cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2, param3_type t3, param4_type t4)
			: base_type(t0, t1, t2, t3, t4, cnull(), cnull(), cnull(), cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2, param3_type t3, param4_type t4, param5_type t5)
			: base_type(t0, t1, t2, t3, t4, t5, cnull(), cnull(), cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2, param3_type t3, param4_type t4, param5_type t5, param6_type t6)
			: base_type(t0, t1, t2, t3, t4, t5, t6, cnull(), cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2, param3_type t3, param4_type t4, param5_type t5, param6_type t6, param7_type t7)
			: base_type(t0, t1, t2, t3, t4, t5, t6, t7, cnull(), cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2, param3_type t3, param4_type t4, param5_type t5, param6_type t6, param7_type t7, param8_type t8)
			: base_type(t0, t1, t2, t3, t4, t5, t6, t7, t8, cnull())
			{}
		tuple(param0_type t0, param1_type t1, param2_type t2, param3_type t3, param4_type t4, param5_type t5, param6_type t6, param7_type t7, param8_type t8, param9_type t9)
			: base_type(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9)
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
			return (tuple_elements_size<base_type>::value);	
		}

	/* VC6.0 exists some bugs:
	 * bug1: t.get<0>() syntax error ')'
	 * work out bug1:
	 * declaration: get(int); call: t.get<0>(0);
	 *
	 * bug2: t.get<0>() and t.set<0>() cannot be called normally.
	 * t.get<0>() will be zero forever
	 */
	#if defined(EXTL_MEMBER_TEMPLATE_FUNCTION_SUPPORT) && \
			!EXTL_WORKAROUND_MSVC(==, 1200)	
		template <e_size_t N>
		typename_type_ret_k 
		tuple_element_traits<	N
							,	base_type
							>::reference 
		get(EXTL_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
		{
			EXTL_STATIC_ASSERT(N < (tuple_elements_size<base_type>::value));
			return get_tuple_element<N>(*this);
		}

		template <e_size_t N>
		typename_type_ret_k 
		tuple_element_traits<	N
							,	base_type
							>::const_reference 
		get(EXTL_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N)) const
		{
			EXTL_STATIC_ASSERT(N < (tuple_elements_size<base_type>::value));
			return get_tuple_element<N>(*this);
		}

		template <e_size_t N>
		void set(typename_type_ret_k 
				tuple_element_traits<	N
									,	base_type
									>::param_type e 
				EXTL_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(e_size_t, N))
		{
			EXTL_STATIC_ASSERT(N < (tuple_elements_size<base_type>::value));
			set_tuple_element<N>(*this, e);
		}
	#endif
	/// @}
};


EXTL_TEMPLATE_SPECIALISATION
class tuple<e_null_t, e_null_t, e_null_t, e_null_t, e_null_t, e_null_t, e_null_t, e_null_t, e_null_t, e_null_t>
{
	/// \name Types
	/// @{
	public:
		typedef e_null_t											base_type;
		typedef tuple												class_type;
		typedef e_size_t											size_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Make tuple
 */
EXTL_INLINE tuple<> make_tuple() 
{
  return tuple<>();
}

template<typename_param_k T0>
EXTL_INLINE tuple<T0> make_tuple(T0 const& t0) 
{
  return tuple<T0>(t0);
}

template<	typename_param_k T0
		,	typename_param_k T1
		>
EXTL_INLINE tuple<T0, T1> make_tuple(T0 const& t0, T1 const& t1) 
{
  return tuple<T0, T1>(t0, t1);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE tuple<T0, T1, T2> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2) 
{
  return tuple<T0, T1, T2>(t0, t1, t2);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		,	typename_param_k T3
		>
EXTL_INLINE tuple<T0, T1, T2, T3> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3) 
{
  return tuple<T0, T1, T2, T3>(t0, t1, t2, t3);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		,	typename_param_k T3
		,	typename_param_k T4
		>
EXTL_INLINE tuple<T0, T1, T2, T3, T4> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4) 
{
  return tuple<T0, T1, T2, T3, T4>(t0, t1, t2, t3, t4);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		,	typename_param_k T3
		,	typename_param_k T4
		,	typename_param_k T5
		>
EXTL_INLINE tuple<T0, T1, T2, T3, T4, T5> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5) 
{
  return tuple<T0, T1, T2, T3, T4, T5>(t0, t1, t2, t3, t4, t5);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		,	typename_param_k T3
		,	typename_param_k T4
		,	typename_param_k T5
		,	typename_param_k T6
		>
EXTL_INLINE tuple<T0, T1, T2, T3, T4, T5, T6> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6) 
{
  return tuple<T0, T1, T2, T3, T4, T5, T6>(t0, t1, t2, t3, t4, t5, t6);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		,	typename_param_k T3
		,	typename_param_k T4
		,	typename_param_k T5
		,	typename_param_k T6
		,	typename_param_k T7
		>
EXTL_INLINE tuple<T0, T1, T2, T3, T4, T5, T6, T7> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7) 
{
  return tuple<T0, T1, T2, T3, T4, T5, T6, T7>(t0, t1, t2, t3, t4, t5, t6, t7);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		,	typename_param_k T3
		,	typename_param_k T4
		,	typename_param_k T5
		,	typename_param_k T6
		,	typename_param_k T7
		,	typename_param_k T8
		>
EXTL_INLINE tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8) 
{
  return tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>(t0, t1, t2, t3, t4, t5, t6, t7, t8);
}

template<	typename_param_k T0
		,	typename_param_k T1
		,	typename_param_k T2
		,	typename_param_k T3
		,	typename_param_k T4
		,	typename_param_k T5
		,	typename_param_k T6
		,	typename_param_k T7
		,	typename_param_k T8
		,	typename_param_k T9
		>
EXTL_INLINE tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> make_tuple(T0 const& t0, T1 const& t1, T2 const& t2, T3 const& t3, T4 const& t4, T5 const& t5, T6 const& t6, T7 const& t7, T8 const& t8, T9 const& t9) 
{
  return tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE void swap(EXTL_NS_DETAIL(tuple2)<T1, T2> &lhs, EXTL_NS_DETAIL(tuple2)<T1, T2> &rhs)
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

template<	typename_param_k T1
		,	typename_param_k T2
		>
EXTL_INLINE void swap(EXTL_NS(EXTL_NS_DETAIL(tuple2))<T1, T2>& lhs, EXTL_NS(EXTL_NS_DETAIL(tuple2))<T1, T2>& rhs)
{
    lhs.swap(rhs);
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /*  EXTL_CONTAINER_DETAIL_TUPLE_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
