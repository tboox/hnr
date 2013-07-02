/* ///////////////////////////////////////////////////////////////////////
 * File:		basic_network_base.h		
 *
 * Created:		08.12.17			
 * Updated:		08.12.17
 *
 * Brief:		The basic_network_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_DETAIL_BASIC_NETWORK_BASE_H
#define EXTL_INTELLIGENCE_ANN_DETAIL_BASIC_NETWORK_BASE_H

/*!\file basic_network_base.h
 * \brief basic_network_base class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Compatibility
 */
#if !defined(EXTL_INTELLIGENCE_ANN_NETWORK_SUPPORT)
#	error basic_network_base.h is not supported by the current compiler.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "../sample.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::detail namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

/*!brief basic_network_traits
 *
 * \param F The float type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k F>
struct basic_network_traits
{
	/// \name Types
	/// @{
	public:
		typedef F			float_type;
		typedef e_bool_t	bool_type;
	/// @}

	/// node_base_type
	struct node_base_type
	{
		/// \name Types
		/// @{
		public:
			typedef F			float_type;
			typedef e_bool_t	bool_type;
		/// @}

		/// \name Members
		/// @{
		private:
			float_type			m_output;
			float_type			m_error;
			bool_type			m_in_olayer;
		/// @}

		/// \name Constructors
		/// @{
		public:
			node_base_type()
				: m_output(0)
				, m_error(0)
				, m_in_olayer(e_false_v)
			{}
		/// @}

		/// \name Attibutes
		/// @{
		public:
			/// the output-value of the current node
			float_type			output() const			{ return m_output;		}
			/// set the output-value of the current node
			void				output(float_type out)	{ m_output = out;		}

			/// the error of the output-layer node
			float_type			error() const			{ return m_error;		}
			/// set error of the output-layer node
			void				error(float_type err)	{ m_error = err;		}

			/// returns \true if the node is in output-layer
			bool_type			in_olayer() const		{ return m_in_olayer;	}
			/// set the node in output-layer
			void				in_olayer(bool_type b)	{ m_in_olayer = b;		}
		/// @}
	};

	/// weight_base_type
	struct weight_base_type
	{
		/// \name Types
		/// @{
		public:
			typedef F			float_type;
			typedef e_bool_t	bool_type;
		/// @}

		/// \name Members
		/// @{
		private:
			float_type			m_value;
		/// @}

		/// \name Constructors
		/// @{
		public:
			explicit_k weight_base_type(float_type val = 0)
				: m_value(val)
			{}
		/// @}

		/// \name Attibutes
		/// @{
		public:
			/// the value of the current weight
			float_type			value() const			{ return m_value;		}
			/// set the value of the current weight
			void				value(float_type val)	{ m_value = val;		}
		/// @}
	};
};
/*!brief basic_network_base
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
class basic_network_base
{
	/// \name Types
	/// @{
	public:
		typedef basic_network_base															class_type;
		typedef Dev																			derived_type;
		typedef e_size_t																	size_type;
		typedef e_bool_t																	bool_type;
		typedef size_type																	index_type;
		typedef Nt																			network_traits_type;
		typedef typename_type_k network_traits_type::rand_type								rand_type;	
		typedef typename_type_k network_traits_type::node_type								node_type;
		typedef typename_type_k network_traits_type::weight_type							weight_type;
		typedef typename_type_k network_traits_type::float_type								float_type;
		typedef typename_type_k network_traits_type::net_type								net_type;	
		typedef typename_type_k net_type::const_in_adjnode_iterator							net_in_adjnode_iterator;
		typedef typename_type_k net_type::const_out_adjnode_iterator						net_out_adjnode_iterator;
		typedef typename_type_k buffer_selector<weight_type>::buffer_type					weights_type;
		
		/// layers_type
		struct																				layers_type	
		{
			/// \name Members
			/// @{
			private:
				typedef typename_type_k buffer_selector<size_type>::buffer_type				buffer_type;
			/// @}

			/// \name Members
			/// @{
			private:
				buffer_type																	m_layers;
				size_type																	m_hnodes_n;
			/// @}

			/// \name Constructors
			/// @{
			public:
				explicit_k layers_type	(	size_type h0_n = 0
										,	size_type h1_n = 0
										,	size_type h2_n = 0
										,	size_type h3_n = 0
										,	size_type h4_n = 0
										,	size_type h5_n = 0
										,	size_type h6_n = 0
										,	size_type h7_n = 0
										,	size_type h8_n = 0
										,	size_type h9_n = 0
										)
					: m_layers()	
					, m_hnodes_n(0)
				{
					EXTL_STATIC_ASSERT(InN > 0);
					EXTL_STATIC_ASSERT(OutN > 0);

					// in-layer + out-layer  + hide-layers
					m_layers.push_back(size_type(InN + 1)); // + a hreshold
					if (h0_n) m_layers.push_back(h0_n);
					if (h1_n) m_layers.push_back(h1_n);
					if (h2_n) m_layers.push_back(h2_n);
					if (h3_n) m_layers.push_back(h3_n);
					if (h4_n) m_layers.push_back(h4_n);
					if (h5_n) m_layers.push_back(h5_n);
					if (h6_n) m_layers.push_back(h6_n);
					if (h7_n) m_layers.push_back(h7_n);
					if (h8_n) m_layers.push_back(h8_n);
					if (h9_n) m_layers.push_back(h9_n);
					m_layers.push_back(size_type(OutN));

					EXTL_ASSERT(layers_size() >= 2);

					// calculate hnodes_n
					size_type n = m_layers.size();
					for (index_type i = 1; i < n - 1; ++i)
						m_hnodes_n += m_layers[i];
				}
			/// @}

			/// \name Attributes
			/// @{
			public:
				/// Returns the number of all layers
				size_type				layers_size() const				{ return m_layers.size();		}
				/// Returns the number of hide-layers
				size_type				hlayers_size() const			{ return m_layers.size() - 2;	}

				/// Returns the number of the nodes in input-layer
				size_type				inodes_size() const				{ return m_layers.front();		}
				/// Returns the number of the all nodes in hide-layers	
				size_type				hnodes_size() const				{ return m_hnodes_n;		}
				/// Returns the number of the nodes in output-layer
				size_type				onodes_size() const				{ return m_layers.back();		}
				/// Returns the number of the all nodes
				size_type				nodes_size() const				{ return inodes_size() + hnodes_size() + onodes_size();		}
				/// Returns the number of the nodes in the given layer
				size_type				nodes_size(index_type i) const	{ EXTL_ASSERT(i < layers_size()); return m_layers.at(i);	}
				/// Returns the number of the nodes in the given hide-layer
				size_type				hnodes_size(index_type i) const	{ EXTL_ASSERT((i + 1) < (layers_size() - 1)); return m_layers.at(i + 1);	}
				/// Returns the maximum number of the nodes in the network
				size_type				max_nodes_size() const			{ return nodes_size();		}
			/// @}

			/// \name Mutators
			/// @{
			public:
				void					swap(layers_type& rhs)
				{
					std_swap(m_hnodes_n, rhs.m_hnodes_n);
					m_layers.swap(rhs.m_layers);
				}
				layers_type&			operator =(layers_type const& rhs)
				{
					layers_type(rhs).swap(*this);
					return (*this);
				}
			/// @}

		};
	/// @}

	/// \name Members
	/// @{
	private:
		/// the layers
		layers_type																			m_layers;
		/// the directed-net
		net_type																			m_net;
		/// the hreshold, range: -1 or 1
		float_type																			m_hreshold;
		/// the random generator
		rand_type																			m_rand;
	/// @}

	/// \name Members
	/// @{
	public:
		enum {	en_input_size = InN		};
		enum {	en_output_size = OutN	};
	/// @}

	private:
		basic_network_base(class_type const& rhs);
		class_type&	operator =(class_type& rhs);

	/// \name Constructors
	/// @{
	public:
		explicit_k basic_network_base	(	layers_type const& layers
										,	float_type hr			
										,	rand_type const& rand
										)
			: m_layers(layers)
			, m_net(layers.nodes_size())
			, m_hreshold(hr)
			, m_rand(rand)
		{
			// initialization
			derive().init();
			EXTL_ASSERT(is_valid());
		}
		explicit_k basic_network_base(derived_type const& rhs)
			: m_layers(static_cast<class_type const&>(rhs).m_layers)
			, m_net(static_cast<class_type const&>(rhs).m_net)
			, m_hreshold(static_cast<class_type const&>(rhs).m_hreshold)
			, m_rand(static_cast<class_type const&>(rhs).m_rand)
			
		{
			EXTL_ASSERT(is_valid());
		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// returns the number of the nodes in input-layer
		static size_type		inodes_size()		{ return en_input_size;	}
		/// returns the number of the nodes in output-layer
		static size_type		onodes_size()		{ return en_output_size;}

		/// returns the random generator
		rand_type&				rand()				{ return m_rand;		}
		/// returns the const layers
		rand_type const&		rand() const		{ return m_rand;		}

		/// returns the layers
		layers_type&			layers()			{ return m_layers;		}
		/// returns the const layers
		layers_type const&		layers() const		{ return m_layers;		}
		
		/// returns the number of the arcs	
		size_type				arcs_size() const	{ return net().arcs_size();	}

		/// returns the hreshold, range: -1 or 1
		float_type				hreshold() const	{ return m_hreshold;	}
		/// invariance
		bool_type				is_valid() const;

		/// returns the weight of the given position
		weight_type&			weight(index_type bid, index_type eid)			{ return net().weight(bid, eid);	}
		/// returns the weight of the given position
		weight_type const&		weight(index_type bid, index_type eid) const	{ return net().weight(bid, eid);	}
	
		/// gets the given input-node
		node_type&				inode(index_type id)		{ extl_assert(id < layers().inodes_size() - 1); return net().at(id + 1);	}	// + a hreshold
		/// gets the given input-node
		node_type const&		inode(index_type id) const	{ extl_assert(id < layers().inodes_size() - 1); return net().at(id + 1);	}
		
		/// gets the given output-node
		node_type&				onode(index_type id)		{ EXTL_ASSERT(id < layers().onodes_size()); return net().at(id + layers().inodes_size() + layers().hnodes_size());	}
		/// gets the given input-node
		node_type const&		onode(index_type id) const	{ EXTL_ASSERT(id < layers().onodes_size()); return net().at(id + layers().inodes_size() + layers().hnodes_size());	}

		/// gets the given node
		node_type&				node(index_type id)			{ return net().at(id);	}
		/// gets the given node
		node_type const&		node(index_type id) const	{ return net().at(id);	}

		/// gets float output
		float_type				foutput(index_type id) const;
		/// gets bool output
		bool_type				boutput(index_type id) const;

		/// sets weights
		void					weights(weights_type const& wgts);
		/// gets weights
		weights_type			weights() const;
	/// @}

	/// \name Mutators
	/// @{
	public:
		void					swap(derived_type& rhs);
		derived_type&			operator =(derived_type const& rhs);
	/// @}

	/// \name Others
	/// @{
	protected:
		net_type&				net()			{ return m_net;			}
		net_type const&			net() const		{ return m_net;			}

		derived_type&			derive()		{ return static_cast<derived_type&>(*this);			}	
		derived_type const&		derive() const	{ return static_cast<derived_type const&>(*this);	}
	/// @}

	/// \name Helpers
	/// @{
	public:
		/// initialize
		void					init();
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * Macro
 */
