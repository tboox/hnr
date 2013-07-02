/* ///////////////////////////////////////////////////////////////////////
 * File:		float_sample.h		
 *
 * Created:		09.03.15
 * Updated:		09.03.15
 *
 * Brief:		The float_sample class 
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_INTELLIGENCE_ANN_FLOAT_SAMPLE_H
#define EXTL_INTELLIGENCE_ANN_FLOAT_SAMPLE_H

/*!\file float_sample.h
 * \brief float_sample class
 */

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_BEGIN_WHOLE_NAMESPACE

/*!brief float_sample
 *
 * \param InN the input demension
 * \param OutN the output demension
 *
 * \ingroup extl_group_intelligence
 */
template<	e_size_t InN
		,	e_size_t OutN
		>
class float_sample
{
	/// \name Types
	/// @{
	public:
		typedef float_sample													class_type;
		typedef e_bool_t														bool_type;
		typedef e_size_t														size_type;
		typedef size_type														index_type;
		typedef e_float_t														float_type;
		typedef e_char_t														achar_type;
		typedef e_wchar_t														wchar_type;
		typedef typename_type_k vvector_selector<float_type>::vvector_type		input_type;
		typedef typename_type_k vvector_selector<float_type>::vvector_type		output_type;
		typedef typename_type_k vvector_selector<float_type>::vvector_type		real_type;
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
		float_sample()
			: m_input(en_input_size)
			, m_real(en_output_size)
			, m_output(en_output_size)
		{
		}
		explicit_k float_sample(input_type const& input)
			: m_input(input)
			, m_real(en_output_size)
			, m_output(en_output_size)
		{
		}
		float_sample(input_type const& input, real_type const& real)
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

		/// gets the output sample
		output_type&			output()				{ return m_output;	}
		/// gets the output sample
		output_type const&		output() const			{ return m_output;	}

		/// gets the result output
		output_type&			real()					{ return m_real;	}
		/// gets the result output
		output_type const&		real() const			{ return m_real;	}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// gets the size of the input
		size_type const			input_size() const		{ return m_input.size();	}
		/// gets the size of the real
		size_type const			real_size() const		{ return m_real.size();		}
		/// gets the size of the output
		size_type const			output_size() const		{ return m_output.size();	}

	/// @}

	/// \name Accessors (Recommended)
	/// @{
	public:
		/// sets the input by string e.g. "010101"
		void					binput(achar_type const* s, size_type n);
		/// sets the input by string e.g. "010101"
		void					binput(achar_type const* s)					{ binput(s, (NULL != s)? std_strlen(s) : 0);	}
		/// sets the input by string e.g. "010101"
		void					binput(wchar_type const* s, size_type n);
		/// sets the input by string e.g. "010101"
		void					binput(wchar_type const* s)					{ binput(s, (NULL != s)? std_strlen(s) : 0);	}

		/// sets the input by digit e.g. 4
		/// \note cannot be larger than 32-bits
		void					dinput(size_type digit);
		/// gets the input by digit e.g. 4
		/// \note cannot be larger than 32-bits
		size_type				dinput() const;

		/// sets the input by string e.g. "010101"
		void					breal(achar_type const* s, size_type n);
		/// sets the input by string e.g. "010101"
		void					breal(achar_type const* s)					{ breal(s, (NULL != s)? std_strlen(s) : 0);		}
		/// sets the input by string e.g. "010101"
		void					breal(wchar_type const* s, size_type n);
		/// sets the input by string e.g. "010101"
		void					breal(wchar_type const* s)					{ breal(s, (NULL != s)? std_strlen(s) : 0);		}

		/// sets the real by digit e.g. 4
		/// \note cannot be larger than 32-bits
		void					dreal(size_type digit);
		/// gets the real by digit e.g. 4
		/// \note cannot be larger than 32-bits
		size_type				dreal() const;

		/// sets the output by digit e.g. 4
		/// \note cannot be larger than 32-bits
		void					doutput(size_type digit);
		/// gets the output sample by digit e.g. 4
		/// \note cannot be larger than 32-bits
		size_type				doutput() const;

		/// sets the float input value at the given position
		void					set_finput(index_type i, float_type f)		{ m_input[i] = f;		}
		/// gets the float input at the given position
		float_type const		get_finput(index_type i) const				{ return m_input[i];	}

