/* ///////////////////////////////////////////////////////////////////////
 * File:		scoped_buffer.h		
 *
 * Created:		08.03.06					
 * Updated:		08.12.22
 *
 * Brief:		the scoped_buffer class
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
#include "..\algorithm\algorithm.h"
/* include "..\utility\uncopyable.h" */
#include "allocator_traits.h"

/// The maximum reversed size
#define EXTL_MEMORY_SCOPED_BUFFER_MAX_RESERVED_SPACE	(512)

/// The grow size
#define EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE		(32)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief: scoped_buffer class
 *
 * \param Val The value type
 * \param GrowN The grow size
 * \param Actr The allocator type
 * \param Mtr The memory traits type
 * \param Intr The initialiser type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k Val
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t GrowN = EXTL_MEMORY_SCOPED_BUFFER_DEFAULT_GROW_SIZE	
		,	typename_param_k Actr = typename_type_def_k allocator_selector<Val>::allocator_type 
		,	typename_param_k Mtr = typename_type_def_k memory_traits_selector<Val>::memory_traits_type
		,	typename_param_k Intr = typename_type_def_k initialiser_selector<Val>::initialiser_type
#else
		,	e_size_t GrowN
		,	typename_param_k Actr	
		,	typename_param_k Mtr
		,	typename_param_k Intr
#endif
		>
