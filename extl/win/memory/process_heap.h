/* ///////////////////////////////////////////////////////////////////////
 * File:		process_heap.h		
 *
 * Created:		08.06.13			
 * Updated:		08.06.13
 *
 * Brief: process_heap class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */
#ifndef EXTL_PLATFORM_WIN_MEMORY_PROCESS_HEAP_H
#define EXTL_PLATFORM_WIN_MEMORY_PROCESS_HEAP_H

/*!\file process_heap.h
 * \brief process_heap class 
 */
#ifndef __cplusplus
#	error process_heap.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "heap.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_BEGIN_WHOLE_NAMESPACE

/*!\brief process_heap class
 * \ingroup extl_group_memory
 */
class process_heap : public heap
{
	/// \name Types
	/// @{
	public:
		typedef heap												base_type;
		typedef process_heap										class_type;
		typedef base_type::handle_type								handle_type;
		typedef base_type::size_type								size_type;
	/// @}

	
	/// \name Constructors
	/// @{
	public:
		/// Creates a private process_heap
		process_heap()
			: base_type(::GetProcessHeap())
		{
		}
		~process_heap()
		{
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::platform::win namespace
 */
EXTL_WIN_END_WHOLE_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_PLATFORM_WIN_MEMORY_PROCESS_HEAP_H */
/* //////////////////////////////////////////////////////////////////// */
