/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_constraints.h		
 *
 * Created:		08.10.23
 * Updated:		08.10.23
 *
 * Brief: The fopti_constraints class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_CONSTRAINTS_H
#define EXTL_INTELLIGENCE_GA_FOPTI_CONSTRAINTS_H

/*!\file fopti_constraints.h
 * \brief The fopti_constraints class
 */
#ifndef __cplusplus
#	error fopti_constraints.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief fopti_constraints class
 * 
 * \param Ft The func_traits type
 *
 * \note x < 10		=> (x - 10)			< 0
 * \note x > 10		=> -1 * (x - 10)	< 0
 * \note x <= 10	=> (x - 10)			<= 0
 * \note x >= 10	=> -1 * (x - 10)	<= 0
 * \note x == 10	=> |x - 10|			== 0
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Ft>
class fopti_constraints
{
	/// \name Types
	/// @{
	public:
		typedef fopti_constraints													class_type;
		typedef Ft																	func_traits_type;
		typedef typename_type_k func_traits_type::func_type							func_type;
		typedef typename_type_k func_traits_type::size_type							size_type;
		typedef typename_type_k func_traits_type::bool_type							bool_type;
		typedef typename_type_k func_traits_type::float_type						float_type;
		typedef typename_type_k func_traits_type::index_type						index_type;
		typedef typename_type_k func_traits_type::int_type							int_type;
		typedef typename_type_k buffer_selector<func_traits_type>::buffer_type		buffer_type;
	/// @}

	/// \name Members
	/// @{
	private:
		buffer_type																	m_fts;
	/// @}

	/// \name Constructors
	/// @{
	public:
		fopti_constraints()
		{
		}
		explicit_k fopti_constraints(func_type const& func1)
		{
			append(func_traits_type(func1));
		}
		fopti_constraints	(	func_type const& func1
							,	func_type const& func2
							)
		{
			append(func_traits_type(func1));
			append(func_traits_type(func2));
		}
		fopti_constraints	(	func_type const& func1
							,	func_type const& func2
							,	func_type const& func3
							)
		{
			append(func_traits_type(func1));
			append(func_traits_type(func2));
			append(func_traits_type(func3));
		}
		fopti_constraints	(	func_type const& func1
							,	func_type const& func2
							,	func_type const& func3
							,	func_type const& func4
							)
		{
			append(func_traits_type(func1));
			append(func_traits_type(func2));
			append(func_traits_type(func3));
			append(func_traits_type(func4));
		}
		fopti_constraints	(	func_type const& func1
							,	func_type const& func2
							,	func_type const& func3
							,	func_type const& func4
							,	func_type const& func5
							)
		{
			append(func_traits_type(func1));
			append(func_traits_type(func2));
			append(func_traits_type(func3));
			append(func_traits_type(func4));
			append(func_traits_type(func5));
		}
		fopti_constraints	(	func_type const& func1
							,	func_type const& func2
							,	func_type const& func3
							,	func_type const& func4
							,	func_type const& func5
							,	func_type const& func6
							)
		{
			append(func_traits_type(func1));
			append(func_traits_type(func2));
			append(func_traits_type(func3));
			append(func_traits_type(func4));
			append(func_traits_type(func5));
			append(func_traits_type(func6));
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		size_type			size() const							{ return m_fts.size();				}

		class_type&			append(func_traits_type const& ft)		{ m_fts.append(ft); return *this;	}
		class_type&			append(func_type const& func)			{ m_fts.append(func); return *this;	}
		class_type&			operator +=(func_traits_type const& ft)	{ return append(ft);				}
		class_type&			operator +=(func_type const& func)		{ return append(func);				}

		func_traits_type&	at(index_type i)						{ return m_fts.at(i);				}
		func_traits_type&	operator [](index_type i)				{ return at(i);						}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_CONSTRAINTS_H */
/* //////////////////////////////////////////////////////////////////// */
