/* ///////////////////////////////////////////////////////////////////////
 * File:		pod_initialiser.h		
 *
 * Created:		08.07.30				
 * Updated:		08.07.30
 *
 * Brief: pod_initialiser class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_POD_INITIALISER_H
#define EXTL_MEMORY_POD_INITIALISER_H

/*!\file pod_initialiser.h
 * \brief pod_initialiser class
 */
#ifndef __cplusplus
#	error pod_initialiser.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "initialiser_base.h"

#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
#	include "../type/traits/is_pod.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief pod_initialiser class
 *
 * \param T The value type
 * 
 * \ingroup extl_group_memory
 */
template<typename_param_k T>
class pod_initialiser
	: public initialiser_base<pod_initialiser<T>, T>
{
	/// \name Types
	/// @{
	public:
		typedef initialiser_base<pod_initialiser<T>, T>					base_type;
		typedef pod_initialiser											class_type;
		typedef typename_type_k base_type::value_type					value_type;
		typedef typename_type_k base_type::pointer						pointer;
		typedef typename_type_k base_type::const_pointer				const_pointer;
		typedef typename_type_k base_type::reference					reference;
		typedef typename_type_k base_type::const_reference				const_reference;
		typedef typename_type_k base_type::size_type					size_type;
	/// @}

	public:
		~pod_initialiser()
		{
		#ifdef EXTL_TYPE_TRAITS_IS_POD_SUPPORT
			EXTL_MUST_BE_POD(value_type);
		#endif
		}

	/// \name Construct and Destruct
	/// @{
	public:
		void do_construct(pointer /*p*/)
		{
		}
		void do_construct(pointer p, const_reference value)
		{
			*p = value;
		}
		void do_destruct(pointer /*p*/)
		{
		}
		void construct_n(pointer /*p*/, size_type /*n*/)
		{
		}
		void construct_n(pointer p, size_type n, const_reference value)
		{
			EXTL_ASSERT(NULL != p);
			pod_copy_n(p, &value, n);
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_POD_INITIALISER_H */
/* //////////////////////////////////////////////////////////////////// */
