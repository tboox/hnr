/* ///////////////////////////////////////////////////////////////////////
 * File:		objects_pool.h		
 *
 * Created:		08.05.04					
 * Updated:		08.05.04	
 *
 * Brief: objects_pool class - slower than pods_pool
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEMORY_OBJECTS_POOL_H
#define EXTL_MEMORY_OBJECTS_POOL_H

/*!\file object_pool.h
 * \brief objects_pool class - slower than pods_pool
 */
#ifndef __cplusplus
#	error objects_pool.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "basic_pool.h"
#include "initialiser_selector.h" 

#ifdef EXTL_MEMORY_OBJECTS_POOL_TEST_ENABLE
#	include "../counter/clock_counter.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE
/*!\brief objects_pool class
 *
 * \param T The element type
 * \param I The initialiser type
 *
 * \ingroup extl_group_memory
 */
template<	typename_param_k T
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
		,	typename_param_k I = typename_type_def_k initialiser_selector<T>::initialiser_type
#else
		,	typename_param_k I 
#endif
		>
class objects_pool
	: public default_basic_pool
	, protected I	/* EXTL_EBO_FORM_7_SUPPORT */
{
	/// \name Types
	/// @{
	public:
		typedef objects_pool<T, I>																class_type;
		typedef T																				value_type;
		typedef default_basic_pool																basic_pool_type;
		typedef typename_type_k basic_pool_type::allocator_type									allocator_type;
		typedef value_type*																		pointer;
		typedef value_type const*																const_pointer;
		typedef value_type																		reference;
		typedef value_type																		const_reference;
		typedef typename_type_k basic_pool_type::size_type										size_type;
		typedef I																				initialiser_type;
	/// @}

	private:
		/*  ----------
		 * |   next   | - alloced_node
		 *  ----------
		 * |  count   | - the count of the object
		 *  ----------
		 * | object1  | - objects
		 *  ----------
		 * | object2  | 
		 *   ... ...
		 */
		/// The allocated node type
		struct alloced_node
		{
			alloced_node*	next;
			size_type		count;
			pointer			objects() { return reinterpret_cast<pointer>(&((this)[1])); }
		};
		/* The linked list of the allocated objects
		 *  ----------     ----------     ----------
		 * |   next   | - |          | - |          | - NULL
		 *  ----------     ----------     ----------
		 *       |                             |
		 * m_alloced_objects          m_last_alloced_objects
		 *
		 */
		/// The alloced objects
		alloced_node*														m_alloced_objects;
		/// The last alloced objects
		alloced_node*														m_last_alloced_objects;

	/// \name Types
	/// @{
	public:
		objects_pool(initialiser_type intr = initialiser_type())
			: basic_pool_type()
			, initialiser_type(intr)
			, m_alloced_objects(NULL)
			, m_last_alloced_objects(NULL)
		{
		}
		~objects_pool()
		{
			destruct_objects_from_pool();
		}
	/// @}

	public:
		/// Allocates memory block of the specified size 
		pointer allocate(size_type size)
		{
			return construct_objects(alloc_objects_from_pool(size));
		}

		/// Reallocates memory block of the specified size 
		pointer reallocate(pointer objects, size_type size)
		{
			EXTL_ASSERT(is_valid());

			alloced_node* node = m_alloced_objects;
			alloced_node* pre_node = node;
			while(NULL != node)
			{
				if(node->objects() == objects)
				{
					if(size <= node->count)
					{
						/* Destructs the redundant objects */
						initialiser().destruct_n(objects + size, node->count - size);
						return objects;
					}
					else
					{
						/* Destructs the objects */
						initialiser().destruct_n(objects, node->count);

						/* Removes the objects from the linked list of the allocated objects */
						if(pre_node == node)m_alloced_objects = m_alloced_objects->next;
						else pre_node->next = node->next;
						if(NULL == m_alloced_objects) m_last_alloced_objects = NULL;
							
						/* Puts the node with the object back into the pool */
						basic_pool_type::deallocate(node);
						return allocate(size);
					}
				}
				pre_node = node;
				node = node->next;
			}

			EXTL_ASSERT(is_valid());

			/* Fails to reallocate the objects */
			EXTL_ASSERT(0);
			return objects;
		}
		
		/// Deallocates the block to pool 
		void deallocate(pointer objects)
		{
			EXTL_ASSERT(is_valid());

			alloced_node* node = m_alloced_objects;
			alloced_node* pre_node = node;
			while(NULL != node)
			{
				if(node->objects() == objects)
				{
					/* Destructs the objects */
					initialiser().destruct_n(objects, node->count);

					/* Removes the objects from the linked list of the allocated objects */
					if(pre_node == node)m_alloced_objects = m_alloced_objects->next;
					else pre_node->next = node->next;
					if(NULL == m_alloced_objects) m_last_alloced_objects = NULL;
					
					/* Puts the node with the object back into the pool */
					basic_pool_type::deallocate(node);
		
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
			basic_pool_type::destroy();
		}
	private:
		/// Allocates objects from the pool 
		alloced_node* alloc_objects_from_pool(size_type size)
		{
			EXTL_ASSERT(is_valid());

			/* Allocates a new node from the pool */
			alloced_node* node = static_cast<alloced_node*>(basic_pool_type::allocate(sizeof(alloced_node) + size * sizeof(value_type)));
			EXTL_ASSERT(NULL != node);
			if(NULL == node) return NULL;
			node->count = size;
			node->next = NULL;
		
			/* Add the node to the linked list of the allocated objects */
			if(NULL == m_last_alloced_objects) m_alloced_objects = node;
			else m_last_alloced_objects->next = node;
			m_last_alloced_objects = node;

			EXTL_ASSERT(is_valid());
			return node;
		}

		/// Constructs the objects 
		pointer construct_objects(alloced_node* node)
		{
			EXTL_ASSERT(is_valid());
			EXTL_ASSERT(NULL != node);
			EXTL_ASSERT(NULL != node->objects());
			if(NULL == node || NULL == node->objects()) return NULL;

			try
			{
				initialiser().construct_n(node->objects(), node->count);
			}
			catch (...)
			{
				deallocate(node->objects());
				EXTL_THROW;
			}

			EXTL_ASSERT(is_valid());
			return node->objects();
		}

		/// Destructs all objects from the pool 
		void destruct_objects_from_pool()
		{
			EXTL_ASSERT(is_valid());

			alloced_node* node = m_alloced_objects;
			while(NULL != node)
			{
				EXTL_ASSERT(NULL != node->objects());
				initialiser().destruct_n(node->objects(), node->count);
				node = node->next;
			}
			m_alloced_objects = NULL;
			m_last_alloced_objects = NULL;

			EXTL_ASSERT(is_valid());
		}
		/// Invariance
		e_bool_t is_valid() const
		{
			if((NULL == m_last_alloced_objects) != (NULL == m_alloced_objects))
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
#ifdef EXTL_MEMORY_OBJECTS_POOL_TEST_ENABLE
#	include "unit_test/objects_pool_test.h"
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEMORY_OBJECTS_POOL_H */
/* //////////////////////////////////////////////////////////////////// */
