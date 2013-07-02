/* ///////////////////////////////////////////////////////////////////////
 * File:		reverse_iterator_base.h		
 *
 * Created:		08.04.04				
 * Updated:		08.11.15
 *
 * Brief: reverse_iterator_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_ITERATOR_REVERSE_ITERATOR_BASE_H
#define EXTL_ITERATOR_REVERSE_ITERATOR_BASE_H

/*!\file reverse_iterator_base.h
 * \brief reverse_iterator_base class
 */
#ifndef __cplusplus
#	error iterator_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "iterator_traits.h"
#include "iterator_base.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE 

// push warning: odd return type for operator-> 
#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER <= 1200)
#	pragma warning(push)
#	pragma warning(disable:4284) 
#endif

/*!\brief const_reverse_iterator_base
 *
 * \param It The iterator type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k It>
struct const_reverse_iterator_base
	: public const_iterator_base<	std_random_access_iterator_tag
								,	typename_type_k xtl_iterator_traits<It>::value_type
								,	typename_type_k xtl_iterator_traits<It>::difference_type
								>
{
	private:
		typedef const_iterator_base	<	std_random_access_iterator_tag
									,	typename_type_k xtl_iterator_traits<It>::value_type
									,	typename_type_k xtl_iterator_traits<It>::difference_type
									>												base_type;
		typedef base_type															iterator_base_type;

	/// \name Types
	/// @{
	public:
		typedef const_reverse_iterator_base											class_type;
		typedef It																	iterator_type;
		typedef typename_type_k iterator_base_type::iterator_category				iterator_category;
		typedef typename_type_k iterator_base_type::value_type						value_type;
		typedef typename_type_k iterator_base_type::reference						reference;
		typedef typename_type_k iterator_base_type::const_reference					const_reference;
		typedef typename_type_k iterator_base_type::pointer							pointer;
		typedef typename_type_k iterator_base_type::const_pointer					const_pointer;
		typedef typename_type_k iterator_base_type::difference_type					difference_type;
		typedef e_bool_t															bool_type;			
	/// @}	
	
	/// \name Members
	/// @{
	private:
		iterator_type																m_current;
	/// @}

	/// \name Constructors
	/// @{
	public:
		const_reverse_iterator_base() 
			: m_current() 
		{}
		explicit_k const_reverse_iterator_base(iterator_type const& it) 
			: m_current(it) 
		{}
		const_reverse_iterator_base(class_type const& it) 
			: m_current(it.current()) 
		{}

	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		explicit_k const_reverse_iterator_base(const_reverse_iterator_base<It2> const& it) 
			: m_current(it.current()) 
		{}
	#endif
	/// @}

	/// \name Methods
	/// @{
	public:
		iterator_type const& current() const
		{
			return m_current;
		}
		class_type& operator ++()
		{
			--m_current;
			return (*this);
		}
		class_type operator ++(int)
		{
			class_type tmp = *this;
			++(*this);
			return tmp;
		}
		class_type& operator --()
		{
			++m_current;
			return (*this);
		}
		class_type operator --(int)
		{
			class_type tmp = *this;
			--(*this);
			return tmp;
		}
		class_type& operator +=(difference_type offset)
		{	
			m_current -= offset;
			return (*this);
		}
		class_type operator +(difference_type offset) const
		{	
			return (class_type(m_current - offset));
		}
		class_type& operator -=(difference_type offset)
		{	
			m_current += offset;
			return (*this);
		}
		class_type operator -(difference_type offset) const
		{	
			return (class_type(current() + offset));
		}
		difference_type operator -(class_type const& rhs) const
		{
			return (rhs.current() - current());
		}
		const_reference operator *() const
		{
			// rbegin() ==> end() 
			iterator_type tmp = current();
			return (*--tmp);
		}
		const_pointer operator ->() const
		{
			return (&**this);
		}
		const_reference operator [](difference_type offset) const
		{	
			return (*(*this + offset));
		}

	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		difference_type operator -(const_reverse_iterator_base<It2> const& rhs) const
		{
			return (rhs.current() - current());
		}
		template<typename_param_k It2>
		bool_type operator <(const_reverse_iterator_base<It2> const& rhs) const
		{
			return (rhs.current() < current());
		}
		template<typename_param_k It2>
		bool_type operator >=(const_reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this) < rhs.current());
		}
		template<typename_param_k It2>
		bool_type operator >(const_reverse_iterator_base<It2> const& rhs) const
		{
			return (rhs.current() > current());
		}
		template<typename_param_k It2>
		bool_type operator <=(const_reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this) > rhs);
		}
		template<typename_param_k It2>
		bool_type operator ==(const_reverse_iterator_base<It2> const& rhs) const
		{
			return (current() == rhs.current());
		}
		template<typename_param_k It2>
		bool_type operator !=(const_reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this) == rhs);
		}
	#endif
		bool_type operator <(class_type const& rhs) const
		{
			return (rhs.current() < current());
		}
		bool_type operator >=(class_type const& rhs) const
		{
			return !((*this) < rhs);
		}
		bool_type operator >(class_type const& rhs) const
		{
			return (rhs.current() > current());
		}
		bool_type operator <=(class_type const& rhs) const
		{
			return !((*this) > rhs);
		}
		bool_type operator ==(class_type const& rhs) const
		{
			return (current() == rhs.current());
		}
		bool_type operator !=(class_type const& rhs) const
		{
			return !((*this) == rhs);
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * const_reverse_iterator_base implemention
 */
