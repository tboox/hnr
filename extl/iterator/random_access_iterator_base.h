/* ///////////////////////////////////////////////////////////////////////
 * File:		random_access_iterator_base.h		
 *
 * Created:		08.12.06				
 * Updated:		08.12.06
 *
 * Brief:		random_access_iterator_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_RANDOM_ACCESS_ITERATOR_BASE_H
#define EXTL_ITERATOR_RANDOM_ACCESS_ITERATOR_BASE_H

/*!\file random_access_iterator_base.h
 * \brief random_access_iterator_base class
 *
 */
#ifndef __cplusplus
#	error random_access_iterator_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "iterator_base.h"
#include "iterator_traits.h"
#include "iterator_category.h"


/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief const_random_access_iterator_base
 *
 * \param Dev The derived type
 * \param Val The value type
 * \param Diff The distance type
 *
 * \ingroup extl_group_iterator
 */
template<	typename_param_k Dev
		,	typename_param_k Val
		,	typename_param_k Diff	
        >
class const_random_access_iterator_base
	: public const_iterator_base	<	std_random_access_iterator_tag
									,	Val
									,	Diff
									>
{
	private:
		typedef const_iterator_base	<	std_random_access_iterator_tag
									,	Val
									,	Diff
									>													base_type;
		typedef base_type																iterator_base_type;
		typedef Dev																		derived_type;

	/// \name Types
	/// @{
	public:
		typedef const_random_access_iterator_base										class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef e_bool_t																bool_type;
	/// @}

	/// \name Operators
	/// @{
	public:
		derived_type& operator ++()
		{
			derive().do_increase();
			return derive();
		}
		derived_type operator ++(int)
		{
			derived_type tmp = derive();
			++derive();
			return (tmp);
		}
		derived_type& operator --()
		{
			derive().do_decrease();
			return derive();
		}
		derived_type operator --(int)
		{
			derived_type tmp = derive();
			--derive();
			return (tmp);
		}
		derived_type& operator +=(difference_type offset)
		{	
			derive().do_inc_offset(offset);
			return derive();
		}
		derived_type operator +(difference_type offset) const
		{	
			return derive().do_inc_offset_copy(offset);
		}
		derived_type& operator -=(difference_type offset)
		{	
			derive().do_dec_offset(offset);
			return derive();
		}
		derived_type operator -(difference_type offset) const
		{	
			return derive().do_dec_offset_copy(offset);
		}
		difference_type operator -(derived_type const& rhs) const
		{
			return derive().do_offset(rhs);
		}
		const_reference operator*() const
		{
			return derive().do_dereference();
		}
		const_pointer operator->() const
		{
			return (&*derive());
		}
		const_reference operator[](difference_type offset) const
		{	
			return (*(derive() + offset));
		}
		bool_type operator <(derived_type const& rhs) const
		{
			return derive().do_less_than(rhs);
		}
		bool_type operator >=(derived_type const& rhs) const
		{
			return !(derive() < rhs);
		}
		bool_type operator >(derived_type const& rhs) const
		{
			return derive().do_greater_than(rhs);
		}
		bool_type operator <=(derived_type const& rhs) const
		{
			return !(derive() > rhs);
		}
		bool_type operator ==(derived_type const& rhs) const
		{
			return derive().do_equal(rhs);
		}
		bool_type operator !=(derived_type const& rhs) const
		{
			return !(derive() == rhs);
		}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template<	typename_param_k Dev2
				,	typename_param_k Val2
				,	typename_param_k Diff2	
				>
		difference_type operator -(const_random_access_iterator_base<Dev2, Val2, Diff2> const& rhs) const
		{
			return derive().do_offset(static_cast<Dev2 const&>(rhs));
		}
		template<	typename_param_k Dev2
				,	typename_param_k Val2
				,	typename_param_k Diff2	
				>
		bool_type operator <(const_random_access_iterator_base<Dev2, Val2, Diff2> const& rhs) const
		{
			return derive().do_less_than(static_cast<Dev2 const&>(rhs));
		}
		template<	typename_param_k Dev2
				,	typename_param_k Val2
				,	typename_param_k Diff2	
				>
		bool_type operator >=(const_random_access_iterator_base<Dev2, Val2, Diff2> const& rhs) const
		{
			return !(derive() < static_cast<Dev2 const&>(rhs));
		}
		template<	typename_param_k Dev2
				,	typename_param_k Val2
				,	typename_param_k Diff2	
				>
		bool_type operator >(const_random_access_iterator_base<Dev2, Val2, Diff2> const& rhs) const
		{
			return derive().do_greater_than(static_cast<Dev2 const&>(rhs));
		}
		template<	typename_param_k Dev2
				,	typename_param_k Val2
				,	typename_param_k Diff2	
				>
		bool_type operator <=(const_random_access_iterator_base<Dev2, Val2, Diff2> const& rhs) const
		{
			return !(derive() > static_cast<Dev2 const&>(rhs));
		}
		template<	typename_param_k Dev2
				,	typename_param_k Val2
				,	typename_param_k Diff2	
				>
		bool_type operator ==(const_random_access_iterator_base<Dev2, Val2, Diff2> const& rhs) const
		{
			return derive().do_equal(static_cast<Dev2 const&>(rhs));
		}
		template<	typename_param_k Dev2
				,	typename_param_k Val2
				,	typename_param_k Diff2	
				>
		bool_type operator !=(const_random_access_iterator_base<Dev2, Val2, Diff2> const& rhs) const
		{
			return !(derive() == static_cast<Dev2 const&>(rhs));
		}
	#endif
	/// @}

	/// \name Helpers
	/// @{
	private:																							
		derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * const_random_access_iterator_base implemention
 */
template<	typename_param_k Dev
		,	typename_param_k Val
		,	typename_param_k Diff	
        >
inline const_random_access_iterator_base<Dev, Val, Diff> operator +(Diff offset, const_random_access_iterator_base<Dev, Val, Diff> const& rhs)
{
	return (static_cast<Dev const&>(rhs) + offset);
}

/*!\brief random_access_iterator_base
 *
 * \param Dev The derived type
 * \param CDev The const derived type - for xxx_iterator(Dev) can be implicitly converted to const_xxx_iterator(CDev)
 * \param Val The value type
 * \param Diff The distance type
 *
 * \ingroup extl_group_iterator
 */
template<	typename_param_k Dev
		,	typename_param_k CDev
		,	typename_param_k Val
		,	typename_param_k Diff	
        >
class random_access_iterator_base
	: public iterator_base	<	std_random_access_iterator_tag
							,	Val
							,	Diff
							>
	, public CDev	// only for implicitly convertion
{
	private:
		typedef CDev																	const_iterator_type;
		typedef iterator_base	<	std_random_access_iterator_tag
								,	Val
								,	Diff
								>														base_type;
		typedef base_type																iterator_base_type;
		typedef Dev																		derived_type;

	/// \name Types
	/// @{
	public:
		typedef random_access_iterator_base												class_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef e_bool_t																bool_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		random_access_iterator_base()
			: const_iterator_type()
		{
		}
		explicit_k random_access_iterator_base(const_iterator_type const& it)
			: const_iterator_type(it)
		{
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		derived_type& operator ++()
		{
			const_iterator_type::operator++();
			return derive();
		}
		derived_type operator ++(int)
		{
			derived_type tmp = derive();
			++derive();
			return (tmp);
		}
		derived_type& operator --()
		{
			const_iterator_type::operator--();
			return derive();
		}
		derived_type operator --(int)
		{
			derived_type tmp = derive();
			--derive();
			return (tmp);
		}
		derived_type& operator +=(difference_type offset)
		{	
			const_iterator_type::operator+=(offset);
			return derive();
		}
		derived_type operator +(difference_type offset) const
		{	
			return derived_type(const_iterator_type::operator+(offset));
		}
		derived_type& operator -=(difference_type offset)
		{	
			const_iterator_type::operator-=(offset);
			return derive();
		}
		derived_type operator -(difference_type offset) const
		{	
			return derived_type(const_iterator_type::operator-(offset));
		}
		difference_type operator -(derived_type const& rhs) const
		{
			return const_iterator_type::operator-(rhs);
		}
		reference operator*() const
		{
			return const_cast<reference>(const_iterator_type::operator*());
		}
		pointer operator->() const
		{
			return (&*derive());
		}
		reference operator[](difference_type offset) const
		{	
			return const_cast<reference>(const_iterator_type::operator[](offset));
		}
	/// @}

	/// \name Helpers
	/// @{
	private:																							
		derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * const_random_access_iterator_base implemention
 */
template<	typename_param_k Dev
		,	typename_param_k CDev
		,	typename_param_k Val
		,	typename_param_k Diff	
        >
inline random_access_iterator_base<Dev, CDev, Val, Diff> operator +(Diff offset, random_access_iterator_base<Dev, CDev, Val, Diff> const& rhs)
{
	return (static_cast<Dev const&>(rhs) + offset);
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_RANDOM_ACCESS_ITERATOR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
