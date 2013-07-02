/* ///////////////////////////////////////////////////////////////////////
 * File:		adaptation_field.h		
 *
 * Created:		09.02.06
 * Updated:		09.02.28
 *
 * Brief:		the adaptation_field class - TS packet adaptation_field
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_ADAPTATION_FIELD_H
#define EXTL_MEDIA_TS_ADAPTATION_FIELD_H

/*!\file adaptation_field.h
 * \brief the adaptation_field class - TS packet adaptation_field
 */
#ifndef __cplusplus
#	error adaptation_field.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "adaptation_field_header.h"
#include "pcr.h"
#include "opcr.h"
#include "splicing.h"
#include "private_data.h"
#include "adaptation_field_extension.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief packet adaptation_field
 *
 * \ingroup extl_group_media
 *
 * \code
 *	// transport packet adaptation filed
 *  struct adaptation_field
	{
		adaptation field header
		[pcr(program clock reference)];
		[opcr(original program clock reference)];
		[splice_countdown]
		[private_data]
		[adaptation_field_extension]
		[stuffing_byte]
	};
 * \endcode
 *
 * \param Pck the packet type
 */
template<typename_param_k Pck>
class adaptation_field
	: private adaptation_field_header<adaptation_field<Pck> >
	, private pcr<adaptation_field<Pck> >
	, private opcr<adaptation_field<Pck> >
	, private splicing<adaptation_field<Pck> >
	, private private_data<adaptation_field<Pck> >
	, private adaptation_field_extension<adaptation_field<Pck> >
{
	/// \name Public Types
	/// @{
	public:
		typedef Pck											packet_type;
		typedef adaptation_field							class_type;
		typedef e_byte_t									byte_type;
		typedef e_uint16_t									word_type;
		typedef e_uint32_t									dword_type;
		typedef e_uint64_t									qword_type;
		typedef byte_type*									pointer;
		typedef byte_type const*							const_pointer;
		typedef e_size_t									size_type;
		typedef size_type									index_type;
		typedef e_bool_t									bool_type;
		typedef adaptation_field_header<class_type>			header_type;
		friend												header_type;
		typedef pcr<class_type>								pcr_type;
		friend												pcr_type;
		typedef opcr<class_type>							opcr_type;
		friend												opcr_type;
		typedef splicing<class_type>						splicing_type;
		friend												splicing_type;
		typedef private_data<class_type>					private_data_type;
		friend												private_data_type;
		typedef adaptation_field_extension<class_type>		extension_type;
		friend												extension_type;
	/// @}

	/// \name Constants
	/// @{
	public:
		enum {	en_header_size	=	2	};
	/// @}

	/// \name Constructors
	/// @{
	public:
		adaptation_field()
			: header_type()
			, pcr_type()
			, opcr_type()
		{}
	/// @}

	/// \name Private Accessors
	/// @{
	private:
		packet_type&		packet()									{ return static_cast<packet_type&>(*this);				}
		packet_type const&	packet() const								{ return static_cast<packet_type const&>(*this);		}
	/// @}

	/// \name Public Accessors
	/// @{
	public:
		pointer						data()						{ return (packet().data() + offset());					}
		const_pointer				data() const				{ return (packet().data() + offset());					}

		header_type&				header()					{ return static_cast<header_type&>(*this);				}
		header_type const&			header() const				{ return static_cast<header_type const&>(*this);		}

		pcr_type&					pcr()						{ return static_cast<pcr_type&>(*this);					}
		pcr_type const&				pcr() const					{ return static_cast<pcr_type const&>(*this);			}

		opcr_type&					opcr()						{ return static_cast<opcr_type&>(*this);				}
		opcr_type const&			opcr() const				{ return static_cast<opcr_type const&>(*this);			}

		splicing_type&				splicing()					{ return static_cast<splicing_type&>(*this);			}
		splicing_type const&		splicing() const			{ return static_cast<splicing_type const&>(*this);		}

		private_data_type&			private_data()				{ return static_cast<private_data_type&>(*this);		}
		private_data_type const&	private_data() const		{ return static_cast<private_data_type const&>(*this);	}

		extension_type&				extension()					{ return static_cast<extension_type&>(*this);			}
		extension_type const&		extension() const			{ return static_cast<extension_type const&>(*this);		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the adaptation field size
		size_type			size() const					{ return header().adaptation_length();							}

		/// return the offset at the packet
		size_type			offset() const					{ return (packet().header().offset() + packet().header().size());	}

		/// return \true if exists adaptation field 
		bool_type			exists() const					{ return (packet().header().adaptation_field_control() == 0x2 || packet().header().adaptation_field_control() == 0x3);	}

		/// return \true if the adaptation field is valid
		bool_type			is_valid() const				{ return ((data() != NULL)) && ((size() + packet().header().size()) <= packet().size());	}
	/// @}

	/// \name Attach & Detach
	/// @{
	public:
		/// decodes packet packet_header
		void				decode()			
		{ 
			if (exists())
			{
				pcr().decode(); 
				opcr().decode();
				extension().decode();
			}
		}
		/// encodes packet packet_header
		void				encode()			
		{ 
			if (exists())
			{
				extension().encode();
				pcr().encode(); 
				opcr().encode();	
			}
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_ADAPTATION_FIELD_H */
/* //////////////////////////////////////////////////////////////////// */
