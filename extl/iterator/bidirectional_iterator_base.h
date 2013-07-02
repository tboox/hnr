/* ///////////////////////////////////////////////////////////////////////
 * File:		bidirectional_iterator_base.h		
 *
 * Created:		08.12.05	
 * Updated:		08.12.05
 *
 * Brief:		bidirectional_iterator_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_BIDIRECTIONAL_ITERATOR_BASE_H
#define EXTL_ITERATOR_BIDIRECTIONAL_ITERATOR_BASE_H


/*!\file bidirectional_iterator_base.h
 * \brief bidirectional_iterator_base class
 *
 */
#ifndef __cplusplus
#	error bidirectional_iterator_base.h need be supported by c++.
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

/*!\brief const_bidirectional_iterator_base
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
class const_bidirectional_iterator_base
	: public const_iterator_base<	std_bidirectional_iterator_tag
								,	Val
								,	Diff
								>
{
	private:
		typedef const_iterator_base	<	std_bidirectional_iterator_tag
									,	Val
									,	Diff
									>													base_type;
		typedef base_type																iterator_base_type;
		typedef Dev																		derived_type;

	/// \name Types
	/// @{
	public:
		typedef const_bidirectional_iterator_base										class_type;
		typedef e_bool_t																bool_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
	/// @}

	/// \name Operators
	/// @{
	public:
		const_reference operator*() const
		{
			return derive().do_dereference();
		}
		const_pointer operator->() const
		{
			return (&*derive());
		}
		derived_type& operator++()
		{
			derive().do_increase();
			return derive();
		}
		derived_type operator++(int)
		{
			derived_type tmp = derive();
			++derive();
			return (tmp);
		}
		derived_type& operator--()
		{
			derive().do_decrease();
			return derive();
		}
		derived_type operator--(int)
		{
			derived_type tmp = derive();
			--derive();
			return (tmp);
		}
		bool_type operator==(derived_type const& rhs) const
		{
			return derive().do_equal(rhs);
		}
		bool_type operator!=(derived_type const& rhs) const
		{
			return !(derive() == rhs);
		}
	/// @}

	/// \name Helpers
	/// @{
	private:																							
		derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
	/// @}

};
/*!\brief bidirectional_iterator_base
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
class bidirectional_iterator_base
	: public iterator_base	<	std_bidirectional_iterator_tag
							,	Val
							,	Diff
							>
	, public CDev	// only for implicitly convertion
{
	private:
		typedef CDev																	const_iterator_type;
		typedef iterator_base	<	std_bidirectional_iterator_tag
								,	Val
								,	Diff
								>														iterator_base_type;
		typedef Dev																		derived_type;

	/// \name Types
	/// @{
	public:
		typedef bidirectional_iterator_base												class_type;
		typedef e_bool_t																bool_type;
		typedef typename_type_k iterator_base_type::iterator_category					iterator_category;
		typedef typename_type_k iterator_base_type::value_type							value_type;
		typedef typename_type_k iterator_base_type::reference							reference;
		typedef typename_type_k iterator_base_type::const_reference						const_reference;
		typedef typename_type_k iterator_base_type::pointer								pointer;
		typedef typename_type_k iterator_base_type::const_pointer						const_pointer;
		typedef typename_type_k iterator_base_type::difference_type						difference_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		bidirectional_iterator_base()
			: const_iterator_type()
		{
		}
		explicit_k bidirectional_iterator_base(const_iterator_type const& it)
			: const_iterator_type(it)
		{
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		reference operator*() const
		{
			return const_cast<reference>(const_iterator_type::operator*());
		}
		pointer operator->() const
		{
			return (&*derive());
		}
		derived_type& operator++()
		{
			const_iterator_type::operator++();
			return derive();
		}
		derived_type operator++(int)
		{
			derived_type tmp = derive();
			++derive();
			return (tmp);
		}
		derived_type& operator--()
		{
			const_iterator_type::operator--();
			return derive();
		}
		derived_type operator--(int)
		{
			derived_type tmp = derive();
			--derive();
			return (tmp);
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
 * ::extl namespace
 */
EXTL_END_NAMESPACE
/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_ITERATOR_BIDIRECTIONAL_ITERATOR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
