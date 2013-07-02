/* ///////////////////////////////////////////////////////////////////////
 * File:		pca_mixed_network.h		
 *
 * Created:		09.03.15		
 * Updated:		09.03.15
 *
 * Brief:		The pca_mixed_network class - PCA & other network
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_H
#define EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_H

/*!\file pca_mixed_network.h
 * \brief pca_mixed_network class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error pca_mixed_network.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "sample_converter.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief The pca_mixed_network class - PCA & other network
 * 
 * input => pca network => other network => output
 * \note PCANet.ouput == OtrNet.input
 *
 * \param PCANet the pca network
 * \param OtrNet the other network sudh as bp_network, ada_boosting_network...
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
class pca_mixed_network
{
	/// \name Constants 
	/// @{
	public:
		enum {	en_input_size = PCANet::en_input_size	};
		enum {	en_output_size = OtrNet::en_output_size	};
	/// @}

	/// \name Types
	/// @{
	public:
		typedef pca_mixed_network													class_type;
		typedef e_size_t															size_type;
		typedef e_bool_t															bool_type;
		typedef e_size_t															index_type;
		typedef e_float_t															float_type;
		typedef PCANet																pnet_type;
		typedef OtrNet																onet_type;
		typedef typename_type_k onet_type::rand_type								rand_type;	
		typedef typename_type_k pnet_type::samples_type								psamples_type;
		typedef typename_type_k pnet_type::sample_type								psample_type;
		typedef typename_type_k onet_type::samples_type								osamples_type;
		typedef typename_type_k onet_type::sample_type								osample_type;
		typedef typename_type_k sample_selector	<	en_input_size
												,	en_output_size
												>::bool_sample_type					sample_type;
		typedef typename_type_k buffer_selector<sample_type>::large_buffer_type		samples_type;
		typedef normalized_converter<OtrNet::en_input_size, OtrNet::en_output_size>	converter_type;
	/// @}

	/// \name Members
	/// @{
	private:
		pnet_type																	m_pnet;
		onet_type																	m_onet;
		converter_type																m_converter;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k pca_mixed_network(pnet_type const& pnet, onet_type const& onet)
			: m_pnet(pnet)
			, m_onet(onet)
			, m_converter()
		{
			init();
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// return the reference of the pca network
		pnet_type&				pnet()			{ return m_pnet;	}
		/// return the const reference of the pca network
		pnet_type const&		pnet() const	{ return m_pnet;	}

		/// return the reference of the other network
		onet_type&				onet()			{ return m_onet;	}
		/// return the const reference of the other network
		onet_type const&		onet() const	{ return m_onet;	}

		/// returns the number of the nodes in input-layer
		static size_type		inodes_size()		{ return en_input_size;	}
		/// returns the number of the nodes in output-layer
		static size_type		onodes_size()		{ return en_output_size;}

		/// returns the random generator
		rand_type&				rand()				{ return onet().rand();	}
		/// returns the const random generator
		rand_type const&		rand() const		{ return onet().rand();	}

		/// returns the converter
		converter_type&			converter()			{ return m_converter;	}
		/// returns the const converter
		converter_type const&	converter() const	{ return m_converter;	}

		/// gets float output
		float_type				foutput(index_type i) const	{ return onet().foutput(i);	}

		/// gets bool output
		bool_type				boutput(index_type i) const	{ return onet().boutput(i);	}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialize network
		void					init();
		/// train the multi-samples
		/// \param otrain_n the training intensity of the other network
		/// \param ptrain_n the training intensity of the pca network
		void					train(samples_type& sps, size_type otrain_n = 1, size_type ptrain_n = 100);
		/// run the given sample
		void					run(sample_type& sp);
	/// @}

	/// \name Helpers
	/// @{
	private:
		void					p2o(psample_type const& psp, osample_type& osp);
		void					s2p(sample_type const& sp, psample_type& psp);
		void					o2s(osample_type const& osp, sample_type& sp);
		void					s2o(sample_type const& sp, osample_type& osp);
	/// @}

};
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
inline void pca_mixed_network<PCANet, OtrNet>::init()
{
	pnet().init();
	onet().init();
}
/* sps(10:3) <=> psps(10:5) & osps(5:3)
 * sps.intput => psps.output	=> input	\
 *												=> osps.output => sps.output
 * sps.real						=> real		/
 */
template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
inline void pca_mixed_network<PCANet, OtrNet>::train(samples_type& sps, size_type otrain_n, size_type ptrain_n)
{
	index_type i;
	size_type sps_n = sps.size();

	// sps.input => psps.input
	psamples_type psps(sps_n);
	for (i = 0; i < sps_n; ++i) s2p(sps[i], psps[i]);

	// trains the pca network using psps
	pnet().train(psps, ptrain_n);
	// gets outputs of the psps
	for (i = 0; i < sps_n; ++i) psps[i] = pnet().run(psps[i]);
	
	// psps.input & sps.output => osps.input & osps.output
	osamples_type osps(sps_n);
	for (i = 0; i < sps_n; ++i) 
	{
		p2o(psps[i], osps[i]);
		s2o(sps[i], osps[i]);
	}

	// normalize inputs
	m_converter.convert_input(osps);

	// trains the other network using osps
	onet().train(osps, otrain_n);
}

template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
inline void pca_mixed_network<PCANet, OtrNet>::run(sample_type& sp)
{
	// sp.input => psp.input
	psample_type psp;
	s2p(sp, psp);

	// runs pca network using psp
	psp = pnet().run(psp);

	// psp.input => osp.input
	osample_type osp;
	p2o(psp, osp);

	// normalize input
	m_converter.convert_input(osp);

	// runs other network using osp
	onet().run(osp);

	// psp.output => sp.output
	o2s(osp, sp);
}
template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
inline void pca_mixed_network<PCANet, OtrNet>::p2o(psample_type const& psp, osample_type& osp)
{
	EXTL_ASSERT(psp.output_size() == osp.input_size());
	// only need input before training network using sample
	size_type n = psp.output_size();
	for (index_type i = 0; i < n; ++i) osp.set_finput(i, psp.get_foutput(i));
}

template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
inline void pca_mixed_network<PCANet, OtrNet>::s2p(sample_type const& sp, psample_type& psp)
{
	EXTL_ASSERT(sp.input_size() == psp.input_size());
	// only need input before training network using sample
	size_type n = sp.input_size();
	for (index_type i = 0; i < n; ++i) psp.set_binput(i, sp.get_binput(i));
}
template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
inline void pca_mixed_network<PCANet, OtrNet>::o2s(osample_type const& osp, sample_type& sp)
{
	EXTL_ASSERT(sp.output_size() == osp.output_size());
	// only need output after running network using sample
	size_type n = osp.output_size();
	for (index_type i = 0; i < n; ++i) sp.set_boutput(i, osp.get_boutput(i));
}
template<	typename_param_k PCANet
		,	typename_param_k OtrNet
		>
inline void pca_mixed_network<PCANet, OtrNet>::s2o(sample_type const& sp, osample_type& osp)
{
	EXTL_ASSERT(sp.real_size() == osp.real_size());
	// only need real before training network using sample
	size_type n = sp.real_size();
	for (index_type i = 0; i < n; ++i) osp.set_freal(i, sp.get_freal(i));
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_PCA_MIXED_NETWORK_H */
/* //////////////////////////////////////////////////////////////////// */
