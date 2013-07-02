/* ///////////////////////////////////////////////////////////////////////
 * File:		fopti_crossover_traits.h		
 *
 * Created:		08.09.13
 * Updated:		08.09.13
 *
 * Brief: The fopti_crossover_traits class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_FOPTI_CROSSOVER_TRAITS_H
#define EXTL_INTELLIGENCE_GA_FOPTI_CROSSOVER_TRAITS_H

/*!\file fopti_crossover_traits.h
 * \brief The fopti_crossover_traits class
 */
#ifndef __cplusplus
#	error fopti_crossover_traits.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief discrete_recombination_crossover_traits
 * 
 * \param Pop The Population type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		>
class discrete_recombination_crossover_traits
	: public crossover_traits_base<discrete_recombination_crossover_traits<Pop, Rand>, Pop, Rand>
{
	/// \name Types
	/// @{
	public:
		typedef crossover_traits_base<discrete_recombination_crossover_traits<Pop, Rand>, Pop, Rand>	base_type;
		typedef Pop																						population_type;
		typedef typename_type_k population_type::individual_type										individual_type;
		typedef typename_type_k individual_type::size_type												size_type;
		typedef typename_type_k individual_type::bool_type												bool_type;
		typedef typename_type_k individual_type::float_type												float_type;
		typedef typename_type_k individual_type::index_type												index_type;
		typedef typename_type_k individual_type::int_type												int_type;
		typedef Rand																					random_type;
	/// @}

	/// \name Constructors
	/// @{
	public:
		discrete_recombination_crossover_traits()
			: base_type()
		{
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(random_type& rand)
		{
			base_type::init(rand);
		}
		/// cross i1 & i2
		void do_cross	(	individual_type& i1
						,	individual_type& i2
						)
		{
			size_type n = i1.size();
			EXTL_ASSERT(i2.size() == n);

			for (size_type i = 0; i < n; ++i)
			{
				float_type old_i1 = i1.value(i);
				float_type old_i2 = i2.value(i);

				size_type i1_p = this->rand().generate(0, 2); // 0 & 1
				size_type i2_p = this->rand().generate(0, 2); // 0 & 1

				i1.value(i, i1_p? old_i1 : old_i2);
				i2.value(i, i2_p? old_i1 : old_i2);
			}
			
		}
	/// @}
};

/*!\brief middle_recombination_crossover_traits
 * 
 * \param Pop The Population type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		>
class middle_recombination_crossover_traits
	: public crossover_traits_base<middle_recombination_crossover_traits<Pop, Rand>, Pop, Rand>
{
	/// \name Types
	/// @{
	public:
		typedef crossover_traits_base<middle_recombination_crossover_traits<Pop, Rand>, Pop, Rand>	base_type;
		typedef Pop																					population_type;
		typedef typename_type_k population_type::individual_type									individual_type;
		typedef typename_type_k individual_type::size_type											size_type;
		typedef typename_type_k individual_type::bool_type											bool_type;
		typedef typename_type_k individual_type::float_type											float_type;
		typedef typename_type_k individual_type::index_type											index_type;
		typedef typename_type_k individual_type::int_type											int_type;
		typedef Rand																				random_type;
	/// @}
	
	/// \name Constructors
	/// @{
	public:
		middle_recombination_crossover_traits()
			: base_type()
		{
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(random_type& rand)
		{
			base_type::init(rand);
		}
		/// cross i1 & i2
		void do_cross	(	individual_type& i1
						,	individual_type& i2
						)
		{
			size_type n = i1.size();
			EXTL_ASSERT(i2.size() == n);

			float_type d = 0.25;
			for (size_type i = 0; i < n; ++i)
			{
				float_type a1 = this->rand().fgenerate(-d, d + 1); 
				float_type a2 = this->rand().fgenerate(-d, d + 1); 

				float_type old_v1 = i1.value(i); 
				float_type old_v2 = i2.value(i); 

				i1.value(i, old_v1 + a1 * (old_v2 - old_v1));	
				i2.value(i, old_v1 + a2 * (old_v2 - old_v1));
			}
		}
	/// @}
};

/*!\brief linear_recombination_crossover_traits
 * 
 * \param Pop The Population type
 * \param Rand The random type
 *
 * \ingroup extl_group_intelligence
 */
template<	typename_param_k Pop
		,	typename_param_k Rand
		>
class linear_recombination_crossover_traits
	: public crossover_traits_base<linear_recombination_crossover_traits<Pop, Rand>, Pop, Rand>
{
	/// \name Types
	/// @{
	public:
		typedef crossover_traits_base<linear_recombination_crossover_traits<Pop, Rand>, Pop, Rand>	base_type;
		typedef Pop																					population_type;
		typedef typename_type_k population_type::individual_type									individual_type;
		typedef typename_type_k individual_type::size_type											size_type;
		typedef typename_type_k individual_type::bool_type											bool_type;
		typedef typename_type_k individual_type::float_type											float_type;
		typedef typename_type_k individual_type::index_type											index_type;
		typedef typename_type_k individual_type::int_type											int_type;
		typedef Rand																				random_type;
	/// @}
		
	/// \name Constructors
	/// @{
	public:
		linear_recombination_crossover_traits()
			: base_type()
		{
		}
	/// @}

	/// \name Methods
	/// @{
	public:
		/// initialization
		void init(random_type& rand)
		{
			base_type::init(rand);
		}
		/// cross i1 & i2
		void do_cross	(	individual_type& i1
						,	individual_type& i2
						)
		{
			size_type n = i1.size();
			EXTL_ASSERT(i2.size() == n);

			float_type d = 0.25;
			float_type a1 = this->rand().fgenerate(-d, d + 1); 
			float_type a2 = this->rand().fgenerate(-d, d + 1); 

			// cross
			for (size_type i = 0; i < n; ++i)
			{
				float_type old_v1 = i1.value(i); 
				float_type old_v2 = i2.value(i); 

				i1.value(i, old_v1 + a1 * (old_v2 - old_v1));	
				i2.value(i, old_v1 + a2 * (old_v2 - old_v1));
			}
		}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_FOPTI_CROSSOVER_TRAITS_H */
/* //////////////////////////////////////////////////////////////////// */
