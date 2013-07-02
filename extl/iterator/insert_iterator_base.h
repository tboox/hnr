/* ///////////////////////////////////////////////////////////////////////
 * File:		insert_iterator_base.h		
 *
 * Created:		08.04.04				
 * Updated:		08.11.15	
 *
 * Brief: insert_iterator_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_INSERT_ITERATOR_BASE_H
#define EXTL_ITERATOR_INSERT_ITERATOR_BASE_H

/*!\file insert_iterator_base.h
 * \brief insert_iterator_base class
 */
#ifndef __cplusplus
#	error insert_iterator_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "iterator_base.h"
#include "iterator_category.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

/*!\brief back_insert_iterator_base
 *
 * \param C The container type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k C> 
struct back_insert_iterator_base
	: public iterator_base<std_output_iterator_tag, e_null_t, e_null_t>
{
	private:
		typedef iterator_base<std_output_iterator_tag, e_null_t, e_null_t>			base_type;

	/// \name Types
	/// @{
	public:
		typedef back_insert_iterator_base											class_type;
		typedef C																	container_type;
		typedef typename_type_k container_type::value_type							value_type;
	/// @}
	
	/// \name Members
	/// @{
	private:
		container_type&																container;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		explicit_k back_insert_iterator_base(container_type& c)
			: container(c) 
		{}
	/// @}
	
	/// \name Methods
	/// @{
	public:
		class_type& operator =(const value_type& value)
		{
			container.push_back(value);
			return (*this); 
		}
		class_type& operator *()
		{
			return (*this); 
		}
		class_type& operator ++()
		{
			return (*this); 
		}
		class_type operator ++(int)
		{
			return (*this); 
		}
	/// @}
};
/*!\brief extl_back_inserter
 *
 * \param C The container type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k C> 
inline back_insert_iterator_base<C> extl_back_inserter(C& c)
{
	return (back_insert_iterator_base<C>(c)); 
}

/*!\brief front_insert_iterator_base
 *
 * \param C The container type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k C> 
struct front_insert_iterator_base
	: public iterator_base<std_output_iterator_tag, e_null_t, e_null_t>
{
	private:
		typedef iterator_base<std_output_iterator_tag, e_null_t, e_null_t>			base_type;

	/// \name Types
	/// @{
	public:
		typedef front_insert_iterator_base											class_type;
		typedef C																	container_type;
		typedef typename_type_k container_type::value_type							value_type;
	/// @}

	/// \name Members
	/// @{
	private:
		container_type&																container;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k front_insert_iterator_base(container_type& c)
			: container(c) 
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		class_type& operator =(const value_type& value)
		{
			container.push_front(value);
			return (*this); 
		}
		class_type& operator *()
		{
			return (*this); 
		}
		class_type& operator ++()
		{
			return (*this); 
		}
		class_type operator ++(int)
		{
			return (*this); 
		}
	/// @}
};

/*!\brief extl_front_inserter
 *
 * \param C The container type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k C> 
inline front_insert_iterator_base<C> extl_front_inserter(C& c)
{
	return (front_insert_iterator_base<C>(c)); 
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_INSERT_ITERATOR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
