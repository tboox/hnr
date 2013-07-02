/* ///////////////////////////////////////////////////////////////////////
 * File:		wga_network.h		
 *
 * Created:		08.12.29	
 * Updated:		08.12.29
 *
 * Brief:		The wga_network class - the genetic algorithm optimization for weight
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_WGA_NETWORK_H
#define EXTL_INTELLIGENCE_ANN_WGA_NETWORK_H

/*!\file wga_network.h
 * \brief wga_network class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error wga_network.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../ga/fopti/fopti.h"
#include "network_validator.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief wga_scopes class
 * 
 * \ingroup extl_group_intelligence
 */
class wga_scopes
{
	/// \name Types
	public:
		typedef e_size_t											size_type;
		typedef e_bool_t											bool_type;
		typedef e_float_t											float_type;
		typedef size_type											index_type;
		typedef class wga_scope
		{
			private:
				float_type											m_lower;
				float_type											m_upper;

			public:
				wga_scope()
					: m_lower(0), m_upper(0)
				{}

				wga_scope(float_type const& lower, float_type const& upper)
					: m_lower(lower), m_upper(upper)
				{}

				float_type const	lower() const					{ return m_lower;	}
				void				lower(float_type l)				{ m_lower = l;		}
				
				float_type const	upper() const					{ return m_upper;	}
				void				upper(float_type u)				{ m_upper = u;		}

				void				scope(float_type l, float_type u)	{ lower(l);	upper(u);	}

				float_type const	size() const					{ return (upper() - lower());	}

				bool_type			include(float_type v) const		{ return ((v >= lower()) && (v <= upper()));	}
				
				float_type			ensure_lower(float_type v) const	{ return ((v < lower())? lower() : v);			}
				float_type			ensure_upper(float_type v) const	{ return ((v > upper())? upper() : v);			}
				float_type			ensure_include(float_type v) const	{ return ensure_upper(ensure_lower(v));			}
		}															scope_type;
		typedef buffer_selector<scope_type>::buffer_type			buffer_type;
	/// @}

	/// \name Members
	/// @{
	private:
		buffer_type													m_scopes;
	/// @}

	/// \name Constructors
	/// @{
	public:
		wga_scopes()
			: m_scopes()
		{}
		wga_scopes(scope_type const& sp, size_type n)
			: m_scopes(sp, n)
		{}
	/// @}

	/// \name Accessors
	/// @{
	public:
		scope_type const&	at(index_type i) const	{ EXTL_ASSERT(i < size()); return m_scopes[i];	}
		scope_type&			at(index_type i)		{ EXTL_ASSERT(i < size()); return m_scopes[i];	}

		scope_type const&	operator[](index_type i) const	{ return at(i);	}
		scope_type&			operator[](index_type i)		{ return at(i);	}

		size_type const		size() const					{ return m_scopes.size();	}
	/// @}
};

