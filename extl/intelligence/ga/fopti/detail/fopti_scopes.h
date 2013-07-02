/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_scopes.h		
 *
 * Created:		08.09.09
 * Updated:		08.10.13
 *
 * Brief: The fopti_scopes class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_DETAIL_SCOPES_H
#define EXTL_INTELLIGENCE_GA_FOPTI_DETAIL_SCOPES_H

#ifndef __cplusplus
#	error fopti_scopes.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE
EXTL_DETAIL_BEGIN_NAMESPACE

// [lower, upper]
template<e_size_t N>
class fopti_scopes
{
	public:
		typedef e_size_t											size_type;
		typedef e_bool_t											bool_type;
		typedef e_float_t											float_type;
		typedef size_type											index_type;
		typedef class fopti_scope
		{
			private:
				float_type											m_lower;
				float_type											m_upper;

			public:
				fopti_scope()
					: m_lower(0), m_upper(0)
				{}

				fopti_scope(float_type const& lower, float_type const& upper)
					: m_lower(lower), m_upper(upper)
				{}

				float_type const	lower() const					{ return m_lower;	}
				void				lower(float_type l)				{ m_lower = l;		}
				
				float_type const	upper() const					{ return m_upper;	}
				void				upper(float_type u)				{ m_upper = u;		}

				void				scope(float_type l, float_type u)	{ lower(l);	upper(u);	}

				float_type const	size() const					{ return (upper() - lower());	}

				bool_type			include(float_type v) const		{ return ((v >= lower()) && (v <= upper()));	}
				
				float_type			ensure_lower(float_type v) const	{ return ((v < lower())? lower() : v);			}
				float_type			ensure_upper(float_type v) const	{ return ((v > upper())? upper() : v);			}
				float_type			ensure_include(float_type v) const	{ return ensure_upper(ensure_lower(v));			}
		}															scope_type;

	private:
		EXTL_STATIC_MEMBER_CONST(size_type, variable_count = N);

	private:
	#if EXTL_WORKAROUND_MSVC(==, 1200)	// warning :zero-sized array in struct/union
		scope_type													m_scopes[variable_count + 1];
	#else
		scope_type													m_scopes[variable_count];
	#endif

	public:
		fopti_scopes()
		{}
		explicit_k fopti_scopes(scope_type const& sp0)
		{
			at(0) = sp0;
		}
		explicit_k fopti_scopes(scope_type const& sp0, scope_type const& sp1)
		{
			at(0) = sp0;
			at(1) = sp1;
		}

	public:
		scope_type const&	at(index_type i) const	{ EXTL_ASSERT(i < variable_count); return m_scopes[i];	}
		scope_type&			at(index_type i)		{ EXTL_ASSERT(i < variable_count); return m_scopes[i];	}

		scope_type const&	operator[](index_type i) const	{ return at(i);	}
		scope_type&			operator[](index_type i)		{ return at(i);	}

		size_type const		size() const					{ return variable_count;	}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::detail namespace 
 */
EXTL_DETAIL_END_NAMESPACE
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_DETAIL_SCOPES_H */
/* //////////////////////////////////////////////////////////////////// */