class scoped_buffer
	: public buffer_base<scoped_buffer<Val, GrowN, Actr, Mtr, Intr>, Actr, Mtr>
	, protected Intr // EXTL_EBO_FORM_7_SUPPORT 
{
	/// \name Types
	/// @{
	public:
		typedef scoped_buffer											class_type;		
		typedef buffer_base<class_type, Actr, Mtr>						base_type;	
		typedef typename_type_k base_type::value_type					value_type;		
		typedef typename_type_k base_type::memory_traits_type			memory_traits_type;	
		typedef typename_type_k base_type::pod_memory_traits_type		pod_memory_traits_type;
		typedef Intr													initialiser_type;
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
		enum{ en_is_pod = (is_pod<Val>::value)	};
	#elif defined(EXTL_TYPE_TRAITS_IS_SCALAR_SUPPORT)
		enum{ en_is_pod = (is_scalar<Val>::value)	};
	#else
		enum{ en_is_pod = (is_arithmetic<Val>::value)	};
	#endif

		/// The enum type
		enum 
		{ 
			/// The grow size
			en_grow_size = EXTL_ALIGN(GrowN, 4)	
			/// The maximum reversed size
		,	en_max_reversed_size = EXTL_MEMORY_SCOPED_BUFFER_MAX_RESERVED_SPACE
		};
	/// @}

	/// \name Members
	/// @{
	private:
		/* data:		|-------------------------------| 
		 * size:		|---------------------|
		 * capacity:	|-------------------------------|
		 */
		pointer		m_data;					//!< The memory storage 
		size_type	m_size;					//!< The size of the used storage 
		size_type	m_capacity;				//!< The size of the reserved storage 
	/// @}

	private:
		friend class buffer_base<class_type, Actr, Mtr>;

	/// \name Constructors
	/// @{
	public:
		/// Constructs a scoped_buffer with the given number of elements
		explicit_k scoped_buffer(size_type const& n = 0, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			resize(n);
		}

		/// Constructs a scoped_buffer with n values from the given buffer at the specified position 
		scoped_buffer(const_pointer buf, size_type n, size_type pos = 0, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			base_type::assign(buf, n, pos);
		}

		/// Constructs a scoped_buffer from the given buffer 
		scoped_buffer(class_type const& buf, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{	
			this->clear();
			base_type::assign(buf, buf.size());	
		}

		/// Constructs a scoped_buffer with n values from the given buffer at the specified position 
		scoped_buffer(class_type const& buf, size_type n, size_type pos = 0, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			base_type::assign(buf, n, pos);
		}

		/// Constructs with n values
		scoped_buffer(const_reference v, size_type n, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			base_type::assign(v, n);
		}

		/// Constructs from range [first, last) with the const pointer
		scoped_buffer(const_pointer first, const_pointer last, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			base_type::assign(first, last);
		}
		/// Constructs from range [first, last) with the const iterator
		scoped_buffer(const_iterator first, const_iterator last, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			base_type::assign(first, last);
		}
		/// Constructs from range [first, last) with the const reverse iterator
		scoped_buffer(const_reverse_iterator first, const_reverse_iterator last, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			base_type::assign(first, last);
		}
	#if defined(EXTL_MEMBER_TEMPLATE_CTOR_OVERLOAD_DISCRIMINATED_SUPPORT) \
			&& !defined(EXTL_COMPILER_IS_DMC)
		/// Constructs from range [first, last) with the input iterator
		template < typename_param_k _InIt >
		scoped_buffer(_InIt first, _InIt last, initialiser_type intr = initialiser_type())
			: m_data(NULL), m_size(0), m_capacity(0), initialiser_type(intr), base_type()
		{
			this->clear();
			base_type::assign(first, last);
		}
	#endif

		/// Destructor
		~scoped_buffer() EXTL_THROW_0() 
		{
			EXTL_STATIC_ASSERT(en_grow_size < en_max_reversed_size);
			destroy();
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		/// Returns the pointer to the buffer
		pointer data()					{ return m_data;		}
		/// Returns the const pointer to the buffer
		const_pointer data()	const	{ return m_data;		}
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

			// Releases the buffer 
			if (NULL != m_data)
			{
				initialiser().destruct_n(m_data, m_size);
				base_type::allocator().deallocate(m_data);
				m_data = NULL;
			}
			m_size = 0;
			m_capacity = 0;

			EXTL_ASSERT(is_valid());
		}

		/*!\brief Resizes the size of buffer
		 *
		 * \note Only resize the capacity of the storage for reserve() when is_update_size is e_false_v
		 */
		void resize(size_type size, bool_type is_update_size = e_true_v)
		{
			EXTL_ASSERT(is_valid());

			/* Adjusts the size for avoiding to allocate memory frequently */
			size_type adjusted_size = EXTL_ALIGN(size, en_grow_size);
			EXTL_ASSERT(!(base_type::max_size() < adjusted_size));
			EXTL_ASSERT_THROW(!(base_type::max_size() < adjusted_size), std_length_error("scoped_buffer too long"));

			size_type old_size = m_size;
			size_type new_size = size;
			if (new_size > old_size)	// grow
			{
				/*!grow
				 * need not allocate memory
				 * <pre>
				 *
				 *           old size
				 *      |---------------|
				 *                 old capacity
				 *      |----------------------------------------|
				 *
				 *         old data           reserved
				 * old: |////////////////|========================|
				 * new: |////////////////|/////////|==============|
				 *         old data        new data  reversed 
				 *
				 *      |--------------------------|
				 *                new size
				 *      |-----------------------------------------|
				 *                      old capacity
				 * </pre>
				 */
				if (adjusted_size <= m_capacity)
				{
					EXTL_ASSERT(NULL != m_data);
					// construct part new storage
					initialiser().construct_n(m_data + old_size, new_size - old_size);
				}
				/*!grow
				 * null data: need allocate memory
				 * <pre>
				 *
				 * old: |
				 * new: |//////////////////////////|==============|
				 *                new data             reversed 
				 *
				 *      |--------------------------|
				 *                new size
				 *      |-----------------------------------------|
				 *                      new capacity
				 * </pre>
				 */
				else if (0 == old_size)
				{
					EXTL_ASSERT(NULL == m_data);
					// allocate new storage
					m_data = base_type::allocator().allocate(adjusted_size);
					EXTL_ASSERT(NULL != m_data);

					// construct new storage
					initialiser().construct_n(m_data, new_size);

					// update the capacity of the storage
					m_capacity = adjusted_size;
				}
				/*!grow
				 * need allocate memory
				 * <pre>
				 *
				 *           old size
				 *      |---------------|
				 *                 old capacity
				 *      |----------------------------------------|
				 *
				 *         old data           reserved
				 * old: |////////////////|========================|
				 * new: |////////////////|//////////////////|==============|
				 *         old data              new data      reversed 
				 *
				 *      |-----------------------------------|
				 *                new size
				 *      |--------------------------------------------------|
				 *                  adjusted_size(new capacity)
				 * </pre>
				 */
				else
				{
					if(allocator_traits<allocator_type>::is_support_reallocate && 
							en_is_pod) // need not construct
					{
						m_data = base_type::allocator().reallocate(m_data, adjusted_size);
					}
					else 
					{
						// allocate new storage
						pointer p = base_type::allocator().allocate(adjusted_size);
						
						EXTL_ASSERT(NULL != p);
						
						// copy old data
						// note: need not object copy
						// p point to uninitialized data, so will appear bug if use object copy
						pod_memory_traits_type::copy(p, m_data, old_size);
						
						// construct remnant new storage
						initialiser().construct_n(p + old_size, new_size - old_size);

						// deallocate old storage
						base_type::allocator().deallocate(m_data);

						// update buffer
						m_data = p;	
					}

					// update the capacity of the storage
					m_capacity = adjusted_size;
				}
			}
			else if (new_size < old_size)	// shrink
			{
				/*!shrink
				 * need not deallocate memory
				 * <pre>
				 *
				 *           old size
				 *      |---------------|
				 *                 old capacity
				 *      |-----------------------------------------|
				 *
				 *         old data           reserved
				 * old: |//////////////////////////|==============|
				 * new: |////////////////|========================|
				 *         old data          reversed 
				 *
				 *      |----------------|
				 *             new size
				 *      |-----------------------------------------|
				 *                     old capacity
				 * </pre>
				 */
				if (m_capacity <= en_max_reversed_size || adjusted_size == m_capacity)
				{
					// destruct part old storage
					initialiser().destruct_n(m_data + new_size, old_size - new_size);
				}
				/*!shrink
				 * need deallocate all memory
				 * <pre>
				 *
				 *           old size
				 *      |---------------|
				 *                 old capacity
				 *      |-----------------------------------------|
				 *
				 *             old data               reserved
				 * old: |//////////////////////////|==============|
				 * new: |
				 * </pre>
				 */
				else if (0 == new_size)
				{
					// destruct old storage
					initialiser().destruct_n(m_data, old_size);

					// deallocate old storage
					EXTL_ASSERT(NULL != m_data);
					if (NULL != m_data) 
					{
						base_type::allocator().deallocate(m_data);
						m_data = NULL;
					}
					
					// update the capacity of the storage
					m_capacity = 0;
				}
				/*!shrink
				 * need deallocate memory
				 * <pre>
				 *
				 *           old size
				 *      |---------------|
				 *                 old capacity
				 *      |-----------------------------------------|
				 *
				 *         old data           reserved
				 * old: |//////////////////////////|==============|
				 * new: |////////////////|===============|
				 *         old data          reversed 
				 *
				 *      |----------------|
				 *             new size
				 *      |--------------------------------|
				 *                     new capacity
				 * </pre>
				 */
				else
				{
					if(allocator_traits<allocator_type>::is_support_reallocate && 
							en_is_pod) // need not construct
					{
						m_data = base_type::allocator().reallocate(m_data, adjusted_size);
					}
					else 
					{
						// allocate new storage
						pointer p = base_type::allocator().allocate(adjusted_size);
						EXTL_ASSERT(NULL != p);

						// copy part old data
						// note: need not object copy
						// p point to uninitialized data, so will appear bug if use object copy
						pod_memory_traits_type::copy(p, m_data, new_size);

						// destruct remnant old storage
						initialiser().destruct_n(m_data + new_size, old_size - new_size);

						// deallocate old storage
						base_type::allocator().deallocate(m_data);

						// update buffer
						m_data = p;	
					}

					// update the capacity of the storage
					m_capacity = adjusted_size;
				}
			}
			else;	// not adjust

			if (is_update_size) m_size = new_size;

			EXTL_ASSERT(is_valid());
		}

		/// Swaps storage
		void swap(class_type& rhs) EXTL_THROW_0()
		{
			EXTL_ASSERT(is_valid());

			if (this != &rhs)
			{
				std_swap(m_data, rhs.m_data);
				std_swap(m_size, rhs.m_size);
				std_swap(m_capacity, rhs.m_capacity);
			}

			EXTL_ASSERT(is_valid());
		}
	/// @}

	// \name Helpers
	// @{
	private:
		// Invariance 
		bool_type is_valid() const
		{
			if (capacity() < size())
				return e_false_v;
			
			if ((0 < size()) && (NULL == data()))
				return e_false_v;
		
			return e_true_v;
		}

		// Returns the initialiser
		initialiser_type&		initialiser()			{ return *this;	}
		// Returns the initialiser
		initialiser_type const&	initialiser() const		{ return *this;	}
	// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_SCOPED_BUFFER_H */
/* //////////////////////////////////////////////////////////////////// */
