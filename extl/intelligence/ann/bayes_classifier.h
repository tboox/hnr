/* ///////////////////////////////////////////////////////////////////////
 * File:		bayes_classifier.h		
 *
 * Created:		09.06.14		
 * Updated:		09.06.14
 *
 * Brief:		The bayes_classifier class - for classifying samples using network
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_BAYES_CLASSIFIER_H
#define EXTL_INTELLIGENCE_ANN_BAYES_CLASSIFIER_H

/*!\file bayes_classifier.h
 * \brief bayes_classifier class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "network_validator.h"

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error basic_classifier_validator.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief bayes_classifier
 *
 * \param NetWork the network type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k NetWork>
class bayes_classifier
{
	
	/// \name Types
	/// @{
	public:
		typedef bayes_classifier													class_type;
		typedef NetWork																network_type;
		typedef typename_type_k network_type::size_type								size_type;
		typedef typename_type_k network_type::bool_type								bool_type;
		typedef typename_type_k network_type::index_type							index_type;
		typedef typename_type_k network_type::float_type							float_type;
		typedef typename_type_k network_type::sample_type							sample_type;
		typedef typename_type_k network_type::samples_type							samples_type;
		typedef typename_type_k network_type::rand_type								rand_type;
		typedef typename_type_k hash_selector<size_type, float_type>::hash_type		hash_type;
		typedef typename_type_k hash_type::iterator									hash_iterator;
		typedef typename_type_k hash_type::const_iterator							hash_const_iterator;
		typedef typename_type_k hash_selector<size_type, hash_type>::hash_type		hashes_type;
		typedef typename_type_k hashes_type::iterator								hashes_iterator;
		typedef typename_type_k hashes_type::const_iterator							hashes_const_iterator;
	/// @}

	/// \name Members
	/// @{
	private:
		/// the network
		network_type*																m_network;
		/// trained samples number
		hash_type																	m_samples_n;
		/// trained samples distribution
		hashes_type																	m_samples_d;
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
		explicit_k bayes_classifier(network_type* network = NULL)
			: m_network(network)
			, m_samples_n()
			, m_samples_d()
		{
		}
		bayes_classifier(class_type const& rhs)
			: m_network(rhs.m_network)
			, m_samples_n(rhs.m_samples_n)
			, m_samples_d(rhs.m_samples_d)
		{
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		network_type&				network()						{ EXTL_ASSERT(NULL != m_network); return *m_network;	}
		network_type const&			network() const					{ EXTL_ASSERT(NULL != m_network); return *m_network;	}

		size_type					classify_n() const				{ return m_samples_n.size();							}
	/// @}

	/// \name Methods
	/// @{
	public:
		size_type hamming(size_type v1, size_type v2)
		{
			size_type count = 0;
			for (size_type i = 0; i < (size_type)en_output_size; ++i)
			{
				size_type v1_i = (size_type(0x1) == ((v1 >> i) & size_type(0x1)));
				size_type v2_i = (size_type(0x1) == ((v2 >> i) & size_type(0x1)));
				if (v1_i != v2_i) count++;
			}
			return count;
		}
		/// init classifier using trained samples
		/// \note must be called after network training
		void init(samples_type& sps)
		{
			// clear data
			m_samples_n.clear();
			for (hashes_iterator pd = m_samples_d.begin(); pd != m_samples_d.end(); ++pd) pd->second().clear();
			m_samples_d.clear();

			// generate trained samples distribution
			size_type i = 0;
			for (i = 0; i < sps.size(); i++)
			{
				// gets trained sample output
				network().run(sps[i]);
				size_type dreal = sps[i].dreal();
				size_type doutput = sps[i].doutput();

				// stats the number of samples which belong to dreal
				// n(dreal)
				if (m_samples_n.count(dreal) == 0) m_samples_n[dreal] = 1;
				else ++m_samples_n[dreal];

				// stats the number of samples which belong to dreal and are considered to be doutput
				// n(doutput|dreal)
				if (m_samples_d[dreal].count(doutput) == 0) m_samples_d[dreal][doutput] = 1;
				else ++m_samples_d[dreal][doutput];
			}

			// calcuate samples distribution: p(doutput|dreal)
			for (hash_const_iterator p = m_samples_n.begin(); p != m_samples_n.end(); ++p)
			{
				//printf("dreal:%d count:%f => ", p->first(), p->second());
				for (hash_iterator pd = m_samples_d[p->first()].begin(); pd != m_samples_d[p->first()].end(); ++pd)
				{
					// p(doutput|dreal) = n(doutput|dreal) / n(dreal)
					pd->second() /= p->second();
					//printf("doutput:%d distribution:%f", pd->first(), pd->second());
				}
				//printf("\n");
			}

		}
		void classify(sample_type& sp)
		{
			// gets sample output
			network().run(sp);
			size_type doutput = sp.doutput();

			// cumulatives hamming distance
			hash_type real_pros;
			float_type hamming_total = 0;
			for (hash_const_iterator p = m_samples_n.begin(); p != m_samples_n.end(); ++p)
			{
				size_type dreal = p->first();
				real_pros[dreal] = en_output_size - hamming(doutput, dreal);
				hamming_total += real_pros[dreal];
			}
			if (hamming_total < 0.00001) hamming_total = 0.00001;

			// calcuate real pros
			for (hash_const_iterator p = m_samples_n.begin(); p != m_samples_n.end(); ++p)
			{
				size_type dreal = p->first();
				real_pros[dreal] /= hamming_total;
			}

			// cumulatives p(doutput_i|dreal) * p(dreal)
			hash_type pre_pros;
			float_type pre_total = 0;
			for (hash_const_iterator p = m_samples_n.begin(); p != m_samples_n.end(); ++p)
			{
				size_type dreal = p->first();

				// p(doutput_i|dreal) * p(dreal)
				if (m_samples_d[dreal].count(doutput) == 0) pre_pros[dreal] = 0;
				else pre_pros[dreal] = m_samples_d[dreal][doutput] * real_pros[dreal];

				pre_total += pre_pros[dreal];
			}

			size_type max_dreal = 0;
			float_type max_pro = -1;

			if (pre_total > 0.00001)
			{
				for (hash_const_iterator p = m_samples_n.begin(); p != m_samples_n.end(); ++p)
				{
					// bayes_pro = p(doutput_i|dreal) * p(dreal) / total
					size_type dreal = p->first();
					pre_pros[dreal] /= pre_total;

					// maximum bayes_pro
					if (pre_pros[dreal] > max_pro)
					{
						max_dreal = dreal;
						max_pro = pre_pros[dreal];
					}
				}
			}
			else
			{
				for (hash_const_iterator p = m_samples_n.begin(); p != m_samples_n.end(); ++p)
				{
					// bayes_pro = p(doutput_i|dreal) * p(dreal) / total
					size_type dreal = p->first();
					// maximum bayes_pro
					if (real_pros[dreal] > max_pro)
					{
						max_dreal = dreal;
						max_pro = real_pros[dreal];
					}
				}
			}

			// reject to clasify if the max_pro is too small
			//if (max_pro < 1 / float_type(classify_n())) max_dreal = -1;

			// dreal with maximum posterior probability is considered to be doutput
			sp.doutput(max_dreal);
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_BAYES_CLASSIFIER_H */
/* //////////////////////////////////////////////////////////////////// */