// Template declaration 
#ifdef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
#	undef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
#endif

#define EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL	\
template<	typename_param_k Dev									\
		,	e_size_t InN											\
		,	e_size_t OutN											\
		,	typename_param_k Nt										\
		>

// Class qualification 
#ifdef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL
#	undef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL
#endif

#define EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL	basic_network_base<Dev, InN, OutN, Nt>

// Class qualification 
#ifdef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL
#	undef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL
#endif

#define EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL(ret_type)	\
					typename_type_ret_k EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL::ret_type \
					EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL

/* ///////////////////////////////////////////////////////////////////////
 * Implementation
 */
EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL(bool_type)::is_valid() const
{
	if (layers().inodes_size() + layers().hnodes_size() + layers().onodes_size() != layers().nodes_size()) return e_false_v;
	if (net().nodes_size() != layers().nodes_size()) return e_false_v;

	size_type nodes_n = 0;
	for (index_type i = 0; i < layers().layers_size(); ++i)
		nodes_n += layers().nodes_size(i);
	if (layers().nodes_size() != nodes_n) return e_false_v;

	return e_true_v;
}

EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL::swap(derived_type& rhs)
{
	layers().swap(static_cast<class_type&>(rhs).m_layers);
	net().swap(static_cast<class_type&>(rhs).m_net);

	std_swap(m_hreshold, static_cast<class_type&>(rhs).m_hreshold);
	std_swap(m_rand, static_cast<class_type&>(rhs).m_rand);
}

EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL(derived_type&)::operator =(derived_type const& rhs)
{
	derived_type(rhs).swap(derive());
	return derive();
}

EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL::init()
{
	size_type layers_n = layers().layers_size();
	EXTL_ASSERT(layers_n >= 2);

	size_type ihs_n = layers().nodes_size() - layers().onodes_size();
	size_type start_n = 0;
	for (index_type i = 1; i < layers_n; ++i)
	{
		size_type n = layers().nodes_size(i);
		size_type pre_n = layers().nodes_size(i - 1);
		for (index_type j = 0; j < n; ++j)
		{
			// insert arc: hreshold -> cur
			net().insert_arc(0, start_n + pre_n + j, derive().do_init_weight());
			// insert other arcs
			for (index_type k = 0; k < pre_n; ++k)
			{
				net().insert_arc(start_n + k, start_n + pre_n + j, derive().do_init_weight());
			}

			// label output-layer node
			if (start_n + pre_n + j >= ihs_n)
				net().at(start_n + pre_n + j).in_olayer(e_true_v);
		}
		start_n += pre_n;
	}
	// set hreshold
	net().at(0).output(hreshold());
	EXTL_ASSERT(is_valid());
}

/// sets weights
/// note: the order of setting and getting must be same
EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline void EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL::weights(weights_type const& wgts)
{
	size_type layers_n = layers().layers_size();
	EXTL_ASSERT(layers_n >= 2);

	index_type wsi = 0;
	size_type start_n = 0;
	for (index_type i = 1; i < layers_n; ++i)
	{
		size_type n = layers().nodes_size(i);
		size_type pre_n = layers().nodes_size(i - 1);
		for (index_type j = 0; j < n; ++j)
		{
			// update arc: hreshold -> cur
			EXTL_ASSERT(wsi < wgts.size());
			net().weight(0, start_n + pre_n + j) = wgts[0 == start_n? wsi : wsi++];
			// update other arcs
			for (index_type k = 0; k < pre_n; ++k)
			{
				EXTL_ASSERT(wsi < wgts.size());
				net().weight(start_n + k, start_n + pre_n + j) = wgts[wsi++];
			}
		}
		start_n += pre_n;
	}
	EXTL_ASSERT(wsi == wgts.size());

	// set hreshold
	net().at(0).output(hreshold());
	EXTL_ASSERT(is_valid());
}

