/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_buffer.h		
 *
 * Created:		08.03.06					
 * Updated:		08.04.14	
 *
 * Brief: scoped_buffer class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_SCOPED_BUFFER_H
#define EXTL_MEMORY_SCOPED_BUFFER_H

/*!\file scoped_buffer.h
 * \brief scoped_buffer class
 */

#ifndef __cplusplus
#	error scoped_buffer.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "buffer_base.h"
#include "memory_traits_selector.h"
#include "allocator_selector.h"
#include "initialiser_selector.h"
#include "../math/max_min.h"
/* include "../utility/uncopyable.h" */
#include "allocator_traits.h"

#ifdef EXTL_MPL_IF_SUPPORT
#	include "../mpl/if_.h"
#endif

#ifdef EXTL_MEMORY_SCOPED_BUFFER_TEST_ENABLE
#	include "../math/rand.h"
#	include "../counter/clock_counter.h"
#	ifndef EXTL_NO_STL
#		include <vector>
#	endif
#endif

/// The maximum number of the static storage space 
#define EXTL_MEMORY_SCOPED_BUFFER_MAX_SPACE	32

/// The minimum number of the static storage space for not using T buf[0]
#define EXTL_MEMORY_SCOPED_BUFFER_SPACE_0	(0)

/// The size of a block 
#define EXTL_MEMORY_SCOPED_BUFFER_BLOCK_SIZE	(128)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_BEGIN_NAMESPACE

template<typename_param_k T, e_size_t SPACE>
union union_scoped_buffer_data_type
{
	T	buf[SPACE];
	T*	ptr;	
};

template<typename_param_k T, e_size_t SPACE>
struct struct_scoped_buffer_data_type
{
	T	buf[SPACE];
	T*	ptr;	
};

template<typename_param_k T>
union SPACE_0_scoped_buffer_data_type
{
	T*	buf;
	T*	ptr;	
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
/*!\brief: scoped_buffer class
 *
 * \param T The element type
 * \param SPACE The static storage space
 * \param A The allocator type
 * \param M The memory traits type
 * \param I The initialiser type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t SPACE = EXTL_MEMORY_SCOPED_BUFFER_MAX_SPACE	
		,	typename_param_k A = typename_type_def_k allocator_selector<T>::allocator_type 
		,	typename_param_k M = typename_type_def_k memory_traits_selector<T>::memory_traits_type
		,	typename_param_k I = typename_type_def_k initialiser_selector<T>::initialiser_type
#else
		,	e_size_t SPACE
		,	typename_param_k A	
		,	typename_param_k M
		,	typename_param_k I
#endif
		>
class scoped_buffer
	: public buffer_base< scoped_buffer<T, SPACE, A, M, I>, A, M>
	, protected I // EXTL_EBO_FORM_7_SUPPORT 
{
	/// \name Types
	/// @{
	public:
		typedef scoped_buffer											class_type;		
		typedef buffer_base<class_type, A, M>							base_type;	
		typedef typename_type_k base_type::value_type					value_type;		
		typedef typename_type_k base_type::memory_traits_type			memory_traits_type;	
		typedef I														initialiser_type;
		typedef	typename_type_k base_type::allocator_type				allocator_type;		
		typedef typename_type_k base_type::pointer						pointer;			
		typedef typename_type_k base_type::const_pointer				const_pointer;		
		typedef typename_type_k base_type::reference					reference;			
		typedef typename_type_k base_type::const_reference				const_reference;	
		typedef typename_type_k base_type::size_type					size_type;			
		typedef typename_type_k base_type::difference_type				difference_type;
		typedef typename_type_k base_type::iterator						iterator;
		typedef typename_type_k base_type::const_iterator				const_iterator;
		typedef typename_type_k base_type::reverse_iterator				reverse_iterator;
		typedef typename_type_k base_type::const_reverse_iterator		const_reverse_iterator;
		typedef typename_type_k base_type::bool_type					bool_type;
		typedef typename_type_k base_type::index_type					index_type;
	/// @}

	/// \name Other Types
	/// @{
	private:
	#if defined(EXTL_TYPE_TRAITS_IS_POD_SUPPORT)
		enum{ en_is_pod = (is_pod<T>::value)	};
	#elif defined(EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT)
		enum{ en_is_pod = (is_scalar<T>::value)	};
	#else
		enum{ en_is_pod = (is_arithmetic<T>::value)	};
	#endif

	#ifdef EXTL_MPL_IF_SUPPORT
		typedef typename_type_k EXTL_NS_MPL(if_)<	(en_is_pod)
												,	EXTL_NS_DETAIL(union_scoped_buffer_data_type)<T, SPACE>
												,	EXTL_NS_DETAIL(struct_scoped_buffer_data_type)<T, SPACE>
												>::type						data_type_;
		typedef typename_type_k EXTL_NS_MPL(if_)<	(SPACE == 0)
												,	EXTL_NS_DETAIL(SPACE_0_scoped_buffer_data_type)<T>
												,	data_type_
												>::type						data_type;
	#else
		typedef EXTL_NS_DETAIL(SPACE_0_scoped_buffer_data_type)<T>			data_type;
	#endif

		/// The enum type
		enum 
		{ 
			en_block_size = EXTL_MEMORY_SCOPED_BUFFER_BLOCK_SIZE	//!< The alignment boundary for adjust_size()
		};
	/// @}

	/// \name Members
	/// @{
	private:
		/* data:		|-------------------------------| 
		 * size:		|---------------------|
		 * capacity:	|-------------------------------|
		 */

