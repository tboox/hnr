/* ///////////////////////////////////////////////////////////////////////
 * File:		object_pool.h		
 *
 * Created:		08.04.14					
 * Updated:		08.05.02	
 *
 * Brief: object_pool class - slower than pod_pool
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_OBJECT_POOL_H
#define EXTL_MEMORY_OBJECT_POOL_H

/*!\file object_pool.h
 * \brief object_pool class - slower than pod_pool
 *
 * Note: The size of an element must be less than 8K,
 * and only one object is allocated at a time
 */
#ifndef __cplusplus
#	error object_pool.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "fixed_pool.h"
#include "pod_pool.h"
#include "initialiser_selector.h"
#ifdef EXTL_MEMORY_OBJECT_POOL_TEST_ENABLE
#	include "../counter/clock_counter.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief object_pool class
 *
 * \param T The element type
 * \param I The initialisation traits type
 * \param CHUNK_SIZE The size of a chunk
 * \param A The allocator type
 *
 * [Structure]
 *
 *               --------------------      --------------------
 * m_chunks ---> |      chunk1      | ---> |      chunk2      | ---> NULL
 *               --------------------      --------------------
 *                       ¡ý
 *			             -------------------------------------
 * one chunk: m_head --> |    object1    -|->   object1   -|-> NULL
 *                       -------------------------------------
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k I = typename_type_def_k initialiser_selector<T>::initialiser_type
		,	e_size_t CHUNK_SIZE = EXTL_FIXED_POOL_DEFAULT_CHUNK_SIZE
		,	typename_param_k A = typename_type_def_k allocator_selector<e_byte_t>::allocator_type
#else
		,	typename_param_k I
		,	e_size_t CHUNK_SIZE 
		,	typename_param_k A
#endif
		>
class object_pool
	: public fixed_pool< sizeof(void*) + sizeof(T), CHUNK_SIZE, A >	/* sizeof(alloced_node) + sizeof(object) */
	, protected I	/* EXTL_EBO_FORM_7_SUPPORT */
{
	/// \name Types
	/// @{
	public:
		typedef object_pool<T, I, CHUNK_SIZE, A>							class_type;
		typedef T															value_type;
		typedef value_type*													pointer;
		typedef value_type const*											const_pointer;
		typedef value_type&													reference;
		typedef value_type const&											const_reference;
		typedef fixed_pool< sizeof(void*) + sizeof(T), CHUNK_SIZE, A >		fixed_pool_type;
		typedef typename_type_k fixed_pool_type::allocator_type				allocator_type;
		typedef typename_type_k allocator_type::size_type					size_type;
		typedef I															initialiser_type;
	/// @}
		
	private:
		/// Prohibit copying and assignment 
		object_pool(class_type const&);
		class_type& operator=(class_type const&);

	private:
		/*  ----------
		 * |   next   | - alloced_node
		 *  ----------
		 * |          | - object
		 */
		/// The alloced_node type
		struct alloced_node
		{
			alloced_node*	next;
			pointer			object() { return reinterpret_cast<pointer>(&((this)[1])); }
		};
		/* The linked list of the allocated objects
		 *  ----------     ----------     ----------
		 * |   next   | - |          | - |          | - NULL
		 *  ----------     ----------     ----------
		 *       |                             |
		 * m_alloced_objects          m_last_alloced_object
		 *
		 */
		/// The alloced objects
		alloced_node*														m_alloced_objects;
		/// The last alloced object
		alloced_node*														m_last_alloced_object;

	/// \name Members
	/// @{
	public:
		object_pool(initialiser_type intr = initialiser_type())
			: fixed_pool_type()
			, initialiser_type(intr)
			, m_alloced_objects(NULL)
			, m_last_alloced_object(NULL)
		{
			EXTL_ASSERT(is_valid());
		}
		~object_pool()
		{
			/* DMC Bug: The compiler will not compile this code if there is not the following statement */
			#if defined(EXTL_COMPILER_IS_DMC)
			{}
			#endif

			/* Destructs all objects from the pool */
			destruct_objects_from_pool();
		}
	/// @}

	public:
		/// Gets the allocator
		allocator_type allocator() const
		{
			return fixed_pool_type::allocator();
		}
		/// Allocates an object from the pool and constucts it 
		pointer allocate(size_type n = 1)
		{
			EXTL_ASSERT(1 == n);
			EXTL_ASSERT(is_valid());
			return construct_object(alloc_object_from_pool());
		}
		/// Deallocates the object and puts the object back into the pool 
		void deallocate(pointer object)
		{
			EXTL_ASSERT(is_valid());

			/* Destructs the object */
			initialiser().destruct(object);
			
			alloced_node* node = m_alloced_objects;
			alloced_node* pre_node = node;
			while(NULL != node)
			{
				if(node->object() == object)
				{
					/* Removes the object from the linked list of the allocated objects */
					if(pre_node == node)m_alloced_objects = m_alloced_objects->next;
					else pre_node->next = node->next;
					if(NULL == m_alloced_objects) m_last_alloced_object = NULL;
						
					/* Puts the node with the object back into the pool */
					fixed_pool_type::deallocate(node);
					return ;
				}
				pre_node = node;
				node = node->next;
			}

			EXTL_ASSERT(is_valid());
		}
		/// Destroys the pool 
		void destroy()
		{
			destruct_objects_from_pool();
			fixed_pool_type::destroy();
		}
	private:
		/// Destructs all objects from the pool 
		void destruct_objects_from_pool()
		{
			EXTL_ASSERT(is_valid());

			alloced_node* node = m_alloced_objects;
			while(NULL != node)
			{
				EXTL_ASSERT(NULL != node->object());

				/* Destructs the object */
				initialiser().destruct(node->object());
				node = node->next;
			}
			m_alloced_objects = NULL;
			m_last_alloced_object = NULL;

			EXTL_ASSERT(is_valid());
		}
		/// Allocates an object from the pool 
		pointer alloc_object_from_pool()
		{
			EXTL_ASSERT(is_valid());

			/* Allocates a new node from the pool */
			alloced_node* node = static_cast<alloced_node*>(fixed_pool_type::allocate(1));
			EXTL_ASSERT(NULL != node);
			node->next = NULL;
			
			/* Add the node to the linked list of the allocated objects */
			if(NULL == m_last_alloced_object) m_alloced_objects = node;
			else m_last_alloced_object->next = node;
			m_last_alloced_object = node;

			EXTL_ASSERT(is_valid());
			return node->object();
		}
		/// Constructs the object 
		pointer construct_object(pointer object)
		{
			EXTL_ASSERT(is_valid());
			EXTL_ASSERT(NULL != object);
			if(NULL == object) return NULL;

			try
			{
				/* Constructs the object */
				initialiser().construct(object);
			}
			catch (...)
			{
				deallocate(object);
				EXTL_THROW;
			}
			EXTL_ASSERT(is_valid());
			return object;
		}
		/// Invariance
		e_bool_t is_valid() const
		{
			if((NULL == m_last_alloced_object) != (NULL == m_alloced_objects))
				return e_false_v;
			return e_true_v;
		}
		/// Returns the initialiser
		initialiser_type&		initialiser()		{ return *this;	}
		/// Returns the initialiser
		initialiser_type const&	initialiser() const	{ return *this;	}

};
/* ///////////////////////////////////////////////////////////////////////
 * Unit-testing
 */
#ifdef EXTL_MEMORY_OBJECT_POOL_TEST_ENABLE
#	include "unit_test/object_pool_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_OBJECT_POOL_H */
/* //////////////////////////////////////////////////////////////////// */
