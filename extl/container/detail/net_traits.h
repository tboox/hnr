/* ///////////////////////////////////////////////////////////////////////
 * File:		net_traits.h		
 *
 * Created:		08.11.26			
 * Updated:		08.11.29
 *
 * Brief:		The net_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONTAINER_DETAIL_NET_TRAITS_H
#define EXTL_CONTAINER_DETAIL_NET_TRAITS_H

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"
#include "../basic_pair.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_BEGIN_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

/// net_traits_impl
template<e_bool_t is_dir>
struct net_traits_impl
{
	/// node_type_impl
	template<	typename_param_k Dev
			,	typename_param_k Val
			,	typename_param_k Wgt
			>
	struct node_type_impl;

	/// arc_type_impl
	template<	typename_param_k Dev
			,	typename_param_k Val
			,	typename_param_k Wgt
			>
	struct arc_type_impl;
};

/// net_traits_impl<e_true_v>
EXTL_TEMPLATE_SPECIALISATION
struct net_traits_impl<e_true_v>	// directed 
{
	/// node_type_impl
	template<	typename_param_k Dev
			,	typename_param_k Val
			,	typename_param_k Wgt
			>
	struct node_type_impl
	{
		/// \name Types
		/// @{
		public:
			typedef Dev									derived_type;
			typedef Val									value_type;
			typedef value_type*							pointer;
			typedef value_type const*					const_pointer;
			typedef value_type&							reference;
			typedef value_type const&					const_reference;
			typedef e_size_t							size_type;
			typedef size_type							index_type;
			typedef e_bool_t							bool_type;
		/// @}

		/// \name Members
		/// @{
		private:
			size_type									m_in_degree;
			size_type									m_out_degree;
		/// @}

		/// \name Constructors
		/// @{
		public:
			node_type_impl()
				: m_in_degree(0)
				, m_out_degree(0)
			{}
		/// @}

		/// \name Attributes
		/// @{
		public:
			size_type		in_degree() const			{ return m_in_degree;	}
			void			in_degree(size_type d)		{ m_in_degree = d;		}

			size_type		out_degree() const			{ return m_out_degree;	}
			void			out_degree(size_type d)		{ m_out_degree = d;		}

			size_type		degree() const				{ return in_degree() + out_degree();	}
		/// @}

		/// \name Mutators
		/// @{
		public:
			void			clear()						
			{ 
				in_degree(0);
				out_degree(0);
			}
		/// @}

		/// \name Helpers
		/// @{
		private:																							
			derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
			derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		/// @}
	};

	/// arc_type_impl
	template<	typename_param_k Dev
			,	typename_param_k Val
			,	typename_param_k Wgt
			>
	struct arc_type_impl
	{
		/// \name Types
		/// @{
		public:
			typedef Dev									derived_type;
			typedef Wgt									weight_type;
			typedef e_size_t							size_type;
			typedef size_type							index_type;
			typedef e_bool_t							bool_type;
		/// @}

		/// \name Helpers
		/// @{
		private:																							
			derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
			derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		/// @}
	};
};
/// net_traits_impl<e_true_v>
EXTL_TEMPLATE_SPECIALISATION
struct net_traits_impl<e_false_v>	// indirected 
{
	/// node_type_impl
	template<	typename_param_k Dev
			,	typename_param_k Val
			,	typename_param_k Wgt
			>
	struct node_type_impl
	{
		/// \name Types
		/// @{
		public:
			typedef Dev									derived_type;
			typedef Val									value_type;
			typedef value_type*							pointer;
			typedef value_type const*					const_pointer;
			typedef value_type&							reference;
			typedef value_type const&					const_reference;
			typedef e_size_t							size_type;
			typedef size_type							index_type;
			typedef e_bool_t							bool_type;
		/// @}

		/// \name Members
		/// @{
		private:
			size_type									m_degree;
		/// @}

		/// \name Constructors
		/// @{
		public:
			node_type_impl()
				: m_degree(0)
			{}
		/// @}

		/// \name Attributes
		/// @{
		public:
			size_type		degree() const				{ return m_degree;	}
			void			degree(size_type d)			{ m_degree = d;		}
		/// @}

		/// \name Mutators
		/// @{
		public:
			void			clear()						
			{ 
				degree(0);
			}
		/// @}

		/// \name Helpers
		/// @{
		private:																							
			derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
			derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		/// @}
	};

	/// arc_type_impl
	template<	typename_param_k Dev
			,	typename_param_k Val
			,	typename_param_k Wgt
			>
	struct arc_type_impl
	{
		/// \name Types
		/// @{
		public:
			typedef Dev									derived_type;
			typedef Wgt									weight_type;
			typedef e_size_t							size_type;
			typedef size_type							index_type;
			typedef e_bool_t							bool_type;
		/// @}

		/// \name Helpers
		/// @{
		private:																							
			derived_type&		derive()		{ return static_cast<derived_type&>(*this);			}	
			derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		/// @}
	};
};

/*!brief net_traits
 *
 * \param is_dir returns \true if it's a directed net
 * \param Val the value type
 * \param Wgt the weight type
 *
 * \ingroup extl_group_container
 */
