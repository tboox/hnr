/* ///////////////////////////////////////////////////////////////////////
 * File:		pointer_iterator.h		
 *
 * Created:		08.04.04					
 * Updated:		08.11.14
 *
 * Brief: Pointer iterator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_POINTER_ITERATOR_H
#define EXTL_ITERATOR_POINTER_ITERATOR_H

/*!\file pointer_iterator.h
 * \brief pointer_iterator class
 *
 * Use pointer_iterator as much as possible rather than raw pointer, 
 * because xtl_iterator_traits can not be specialization to raw pointer by some compilers.
 *
 */
#ifndef __cplusplus
#	error pointer_iterator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "random_access_iterator_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief const_pointer_iterator class
 *
 * \param Val The value type of the raw pointer
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k Val>
class const_pointer_iterator
	: public const_random_access_iterator_base	<	const_pointer_iterator<Val>
												,	Val
												,	e_ptrdiff_t
												>
{
	private:
		typedef const_random_access_iterator_base	<	const_pointer_iterator<Val>
													,	Val
													,	e_ptrdiff_t
													>									base_type;
		typedef base_type																iterator_base_type;

	/// \name Types
	/// @{
	public:
		typedef const_pointer_iterator													class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k base_type::bool_type									bool_type;
	/// @}
	
	/// \name Members
	/// @{
	protected:
		const_pointer																	m_current;
	/// @}

	/// \name Constructors
	/// @{
	public:
		const_pointer_iterator() 
			: m_current(NULL)
		{}
		explicit_k const_pointer_iterator(const_pointer p) 
			: m_current(p) 
		{}
		const_pointer_iterator(class_type const& it) 
			: m_current(it.current()) 
		{}
	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k Val2>
		explicit_k const_pointer_iterator(const_pointer_iterator<Val2> const& it) 
			: m_current(it.current()) 
		{}
	#endif
	/// @}

	/// \name Accessors
	/// @{
	public:
		const_pointer current() const	{ return m_current;	}
	/// @}

	/// \name Operators
	/// @{
	public:
		void do_increase()
		{
			++m_current;
		}
		void do_decrease()
		{
			--m_current;
		}
		void do_inc_offset(difference_type offset)
		{
			m_current += offset;
		}
		class_type do_inc_offset_copy(difference_type offset) const
		{
			return (class_type(m_current + offset));
		}
		void do_dec_offset(difference_type offset)
		{	
			m_current -= offset;
		}
		class_type do_dec_offset_copy(difference_type offset) const
		{	
			return (class_type(current() - offset));
		}
		difference_type do_offset(class_type const& rhs) const
		{
			return (current() - rhs.current());
		}
		const_reference do_dereference() const
		{
			return (*current());
		}
		bool_type do_less_than(class_type const& rhs) const
		{
			return (current() < rhs.current());
		}
		bool_type do_greater_than(class_type const& rhs) const
		{
			return (current() > rhs.current());
		}
		bool_type do_equal(class_type const& rhs) const
		{
			return (current() == rhs.current());
		}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k Val2>
		difference_type do_offset(const_pointer_iterator<Val2> const& rhs) const
		{
			return (current() - rhs.current());
		}
		template<typename_param_k Val2>
		bool_type do_less_than(const_pointer_iterator<Val2> const& rhs) const
		{
			return (current() < rhs.current());
		}
		template<typename_param_k Val2>
		bool_type do_greater_than(const_pointer_iterator<Val2> const& rhs) const
		{
			return (current() > rhs.current());
		}
		template<typename_param_k Val2>
		bool_type do_equal(const_pointer_iterator<Val2> const& rhs) const
		{
			return (current() == rhs.current());
		}
	#endif
	/// @}
};

/// Shim: get pointer 
template<typename_param_k Val> 
inline typename_type_ret_k const_pointer_iterator<Val>::
const_pointer get_ptr(const_pointer_iterator<Val> const& it)
{
	return it.current();
}

/*!\brief pointer_iterator class
 *
 * \param Val The value type of the raw pointer
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k Val>
class pointer_iterator
	: public random_access_iterator_base<	pointer_iterator<Val>
										,	const_pointer_iterator<Val>	
										,	Val
										,	e_ptrdiff_t
										>
{
	private:
		typedef random_access_iterator_base	<	pointer_iterator<Val>
											,	const_pointer_iterator<Val>	
											,	Val
											,	e_ptrdiff_t
											>											base_type;
		typedef const_pointer_iterator<Val>												const_iterator_type;
		typedef base_type																iterator_base_type;
	/// \name Types
	/// @{
	public:
		typedef pointer_iterator														class_type;
		typedef typename_type_k base_type::bool_type									bool_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		pointer_iterator() 
			: base_type()
		{}
		explicit_k pointer_iterator(const_pointer p) 
			: base_type(const_iterator_type(p)) 
		{}
		pointer_iterator(class_type const& it) 
			: base_type(it) 
		{}
		// const_pointer_iterator can be explicitly converted to pointer_iterator
		explicit_k pointer_iterator(const_iterator_type const& it) 
			: base_type(it) 
		{}
	/// @}


};

/// Shim: get pointer 
template<typename_param_k Val> 
inline typename_type_ret_k pointer_iterator<Val>::
const_pointer get_ptr(pointer_iterator<Val> const& it)
{
	return it.current();
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_POINTER_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
