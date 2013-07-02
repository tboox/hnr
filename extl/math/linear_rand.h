/* ///////////////////////////////////////////////////////////////////////
 * File:		linear_rand.h		
 *
 * Created:		08.05.24		
 * Updated:		08.09.08	
 *
 * Brief: The linear random number generator
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MATH_LINEAR_RAND_H
#define EXTL_MATH_LINEAR_RAND_H

/*!\file linear_rand.h
 * \brief The linear random number generator
 */

#ifndef __cplusplus
#	error linear_rand.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../type/traits/limit_traits.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_BEGIN_NAMESPACE

/*!\brief The linear random number generator
 *
 * Xn+1 = ( a * Xn) mod ( 2^31 ¨C 1 ) 
 * 
 * \ingroup extl_group_algorithm
 */
struct linear_rand
{
	/// \name Types
	/// @{
	public:
		typedef double			float_type;
		typedef linear_rand		class_type;
		typedef e_size_t		size_type;
		typedef e_int_t			int_type;
	/// @}

	/// \name Members
	/// @{
	private:
		float_type				m_scope;
		size_type				m_seed;
		size_type				m_value;
	/// @}

	public:
		/// Constructor
		explicit_k linear_rand(size_type seed = 1) 
			: m_scope(EXTL_LIMIT_TRAITS_SINT32_MAX)
			, m_seed(seed)
			, m_value(seed)
		{}

		/// Generates a random number with the given range [0, scope())
		size_type generate()
		{
			return next() % scope();
		}

		/// Generates a random number with the given range [lower, upper)
		int_type generate(int_type lower, int_type upper)
		{
			return (lower + next() % (upper - lower));
		}

		/// Generates a random float number with the given range [0, fscope())
		float_type fgenerate()
		{
			return fgenerate(0, fscope());
		}

		/// Generates a random float number with the given range [lower, upper)
		float_type fgenerate(float_type flower, float_type fupper)
		{
			EXTL_ASSERT(fupper > flower);

			float_type f01 = static_cast<float_type>(generate()) / fscope();
			return flower + (fupper - flower) * f01;
		}

		/// Returns the scope of the random number
		size_type scope() const
		{
			return static_cast<int_type>(m_scope);
		}

		/// Returns the float scope of the random number
		float_type fscope() const
		{
			return m_scope;
		}

		/// Resets the value of the random number
		void reset()
		{
			m_value = m_seed;
		}

		/// Sets the seed of the random number
		void set_seed(size_type seed)
		{
			m_seed = seed;
		}

		/// Gets the seed of the random number
		size_type get_seed()
		{
			return m_seed;
		}

	private:
		size_type next()
		{
			return (m_value = (m_value * EXTL_CONST_SINT32_SUFFIX(10807) + 1) & EXTL_CONST_SINT32_SUFFIX(0x7FFFFFFF));
		}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl namespace 
 */
EXTL_END_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MATH_LINEAR_RAND_H */
/* //////////////////////////////////////////////////////////////////// */
