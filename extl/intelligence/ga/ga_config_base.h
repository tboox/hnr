/* ///////////////////////////////////////////////////////////////////////
 * File:		ga_config_base.h		
 *
 * Created:		08.11.02
 * Updated:		08.11.02
 *
 * Brief: The ga_config_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_CONFIG_BASE_H
#define EXTL_INTELLIGENCE_GA_CONFIG_BASE_H

/*!\file ga_config_base.h
 * \brief The ga_config_base class
 */
#ifndef __cplusplus
#	error ga_config_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief ga_config_base class
 * 
 * \ingroup extl_group_intelligence
 */
struct ga_config_base
{
	/// \name The Configuration Types
	/// @{

	/// The random type
	typedef linear_rand											random_type;

	/// The population type
	typedef e_null_t											population_type;

	/// The fitness_traits type - basic
	typedef e_null_t											fitness_traits_type;

	/// The rmake_traits type - basic
	typedef e_null_t											rmake_traits_type;

	/// The stop_traits type - basic
	typedef e_null_t											stop_traits_type;

	/// The selection_traits type - basic
	typedef e_null_t											selection_traits_type;

	/// The crossover_traits type - fopti
	typedef e_null_t											crossover_traits_type;

	/// The mutation_traits type - fopti
	typedef e_null_t											mutation_traits_type;

	/// The cross_p_traits type - basic
	typedef e_null_t											cross_p_traits_type;

	/// The mutate_p_traits type - basic
	typedef e_null_t											mutate_p_traits_type;

	/// The local_search_traits type - basic
	typedef e_null_t											local_search_traits_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_CONFIG_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
