/* ///////////////////////////////////////////////////////////////////////
 * File:		bagging_networks.h		
 *
 * Created:		08.12.27		
 * Updated:		08.12.27
 *
 * Brief:		The bagging_networks class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_H
#define EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_H

/*!\file bagging_networks.h
 * \brief bagging_networks class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error bagging_networks.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief bagging_networks
 *
 * \param NetWork the network type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k NetWork>
class bagging_networks
{
	
	/// \name Public Types
	/// @{
	public:
		typedef bagging_networks													class_type;
		typedef NetWork																network_type;
		typedef typename_type_k network_type::size_type								size_type;
		typedef typename_type_k network_type::bool_type								bool_type;
		typedef typename_type_k network_type::index_type							index_type;
		typedef typename_type_k network_type::float_type							float_type;
		typedef typename_type_k network_type::sample_type							sample_type;
		typedef typename_type_k network_type::samples_type							samples_type;
		typedef typename_type_k network_type::rand_type								rand_type;
		typedef typename_type_k buffer_selector<network_type*>::buffer_type			networks_type;
		typedef typename_type_k buffer_selector<float_type>::buffer_type			float_buffer_type;
	/// @}

	/// \name Members
	/// @{
	private:
		networks_type																m_networks;
		float_buffer_type															m_foutputs;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k bagging_networks	(	network_type* network_0 = NULL
									,	network_type* network_1 = NULL	
									,	network_type* network_2 = NULL	
									,	network_type* network_3 = NULL
									,	network_type* network_4 = NULL
									,	network_type* network_5 = NULL
									,	network_type* network_6 = NULL	
									,	network_type* network_7 = NULL
									,	network_type* network_8 = NULL
									,	network_type* network_9 = NULL
									)
			: m_networks()
			, m_foutputs()
		{
			if (NULL != network_0) m_networks.push_back(network_0);
			if (NULL != network_1) m_networks.push_back(network_1);
			if (NULL != network_2) m_networks.push_back(network_2);
			if (NULL != network_3) m_networks.push_back(network_3);
			if (NULL != network_4) m_networks.push_back(network_4);
			if (NULL != network_5) m_networks.push_back(network_5);
			if (NULL != network_6) m_networks.push_back(network_6);
			if (NULL != network_7) m_networks.push_back(network_7);
			if (NULL != network_8) m_networks.push_back(network_8);
			if (NULL != network_9) m_networks.push_back(network_9);
		}
		bagging_networks(class_type const& rhs)
			: m_networks(rhs.m_networks)
			, m_foutputs(rhs.m_foutputs)
		{
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		networks_type&			networks()				{ return m_networks;				}
		networks_type const&	networks() const		{ return m_networks;				}

		float_type				foutput(index_type i) const;
		bool_type				boutput(index_type i) const;

		/// returns the random generator
		rand_type&				rand()			{ return rand_type();	}
		/// returns the const layers
		rand_type const&		rand() const	{ return rand_type();	}
	/// @}

	/// \name Operators
	/// @{
	public:
		void					swap(class_type& rhs);
	/// @}

	/// \name Methods
	/// @{
	public:
		/// train samples and return mse
		void					train(samples_type& sps, size_type train_n = 1);
		/// run the given sample
		void					run(sample_type& sp);
		/// run the given samples
		//void					run(samples_type& sps);
	/// @}

	/// \name helpers
	/// @{
	private:
		float_buffer_type&			foutputs()				{ return m_foutputs;	}
		float_buffer_type const&	foutputs() const		{ return m_foutputs;	}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
template<typename_param_k NetWork>
inline void bagging_networks<NetWork>::swap(class_type& rhs)	
{
	m_networks.swap(rhs.m_networks); 
	m_foutputs.swap(rhs.m_foutputs);
}
template<typename_param_k NetWork>
inline void bagging_networks<NetWork>::train(samples_type& sps, size_type train_n)
{
	index_type i, j;
	size_type sps_n = sps.size();
	size_type networks_n = networks().size();
	for (i = 0; i < networks_n; ++i)
	{
		EXTL_ASSERT(NULL != networks()[i]);
		// select sps_n samples randomly
		samples_type tsps;
		for (j = 0; j < sps_n; ++j)
		{
			index_type sps_i = networks()[i]->rand().generate(0, sps_n);
			tsps.push_back(sps[sps_i]);
		}

		// train
		networks()[i]->train(tsps, train_n);
	}
}

template<typename_param_k NetWork>
inline void bagging_networks<NetWork>::run(sample_type& sp)
{
	index_type i, j;

	// initialize foutputs
	size_type output_n = sp.output_size();
	foutputs().resize(output_n);
	for (i = 0; i < output_n; ++i)
		foutputs()[i] = 0;

	size_type networks_n = networks().size();
	for (i = 0; i < networks_n; ++i)
	{
		EXTL_ASSERT(NULL != networks()[i]);
		networks()[i]->run(sp);

		// accumulate outputs
		for (j = 0; j < output_n; ++j)
			foutputs()[j] += static_cast<float_type>(sp.get_boutput(j));
	}

	// calculate the average of the outputs
	for (j = 0; j < output_n; ++j)
	{
		foutputs()[j] /= networks_n;
		sp.set_foutput(j, foutputs()[j]);
	}
}
/*template<typename_param_k NetWork>
inline void bagging_networks<NetWork>::run(samples_type& sps)
{
	size_type sps_n = sps.size();
	for (index_type i = 0; i < sps_n; ++i)
		run(sps[i]);

}*/
template<typename_param_k NetWork>
inline typename_type_ret_k bagging_networks<NetWork>::
float_type bagging_networks<NetWork>::foutput(index_type i) const
{
	EXTL_ASSERT(i < m_foutputs.size());
	return m_foutputs[i];	
}
template<typename_param_k NetWork>
inline typename_type_ret_k bagging_networks<NetWork>::
bool_type bagging_networks<NetWork>::boutput(index_type i) const
{
	EXTL_ASSERT(i < m_foutputs.size());
	return xtl_round45(m_foutputs[i] == 1);	
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_BAGGING_NETWORKS_H */
/* //////////////////////////////////////////////////////////////////// */