template<	typename_param_k It
		,	typename_param_k Diff 
		> 
inline const_reverse_iterator_base<It> operator +(Diff offset, const_reverse_iterator_base<It> const& rhs)
{
	return (rhs + offset);
}

/*!\brief reverse_iterator_base
 *
 * \param It The iterator type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k It>
struct reverse_iterator_base
	: public const_reverse_iterator_base<It>	// reverse_iterator can be implicitly converted to const_reverse_iterator 
	, public iterator_base	<	std_random_access_iterator_tag
							,	typename_type_k xtl_iterator_traits<It>::value_type
							,	typename_type_k xtl_iterator_traits<It>::difference_type
							>
{
	private:
		typedef const_reverse_iterator_base<It>										base_type;
		typedef iterator_base	<	std_random_access_iterator_tag
								,	typename_type_k xtl_iterator_traits<It>::value_type
								,	typename_type_k xtl_iterator_traits<It>::difference_type
								>													iterator_base_type;

	/// \name Types
	/// @{
	public:
		typedef reverse_iterator_base												class_type;
		typedef It																	iterator_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k iterator_base_type::iterator_category				iterator_category;
		typedef typename_type_k iterator_base_type::value_type						value_type;
		typedef typename_type_k iterator_base_type::reference						reference;
		typedef typename_type_k iterator_base_type::const_reference					const_reference;
		typedef typename_type_k iterator_base_type::pointer							pointer;
		typedef typename_type_k iterator_base_type::const_pointer					const_pointer;
		typedef typename_type_k iterator_base_type::difference_type					difference_type;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		reverse_iterator_base() 
			: base_type() 
		{}
		explicit_k reverse_iterator_base(iterator_type const& it) 
			: base_type(it) 
		{}
		reverse_iterator_base(class_type const& it) 
			: base_type(it.current()) 
		{}
		// const_reverse_iterator_base can be explicitly converted to reverse_iterator_base
		explicit_k reverse_iterator_base(base_type const& it) 
			: base_type(it) 
		{}
	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		explicit_k reverse_iterator_base(reverse_iterator_base<It2> const& it) 
			: base_type(it.current()) 
		{}
	#endif
	/// @}

	/// \name Helpers
	/// @{
	private:
		base_type const&	base() const	{ return *this;	}
		base_type&			base()			{ return *this;	}
	/// @}

	/// \name Methods
	/// @{
	public:
		class_type& operator ++()
		{
			++base();
			return (*this);
		}
		class_type operator ++(int)
		{
			class_type tmp = *this;
			++base();
			return tmp;
		}
		class_type& operator --()
		{
			--base();
			return (*this);
		}
		class_type operator --(int)
		{
			class_type tmp = *this;
			--base();
			return tmp;
		}
		class_type& operator +=(difference_type offset)
		{	
			base() += offset;
			return (*this);
		}
		class_type operator +(difference_type offset) const
		{	
			return (class_type(this->current() - offset));
		}
		class_type& operator -=(difference_type offset)
		{	
			base() -= offset;
			return (*this);
		}
		class_type operator -(difference_type offset) const
		{	
			return (class_type(this->current() + offset));
		}
		difference_type operator -(class_type const& rhs) const
		{
			return (base() - static_cast<base_type const&>(rhs));
		}
		reference operator *()
		{
			return const_cast<reference>(*base());
		}
		pointer operator ->()
		{
			return (&**this);
		}
		reference operator [](difference_type offset) 
		{	
			return const_cast<reference>(base()[offset]);
		}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		difference_type operator -(reverse_iterator_base<It2> const& rhs) const
		{
			return (rhs.current() - this->current());
		}
		template<typename_param_k It2>
		bool_type operator <(reverse_iterator_base<It2> const& rhs) const
		{
			return (rhs.current() < this->current());
		}
		template<typename_param_k It2>
		bool_type operator >=(reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this) < rhs);
		}
		template<typename_param_k It2>
		bool_type operator >(reverse_iterator_base<It2> const& rhs) const
		{
			return (rhs > this->current());
		}
		template<typename_param_k It2>
		bool_type operator <=(reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this) > rhs);
		}
		template<typename_param_k It2>
		bool_type operator ==(reverse_iterator_base<It2> const& rhs) const
		{
			return (this->current() == rhs);
		}
		template<typename_param_k It2>
		bool_type operator !=(reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this)== rhs);
		}
	#endif
		bool_type operator <(class_type const& rhs) const
		{
			return (rhs.current() < this->current());
		}
		bool_type operator >=(class_type const& rhs) const
		{
			return !((*this) < rhs);
		}
		bool_type operator >(class_type const& rhs) const
		{
			return (rhs.current() > this->current());
		}
		bool_type operator <=(class_type const& rhs) const
		{
			return !((*this) > rhs);
		}
		bool_type operator ==(class_type const& rhs) const
		{
			return (this->current() == rhs.current());
		}
		bool_type operator !=(class_type const& rhs) const
		{
			return !((*this) == rhs);
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * reverse_iterator_base implemention
 */
