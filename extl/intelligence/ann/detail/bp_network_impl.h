/* ///////////////////////////////////////////////////////////////////////
 * File:		bp_network_impl.h		
 *
 * Created:		08.12.17			
 * Updated:		08.12.17
 *
 * Brief:		The bp_network_impl class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_DETAIL_BP_NETWORK_IMPL_H
#define EXTL_INTELLIGENCE_ANN_DETAIL_BP_NETWORK_IMPL_H

/*!\file bp_network_impl.h
 * \brief bp_network_impl class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error bp_network_impl.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "basic_network_base.h"
#include "../basic_network_validator.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::detail namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

/*!brief bp_network_impl
 *
 * \param Dev The derived type
 * \param InN the input demension
 * \param OutN the output demension
 * \param Nt The network traits type
 *
 * <pre>
 * note: node id: 0 1 2 3 4 5
 * [0]: hreshold
 *
 * input  hide0    output
 * [0]--------------\
 *        \         /[4]
 * [1]---->[3]---->|
 *        /         \[5]
 * [2]---
 *
 * </pre>
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Dev
		,	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Nt
		>
class bp_network_impl
	: public basic_network_base<Dev, InN, OutN, Nt>
{
	/// \name Types
	/// @{
	protected:
		typedef basic_network_base<Dev, InN, OutN, Nt>										base_type;
	/// @}

	/// \name Types
	/// @{
	public:
		typedef bp_network_impl																class_type;
		typedef Dev																			derived_type;
		typedef typename_type_k base_type::size_type										size_type;
		typedef typename_type_k base_type::bool_type										bool_type;
		typedef typename_type_k base_type::index_type										index_type;
		typedef typename_type_k base_type::network_traits_type								network_traits_type;
		typedef typename_type_k base_type::rand_type										rand_type;	
		typedef typename_type_k base_type::node_type										node_type;
		typedef typename_type_k base_type::weight_type										weight_type;
		typedef typename_type_k base_type::float_type										float_type;
		typedef typename_type_k base_type::net_type											net_type;	
		typedef typename_type_k base_type::net_in_adjnode_iterator							net_in_adjnode_iterator;
		typedef typename_type_k base_type::net_out_adjnode_iterator							net_out_adjnode_iterator;
		typedef typename_type_k base_type::layers_type										layers_type;
		typedef typename_type_k network_traits_type::afunc_type								afunc_type;	
		typedef typename_type_k network_traits_type::sample_type							sample_type;
		typedef typename_type_k buffer_selector<sample_type>::large_buffer_type				samples_type;
		typedef typename_type_k buffer_selector<float_type>::buffer_type					floats_type;
	/// @}

	/// \name Members
	/// @{
	private:
		/// the learning rate, range: [0, 1]
		float_type																			m_lrate;
		/// the activation function
		afunc_type																			m_afunc;
	/// @}

	private:
		bp_network_impl(class_type const& rhs);
		class_type&	operator =(class_type& rhs);

	/// \name Constructors
	/// @{
	public:
		explicit_k bp_network_impl	(	layers_type const& layers
									,	float_type lrate		
									,	float_type hr			
									,	afunc_type const& afunc
									,	rand_type const& rand
									)
			: base_type(layers, hr, rand)
			, m_lrate(lrate) 
			, m_afunc(afunc)
		{
		}
		explicit_k bp_network_impl(derived_type const& rhs)
			: base_type(rhs)
			, m_lrate(static_cast<class_type const&>(rhs).m_lrate) 
			, m_afunc(static_cast<class_type const&>(rhs).m_afunc)
			
		{
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// gets the activation function
		afunc_type&				afunc()					{ return m_afunc;		}
		/// gets the activation function
		afunc_type const&		afunc()	const			{ return m_afunc;		}
		
		/// gets the learning rate, range: [0, 1]
		float_type				lrate() const			{ return m_lrate;		}
		/// sets the learning rate, range: [0, 1]
		void					lrate(float_type lr)	{ m_lrate = lr;			}
	/// @}

	/// \name Mutators
	/// @{
	public:
		void					swap(derived_type& rhs);
		derived_type&			operator =(derived_type const& rhs);
	/// @}

	/// \name Methods
	/// @{
	public:
		/// train the single sample
		void					train(sample_type& sp);
		/// train the multi-samples
		void					train(samples_type& sps, size_type train_n = 1);
		/// train the multi-samples with weights
		void					train(samples_type& sps, floats_type const& sps_ws, size_type train_n = 1);
		/// run the given sample
		void					run(sample_type& sp);
		/// run the given samples
		//void					run(samples_type& sps);
	/// @}

	/// \name Others
	/// @{
	protected:
		derived_type&			derive()		{ return static_cast<derived_type&>(*this);			}	
		derived_type const&		derive() const	{ return static_cast<derived_type const&>(*this);	}
	/// @}

	/// \name Helpers
	/// @{
	protected:
		/// forward calculation: input sample & calcucate output
		void					forward(sample_type& sp);
		/// backward calculation: modify weight
		void					backward();
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */
// Template declaration 
#ifdef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
#	undef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
#endif

