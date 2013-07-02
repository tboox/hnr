/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_pool.h		
 *
 * Created:		08.04.14					
 * Updated:		08.04.28	
 *
 * Brief: basic_pool class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_BASIC_POOL_H
#define EXTL_MEMORY_BASIC_POOL_H

/*!\file basic_pool.h
 * \brief basic_pool class 
 */
#ifndef __cplusplus
#	error basic_pool.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_allocator_selector.h"
#include "../type/traits/limit_traits.h" 
#include "../mpl/math/max_min.h"

#ifdef EXTL_MEMORY_BASIC_POOL_TEST_ENABLE
#	include "../counter/clock_counter.h"
#	include "../math/rand.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */

/// EXTL_BASIC_POOL_DEFAULT_MAX_FREE_UNLIMITED
#define EXTL_BASIC_POOL_DEFAULT_MAX_FREE_UNLIMITED					(0)	

/*!if EXTL_BASIC_POOL_DEFAULT_MAX_FREE_INDEX == 15
 * max_free_chunk_size = (15 + 1) * 4K = 64K
 */
#define EXTL_BASIC_POOL_DEFAULT_MAX_FREE_INDEX						(15)

/// Default alignment boundary = 2^4 = 16B 
#define EXTL_BASIC_POOL_DEFAULT_ALIGN_BOUNDARY_POWER				(4)

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief basic_pool class
 * 
 * \param A The basic allocator type
 * \param MAX_FREE_INDEX: The maximum index of a free chunk in the pool
 * \param DEFAULT_ALIGN_BOUNDARY_POWER: Default alignment boundary = 2^DEFAULT_ALIGN_BOUNDARY_POWER (B)
 *
 * \ingroup extl_group_memory
 */
template<	
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
			typename_param_k A = typename_type_def_k basic_allocator_selector<e_byte_t>::allocator_type
		,	e_size_t MAX_FREE_INDEX = EXTL_BASIC_POOL_DEFAULT_MAX_FREE_INDEX
		,	e_size_t DEFAULT_ALIGN_BOUNDARY_POWER = EXTL_BASIC_POOL_DEFAULT_ALIGN_BOUNDARY_POWER
#else
			typename_param_k A
		,	e_size_t MAX_FREE_INDEX 
		,	e_size_t DEFAULT_ALIGN_BOUNDARY_POWER
#endif
		>
class basic_pool
#ifdef EXTL_EBO_FORM_2_SUPPORT
	: protected A	/* if EBO is supported */
