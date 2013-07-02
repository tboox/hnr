/* ///////////////////////////////////////////////////////////////////////
 * File:		path_entry_iterator.h		
 *
 * Created:		08.07.06				
 * Updated:		08.07.06
 *
 * Brief:		path_entry_iterator class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_PLATFORM_WIN_PATH_ENTRY_ITERATOR_H
#define EXTL_PLATFORM_WIN_PATH_ENTRY_ITERATOR_H

/*!\file path_entry_iterator.h
 * \brief path_entry_iterator class
 */

#ifndef __cplusplus
#	error path_entry_iterator.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "path_traits.h"
#include "../../iterator/iterator.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief const_path_entry_iterator class
 *
 * \param C The character type
 * \param T The path traits type
 *
 * \ingroup extl_group_filesystem
 */
template<	typename_param_k C
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k T = path_traits<C>
	#else
		,	typename_param_k T
	#endif
		>
class const_path_entry_iterator
	: public const_iterator_base<	std_input_iterator_tag
								,	typename_type_k T::path_entry_type
								,	e_ptrdiff_t
								>
{
	private:
		typedef const_iterator_base	<	std_input_iterator_tag
									,	typename_type_k T::path_entry_type
									,	e_ptrdiff_t
									>											base_type;
		typedef base_type														iterator_base_type;
	/// \name Types
	/// @{
	public:
		typedef	C																char_type;
		typedef typename_type_k iterator_base_type::iterator_category			iterator_category;
		typedef typename_type_k iterator_base_type::value_type					value_type;
		typedef typename_type_k iterator_base_type::reference					reference;
		typedef typename_type_k iterator_base_type::const_reference				const_reference;
		typedef typename_type_k iterator_base_type::pointer						pointer;
		typedef typename_type_k iterator_base_type::const_pointer				const_pointer;
		typedef typename_type_k iterator_base_type::difference_type				difference_type;
		typedef T																path_traits_type;
		typedef	const_path_entry_iterator										class_type;
		typedef	typename_type_k path_traits_type::size_type						size_type;
		typedef	typename_type_k path_traits_type::bool_type						bool_type;
		typedef	value_type														path_entry_type;
		typedef	typename_type_k path_entry_type::enum_flag_type					enum_flag_type;
	/// @}

	/// \name Members
	/// @{
	private:
		value_type																m_current;
	/// @}

	/// \name Constructor
	/// @{
	public:
		const_path_entry_iterator()
			: m_current()
		{}
		const_path_entry_iterator(class_type const& it) 
			: m_current(it.current())
		{}
		explicit_k const_path_entry_iterator(char_type const* path, enum_flag_type flag)
			: m_current(flag)
		{
			path_traits_type::entry_enum_start(path, m_current);
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		const_reference current() const	{ return m_current;	}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator++()
		{
			if (!path_traits_type::entry_enum(m_current))
			{
				path_traits_type::entry_enum_stop(m_current);
			}
			return *this;
		}
		class_type operator++(int)
		{
			class_type tmp = *this;
			if (!path_traits_type::entry_enum(m_current))
			{
				path_traits_type::entry_enum_stop(m_current);
			}
			return tmp;
		}
		const_reference operator*() const
		{
			return current();
		}
		const_pointer operator->() const
		{
			return (&**this);
		}
	/// @}

	/// \name Comparison
	/// @{
	public:
		bool_type operator ==(class_type const& rhs) const
		{
			return current() == rhs.current();
		}
		bool_type operator !=(class_type const& rhs) const
		{
			return !(current() == rhs.current());
		}
	/// @}
};

/*!\brief const_reverse_path_entry_iterator class
 *
 * \param C The character type
 * \param T The path traits type
 *
 * \note only for implementing strong type
 *
 * \ingroup extl_group_filesystem
 */
template<	typename_param_k C
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k T = path_traits<C>
	#else
		,	typename_param_k T
	#endif
		>
class const_reverse_path_entry_iterator
	: public const_iterator_base	<	std_input_iterator_tag
									,	typename_type_k T::path_entry_type
									,	e_ptrdiff_t
									>
{
	private:
		typedef const_iterator_base	<	std_input_iterator_tag
									,	typename_type_k T::path_entry_type
									,	e_ptrdiff_t
									>									base_type;
		typedef base_type												iterator_base_type;
	/// \name Types
	/// @{
	public:
		typedef	C																char_type;
		typedef typename_type_k iterator_base_type::iterator_category			iterator_category;
		typedef typename_type_k iterator_base_type::value_type					value_type;
		typedef typename_type_k iterator_base_type::reference					reference;
		typedef typename_type_k iterator_base_type::const_reference				const_reference;
		typedef typename_type_k iterator_base_type::pointer						pointer;
		typedef typename_type_k iterator_base_type::const_pointer				const_pointer;
		typedef typename_type_k iterator_base_type::difference_type				difference_type;
		typedef T																path_traits_type;
		typedef	const_reverse_path_entry_iterator								class_type;
		typedef	typename_type_k path_traits_type::size_type						size_type;
		typedef	typename_type_k path_traits_type::bool_type						bool_type;
		typedef	value_type														path_entry_type;
		typedef	typename_type_k path_entry_type::enum_flag_type					enum_flag_type;
	/// @}

	/// \name Members
	/// @{
	private:
		value_type																m_current;
	/// @}

	/// \name Constructor
	/// @{
	public:
		const_reverse_path_entry_iterator()
			: m_current()
		{}
		const_reverse_path_entry_iterator(class_type const& it) 
			: m_current(it.current()) 
			{}
		explicit_k const_reverse_path_entry_iterator(char_type const* path, enum_flag_type flag)
			: m_current(flag)
		{
			path_traits_type::entry_enum_start(path, m_current);
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		reference current() const	{ return m_current;	}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator++()
		{
			if (!path_traits_type::entry_enum(m_current))
			{
				path_traits_type::entry_enum_stop(m_current);
			}
			return *this;
		}
		class_type operator++(int)
		{
			class_type tmp = *this;
			if (!path_traits_type::entry_enum(m_current))
			{
				path_traits_type::entry_enum_stop(m_current);
			}
			return tmp;
		}
		const_reference operator*() const
		{
			return current();
		}
		const_pointer operator->() const
		{
			return (&**this);
		}
	/// @}

	/// \name Comparison
	/// @{
	public:
		bool_type operator ==(class_type const& rhs) const
		{
			return current() == rhs.current();
		}
		bool_type operator !=(class_type const& rhs) const
		{
			return !(current() == rhs.current());
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_PATH_ENTRY_ITERATOR_H */
/* //////////////////////////////////////////////////////////////////// */
