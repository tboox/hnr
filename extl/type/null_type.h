/* ///////////////////////////////////////////////////////////////////////
 * File:		null_type.h		
 *
 * Created:		08.07.16				
 * Updated:		08.07.16
 *
 * Brief: The null type - as type placeholder instead of void type
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_NULL_TYPE_H
#define EXTL_TYPE_NULL_TYPE_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 
#include "typedef.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

#ifdef __cplusplus

// forward declaration 
struct null_type;
EXTL_INLINE null_type const& cnull();

// null_type 
struct null_type
{
	private:
		// Prohibit generating an instance 
		null_type(){};
		// Prohibit copy constructor 
		null_type(null_type const&);
		// Prohibit assignment 
		null_type& operator =(null_type const&);

	public:
		/* Gets a const reference instance as ab placeholder 
		 * e.g.
		 * void func(null_type const& p = cnull());
		 */
		friend null_type const& cnull() 
		{
			/* a helper function to provide a static const null_type instance */
			static const null_type s_null_obj;
			return s_null_obj;
		}
};

// is_null_type traits
template < typename_param_k T >
struct is_null_type
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_false_v);
};

EXTL_TEMPLATE_SPECIALISATION
struct is_null_type<null_type>
{
	EXTL_STATIC_MEMBER_CONST(e_bool_t, value = e_true_v);
};

#else /* !__cplusplus */

typedef struct null_type_tag{}		null_type;
/* a helper function to provide a const null_type type temporary */
EXTL_INLINE const null_type cnull()	{ return null_type();	}

#endif /* __cplusplus */

/* e_null_t */
typedef null_type				e_null_t;

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_TYPE_NULL_TYPE_H */
/* //////////////////////////////////////////////////////////////////// */
