/* ///////////////////////////////////////////////////////////////////////
 * File:		penalty_traits_base.h		
 *
 * Created:		08.10.23
 * Updated:		08.10.23
 *
 * Brief: The penalty_traits_base class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_PENALTY_TRAITS_BASE_H
#define EXTL_INTELLIGENCE_GA_PENALTY_TRAITS_BASE_H

/*!\file penalty_traits_base.h
 * \brief The penalty_traits_base class
 */
#ifndef __cplusplus
#	error penalty_traits_base.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief penalty_traits_base class
 * 
 * \param D The derived type
 * \param Idl The individual type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k D
		,	typename_param_k Idl
		>
class penalty_traits_base
{
	/// \name Types
	/// @{
	public:
		typedef D														derived_type;
		typedef penalty_traits_base										class_type;
		typedef Idl														individual_type;
		typedef typename_type_k individual_type::size_type				size_type;
		typedef typename_type_k individual_type::bool_type				bool_type;
		typedef typename_type_k individual_type::index_type				index_type;
		typedef typename_type_k individual_type::int_type				int_type;
		typedef typename_type_k individual_type::float_type				float_type;
	/// @}

	/// \name Methods
	/// @{
	public:
		void penalty(individual_type& idl)
		{
			derive().do_penalty(idl);
		}
	/// @}

	private:
		derived_type const&	derive() const	{ return static_cast<derived_type const&>(*this);	}
		derived_type&		derive() 		{ return static_cast<derived_type&>(*this);			}
};

/*!\brief no_penalty_traits class
 * 
 * \param Idl The individual type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Idl>
class no_penalty_traits
	: public penalty_traits_base<no_penalty_traits<Idl>, Idl >
{
	/// \name Types
	/// @{
	public:
		typedef penalty_traits_base<no_penalty_traits<Idl>, Idl >				base_type;
		typedef no_penalty_traits												class_type;
		typedef Idl																individual_type;
		typedef typename_type_k base_type::size_type							size_type;
		typedef typename_type_k base_type::bool_type							bool_type;
		typedef typename_type_k base_type::index_type							index_type;
		typedef typename_type_k base_type::int_type								int_type;
		typedef typename_type_k base_type::float_type							float_type;
	/// @}
	
	public:
		void do_penalty(individual_type const& /*idl*/)
		{
		}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_PENALTY_TRAITS_BASE_H */
/* //////////////////////////////////////////////////////////////////// */