#endif
{
	private:
		typedef A																	base_type;
	/// \name Types
	/// @{
	public:
		typedef basic_pool<A, MAX_FREE_INDEX, DEFAULT_ALIGN_BOUNDARY_POWER >		class_type;
		typedef void																value_type;
		typedef A																	allocator_type;
		typedef void*																pointer;
		typedef void const*															const_pointer;
		typedef void																reference;
		typedef void																const_reference;
		typedef typename_type_k allocator_type::size_type							size_type;
	/// @}

	private:
		/*!\brief Prohibit copy constructor and copy assignment
		 * 
		 * Maybe EBO is not supported if uses extl::uncopyable,
		 * because some compilers do not support EBO_FORM_6 - EXTL_EBO_FORM_6_SUPPORT
		 */
		basic_pool(class_type const&);
		class_type& operator=(class_type const&);

	private:
		
		/* ///////////////////////////////////////////////////////////////////////
		 * The size of a memory page : 8K 
		 */
		enum { en_per_page_size = 8 * 1024 };
		
		/* ///////////////////////////////////////////////////////////////////////
		 * Boundary alignment
		 */
		/* Default boundary alignment : 16B = 2^4 */
		enum { en_default_boundary_power = DEFAULT_ALIGN_BOUNDARY_POWER };
		enum { en_default_boundary = 1 << en_default_boundary_power };
		
		/* The boundary size of one chunk : 4K */
		enum { en_chunk_boundary_size = en_per_page_size >> 1 };

		/* ///////////////////////////////////////////////////////////////////////
		 * Index 
		 */

		/* Used to the conversion between index and the size of the chunk in the free pool and 
		 * en_boundary_index = log2(en_per_page_size / 2)
		 *
		 * [Convertsion]
		 * index = (chunk_size >> en_boundary_index) - 1; ==> index = (chunk_size / 4K) - 1 
		 * chunk_size = (index + 1) << en_boundary_index; ==> chunk_size = (index + 1) * 4K
		 */
		enum { en_boundary_index = 12 };

		/* The maximum index of the free pool 
		 * if en_fp_max_index == 20 :
		 * max_regular_chunk_size = 8K(per_page_size) + 4K * (en_fp_max_index - 1) = 84K
		 */
		enum { en_fp_max_index = 20 };

		/* The index of the larger than en_fp_max_regular_chunk_size size 
		 * chunks linked list in the free pool
		 */
		enum { en_fp_non_regular_index = 0 };

		/* The maximum index of the free chunk
		 * When the size of a chunk is larger than index_to_size(en_fp_max_free_index), 
		 * the chunk will be destroyed at once 
		 * and if the index is equal with EXTL_BASIC_POOL_DEFAULT_MAX_FREE_UNLIMITED,
		 * the chunk will be not destroyed until the basic_pool is destroyed 
		 */
		enum { en_fp_max_free_index = MAX_FREE_INDEX };

		/* The current maximum index of the chunks linked list in the free pool
		 *  ------ ------ ------  ------ ------ ------
		 * |      |      |      |       |      |      |
		 *  ------ ------ ------  ------ ------ ------
		 *                                         |                    |
		 *                                   en_fp_max_index   en_fp_max_free_index
		 * [Result]
		 * en_fp_cur_max_index = en_fp_max_index    
		 *
		 *  ------ ------ ------  ------ ------ ------
		 * |      |      |      |       |      |      |
		 *  ------ ------ ------  ------ ------ ------
		 *                   |                     |                   
		 *        en_fp_max_free_index        en_fp_max_index   
		 * [Result]
		 * en_fp_cur_max_index = en_fp_max_free_index  
		 *                                   
		 *
		 */
		enum { en_fp_cur_max_index = 
				(en_fp_max_free_index == EXTL_BASIC_POOL_DEFAULT_MAX_FREE_UNLIMITED)?
					en_fp_max_index : (EXTL_NS_MPL(min)<en_fp_max_free_index, en_fp_max_index>::value) };

		/* Used to the conversion between index and the size of the block in the active pool  */
		enum { en_ap_max_index = (8 * 1024 / en_default_boundary) };
		enum { en_ap_larger_blocks_index = en_ap_max_index - 1 };
		enum { en_ap_non_free_index = 0 };

	private:
		/// The index of the free pool is converted to the size of the chunk 
		static size_type index_to_size(size_type index)
		{	
			EXTL_ASSERT(0 < index);
			return ((index + 1) << en_boundary_index);
		}
		/// The size of the chunk is converted to the index of the free pool 
		static size_type size_to_index(size_type size)	
		{	
			EXTL_ASSERT(en_per_page_size <= size);
			return ((size >> en_boundary_index) - 1);
		}

		/// Deafult boundary alignment 
		static size_type default_align(size_type size)
		{	
			return EXTL_ALIGN(size, en_default_boundary);
		}

	private:
		enum { en_block_head_size = sizeof(size_type) }; 
		/*!\brief The block type
		 * The linked node of the free blocks in one chunk 
		 * <pre>
		 *  ------ ------ ------  ------ ------ ------
		 * |      |      |      |       |      |      | - m_active_pool
		 *  ------ ------ ------  ------ ------ ------
		 *  block_head:             |
		 *  --------------          |
	     * |   ap_index   |  -------
		 *  --------------   <-- data()  
		 * |     next     |  ---------------> next block
		 *  --------------    
		 * |              |   
		 * |              |
		 * |              |  
		 *  --------------     
		 * </pre>
		 */
		struct block_head
		{ 
			/// \name Members
			/// @{
			size_type			ap_index; 
			block_head*			next; 
			/// @}

			/// \name Methods
			/// @{
			pointer				data()							{ return reinterpret_cast<pointer>(&next);						}
			size_type			get_ap_index() const			{ return ap_index;												}
			void				set_ap_index(size_type index)	{ ap_index = index;												}
			static block_head*	get_block(pointer p)			{ return reinterpret_cast<block_head*>(static_cast<e_byte_t*>(p) - en_block_head_size);	}
			/// @}
		};
		friend struct block_head;

		/*!\brief The chunk type 
		 * A memory chunk node 
		 * <pre>
		 * next: pointer to the next chunk
		 * index: (chunk_size >> boundary_index) - 1
		 *
		 *  --------------              --------------
		 * |     next     | ---------> |              | ----------> ... ----------> NULL
		 *  --------------             |              |
		 * |     index    |            |              |
		 *  --------------             | chunk_head2  |
		 * |  block_size  |            |              |
		 *  --------------             |              |
		 * |  free_count  |            |              |
		 *  --------------             |              |
		 * |   reserve1   |            |              |
		 *  --------------             |              |
		 * |  first_free  | ---        |              |
		 *  --------------     |       |              |
		 * |  last_free   | ---|--     |              |
		 *  --------------     |  |     --------------
		 * |              |  <-   |
		 * |              |       |
		 * | free blocks  |       |
		 * |              |       |
		 * |              |  <----
		 *  --------------
		 *
		 * [size]
		 *  --------------                                   -
		 * |  chunk_head  |                                   |
		 *  --------------   <- first_free   -                |
		 * |  free_block1 |  --               | block_size    |
		 *  --------------     |             -                |
		 * |  free_block2 |  --                               | chunk size
		 *  --------------     |                              |
		 * |  free_block3 |  --                               |
		 *  --------------   <-| last_free                    |
		 * |  free_block4 |  --                               |
		 *  --------------     |                             -
		 *       NULL        <-
		 * </pre>
		 */
		struct chunk_head
		{
			/// \name Members
			/// @{
			chunk_head*		next;
			size_type		index;	
			size_type		block_size;
			size_type		free_count;
			size_type		reserve1;
			block_head*		first_free;
			block_head*		last_free;
			/// @}

			/// The bit count of the mask in the reserve1 
			enum mask1_bit_count
			{ 
				/// Does allocate free blocks by linked list? 
				en_is_alloc_by_linked_list = 0
			};

			/// \name Methods
			/// @{
			/// Allocates free blocks by linked list 
			e_bool_t is_alloc_by_linked_list() const	{ return 1 == (reserve1 & (1 << en_is_alloc_by_linked_list));					}
			void enable_alloc_by_linked_list()			{ reserve1 |= (1 << en_is_alloc_by_linked_list);								}
			void disable_alloc_by_linked_list() 		{ reserve1 &= ~(1 << en_is_alloc_by_linked_list);								}

			size_type		chunk_size() const				{ return index_to_size(index);													}
			size_type		data_size() const				{ return (chunk_size() - sizeof(chunk_head));									}
			size_type		block_count() const				{ return (data_size() / block_size);											}
			e_byte_t*		data()							{ return reinterpret_cast<e_byte_t*>(&((this)[1]));								}
			block_head*		first_block()					{ return reinterpret_cast<block_head*>(data());										}
			block_head*		last_block()					{ return reinterpret_cast<block_head*>(data() + (block_count() - 1) * block_size);	}
			e_bool_t		is_free() const					{ return free_count == block_count();											}
			
			/// Returns true if the block in the chunk 
			e_bool_t is_in_chunk(block_head const* block) const
			{
				EXTL_ASSERT(NULL != block);
				if (reinterpret_cast<e_byte_t const*>(this) < reinterpret_cast<e_byte_t const*>(block) && 
					reinterpret_cast<e_byte_t const*>(block) < (reinterpret_cast<e_byte_t const*>(this) + chunk_size()))
					return e_true_v;
				else return e_false_v;
			}
			/// @}
		
		};
		friend struct chunk_head;

		/// The snapshot info of the pool 
		struct snapshot_info
		{
			/// \name Members
			/// @{
			size_type							cur_alloc_size_from_system;
			size_type							cur_alloc_size_from_pool;
			/// @}
		};

	/// \name Members
	/// @{
	private:
		/*!\brief free pool 
		 * <pre>
		 * index:             0             1             2                      ... ...                  en_fp_max_index - 1
		 * chunk_size:     larger          8K        8K + 4K * 1  8K + 4K * 2                             8K + 4K * (index - 1)
		 *              ------------- ------------- ------------- -------------             ------------- -------------
		 *             |             |             |             |               ... ...                 |             |
		 *              ------------- ------------- ------------- -------------             ------------- -------------
		 *                    |             |             |             |                         |             |
		 *              ------------- -------------                                                       -------------
		 *             |    chunk1   |             |                             ... ...                 |             |
		 *              ------------- -------------                                                       -------------
 		 *                    |             |                                                                   |
		 *              ------------- -------------                                                            NULL
		 *             |    chunk2   |             |
		 *              ------------- -------------
		 *                    |             |
		 *                   NULL     -------------
		 *                           |             |
		 *                            -------------
		 *                                  |
		 *                                 NULL
		 * Note:         non-regular     regular                                 ... ...       regular        regular
		 *             descending order
		 * </pre>
		 */

		/*!\brief active pool 
		 * <pre>
		 * en_default_boundary = 16
		 *
		 * index:             0             1             2                      ... ...                  en_ap_max_index - 1
		 * block_size:     unknown         16B         16B * 2        16B * 3                 16B * index  en_ap_larger_blocks_index         
		 *              ------------- ------------- ------------- -------------             ------------- -------------
		 *             |             |             |             |               ... ...                 |             |
		 *              ------------- ------------- ------------- -------------             ------------- -------------
		 *                    |             |             |             |                         |             |
		 *              ------------- -------------                                                       -------------
		 *             |    chunk1   |             |                             ... ...                 |             |
		 *              ------------- -------------                                                       -------------
 		 *                    |             |                                                                   |
		 *              ------------- -------------                                                            NULL
		 *             |    chunk2   |             |
		 *              ------------- -------------
		 *                    |             |
		 *                   NULL     -------------
		 *                           |             |
		 *                            -------------
		 *                                  |
		 *                                 NULL
		 *
		 * Note:          non-free     partial free                              ... ...     partial free  partial free
		 *             (only a block)                                                                      ascending order 
		 * </pre>
		 */
		chunk_head*								m_free_pool[en_fp_max_index];
		chunk_head*								m_active_pool[en_ap_max_index];
	/// @}
		
	private:
		/// Initialize a free chunk 
		void init_free_chunk(chunk_head* free_chunk, size_type block_size);


		/// Allocates a free block from the partial-free chunk 
		block_head* alloc_block_from_free_chunk(chunk_head* free_chunk);
		/// Allocates a free chunk from the free pool 
		chunk_head* alloc_chunk_from_free_pool(size_type chunk_size);


		/// Deallocates a block to the chunk 
		void dealloc_block_to_chunk(block_head* block, chunk_head* chunk);
		/// Deallocates a allocated chunk to the free pool 
		void dealloc_chunk_to_free_pool(chunk_head* chunk);
		/// Deallocates a block from the given index of the active pool 
		e_bool_t dealloc_block_from_active_index(pointer block, size_type index);


		/// Adds a chunk to the active pool and returns the index in the active pool 
		size_type add_chunk_to_active_pool(chunk_head* chunk);

	/// \name Constructors
	/// @{
	public:
		basic_pool()
		{
			EXTL_STATIC_ASSERT(en_ap_max_index >= 2);
			EXTL_STATIC_ASSERT(en_fp_max_index >= 2);

			/* Creates the basic_pool */
			create();
		}
		~basic_pool()
		{
			/* Destroys the basic_pool */
			destroy();
		}
	/// @}
		
	public:
		allocator_type allocator() const
		{
		#ifdef EXTL_EBO_FORM_2_SUPPORT
			return *this;
		#else
			return allocator_type();
		#endif
		}

		/// Creates the basic_pool 
		void create();

		/// Destroys the basic_pool 
		void destroy();

		/// Shrinks the basic_pool 
		void shrink();

		/// Allocates memory block of the specified size 
		pointer allocate(size_type size);

		/// Reallocates memory block of the specified size 
		pointer reallocate(pointer block, size_type size);
		
		/// Deallocates the block to pool 
		void deallocate(pointer block);

	public:
		/// Creates a snapshot of the pool 
		snapshot_info							get_snapshot() const;
		
};