#define EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL	\
template<	typename_param_k Dev								\
		,	e_size_t InN										\
		,	e_size_t OutN										\
		,	typename_param_k Nt									\
		>

// Class qualification 
#ifdef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL
#	undef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL
#endif

#define EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL	bp_network_impl<Dev, InN, OutN, Nt>

// Class qualification 
#ifdef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_RET_QUAL
#	undef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_RET_QUAL
#endif

#define EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::ret_type \
					EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Implementation
 */

EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::swap(derived_type& rhs)
{
	std_swap(m_afunc, static_cast<class_type&>(rhs).m_afunc);
	std_swap(m_lrate, static_cast<class_type&>(rhs).m_lrate);

	static_cast<base_type&>(*this).swap(rhs);
}

EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_RET_QUAL(derived_type&)::operator =(derived_type const& rhs)
{
	derived_type(rhs).swap(derive());
	return derive();
}

EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::forward(sample_type& sp)
{
	EXTL_ASSERT(derive().is_valid());

	// input sample
	index_type i;
	size_type input_n = sp.input_size();
	EXTL_ASSERT(this->layers().inodes_size() == input_n + 1); // + a hreshold
	for (i = 0; i < input_n; ++i)
	{
		// note: this->net().at(0) is hreshold
		this->net().at(i + 1).output(sp.get_finput(i));
	}

	// calculate hide-layer & output-layer output
	size_type ihs_n = this->layers().nodes_size() - this->layers().onodes_size();
	index_type start_n = this->layers().inodes_size();
	size_type nodes_n = this->layers().nodes_size();
	EXTL_ASSERT(start_n <= nodes_n);
	for (i = start_n; i < nodes_n; ++i)
	{
		// weighted_sum = sum(weight_k * val_k)
		float_type weighted_sum = 0;
		net_in_adjnode_iterator pe = this->net().in_adjnode_end(i);
		for (net_in_adjnode_iterator pi = this->net().in_adjnode_begin(i); pi != pe; ++pi)
		{
			weighted_sum += this->net().weight(*pi, i).value() * this->net().at(*pi).output();
		}
		// activate output
		node_type& node = this->net().at(i);
		derive().do_activate_output(node, weighted_sum);

		// calculate the error of real_output & the output-layer node
		if (node.in_olayer())
		{
			// calculate output error
			node.error(sp.get_freal(i - ihs_n) - node.output());
		}
	}

	EXTL_ASSERT(derive().is_valid());
}

EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::backward()
{
	EXTL_ASSERT(derive().is_valid());

	// modify output-layer weight
	index_type start_n = this->layers().nodes_size() - 1;
	index_type end_n = this->layers().inodes_size(); 
	for (index_type i = start_n + 1; i >= end_n + 1; --i) // prevent generate bug for index_type is unsigned type 
	{
		index_type cur = i - 1;
		node_type& node = this->net().at(cur);

		// prepare modify weight
		derive().do_prepare_modify_weight(node);

		// modify weight
		net_in_adjnode_iterator pe = this->net().in_adjnode_end(cur);
		for (net_in_adjnode_iterator pi = this->net().in_adjnode_begin(cur); pi != pe; ++pi)
		{
			derive().do_modify_weight(this->net().weight(*pi, cur), node, this->net().at(*pi));
		}
	}

	//EXTL_TRACEA("\n");

	EXTL_ASSERT(derive().is_valid());
}
EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::train(sample_type& sp)
{
	EXTL_ASSERT(derive().is_valid());

	// forward calculation: input sample & calcucate output
	derive().forward(sp);
	/// backward calculation: modify weight
	derive().backward();

	EXTL_ASSERT(derive().is_valid());
}

EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::train(samples_type& sps, size_type train_n)
{
	EXTL_ASSERT(derive().is_valid());

#if 0
	size_type sps_n = sps.size();
	for (size_type train_i = 0; train_i < train_n; ++train_i)
		for (index_type i = 0; i < sps_n; ++i)
			train(sps[i]);
#else	// for optimization: adaptive learning rate
	typedef basic_network_validator<derived_type>	validator_type;
	validator_type									validator;

	size_type sps_n = sps.size();
	float_type old_mse = -1;
	for (size_type train_i = 0; train_i < train_n; ++train_i)
	{
		for (index_type i = 0; i < sps_n; ++i)
			train(sps[i]);

		// modify learning rate
		validator.validate(derive(), sps);
		if (old_mse < 0) old_mse = validator.mse();
		else if (validator.mse() < old_mse) m_lrate *= 1.06; 
		else if (validator.mse() > (1.06 * old_mse)) m_lrate *= 0.8; 
		old_mse = validator.mse();
	}
#endif
	EXTL_ASSERT(derive().is_valid());
}

EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::train(samples_type& sps, floats_type const& sps_ws, size_type train_n)
{
	EXTL_ASSERT(derive().is_valid());
#if 0
	size_type sps_n = sps.size();
	for (size_type train_i = 0; train_i < train_n; ++train_i)
	{
		for (index_type i = 0; i < sps_n; ++i)
		{
			// select sample
			float_type p = derive().rand().fgenerate(0, 1);
			float_type sum = 0;
			index_type j;
			for (j = 0; (sum <= p) && (j < sps_n); ++j)
				sum += sps_ws[j];
			j = j > 0? j - 1 : 0;
			
			// train sample
			train(sps[j]);
		}
	}
#else	// for optimization: adaptive learning rate

	typedef basic_network_validator<derived_type>	validator_type;
	validator_type									validator;

	size_type sps_n = sps.size();
	float_type old_mse = -1;
	for (size_type train_i = 0; train_i < train_n; ++train_i)
	{
		for (index_type i = 0; i < sps_n; ++i)
		{
			// select sample
			float_type p = derive().rand().fgenerate(0, 1);
			float_type sum = 0;
			index_type j;
			for (j = 0; (sum <= p) && (j < sps_n); ++j)
				sum += sps_ws[j];
			j = j > 0? j - 1 : 0;
			
			// train sample
			train(sps[j]);
		}

		// modify learning rate
		validator.validate(derive(), sps);
		if (old_mse < 0) old_mse = validator.mse();
		else if (validator.mse() < old_mse) m_lrate *= 1.06; 
		else if (validator.mse() > (1.06 * old_mse)) m_lrate *= 0.8; 
		old_mse = validator.mse();
	}
#endif
	EXTL_ASSERT(derive().is_valid());
}

EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::run(sample_type& sp)
{
	EXTL_ASSERT(derive().is_valid());

	// forward calculation: input sample & calcucate output
	derive().forward(sp);

	// get output
	index_type start_n = this->layers().nodes_size() - this->layers().onodes_size();
	index_type end_n = this->layers().nodes_size(); 
	EXTL_ASSERT(start_n <= end_n);
	EXTL_ASSERT(sp.output_size() == this->layers().onodes_size());
	for (index_type i = start_n; i < end_n; ++i)
	{
		// the sample type is the bit array type
		sp.set_foutput(i - start_n, this->net().at(i).output());
	}
	EXTL_ASSERT(derive().is_valid());
}
/*EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL::run(samples_type& sps)
{
	EXTL_ASSERT(derive().is_valid());

	size_type sps_n = sps.size();
	for (index_type i = 0; i < sps_n; ++i)
		run(sps[i]);

	EXTL_ASSERT(derive().is_valid());
}*/

/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_TEMPLATE_DECL
#undef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_QUAL
#undef EXTL_INTELLI_ANN_DETAIL_BP_NETWORK_IMPL_RET_QUAL


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_DETAIL_BP_NETWORK_IMPL_H */
/* //////////////////////////////////////////////////////////////////// */
