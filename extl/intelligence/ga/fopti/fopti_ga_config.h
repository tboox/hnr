/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_ga_config.h		
 *
 * Created:		08.10.07
 * Updated:		08.10.13
 *
 * Brief: The fopti_ga_config class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_FOPTI_GA_CONFIG_H
#define EXTL_INTELLIGENCE_FOPTI_GA_CONFIG_H

/*!\file fopti_ga_config.h
 * \brief The fopti_ga_config class
 */
#ifndef __cplusplus
#	error fopti_ga_config.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "fopti_individual.h"
#include "fopti_crossover_traits.h"
#include "fopti_mutation_traits.h"
#include "fopti_rmake_traits.h"
#include "fopti_fitness_traits.h"
#include "fopti_penalty_traits.h"


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_ga_config class
 * 
 * \param for_max Set \true for maximum 
 * \param Func The function type
 *
 * \ingroup extl_group_intelligence
 */
template<	e_bool_t for_max
		,	typename_param_k Func
		>
struct fopti_test_ga_config
	: ga_config_base
{
	/// \name The Configuration Types
	/// @{

	/// The function type - fopti
	typedef Func																func_type;

	/// The random type - basic
	typedef linear_rand															random_type;

	/// The population type - basic
#if EXTL_WORKAROUND_BORLAND(==, 0x551)
	typedef population<fopti_individual<(func_type::param_num)> >				population_type;
#else
	typedef population<fopti_individual<func_type::param_num> >					population_type;
#endif

	/// The rmake_traits type - basic
	typedef fopti_rmake_traits	<	population_type
								,	random_type
								>												rmake_traits_type;

	/// The fitness_traits type - basic
	typedef fopti_fitness_traits	<	for_max
									,	population_type
									,	fopti_penalty_traits<	typename_type_k population_type::individual_type
															,	func_type
															>
									,	rmake_traits_type
									>											fitness_traits_type;

	/// The stop_traits type - basic
	typedef external_minimal_residual_stop_traits<population_type, 64>			stop_traits_type;

	/// The selection_traits type - basic
	typedef roulette_wheel_selection_traits	<	population_type
											,	random_type
											,	rank_based_probability_traits<population_type, 30>
											>									selection_traits_type;

	/*typedef roulette_wheel_selection_traits	<	population_type
											,	random_type
											,	proportional_probability_traits<population_type>
											>									selection_traits_type;*/

	/*typedef tournament_selection_traits	<	population_type
										,	random_type
										>										selection_traits_type;*/

	/// The crossover_traits type - fopti
	typedef middle_recombination_crossover_traits	<	population_type
													,	random_type
													>							crossover_traits_type;


	/*typedef discrete_recombination_crossover_traits	<	population_type
													,	random_type
													>							crossover_traits_type;*/

	/*typedef linear_recombination_crossover_traits	<	population_type
													,	random_type
													>							crossover_traits_type;*/

	/// The mutation_traits type - fopti
	typedef fopti_mutation_traits	<	population_type
									,	random_type
									>											mutation_traits_type;

	/// The cross_p_traits type - basic
	typedef adaptive_cross_p_traits<population_type>							cross_p_traits_type;

	//typedef simple_cross_p_traits<population_type>								cross_p_traits_type;

	/// The mutate_p_traits type - basic
	typedef adaptive_mutate_p_traits<population_type>							mutate_p_traits_type;

	//typedef simple_mutate_p_traits<population_type>								mutate_p_traits_type;

	/// The local_search_traits type - basic
	/*typedef no_local_search_traits					<	population_type
													,	random_type
													,	rmake_traits_type
													,	fitness_traits_type
													>							local_search_traits_type;*/

	typedef simulated_annealing_local_search_traits	<	population_type
													,	random_type
													,	rmake_traits_type
													,	fitness_traits_type
													>							local_search_traits_type;

	/*typedef hill_climbing_local_search_traits		<	population_type
													,	random_type
													,	rmake_traits_type
													,	fitness_traits_type
													>							local_search_traits_type;*/

	/// @}
};

template<	e_bool_t for_max
		,	typename_param_k Func
		>
