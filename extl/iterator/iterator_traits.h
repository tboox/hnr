/* ///////////////////////////////////////////////////////////////////////
 * File:		iterator_traits.h		
 *
 * Created:		08.04.04				
 * Updated:		08.04.15	
 *
 * Brief: Iterator traits
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_ITERATOR_TRAITS_H
#define EXTL_ITERATOR_ITERATOR_TRAITS_H

/*!\file iterator_traits.h
 * \brief iterator_traits class
 */
#ifndef __cplusplus
#	error iterator_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "iterator_category.h"

#ifdef EXTL_TYPE_TRAITS_IS_PTR_SUPPORT
#	include "../type/traits/is_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CONST_SUPPORT
#	include "../type/traits/is_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_REF_SUPPORT
#	include "../type/traits/is_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_PTR_SUPPORT
#	include "../type/traits/remove_ptr.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_CV_SUPPORT
#	include "../type/traits/remove_cv.h"
#endif

#ifdef EXTL_TYPE_TRAITS_REMOVE_REF_SUPPORT
#	include "../type/traits/remove_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_REF_SUPPORT
#	include "../type/traits/add_ref.h"
#endif

#ifdef EXTL_TYPE_TRAITS_ADD_CONST_SUPPORT
#	include "../type/traits/add_const.h"
#endif

#ifdef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
#	include "../type/traits/is_convertible.h"
#endif

#ifdef EXTL_MPL_IF_SUPPORT
#	include "../mpl/if_.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Micros
 */
#ifdef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT

#define	EXTL_ITERATOR_MUST_BE_INPUT(it)			EXTL_STATIC_ASSERT(EXTL_NS(xtl_iterator_traits)<it>::is_input_iterator)
#define	EXTL_ITERATOR_MUST_BE_OUTPUT(it)		//EXTL_STATIC_ASSERT(EXTL_NS(xtl_iterator_traits)<it>::is_output_iterator)
#define	EXTL_ITERATOR_MUST_BE_FORWARD(it)		EXTL_STATIC_ASSERT(EXTL_NS(xtl_iterator_traits)<it>::is_forward_iterator)
#define	EXTL_ITERATOR_MUST_BE_BIDIRECTIONAL(it)	EXTL_STATIC_ASSERT(EXTL_NS(xtl_iterator_traits)<it>::is_bidirectional_iterator)
#define	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(it)	EXTL_STATIC_ASSERT(EXTL_NS(xtl_iterator_traits)<it>::is_random_access_iterator)

#else

#define	EXTL_ITERATOR_MUST_BE_INPUT(it)			
#define	EXTL_ITERATOR_MUST_BE_OUTPUT(it)		
#define	EXTL_ITERATOR_MUST_BE_FORWARD(it)		
#define	EXTL_ITERATOR_MUST_BE_BIDIRECTIONAL(it)	
#define	EXTL_ITERATOR_MUST_BE_RANDOM_ACCESS(it)	

#endif
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

#ifdef EXTL_ITERATOR_RAW_POINTER_ITERATOR_TRAITS_SUPPORT

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_BEGIN_NAMESPACE 
/* xtl_iterator_traits_selector */
template<e_bool_t is_pointer>
struct xtl_iterator_traits_selector
{
	template<typename_param_k It>
	struct result
	{
		typedef It													iterator_type;
		typedef typename_type_k iterator_type::iterator_category	iterator_category;
		typedef typename_type_k iterator_type::value_type			value_type;
		typedef typename_type_k iterator_type::difference_type		difference_type;
		typedef typename_type_k iterator_type::pointer				pointer;
		typedef typename_type_k iterator_type::reference			reference;

		typedef typename_type_k EXTL_NS_MPL(if_)<	(is_const<pointer>::value)
												,	pointer
												,	typename_type_k add_const<pointer>::type
												>::type				const_pointer;

		typedef typename_type_k EXTL_NS_MPL(if_)<	(is_const<reference>::value)
												,	reference
												,	typename_type_k add_const<reference>::type
												>::type				const_reference;
	};
};

/* raw pointer traits */
EXTL_TEMPLATE_SPECIALISATION
struct xtl_iterator_traits_selector<e_true_v>
{
	template<typename_param_k It>
	struct result
	{
		typedef It													iterator_type;
		typedef std_random_access_iterator_tag						iterator_category;
		typedef iterator_type										pointer;

		/* T const vloatile* ==> T const vloatile */
		typedef typename_type_k remove_ptr<pointer>::type			reduced_ptr_type;

