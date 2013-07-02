/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_queue.h		
 *
 * Created:		08.08.21			
 * Updated:		08.08.21
 *
 * Brief: basic_queue class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_BASIC_QUEUE_H
#define EXTL_CONTAINER_BASIC_QUEUE_H

/*!\file basic_queue.h
 * \brief basic_queue class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "fixed_reque.h"
#include "list.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief basic_queue
 *
 * \param T The element type
 * \param C The container type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k T
	#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k C = typename_type_def_k list_selector<T>::list_type //fixed_reque<T>
	#else
		,	typename_param_k C
	#endif
		>
class basic_queue
{
	/// \name Types
	/// @{
	public:
		typedef basic_queue															class_type;
		typedef C																	container_type;
		typedef typename_type_k container_type::allocator_type						allocator_type;
		typedef typename_type_k container_type::value_type							value_type;
		typedef typename_type_k container_type::reference							reference;
		typedef typename_type_k container_type::const_reference						const_reference;
		typedef typename_type_k container_type::size_type							size_type;
		typedef typename_type_k container_type::bool_type							bool_type;
		typedef typename_type_k container_type::difference_type						difference_type;
		typedef typename_type_k container_type::iterator							iterator;
		typedef typename_type_k container_type::const_iterator						const_iterator;
		typedef typename_type_k container_type::reverse_iterator					reverse_iterator;
		typedef typename_type_k container_type::const_reverse_iterator				const_reverse_iterator;
	/// @}

	
	/// \name Members
	/// @{
	private:
		container_type																m_c;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_queue()
			: m_c()
		{
		}
		explicit_k basic_queue(container_type const& c)
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
		size_type			max_size() const	{ return container().max_size();		}

		reference			front()				{ return m_c.front();		}
		const_reference		front() const		{ return m_c.front();		}

		reference			back()				{ return m_c.back();		}
		const_reference		back() const		{ return m_c.back();		}
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator begin() const			{ return m_c.begin();		}
		iterator begin()						{ return m_c.begin();		}
		const_iterator end() const				{ return m_c.end();			}
		iterator end()							{ return m_c.end();			}

		const_reverse_iterator rbegin() const	{ return m_c.rbegin();		}
		reverse_iterator  rbegin()				{ return m_c.rbegin();		}
		const_reverse_iterator rend() const		{ return m_c.rend();		}
		reverse_iterator  rend()				{ return m_c.rend();		}
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
		void pop()								{ m_c.pop_front();			}
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
EXTL_INLINE void swap(basic_queue<T, C>& lhs, basic_queue<T, C>& rhs)
{
	lhs.swap(rhs);
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k T
		,	typename_param_k C
		>
EXTL_INLINE typename_type_ret_k basic_queue<T, C>::
size_type get_size(basic_queue<T, C> const& st)
{
	return st.size();
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_BASIC_QUEUE_H */
/* //////////////////////////////////////////////////////////////////// */