		/// sets the bool input value at the given position
		void					set_binput(index_type i, bool_type b)		{ m_input[i] = static_cast<float_type>(b);	}
		/// gets the bool input at the given position
		bool_type const			get_binput(index_type i) const				{ return (xtl_round45(m_input[i]) == 1);	}

		/// sets the float real value at the given position
		void					set_freal(index_type i, float_type f)		{ m_real[i] = f;		}
		/// gets the float real at the given position
		float_type const		get_freal(index_type i) const				{ return m_real[i];	}

		/// sets the bool real value at the given position
		void					set_breal(index_type i, bool_type b)		{ m_real[i] = static_cast<float_type>(b);	}
		/// gets the bool real at the given position
		bool_type const			get_breal(index_type i) const				{ return (xtl_round45(m_real[i]) == 1);	}

		/// sets the float output value at the given position
		void					set_foutput(index_type i, float_type f)		{ m_output[i] = f;		}
		/// gets the float output at the given position
		float_type const		get_foutput(index_type i) const				{ return m_output[i];	}

		/// sets the bool output value at the given position
		void					set_boutput(index_type i, bool_type b)		{ m_output[i] = static_cast<float_type>(b);	}
		/// gets the bool output at the given position
		bool_type const			get_boutput(index_type i) const				{ return (xtl_round45(m_output[i]) == 1);	}
	/// @}
};
/* ///////////////////////////////////////////////////////////////////////
 * Implemention
 */
template<	e_size_t InN
		,	e_size_t OutN
		>
inline void float_sample<InN, OutN>::binput(achar_type const* s, size_type n)
{
	for (index_type i = 0; i < n; ++i) 
		set_binput(i, s[i] != '0');
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline void float_sample<InN, OutN>::binput(wchar_type const* s, size_type n)
{
	for (index_type i = 0; i < n; ++i) 
		set_binput(i, s[i] != L'0');
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline void float_sample<InN, OutN>::breal(achar_type const* s, size_type n)
{
	for (index_type i = 0; i < n; ++i) 
		set_breal(i, s[i] != '0');
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline void float_sample<InN, OutN>::breal(wchar_type const* s, size_type n)
{
	for (index_type i = 0; i < n; ++i) 
		set_breal(i, s[i] != L'0');
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline void float_sample<InN, OutN>::dinput(size_type digit)
{
	size_type n = xtl_min(input_size(), sizeof(size_type) * 8);
	bit_field<size_type> field(n);
	field.numeric(digit);
	for (index_type i = 0; i < n; ++i) 
		set_binput(i, field[i]);
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline typename_type_ret_k float_sample<InN, OutN>::
size_type float_sample<InN, OutN>::dinput() const
{
	size_type n = xtl_min(input_size(), sizeof(size_type) * 8);
	bit_field<size_type> field(n);
	for (index_type i = 0; i < n; ++i) 
		field.set(i, get_binput(i));
	return field.numeric();
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline void float_sample<InN, OutN>::dreal(size_type digit)
{
	size_type n = xtl_min(real_size(), sizeof(size_type) * 8);
	bit_field<size_type> field(n);
	field.numeric(digit);
	for (index_type i = 0; i < n; ++i) 
		set_breal(i, field[i]);
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline typename_type_ret_k float_sample<InN, OutN>::
size_type float_sample<InN, OutN>::dreal() const
{
	size_type n = xtl_min(real_size(), sizeof(size_type) * 8);
	bit_field<size_type> field(n);
	for (index_type i = 0; i < n; ++i) 
		field.set(i, get_breal(i));
	return field.numeric();
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline void float_sample<InN, OutN>::doutput(size_type digit)
{
	size_type n = xtl_min(output_size(), sizeof(size_type) * 8);
	bit_field<size_type> field(n);
	field.numeric(digit);
	for (index_type i = 0; i < n; ++i) 
		set_boutput(i, field[i]);
}
template<	e_size_t InN
		,	e_size_t OutN
		>
inline typename_type_ret_k float_sample<InN, OutN>::
size_type float_sample<InN, OutN>::doutput() const
{
	size_type n = xtl_min(output_size(), sizeof(size_type) * 8);
	bit_field<size_type> field(n);
	for (index_type i = 0; i < n; ++i) 
		field.set(i, get_boutput(i));
	return field.numeric();
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::intelligence namespace 
 */
EXTL_INTELLIGENCE_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif	/* EXTL_INTELLIGENCE_ANN_FLOAT_SAMPLE_H */
/* //////////////////////////////////////////////////////////////////// */