/*!\brief wga_individual class
 * 
 * \param Wgts the weights type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Wgts>
class wga_individual
	: public individual_base<wga_individual<Wgts> >
{
	/// \name Types
	/// @{
	public:
		typedef individual_base<wga_individual<Wgts> >			base_type;
		typedef wga_individual									class_type;
		typedef typename_type_k base_type::size_type			size_type;
		typedef typename_type_k base_type::bool_type			bool_type;
		typedef typename_type_k base_type::float_type			float_type;
		typedef typename_type_k base_type::index_type			index_type;
		typedef typename_type_k base_type::int_type				int_type;
		typedef Wgts											weights_type;
		typedef wga_scopes										scopes_type;
		typedef typename_type_k scopes_type::scope_type			scope_type;
	/// @}
		
	/// \name Members
	/// @{
	private:
		weights_type											m_weights;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		wga_individual()
			: base_type()
			, m_weights()
		{}
	/// @}

	/// \name Attributes
	/// @{
	public:
		weights_type const&		weights() const						{ return m_weights;	}
		weights_type&			weights()							{ return m_weights;	}
		void					weights(weights_type const& wgts)	{ m_weights = wgts;	}

		float_type const		value(index_type i) const					{ EXTL_ASSERT(i < size()); return weights()[i].value();		}
		void					value(index_type i, float_type v)			{ EXTL_ASSERT(i < size()); weights()[i].value(v);			}

		size_type				size() const								{ return weights().size();			}
	/// @}
};


/*!\brief wga_fitness_traits class
 * 
 * \param Network the network type
 * \param Pop the population type
 * \param Pen the penalty traits type
 * \param Rt the rmake_traits type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Network
		,	typename_param_k Pop
		,	typename_param_k Pen
		,	typename_param_k Rt
		>
class wga_fitness_traits
	: public fitness_traits_base<wga_fitness_traits<Network, Pop, Pen, Rt>, Pop, Pen >
{
	/// \name Types
	/// @{
	public:
		typedef fitness_traits_base<wga_fitness_traits<Network, Pop, Pen, Rt>, Pop, Pen >	base_type;
		typedef wga_fitness_traits															class_type;
		typedef typename_type_k base_type::population_type									population_type;
		typedef typename_type_k base_type::individual_type									individual_type;
		typedef typename_type_k base_type::size_type										size_type;
		typedef typename_type_k base_type::bool_type										bool_type;
		typedef typename_type_k base_type::index_type										index_type;
		typedef typename_type_k base_type::int_type											int_type;
		typedef typename_type_k base_type::float_type										float_type;
		typedef typename_type_k base_type::penalty_traits_type								penalty_traits_type;
		typedef Rt																			rmake_traits_type;
		typedef Network																		network_type;
		typedef typename_type_k network_type::samples_type									samples_type;
		typedef basic_network_validator<network_type>										validator_type;
	/// @}

	/// \name Members
	/// @{
	private:
		network_type*																		m_pnetwork;
		samples_type*																		m_psamples;
		validator_type																		m_validator;
	/// @}
		
	/// \name Traits
	/// @{
	public:
		network_type const&		network() const					{ EXTL_ASSERT(NULL != m_pnetwork); return *m_pnetwork;	}
		network_type&			network()						{ EXTL_ASSERT(NULL != m_pnetwork); return *m_pnetwork;	}
		void					network(network_type& net)		{ m_pnetwork = &net;									}

		samples_type const&		samples() const					{ EXTL_ASSERT(NULL != m_psamples); return *m_psamples;	}
		samples_type&			samples()						{ EXTL_ASSERT(NULL != m_psamples); return *m_psamples;	}
		void					samples(samples_type& sps)		{ m_psamples = &sps;									}

		validator_type const&	validator() const	{ return m_validator;	}
		validator_type&			validator()			{ return m_validator;	}
	/// @}

	/// \name Methods
	/// @{
	public:
		void init(network_type& net, samples_type& sps)
		{
			network(net);
			samples(sps);
			base_type::init();
		}
	/// @}

	/// \name Implemention
	/// @{
	public:
		void do_fitness(individual_type& idl)
		{
			// update the weights of the network
			network().weights(idl.weights());

			// calculate mse
			validator().validate(network(), samples());

			// [<focus>]
			// calculate the fitness
			//idl.fitness(100 / (validator().mse()));
			idl.fitness(1 / (validator().mse() * 100));
			//idl.fitness(100 - validator().mse());

			printf("%f %f\n", idl.fitness(), validator().mse());
		}
	/// @}
};

/*!\brief wga_traits class
 * 
 * \param Cfg The ga_config type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Cfg>
class wga_traits
	: public ga_traits_base<wga_traits<Cfg>, Cfg>
{
	/// \name Types
	/// @{
	public:
		typedef ga_traits_base<wga_traits<Cfg>, Cfg>						base_type;
		typedef wga_traits													class_type;
		typedef typename_type_k base_type::config_type						config_type;
		typedef typename_type_k base_type::size_type						size_type;
		typedef typename_type_k base_type::bool_type						bool_type;
		typedef typename_type_k base_type::index_type						index_type;
		typedef typename_type_k base_type::int_type							int_type;
		typedef typename_type_k base_type::float_type						float_type;
		typedef typename_type_k base_type::random_type						random_type;
		typedef typename_type_k base_type::population_type					population_type;
		typedef typename_type_k base_type::individual_type					individual_type;
		typedef typename_type_k base_type::selection_traits_type			selection_traits_type;
		typedef typename_type_k base_type::crossover_traits_type			crossover_traits_type;
		typedef typename_type_k base_type::fitness_traits_type				fitness_traits_type;
		typedef typename_type_k base_type::rmake_traits_type				rmake_traits_type;
		typedef typename_type_k fitness_traits_type::network_type			network_type;
		typedef typename_type_k fitness_traits_type::samples_type			samples_type;
		typedef typename_type_k individual_type::scopes_type				scopes_type;
		typedef typename_type_k scopes_type::scope_type						scope_type;
	/// @}

	/// \name Members
	/// @{
	private:
		scopes_type															m_scopes;
		network_type*														m_pnetwork;
		samples_type*														m_psamples;
	/// @}
		
	/// \name Attributes
	/// @{
	public:
		network_type const&		network() const					{ EXTL_ASSERT(NULL != m_pnetwork); return *m_pnetwork;	}
		network_type&			network()						{ EXTL_ASSERT(NULL != m_pnetwork); return *m_pnetwork;	}
		void					network(network_type& net)		{ m_pnetwork = &net;									}

		samples_type const&		samples() const					{ EXTL_ASSERT(NULL != m_psamples); return *m_psamples;	}
		samples_type&			samples()						{ EXTL_ASSERT(NULL != m_psamples); return *m_psamples;	}
		void					samples(samples_type& sps)		{ m_psamples = &sps;									}

		scopes_type&			scopes()						{ return m_scopes;	}
		scopes_type const&		scopes() const					{ return m_scopes;	}
		void					scopes(scopes_type const& sps)	{ m_scopes = sps;	}
	/// @}

	/// \name Initialization
	/// @{
	public:
		/// initialize individual
		void init_individual(individual_type& idl)
		{
			idl.weights().resize(network().arcs_size());
			base_type::init_individual(idl);
		}
		/// initialize rmake_traits
		void init_rmake_traits()
		{
			this->rmake_traits().init(this->rand(), scopes());
		}
		/// initialize fitness_traits
		void init_fitness_traits()
		{
			this->fitness_traits().init(network(), samples());
		}
		/// initialize crossover_traits
		void init_crossover_traits()
		{
			this->crossover_traits().init(this->rand());
		}
		/// initialize mutation_traits
		void init_mutation_traits()
		{
			this->mutation_traits().init(this->rand(), scopes());
		}
		/// initialize local_search_traits
		void init_local_search_traits()
		{
			if (!(this->rmake_traits().is_valid())) 
				init_rmake_traits();
			if (!(this->fitness_traits().is_valid())) 
				init_fitness_traits();

			this->local_search_traits().init(this->rand(), this->rmake_traits(), this->fitness_traits());
		}
	/// @}
	
	/// \name Methods
	/// @{
	public:
		/// invariance
		bool_type is_valid() const
		{
			return base_type::is_valid();
		}
	/// @}
};


/*!\brief network_local_search_traits class
 * 
 * \param Network the network type
 * \param Pop the population type
 * \param Pen the penalty traits type
 * \param Rt the rmake_traits type
 * \param Ft the fitness_traits type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Network
		,	typename_param_k Pop
		,	typename_param_k Rand
		,	typename_param_k Rt
		,	typename_param_k Ft
		>
class network_local_search_traits
{
	/// \name Types
	/// @{
	public:
		typedef Pop													population_type;
		typedef typename_type_k population_type::individual_type	individual_type;
		typedef typename_type_k population_type::size_type			size_type;
		typedef typename_type_k population_type::bool_type			bool_type;
		typedef typename_type_k population_type::float_type			float_type;
		typedef typename_type_k population_type::index_type			index_type;
		typedef typename_type_k population_type::int_type			int_type;
		typedef Rt													rmake_traits_type;
		typedef Ft													fitness_traits_type;
		typedef Rand												random_type;
		typedef Network												network_type;
	/// @}

	/// \name Members
	/// @{
	private:
		fitness_traits_type*										m_pft;
	/// @}

	/// \name Traits
	/// @{
	private:
		fitness_traits_type const&	fitness_traits() const			{ return *m_pft;	}
		fitness_traits_type&		fitness_traits()				{ return *m_pft;	}
	/// @}

	/// \name Constructors
	/// @{
	public:
		network_local_search_traits()
			: m_pft(NULL)
		{}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init	(	random_type& /*rand*/
					,	rmake_traits_type& /*rt*/
					,	fitness_traits_type& ft)
		{
			m_pft = &ft;
		}

		/// local search
		void search(population_type& pop)
		{
			EXTL_ASSERT(is_valid());

			// [<focus>]
			// local search using network
			fitness_traits().network().train(fitness_traits().samples(), 20);

			// adaptive search
			// primary stage: maintain diversity
			// later stage: strengthen search
			//fitness_traits().network().train(fitness_traits().samples(), pop.generation());

			// update population
			pop.individual(0).weights(fitness_traits().network().weights());
			//pop.worst().weights(fitness_traits().network().weights());
		}
		/// invariance
		bool is_valid() const
		{
			if (NULL == m_pft) return e_false_v;
			return e_true_v;
		}
	/// @}
};

