/* ///////////////////////////////////////////////////////////////////////
 * File:		uncopyable.h		
 *
 * Created:		08.03.20				
 * Updated:		08.05.05
 *
 * Brief: Protects copying construction and assignment
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_UTILITY_NONCOPYABLE_H
#define EXTL_UTILITY_NONCOPYABLE_H

/*!\file uncopyable.h
 * \brief Protects copying construction and assignment
 */
#ifndef __cplusplus
#	error uncopyable.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../config/config.h" 

/*!\brief uncopyable<> class
 *
 * \param Tag The tag type - be convenient to find the uncopyable class
 *
 * \ingroup extl_group_utility
 */
EXTL_BEGIN_NAMESPACE
template < typename_param_k Tag >
class uncopyable
{
	protected:
		uncopyable(){}
		~uncopyable(){}

	private:
		typedef uncopyable<Tag>	class_type;
	private:
		uncopyable(class_type const &);
		class_type const & operator=(class_type const&);
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE	

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_UTILITY_NONCOPYABLE_H */
/* //////////////////////////////////////////////////////////////////// */
