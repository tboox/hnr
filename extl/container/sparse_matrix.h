/* ///////////////////////////////////////////////////////////////////////
 * File:		sparse_matrix.h		
 *
 * Created:		08.12.07			
 * Updated:		08.12.07
 *
 * Brief:		sparse_matrix class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_SPARSE_MATRIX_H
#define EXTL_CONTAINER_SPARSE_MATRIX_H

/*!\file sparse_matrix.h
 * \brief sparse_matrix class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "sparse_matrix_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE


/*!\brief: sparse_matrix class
 *
 * \param Val The element type
 *
 * \ingroup extl_group_container
 */
template<typename_param_k Val>
class sparse_matrix
	: public sparse_matrix_base	<	sparse_matrix<Val>
								,	Val
								>
{
	private:
		typedef sparse_matrix_base	<	sparse_matrix<Val>
									,	Val
									>												base_type;

	/// \name Types
	/// @{
	public:
		typedef sparse_matrix														class_type;
		typedef typename_type_k base_type::buffer_type								buffer_type;
		typedef typename_type_k base_type::allocator_type							allocator_type;
		typedef typename_type_k base_type::value_type								value_type;
		typedef typename_type_k base_type::pointer									pointer;
		typedef typename_type_k base_type::const_pointer							const_pointer;
		typedef typename_type_k base_type::reference								reference;
		typedef typename_type_k base_type::const_reference							const_reference;
		typedef typename_type_k base_type::size_type								size_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k base_type::difference_type							difference_type;
		typedef	typename_type_k base_type::int_type									int_type;	
		typedef typename_type_k base_type::index_type								index_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		sparse_matrix()
			: base_type()
		{
		}
		sparse_matrix(class_type const& rhs)
			: base_type(rhs)
		{
		}
		sparse_matrix(index_type d0, index_type d1)
			: base_type(d0, d1)
		{
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& rhs)	{ return base_type::operator=(rhs);		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_SPARSE_MATRIX_H */
/* //////////////////////////////////////////////////////////////////// */