/*!\brief wga_default_ga_config class
 * 
 * \param Network the network type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Network>
struct wga_default_ga_config
	: ga_config_base
{
	/// \name The Configuration Types
	/// @{
	public:
		/// The network type - wga
		typedef Network																	network_type;

		/// The random type - basic
		typedef typename_type_k rand_selector::rand_type								random_type;

		/// The population type - basic
		typedef population<wga_individual<typename_type_k network_type::weights_type> >	population_type;

		/// The rmake_traits type - basic
		typedef fopti_rmake_traits	<	population_type
									,	random_type
									>													rmake_traits_type;

		/// The fitness_traits type - basic
		typedef wga_fitness_traits	<	network_type
									,	population_type
									,	no_penalty_traits<typename_type_k population_type::individual_type>
									,	rmake_traits_type
									>													fitness_traits_type;

		/// The stop_traits type - basic
		typedef external_minimal_residual_stop_traits<population_type, 64>				stop_traits_type;

		/// The selection_traits type - basic
		typedef roulette_wheel_selection_traits	<	population_type
												,	random_type
												,	rank_based_probability_traits<population_type, 30>
												>										selection_traits_type;

		/*typedef roulette_wheel_selection_traits	<	population_type
												,	random_type
												,	proportional_probability_traits<population_type>
												>										selection_traits_type;*/

		/*typedef tournament_selection_traits	<	population_type
											,	random_type
											>											selection_traits_type;*/

		/// The crossover_traits type - wga
		typedef middle_recombination_crossover_traits	<	population_type
														,	random_type
														>								crossover_traits_type;


		/*typedef discrete_recombination_crossover_traits	<	population_type
														,	random_type
														>								crossover_traits_type;*/

		/*typedef linear_recombination_crossover_traits	<	population_type
														,	random_type
														>								crossover_traits_type;*/

		/// The mutation_traits type - wga
		typedef fopti_mutation_traits	<	population_type
										,	random_type
										>												mutation_traits_type;

		/// The cross_p_traits type - basic
		typedef adaptive_cross_p_traits<population_type>								cross_p_traits_type;

		//typedef simple_cross_p_traits<population_type>								cross_p_traits_type;

		/// The mutate_p_traits type - basic
		typedef adaptive_mutate_p_traits<population_type>								mutate_p_traits_type;

		//typedef simple_mutate_p_traits<population_type>								mutate_p_traits_type;

		/// The local_search_traits type - basic
		typedef no_local_search_traits	<	population_type
										,	random_type
										,	rmake_traits_type
										,	fitness_traits_type
										>												local_search_traits_type;

		/*typedef network_local_search_traits	<	network_type
											,	population_type
											,	random_type
											,	rmake_traits_type
											,	fitness_traits_type
											>											local_search_traits_type;*/
	/// @}
};