		/* T const vloatile* ==> T */
		typedef typename_type_k remove_ref	<	typename_type_k remove_cv< reduced_ptr_type >::type
											>::type					value_type;

		typedef e_ptrdiff_t											difference_type;
		
		/* T const vloatile* ==> T const vloatile&, T* ==> T& */
		typedef typename_type_k EXTL_NS_MPL(if_)<	(is_ref< reduced_ptr_type >::value)
												,	reduced_ptr_type
												,	typename_type_k add_ref<reduced_ptr_type>::type
												>::type				reference;

		
		/* T const vloatile* ==> T const vloatile*, T* ==> T const* */
		typedef typename_type_k EXTL_NS_MPL(if_)<	(is_const< pointer >::value)
												,	pointer
												,	typename_type_k add_const<pointer>::type
												>::type				const_pointer;

		/* T const vloatile* ==> T const vloatile&, T* ==> T const& */
		typedef typename_type_k EXTL_NS_MPL(if_)<	(is_const< reference >::value)
												,	reference
												,	typename_type_k add_const<reference>::type
												>::type				const_reference;
	};
};

template<typename_param_k It>
struct xtl_iterator_traits_impl
	: public xtl_iterator_traits_selector< (is_ptr<It>::value) >::template_qual_k result<It>
{
};

/* ///////////////////////////////////////////////////////////////////////
 * namespace extl::detail 
 */
EXTL_DETAIL_END_NAMESPACE 

/*!\brief xtl_iterator_traits
 * 
 * \param It The iterator type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k It>
struct xtl_iterator_traits
{
	/// \name Types
	/// @{
	private:
		typedef EXTL_NS_DETAIL(xtl_iterator_traits_impl)<It>					iterator_traits_impl_;
	public:
		typedef It																iterator_type;
		typedef typename_type_k iterator_traits_impl_::iterator_category		iterator_category;
		typedef typename_type_k iterator_traits_impl_::value_type				value_type;
		typedef typename_type_k iterator_traits_impl_::difference_type			difference_type;
		typedef typename_type_k iterator_traits_impl_::pointer					pointer;
		typedef typename_type_k iterator_traits_impl_::reference				reference;
		
		typedef typename_type_k iterator_traits_impl_::const_pointer			const_pointer;
		typedef typename_type_k iterator_traits_impl_::const_reference			const_reference;
	/// @}

	/// \name Traits
	/// @{
	public:
		// note: std_output_iterator_tag is not a base class of all iterators
	#ifdef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_input_iterator = (is_convertible<iterator_category, std_input_iterator_tag>::value));
		//EXTL_STATIC_MEMBER_CONST(e_bool_t, is_output_iterator = (is_convertible<iterator_category, std_output_iterator_tag>::value));
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_forward_iterator = (is_convertible<iterator_category, std_forward_iterator_tag>::value));
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_bidirectional_iterator = (is_convertible<iterator_category, std_bidirectional_iterator_tag>::value));
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_random_access_iterator = (is_convertible<iterator_category, std_random_access_iterator_tag>::value));
	#endif	
	/// @}
};
#else

/*!\brief xtl_iterator_traits
 * 
 * \param It The interator type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k It>
struct xtl_iterator_traits
{
	/// \name Types
	/// @{
	public:
		typedef It													iterator_type;
		typedef typename_type_k iterator_type::iterator_category	iterator_category;
		typedef typename_type_k iterator_type::value_type			value_type;
		typedef typename_type_k iterator_type::difference_type		difference_type;
		typedef typename_type_k iterator_type::pointer				pointer;
		typedef typename_type_k iterator_type::reference			reference;

		typedef pointer												const_pointer;
		typedef reference											const_reference;
	/// @}

	/// \name Traits
	/// @{
	public:
	#ifdef EXTL_TYPE_TRAITS_IS_CONVERTIBLE_SUPPORT
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_input_iterator = (is_convertible<iterator_category, std_input_iterator_tag>::value));
		//EXTL_STATIC_MEMBER_CONST(e_bool_t, is_output_iterator = (is_convertible<iterator_category, std_output_iterator_tag>::value));
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_forward_iterator = (is_convertible<iterator_category, std_forward_iterator_tag>::value));
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_bidirectional_iterator = (is_convertible<iterator_category, std_bidirectional_iterator_tag>::value));
		EXTL_STATIC_MEMBER_CONST(e_bool_t, is_random_access_iterator = (is_convertible<iterator_category, std_random_access_iterator_tag>::value));
	#endif
	/// @}
};

#endif /* EXTL_ITERATOR_RAW_POINTER_ITERATOR_TRAITS_SUPPORT */

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_ITERATOR_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