		data_type	m_data;					//!< The memory storage 
		size_type	m_size;					//!< The size of the used storage 
		size_type	m_capacity;				//!< The size of the reserved storage 
		
	/// @}

	private:
		friend class buffer_base<class_type, A, M>;

	/// \name Constructors
	/// @{
	public:
		/// Constructs a scoped_buffer with the given number of elements
		explicit_k scoped_buffer(size_type const& n = 0, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			resize(n);
		}

		/// Constructs a scoped_buffer with n values from the given buffer at the specified position 
		scoped_buffer(const_pointer buf, size_type n, size_type pos = 0, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			base_type::assign(buf, n, pos);
		}

		/// Constructs a scoped_buffer from the given buffer 
		scoped_buffer(class_type const& buf, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{	
			init();
			base_type::assign(buf, buf.size());	
		}

		/// Constructs a scoped_buffer with n values from the given buffer at the specified position 
		scoped_buffer(class_type const& buf, size_type n, size_type pos = 0, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			base_type::assign(buf, n, pos);
		}

		/// Constructs with n values
		scoped_buffer(const_reference v, size_type n, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			base_type::assign(v, n);
		}

		/// Constructs from range [first, last) with the const pointer
		scoped_buffer(const_pointer first, const_pointer last, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			base_type::assign(first, last);
		}
		/// Constructs from range [first, last) with the const iterator
		scoped_buffer(const_iterator first, const_iterator last, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			base_type::assign(first, last);
		}
		/// Constructs from range [first, last) with the const reverse iterator
		scoped_buffer(const_reverse_iterator first, const_reverse_iterator last, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			base_type::assign(first, last);
		}
	#if defined(EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT) \
			&& !defined(EXTL_COMPILER_IS_DMC)
		/// Constructs from range [first, last) with the input iterator
		template < typename_param_k _InIt >
		scoped_buffer(_InIt first, _InIt last, initialiser_type intr = initialiser_type())
			: m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			init();
			base_type::assign(first, last);
		}
	#endif

		/// Destructor
		~scoped_buffer() EXTL_THROW_0() 
		{
			destroy();
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns the pointer to the buffer
		pointer data()					
		{ 
			if (0 == size()) return NULL;
			return ((m_capacity <= SPACE) && (SPACE != 0))? m_data.buf : m_data.ptr;	
		}
		/// Returns the const pointer to the buffer
		const_pointer data()	const	
		{ 
			if (0 == size()) return NULL;
			return ((m_capacity <= SPACE) && (SPACE != 0))? m_data.buf : m_data.ptr;	
		}
		/// Returns the size of the buffer
		size_type size()		const	{ return m_size;		}
		/// Returns the capacity size of the buffer
		size_type capacity()	const	{ return m_capacity;	}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& buf)	{ return base_type::operator=(buf);	}
		class_type& operator=(const_reference v)		{ return base_type::operator=(v);	}
	/// @}
		
	/// \name Mutators
	/// @{
	public:
		/// Destroy the buffer
		void destroy()
		{
			EXTL_ASSERT(is_valid());

			/* Releases the buffer */
			if (SPACE < capacity())
			{
				EXTL_ASSERT(NULL != data());
				initialiser().destruct_n(data(), m_capacity);
				base_type::allocator().deallocate(data());
				m_data.ptr = NULL;
			}
			m_size = 0;
			m_capacity = 0;

			EXTL_ASSERT(is_valid());
		}