struct fopti_simple_ga_config
	: ga_config_base
{
	/// \name The Configuration Types
	/// @{

	/// The function type - fopti
	typedef Func																func_type;

	/// The random type - basic
	typedef linear_rand															random_type;

	/// The population type - basic
#if EXTL_WORKAROUND_BORLAND(==, 0x551)
	typedef population<fopti_individual<(func_type::param_num)> >				population_type;
#else
	typedef population<fopti_individual<func_type::param_num> >					population_type;
#endif

	/// The rmake_traits type - basic
	typedef fopti_rmake_traits	<	population_type
								,	random_type
								>												rmake_traits_type;

	/// The fitness_traits type - basic
	typedef fopti_fitness_traits	<	for_max
									,	population_type
									,	fopti_penalty_traits<	typename_type_k population_type::individual_type
															,	func_type
															>
									,	rmake_traits_type
									>											fitness_traits_type;

	/// The stop_traits type - basic
	typedef external_minimal_residual_stop_traits<population_type, 64>			stop_traits_type;

	/// The selection_traits type - basic
	typedef roulette_wheel_selection_traits	<	population_type
											,	random_type
											,	proportional_probability_traits<population_type>
											>									selection_traits_type;
	/*typedef tournament_selection_traits	<	population_type
										,	random_type
										>										selection_traits_type;*/

	/// The crossover_traits type - fopti
	typedef middle_recombination_crossover_traits	<	population_type
													,	random_type
													>							crossover_traits_type;
	/*typedef discrete_recombination_crossover_traits	<	population_type
													,	random_type
													>							crossover_traits_type;*/

	/*typedef linear_recombination_crossover_traits	<	population_type
													,	random_type
													>							crossover_traits_type;*/

	/// The mutation_traits type - fopti
	typedef fopti_mutation_traits	<	population_type
									,	random_type
									>											mutation_traits_type;

	/// The cross_p_traits type - basic
	typedef simple_cross_p_traits<population_type>								cross_p_traits_type;

	/// The mutate_p_traits type - basic
	typedef simple_mutate_p_traits<population_type>								mutate_p_traits_type;

	/// The local_search_traits type - basic
	typedef no_local_search_traits					<	population_type
													,	random_type
													,	rmake_traits_type
													,	fitness_traits_type
													>							local_search_traits_type;

	/// @}
};

template<	e_bool_t for_max
		,	typename_param_k Func
		>
struct fopti_default_ga_config
	: ga_config_base
{
	/// \name The Configuration Types
	/// @{

	/// The function type - fopti
	typedef Func																func_type;

	/// The random type - basic
	typedef linear_rand															random_type;

	/// The population type - basic
#if EXTL_WORKAROUND_BORLAND(==, 0x551)
	typedef population<fopti_individual<(func_type::param_num)> >				population_type;
#else
	typedef population<fopti_individual<func_type::param_num> >					population_type;
#endif

	/// The rmake_traits type - basic
	typedef fopti_rmake_traits	<	population_type
								,	random_type
								>												rmake_traits_type;

	/// The fitness_traits type - basic
	typedef fopti_fitness_traits	<	for_max
									,	population_type
									,	fopti_penalty_traits<	typename_type_k population_type::individual_type
															,	func_type
															>
									,	rmake_traits_type
									>											fitness_traits_type;

	/// The stop_traits type - basic
	typedef external_minimal_residual_stop_traits<population_type, 64>			stop_traits_type;

	/// The selection_traits type - basic
	typedef tournament_selection_traits	<	population_type
										,	random_type
										>										selection_traits_type;

	/// The crossover_traits type - fopti
	typedef middle_recombination_crossover_traits	<	population_type
													,	random_type
													>							crossover_traits_type;

	/// The mutation_traits type - fopti
	typedef fopti_mutation_traits	<	population_type
									,	random_type
									>											mutation_traits_type;

	/// The cross_p_traits type - basic
	typedef adaptive_cross_p_traits<population_type>							cross_p_traits_type;

	/// The mutate_p_traits type - basic
	typedef adaptive_mutate_p_traits<population_type>							mutate_p_traits_type;

	/// The local_search_traits type - basic
	typedef simulated_annealing_local_search_traits	<	population_type
													,	random_type
													,	rmake_traits_type
													,	fitness_traits_type
													>							local_search_traits_type;
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_FOPTI_GA_CONFIG_H */
/* //////////////////////////////////////////////////////////////////// */
