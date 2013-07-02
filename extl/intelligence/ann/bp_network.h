/* ///////////////////////////////////////////////////////////////////////
 * File:		bp_network.h		
 *
 * Created:		08.12.14		
 * Updated:		08.12.14
 *
 * Brief:		The bp_network class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_BP_NETWORK_H
#define EXTL_INTELLIGENCE_ANN_BP_NETWORK_H

/*!\file bp_network.h
 * \brief bp_network class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error bp_network.h is not supported by the current compiler.
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

/*!brief bp_network_tratis
 *
 * \param InN the input demension
 * \param OutN the output demension
 * \param Sp the sample type
 * \param aFunc The activation function type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Sp
		,	typename_param_k aFunc 
		,	typename_param_k Rand 
		>
struct bp_network_traits
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

			/// \name Members
			/// @{
			private:
				/// the first order derivative value of the current node
				float_type																	m_first_d;
				/// the gradient of the current node
				float_type																	m_grad;	
				/// the right weighted sum
				/// sum(grad_k * weight_k) in right layer
				/// weight_k is weight of the out-arc of this node
				/// grad_k is gradient of the out-node of this node
				float_type																	m_rws;
			/// @}

			/// \name Constructors
			/// @{
			public:
				node_type()
					: base_type()
					, m_first_d(0)
					, m_grad(0)
					, m_rws(0)
				{}
			/// @}

			/// \name Attibutes
			/// @{
			public:
				/// the first order derivative value of the current node
				float_type			first_d() const			{ return m_first_d;		}
				/// set the first order derivative value of the current node
				void				first_d(float_type fd)	{ m_first_d = fd;		}

				/// the gradient of the current node
				float_type			grad() const			{ return m_grad;		}
				/// set the gradient of the current node
				void				grad(float_type gd)		{ m_grad = gd;			}

				/// the right weighted sum
				float_type			rws() const				{ return m_rws;			}
				/// set the right weighted sum
				void				rws(float_type rws)		{ m_rws = rws;			}
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

			/// \name Members
			/// @{
			private:
				float_type																	m_old_dw;
			/// @}

			/// \name Constructors
			/// @{
			public:
				explicit_k weight_type(float_type val = 0)
					: base_type(val)
					, m_old_dw(0)
				{}
			/// @}

			/// \name Attibutes
			/// @{
			public:
				/// the difference of the old weight for optimization
				float_type			old_dw() const			{ return m_old_dw;		}
				/// set the difference of the old weight for optimization
				void				old_dw(float_type dw)	{ m_old_dw = dw;		}
			/// @}
		};

		/// the directed-net
		typedef typename_type_k net_selector<e_true_v, node_type, weight_type>::sparse_net_type	net_type;

		/// the sample type
		//typedef typename_type_k sample_selector<InN, OutN>::bool_sample_type				sample_type;
		typedef Sp																			sample_type;
	/// @}
};

/*!brief bp_network
 *
 * \param InN the input demension
 * \param OutN the output demension
 * \param Sp the sample type
 * \param aFunc The activation function type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
#ifdef EXTL_TEMPLATE_CLASS_DEFAULT_ARGUMENT_SUPPORT
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Sp		= typename_type_def_k sample_selector<InN, OutN>::bool_sample_type
		,	typename_param_k aFunc	= tanh_sigmoid_afunc_traits // sigmoid_afunc_traits
		,	typename_param_k Rand	= typename_type_def_k rand_selector::rand_type
		>
#else
template<	e_size_t InN
		,	e_size_t OutN
		,	typename_param_k Sp
		,	typename_param_k aFunc 
		,	typename_param_k Rand 
		>
#endif
class bp_network
	: public EXTL_NS_DETAIL(bp_network_impl)<	bp_network<InN, OutN, Sp, aFunc, Rand>
											,	InN, OutN
											,	bp_network_traits<InN, OutN, Sp, aFunc, Rand>
											>
{
	/// \name Private Types
	/// @{
	private:
		typedef EXTL_NS_DETAIL(bp_network_impl)	<	bp_network<InN, OutN, Sp, aFunc, Rand>
												,	InN, OutN
												,	bp_network_traits<InN, OutN, Sp, aFunc, Rand>
												>									base_type;
		typedef typename_type_k base_type::base_type								next_base_type;
	/// @}
	
	/// \name Public Types
	/// @{
	public:
		typedef bp_network															class_type;
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
		typedef typename_type_k base_type::floats_type								floats_type;
		typedef typename_type_k net_type::const_in_adjnode_iterator					net_in_adjnode_iterator;
		typedef typename_type_k net_type::const_out_adjnode_iterator				net_out_adjnode_iterator;
	#ifdef EXTL_TYPE_ALIAS_FRIEND_SUPPORT
		friend																		base_type;
		friend																		next_base_type;
	#endif
	/// @}

	/// \name Members
	/// @{
	private:
		/// range:[0-1], for momentum term factor - for optimization
		float_type																	m_mf;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k bp_network	(	layers_type const& layers = layers_type()
								,	float_type lrate = 0.5
								,	float_type mf = 1		
								,	float_type hr = -1		
								,	afunc_type const& afunc = afunc_type()
								,	rand_type const& rand = rand_type()
								)
			: base_type(layers, lrate, hr, afunc, rand)
			, m_mf(mf)
		{
		}
		bp_network(class_type const& rhs)
			: base_type(rhs)
			, m_mf(rhs.m_mf)
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
			node.first_d(this->afunc().calc_1d(weighted_sum));
			node.rws(0);	// must initialize for summation
			node.grad(0);
		}

		// prepare to modify the weight
		void					do_prepare_modify_weight(node_type& node)
		{
			// calculate gradient
			if (node.in_olayer())	// output-layer
			{
				node.grad(node.error() * node.first_d());
			}
			else	// input-layer & hide-layers
			{
				node.grad(node.first_d() * node.rws());
			}
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
			// modify weight
			float_type dw = this->lrate() * node.grad() * left_node.output();

			// non-optimization
			//weight.value(weight.value() + dw);

			// for optimization
			// add momentum term: weight.old_dw() * m_a
			weight.value(weight.value() + dw + weight.old_dw() * m_mf);
			weight.old_dw(dw);

			/* pre-calcuate for optimization
			 * sum(grad_k * weight_k) in right layer
			 * weight_k is weight of the in-arc of this node
			 * grad_k is gradient of the in-node of this node
			 */
			left_node.rws(left_node.rws() + node.grad() * weight.value());
		}
	/// @}

	/// \name Operators
	/// @{
	public:
		void		swap(class_type& rhs)				{ std_swap(m_mf, rhs.m_mf);	base_type::swap(rhs);	}
		class_type& operator=(class_type const& rhs)	{ return base_type::operator=(rhs);					}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_BP_NETWORK_H */
/* //////////////////////////////////////////////////////////////////// */