		/*!\brief Resizes the size of buffer
		 *
		 * \note Only resize the capacity of the storage when is_update_size is e_false_v
		 */
		void resize(size_type size, bool_type is_update_size = e_true_v)
		{
			EXTL_ASSERT(is_valid());

			/* Adjusts the size for avoiding to allocate memory frequently */
			size_type adjusted_size = adjust_size(size);
			EXTL_ASSERT(!(base_type::max_size() < adjusted_size));
			EXTL_ASSERT_THROW(!(base_type::max_size() < adjusted_size), std_length_error("scoped_buffer too long"));

			/* needn't to adjust size in the static storage */
			if (adjusted_size <= SPACE && m_size <= SPACE)
			{
				m_capacity = SPACE;
			}
			/* needn't to adjust the size of storage 
			 * when the difference between size and m_size is too small
			 */
			else if (adjusted_size == m_capacity)
			{
			}
			/* Shrinks the size of memory
			 * m_data.ptr ==> m_data.buf
			 */
			else if (adjusted_size <= SPACE)
			{
				pointer p = m_data.ptr;
				memory_traits_type::copy(m_data.buf, p, adjusted_size);
				
				initialiser().destruct_n(p, m_capacity);
				base_type::allocator().deallocate(p);

				m_capacity = SPACE;
			}
			/* Expands the size of memory 
			 * m_data.buf ==> m_data.ptr
			 */
			else if (m_size <= SPACE)
			{
				pointer p = base_type::allocator().allocate(adjusted_size);
				EXTL_ASSERT(NULL != p);
				initialiser().construct_n(p, adjusted_size);

				memory_traits_type::copy(p, m_data.buf, m_size);
				m_data.ptr = p;
				m_capacity = adjusted_size;
			}
			/* Shrinks and expands the size of memory
			 * m_data.ptr ==> m_data.ptr
			 */
			else
			{
				if(allocator_traits<allocator_type>::is_support_reallocate && 
						en_is_pod) // need not construct
				{
					m_data.ptr = base_type::allocator().reallocate(m_data.ptr, adjusted_size);
				}
				else 
				{
					pointer p = base_type::allocator().allocate(adjusted_size);
					EXTL_ASSERT(NULL != p);
					initialiser().construct_n(p, adjusted_size);

					memory_traits_type::copy(p, m_data.ptr, xtl_min(m_size, adjusted_size));

					initialiser().destruct_n(m_data.ptr, m_capacity);
					base_type::allocator().deallocate(m_data.ptr);
					m_data.ptr = p;	
				}
				m_capacity = adjusted_size;
			}

			if (is_update_size) m_size = size;

			EXTL_ASSERT(is_valid());
		}

		/// Swaps storage
		void swap(class_type& rhs) EXTL_THROW_0()
		{
			EXTL_ASSERT(is_valid());

			if (this == &rhs) return ;

			if (m_capacity <= SPACE) std_swap(m_data, rhs.m_data);
			else std_swap(m_data.ptr, rhs.m_data.ptr);

			std_swap(m_size, rhs.m_size);
			std_swap(m_capacity, rhs.m_capacity);

			EXTL_ASSERT(is_valid());
		}
	/// @}

	// \name Helpers
	// @{
	private:
		// Adjusts the size for avoiding to allocate memory frequently 
		size_type adjust_size(size_type n)
		{
			return EXTL_ALIGN(n, en_block_size);
		}
		// Invariance 
		bool_type is_valid() const
		{
			if (capacity() < size())
				return e_false_v;
			
			if ((0 < size()) && (NULL == data()))
			{
				return e_false_v;
			}
		
			return e_true_v;
		}

		// init
		void init()
		{
			this->clear();

			// initialize T buf[SPACE]
			if (SPACE > 0) initialiser().construct_n(m_data.buf, SPACE);
		}

		// Returns the initialiser
		initialiser_type&		initialiser()			{ return *this;	}
		// Returns the initialiser
		initialiser_type const&	initialiser() const		{ return *this;	}
	// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing 
 */
#ifdef EXTL_MEMORY_SCOPED_BUFFER_TEST_ENABLE
#	include "unit_test/scoped_buffer_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_SCOPED_BUFFER_H */
/* //////////////////////////////////////////////////////////////////// */
