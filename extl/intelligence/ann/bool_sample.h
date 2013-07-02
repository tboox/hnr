/* ///////////////////////////////////////////////////////////////////////
 * File:		bool_sample.h		
 *
 * Created:		08.12.17		
 * Updated:		09.03.15
 *
 * Brief:		The bool_sample class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_BOOL_SAMPLE_H
#define EXTL_INTELLIGENCE_ANN_BOOL_SAMPLE_H

/*!\file bool_sample.h
 * \brief bool_sample class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief bool_sample
 *
 * \param InN the input demension
 * \param OutN the real demension
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		>
class bool_sample
{
	/// \name Types
	/// @{
	public:
		typedef bool_sample														class_type;
		typedef e_bool_t														bool_type;
		typedef e_size_t														size_type;
		typedef size_type														index_type;
		typedef e_float_t														float_type;
		typedef e_char_t														achar_type;
		typedef e_wchar_t														wchar_type;
		typedef bit_array<	size_type
						,	stack_buffer<	size_type
										,	InN
										,	typename_type_k memory_traits_selector<size_type>::memory_traits_type
										>
						>														input_type;
		typedef bit_array<	size_type
						,	stack_buffer<	size_type
										,	OutN
										,	typename_type_k memory_traits_selector<size_type>::memory_traits_type
										>
						>														real_type;
		typedef real_type														output_type;
	/// @}

	/// \name Members
	/// @{
	private:
		input_type																m_input;
		real_type																m_real;
		output_type																m_output;
	/// @}

	/// \name Constants 
	/// @{
	public:
		enum {	en_input_size = InN		};
		enum {	en_output_size = OutN	};
	/// @}


	/// \name Constructors
	/// @{
	public:
		bool_sample()
			: m_input(en_input_size)
			, m_real(en_output_size)
			, m_output(en_output_size)
		{
		}
		explicit_k bool_sample(input_type const& input)
			: m_input(input)
			, m_real(en_output_size)
			, m_output(en_output_size)
		{
		}
		bool_sample(input_type const& input, real_type const& real)
			: m_input(input)
			, m_real(real)
			, m_output(en_output_size)
		{
		}
	/// @}

	/// \name Native Accessors
	/// @{
	public:
		/// gets the input sample
		input_type&				input()					{ return m_input;	}
		/// gets the input sample
		input_type const&		input() const			{ return m_input;	}

		/// gets the real sample
		real_type&				real()					{ return m_real;	}
		/// gets the real sample
		real_type const&		real() const			{ return m_real;	}

		/// gets the output real
		output_type&			output()				{ return m_output;	}
		/// gets the output real
		output_type const&		output() const			{ return m_output;	}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// gets the size of the input
		size_type const			input_size() const		{ return m_input.size();	}
		/// gets the size of the real
		size_type const			real_size() const		{ return m_real.size();	}
		/// gets the size of the output
		size_type const			output_size() const		{ return m_output.size();	}

	/// @}

	/// \name Accessors (Recommended)
	/// @{
	public:
		/// sets the input by string e.g. "010101"
		void					binput(achar_type const* s, size_type n)	{ m_input.assign(s, n);		}
		/// sets the input by string e.g. "010101"
		void					binput(achar_type const* s)					{ m_input.assign(s);		}
		/// sets the input by string e.g. "010101"
		void					binput(wchar_type const* s, size_type n)	{ m_input.assign(s, n);		}
		/// sets the input by string e.g. "010101"
		void					binput(wchar_type const* s)					{ m_input.assign(s);		}

		/// sets the input by digit e.g. 4
		/// \note cannot be larger than 32-bits
		void					dinput(size_type digit)						{ m_input.numeric(digit);	}
		/// gets the input by digit e.g. 4
		/// \note cannot be larger than 32-bits
		size_type				dinput() const								{ return m_input.numeric();	}

		/// sets the input by string e.g. "010101"
		void					breal(achar_type const* s, size_type n)		{ m_real.assign(s, n);	}
		/// sets the input by string e.g. "010101"
		void					breal(achar_type const* s)					{ m_real.assign(s);		}
		/// sets the input by string e.g. "010101"
		void					breal(wchar_type const* s, size_type n)		{ m_real.assign(s, n);	}
		/// sets the input by string e.g. "010101"
		void					breal(wchar_type const* s)					{ m_real.assign(s);		}

		/// sets the real by digit e.g. 4
		/// \note cannot be larger than 32-bits
		void					dreal(size_type digit)						{ m_real.numeric(digit);	}
		/// gets the real by digit e.g. 4
		/// \note cannot be larger than 32-bits
		size_type				dreal() const								{ return m_real.numeric();	}

		/// sets the output by digit e.g. 4
		/// \note cannot be larger than 32-bits
		void					doutput(size_type digit)					{ m_output.numeric(digit);	}
		/// gets the output sample by digit e.g. 4
		/// \note cannot be larger than 32-bits
		size_type				doutput() const								{ return m_output.numeric();}

		/// sets the float input value at the given position
		void					set_finput(index_type i, float_type f)		{ m_input.set(i, (xtl_round45(f) == 1));			}
		/// gets the float input at the given position
		float_type const		get_finput(index_type i) const				{ return static_cast<float_type>(m_input.get(i));	}

		/// sets the bool input value at the given position
		void					set_binput(index_type i, bool_type b)		{ m_input.set(i, b);		}
		/// gets the bool input at the given position
		bool_type const			get_binput(index_type i) const				{ return m_input.get(i);	}

		/// sets the float real value at the given position
		void					set_freal(index_type i, float_type f)		{ m_real.set(i, (xtl_round45(f) == 1));			}
		/// gets the float real at the given position
		float_type const		get_freal(index_type i) const				{ return static_cast<float_type>(m_real.get(i));	}

		/// sets the bool real value at the given position
		void					set_breal(index_type i, bool_type b)		{ m_real.set(i, b);		}
		/// gets the bool real at the given position
		bool_type const			get_breal(index_type i) const				{ return m_real.get(i);	}

		/// sets the float output value at the given position
		void					set_foutput(index_type i, float_type f)		{ m_output.set(i, (xtl_round45(f) == 1));			}
		/// gets the float output at the given position
		float_type const		get_foutput(index_type i) const				{ return static_cast<float_type>(m_output.get(i));	}

		/// sets the bool output value at the given position
		void					set_boutput(index_type i, bool_type b)		{ m_output.set(i, b);		}
		/// gets the bool output at the given position
		bool_type const			get_boutput(index_type i) const				{ return m_output.get(i);	}
	/// @}
};


/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_BOOL_SAMPLE_H */
/* //////////////////////////////////////////////////////////////////// */
