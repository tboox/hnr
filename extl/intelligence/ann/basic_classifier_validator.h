/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_classifier_validator.h		
 *
 * Created:		08.12.29		
 * Updated:		08.12.29
 *
 * Brief:		The basic_classifier_validator class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_BASIC_CLASSIFIER_VALIDATOR_H
#define EXTL_INTELLIGENCE_ANN_BASIC_CLASSIFIER_VALIDATOR_H

/*!\file basic_classifier_validator.h
 * \brief basic_classifier_validator class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error basic_classifier_validator.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE


/*!brief basic_classifier_validator
 *
 * \param Classifier the classifiers type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Classifier>
class basic_classifier_validator
{
	/// \name Types
	/// @{
	public:
		typedef basic_classifier_validator												class_type;
		typedef Classifier																classifier_type;
		typedef typename_type_k classifier_type::size_type								size_type;
		typedef typename_type_k classifier_type::bool_type								bool_type;
		typedef typename_type_k classifier_type::index_type								index_type;
		typedef typename_type_k classifier_type::float_type								float_type;
		typedef typename_type_k classifier_type::sample_type							sample_type;
		typedef typename_type_k classifier_type::samples_type							samples_type;
		typedef bit_array	<	size_type
							,	typename_type_k buffer_selector<size_type>::buffer_type
							>															bools_type;
	/// @}

	/// \name Members
	/// @{
	private:
		/// the mean square error, range: [0, 1]
		float_type																		m_mse;
		/// the error rate, range: [0, 1]
		float_type																		m_erate;
		/// m_is_errors[i] is true if the samples[i] is incorrect
		bools_type																		m_is_errors;
	/// @}

	/// \name Constructors
	/// @{
	public:
		basic_classifier_validator()
			: m_mse(0)
			, m_erate(0)
			, m_is_errors()
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

		/// returns the error rate, range: [0, 1]
		bool_type					is_error(index_type i) const	{ EXTL_ASSERT(i < m_is_errors.size()); return m_is_errors[i];	}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// \note sps must have real outputs
		void	validate(classifier_type& classifier, samples_type& sps)
		{
			// initialize mse & error rate
			m_mse = 0;
			m_erate = 0;

			// validate samples
			index_type i, j;
			size_type sps_n = sps.size();
			m_is_errors.resize(sps_n);
			for (i = 0; i < sps_n; ++i)
			{
				// run classifier
				classifier.classify(sps[i]);

				// set true if output != real output
				bool_type is_error = e_false_v;
				size_type output_n = sps[i].output_size();
				for (j = 0; j < output_n; ++j)
				{
					if (sps[i].get_boutput(j) != sps[i].get_breal(j))
					{
						is_error = e_true_v;
						break;
					}
				}

				// accumulate error rate
				m_erate += static_cast<float_type>(is_error);

				// save is_error 
				m_is_errors.set(i, is_error);

				// calculate square error
				float_type square_error = 0;
				for (j = 0; j < output_n; ++j)
				{
					float_type error = sps[i].get_freal(j) - classifier.network().foutput(j);
					square_error += error * error;
				}
				//square_error /= 2;
				square_error /= output_n;
				square_error = xtl_sqrt(square_error);

				// accumulate mean square error
				m_mse += square_error;
			}
			
			m_mse /= sps_n;
			m_erate /= sps_n;
		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_BASIC_CLASSIFIER_VALIDATOR_H */
/* //////////////////////////////////////////////////////////////////// */
