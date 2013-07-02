/* ///////////////////////////////////////////////////////////////////////
 * File:		iterator_base.h		
 *
 * Created:		08.04.04				
 * Updated:		08.11.14
 *
 * Brief: iterator_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_ITERATOR_BASE_H
#define EXTL_ITERATOR_ITERATOR_BASE_H

/*!\file iterator_base.h
 * \brief iterator_base class
 */
#ifndef __cplusplus
#	error iterator_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief const_iterator_base
 *
 * \param Cat The iterator category
 * \param Val The value type
 * \param Diff The distance type
 *
 * \ingroup extl_group_iterator
 */
template<	typename_param_k Cat	
		,	typename_param_k Val	
		,	typename_param_k Diff	
        >
struct const_iterator_base
{
	/// \name STL Types	
	/// @{
	public:
		typedef Cat														iterator_category;
		typedef Val														value_type;
		typedef Diff													difference_type;
		typedef value_type const*										pointer;
		typedef value_type const&										reference;
	/// @}

	/// \name Custom Types
	/// @{
	public:
		typedef const_iterator_base										class_type;
		typedef value_type const*										const_pointer;
		typedef value_type const&										const_reference;
	/// @}

};

/*!\brief iterator_base
 *
 * \param Cat The iterator category
 * \param Val The value type
 * \param Diff The distance type
 *
 * \ingroup extl_group_iterator
 */
template<	typename_param_k Cat	
		,	typename_param_k Val	
		,	typename_param_k Diff	
        >
struct iterator_base
{
	/// \name STL Types	
	/// @{
	public:
		typedef Cat														iterator_category;
		typedef Val														value_type;
		typedef Diff													difference_type;
		typedef value_type*												pointer;
		typedef value_type&												reference;
	/// @}

	/// \name Custom Types
	/// @{
	public:
		typedef iterator_base											class_type;
		typedef value_type const*										const_pointer;
		typedef value_type const&										const_reference;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_ITERATOR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
