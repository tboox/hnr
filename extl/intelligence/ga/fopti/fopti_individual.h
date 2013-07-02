/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_individual.h		
 *
 * Created:		08.09.09
 * Updated:		08.10.13
 *
 * Brief: The fopti_individual class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_INDIVIDUAL_H
#define EXTL_INTELLIGENCE_GA_FOPTI_INDIVIDUAL_H

/*!\file fopti_individual.h
 * \brief The fopti_individual class
 */
#ifndef __cplusplus
#	error fopti_individual.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "detail/fopti_scopes.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_individual class
 * 
 * \param N The number of the variables 
 *
 * \ingroup extl_group_intelligence
 */
template<e_size_t N>
class fopti_individual
	: public individual_base<fopti_individual<N> >
{
	/// \name Types
	/// @{
	public:
		typedef individual_base<fopti_individual<N> >			base_type;
		typedef fopti_individual								class_type;
		typedef typename_type_k base_type::size_type			size_type;
		typedef typename_type_k base_type::bool_type			bool_type;
		typedef typename_type_k base_type::float_type			float_type;
		typedef typename_type_k base_type::index_type			index_type;
		typedef typename_type_k base_type::int_type				int_type;
		typedef EXTL_NS_DETAIL(fopti_scopes)<N>					scopes_type;
		typedef typename_type_k scopes_type::scope_type			scope_type;
	/// @}
		
	public:
		EXTL_STATIC_MEMBER_CONST(size_type, variable_count = N);

	/// \name Members
	/// @{
	private:
	#if EXTL_WORKAROUND_MSVC(==, 1200)
		float_type												m_variables[variable_count + 1];
	#else
		float_type												m_variables[variable_count];
	#endif
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		fopti_individual()
			: base_type()
		{}
	/// @}

	/// \name Attributes
	/// @{
	public:
		float_type const	value(index_type i) const					{ EXTL_ASSERT(i < size()); return m_variables[i];		}
		void				value(index_type i, float_type v)			{ EXTL_ASSERT(i < size()); m_variables[i] = v;			}

		size_type			size() const								{ return variable_count;			}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_INDIVIDUAL_H */
/* //////////////////////////////////////////////////////////////////// */