template<	typename_param_k It
		,	typename_param_k Diff 
		> 
inline reverse_iterator_base<It> operator +(Diff offset, reverse_iterator_base<It> const& rhs)
{
	return (rhs + offset);
}

/*!\brief const_reverse_bidirectional_iterator_base
 *
 * \param It The iterator type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k It>
struct const_reverse_bidirectional_iterator_base
	: public const_iterator_base<	std_bidirectional_iterator_tag
								,	typename_type_k xtl_iterator_traits<It>::value_type
								,	typename_type_k xtl_iterator_traits<It>::difference_type
								>
{
	private:
		typedef const_iterator_base	<	std_bidirectional_iterator_tag
									,	typename_type_k xtl_iterator_traits<It>::value_type
									,	typename_type_k xtl_iterator_traits<It>::difference_type
									>												base_type;
		typedef base_type															iterator_base_type;

	/// \name Types
	/// @{
	public:
		typedef const_reverse_bidirectional_iterator_base							class_type;
		typedef It																	iterator_type;
		typedef typename_type_k iterator_base_type::iterator_category				iterator_category;
		typedef typename_type_k iterator_base_type::value_type						value_type;
		typedef typename_type_k iterator_base_type::reference						reference;
		typedef typename_type_k iterator_base_type::const_reference					const_reference;
		typedef typename_type_k iterator_base_type::pointer							pointer;
		typedef typename_type_k iterator_base_type::const_pointer					const_pointer;
		typedef typename_type_k iterator_base_type::difference_type					difference_type;
		typedef e_bool_t															bool_type;
	/// @}
	
	/// \name Members
	/// @{
	private:
		iterator_type																m_current;
	/// @}

	/// \name Constructors
	/// @{
	public:
		const_reverse_bidirectional_iterator_base() 
			: m_current() 
		{}
		explicit_k const_reverse_bidirectional_iterator_base(iterator_type const& it) 
			: m_current(it) 
		{}
		const_reverse_bidirectional_iterator_base(class_type const& it) 
			: m_current(it.current()) 
		{}

	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		explicit_k const_reverse_bidirectional_iterator_base(const_reverse_bidirectional_iterator_base<It2> const& it) 
			: m_current(it.current()) 
		{}
	#endif
	/// @}

	/// \name Methods
	/// @{
	public:
		iterator_type const& current() const
		{
			return m_current;
		}
		class_type& operator ++()
		{
			--m_current;
			return (*this);
		}
		class_type operator ++(int)
		{
			class_type tmp = *this;
			++(*this);
			return tmp;
		}
		class_type& operator --()
		{
			++m_current;
			return (*this);
		}
		class_type operator --(int)
		{
			class_type tmp = *this;
			--(*this);
			return tmp;
		}
		
		const_reference operator *() const
		{
			// rbegin() ==> end() 
			iterator_type tmp = current();
			return (*--tmp);
		}
		const_pointer operator ->() const
		{
			return (&**this);
		}
		
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		bool_type operator ==(const_reverse_iterator_base<It2> const& rhs) const
		{
			return (current() == rhs.current());
		}
		template<typename_param_k It2>
		bool_type operator !=(const_reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this) == rhs);
		}
	#endif
		bool_type operator ==(class_type const& rhs) const
		{
			return (current() == rhs.current());
		}
		bool_type operator !=(class_type const& rhs) const
		{
			return !((*this) == rhs);
		}
	/// @}
};
/*!\brief reverse_bidirectional_iterator_base
 *
 * \param It The iterator type
 *
 * \ingroup extl_group_iterator
 */
