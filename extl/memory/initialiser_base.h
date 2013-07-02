/* ///////////////////////////////////////////////////////////////////////
 * File:		initialiser_base.h		
 *
 * Created:		08.07.30				
 * Updated:		08.07.30
 *
 * Brief: initialiser_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_INITIALISER_BASE_H
#define EXTL_MEMORY_INITIALISER_BASE_H

/*!\file initialiser_base.h
 * \brief initialiser_base class
 */
#ifndef __cplusplus
#	error initialiser_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief initialiser_base class
 *
 * \param D The derived type
 * \param T The value type
 * 
 * \ingroup extl_group_memory
 */
template<	typename_param_k D
		,	typename_param_k T
		>
class initialiser_base
{
	/// \name Types
	/// @{
	public:
		typedef D															derived_type;
		typedef initialiser_base											class_type;
		typedef T															value_type;
		typedef T*															pointer;
		typedef T const*													const_pointer;
		typedef T&															reference;
		typedef T const&													const_reference;
		typedef e_size_t													size_type;
	/// @}

	/// \name Construct and Destruct
	/// @{
	public:
		void construct(pointer p)
		{
			EXTL_ASSERT(NULL != p);
			derive().do_construct(p);
		}
		void construct(pointer p, const_reference value)
		{
			EXTL_ASSERT(NULL != p);
			derive().do_construct(p, value);
		}
		void construct_n(pointer p, size_type n)
		{
			EXTL_ASSERT(NULL != p);
			for (pointer pv = p; pv != p + n; ++pv)
				derive().construct(pv);
		}
		void construct_n(pointer p, size_type n, const_reference value)
		{
			EXTL_ASSERT(NULL != p);
			for (pointer pv = p; pv != p + n; ++pv)
				derive().construct(pv, value);
		}
		void destruct(pointer p)
		{
			EXTL_ASSERT(NULL != p);
			derive().do_destruct(p);
		}
		void destruct_n(pointer p, size_type n)
		{
			/* note: reversely destruct
			 *
				struct object1
				{
					object1()
					{
						new object2;
					}
				};
				new object1;
			 * 
			 * construct: object1 => object2
			 * destruct: object2 => object1
			 */
			for (T* pv = p + n - 1; pv != p - 1; --pv)
				derive().destruct(pv);
		}
	/// @}

	private:
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}

};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_INITIALISER_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
