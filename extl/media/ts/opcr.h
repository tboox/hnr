/* ///////////////////////////////////////////////////////////////////////
 * File:		opcr.h		
 *
 * Created:		09.02.06
 * Updated:		09.03.04
 *
 * Brief:		the opcr class - the original program clock reference
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_OPCR_H
#define EXTL_MEDIA_TS_OPCR_H

/*!\file opcr.h
 * \brief the opcr class - program clock reference
 */
#ifndef __cplusplus
#	error opcr.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief the program clock reference
 *
 * \ingroup extl_group_media
 *
 * \code
 *	// original program clock reference
 *  struct opcr
	{
		opcr_base			: 33	;
		reseved				: 6		;
		opcr_extension		: 9		;
	};
 * \endcode
 *
 * \param Ada the adaptation field type
 */
template<typename_param_k Ada>
class opcr
{
	/// \name Public Types
	/// @{
	public:
		typedef Ada								adaptation_type;
		typedef opcr							class_type;
		typedef e_byte_t						byte_type;
		typedef e_uint16_t						word_type;
		typedef e_uint32_t						dword_type;
		typedef e_uint64_t						qword_type;
		typedef byte_type*						pointer;
		typedef byte_type const*				const_pointer;
		typedef e_size_t						size_type;
		typedef size_type						index_type;
		typedef e_bool_t						bool_type;
	/// @}

	/// \name Member Type
	/// @{
	private:
		// program_clock_reference
		// base + base1 + reseved + opcr_extension
		// |=> 33bit <=|      6            9
		struct									members_type
		{
			// 32(base) + 1(base1)
			dword_type base											;

			// \note defined in reverse order by word_type
			word_type extension								: 9		;	//< low bit
			word_type reseved								: 6		;
			word_type base1									: 1		;	//< high bit
		};
	/// @}

	/// \name Constants
	/// @{
	public:
		enum {	en_opcr_size	=	6	};
	/// @}

	/// \name Private Accessors
	/// @{
	private:
		adaptation_type&		adaptation()		{ return static_cast<adaptation_type&>(*this);				}
		adaptation_type const&	adaptation() const	{ return static_cast<adaptation_type const&>(*this);		}

		members_type&			members()			{ return *reinterpret_cast<members_type*>(data());			}
		members_type const&		members() const		{ return *reinterpret_cast<members_type const*>(data());	}
	/// @}

	/// \name Public Accessors
	/// @{
	public:
		pointer				data()							{ return (adaptation().packet().data() + offset());	}
		const_pointer		data() const					{ return (adaptation().packet().data() + offset());	}

		qword_type			value() const					{ return (base() * 300 + extension());	}

		qword_type			base() const					{ return ((static_cast<qword_type>(members().base) << 1) | members().base1);									}
		void				base(qword_type value)			{ members().base = static_cast<dword_type>(value >> 1); members().base1 = static_cast<word_type>(value & 0x1);	}

		size_type			extension() const				{ return static_cast<size_type>(members().extension);		}
		void				extension(size_type value)		{ members().extension = static_cast<word_type>(value);		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the opcr size
		size_type			size() const		{ return en_opcr_size;			}

		/// return the offset at the packet
		size_type			offset() const		{ return (adaptation().pcr().offset() + (exists()? adaptation().pcr().size() : 0));	}

		///  return \true if exists opcr
		bool_type			exists() const		{ return (1 == adaptation().header().opcr_flag());	}

		/// return \true if the packet is valid
		bool_type			is_valid() const	{ return e_true_v;									}
	/// @}

	/// \name Attach & Detach
	/// @{
	public:
		/// decodes packet packet_header
		void				decode()			
		{ 
			if (exists()) 
			{
				adaptation().packet().buffer().reverse(offset(), 4); 
				adaptation().packet().buffer().reverse(offset() + 4, 2);	
			}
		}
		/// encodes packet packet_header
		void				encode()		
		{ 
			if (exists()) 
			{
				adaptation().packet().buffer().reverse(offset(), 4);
				adaptation().packet().buffer().reverse(offset() + 4, 2);	
			}
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_OPCR_H */
/* //////////////////////////////////////////////////////////////////// */
