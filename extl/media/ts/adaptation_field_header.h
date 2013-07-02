/* ///////////////////////////////////////////////////////////////////////
 * File:		adaptation_field_header.h		
 *
 * Created:		09.03.05
 * Updated:		09.03.05
 *
 * Brief:		the adaptation_field_header class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_ADAPTATION_FIELD_HEADER_H
#define EXTL_MEDIA_TS_ADAPTATION_FIELD_HEADER_H

/*!\file adaptation_field_header.h
 * \brief the adaptation_field_header class
 */
#ifndef __cplusplus
#	error adaptation_field_header.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../memory/buffer.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief the adaptation_field_header class
 *
 * \ingroup extl_group_media
 *
 * \code
 *	// program clock reference
 *  struct adaptation_field_header
	{
		length									: 8		;
		discontinuity_indicator					: 1		;
		random_access_indicator					: 1		;
		elementary_stream_priority_indicator	: 1		;
		pcr_flag								: 1		;
		opcr_flag								: 1		;
		splicing_point_flag						: 1		;
		private_data_flag						: 1		;
		extension_flag							: 1		;
	};
 * \endcode
 *
 * \param Pck the packet type
 */
template<typename_param_k Ada>
class adaptation_field_header
{
	/// \name Public Types
	/// @{
	public:
		typedef Ada								adaptation_type;
		typedef adaptation_field_header			class_type;
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
		// base + base1 + reseved + pcr_extension
		// |=> 33bit <=|      6            9
		struct									members_type
		{
			byte_type adaptation_length						;

			// \note defined in reverse order by byte_type
			byte_type extension_flag						: 1		;	//< low bit
			byte_type private_data_flag						: 1		;
			byte_type splicing_point_flag					: 1		;
			byte_type opcr_flag								: 1		;
			byte_type pcr_flag								: 1		;
			byte_type elementary_stream_priority_indicator	: 1		;
			byte_type random_access_indicator				: 1		;
			byte_type discontinuity_indicator				: 1		;	//< high bit
		};
	/// @}

	/// \name Constants
	/// @{
	public:
		enum {	en_header_size	=	2	};
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
		pointer				data()							{ return (adaptation().data());	}
		const_pointer		data() const					{ return (adaptation().data());	}

		size_type			adaptation_length() const				{ return static_cast<size_type>(members().adaptation_length);			}
		void				adaptation_length(size_type value)		{ members().adaptation_length = static_cast<byte_type>(value);			}
	
		size_type			discontinuity_indicator() const				{ return static_cast<size_type>(members().discontinuity_indicator);		}
		void				discontinuity_indicator(size_type value)	{ members().discontinuity_indicator = static_cast<byte_type>(value);		}
	
		size_type			random_access_indicator() const				{ return static_cast<size_type>(members().random_access_indicator);		}
		void				random_access_indicator(size_type value)	{ members().random_access_indicator = static_cast<byte_type>(value);		}

		size_type			elementary_stream_priority_indicator() const			{ return static_cast<size_type>(members().elementary_stream_priority_indicator);		}
		void				elementary_stream_priority_indicator(size_type value)	{ members().elementary_stream_priority_indicator = static_cast<byte_type>(value);	}
		
		size_type			pcr_flag() const							{ return static_cast<size_type>(members().pcr_flag);				}
		void				pcr_flag(size_type value)					{ members().pcr_flag = static_cast<byte_type>(value);			}
		
		size_type			opcr_flag() const							{ return static_cast<size_type>(members().opcr_flag);			}
		void				opcr_flag(size_type value)					{ members().opcr_flag = static_cast<byte_type>(value);			}
	
		size_type			splicing_point_flag() const					{ return static_cast<size_type>(members().splicing_point_flag);		}
		void				splicing_point_flag(size_type value)		{ members().splicing_point_flag = static_cast<byte_type>(value);		}

		size_type			private_data_flag() const					{ return static_cast<size_type>(members().private_data_flag);		}
		void				private_data_flag(size_type value)			{ members().private_data_flag = static_cast<byte_type>(value);		}
	
		size_type			extension_flag() const						{ return static_cast<size_type>(members().extension_flag);	}
		void				extension_flag(size_type value)				{ members().extension_flag = static_cast<byte_type>(value);	}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the adaptation_field_header size
		size_type			size() const		{ return en_header_size;			}

		/// return the offset at the packet
		size_type			offset() const		{ return adaptation().offset();		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_ADAPTATION_FIELD_HEADER_H */
/* //////////////////////////////////////////////////////////////////// */