/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */

/* Template declaration */
#ifdef EXTL_BASIC_POOL_TEMPLATE_DECL
#	undef EXTL_BASIC_POOL_TEMPLATE_DECL
#endif

#define EXTL_BASIC_POOL_TEMPLATE_DECL					\
template<	typename_param_k A							\
		,	e_size_t MAX_FREE_INDEX						\
		,	e_size_t DEFAULT_ALIGN_BOUNDARY_POWER			\
		>

/* Class qualification */
#ifdef EXTL_BASIC_POOL_CLASS_QUAL
#	undef EXTL_BASIC_POOL_CLASS_QUAL
#endif

#define EXTL_BASIC_POOL_CLASS_QUAL	basic_pool<A, MAX_FREE_INDEX, DEFAULT_ALIGN_BOUNDARY_POWER>

/* Class qualification */
#ifdef EXTL_BASIC_POOL_CLASS_RET_QUAL
#	undef EXTL_BASIC_POOL_CLASS_RET_QUAL
#endif

#define EXTL_BASIC_POOL_CLASS_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_BASIC_POOL_CLASS_QUAL::ret_type \
					EXTL_BASIC_POOL_CLASS_QUAL
/* ///////////////////////////////////////////////////////////////////////
 * Class implemention
 */

/* Creates the basic_pool */
EXTL_BASIC_POOL_TEMPLATE_DECL
inline void EXTL_BASIC_POOL_CLASS_QUAL::create()
{
	mem_fill_0(m_free_pool, en_fp_max_index * sizeof(chunk_head*));
	mem_fill_0(m_active_pool, en_ap_max_index * sizeof(chunk_head*));
}
/* Destroys the basic_pool */
EXTL_BASIC_POOL_TEMPLATE_DECL
void EXTL_BASIC_POOL_CLASS_QUAL::destroy()
{
	size_type index;

	/*!Frees all chunks in the active pool to system */
	for(index = 0; index < en_ap_max_index; index++)
	{
		chunk_head*	node = m_active_pool[index];
		while(NULL != node) 
		{
			chunk_head*	pre_node = node;
			node = node->next;
			allocator().deallocate(reinterpret_cast<e_byte_t*>(pre_node));
		}
		m_active_pool[index] = NULL;
	}

	/*!Frees all chunks in the free pool to system */
	for(index = 0; index < en_fp_cur_max_index; index++)
	{
		chunk_head*	node = m_free_pool[index];
		while(NULL != node) 
		{
			chunk_head*	pre_node = node;
			node = node->next;
			allocator().deallocate(reinterpret_cast<e_byte_t*>(pre_node));
		}
		m_free_pool[index] = NULL;
	}
}
/* Shrinks the basic_pool */
EXTL_BASIC_POOL_TEMPLATE_DECL
void EXTL_BASIC_POOL_CLASS_QUAL::shrink()
{
	/* Frees all chunks in the free pool to system */
	for(size_type index = 0; index < en_fp_cur_max_index; index++)
	{
		chunk_head*	node = m_free_pool[index];
		while(NULL != node) 
		{
			chunk_head*	pre_node = node;
			node = node->next;
			allocator().deallocate(reinterpret_cast<e_byte_t*>(pre_node));
		}
		m_free_pool[index] = NULL;
	}
}
/* Allocates memory block of the specified size */
EXTL_BASIC_POOL_TEMPLATE_DECL
EXTL_BASIC_POOL_CLASS_RET_QUAL(pointer)::allocate(size_type size)
{
	if (0 == size) return NULL;

	/*!Default: the eight-byte alignment */
	size += en_block_head_size;
	if(size < sizeof(block_head)) size = sizeof(block_head);
	size_type block_size = default_align(size);
	EXTL_ASSERT(0 == block_size % en_default_boundary);
	EXTL_ASSERT(size <= block_size);

	/*!index = block_size / 16 if en_default_boundary == 16 */
	size_type index = block_size >> en_default_boundary_power;
	EXTL_ASSERT((0 < index) && (index <= EXTL_LIMIT_TRAITS_UINT32_MAX));
#if 0
	/*!Allocates a free block from the active pool */
	if (index > en_ap_larger_blocks_index) index = en_ap_larger_blocks_index;
	EXTL_ASSERT(0 != index);
	chunk_head* node = m_active_pool[index];
	while(NULL != node)
	{
		if (NULL != node->first_free && block_size <= node->block_size)
		{
			/* Allocates a free block from the free chunk */
			block_head* block = alloc_block_from_free_chunk(node);
			if(NULL != block) block->set_ap_index(index);

			EXTL_ASSERT(size <= node->block_size);
			return block->data();
		}
		node = node->next;
	}
#else /* The optimization of the above code */
	/*!Allocates a free block from the active pool */
	if (index < en_ap_larger_blocks_index) 
	{
		EXTL_ASSERT(0 != index);
		chunk_head* node = m_active_pool[index];
		while(NULL != node)
		{
			if (NULL != node->first_free)
			{
				/* Allocates a free block from the free chunk */
				block_head* block = alloc_block_from_free_chunk(node);
				if(NULL != block) block->set_ap_index(index);

				EXTL_ASSERT(size <= node->block_size);
				return block->data();
			}
			node = node->next;
		}
	}
	else 
	{
		chunk_head* node = m_active_pool[en_ap_larger_blocks_index];
		while(NULL != node)
		{
			if (NULL != node->first_free && block_size <= node->block_size)
			{
				/* Allocates a free block from the free chunk */
				block_head* block = alloc_block_from_free_chunk(node);
				if(NULL != block) block->set_ap_index(en_ap_larger_blocks_index);

				EXTL_ASSERT(size <= node->block_size);
				return block->data();
			}
			node = node->next;
		}
	
	}
#endif
	/*!Adjusts the size of a free chunck
	 * <pre>
	 * [Default]
	 * 8K, 8K + 4K * 1, 8K + 4K * 2, ..., 8K + 4K * n
	 * [Note]
	 * per-page size: 8K
	 * </pre>
	 */
	size_type chunk_size = EXTL_ALIGN(sizeof(chunk_head) + block_size, en_chunk_boundary_size);
	if (chunk_size < en_per_page_size) chunk_size = en_per_page_size;

	/*!Allocates a free chunk from the free pool 
	 * Note: Maybe new_chunk->chunk_size() != chunk_size 
	 */
	chunk_head* new_chunk = alloc_chunk_from_free_pool(chunk_size); 
	EXTL_ASSERT(NULL != new_chunk);

#if 0

	/* Initializes the free chunk */
	init_free_chunk(new_chunk, block_size);

	/* Allocates a free block from the free chunk */
	block_head* block = alloc_block_from_free_chunk(new_chunk);

#else /* The optimization of the above code */

	EXTL_ASSERT(block_size <= new_chunk->chunk_size());
	EXTL_ASSERT(sizeof(block_head) <= block_size);

	/*!Initializes the free chunk */
	new_chunk->block_size = block_size;
	new_chunk->free_count = (new_chunk->chunk_size() - sizeof(chunk_head)) / block_size;
	EXTL_ASSERT(0 < new_chunk->free_count);

	/*!Allocates a free block from the free chunk */
	block_head* block = new_chunk->first_block();
	new_chunk->last_free = reinterpret_cast<block_head*>(reinterpret_cast<e_byte_t*>(block) + (new_chunk->free_count - 1) * block_size);
	new_chunk->last_free->next = NULL;

	/*!Delay to segregate a chunk */
	if (1 == new_chunk->free_count)
	{
		new_chunk->first_free = NULL;
		new_chunk->last_free = NULL;
		new_chunk->enable_alloc_by_linked_list();
	}
	else
	{
		new_chunk->first_free = reinterpret_cast<block_head*>(reinterpret_cast<e_byte_t*>(block) + block_size);
		if (new_chunk->first_free == new_chunk->last_free) 
			new_chunk->enable_alloc_by_linked_list();
		else new_chunk->disable_alloc_by_linked_list();
	}
	--new_chunk->free_count;
	
#endif
	/*!Adds the chunk to the active pool */
	block->set_ap_index(add_chunk_to_active_pool(new_chunk));

	return block->data();
}
/* Adds a chunk to the active pool and returns the index in the active pool */
EXTL_BASIC_POOL_TEMPLATE_DECL
EXTL_BASIC_POOL_CLASS_RET_QUAL(size_type)::add_chunk_to_active_pool(chunk_head* chunk)
{
	EXTL_ASSERT(NULL != chunk);
	/*!Puts the chunk to m_active_pool[en_ap_non_free_index] 
	 * if there is only one block which has been allocated in the chunk
	 * <pre>
	 * [chunk]
	 *  --------------
	 * |  chunk_head  |
	 *  --------------   <- first_free
	 * |  free_block1 |  --
	 *  --------------     |
	 *       NULL        <-
	 * </pre>
	 */
	if (NULL == chunk->first_free) 
	{
		EXTL_ASSERT(0 == chunk->free_count);
		chunk->next = m_active_pool[en_ap_non_free_index];
		m_active_pool[en_ap_non_free_index] = chunk;
		return en_ap_non_free_index;
	}
	/* Puts the chunk to m_active_pool[index] */
	else
	{
		/*!index = block_size / 8 if en_default_boundary == 8 */
		size_type index = chunk->block_size >> en_default_boundary_power;
		EXTL_ASSERT((0 < index) && (index <= EXTL_LIMIT_TRAITS_UINT32_MAX));

		/* smaller block in the chunk */
		if (index < en_ap_larger_blocks_index)
		{
			chunk->next = m_active_pool[index];
			m_active_pool[index] = chunk;
			return index;
		}
		/*!larger block in the chunk
		 * The chunks in the m_active_pool[en_ap_larger_blocks_index] is sorted by the size of a block in the ascending order
		 * <pre>
		 * m_active_pool[en_ap_larger_blocks_index]
		 *                |
		 *  ---------   <-  
		 * |  chunk1 |  --   eg: block_size = 1
		 *  ---------     |
		 * |  chunk2 |  --   eg: block_size = 2
		 *  ---------     |                      <- insert a chunk
		 * |  chunk3 |  --   eg: block_size = 3
		 *  ---------     |
		 * |  chunk4 |  --   eg: block_size = 4
		 *  ---------     |
		 * |  chunk5 |  --   eg: block_size = 5
		 *  --------------     |
		 *       NULL        <-
		 * </pre>
		 */
		else
		{
			chunk_head* node = m_active_pool[en_ap_larger_blocks_index];
			if (NULL != node)
			{
				chunk_head* pre_node = node;
				while(NULL != node && node->block_size < chunk->block_size) 
				{
					pre_node = node;
					node = node->next;
				}
				chunk->next = pre_node->next;
				pre_node->next = chunk;
			}
			else
			{
				m_active_pool[en_ap_larger_blocks_index] = chunk;
				chunk->next = NULL;
			}
			return en_ap_larger_blocks_index;
		}
	}

}
/* Allocates a free chunk from the free pool */
EXTL_BASIC_POOL_TEMPLATE_DECL
EXTL_BASIC_POOL_CLASS_RET_QUAL(chunk_head*)::alloc_chunk_from_free_pool(size_type chunk_size)
{
	EXTL_ASSERT(sizeof(chunk_head) < chunk_size);
	/*!<pre>
	 * index = chunk_size / 4K - 1
	 * [chunk size]
	 * 8K, 8K + 4K * 1, 8K + 4K * 2, ..., 8K + 4K * n
	 * [index]
	 * 1,  2,         , 3,         , ..., n + 1
	 * [Note]
	 * per-page size: 8K
	 * </pre>
	 */
	size_type index = size_to_index(chunk_size);
	EXTL_ASSERT((0 < index) && (index <= EXTL_LIMIT_TRAITS_UINT32_MAX));

	/*!Finds a regular chunk
	 * <pre>
	 * [chunk size]
	 * 8K, 8K + 4K * 1, 8K + 4K * 2, ..., 8K + 4K * n
	 * -----> find
	 * </pre>
	 */
	for(size_type i = index; i < en_fp_cur_max_index; i++)
	{
		/* Non-empty linked list */
		if (NULL != m_free_pool[i])
		{
			chunk_head* node = m_free_pool[i];
			m_free_pool[i] = m_free_pool[i]->next;
			node->next = NULL;
			EXTL_ASSERT(node->index == i);
			return node;
		}
	}

	/*!Finds a non-regular chunk 
	 * <pre>
	 * index = en_fp_non_regular_index = 0
	 * [Note]
	 * The size of a non-regular chunk is larger than a regular chunk
	 * </pre>
	 */
	chunk_head* node = m_free_pool[en_fp_non_regular_index];
	if (NULL != node && index <= node->index) /* chunk_size <= node->chunk_size() */
	{
		m_free_pool[en_fp_non_regular_index] = node->next;
		node->next = NULL;
		EXTL_ASSERT(node->index == en_fp_non_regular_index);
		return node;
	}

	/*!Allocates a new chunk 
	 * if there is not a chunk of the appropriate size in the free pool 
	 */
	node = reinterpret_cast<chunk_head*>(allocator().allocate(chunk_size));
	EXTL_ASSERT(NULL != node);
	node->next = NULL;
	node->index = index;

	return node;
}
/* Initialize a free chunk */
EXTL_BASIC_POOL_TEMPLATE_DECL
inline void EXTL_BASIC_POOL_CLASS_QUAL::init_free_chunk(chunk_head* free_chunk, size_type block_size)
{
	EXTL_ASSERT(NULL != free_chunk);
	EXTL_ASSERT(block_size <= free_chunk->chunk_size());
	EXTL_ASSERT(sizeof(block_head) <= block_size);

	free_chunk->block_size = block_size;
	free_chunk->free_count = free_chunk->block_count();
	free_chunk->first_free = free_chunk->first_block();
	free_chunk->last_free = free_chunk->last_block();
	free_chunk->last_free->next = NULL;
	free_chunk->disable_alloc_by_linked_list();
}
/* Allocates a free block from the partial-free chunk */
EXTL_BASIC_POOL_TEMPLATE_DECL
inline EXTL_BASIC_POOL_CLASS_RET_QUAL(block_head*)::alloc_block_from_free_chunk(chunk_head* free_chunk)
{
	EXTL_ASSERT(NULL != free_chunk);
	EXTL_ASSERT(NULL != free_chunk->first_free);
	EXTL_ASSERT(0 < free_chunk->free_count);

	block_head* block = free_chunk->first_free;

	if (free_chunk->is_alloc_by_linked_list() || free_chunk->free_count <= 1)
	{
		/*!<pre>
		 * --------------                             
		 * |  chunk_head  |                             
		 *  --------------    
		 * |  free_block1 |              
		 *  --------------  <- first_free           
		 * |  free_block2 | --                
		 *  --------------    |                            
		 * |  free_block3 |   |                             
		 *  --------------  <- next_free           
		 * |  free_block4 |                                 
		 *  --------------                                
		 *       NULL    
		 * </pre>
		 */  
		free_chunk->first_free = free_chunk->first_free->next;
	}
	else 
	{
		/*!Delay to segregate a chunk for optimization
		 * 
		 * The chunk is not segregated until a block in the chunk is allocated
		 * and the chunk will be segregated completely when first_free is pointed to the last block,
		 * then the blocks in the chunk will be allocated by linked list
		 * <pre>
		 *  --------------                             
		 * |  chunk_head  |                             
		 *  --------------    
		 * |  free_block1 |              
		 *  --------------  <- first_free           
		 * |  free_block2 |                +  block_size
		 *  --------------  <- next_free                                
		 * |  free_block3 | 
		 *  --------------    
		 * |  free_block4 |   
		 *  --------------  <- first_free (complete to segregate)         
		 * |  free_block5 |                                 
		 *  --------------                             
		 *       NULL       
		 * </pre>
		 */  
		EXTL_ASSERT(1 < free_chunk->free_count);
		free_chunk->first_free = reinterpret_cast<block_head*>
			(reinterpret_cast<e_byte_t*>(free_chunk->first_free) + free_chunk->block_size);
		if (free_chunk->first_free == free_chunk->last_block())
			free_chunk->enable_alloc_by_linked_list();
	
	};

	if (NULL == free_chunk->first_free) free_chunk->last_free = NULL;

	EXTL_ASSERT(free_chunk->free_count > 0);
	--free_chunk->free_count;

	return block;
}

