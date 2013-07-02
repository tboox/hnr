/* ///////////////////////////////////////////////////////////////////////
 * File:		ghia_network.h		
 *
 * Created:		09.03.15		
 * Updated:		09.03.15
 *
 * Brief:		The ghia_network class for PCA
 * Detail:		GHIA: The Generalized Hebbian Improved Algorithm for PCA(Principal Component Analysis)
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_GHIA_NETWORK_H
#define EXTL_INTELLIGENCE_ANN_GHIA_NETWORK_H

/*!\file ghia_network.h
 * \brief ghia_network class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error ghia_network.h is not supported by the current compiler.
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

/*!brief ghia_network
 * 
 * network: the self-organizing network
 * GHIA: The Generalized Hebbian Improved Algorithm for PCA(Principal Component Analysis)
 * \note can not use net for optimization
 *
 * input:			x1, x2, x3, ... xm
 * output:			y1, y2, ... yn
 * approximate:		a1, a2, a3, ... am
 * eigenvectors:	t1, t2, t3, ... tm
 * m > n
 *
 * calculate output:		y = t1 * x1 + t2 *x2 .. tm * xm
 * calculate approximate:	x = t1 * y1 + t2 *y2 .. tm * ym
 *
 * <pre>
 * 
 * []--------\
 *            /[]
 * []------>|       
 *            \[] 
 * []--------/
 *
 * </pre>
 *
 * \param InN the input demension
 * \param OutN the output demension
 * \param Ctr the converter type
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Ctr = standardized_converter<InN, OutN>
		>
class ghia_network
{
	/// \name Types
	/// @{
	public:
		typedef ghia_network														class_type;
		typedef e_size_t															size_type;
		typedef e_bool_t															bool_type;
		typedef e_size_t															index_type;
		typedef e_float_t															float_type;
		typedef typename_type_k rand_selector::rand_type							rand_type;	
		typedef typename_type_k vvector_selector<float_type>::vvector_type			vector_type;
		typedef typename_type_k sample_selector<InN, OutN>::float_sample_type		sample_type;
		typedef typename_type_k buffer_selector<sample_type>::large_buffer_type		samples_type;
		typedef Ctr																	converter_type;
	/// @}

	/// \name Constants 
	/// @{
	public:
		enum {	en_input_size = InN		};
		enum {	en_output_size = OutN	};
	/// @}

	/// \name Members
	/// @{
	private:
		float_type																	m_outputs[en_output_size];	
		vector_type																	m_vectors[en_output_size];
		float_type																	m_lrate;
		rand_type																	m_rand;
		converter_type																m_converter;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k ghia_network(float_type lrate = 0.0001)
			: m_lrate(lrate)
			, m_rand()
			, m_converter()
		{
			init();
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// returns the number of the nodes in input-layer
		static size_type		inodes_size()		{ return en_input_size;	}
		/// returns the number of the nodes in output-layer
		static size_type		onodes_size()		{ return en_output_size;}
		/// returns the number of the eigenvectors
		static size_type		vectors_size()		{ return en_output_size;}

		/// returns the random generator
		rand_type&				rand()				{ return m_rand;		}
		/// returns the const random generator
		rand_type const&		rand() const		{ return m_rand;		}

		/// returns the converter
		converter_type&			converter()			{ return m_converter;	}
		/// returns the const converter
		converter_type const&	converter() const	{ return m_converter;	}

		/// Returns the learning rate, range: [0, 1]
		float_type				lrate() const		{ return m_lrate;		}

		/// gets the eigenvector of the i-th principal component
		vector_type&			vector(index_type i)		{ EXTL_ASSERT(i < en_output_size); return m_vectors[i];	}
		/// gets the eigenvector of the i-th principal component
		vector_type const&		vector(index_type i) const	{ EXTL_ASSERT(i < en_output_size); return m_vectors[i];	}

		/// gets float output
		float_type				foutput(index_type i) const	{ return m_outputs[i];						}

		/// gets bool output
		bool_type				boutput(index_type i) const	{ return (xtl_round45(foutput(i)) == 1);	}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialize network
		void					init();
		/// train the multi-samples
		void					train(samples_type const& sps, size_type train_n = 1);
		/// run the given sample
		/// ret.input is approximate value using pca
		/// ret.output is pca output
		sample_type const		run(sample_type const& sp);
	/// @}

};
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Ctr
		>
inline void ghia_network<InN, OutN, Ctr>::init()
{
	index_type i, j;
	for (i = 0; i < en_output_size; ++i)
	{
		// initialize output nodes
		m_outputs[i] = 0;

		// initialize vector randomly
		vector(i).resize(en_input_size);
		for (j = 0; j < en_input_size; ++j)
			vector(i)[j] = rand().fgenerate(-0.1, 0.1);
	}
}
#if 1	// for optimization
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Ctr
		>
inline void ghia_network<InN, OutN, Ctr>::train(samples_type const& sps, size_type train_n)
{
	// standardize
	samples_type std_sps(sps);
	m_converter.convert_input(std_sps);

	vector_type tmp;
	typedef typename_type_k buffer_selector<vector_type>::buffer_type	buffer_type;
	size_type sps_n = std_sps.size();
	buffer_type	outputs(sps_n);

	index_type i, j;
	for (j = 0; j < sps_n; ++j) outputs[j] = vector_type(0.0, en_input_size);
	for (i = 0; i < en_output_size; ++i)
	{
		double lr = lrate() * (i + 1);
		size_type n = train_n * sps_n;
		for (j = 0; j < n; ++j)
		{
			sample_type& sp = std_sps[j % sps_n];

			// modify vevtors
			m_outputs[i] = vector(i).dot(sp.input());

			// adaptive learning rate
			lr = lr / (0.99 + m_outputs[i] * m_outputs[i] * lr);

			// for optimization, reduce temporary variables
			// vector(i) += lr * m_outputs[i] * (sp.input() - (outputs[j % sps_n] + vector(i) * m_outputs[i]));
			tmp = sp.input();
			tmp -= outputs[j % sps_n];
			tmp -= vector(i) * m_outputs[i];
			tmp *= m_outputs[i] * lr;
			vector(i) += tmp;

			if (vector(i).is_orthogonal()) break;
		}
		//printf("%d\n", j);

		// save outputs
		for (j = 0; j < sps_n; ++j) outputs[j] += vector(i) * vector(i).dot(std_sps[j].input());	
	}
}
#else
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Ctr
		>
inline void ghia_network<InN, OutN, Ctr>::train(samples_type const& sps, size_type train_n)
{
	// standardize
	samples_type std_sps(sps);
	m_converter.convert_input(std_sps);

	vector_type	outputs;
	size_type sps_n = std_sps.size();
	for (size_type i = 0; i < en_output_size; ++i)
	{
		double lr = lrate() * (i + 1);
		size_type n = train_n * sps_n;
		for (size_type j = 0; j < n; ++j)
		{
			sample_type& sp = std_sps[j % sps_n];

			// calculate old outputs
			outputs = vector(0) * vector(0).dot(sp.input());
			for (size_type k = 1; k <= i; ++k) outputs += vector(k) * vector(k).dot(sp.input());	//<= too slowly

			// modify vevtors
			m_outputs[i] = vector(i).dot(sp.input());

			// adaptive learning rate
			lr = lr / (0.99 + m_outputs[i] * m_outputs[i] * lr);

			vector(i) += lr * m_outputs[i] * (sp.input() - outputs);
			if (vector(i).is_orthogonal()) break;
		}
		//printf("%d\n", j);
	}
}
#endif
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Ctr
		>
inline typename_type_ret_k ghia_network<InN, OutN, Ctr>::
sample_type const ghia_network<InN, OutN, Ctr>::run(sample_type const& sp)
{
	// standardize
	sample_type ret(sp);
	m_converter.convert_input(ret);

	// calculate outputs after dimensionality reduction
	vector_type apx_input(0.0, sp.input_size());
	for (index_type i = 0; i < en_output_size; ++i)
	{
		// calculates outputs 
		m_outputs[i] = vector(i).dot(ret.input());
		
		// calcucates approximate old inputs by outputs
		apx_input += vector(i) * m_outputs[i];

		// save outputs
		ret.set_foutput(i, m_outputs[i]);
	}

	//float_type sum = ret.input().sum();
	/*float_type sum = en_output_size;
	vector_type apx_input(0.0, sp.input_size());
	for (index_type i = 0; i < en_output_size; ++i)
	{
		// calculates outputs 
		m_outputs[i] = vector(i).dot(ret.input()) / (sum + 1);
		
		// calcucates approximate old inputs by outputs
		apx_input += vector(i) * m_outputs[i] * (sum + 1);

		// save outputs
		ret.set_foutput(i, m_outputs[i]);
	}*/

	// restore
	ret.input() = apx_input;
	m_converter.restore_input(ret);
	return ret;
}

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_GHIA_NETWORK_H */
/* //////////////////////////////////////////////////////////////////// */