template<typename_param_k It>
struct reverse_bidirectional_iterator_base
	: public const_reverse_bidirectional_iterator_base<It>	// reverse_bidirectional_iterator can be implicitly converted to const_reverse_bidirectional_iterator
	, public iterator_base	<	std_bidirectional_iterator_tag
							,	typename_type_k xtl_iterator_traits<It>::value_type
							,	typename_type_k xtl_iterator_traits<It>::difference_type
							>
{
	private:
		typedef const_reverse_bidirectional_iterator_base<It>						base_type;
		typedef iterator_base	<	std_bidirectional_iterator_tag
								,	typename_type_k xtl_iterator_traits<It>::value_type
								,	typename_type_k xtl_iterator_traits<It>::difference_type
								>													iterator_base_type;

	/// \name Types
	/// @{
	public:
		typedef reverse_bidirectional_iterator_base									class_type;
		typedef It																	iterator_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k iterator_base_type::iterator_category				iterator_category;
		typedef typename_type_k iterator_base_type::value_type						value_type;
		typedef typename_type_k iterator_base_type::reference						reference;
		typedef typename_type_k iterator_base_type::const_reference					const_reference;
		typedef typename_type_k iterator_base_type::pointer							pointer;
		typedef typename_type_k iterator_base_type::const_pointer					const_pointer;
		typedef typename_type_k iterator_base_type::difference_type					difference_type;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		reverse_bidirectional_iterator_base() 
			: base_type() 
		{}
		explicit_k reverse_bidirectional_iterator_base(iterator_type const& it) 
			: base_type(it) 
		{}
		reverse_bidirectional_iterator_base(class_type const& it) 
			: base_type(it.current()) 
		{}
		// const_reverse_bidirectional_iterator_basee can be explicitly converted to reverse_bidirectional_iterator_base
		explicit_k reverse_bidirectional_iterator_base(base_type const& it) 
			: base_type(it) 
		{}

	#ifdef EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		explicit_k reverse_bidirectional_iterator_base(reverse_bidirectional_iterator_base<It2> const& it) 
			: base_type(it.current()) 
		{}
	#endif
	/// @}

	/// \name Helpers
	/// @{
	private:
		base_type const&	base() const	{ return *this;	}
		base_type&			base()			{ return *this;	}
	/// @}

	/// \name Methods
	/// @{
	public:
		class_type& operator ++()
		{
			++base();
			return (*this);
		}
		class_type operator ++(int)
		{
			class_type tmp = *this;
			++base();
			return tmp;
		}
		class_type& operator --()
		{
			--base();
			return (*this);
		}
		class_type operator --(int)
		{
			class_type tmp = *this;
			--base();
			return tmp;
		}
		reference operator *()
		{
			return const_cast<reference>(*base());
		}
		pointer operator ->()
		{
			return (&**this);
		}
	#ifdef EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT
		template<typename_param_k It2>
		bool_type operator ==(reverse_iterator_base<It2> const& rhs) const
		{
			return (this->current() == rhs.current());
		}
		template<typename_param_k It2>
		bool_type operator !=(reverse_iterator_base<It2> const& rhs) const
		{
			return !((*this) == rhs);
		}
	#endif
		bool_type operator ==(class_type const& rhs) const
		{
			return (this->current() == rhs.current());
		}
		bool_type operator !=(class_type const& rhs) const
		{
			return !((*this) == rhs);
		}
	/// @}
};

// pop warning
#if defined(EXTL_COMPILER_IS_MSVC) && (_MSC_VER <= 1200)
#	pragma warning(pop)
#endif  

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE 

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_ITERATOR_REVERSE_ITERATOR_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
