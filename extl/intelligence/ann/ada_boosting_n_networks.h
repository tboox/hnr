/* ///////////////////////////////////////////////////////////////////////
 * File:		ada_boosting_n_networks.h		
 *
 * Created:		08.12.27		
 * Updated:		09.06.07
 *
 * Brief:		The ada_boosting_n_networks class - for binary-class problem
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_N_NETWORKS_H
#define EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_N_NETWORKS_H

/*!\file ada_boosting_n_networks.h
 * \brief ada_boosting_n_networks class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_NETWORKS_SUPPORT)
#	error ada_boosting_n_networks.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "network_validator.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief ada_boosting_n_networks
 *
 * \param NetWork the network type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k NetWork>
class ada_boosting_n_networks
{
	
	/// \name Types
	/// @{
	public:
		typedef ada_boosting_n_networks												class_type;
		typedef NetWork																network_type;
		typedef typename_type_k network_type::size_type								size_type;
		typedef typename_type_k network_type::bool_type								bool_type;
		typedef typename_type_k network_type::index_type							index_type;
		typedef typename_type_k network_type::float_type							float_type;
		typedef typename_type_k network_type::sample_type							sample_type;
		typedef typename_type_k network_type::samples_type							samples_type;
		typedef typename_type_k network_type::rand_type								rand_type;
		typedef typename_type_k network_type::floats_type							floats_type;
		typedef basic_network_validator<network_type>								validator_type;
		typedef typename_type_k buffer_selector<network_type>::buffer_type			networks_type;
	/// @}

	/// \name Members
	/// @{
	private:
		/// the networks
		networks_type																m_networks;
		/// the outputs
		floats_type																	m_foutputs;
		/// the weight of every networks
		floats_type																	m_weights;
		/// the network validator 
		validator_type																m_validator;
	/// @}

	/// \name Constants 
	/// @{
	public:
		enum {	en_input_size = network_type::en_input_size	};
		enum {	en_output_size = network_type::en_output_size	};
	/// @}

	/// \name Constructors
	/// @{
	public:
		ada_boosting_n_networks()
			: m_networks()
			, m_foutputs()
			, m_weights()
			, m_validator()
		{
			init();
		}
		ada_boosting_n_networks(class_type const& rhs)
			: m_networks(rhs.m_networks)
			, m_foutputs(rhs.m_foutputs)
			, m_weights(rhs.m_weights)
			, m_validator(rhs.m_validator)
		{
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		networks_type&				networks()						{ return m_networks;	}
		networks_type const&		networks() const				{ return m_networks;	}

		network_type&				network(index_type i)			{ EXTL_ASSERT(i < networks().size()); return networks()[i];	}
		network_type const&			network(index_type i) const		{ EXTL_ASSERT(i < networks().size()); return networks()[i];	}
	
		void						push_back(network_type const& net);

		/// returns the float output 
		float_type					foutput(index_type i) const;

		/// returns the bool output
		bool_type					boutput(index_type i) const;

		/// returns the random generator
		rand_type&					rand()			{ return network().rand();	}
		/// returns the const layers
		rand_type const&			rand() const	{ return network().rand();	}
	/// @}

	/// \name Operators
	/// @{
	public:
		void						swap(class_type& rhs);
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialize networks
		void						init();
		/// train samples and return mse
		void						train(samples_type& sps, size_type train_n = 1);
		/// run the given sample
		void						run(sample_type& sp);
		/// run the given samples
		//void						run(samples_type& sps);
	/// @}

	/// \name Attributes
	/// @{
	public:
		floats_type&				foutputs()				{ return m_foutputs;	}
		floats_type const&			foutputs() const		{ return m_foutputs;	}

		floats_type&				weights()							{ return m_weights;		}
		floats_type const&			weights() const						{ return m_weights;		}
		void						weights(floats_type const& wgts)	{ m_weights = wgts;		}

		validator_type&				validator()				{ return m_validator;	}
		validator_type const&		validator() const		{ return m_validator;	}
	/// @}

	/// \name helpers
	/// @{
	private:
		/// train network using the given weights
		void						train_network(network_type& net, samples_type& sps, size_type train_n, floats_type const& sps_ws);
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
template<typename_param_k NetWork>
void ada_boosting_n_networks<NetWork>::push_back(network_type const& net)
{
	networks().push_back(net);
	weights().resize(networks().size());
}
template<typename_param_k NetWork>
void ada_boosting_n_networks<NetWork>::swap(class_type& rhs)	
{ 
	m_networks.swap(rhs.m_networks); 
	m_foutputs.swap(rhs.m_foutputs);
	m_weights.swap(rhs.m_weights);
	std_swap(m_validator, rhs.m_validator);
}
template<typename_param_k NetWork>
void ada_boosting_n_networks<NetWork>::train_network(network_type& net, samples_type& sps, size_type train_n, floats_type const& sps_ws)
{
	size_type sps_n = sps.size();
	for (size_type train_i = 0; train_i < train_n; ++train_i)
	{
		for (index_type i = 0; i < sps_n; ++i)
		{
			float_type p = net.rand().fgenerate(0, 1);

			float_type sum = 0;
			index_type j;
			for (j = 0; (sum <= p) && (j < sps_n); ++j)
				sum += sps_ws[j];
			j = j > 0? j - 1 : 0;
			
			//printf("train %d\n", j);
			net.train(sps[j]);
		}
	}
}
template<typename_param_k NetWork>
void ada_boosting_n_networks<NetWork>::train(samples_type& sps, size_type train_n)
{
	// initialize weights and corrects of samples
	size_type sps_n = sps.size();
	floats_type sample_weights(float_type(1.0) / sps_n, sps_n);

	// train networks
	index_type i, j;
	float_type networks_weights_sum = 0;
	size_type networks_n = networks().size();
	EXTL_ASSERT(weights().size() == networks_n);
	for (i = 0; i < networks_n; ++i)
	{
		// train samples using network(i)
		//network(i).train(sps, train_n);
		//train_network(network(i), sps, train_n, sample_weights);
		network(i).train(sps, sample_weights, train_n);

		// validate this network
		validator().validate(network(i), sps);

		// calculate weighted error rate
		float_type weighted_erate = 0;
		for (j = 0; j < sps_n; ++j)
		{
			//printf("sample_weights: %f %d\n", sample_weights[j], validator().is_error(j));

			// calculate weighted error rate
			// note: sample_weights[j] is normalized
			weighted_erate += sample_weights[j] * static_cast<float_type>(validator().is_error(j));
		}
		
		// avoid division by zero 
		if (weighted_erate < 0.000001) weighted_erate = 0.000001;
		if (weighted_erate > 0.999999) weighted_erate = 0.999999;

		// the weight of the network(i)
		EXTL_ASSERT(((1 - weighted_erate) / weighted_erate) > 0);

		weights()[i] = 0.5 * xtl_ln((1 - weighted_erate) / weighted_erate);
		//weights()[i] = 0.5 * xtl_ln((1 - weighted_erate) / weighted_erate) + xtl_ln(size_type(weighted_erate / (1 - weighted_erate)) + 1);
		//weights()[i] = 0.5 * xtl_ln((1 - weighted_erate) / weighted_erate) + xtl_ln(xtl_pow2(network_type::onodes_size()) - 1); 
		networks_weights_sum += weights()[i];

		//printf("weights:%f weighted_erate:%f\n", weights()[i], weighted_erate);
		EXTL_MESSAGE_ASSERT(weights()[i] >= 0, "maybe the networks is not converged");
		//if (weights()[i] < 0) weights()[i] = 0;

		// modify weights
		float_type sample_weights_sum = 0;
		for (j = 0; j < sps_n; ++j)
		{
			sample_weights[j] = sample_weights[j] * xtl_exp(weights()[i] * static_cast<float_type>(validator().is_error(j)));
			sample_weights_sum += sample_weights[j];
		}

		// normalize weights
		for (j = 0; j < sps_n; ++j) sample_weights[j] /= sample_weights_sum;

		//printf("\n");
	}
}

template<typename_param_k NetWork>
inline void ada_boosting_n_networks<NetWork>::run(sample_type& sp)
{
	index_type i, j;

	// initialize foutputs
	size_type output_n = sp.output_size();
	foutputs().resize(output_n);
	for (i = 0; i < output_n; ++i)
		foutputs()[i] = 0;

	// calculate the sum of weights
	size_type networks_n = networks().size();
	float_type weight_sum = 0;
	for (i = 0; i < networks_n; ++i)
		weight_sum += weights()[i];

	// run networks
	for (i = 0; i < networks_n; ++i)
	{
		// run
		network(i).run(sp);

		// accumulate outputs
		// the weighted average
		for (j = 0; j < output_n; ++j)
			foutputs()[j] += (weights()[i] * static_cast<float_type>(sp.get_boutput(j)) / weight_sum);
	}

	// calculate outputs
	for (j = 0; j < output_n; ++j)
	{
		// set result
		sp.set_foutput(j, foutputs()[j]);
	}
}
/*template<typename_param_k NetWork>
inline void ada_boosting_n_networks<NetWork>::run(samples_type& sps)
{
	size_type sps_n = sps.size();
	for (index_type i = 0; i < sps_n; ++i)
		run(sps[i]);

}*/
template<typename_param_k NetWork>
inline typename_type_ret_k ada_boosting_n_networks<NetWork>::
float_type ada_boosting_n_networks<NetWork>::foutput(index_type i) const
{
	EXTL_ASSERT(i < m_foutputs.size());
	return m_foutputs[i];	
}
template<typename_param_k NetWork>
inline typename_type_ret_k ada_boosting_n_networks<NetWork>::
bool_type ada_boosting_n_networks<NetWork>::boutput(index_type i) const
{
	EXTL_ASSERT(i < m_foutputs.size());
	return xtl_round45(m_foutputs[i] == 1);	
}
template<typename_param_k NetWork>
void ada_boosting_n_networks<NetWork>::init()
{
	index_type i;
	for (i = 0; i < networks().size(); ++i)
		network(i).init();

	for (i = 0; i < m_weights.size(); ++i)
		m_weights[i] = 0;

	for (i = 0; i < m_foutputs.size(); ++i)
		m_foutputs[i] = 0;
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_ADA_BOOSTING_N_NETWORKS_H */
/* //////////////////////////////////////////////////////////////////// */