/// gets weights
/// note: the order of setting and getting must be same
EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL(weights_type)::weights() const
{
	weights_type wgts;

	size_type layers_n = layers().layers_size();
	EXTL_ASSERT(layers_n >= 2);

	size_type start_n = 0;
	for (index_type i = 1; i < layers_n; ++i)
	{
		size_type n = layers().nodes_size(i);
		size_type pre_n = layers().nodes_size(i - 1);
		for (index_type j = 0; j < n; ++j)
		{
			// save weight: hreshold -> cur
			if (0 != start_n)
				wgts.push_back(net().weight(0, start_n + pre_n + j));
			// save other weight
			for (index_type k = 0; k < pre_n; ++k)
			{
				wgts.push_back(net().weight(start_n + k, start_n + pre_n + j));
			}
		}
		start_n += pre_n;
	}

	EXTL_ASSERT(wgts.size() == this->arcs_size());

	return wgts;
}
EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL(float_type)::foutput(index_type id) const
{
	EXTL_ASSERT(id < layers().onodes_size());
	return onode(id).output();	
}
EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
inline EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL(bool_type)::boutput(index_type id) const
{
	EXTL_ASSERT(id < layers().onodes_size());
	return (xtl_round45(onode(id).output()) == 1);	
}
/* //////////////////////////////////////////////////////////////////// */
#undef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_TEMPLATE_DECL
#undef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_QUAL
#undef EXTL_INTELLI_ANN_DETAIL_BASIC_NETWORK_BASE_RET_QUAL


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_DETAIL_BASIC_NETWORK_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
