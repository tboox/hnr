/* ///////////////////////////////////////////////////////////////////////
 * File:		fixed_pool.h		
 *
 * Created:		08.04.14					
 * Updated:		08.05.01	
 *
 * Brief: fixed_pool class - allocate a fixed-size memory block every once
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_FIXED_POOL_H
#define EXTL_MEMORY_FIXED_POOL_H

/*!\file fixed_pool.h
 * \brief fixed_pool class - allocate a fixed-size memory block every once
 *
 * Note: The size of a block must be less than 8K
 *
 */
#ifndef __cplusplus
#	error fixed_pool.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "allocator_selector.h"
#include "../utility/suppress_unused.h"

#ifdef EXTL_MEMORY_FIXED_POOL_TEST_ENABLE
#	include "../counter/clock_counter.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Macros
 */
/// Slightly less than 8K so that a chunk in the basic_pool will fit in 8K 
#define EXTL_FIXED_POOL_DEFAULT_CHUNK_SIZE	(8 * 1024 - 64)
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief fixed_pool class
 * 
 * \param BLOCK_SIZE The size of the fixed memory block
 * \param CHUNK_SIZE The size of a chunk
 * \param A The allocator type
 *
 * [Structure]
 *
 *               --------------------      --------------------
 * m_chunks ---> |      chunk1      | ---> |      chunk2      | ---> NULL
 *               --------------------      --------------------
 *                       ¡ý
 *			                    -------------------------------
 * one chunk: m_first_free --> |    block1    -|->   block2   -|-> NULL
 *                              -------------------------------
 *
 * \ingroup extl_group_memory
 */
template<	e_size_t BLOCK_SIZE
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	e_size_t CHUNK_SIZE = EXTL_FIXED_POOL_DEFAULT_CHUNK_SIZE
		,	typename_param_k A = typename_type_def_k allocator_selector<e_byte_t>::allocator_type	
#else
		,	e_size_t CHUNK_SIZE
		,	typename_param_k A
#endif
		>
class fixed_pool
#ifdef EXTL_EBO_FORM_2_SUPPORT
	: protected A	/* if EBO is supported */
