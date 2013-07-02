/* ///////////////////////////////////////////////////////////////////////
 * File:		n_types.h		
 *
 * Created:		08.03.17				
 * Updated:		08.07.30
 *
 * Brief: n_types class - for function overload determination
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_TYPE_N_TYPES_H
#define EXTL_TYPE_N_TYPES_H

/*!\file n_types.h
 * \brief n_types class - logical operation 
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h"
#include "../utility/static_assert.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_BEGIN_NAMESPACE 

typedef struct { e_byte_t padding[1];	}    one_type;
typedef struct { one_type padding[2];	}    two_type;
typedef struct { one_type padding[3];	}    three_type;
typedef struct { one_type padding[4];	}    four_type;
typedef struct { one_type padding[5];	}    five_type;
typedef struct { one_type padding[6];	}    six_type;
typedef struct { one_type padding[7];	}    seven_type;
typedef struct { one_type padding[8];	}    eight_type;
typedef struct { one_type padding[9];	}    nine_type;
typedef struct { one_type padding[10];	}    ten_type;

#ifdef	EXTL_TYPE_SIZE_TEST_ENABLE
EXTL_INLINE void n_types_size_checker()
{
	EXTL_STATIC_ASSERT(sizeof(one_type) < sizeof(two_type));
	EXTL_STATIC_ASSERT(sizeof(two_type) < sizeof(three_type));
	EXTL_STATIC_ASSERT(sizeof(three_type) < sizeof(four_type));
	EXTL_STATIC_ASSERT(sizeof(four_type) < sizeof(five_type));
	EXTL_STATIC_ASSERT(sizeof(five_type) < sizeof(six_type));
	EXTL_STATIC_ASSERT(sizeof(six_type) < sizeof(seven_type));
	EXTL_STATIC_ASSERT(sizeof(seven_type) < sizeof(eight_type));
	EXTL_STATIC_ASSERT(sizeof(eight_type) < sizeof(nine_type));
	EXTL_STATIC_ASSERT(sizeof(nine_type) < sizeof(ten_type));
}
#endif


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_TYPE_N_TYPES_H */
/* //////////////////////////////////////////////////////////////////// */
