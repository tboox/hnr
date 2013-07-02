/* ///////////////////////////////////////////////////////////////////////
 * File:		packet.h		
 *
 * Created:		09.02.06
 * Updated:		09.02.28
 *
 * Brief:		the packet class - TS packet
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_PACKET_H
#define EXTL_MEDIA_TS_PACKET_H

/*!\file packet.h
 * \brief the packet class - TS packet
 */
#ifndef __cplusplus
#	error packet.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../memory/buffer.h"
#include "packet_header.h"
#include "adaptation_field.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief packet
 *
 * \ingroup extl_group_media
 *
 * \code
 * // transport packet format - TS
 *  struct packet
	{
		packet_header;
		[adaptation_field];
		[payload_data];
	};
 * \endcode
 *
 * \code
	// non-static
	packet p1;
	p1.attach(buf);
	printf("%x\n", p1.sync_byte());
	printf("%x\n", p1.transport_error_indicator());
	printf("%x\n", p1.payload_unit_start_indicator());
	printf("%x\n", p1.transport_priority());
	printf("%x\n", p1.pid());
	printf("%x\n", p1.transport_scrambling_control());
	printf("%x\n", p1.adaptation_field_control());
	printf("%x\n", p1.continuity_counter());
	// modify payload ...
	p1.detach();

	// static
	printf("%x\n", packet::pid(buf));
 *
 * \endcode
 */
class packet
: private packet_header<packet>
, private adaptation_field<packet>
{
	/// \name Types
	/// @{
	public:
		typedef packet									class_type;
		typedef e_byte_t								byte_type;
		typedef e_uint16_t								word_type;
		typedef e_uint32_t								dword_type;
		typedef e_uint64_t								qword_type;
		typedef byte_type*								pointer;
		typedef byte_type const*						const_pointer;
		typedef e_size_t								size_type;
		typedef size_type								index_type;
		typedef e_bool_t								bool_type;
		typedef packet_header<class_type>				header_type;
		typedef adaptation_field<class_type>			adaptation_type;
		typedef attached_buffer	<	byte_type
								,	EXTL_TS_PACKET_MAX_SIZE + 1
								>						buffer_type;
	/// @}

	/// \name Members
	/// @{
	private:
		buffer_type										m_buffer;
		bool_type										m_is_decoded;
	/// @}

	/// \name Constants
	/// @{
	public:
		// the maximum size of the packet: max(188, 204)
		enum {	en_max_size	=	EXTL_TS_PACKET_MAX_SIZE	};

		// pid flag
		enum {	en_pid_pat		=	0x0000	};	//!< program association table
		enum {	en_pid_cat		=	0x0001	};	//!< conditional access table
		enum {	en_pid_tsdt		=	0x0002	};	//!< transport atream description table
		enum {	en_pid_nit		=	0x0010	};	//!< network information table
		enum {	en_pid_sdt		=	0x0011	};	//!< service description table
		enum {	en_pid_bat		=	0x0011	};
		enum {	en_pid_eit		=	0x0012	};	//!< event information table
		enum {	en_pid_tdt		=	0x0014	};
		enum {	en_pid_tot		=	0x0014	};
		enum {	en_pid_dit		=	0x001E	};
		enum {	en_pid_sit		=	0x001F	};
		enum {	en_pid_null		=	0x1FFF	};	//!< null packet
	/// @}

	/// \name Constructors
	/// @{
	public:
		packet()
			: header_type()
			, adaptation_type()
			, m_buffer()
			, m_is_decoded(e_false_v)
		{}
		explicit_k packet(const_pointer p)
			: header_type()
			, adaptation_type()
			, m_buffer()
			, m_is_decoded(e_false_v)
		{
			decode(p);
		}
		~packet()
		{
			encode();
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		buffer_type&			buffer()			{ return m_buffer;			}
		buffer_type const&		buffer() const		{ return m_buffer;			}

		pointer					data()				{ return buffer().data();	}
		const_pointer			data() const		{ return buffer().data();	}

		header_type&			header()			{ return static_cast<header_type&>(*this);				}
		header_type const&		header() const		{ return static_cast<header_type const&>(*this);		}

		adaptation_type&		adaptation()		{ return static_cast<adaptation_type&>(*this);			}
		adaptation_type const&	adaptation() const	{ return static_cast<adaptation_type const&>(*this);	}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// return the packet size
		/// common: 188
		/// other: 204 == 188 + 16(CRC)
		size_type			size() const		{ return 188;								}

		/// return \true if the packet is pat
		bool_type			is_pat() const		{ return (header().pid() == en_pid_pat);	}

		/// return \true if the packet is cat
		bool_type			is_cat() const		{ return (header().pid() == en_pid_cat);	}

		/// return \true if the packet is tsdt
		bool_type			is_tsdt() const		{ return (header().pid() == en_pid_tsdt);	}

		/// return \true if the packet is null
		bool_type			is_null() const		{ return (header().pid() == en_pid_null);	}

		// return \true if the packet has decoded
		bool_type			is_decoded() const	{ return m_is_decoded;						}

		/// return \true if the packet is scrambled
		bool_type			is_scrambling() const	{ return (header().transport_scrambling_control() != 0);	}

		/// return \true if the packet exists error
		bool_type			exists_error() const	{ return (header().transport_error_indicator() != 0);		}

		/// return \true if the packet is valid
		bool_type			is_valid() const		{ return (header().is_valid() && adaptation().is_valid());	}
	/// @}

	/// \name Mutators
	/// @{
	public:
		/// decodes transport packet
		/// \note p points to encoded stream data
		void				decode(const_pointer p)
		{
			EXTL_MESSAGE_ASSERT(!is_decoded(), "cannot decode the same stream repeatly");
			if (is_decoded()) return ;
			m_is_decoded = e_true_v;

			buffer().attach(p, size());
			header().decode();
			adaptation().decode();
		}
		/// encodes transport packet
		const_pointer		encode()
		{
			EXTL_MESSAGE_ASSERT(is_decoded(), "cannot encode the same stream repeatly");
			if (!is_decoded()) return NULL;
			m_is_decoded = e_false_v;

			adaptation().encode();
			header().encode();
			return buffer().detach();
		}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_PACKET_H */
/* //////////////////////////////////////////////////////////////////// */