#endif
{
	private:
		typedef A													base_type;
	/// \name Types
	/// @{
	public:
		typedef fixed_pool<BLOCK_SIZE, CHUNK_SIZE, A>				class_type;
		typedef void												value_type;
		typedef A													allocator_type;
		typedef void*												pointer;
		typedef void const*											const_pointer;
		typedef void												reference;
		typedef void												const_reference;
		typedef typename_type_k allocator_type::size_type			size_type;
	/// @}

	private:

		/// The node of the block_head 
		struct block_head{ block_head* next; };
		/// The node of the chunk_head 
		struct chunk_head
		{	
			/* BCC Bug: Can not use BLOCK_SIZE directly when BLOCK_SIZE = sizeof(object) */
			enum{en_raw_block_size = BLOCK_SIZE};

			/* The size of one block is sizeof(block_head) at least */
		#if EXTL_WORKAROUND_BORLAND(==, 0x564)
			enum { en_block_size = 
					BLOCK_SIZE < sizeof(block_head)? sizeof(block_head) : BLOCK_SIZE };
		#else
			enum { en_block_size = 
					en_raw_block_size < sizeof(block_head)? sizeof(block_head) : en_raw_block_size };
		#endif

			enum { en_data_size = CHUNK_SIZE };
			enum { en_block_count = en_data_size / en_block_size };

			chunk_head* next;
			e_byte_t data[en_data_size];
			block_head* first_block()	{ return reinterpret_cast<block_head*>(&data[0]);										}
			block_head* last_block()	{ return reinterpret_cast<block_head*>(data + (en_block_count - 1) * en_block_size);	}
			
		};
		friend struct chunk_head;

		enum {en_data_size = chunk_head::en_data_size};
		enum {en_block_size = chunk_head::en_block_size};
		
	/// \name Members
	/// @{
	private:
		chunk_head*				m_chunks;					//!< The head of the linked list of the whole storage 
		block_head*				m_first_free;				//!< The first free block of the free linked list 
		block_head*				m_last_free;				//!< The last free block of the free linked list 
		chunk_head*				m_free_chunk;			
	/// @}

	private:
		/*!\brief Prohibit copying and assignment
		 *
		 * Maybe EBO is not supported if uses extl::uncopyable,
		 * because some compilers do not support EBO_FORM_6 - EXTL_EBO_FORM_6_SUPPORT
		 */
		fixed_pool(class_type const&);
		class_type& operator=(class_type const&);

	/// \name Constructors
	/// @{
	public:
		fixed_pool()
			: m_chunks(NULL)
			, m_first_free(NULL)
			, m_last_free(NULL)
			, m_free_chunk(NULL)
		{
			
		}
		virtual ~fixed_pool()
		{
			destroy();
		}
	/// @}

	public:
		/// Destroys the pool
		void destroy()
		{
			EXTL_ASSERT(is_valid());
			/* Releases the memory of the fixed pool */
			chunk_head* node = m_chunks;
			while(NULL != node)
			{
				chunk_head* p = node;
				node = node->next;
				allocator().deallocate(reinterpret_cast<e_byte_t*>(p), 0);
			}
			m_chunks = NULL;
			m_first_free = NULL;
			m_last_free = NULL;
			m_free_chunk = NULL;

			EXTL_ASSERT(is_valid());
		}

	public:
		/// Gets the allocator of the pool
		allocator_type allocator() const
		{
		#ifdef EXTL_EBO_FORM_2_SUPPORT
			return *this;
		#else
			return allocator_type();
		#endif
		}
		/// Allocates a fixed-size memory block
		pointer allocate(size_type n = 1)
		{
			EXTL_SUPPRESS_UNUSED(n);
			EXTL_ASSERT(1 == n);
			EXTL_ASSERT(is_valid());
			
		#ifdef EXTL_COMPILER_IS_GCC
			EXTL_STATIC_ASSERT(size_type(en_block_size) <= size_type(en_data_size));
		#else
			EXTL_STATIC_ASSERT(en_block_size <= en_data_size);
		#endif

			if (NULL == m_first_free) grow();
			return alloc_block_from_pool();
		}

		/// Only puts the fixed back into the pool
		void deallocate(pointer block)
		{
			dealloc_block_to_pool(block);
		}
	private:
		/// Grows the size of the pool 
		void grow()
		{
			EXTL_ASSERT(is_valid());
			EXTL_ASSERT(NULL == m_last_free);
			EXTL_ASSERT(NULL == m_first_free);
			/* Adds a new chunk into the pool 
			 *  -----------     ----------
			 * | new_chunk | - |  chunk1  | - ... ...
			 *  -----------     ----------
			 */
			chunk_head* new_chunk = reinterpret_cast<chunk_head*>(allocator().allocate(sizeof(chunk_head), NULL));
			EXTL_ASSERT(NULL != new_chunk);
			new_chunk->next = m_chunks;
			m_chunks = new_chunk;

			/* The new chunk
			 *  -----------------------------------------
			 * | block | block |  ....  |        |       |
			 *  -----------------------------------------
			 *     |                                 |
			 * first_free                        last_free
			 */
			m_first_free = new_chunk->first_block();
			m_last_free = new_chunk->last_block();
			m_last_free->next = NULL;
			
			/* The current free chunk */
			m_free_chunk = new_chunk;
			EXTL_ASSERT(is_valid());
		}

		/// Allocates a free block from the pool 
		pointer alloc_block_from_pool()
		{
			EXTL_ASSERT(is_valid());
			EXTL_ASSERT(NULL != m_first_free);
			pointer p = static_cast<pointer>(m_first_free);

			/* Allocates a free block by linked list if m_free_chunk is NULL
			 * --------------     
			 * |  free_block1 |              
			 *  --------------  <- first_free           
			 * |  free_block2 | --                
			 *  --------------    |                            
			 * |  free_block3 |   |                             
			 *  --------------  <- next_free           
			 * |  free_block4 |                                 
			 *  --------------                                
			 *       NULL       
			 */  
			if (NULL == m_free_chunk || 1 == chunk_head::en_block_count)
			{
				m_first_free = m_first_free->next;
			}
			/* Delay to segregate a chunk for optimization
			 * The chunk is not segregated until a block in the chunk is allocated
			 * and the chunk will be segregated completely when first_free is pointed to the last block,
			 * then the blocks in the chunk will be allocated by linked list
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
			 */  
			else
			{
				m_first_free = reinterpret_cast<block_head*>
					(reinterpret_cast<e_byte_t*>(m_first_free) + chunk_head::en_block_size);

				if (m_first_free == m_free_chunk->last_block())
				{
					m_free_chunk = NULL;
				}
			}

			/* There are not more free block after allocating a block from the chunk */
			if (NULL == m_first_free)
				m_last_free = NULL;

			EXTL_ASSERT(is_valid());
			return p;
		}
		/// Deallocates a block to the pool 
		void dealloc_block_to_pool(pointer block)
		{
			EXTL_ASSERT(is_valid());

			block_head* p = static_cast<block_head*>(block);
			p->next = NULL;
			
			if (NULL == m_last_free)
			{
				EXTL_ASSERT(NULL == m_first_free);
				m_last_free = p;
				m_first_free = p;
			}
			else
			{
				m_last_free->next = p;
				m_last_free = p;
			}

			EXTL_ASSERT(is_valid());
		}

	
	private:
		e_bool_t is_valid() const
		{
			if ((NULL == m_first_free) != (NULL == m_last_free))
				return e_false_v;

			return e_true_v;
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_FIXED_POOL_TEST_ENABLE
#	include "unit_test/fixed_pool_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_FIXED_POOL_H */
/* //////////////////////////////////////////////////////////////////// */
