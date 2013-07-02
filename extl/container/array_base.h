/* ///////////////////////////////////////////////////////////////////////
 * File:		array_base.h		
 *
 * Created:		08.08.07			
 * Updated:		08.08.07
 *
 * Brief:		The array_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_ARRAY_BASE_H
#define EXTL_CONTAINER_ARRAY_BASE_H

/*!\file array_base.h
 * \brief array_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!brief array_base
 *
 * \param D The derived type
 * \param B The buffer type
 *
 * \ingroup extl_group_container
 */
template<	typename_param_k D
		,	typename_param_k B
		>
class array_base
{
	/// \name Types
	/// @{
	public:
		typedef array_base															class_type;
		typedef D																	derived_type;
		typedef B																	buffer_type;
		typedef typename_type_k buffer_type::allocator_type							allocator_type;
		typedef typename_type_k buffer_type::value_type								value_type;
		typedef typename_type_k buffer_type::pointer								pointer;
		typedef typename_type_k buffer_type::const_pointer							const_pointer;
		typedef typename_type_k buffer_type::reference								reference;
		typedef typename_type_k buffer_type::const_reference						const_reference;
		typedef typename_type_k buffer_type::iterator								iterator;
		typedef typename_type_k buffer_type::const_iterator							const_iterator;
		typedef typename_type_k buffer_type::reverse_iterator						reverse_iterator;
		typedef typename_type_k buffer_type::const_reverse_iterator					const_reverse_iterator;
		typedef typename_type_k buffer_type::size_type								size_type;
		typedef typename_type_k buffer_type::bool_type								bool_type;
		typedef typename_type_k buffer_type::difference_type						difference_type;
		typedef	e_int_t																int_type;	
		typedef size_type															index_type;
	/// @}

	public:
		/// The dimension of the matrix
		EXTL_STATIC_MEMBER_CONST(size_type, dimension = 1);

	/// \name Members
	/// @{
	private:
		buffer_type																	m_buffer;
	/// @}

	private:
		/*!\brief Prohibit the following case:
		 * 
		 * \code
			D da, db;
			B &ba = da, &bb = db;
			ba = bb;
			B b(ba);
		 * \endcode
		 */
		array_base(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		array_base()
			: m_buffer()
		{
		}
		explicit_k array_base(derived_type const& rhs)
			: m_buffer(static_cast<class_type const&>(rhs).buffer())
		{
		}
		array_base(const_pointer ar, size_type n)
			: m_buffer(ar, n)
		{
		}
		array_base(const_reference value, size_type n)
			: m_buffer(value, n)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		allocator_type		allocator() const		{ return buffer().allocator();		}
		index_type			dim0() const			{ return buffer().size();			}
		size_type			size() const			{ return buffer().size();			}
		size_type			capacity() const		{ return buffer().capacity();		}
		bool_type			is_empty() const		{ return buffer().is_empty();		}
		bool_type			empty() const			{ return buffer().is_empty();		}
		size_type			max_size() const		{ return buffer().max_size();		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		pointer				data()							{ return buffer().data();			}
		const_pointer		data() const					{ return buffer().data();			}

		reference			front()							{ return buffer().front();			}
		const_reference		front()	const					{ return buffer().front();			}

		reference			back()							{ return buffer().back();			}
		const_reference		back() const					{ return buffer().back();			}

		reference			operator[](index_type index)		{ return derive().at_unchecked(index);	}
		const_reference		operator[](index_type index) const	{ return derive().at_unchecked(index);	}
		
		reference			at(index_type index)
		{
			return const_cast<reference>(static_cast<derived_type const&>(*this).at(index));
		}
		const_reference		at(index_type index) const
		{
			EXTL_ASSERT_THROW(index < derive().dim0(), index_error("out of range"));
			return derive().at_unchecked(index);
		}

		reference			at_unchecked(index_type index)
		{
			return const_cast<reference>(static_cast<derived_type const&>(*this).at(index));
		}
		const_reference		at_unchecked(index_type index) const
		{
			EXTL_ASSERT(NULL != derive().data());
			EXTL_ASSERT(index < derive().dim0());
			return derive().data()[index];
		}
	/// @}

	/// \name Mutators
	/// @{
	public:
		derived_type& operator =(derived_type const& rhs)
		{
			if (this != static_cast<class_type const*>(&rhs)) 
				buffer().assign(static_cast<class_type const&>(rhs).buffer());
			return derive();
		}
		derived_type& operator =(const_reference value)
		{
			buffer().assign(value, buffer().size());
			return derive();
		}

		void push_back(const_reference value)	{ buffer().push_back(value);	}
		void pop_back()							{ buffer().pop_back();			}
		void swap(derived_type& rhs)			{ buffer().swap(static_cast<class_type&>(rhs).buffer());	}
		void clear()							{ buffer().clear();				}
		void resize(size_type n)				{ buffer().resize(n);			}
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const	{ return const_iterator(derive().data());							}
		iterator				begin()			{ return iterator(derive().data());									}
		
		const_iterator			end() const		{ return const_iterator(derive().data() + derive().size());		}
		iterator				end()			{ return iterator(derive().data() + derive().size());			}
		
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(derive().end());					}
		reverse_iterator		rbegin()		{ return reverse_iterator(derive().end());							}
	
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(derive().begin());					}
		reverse_iterator		rend()			{ return reverse_iterator(derive().begin());						}
	/// @}

	/// \name Others
	/// @{
	protected:
		derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
	
		buffer_type&		buffer()		{ return m_buffer;									}
		buffer_type const&	buffer() const	{ return m_buffer;									}
	/// @}
};

/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE void swap(array_base<D, B>& lhs, array_base<D, B>& rhs)
{
	static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k array_base<D, B>::
const_pointer get_ptr(array_base<D, B> const& ar)
{
	return static_cast<D const&>(ar).data();
}

template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE typename_type_ret_k array_base<D, B>::
size_type get_size(array_base<D, B> const& ar)
{
	return static_cast<D const&>(ar).size();
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * std::swap 
 */
#if !defined(EXTL_NO_STL) && \
		!defined(EXTL_NO_NAMESPACE)
/* ::std namespace */
EXTL_STD_BEGIN_NAMESPACE

template<	typename_param_k D
		,	typename_param_k B
		>
EXTL_INLINE void swap(EXTL_NS(array_base)<D, B>& lhs, 
						EXTL_NS(array_base)<D, B>& rhs)
{
	static_cast<D&>(lhs).swap(static_cast<D&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_ARRAY_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
