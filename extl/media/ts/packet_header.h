/* ///////////////////////////////////////////////////////////////////////
 * File:		packet_header.h		
 *
 * Created:		09.02.06
 * Updated:		09.02.28
 *
 * Brief:		the packet_header class - TS packet packet_header
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_PACKET_HEADER_H
#define EXTL_MEDIA_TS_PACKET_HEADER_H

/*!\file packet_header.h
 * \brief the packet_header class - TS packet packet_header
 */
#ifndef __cplusplus
#	error packet_header.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief packet packet_header
 *
 * \ingroup extl_group_media
 *
 * \code
 *	// transport packet packet_header
 *  struct packet_header
	{
		sync_byte 						: 8		;
		transport_error_indicator 		: 1		;
		payload_unit_start_indicator 	: 1		;
		transport_priority 				: 1		;
		pid 							: 13	;
		transport_scrambling_control 	: 2		;
		adaptation_field_control 		: 2		;
		continuity_counter 				: 4		;
	};
 * \endcode
 *
 * \param Pck the packet type
 */
template<typename_param_k Pck>
class packet_header
{
	/// \name Public Types
	/// @{
	public:
		typedef Pck								packet_type;
		typedef packet_header					class_type;
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
		struct									members_type
		{
			// \note defined in reverse order by dword_type
			dword_type continuity_counter 					: 4		;	//< low bit
			dword_type adaptation_field_control 			: 2		;
			dword_type transport_scrambling_control 		: 2		;
			dword_type pid 									: 13	;
			dword_type transport_priority 					: 1		;
			dword_type payload_unit_start_indicator 		: 1		;
			dword_type transport_error_indicator 			: 1		;
			dword_type sync_byte 							: 8		;	//< high bit
		};
	/// @}

	/// \name Constants
	/// @{
	public:
		// sync_byte flag
		enum {	en_sync_byte	=	0x47	};

		// the packet header size
		enum {	en_header_size	=	4		};
	/// @}

	/// \name Private Accessors
	/// @{
	private:
		packet_type&		packet()			{ return static_cast<packet_type&>(*this);					}
		packet_type const&	packet() const		{ return static_cast<packet_type const&>(*this);			}

		members_type&		members()			{ return *reinterpret_cast<members_type*>(data());			}
		members_type const&	members() const		{ return *reinterpret_cast<members_type const*>(data());	}
	/// @}

	/// \name Public Accessors
	/// @{
	public:
		pointer				data()											{ return (packet().data() + offset());										}
		const_pointer		data() const									{ return (packet().data() + offset());										}

		size_type			sync_byte() const								{ return static_cast<size_type>(members().sync_byte);						}
		void				sync_byte(size_type value)						{ members().sync_byte = static_cast<dword_type>(value);						}
		
		size_type			transport_error_indicator() const				{ return static_cast<size_type>(members().transport_error_indicator);		}
		void				transport_error_indicator(size_type value)		{ members().transport_error_indicator = static_cast<dword_type>(value);		}
		
		size_type			payload_unit_start_indicator() const			{ return static_cast<size_type>(members().payload_unit_start_indicator);	}
		void				payload_unit_start_indicator(size_type value)	{ members().payload_unit_start_indicator = static_cast<dword_type>(value);	}

		size_type			transport_priority() const						{ return static_cast<size_type>(members().transport_priority);				}
		void				transport_priority(size_type value)				{ members().transport_priority = static_cast<dword_type>(value);			}

		size_type			pid() const										{ return static_cast<size_type>(members().pid);								}
		void				pid(size_type value)							{ members().pid = static_cast<dword_type>(value);							}

		size_type			transport_scrambling_control() const			{ return static_cast<size_type>(members().transport_scrambling_control);	}
		void				transport_scrambling_control(size_type value)	{ members().transport_scrambling_control = static_cast<dword_type>(value);	}

		size_type			adaptation_field_control() const				{ return static_cast<size_type>(members().adaptation_field_control);		}
		void				adaptation_field_control(size_type value)		{ members().adaptation_field_control = static_cast<dword_type>(value);		}

		size_type			continuity_counter() const						{ return static_cast<size_type>(members().continuity_counter);				}
		void				continuity_counter(size_type value)				{ members().continuity_counter = static_cast<dword_type>(value);			}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the packet_header size
		size_type			size() const		{ return en_header_size;		}		
		
		/// return the offset at the packet
		size_type			offset() const		{ return 0;						}
	
		/// return \true if the packet is valid
		bool_type			is_valid() const	{ return ((data() != NULL) && (sync_byte() == en_sync_byte) && (size() < packet().size()));	}
	/// @}

	/// \name Attach & Detach
	/// @{
	public:
		/// decodes packet packet_header
		void				decode()			{ packet().buffer().reverse(offset(), size());		}
		/// encodes packet packet_header
		void				encode()			{ packet().buffer().reverse(offset(), size());		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_PACKET_HEADER_H */
/* //////////////////////////////////////////////////////////////////// */
