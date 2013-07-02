/* ///////////////////////////////////////////////////////////////////////
 * File:		pca_network_validator.h		
 *
 * Created:		09.03.24		
 * Updated:		09.03.24
 *
 * Brief:		The pca_network_validator class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_PCA_NETWORK_VALIDATOR_H
#define EXTL_INTELLIGENCE_ANN_PCA_NETWORK_VALIDATOR_H

/*!\file pca_network_validator.h
 * \brief pca_network_validator class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error pca_network_validator.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE


/*!brief pca_network_validator
 *
 * \param NetWork the networks type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k NetWork>
class pca_network_validator
{
	/// \name Types
	/// @{
	public:
		typedef pca_network_validator												class_type;
		typedef NetWork																network_type;
		typedef typename_type_k network_type::size_type								size_type;
		typedef typename_type_k network_type::bool_type								bool_type;
		typedef typename_type_k network_type::index_type							index_type;
		typedef typename_type_k network_type::float_type							float_type;
		typedef typename_type_k network_type::sample_type							sample_type;
		typedef typename_type_k network_type::samples_type							samples_type;
	/// @}

	/// \name Members
	/// @{
	private:
		/// the mean square error, range: [0, 1]
		float_type																	m_mse;
	/// @}

	/// \name Constructors
	/// @{
	public:
		pca_network_validator()
			: m_mse(0)
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// returns the mean square error, range: [0, 1]
		float_type					mse() const						{ return m_mse;	}

		/// \note not support, only for placeholder
		float_type					erate() const					{ return 0;		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// \note sps must have real outputs
		void	validate(network_type& network, samples_type& sps)
		{
			// initialize mse
			m_mse = 0;

			// validate samples
			size_type sps_n = sps.size();
			for (index_type i = 0; i < sps_n; ++i)
			{
				// run network
				sample_type ret = network.run(sps[i]);

				// calculate square error
				size_type input_n = sps[i].input_size();
				float_type mean_square_error = 0;
				for (index_type j = 0; j < input_n; ++j)
				{
					float_type error = ret.get_finput(j) - sps[i].get_finput(j);
					mean_square_error += error * error;
				}
				//mean_square_error /= 2;
				mean_square_error /= input_n;
				mean_square_error = xtl_sqrt(mean_square_error);

				// accumulate mean square error
				m_mse += mean_square_error;
			}
			
			m_mse /= sps_n;
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_PCA_NETWORK_VALIDATOR_H */
/* //////////////////////////////////////////////////////////////////// */