/*!Deallocates the chunk to the pool 
 *  
 * <pre>
 * active pool:
 *
 * index:                0             1             2                      ... ...                        
 *                 ------------- ------------- ------------- -------------             ------------- -------------
 *           ---->|             |             |             |               ... ...                 |             |
 *          |      ------------- ------------- ------------- -------------             ------------- -------------
 *          |            |          
 * ap_index |----  ------------- 
 * ap_index |---- |    chunk1   | 
 *          |      -------------
 *          |            |            
 * ap_index |----  -------------                                     
 * ap_index |---- |    chunk2   |           
 *                 ------------- 
 *                       |         
 *                      NULL     
 *
 * </pre>
 */
EXTL_BASIC_POOL_TEMPLATE_DECL
void EXTL_BASIC_POOL_CLASS_QUAL::deallocate(pointer p)
{
	if (NULL == p) return ;
	block_head* block = block_head::get_block(p);
	EXTL_ASSERT(NULL != block);

	size_type index = block->get_ap_index();
	EXTL_ASSERT(index >= 0 && index < en_ap_max_index);

	chunk_head*	node = m_active_pool[index];
	chunk_head* pre_node = node;

	while(NULL != node) 
	{
		if (node->is_in_chunk(block))
		{
			EXTL_ASSERT(((reinterpret_cast<e_byte_t*>(block) - 
							reinterpret_cast<e_byte_t*>(node) - 
								sizeof(chunk_head)) % node->block_size) == 0);

			dealloc_block_to_chunk(block, node);

			/*!Removes the chunk from the active pool 
			 * and puts the chunk to the free pool if the chunk is free. 
			 */
			if (node->is_free())
			{
				/*!Removes the chunk from the active pool */
				if (pre_node == node) m_active_pool[index] = node->next; /* Remove the head node */
				else pre_node->next = node->next;	

				/*!Deallocates the chunk to the free pool */
				dealloc_chunk_to_free_pool(node);
			}
			return ;
		}
		pre_node = node;
		node = node->next;
	}
}
/* Dealocates a allocated chunk to the free pool */
EXTL_BASIC_POOL_TEMPLATE_DECL
void EXTL_BASIC_POOL_CLASS_QUAL::dealloc_chunk_to_free_pool(chunk_head* chunk)
{
	EXTL_ASSERT(NULL != chunk);
	EXTL_ASSERT(chunk->is_free());

	size_type index = chunk->index;
	EXTL_ASSERT((0 < index) && (index <= EXTL_LIMIT_TRAITS_UINT32_MAX));
	
	/*!Frees the chunk to system if the size of the chunk is larger than index_to_size(en_fp_max_free_index).
	 * Does't free the chunk until the pool is destroyed, if en_fp_max_free_index == en_fp_max_free_unlimited.
	 */
	if ((index >= en_fp_max_free_index) && 
		(en_fp_max_free_index != EXTL_BASIC_POOL_DEFAULT_MAX_FREE_UNLIMITED))
	{
		allocator().deallocate(reinterpret_cast<e_byte_t*>(chunk));
	}
	/*!Frees the regular chunk to the free pool */
	else if (index < en_fp_cur_max_index)
	{
		EXTL_ASSERT(index != en_fp_non_regular_index);
		chunk->next = m_free_pool[index];
		m_free_pool[index] = chunk;
	}
	/*!Frees the non-regular chunk to the free pool 
	 * and the non-chunks in the free pool is sorted in descending order by the size of a chunk.
	 * <pre>
	 *  m_free_pool[0]   --
	 *                     |
	 *  --------------   <-  
	 * |  free_chunk1 |  --   eg: size = 10
	 *  --------------     |
	 * |  free_chunk2 |  --   eg: size = 8
	 *  --------------     |                <- insert a non-regular chunk
	 * |  free_chunk3 |  --   eg: size = 5
	 *  --------------     |
	 * |  free_chunk4 |  --   eg: size = 3
	 *  --------------     |
	 * |  free_chunk5 |  --   eg: size = 1
	 *  --------------     |
	 *       NULL        <-
	 * </pre>
	 */
	else
	{
		chunk_head* node = m_free_pool[en_fp_non_regular_index];
		
		if (NULL != node)
		{
			/* Finds the position where the chunk will be inserted */
			chunk_head* pre_node = node;
			while(NULL != node && node->index > index) 
			{
				pre_node = node;
				node = node->next;
			}
			node = pre_node;
			
			/* Inserts the chunk */
			chunk->next = node->next;
			node->next = chunk;
		}
		else
		{
			/* Inserts the chunk into the head of m_free_pool[en_fp_non_regular_index] */
			chunk->next = NULL;
			m_free_pool[en_fp_non_regular_index] = chunk;
		}
	}
}
/* Deallocates a block to the chunk */
EXTL_BASIC_POOL_TEMPLATE_DECL
inline void EXTL_BASIC_POOL_CLASS_QUAL::dealloc_block_to_chunk(block_head* block, chunk_head* chunk)
{
	EXTL_ASSERT(NULL != chunk);
	EXTL_ASSERT(NULL != block);
	EXTL_ASSERT(chunk->is_in_chunk(block));

	block->next = NULL;

	if (NULL == chunk->last_free)
	{
		EXTL_ASSERT(NULL == chunk->first_free);
		chunk->last_free = block;
		chunk->first_free = block;
	}
	else
	{
		chunk->last_free->next = block;
		chunk->last_free = block;
	}

	EXTL_ASSERT(chunk->free_count < chunk->block_count());
	++chunk->free_count;
}

