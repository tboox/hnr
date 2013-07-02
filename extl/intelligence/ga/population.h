/* ///////////////////////////////////////////////////////////////////////
 * File:		population.h		
 *
 * Created:		08.09.09
 * Updated:		08.11.07
 *
 * Brief: The population class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_GA_POPULATION_H
#define EXTL_INTELLIGENCE_GA_POPULATION_H

/*!\file population.h
 * \brief The population class
 */
#ifndef __cplusplus
#	error population.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!\brief population class
 * 
 * \param Idl The individual type
 *
 * \ingroup extl_group_intelligence
 */
template<typename_param_k Idl>
class population
{
	/// \name Types
	/// @{
	public:
		typedef population														class_type;
		typedef Idl																individual_type;
		typedef typename_type_k individual_type::size_type						size_type;
		typedef typename_type_k individual_type::bool_type						bool_type;
		typedef typename_type_k individual_type::float_type						float_type;
		typedef typename_type_k individual_type::index_type						index_type;
		typedef typename_type_k individual_type::int_type						int_type;
		typedef typename_type_k buffer_selector<individual_type>::buffer_type	buffer_type;
	/// @}

	/// \name Members
	/// @{
	private:
		size_type																m_generation;
		buffer_type																m_individuals;
		float_type																m_fsum;
		float_type																m_fmin;
		float_type																m_fmax;
		float_type																m_favg;
	/// @}

	/// \name Constructors
	/// @{
	public:
		population()
			: m_generation(0)
			, m_individuals()
			, m_fsum(0)
			, m_fmin(0)
			, m_fmax(0)
			, m_favg(0)
		{}

		explicit_k population(size_type n)
			: m_generation(0)
			, m_individuals(n)
			, m_fsum(0)
			, m_fmin(0)
			, m_fmax(0)
			, m_favg(0)
		{}
	/// @}

	/// \name Mutations
	/// @{
	public:
		/// Resizes the number of the individuals in the population 
		void					resize(size_type n)				{ m_individuals.resize(n);		}
		/// Set the generation of the population
		void					generation(size_type g)			{ m_generation = g;				}
		/// Sets the sum of the fitness of all individuals
		void					fsum(float_type f)				{ m_fsum = f;					}
		/// Sets the minimum of the fitness of all individuals
		void					fmin(float_type f)				{ m_fmin = f;					}
		/// Sets the maximum of the fitness of all individuals
		void					fmax(float_type f)				{ m_fmax = f;					}
		/// Sets the average of the fitness of all individuals
		void					favg(float_type f)				{ m_favg = f;					}
	/// @}
	
	/// \name Attributes
	/// @{
	public:
		/// Gets the generation of the population
		size_type				generation() const				{ return m_generation;			}
		/// Returns the number of the individuals in the population 
		size_type				size() const					{ return m_individuals.size();	}
	
		/// Returns the const reference of the individual at the given index
		individual_type const&	individual(index_type i) const	{ return m_individuals[i];		}
		/// Returns thereference of the individual at the given index
		individual_type&		individual(index_type i)		{ return m_individuals[i];		}
		
		/// Returns the const reference of the individuals
		buffer_type const&		individuals() const				{ return m_individuals;			}
		/// Returns the reference of the individuals
		buffer_type&			individuals()					{ return m_individuals;			}

		/// Gets the sum of the fitness of all individuals
		float_type				fsum() const					{ return m_fsum;				}
		/// Gets the minimum of the fitness of all individuals
		float_type				fmin() const					{ return m_fmin;				}
		/// Gets the maximum of the fitness of all individuals
		float_type				fmax() const					{ return m_fmax;				}
		/// Gets the average of the fitness of all individuals
		float_type				favg() const					{ return m_favg;				}
		
		/// Returns the best individual of the population
		individual_type const&	best() const					
		{
			size_type n = size();
			index_type i;
			for (i = 0; i < n; ++i)
			{
				if (individual(i).is_best()) break;
			}
			EXTL_MESSAGE_ASSERT(i < n, "no best individual!");
			return individual(i);
		}
		/// Returns the best individual of the population
		individual_type&		best() 					
		{
			return const_cast<individual_type&>(static_cast<class_type const&>(*this).best());
		}
		/// Returns the worst individual of the population
		individual_type const&	worst() const					
		{
			size_type n = size();
			index_type i = 0;
			for (i = 0; i < n; ++i)
			{
				if (individual(i).is_worst()) break;
			}
			EXTL_MESSAGE_ASSERT(i < n, "no worst individual!");
			return individual(i);
		}
		/// Returns the worst individual of the population
		individual_type&		worst() 					
		{
			return const_cast<individual_type&>(static_cast<class_type const&>(*this).worst());
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_INTELLIGENCE_GA_POPULATION_H */
/* //////////////////////////////////////////////////////////////////// */
