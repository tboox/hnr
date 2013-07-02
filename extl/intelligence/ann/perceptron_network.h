/* ///////////////////////////////////////////////////////////////////////
 * File:		perceptron_network.h		
 *
 * Created:		08.12.14		
 * Updated:		08.12.14
 *
 * Brief:		The perceptron_network class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_H
#define EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_H

/*!\file perceptron_network.h
 * \brief perceptron_network class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error perceptron_network.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/basic_network_base.h"
#include "detail/bp_network_impl.h"
#include "afunc_traits.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief perceptron_network_tratis
 *
 * \param InN the input demension
 * \param OutN the output demension
 * \param aFunc The activation function type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k aFunc 
		,	typename_param_k Rand 
		>
struct perceptron_network_traits
	: public EXTL_NS_DETAIL(basic_network_traits)<e_float_t>
{
	/// \name Private Types
	/// @{
	private:
		typedef EXTL_NS_DETAIL(basic_network_traits)<e_float_t>								base_type;
		typedef typename_type_k base_type::node_base_type									node_base_type;
		typedef typename_type_k base_type::weight_base_type									weight_base_type;
	/// @}

	/// \name Types
	/// @{
	public:
		/// the activation function
		typedef aFunc																		afunc_type;

		/// the random generator type
		typedef Rand																		rand_type;

		/// the float type
		typedef typename_type_k base_type::float_type										float_type;

		/// the node type
		struct																				node_type
			: public node_base_type
		{
			/// \name Types
			/// @{
			public:
				typedef node_base_type														base_type;
			/// @}

			/// \name Constructors
			/// @{
			public:
				node_type()
					: base_type()
				{}
			/// @}

		};

		/// the weight type
		struct																				weight_type
			: public weight_base_type
		{
			/// \name Types
			/// @{
			public:
				typedef weight_base_type													base_type;
			/// @}

			/// \name Constructors
			/// @{
			public:
				explicit_k weight_type(float_type val = 0)
					: base_type(val)
				{}
			/// @}
		};

		/// the directed-net
		typedef typename_type_k net_selector<e_true_v, node_type, weight_type>::net_type	net_type;

		/// the sample type
		typedef typename_type_k sample_selector<InN, OutN>::bool_sample_type				sample_type;
	/// @}
};

/*!brief perceptron_network
 *
 * \param InN the input demension
 * \param OutN the output demension
 * \param aFunc The activation function type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k aFunc = sigmoid_afunc_traits	// tanh_sigmoid_afunc_traits
		,	typename_param_k Rand = typename_type_def_k rand_selector::rand_type
		>
#else
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k aFunc 
		,	typename_param_k Rand 
		>
#endif
class perceptron_network
	: public EXTL_NS_DETAIL(bp_network_impl)<	perceptron_network<InN, OutN, aFunc, Rand>
											,	InN, OutN
											,	perceptron_network_traits<InN, OutN, aFunc, Rand>
											>
{
	/// \name Private Types
	/// @{
	private:
		typedef EXTL_NS_DETAIL(bp_network_impl)	<	perceptron_network<InN, OutN, aFunc, Rand>
												,	InN, OutN
												,	perceptron_network_traits<InN, OutN, aFunc, Rand>
												>									base_type;
		typedef typename_type_k base_type::base_type								next_base_type;
	/// @}
	
	/// \name Public Types
	/// @{
	public:
		typedef perceptron_network													class_type;
		typedef typename_type_k base_type::size_type								size_type;
		typedef typename_type_k base_type::bool_type								bool_type;
		typedef typename_type_k base_type::index_type								index_type;
		typedef typename_type_k base_type::layers_type								layers_type;
		typedef typename_type_k base_type::network_traits_type						network_traits_type;
		typedef typename_type_k base_type::float_type								float_type;
		typedef typename_type_k base_type::sample_type								sample_type;
		typedef typename_type_k base_type::samples_type								samples_type;
		typedef typename_type_k base_type::afunc_type								afunc_type;
		typedef typename_type_k base_type::rand_type								rand_type;	
		typedef typename_type_k base_type::node_type								node_type;
		typedef typename_type_k base_type::weight_type								weight_type;
		typedef typename_type_k base_type::net_type									net_type;	
		typedef typename_type_k net_type::const_in_adjnode_iterator					net_in_adjnode_iterator;
		typedef typename_type_k net_type::const_out_adjnode_iterator				net_out_adjnode_iterator;
	#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
		friend																		base_type;
		friend																		next_base_type;
	#endif
	/// @}

	/// \name Constructors
	/// @{
	public:
		perceptron_network	(	size_type mid_n
							,	float_type lrate = 0.5		
							,	float_type hr = -1		
							,	afunc_type const& afunc = afunc_type()
							,	rand_type const& rand = rand_type()
							)
			: base_type(layers_type(mid_n), lrate, hr, afunc, rand)
		{
		}
		perceptron_network(class_type const& rhs)
			: base_type(rhs)
		{
		}
	/// @}

	/// \name Implementions
	/// @{
#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
	protected:
#else
	public:
#endif
		// initialiate weights
		weight_type				do_init_weight()
		{
			float_type bw = -3 / std_sqrt(this->layers().inodes_size());
			float_type ew = 3 / std_sqrt(this->layers().inodes_size());
			return weight_type(this->rand().fgenerate(bw, ew));
		}
		// activate output
		void					do_activate_output(node_type& node, float_type weighted_sum)
		{
			node.output(this->afunc().calc(weighted_sum));
		}

		// prepare to modify the weight
		void					do_prepare_modify_weight(node_type& /*node*/)
		{
		}
		
		/* modify weight
		 *
		 * left_nodes  nodes right_nodes
		 * [0]--------------\
		 *        \         /[4]
		 * [1]---->[3]---->|
		 *        /         \[5]
		 * [2]---
		 */
		void					do_modify_weight(weight_type& weight, node_type& node, node_type& left_node)
		{
			// note: only modify the weight of the output-layer
			if (node.in_olayer())
			{
				// modify weight
				float_type dw = this->lrate() * node.error() * left_node.output();
				weight.value(weight.value() + dw);
			}
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		class_type& operator=(class_type const& rhs)	{ return base_type::operator=(rhs);		}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_PERCEPTRON_NETWORK_H */
/* //////////////////////////////////////////////////////////////////// */
