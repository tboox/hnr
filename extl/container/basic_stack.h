/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_stack.h		
 *
 * Created:		08.08.19			
 * Updated:		08.08.20
 *
 * Brief: basic_stack class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BASIC_STACK_H
#define EXTL_CONTAINER_BASIC_STACK_H

/*!\file basic_stack.h
 * \brief basic_stack class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "basic_array.h"
#include "basic_list.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief basic_stack
 *
 * \param T The element type
 * \param C The container type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k T
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k C = typename_type_def_k array_selector<T>::array_type // basic_list<T>
	#else
		,	typename_param_k C
	#endif
		>
class basic_stack
{
	/// \name Types
	/// @{
	public:
		typedef basic_stack															class_type;
		typedef C																	container_type;
		typedef typename_type_k container_type::allocator_type						allocator_type;
		typedef typename_type_k container_type::value_type							value_type;
		typedef typename_type_k container_type::reference							reference;
		typedef typename_type_k container_type::const_reference						const_reference;
		typedef typename_type_k container_type::size_type							size_type;
		typedef typename_type_k container_type::bool_type							bool_type;
		typedef typename_type_k container_type::difference_type						difference_type;
	/// @}

	
	/// \name Members
	/// @{
	private:
		container_type																m_c;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_stack()
			: m_c()
		{
		}
		explicit_k basic_stack(container_type const& c)
			: m_c(c)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		bool_type			is_empty() const	{ return m_c.empty();					}
		bool_type			empty() const		{ return is_empty();					}
		size_type			size() const		{ return m_c.size();					}
		static size_type	max_size()			{ return container_type::max_size();	}

		reference			top()				{ return m_c.back();		}
		const_reference		top() const			{ return m_c.back();		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		container_type const&	container() const	{ return m_c;				}
		allocator_type			allocator() const	{ return m_c.allocator();	}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void push(const_reference value)		{ m_c.push_back(value);		}
		void pop()								{ m_c.pop_back();			}
		void swap(class_type& rhs)				{ m_c.swap(rhs.m_c);		}
		void clear()							{ m_c.clear();				}
	/// @}
};

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k T
		,	typename_param_k C
		>
EXTL_INLINE void swap(basic_stack<T, C>& lhs, basic_stack<T, C>& rhs)
{
	lhs.swap(rhs);
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k T
		,	typename_param_k C
		>
EXTL_INLINE typename_type_ret_k basic_stack<T, C>::
size_type get_size(basic_stack<T, C> const& st)
{
	return st.size();
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_BASIC_STACK_H */
/* //////////////////////////////////////////////////////////////////// */
