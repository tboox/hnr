/* ///////////////////////////////////////////////////////////////////////
 * File:		buffer_base.h		
 *
 * Created:		08.05.26					
 * Updated:		08.05.27	
 *
 * Brief: Memory buffer base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_BUFFER_BASE_H
#define EXTL_MEMORY_BUFFER_BASE_H

/*!\file buffer_base.h
 * \brief Memory buffer base class
 */

#ifndef __cplusplus
#	error buffer_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../iterator/iterator.h"
#include "../algorithm/algorithm.h" 
#include "../error/error.h"
#include "pod_memory_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief buffer base class 
 * \param B The buffer type
 * \param A The buffer type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k B
		,	typename_param_k A
		,	typename_param_k M
		>
class buffer_base 
#ifdef EXTL_EBO_FORM_2_SUPPORT
	: protected A	/* if EBO is supported */
#endif
{
	/// \name Types
	/// @{
	public:
		typedef buffer_base<B, A, M>									class_type;	
		typedef	A														allocator_type;	
		typedef	B														buffer_type;	
		typedef	M														memory_traits_type;
		typedef typename_type_k allocator_type::value_type				value_type;	
		typedef pod_memory_traits<value_type>							pod_memory_traits_type;
		typedef typename_type_k allocator_type::pointer					pointer;			
		typedef typename_type_k allocator_type::const_pointer			const_pointer;		
		typedef typename_type_k allocator_type::reference				reference;			
		typedef typename_type_k allocator_type::const_reference			const_reference;	
		typedef typename_type_k allocator_type::size_type				size_type;			
		typedef e_ptrdiff_t												difference_type;
		typedef e_bool_t												bool_type;
		typedef size_type												index_type;
		typedef pointer_iterator<value_type>							iterator;
		typedef const_pointer_iterator<value_type>						const_iterator;
		typedef reverse_iterator_base<const_iterator>					reverse_iterator;
		typedef const_reverse_iterator_base<const_iterator>				const_reverse_iterator;
	/// @}

	/// \name Iterators
	/// @{
	public:
		const_iterator			begin() const		{ return const_iterator(buffer().data());								}
		iterator				begin()				{ return iterator(buffer().data());										}

		const_iterator			end() const			{ return const_iterator(buffer().data() + buffer().size());			}
		iterator				end()				{ return iterator(buffer().data() + buffer().size());				}

		const_reverse_iterator	rbegin() const		{ return const_reverse_iterator(buffer().end());		}
		reverse_iterator		rbegin()			{ return reverse_iterator(buffer().end());				}

		const_reverse_iterator	rend() const		{ return const_reverse_iterator(buffer().begin());		}
		reverse_iterator		rend()				{ return reverse_iterator(buffer().begin());			}
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns reference at the given index
		reference		operator[](index_type index)
		{
			return const_cast<reference>(static_cast<buffer_type const&>(*this).operator[](index));
		}
		/// Returns const reference at the given index
		const_reference	operator[](index_type index) const
		{
			EXTL_ASSERT(buffer().is_valid());
			EXTL_ASSERT(NULL != buffer().data());
			EXTL_ASSERT(index < buffer().size());
			return buffer().data()[index];
		}
		/// Returns reference at the given index and throws index_error() if index >= size() 
		reference		at(index_type index)
		{
			return const_cast<reference>(static_cast<buffer_type const&>(*this).at(index));
		}
		/// Returns const reference at the given index and throws index_error() if index >= size() 
		const_reference	at(index_type index) const
		{
			EXTL_ASSERT(buffer().is_valid());
			EXTL_ASSERT(NULL != buffer().data());
			EXTL_ASSERT(index < buffer().size());
			EXTL_ASSERT_THROW(index < buffer().size(), index_error("out of range"));
			return buffer().data()[index];
		}

		// Returns the first element of the buffer
		reference		front()			{ return buffer().at(0);	}
		// Returns the first element of the buffer
		const_reference	front()	const	{ return buffer().at(0);	}
		// Returns the last element of the buffer
		reference		back()			{ return buffer().at(buffer().size() - 1);	}
		// Returns the last element of the buffer
		const_reference	back() const	{ return buffer().at(buffer().size() - 1);	}
	/// @}

	/// \name Others
	/// @{
	public:
		/// Indicates whether the buffer is empty
		bool_type	is_empty()	const			{ return 0 == buffer().size();	}
		/// Indicates whether the buffer is empty for comparability
		bool_type	empty()	const				{ return buffer().is_empty();	}
		/// The maximum size of the buffer
		size_type	max_size() const			{ return allocator().max_size();	}
		/// Reserves at least newcap size memory storage
		void		reserve(size_type newcap)	{ if (buffer().capacity() < newcap) buffer().resize(newcap, e_false_v);	}
		/// Clears the memory of the buffer
		void		clear()						{ buffer().erase(0, buffer().size());	}
		/// Fills zero in the whole buffer
		void		clean()						{ memory_traits_type::fill_0(buffer().data(), buffer().size());	}
	public:
		/// Returns the allocator
		allocator_type allocator() const
		{
		#ifdef EXTL_EBO_FORM_2_SUPPORT
			return *this;
		#else
			return allocator_type();
		#endif
		}
	/// @}

	/// \name Replacements
	/// @{
	public:
		/// Replaces the given range [pos, pos + old_n) with the given new buffer with new_n value 
		buffer_type& replace(size_type pos, size_type old_n, const_pointer new_buf, size_type new_n);
		/// Replaces the given range [pos, pos + old_n) with the given new buffer
		buffer_type& replace(size_type pos, size_type old_n, buffer_type const& new_buf)						{ return replace(pos, old_n, new_buf.data(), new_buf.size());		}
		/// Replaces the given range [pos, pos + old_n) with the given new buffer with new_n value 
		buffer_type& replace(size_type pos, size_type old_n, buffer_type const& new_buf, size_type new_n)		{ return buffer().replace(pos, old_n, new_buf.data(), new_n);				}
		/// Replaces the given range [pos, pos + old_n) with the given new_n value with the value new_value 
		buffer_type& replace(size_type pos, size_type old_n, const_reference new_value, size_type new_n = 1);	
		/// Replaces the given position [pos, pos + 1) with the given new_n value with the value new_value 
		buffer_type& replace(size_type pos, const_reference new_value, size_type new_n = 1)								{ return buffer().replace(pos, 1, new_value, new_n);												}
	
		/// Replaces the given range [first, last) with the input const_iterator with the given new buffer with new_n value 
		buffer_type& replace(const_iterator first, const_iterator last, const_pointer new_buf, size_type new_n)			{ return buffer().replace(ptr_diff(buffer().begin(), first), ptr_diff(first, last), new_buf, new_n);		}
		/// Replaces the given range [first, last) with the input const_iterator with the given new buffer
		buffer_type& replace(const_iterator first, const_iterator last, buffer_type const& new_buf)						{ return buffer().replace(first, last, new_buf.data(), new_buf.size());									}
		/// Replaces the given range [first, last) with the input const_iterator with the given new buffer with new_n value 
		buffer_type& replace(const_iterator first, const_iterator last, buffer_type const& new_buf, size_type new_n)	{ return buffer().replace(first, last, new_buf.data(), new_n);									}
		/// Replaces the given range [first, last) with the input const_iterator with the given new_n value with the value new_value 
		buffer_type& replace(const_iterator first, const_iterator last, const_reference new_value, size_type new_n = 1)	{ return buffer().replace(ptr_diff(buffer().begin(), first), ptr_diff(first, last), new_value, new_n);	}
		/// Replaces the given position [pos, pos + 1) with the input const_iterator with the given new buffer with new_n value 
		buffer_type& replace(const_iterator pos, const_reference new_value, size_type new_n = 1)						{ return buffer().replace(ptr_diff(buffer().begin(), pos), 1, new_value, new_n);							}
	
		/// Replaces the given range [first, last) with the input iterator with the given range [first2, last2) 
		buffer_type& replace(const_iterator first, const_iterator last, const_pointer first2, const_pointer last2)						{ return buffer().replace(ptr_diff(buffer().begin(), first), ptr_diff(first, last), first2, ptr_diff(first2, last2));	}
		/// Replaces the given range [first, last) with the input iterator with the given range [first2, last2) with the input iterator 
		buffer_type& replace(const_iterator first, const_iterator last, const_iterator first2, const_iterator last2)					{ return buffer().replace(first, last, get_ptr(first2), get_ptr(last2));	}
		/// Replaces the given range [first, last) with the input iterator with the given range [first2, last2) with the input reverse iterator 
		buffer_type& replace(const_iterator first, const_iterator last, const_reverse_iterator first2, const_reverse_iterator last2)	
		{	
			size_type n = static_cast<size_type>(ptr_diff(first2, last2));
			EXTL_ASSERT(0 != n);
			if(0 == n) return buffer();

		#if 0 // Maybe the buffer type is not owner of memory storage
			buffer_type buf(n);
			std_copy(first2, last2, buf.data());
			buffer().replace(first, last, buf.data(), n);
		#else
			pointer buf = allocator().allocate(n);
			EXTL_ASSERT(NULL != buf);

			std_copy(first2, last2, buf);
			buffer().replace(first, last, buf, n);

			allocator().deallocate(buf);
		#endif
			return buffer();
		}
	
	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		/// Replaces the given range [first, last) with the input iterator with the given new buffer with new_n values 
		template < typename_param_k _InIt >
		buffer_type& replace(const_iterator first, const_iterator last, _InIt first2, _InIt last2 )								
		{	
			size_type n = static_cast<size_type>(std_distance(first2, last2));
			EXTL_ASSERT(0 != n);
			if(0 == n) return buffer();

		#if 0 // Maybe the buffer type is not owner of memory storage
			buffer_type buf(n);
			std_copy(first2, last2, buf.data());
			buffer().replace(first, last, buf.data(), n);
		#else
			pointer buf = allocator().allocate(n);
			EXTL_ASSERT(NULL != buf);

			std_copy(first2, last2, buf);
			buffer().replace(first, last, buf, n);

			allocator().deallocate(buf);
		#endif
			return buffer();
		}
	#endif /* EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT */
	
	/// @}

	/// \name Assignments
	/// @{
	public:
		/// Assigns from the given buffer
		buffer_type& assign(buffer_type const& buf)									{ return buffer().assign(buf.data(), buf.size(), 0);				}
		/// Assigns with n values from the given buffer at the specified position 
		buffer_type& assign(buffer_type const& buf, size_type n, size_type pos = 0)	{ return buffer().assign(buf.data(), n, pos);						}
		/// Assigns with n values from the given buffer at the specified position 
		buffer_type& assign(const_pointer buf, size_type n, size_type pos = 0)		{ return buffer().replace(0, buffer().size(), buf + pos, n);	}
		/// Assigns with n values 
		buffer_type& assign(const_reference v, size_type n = 1)						{ return buffer().replace(0, buffer().size(), v, n);			}

		/// Assigns from range [first, last) with the const pointer iterator  
		buffer_type& assign(const_pointer first, const_pointer last)					{	return buffer().assign(first, last - first);				}
		/// Assigns from range [first, last) with the const input iterator  
		buffer_type& assign(const_iterator first, const_iterator last)					{	return buffer().assign(get_ptr(first), get_ptr(last));		}
		/// Assigns from range [first, last) with the const reverse input iterator  
		buffer_type& assign(const_reverse_iterator first, const_reverse_iterator last)	{	return buffer().replace(buffer().begin(), buffer().end(), first, last);	}

	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		/// Assigns from range [first, last) with the input iterator  
		template < typename_param_k _InIt >
		buffer_type& assign(_InIt first, _InIt last)
		{
			return buffer().replace(begin(), end(), first, last);
		}
	#endif /* EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT */

		buffer_type& operator=(buffer_type const& buf)	{ return buffer().assign(buf, buf.size());	}
		buffer_type& operator=(const_reference v)		{ return buffer().assign(v, 1);				}
	/// @}

	/// \name Appending
	/// @{
	public:
		/// Appends from the given buffer
		buffer_type& append(buffer_type const& buf)									{ return buffer().append(buf.data(), buf.size(), 0);			}
		/// Appends with n values from the given buffer at the specified position 
		buffer_type& append(buffer_type const& buf, size_type n, size_type pos = 0)	{ return buffer().append(buf.data(), n, pos);			}
		/// Appends with n values from the given buffer at the specified position 
		buffer_type& append(const_pointer buf, size_type n, size_type pos = 0)		{ return buffer().replace(buffer().size(), 0, buf + pos, n);	}
		/// Appends with n values with the value v 
		buffer_type& append(const_reference v, size_type n = 1)						{ return buffer().replace(buffer().size(), 0, v, n);			}
		
		/// Appends from range [first, last) with the const pointer  
		buffer_type& append(const_pointer first, const_pointer last)					{ return buffer().append(first, last - first, 0);			}
		/// Appends from range [first, last) with the const input iterator  
		buffer_type& append(const_iterator first, const_iterator last)					{ return buffer().append(get_ptr(first), get_ptr(last));				}
		/// Appends from range [first, last) with the const reverse input iterator  
		buffer_type& append(const_reverse_iterator first, const_reverse_iterator last)	
		{ 
			std_copy(first, last, extl_back_inserter(buffer()));
			return buffer();			
		}

	#if defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT)
		template < typename_param_k _InIt >
		buffer_type& append(_InIt first, _InIt last) /* optimization */
		{
			std_copy(first, last, extl_back_inserter(buffer()));
			return buffer();
		}
	#endif /* defined(EXTL_MEMBER_TEMPLATE_FUNC_OVERLOAD_DISCRIMINATED_SUPPORT) */

	public: 
		buffer_type& operator+=(buffer_type const& buf)		{ return buffer().append(buf, buf.size());	}
		buffer_type& operator+=(const_reference v)			{ return buffer().append(v, size_type(1));	}
	
	public:
		void push_back(const_reference v)					{ buffer().append(v);					}
		void pop_back()										{ buffer().resize(buffer().size() - 1); }
	/// @}

	/// \name Insertments
	/// @{
	public:
		/// Inserts the given new buffer with new_n values into the given position *this[pos] 
		buffer_type& insert(size_type pos, const_pointer new_buf, size_type new_n)				{ return buffer().replace(pos, 0, new_buf, new_n);		}
		/// Inserts the given new buffer into the given position *this[pos] 
		buffer_type& insert(size_type pos, buffer_type const& new_buf)							{ return buffer().insert(pos, new_buf.data(), new_buf.size());	}
		/// Inserts the given new buffer with new_n values into the given position *this[pos] 
		buffer_type& insert(size_type pos, buffer_type const& new_buf, size_type new_n)			{ return buffer().insert(pos, new_buf.data(), new_n);	}
		/// Inserts the given new_n value with the value new_value into the given position *this[pos]
		buffer_type& insert(size_type pos, const_reference new_value, size_type new_n = 1)		{ return buffer().replace(pos, 0, new_value, new_n);		}

		/// Inserts the given new buffer with new_n values into the given position *pos with the input iterator 
		buffer_type& insert(const_iterator pos, const_pointer new_buf, size_type new_n)			{ return buffer().insert(ptr_diff(buffer().begin(), pos), new_buf, new_n);	}
		/// Inserts the given new buffer into the given position *pos with the input const_iterator 
		buffer_type& insert(const_iterator pos, buffer_type const& new_buf)						{ return buffer().insert(ptr_diff(buffer().begin(), pos), new_buf, new_buf.size());	}
		/// Inserts the given new buffer with new_n values into the given position *pos with the input const_iterator 
		buffer_type& insert(const_iterator pos, buffer_type const& new_buf, size_type new_n)	{ return buffer().insert(ptr_diff(buffer().begin(), pos), new_buf, new_n);	}
		/// Inserts the given new_n value with the value new_value into the given position *pos with the input const_iterator 
		buffer_type& insert(const_iterator pos, const_reference new_value, size_type new_n = 1)	{ return buffer().insert(ptr_diff(buffer().begin(), pos), new_value, new_n);	}
	/// @}

	/// \name Erasements
	/// @{
	public:
		/// Erases the given range [pos, pos + n) from this 
		buffer_type& erase(size_type pos, size_type n = 1);
		/// Erases the given position *pos with the input iterator from this 
		buffer_type& erase(const_iterator pos)							{ return buffer().erase(ptr_diff(buffer().begin(), pos), 1);							}
		/// Erases the given range [first, last) with the input iterator from this 
		buffer_type& erase(const_iterator first, const_iterator last)	{ return buffer().erase(ptr_diff(buffer().begin(), first), ptr_diff(first, last));		}
	/// @}

	/// \name Reversement
	/// @{
	public:
		/// Reverses the given range [first, last] of the buffer
		buffer_type& reverse(const_iterator first, const_iterator last)	{ return buffer().replace(first, last, const_reverse_iterator(last), const_reverse_iterator(first));	}
		/// Reverses the given range [pos, pos + n] of the buffer
		buffer_type& reverse(size_type pos, size_type n)				{ return buffer().reverse(buffer().begin() + pos, buffer().begin() + pos + n);	}
		/// Reverses the whole buffer
		buffer_type& reverse()											{ return reverse(0, buffer().size());	}
	/// @}

	/// \name Helpers
	/// @{
	private:
		/// Returns the difference between two pointers, last >= first 
		size_type ptr_diff(const_pointer first, const_pointer last) const									{ EXTL_ASSERT(first <= last); return last - first;		}
		/// Returns the difference between two iterators, last >= first 
		size_type ptr_diff(const_iterator const& first, const_iterator const& last) const					{ EXTL_ASSERT(first <= last); return last - first;		}
		/// Returns the difference between two reverse iterators, rfirst >= rlast 
		size_type ptr_diff(const_reverse_iterator const& rfirst, const_reverse_iterator const& rlast) const	{ EXTL_ASSERT(rfirst <= rlast); return rlast - rfirst;	}

		/// Returns the derived class
		buffer_type const&	buffer() const			{ return reinterpret_cast<buffer_type const&>(*this);	}
		/// Returns the derived class
		buffer_type&		buffer()				{ return reinterpret_cast<buffer_type&>(*this);			}

		/// Returns the const pointer of the given the const pointer iterator
		const_pointer		get_ptr(const_iterator const& it) const	{ return it.current();	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_BUFFER_BASE_TEMPLATE_DECL
#	undef EXTL_BUFFER_BASE_TEMPLATE_DECL
#endif

#define EXTL_BUFFER_BASE_TEMPLATE_DECL			\
template<	typename_param_k		B			\
		,	typename_param_k		A			\
		,	typename_param_k		M			\
		>

/* Class qualification */
#ifdef EXTL_BUFFER_BASE_QUAL
#	undef EXTL_BUFFER_BASE_QUAL
#endif

#define EXTL_BUFFER_BASE_QUAL	buffer_base<B, A, M>

/* Class qualification */
#ifdef EXTL_BUFFER_BASE_RET_QUAL
#	undef EXTL_BUFFER_BASE_RET_QUAL
#endif

#define EXTL_BUFFER_BASE_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_BUFFER_BASE_QUAL::ret_type \
					EXTL_BUFFER_BASE_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Class implemention
 */

/* Replaces the given range [*this[pos], *this[pos + old_n]) to the given new c-style buffer with new_n characters */
EXTL_BUFFER_BASE_TEMPLATE_DECL
inline EXTL_BUFFER_BASE_RET_QUAL(buffer_type&)::replace(size_type pos, size_type old_n, const_pointer new_buf, size_type new_n)
{
	EXTL_ASSERT(buffer().is_valid());
	if (NULL == new_buf) return buffer();
	if (!(0 < new_n || 0 < old_n)) return buffer();

	size_type size = buffer().size();
	EXTL_MESSAGE_ASSERT(!(size < pos), "out of range");
	EXTL_ASSERT_THROW(!(size < pos), index_error("out of range"));

	if (size - pos < old_n) old_n = size - pos;
	EXTL_MESSAGE_ASSERT(!(max_size() < size - old_n + new_n), "result buffer is too long");
	EXTL_ASSERT_THROW(!(max_size() < size - old_n + new_n), std_length_error("result buffer is too long"));
	
	/* the size of tail
	 * data:     |-------------------------------|||||||||||||||||||
	 * old_buf:			|------------------------|
	 * tail:									 |||||||||||||||||||
	 */
	size_type tail_n = size - pos - old_n;

	/* Calculates the new size of the replaced buffer */
	size_type new_size = size + (new_n - old_n);
	EXTL_ASSERT(new_size > 0);
	if (new_size <= 0) return buffer();
	
	/* resize the size of buffer */
	buffer().resize(new_size);

	/* resize() maybe change the pointer to the buffer and size */
	pointer data = buffer().data();
	size = buffer().size();
	EXTL_ASSERT(NULL != data);

	/* new_buf has no overlap with the data */
	if (new_buf < data || data + size <= new_buf) 
	{
		/* move tail */
		memory_traits_type::move(data + pos + new_n, data + pos + old_n, tail_n);
		
		/* fill hole */
		memory_traits_type::copy(data + pos, new_buf, new_n);
	}
	else /* new_buf is the subbuffer of this, replace carefully
		  * std::replace of VC 6.0 exist bugs
		  */
	{
		if (new_n <= old_n) /* The hole is not large, only copy in subbuffer */
		{
			/* data:     |--------------------------------------||||||||||||
			 * old_buf:			|-------------------------------|
			 * new_buf:		|==========|	
			 */
			
			/* fill hole
			 * data:     |------==========----------------------||||||||||||
			 * old_buf:			|-------------------------------|
			 * new_buf:		|==========|	
			 */
			
			/* move tail
			 * data:     |------==========||||||||||||
			 * old_buf:			|-------------------------------|
			 * new_buf:		|==========|	
			 */

			/* fill hole */
			memory_traits_type::move(data + pos, new_buf, new_n);
			/* move tail */
			memory_traits_type::move(data + pos + new_n, data + pos + old_n, tail_n);
		}
		else if (new_buf <= data + pos)
		{
			/*if (new_buf + new_n >= data + pos + old_n)
			{*/
				/* data:     |------------------------|||||||||||||||||||||||||||
				 * old_buf:					|--------|	
				 * new_buf:		|========//////////////////////|
				 */

				/* move tail
				 * data:     |------------------------                    |||||||||||||||||||||||||||
				 * old_buf:					|--------|	
				 * old_new_buf:	|========//////////////////////|
				 * new_new_buf:	|========/////////////                    /////////|
				 */

				/* fill hole
				 * data:     |--------------=========/////////////////////|||||||||||||||||||||||||||
				 * old_buf:					|--------|	
				 * old_new_buf:	|========//////////////////////|
				 * new_new_buf:	|========/////////////                    /////////|
				 */

				/* move tail */
				/*memory_traits_type::move(data + pos + new_n, data + pos + old_n, tail_n);*/
				/* fill hole */
				/*size_type new_head_n = pos + old_n - (new_buf - data);*/ /* |========///////////// */
				/*memory_traits_type::move(data + pos, new_buf, new_head_n);*/
				/*memory_traits_type::move(data + pos + new_head_n, new_buf + new_head_n + new_n - old_n, new_n - new_head_n);*/
				
			/*}
			else
			{*/
				/* data:     |------------------------|||||||||||||||||||||||||||
				 * old_buf:					|--------|	
				 * new_buf:		|========////////|
				 */

				/* move tail
				 * data:     |------------------------           |||||||||||||||||||||||||||
				 * old_buf:					|--------|	
				 * old_new_buf:	|========//////////////////////|
				 * new_new_buf:	|========////////|
				 */

				/* fill hole
				 * data:     |--------------=========/////////////|||||||||||||||||||||||||||
				 * old_buf:					|--------|	
				 * old_new_buf:	|========//////////////////////|
				 * new_new_buf:	|========////////|
				 */

				/* move tail */
				memory_traits_type::move(data + pos + new_n, data + pos + old_n, tail_n);
				/* fill hole */
				memory_traits_type::move(data + pos, new_buf, new_n);
			/*}*/
		}
		else if (data + pos + old_n <= new_buf)
		{
			/* data:     |-----------|||||||||||||||||||||||||||||||||||||||
			 * old_buf:		|-------|
			 * new_buf:				   |========//////////////////////|
			 */

			/* move tail
			 * data:     |-----------					  |||||||||||||||||||||||||||||||||||||||
			 * old_buf:		|-------|
			 * old_new_buf:			   |========//////////////////////|
			 * new_new_buf:									  |========//////////////////////|
			 */

			/* fill hole
			 * data:     |--========//////////////////////|||||||||||||||||||||||||||||||||||||||
			 * old_buf:		|-------|
			 * old_new_buf:			   |========//////////////////////|
			 * new_new_buf:									  |========//////////////////////|
			 */

			/* move tail */
			memory_traits_type::move(data + pos + new_n, data + pos + old_n, tail_n);
			/* fill hole */
			memory_traits_type::move(data + pos, new_buf + (new_n - old_n), new_n);
		}
		else
		{
			/* data:     |-------------------|||||||||||||||||||||||||||||||
			 * old_buf:				|-------|
			 * new_buf:					|=======//////////////////|
			 */

			/* fill old hole
			 * data:     |----------=========|||||||||||||||||||||||||||||||
			 * old_buf:				|-------|
			 * new_buf:					|=======//////////////////|
			 */

			/* move tail
			 * data:     |----------=========                ||||||||||||||||||||||||||||||||
			 * old_buf:				|-------|
			 * old_new_buf:				|=======//////////////////|
			 * new_new_buf:				|====                ===//////////////////|
			 */

			/* fill rest of new hole
			 * data:     |----------=========//////////////////||||||||||||||||||||||||||||||||
			 * old_buf:				|-------|
			 * old_new_buf:				|=======//////////////////|
			 * new_new_buf:				|====                ===//////////////////|
			 */


			/* fill old hole */
			memory_traits_type::move(data + pos, new_buf, old_n);
			/* move tail */
			memory_traits_type::move(data + pos + new_n, data + pos + old_n, tail_n);
			/* fill rest of new hole */
			memory_traits_type::move(data + pos + old_n, new_buf + (new_n) /* Note: not old_n */
			, new_n - old_n);
		}
	}

	EXTL_ASSERT(buffer().is_valid());

	return buffer();
}
/* Replaces the given range [*this[pos], *this[pos + old_n]) to the given new_n value with the value new_value */
EXTL_BUFFER_BASE_TEMPLATE_DECL
inline EXTL_BUFFER_BASE_RET_QUAL(buffer_type&)::replace(size_type pos, size_type old_n, const_reference new_value, size_type new_n)
{
	EXTL_ASSERT(buffer().is_valid());
	if (0 == new_n) return buffer();
	if (!(0 < new_n || 0 < old_n)) return buffer();

	size_type size = buffer().size();
	EXTL_MESSAGE_ASSERT(!(size < pos), "out of range");
	EXTL_ASSERT_THROW(!(size < pos), index_error("out of range"));

	if (size - pos < old_n) old_n = size - pos;
	EXTL_MESSAGE_ASSERT(!(max_size() < size - old_n + new_n), "result buffer is too long");
	EXTL_ASSERT_THROW(!(max_size() < size - old_n + new_n), std_length_error("result buffer is too long"));

	/* the length of tail
	 * data: |-------------------------------|||||||||||||||||||
	 * old_str:			|------------------------|
	 * tail:									 |||||||||||||||||||
	 */
	size_type tail_n = size - pos - old_n;

	/* Calculates the new size of the replaced buffer */
	size_type new_size = size + (new_n - old_n);
	EXTL_ASSERT(new_size > 0);
	if (new_size <= 0) return buffer();
	
	/* resize the size of buffer */
	buffer().resize(new_size);

	/* resize() maybe change the pointer to the buffer and size */
	pointer data = buffer().data();
	size = buffer().size();
	EXTL_ASSERT(NULL != data);

	if (old_n < new_n)
	{
		/* move tail */
		memory_traits_type::move(data + pos + new_n, data + pos + old_n, tail_n);
	}

	/* fill hole */
	memory_traits_type::fill(data + pos, new_value, new_n);

	EXTL_ASSERT(buffer().is_valid());
	return buffer();
}

/* Erases the given range [*this[pos], *this[pos + n]) from this */
EXTL_BUFFER_BASE_TEMPLATE_DECL
inline EXTL_BUFFER_BASE_RET_QUAL(buffer_type&)::erase(size_type pos, size_type n)
{
	if (n <= 0) return buffer();
	EXTL_ASSERT(buffer().is_valid());

	size_type size = buffer().size();
	pointer data = buffer().data();
	EXTL_ASSERT(NULL != data);
	if(NULL == data) return buffer();

	if (size - pos < n) n = size - pos;

	EXTL_MESSAGE_ASSERT(!(size < pos), "out of range");
	EXTL_ASSERT_THROW(!(size < pos), index_error("out of range"));

	memory_traits_type::move(data + pos, data + pos + n, size - pos - n);
	buffer().resize(size - n);
	
	EXTL_ASSERT(buffer().is_valid());
	return buffer();
}
/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */
EXTL_BUFFER_BASE_TEMPLATE_DECL
EXTL_INLINE void swap(EXTL_BUFFER_BASE_QUAL& lhs, EXTL_BUFFER_BASE_QUAL& rhs)
{
	static_cast<B&>(lhs).swap(static_cast<B&>(rhs));
}
/* /////////////////////////////////////////////////////////////////////////
 * shims
 */
EXTL_BUFFER_BASE_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_BUFFER_BASE_QUAL::
const_pointer get_ptr(EXTL_BUFFER_BASE_QUAL const& p)
{
	return static_cast<B const&>(p).data();
}

EXTL_BUFFER_BASE_TEMPLATE_DECL
EXTL_INLINE typename_type_ret_k EXTL_BUFFER_BASE_QUAL::
size_type get_size(EXTL_BUFFER_BASE_QUAL const& p)
{
	return static_cast<B const&>(p).size();
}
/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_BUFFER_BASE_TEMPLATE_DECL
#undef EXTL_BUFFER_BASE_QUAL
#undef EXTL_BUFFER_BASE_RET_QUAL

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

template<	typename_param_k	B			
		,	typename_param_k	A			
		,	typename_param_k	M			
		>
EXTL_INLINE void swap(EXTL_NS(buffer_base)<B, A, M>& lhs, 
						EXTL_NS(buffer_base)<B, A, M>& rhs)
{
	static_cast<B&>(lhs).swap(static_cast<B&>(rhs));
}
/* ::std namespace */
EXTL_STD_END_NAMESPACE
#endif

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_BUFFER_BASE_H */
/* //////////////////////////////////////////////////////////////////// */