/*!\brief wga_network class
 * 
 * \param Network the network type
 * \param Cfg the config type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Network
		,	typename_param_k Cfg = wga_default_ga_config<Network>
		>
class wga_network
	: public ga_base<wga_traits<Cfg> >
{
	/// \name Types
	/// @{
	public:
		typedef ga_base<wga_traits<Cfg> >							base_type;
		typedef wga_network											class_type;
		typedef typename_type_k base_type::ga_traits_type			ga_traits_type;
		typedef typename_type_k ga_traits_type::size_type			size_type;
		typedef typename_type_k ga_traits_type::bool_type			bool_type;
		typedef typename_type_k ga_traits_type::float_type			float_type;
		typedef typename_type_k ga_traits_type::index_type			index_type;
		typedef typename_type_k ga_traits_type::int_type			int_type;
		typedef typename_type_k ga_traits_type::population_type		population_type;
		typedef typename_type_k ga_traits_type::individual_type		individual_type;
		typedef typename_type_k ga_traits_type::random_type			random_type;
		typedef typename_type_k ga_traits_type::scopes_type			scopes_type;
		typedef typename_type_k ga_traits_type::scope_type			scope_type;
		typedef typename_type_k ga_traits_type::network_type		network_type;
		typedef typename_type_k network_type::rand_type				rand_type;
		typedef typename_type_k network_type::samples_type			samples_type;
		typedef typename_type_k network_type::sample_type			sample_type;
	/// @}
		
	/// \name Constructors
	/// @{
	public:
		wga_network()
			: base_type()
		{}
		explicit_k wga_network	(	network_type& net
								,	scope_type const& sp	= scope_type(-1, 1)
								,	size_type pop_size		= 63
								,	float_type cross_p		= 0.65
								,	float_type mutate_p		= 0.001
								,	random_type const& rand	= random_type()
								)
			: base_type()
		{
			this->ga_traits().network(net);
			this->ga_traits().scopes(scopes_type(sp, net.arcs_size()));
			this->ga_traits().pop_size(pop_size);
			this->ga_traits().cross_p(cross_p);
			this->ga_traits().mutate_p(mutate_p);
			this->ga_traits().rand(rand);
		}
	/// @}

	/// \name Members
	/// @{
	public:
		enum {	en_input_size = network_type::en_input_size		};
		enum {	en_output_size = network_type::en_output_size	};
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// returns the number of the nodes in input-layer
		static size_type		inodes_size()		{ return network_type::inodes_size();	}
		/// returns the number of the nodes in output-layer
		static size_type		onodes_size()		{ return network_type::onodes_size();	}

		/// returns the random generator
		rand_type&				rand()				{ return this->ga_traits().network().rand();	}
		/// returns the const layers
		rand_type const&		rand() const		{ return this->ga_traits().network().rand();	}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialize network
		void		init()		//< need update
		{
			this->ga_traits().init_traits();
			this->ga_traits().network().init();
		}
		/// train samples
		void		train(samples_type& sps, size_type train_n = 1)
		{
			// initialize traits
			this->ga_traits().samples(sps);
			this->ga_traits().max_g(train_n);
			this->ga_traits().init_traits();

			// run genetic algorithm
			this->generate();

			// train network using best weights
			this->ga_traits().network().weights(this->best().weights());
			this->ga_traits().network().train(sps, train_n);
		}
		/// run the given sample
		void		run(sample_type& sp)
		{
			this->ga_traits().network().run(sp);
		}
		/// run the given samples
		/*void		run(samples_type& sps)
		{
			this->ga_traits().network().run(sps);
		}*/
		/// gets float output
		float_type	foutput(index_type id) const
		{
			return this->ga_traits().network().foutput(id);
		}
		/// gets bool output 
		bool_type	boutput(index_type id) const
		{
			return this->ga_traits().network().boutput(id);
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_WGA_NETWORK_H */
/* //////////////////////////////////////////////////////////////////// */