/* Reallocates memory block of the specified size */
EXTL_BASIC_POOL_TEMPLATE_DECL
EXTL_BASIC_POOL_CLASS_RET_QUAL(pointer)::reallocate(pointer p, size_type size)
{
	if (NULL == p) return NULL;
	block_head* block = block_head::get_block(p);
	EXTL_ASSERT(NULL != block);

	size_type index = block->get_ap_index();
	EXTL_ASSERT(index >= 0 && index < en_ap_max_index);

	chunk_head*	node = m_active_pool[index];
	chunk_head* pre_node = node;
	while(NULL != node) 
	{
		if (node->is_in_chunk(block))
		{
			if (size <= node->block_size - en_block_head_size)
				return p;
			else if (node->block_count() == 1 && 
					size <= node->data_size() - en_block_head_size)
				return p;
			else
			{
				/* Allocates a new block */
				pointer p = allocate(size);

				EXTL_ASSERT(NULL != p);
				mem_copy(p, block->data(), node->block_size - en_block_head_size);
				
				/* Deallocate the block */
				dealloc_block_to_chunk(block, node);
				if (node->is_free())
				{
					/* Removes the chunk from the active pool */
					if (pre_node == node) m_active_pool[index] = NULL;
					else pre_node->next = node->next;	

					/* Deallocates the chunk to the free pool */
					dealloc_chunk_to_free_pool(node);
				}
				return p;
			}
		}
		pre_node = node;
		node = node->next;
	}
	
	return p;
}