template<	e_bool_t is_dir
		,	typename_param_k Val
		,	typename_param_k Wgt
		>
struct net_traits
{
	struct arc_type;
	/// node_type
	struct node_type
		: public net_traits_impl<is_dir>::template_qual_k node_type_impl<node_type, Val, Wgt>
	{
		/// \name Types
		/// @{
		public:
			typedef typename_type_k net_traits_impl<is_dir>::
					template_qual_k node_type_impl<node_type, Val, Wgt>			base_type;
			typedef Val															value_type;
			typedef value_type*													pointer;
			typedef value_type const*											const_pointer;
			typedef value_type&													reference;
			typedef value_type const&											const_reference;
			typedef e_size_t													size_type;
			typedef size_type													index_type;
			typedef e_bool_t													bool_type;
			friend struct														arc_type;
		/// @}

		/// \name Members
		/// @{
		private:
			index_type									m_id;
			value_type									m_value;
		/// @}

		private:
			enum { en_id_empty = -1	};

		/// \name Constructors
		/// @{
		public:
			explicit_k node_type(	index_type id = index_type(en_id_empty)
								,	const_reference value = value_type())
				: base_type()
				, m_id(id)
				, m_value(value)
			{}
		/// @}

		/// \name Attributes
		/// @{
		public:
			const_reference		value() const				{ return m_value;	}
			reference			value()						{ return m_value;	}
			void				value(const_reference val)	{ m_value = val;	}

			index_type const&	id() const					{ return m_id;		}
			void				id(index_type i)			{ m_id = i;			}
			bool_type			is_empty() const			{ return id() == index_type(en_id_empty);	}
		/// @}

		/// \name Mutators
		/// @{
		public:
			void			clear()						
			{
				id(index_type(en_id_empty));	
				value(value_type());
				base_type::clear();
			}
		/// @}
	};

	/// arc_type
	struct arc_type
		: public net_traits_impl<is_dir>::template_qual_k arc_type_impl<arc_type, Val, Wgt>
	{
		/// \name Types
		/// @{
		public:
			typedef Wgt									weight_type;
			typedef e_size_t							size_type;
			typedef size_type							index_type;
			typedef e_bool_t							bool_type;
			typedef basic_pair<index_type, index_type>	index_pair_type;
		/// @}

		/// \name Members
		/// @{
		public:
			index_pair_type								m_ids;
			weight_type									m_weight;
		/// @}

		/// \name Constructors
		/// @{
		public:
			arc_type()
				: m_ids(index_pair_type())
				, m_weight(weight_type())
			{}
			arc_type(	index_type bid
					,	index_type eid
					,	weight_type const& w = weight_type())
				: m_ids(bid, eid)
				, m_weight(w)
			{
			}
		/// @}

		/// \name Attributes
		/// @{
		public:
			weight_type const&		weight() const					{ return m_weight;	}
			weight_type&			weight()						{ return m_weight;	}
			void					weight(weight_type const& w)	{ m_weight = w;		}

			index_pair_type const&	ids() const						{ return m_ids;		}
			index_pair_type&		ids()							{ return m_ids;		}
			void					ids(index_pair_type const& ids)	{ m_ids = ids;		}

			index_type const&		begin_id() const				{ return ids().first();		}
			void					begin_id(index_type const& id)	{ ids().first(id);			}

			index_type const&		end_id() const					{ return ids().second();	}
			void					end_id(index_type const& id)	{ ids().second(id);			}

			bool_type				is_empty() const				
			{
				EXTL_ASSERT(is_valid());
				return index_type(node_type::en_id_empty) == begin_id() 
					&& index_type(node_type::en_id_empty) == end_id();	
			}
			bool_type				is_valid() const
			{
				if ((index_type(node_type::en_id_empty) == begin_id()) 
					!= (index_type(node_type::en_id_empty) == end_id()))
					return e_false_v;
				return e_true_v;
			}
		/// @}

		/// \name Mutators
		/// @{
		public:
			void					clear()							
			{ 
				weight(weight_type());
				begin_id(index_type(node_type::en_id_empty));
				end_id(index_type(node_type::en_id_empty));
				EXTL_ASSERT(is_valid());
			}
		/// @}
	};
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_CONTAINER_DETAIL_NET_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
