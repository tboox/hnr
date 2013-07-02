/* ///////////////////////////////////////////////////////////////////////
 * File:		kfold_cross_validator.h		
 *
 * Created:		09.04.05		
 * Updated:		09.04.05
 *
 * Brief:		The kfold_cross_validator class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_KFOLD_CROSS_VALIDATOR_H
#define EXTL_INTELLIGENCE_ANN_KFOLD_CROSS_VALIDATOR_H

/*!\file kfold_cross_validator.h
 * \brief kfold_cross_validator class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error kfold_cross_validator.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE


/*!brief kfold_cross_validator
 *
 * \param NetWork the networks type
 * \param NetVdtr the network validator type
 * \param K k-fold validation
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k NetWork
		,	typename_param_k NetVdtr
		,	e_size_t K = 10
		>
class kfold_cross_validator
{
	/// \name Types
	/// @{
	public:
		typedef kfold_cross_validator												class_type;
		typedef NetWork																network_type;
		typedef typename_type_k network_type::size_type								size_type;
		typedef typename_type_k network_type::bool_type								bool_type;
		typedef typename_type_k network_type::index_type							index_type;
		typedef typename_type_k network_type::float_type							float_type;
		typedef typename_type_k network_type::sample_type							sample_type;
		typedef typename_type_k network_type::samples_type							samples_type;
		typedef NetVdtr																validator_type;
	/// @}

	/// \name Members
	/// @{
	private:
		/// the mean square error, range: [0, 1]
		float_type																	m_mse;
		/// the error rate, range: [0, 1]
		float_type																	m_erate;
		/// network validator
		validator_type																m_validator;
	/// @}

	/// \name Constants
	/// @{
	public:
		enum { en_kfold = K	};
	/// @}

	/// \name Constructors
	/// @{
	public:
		kfold_cross_validator()
			: m_mse(0)
			, m_erate(0)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// returns the mean square error, range: [0, 1]
		float_type					mse() const						{ return m_mse;				}

		/// returns the error rate, range: [0, 1]
		float_type					erate() const					{ return m_erate;			}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// \note sps must have real outputs
		void	validate(network_type const& network, samples_type& sps, size_type train_n = 100)
		{
			// initialize mse & error rate
			m_mse = 0;
			m_erate = 0;

			size_type sps_n = sps.size();
			EXTL_ASSERT(size_type(en_kfold) <= sps_n);

			// validate samples
			size_type part_n = sps_n / en_kfold;
			for (index_type k = 0; k < en_kfold; ++k)
			{
				// calculates validated range
				index_type b = part_n * k;
				index_type e = part_n * (k + 1);
				if (k == en_kfold - 1) e = sps_n;

				samples_type vsps;	// validated samples
				samples_type tsps;	// trained samples
				for (index_type i = 0; i < sps_n; ++i)
				{
					// split samples
					if (i >= b && i < e) vsps.push_back(sps[i]);
					else tsps.push_back(sps[i]);
				}

				// train network
				network_type net(network);
				net.init();
				net.train(tsps, train_n);
				m_validator.validate(net, vsps);

				// validate network
				m_mse += m_validator.mse();
				m_erate += m_validator.erate();
			}

			m_mse /= en_kfold;
			m_erate /= en_kfold;
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_KFOLD_CROSS_VALIDATOR_H */
/* //////////////////////////////////////////////////////////////////// */