/* Creates a snapshot of the pool */
EXTL_BASIC_POOL_TEMPLATE_DECL
EXTL_BASIC_POOL_CLASS_RET_QUAL(snapshot_info)::get_snapshot() const
{
	snapshot_info cur_snapshot_info;
	mem_fill_0(&cur_snapshot_info, sizeof(snapshot_info));

	size_type index;

	/* the snapshot info of the active pool */
	for(index = 0; index < en_ap_max_index; index++)
	{
		chunk_head*	node = m_active_pool[index];
		while(NULL != node) 
		{
			cur_snapshot_info.cur_alloc_size_from_system += node->chunk_size();
			cur_snapshot_info.cur_alloc_size_from_pool += node->block_size * (node->block_count() - node->free_count);
			node = node->next;
		}
	}

	/* the snapshot info of the free pool */
	for(index = 0; index < en_fp_cur_max_index; index++)
	{
		chunk_head*	node = m_free_pool[index];
		while(NULL != node) 
		{
			cur_snapshot_info.cur_alloc_size_from_system += node->chunk_size();
			node = node->next;
		}
	}

	return cur_snapshot_info;
}

/* ///////////////////////////////////////////////////////////////////////
 * Undefine macros
 */
#undef EXTL_BASIC_POOL_TEMPLATE_DECL
#undef EXTL_BASIC_POOL_CLASS_QUAL
#undef EXTL_BASIC_POOL_CLASS_RET_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * some basic_pool type
 */
/// default_basic_pool
typedef basic_pool	<	basic_allocator_selector<e_byte_t>::allocator_type
					,	EXTL_BASIC_POOL_DEFAULT_MAX_FREE_INDEX
					,	EXTL_BASIC_POOL_DEFAULT_ALIGN_BOUNDARY_POWER
					>	default_basic_pool;
/// fast_basic_pool
typedef basic_pool	<	basic_allocator_selector<e_byte_t>::allocator_type
					,	EXTL_BASIC_POOL_DEFAULT_MAX_FREE_UNLIMITED
					,	4		/* Default alignment boundary: 16 = 2^4 */
					>	fast_basic_pool;
/// spare_basic_pool
typedef basic_pool	<	basic_allocator_selector<e_byte_t>::allocator_type
					,	15		/* max_free_chunk_size = (15 + 1) * 4K = 64K */
					,	3		/* Default alignment boundary: 8 = 2^8 */
					>	spare_basic_pool;
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_BASIC_POOL_TEST_ENABLE
#	include "unit_test/basic_pool_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_BASIC_POOL_H */
/* //////////////////////////////////////////////////////////////////// */
