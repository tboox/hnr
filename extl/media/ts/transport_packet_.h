/* ///////////////////////////////////////////////////////////////////////
 * File:		transport_packet.h		
 *
 * Created:		09.02.06
 * Updated:		09.02.06
 *
 * Brief:		the transport_packet class - TS packet
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_TRANSPORT_PACKET_H
#define EXTL_MEDIA_TS_TRANSPORT_PACKET_H

/*!\file transport_packet.h
 * \brief the transport_packet class - TS packet
 */
#ifndef __cplusplus
#	error transport_packet.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "../../memory/buffer.h"
#include "../../algorithm/algorithm.h"
#include "../../utility/bit_op.h"
#include "../../type/traits/is_unsigned.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media namespace 
 */
EXTL_MEDIA_BEGIN_WHOLE_NAMESPACE


/*!brief transport_packet
 *
 * \ingroup extl_group_media
 *
 * \code
 * // transport packet format - TS
 *  struct transport_packet
	{
		// header
		sync_byte 						: 8		;
		transport_error_indicator 		: 1		;
		payload_unit_start_indicator 	: 1		;
		transport_priority 				: 1		;
		pid 							: 13	;
		transport_scrambling_control 	: 2		;
		adaptation_field_control 		: 2		;
		continuity_counter 				: 4		;

		// adaptation field
		if (adaptation_field_control == 0x2 
		||	adaptation_field_control == 0x3 )
		{
			struct adaptation_field
			{
				// adaptation field header
				adaptation_field_length					: 8		;
				discontinuity_indicator					: 1		;
				random_access_indicator					: 1		;
				elementary_stream_priority_indicator	: 1		;
				pcr_flag								: 1		;
				opcr_flag								: 1		;
				splicing_point_flag						: 1		;
				transport_private_data_flag				: 1		;
				adaptation_field_extension_flag			: 1		;

				// program clock reference
				if (pcr_flag == 1)
				{
					pcr_base							: 33	;
					reseved								: 6		;
					pcr_extension						: 9		;
					
				}

				// original program clock reference
				if (opcr_flag == 1)
				{
					opcr_base							: 33	;
					reseved								: 6		;
					opcr_extension						: 9		;
				}

				// splicing point
				if (splicing_point_flag == 1)
				{
					splice_countdown					: 8		;
				}

				// transport private data
				if (transport_private_data_flag == 1)
				{
					for (i = 0; i < transport_private_data_length; ++i)
						private_data_byte				: 8		;

					if (adaptation_field_extension_flag == 1)
					{
						adaptation_field_extension_length	: 8		;
						ltw_flag							: 1		;
						piecewise_rate_flag					: 1		;
						seamless_splice_flag				: 1		;
						reserved							: 5		;

						if (ltw_flag == 1)
						{
							ltw_valid_flag					: 1		;
							ltw_offset						: 15	;
						}

						if (piecewise_rate_flag == 1)
						{
							reserved						: 2		;
							piecewise_rate					: 22	;
						}

						if (seamless_splice_flag == 1)
						{
							splice_type						: 4		;
							dts_next_au[32..30]				: 3		;
							marker_bit						: 1		;
							dts_next_au[29..15]				: 15	;
							marker_bit						: 1		;
							dts_next_au[14..0]				: 15	;
							marker_bit						: 1		;
						}

						for (i = 0; i < N; ++i)
							reserved						: 8		;
					}
				}

				for (i = 0; i < N; ++i)
					stuffing_byte						: 8		;
			};
		}

		// payload data
		if (adaptation_field_control == 0x1
		||	adaptation_field_control == 0x3 )
		{
			for (i = 0; i < N; ++i)
				data_byte				: 8		;
		}
	};
 * \endcode
 *
 * \note member methods and attributes need using attach and detach, static methods need not
 * \code
	// non-static
	transport_packet p1;
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
	printf("%x\n", transport_packet::pid(buf));
 *
 * \endcode
 */
class transport_packet
{
	/// \name Types
	/// @{
	public:
		typedef transport_packet						class_type;
		typedef e_byte_t								byte_type;
		typedef e_uint16_t								word_type;
		typedef e_uint32_t								dword_type;
		typedef e_uint64_t								qword_type;
		typedef byte_type*								pointer;
		typedef byte_type const*						const_pointer;
		typedef attached_buffer<byte_type, 188>			buffer_type;
		typedef e_size_t								size_type;
		typedef size_type								index_type;
		typedef e_bool_t								bool_type;
		struct											header_type
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

		struct											adaptation_field_header_type
		{
			byte_type adaptation_field_length						;

			// \note defined in reverse order by byte_type
			byte_type adaptation_field_extension_flag		: 1		;	//< low bit
			byte_type transport_private_data_flag			: 1		;
			byte_type splicing_point_flag					: 1		;
			byte_type opcr_flag								: 1		;
			byte_type pcr_flag								: 1		;
			byte_type elementary_stream_priority_indicator	: 1		;
			byte_type random_access_indicator				: 1		;
			byte_type discontinuity_indicator				: 1		;	//< high bit
		};

		// program_clock_reference
		// pcr_base + base1 + reseved + pcr_extension
		// |=>   33bit  <=|      6            9
		struct											pcr_type
		{
			// 32(pcr_base) + 1(base1)
			dword_type pcr_base										;

			// \note defined in reverse order by word_type
			word_type pcr_extension							: 9		;	//< low bit
			word_type reseved								: 6		;
			word_type base1									: 1		;	//< high bit
		};

		// original_program_clock_reference
		// opcr_base + base1 + reseved + pcr_extension
		// |=>   33bit   <=|      6            9
		struct											opcr_type
		{
			// 32(opcr_base) + 1(base1)
			dword_type opcr_base									;

			// \note defined in reverse order by word_type
			word_type opcr_extension						: 9		;	//< low bit
			word_type reseved								: 6		;
			word_type base1									: 1		;	//< high bit
		};

		// adaptation_field_extension_header
		struct											adaptation_field_extension_header_type
		{
			byte_type adaptation_field_extension_length		: 8		;

			// \note defined in reverse order by byte_type
			byte_type reserved								: 5		;
			byte_type seamless_splice_flag					: 1		;
			byte_type piecewise_rate_flag					: 1		;
			byte_type ltw_flag								: 1		;
		};

		// ltw
		struct											ltw_type
		{
			// \note defined in reverse order by word_type
			word_type ltw_offset							: 15	;
			word_type ltw_valid_flag						: 1		;
		};
	/// @}

	/// \name Enumerators
	/// @{
	public:
		// the packet header size
		enum {	en_header_size	=	sizeof(header_type)		};
		// the whole packet size
		enum {	en_packet_size	=	188						};
		//
		enum {	en_adaptation_field_header_size = sizeof(adaptation_field_header_type)	};
		// the pcr size
		enum {	en_pcr_size		=	sizeof(pcr_type)		};
		// the whole packet size
		enum {	en_opcr_size	=	sizeof(opcr_type)		};
		// the splice size
		enum {	en_splicing_size	=	1					};
		// the adaptation field extension _header size
		enum {	en_adaptation_field_extension_header_size	=	sizeof(adaptation_field_extension_header_type)					};
		// the ltw size
		enum {	en_ltw_size	=	sizeof(ltw_type)			};


		// for header_type::sync_byte
		enum {	en_sync_byte	=	0x47	};

		// for header_type::pid
		enum {	en_pid_pat		=	0x0000	};
		enum {	en_pid_cat		=	0x0001	};
		enum {	en_pid_tsdt		=	0x0002	};
		enum {	en_pid_null		=	0x1FFF	};	//!<? 0xFFFF or 0x 1FFF
	/// @}

	/// \name Members
	/// @{
	private:
		buffer_type										m_buffer;
	/// @}

	/// \name Constructors
	/// @{
	public:
		explicit_k transport_packet(const_pointer data = NULL)
		{
			attach(data);
		}
		~transport_packet()
		{
			EXTL_STATIC_ASSERT(sizeof(header_type) == 4);
			EXTL_STATIC_ASSERT(sizeof(byte_type) == 1);
			EXTL_STATIC_ASSERT(is_unsigned<byte_type>::value);
			EXTL_STATIC_ASSERT(is_unsigned<dword_type>::value);
		}
	/// @}

	/// \name Accessors
	/// @{
	public:
		buffer_type&		buffer()			{ return m_buffer;	}
		buffer_type const&	buffer() const		{ return m_buffer;	}

		pointer				data()				{ return buffer().data();	}
		const_pointer		data() const		{ return buffer().data();	}

		pointer				adaptation_field_data()			{ return (data() + en_header_size);	}
		const_pointer		adaptation_field_data() const	{ return (data() + en_header_size);	}

		pointer				pcr_data()			{ return (exists_pcr()? (adaptation_field_data() + en_adaptation_field_header_size) : adaptation_field_data());	}
		const_pointer		pcr_data() const	{ return (exists_pcr()? (adaptation_field_data() + en_adaptation_field_header_size) : adaptation_field_data());	}

		pointer				opcr_data()			{ return (exists_opcr()? (pcr_data() + en_pcr_size) : pcr_data());	}
		const_pointer		opcr_data() const	{ return (exists_opcr()? (pcr_data() + en_pcr_size) : pcr_data());	}

		pointer				splicing_data()			{ return (exists_splicing()? (opcr_data() + en_opcr_size) : opcr_data());	}
		const_pointer		splicing_data() const	{ return (exists_splicing()? (opcr_data() + en_opcr_size) : opcr_data());	}

		pointer				transport_private_data()		{ return (exists_private_data()? (splicing_data() + en_splicing_size) : splicing_data());	}
		const_pointer		transport_private_data() const	{ return (exists_private_data()? (splicing_data() + en_splicing_size) : splicing_data());	}
	
		pointer				private_data()			{ return &(transport_private_data()[1]);	}
		const_pointer		private_data() const	{ return &(transport_private_data()[1]);	}

		pointer				adaptation_field_extension_data()			{ return (exists_adaptation_field_extension()? (private_data() + private_data_length()) : transport_private_data());	}
		const_pointer		adaptation_field_extension_data() const		{ return (exists_adaptation_field_extension()? (private_data() + private_data_length()) : transport_private_data());	}
	
		pointer				ltw_data()			{ return (exists_ltw()? (adaptation_field_extension_data() + en_adaptation_field_extension_header_size) : adaptation_field_extension_data());	}
		const_pointer		ltw_data() const	{ return (exists_ltw()? (adaptation_field_extension_data() + en_adaptation_field_extension_header_size) : adaptation_field_extension_data());	}
	/// @}

	/// \name Protected Accessors
	/// @{
	public:
		header_type&		header()										{ return *reinterpret_cast<header_type*>(data());							}
		header_type const&	header() const									{ return *reinterpret_cast<header_type const*>(data());						}
		
		adaptation_field_header_type&		adaptation_field_header()		{ return *reinterpret_cast<adaptation_field_header_type*>(adaptation_field_data());			}
		adaptation_field_header_type const&	adaptation_field_header() const	{ return *reinterpret_cast<adaptation_field_header_type const*>(adaptation_field_data());	}

		pcr_type&			pcr_body()								{ return *reinterpret_cast<pcr_type*>(pcr_data());			}
		pcr_type const&		pcr_body() const						{ return *reinterpret_cast<pcr_type const*>(pcr_data());	}

		opcr_type&			opcr_body()								{ return *reinterpret_cast<opcr_type*>(opcr_data());		}
		opcr_type const&	opcr_body() const						{ return *reinterpret_cast<opcr_type const*>(opcr_data());	}

		adaptation_field_extension_header_type&			adaptation_field_extension()		{ return *reinterpret_cast<adaptation_field_extension_header_type*>(adaptation_field_extension_data());			}
		adaptation_field_extension_header_type const&	adaptation_field_extension() const	{ return *reinterpret_cast<adaptation_field_extension_header_type const*>(adaptation_field_extension_data());	}
	
		ltw_type&			ltw()					{ return *reinterpret_cast<ltw_type*>(ltw_data());			}
		ltw_type const&		ltw() const				{ return *reinterpret_cast<ltw_type const*>(ltw_data());	}

	/// @}

	/// \name Mutators
	/// @{
	public:
		/// attaches packet buffer - size: 188b
		/// \note maybe modify the buffer for performance
		void				attach(const_pointer p);
		/// detaches packet buffer
		/// \note maybe modify the buffer for performance
		const_pointer		detach();
	/// @}

	/// \name Header Attributes
	/// @{
	public:
		size_type			sync_byte() const								{ return static_cast<size_type>(header().sync_byte);						}
		void				sync_byte(size_type value)						{ header().sync_byte = static_cast<dword_type>(value);						}
		
		size_type			transport_error_indicator() const				{ return static_cast<size_type>(header().transport_error_indicator);		}
		void				transport_error_indicator(size_type value)		{ header().transport_error_indicator = static_cast<dword_type>(value);		}
		
		size_type			payload_unit_start_indicator() const			{ return static_cast<size_type>(header().payload_unit_start_indicator);		}
		void				payload_unit_start_indicator(size_type value)	{ header().payload_unit_start_indicator = static_cast<dword_type>(value);	}

		size_type			transport_priority() const						{ return static_cast<size_type>(header().transport_priority);				}
		void				transport_priority(size_type value)				{ header().transport_priority = static_cast<dword_type>(value);				}

		size_type			pid() const										{ return static_cast<size_type>(header().pid);								}
		void				pid(size_type value)							{ header().pid = static_cast<dword_type>(value);							}

		size_type			transport_scrambling_control() const			{ return static_cast<size_type>(header().transport_scrambling_control);		}
		void				transport_scrambling_control(size_type value)	{ header().transport_scrambling_control = static_cast<dword_type>(value);	}

		size_type			adaptation_field_control() const				{ return static_cast<size_type>(header().adaptation_field_control);			}
		void				adaptation_field_control(size_type value)		{ header().adaptation_field_control = static_cast<dword_type>(value);		}

		size_type			continuity_counter() const						{ return static_cast<size_type>(header().continuity_counter);				}
		void				continuity_counter(size_type value)				{ header().continuity_counter = static_cast<dword_type>(value);				}
	/// @}

	/// \name Adaptation Field Header Attributes
	/// @{
	public:
		size_type			adaptation_field_length() const				{ return static_cast<size_type>(adaptation_field_header().adaptation_field_length);			}
		void				adaptation_field_length(size_type value)	{ adaptation_field_header().adaptation_field_length = static_cast<byte_type>(value);		}
	
		size_type			discontinuity_indicator() const				{ return static_cast<size_type>(adaptation_field_header().discontinuity_indicator);			}
		void				discontinuity_indicator(size_type value)	{ adaptation_field_header().discontinuity_indicator = static_cast<byte_type>(value);		}
	
		size_type			random_access_indicator() const				{ return static_cast<size_type>(adaptation_field_header().random_access_indicator);			}
		void				random_access_indicator(size_type value)	{ adaptation_field_header().random_access_indicator = static_cast<byte_type>(value);		}

		size_type			elementary_stream_priority_indicator() const			{ return static_cast<size_type>(adaptation_field_header().elementary_stream_priority_indicator);	}
		void				elementary_stream_priority_indicator(size_type value)	{ adaptation_field_header().elementary_stream_priority_indicator = static_cast<byte_type>(value);	}
		
		size_type			pcr_flag() const									{ return static_cast<size_type>(adaptation_field_header().pcr_flag);			}
		void				pcr_flag(size_type value)							{ adaptation_field_header().pcr_flag = static_cast<byte_type>(value);			}
		
		size_type			opcr_flag() const									{ return static_cast<size_type>(adaptation_field_header().opcr_flag);			}
		void				opcr_flag(size_type value)							{ adaptation_field_header().opcr_flag = static_cast<byte_type>(value);			}
	
		size_type			splicing_point_flag() const							{ return static_cast<size_type>(adaptation_field_header().splicing_point_flag);					}
		void				splicing_point_flag(size_type value)				{ adaptation_field_header().splicing_point_flag = static_cast<byte_type>(value);				}

		size_type			transport_private_data_flag() const					{ return static_cast<size_type>(adaptation_field_header().transport_private_data_flag);			}
		void				transport_private_data_flag(size_type value)		{ adaptation_field_header().transport_private_data_flag = static_cast<byte_type>(value);		}
	
		size_type			adaptation_field_extension_flag() const				{ return static_cast<size_type>(adaptation_field_header().adaptation_field_extension_flag);		}
		void				adaptation_field_extension_flag(size_type value)	{ adaptation_field_header().adaptation_field_extension_flag = static_cast<byte_type>(value);	}
	
		bool_type			exists_pcr() const							{ return (1 == pcr_flag());							}
		bool_type			exists_opcr() const							{ return (1 == opcr_flag());						}
		bool_type			exists_splicing() const						{ return (1 == splicing_point_flag());				}
		bool_type			exists_private_data() const					{ return (1 == transport_private_data_flag());		}
		bool_type			exists_adaptation_field_extension() const	{ return (1 == adaptation_field_extension_flag());	}
	/// @}

	/// \name Adaptation Field PCR Attributes
	/// @{
	public:
		qword_type			pcr() const							{ return (pcr_base() * 300 + pcr_extension());		}
		qword_type			opcr() const						{ return (opcr_base() * 300 + opcr_extension());	}

		qword_type			pcr_base() const					{ return ((static_cast<qword_type>(pcr_body().pcr_base) << 1) | pcr_body().base1);										}
		void				pcr_base(qword_type value)			{ pcr_body().pcr_base = static_cast<dword_type>(value >> 1); pcr_body().base1 = static_cast<word_type>(value & 0x1);	}

		size_type			pcr_extension() const				{ return static_cast<size_type>(pcr_body().pcr_extension);		}
		void				pcr_extension(size_type value)		{ pcr_body().pcr_extension = static_cast<word_type>(value);		}

		qword_type			opcr_base() const					{ return ((static_cast<qword_type>(opcr_body().opcr_base) << 1) | opcr_body().base1);									}
		void				opcr_base(qword_type value)			{ opcr_body().opcr_base = static_cast<dword_type>(value >> 1); opcr_body().base1 = static_cast<word_type>(value & 0x1);	}

		size_type			opcr_extension() const				{ return static_cast<size_type>(opcr_body().opcr_extension);	}
		void				opcr_extension(size_type value)		{ opcr_body().opcr_extension = static_cast<word_type>(value);	}
	/// @}

	/// \name Adaptation Field Other Attributes
	/// @{
	public:
		size_type			splice_countdown() const			{ return splicing_data()[0];							}
		void				splice_countdown(size_type value)	{ splicing_data()[0] = static_cast<byte_type>(value);	}

		size_type			private_data_length() const			{ return transport_private_data()[0];							}
		void				private_data_length(size_type value){ transport_private_data()[0] = static_cast<byte_type>(value);	}

	//	size_type			adaptation_field_extension_length() const			{ return adaptation_field_extension().adaptation_field_extension_length;														}
		//void				adaptation_field_extension_length(size_type value)	{ adaptation_field_extension().adaptation_field_extension_length = static_cast<byte_type>(adaptation_field_extension_length);	}

		size_type			ltw_flag() const			{ return adaptation_field_extension().ltw_flag;								}
		void				ltw_flag(size_type value)	{ adaptation_field_extension().ltw_flag = static_cast<byte_type>(value);	}

		size_type			piecewise_rate_flag() const				{ return adaptation_field_extension().piecewise_rate_flag;							}
		void				piecewise_rate_flag(size_type value)	{ adaptation_field_extension().piecewise_rate_flag = static_cast<byte_type>(value);	}

		size_type			seamless_splice_flag() const			{ return adaptation_field_extension().seamless_splice_flag;							}
		void				seamless_splice_flag(size_type value)	{ adaptation_field_extension().seamless_splice_flag = static_cast<byte_type>(value);	}

		bool_type			exists_ltw() const							{ return (1 == ltw_flag());							}
		bool_type			exists_piecewise_rate() const				{ return (1 == piecewise_rate_flag());				}
		bool_type			exists_seamless_splice() const				{ return (1 == seamless_splice_flag());				}

		size_type			ltw_valid_flag() const			{ return ltw().ltw_valid_flag;							}
		void				ltw_valid_flag(size_type value)	{ ltw().ltw_valid_flag = static_cast<word_type>(value);	}

		size_type			ltw_offset() const				{ return ltw().ltw_offset;							}
		void				ltw_offset(size_type value)		{ ltw().ltw_offset = static_cast<word_type>(value);	}

	/// @}

	/// \name Packet Attributes
	/// @{
	public:
		/// return \true if packet is pat(program association table)
		bool_type			is_pat() const		{ return (pid() == en_pid_pat);		}
		/// the packet is set to be pat
		void				set_pat()			{ pid(en_pid_pat);					}

		/// return \true if packet is cat(conditional access table)
		bool_type			is_cat() const		{ return (pid() == en_pid_cat);		}
		/// the packet is set to be cat
		void				set_cat()			{ pid(en_pid_cat);					}

		/// return \true if packet is tsdt(transport stream description table)
		bool_type			is_tsdt() const		{ return (pid() == en_pid_tsdt);	}
		/// the packet is set to be tsdt
		void				set_tsdt()			{ pid(en_pid_tsdt);					}

		/// return \true if packet is null
		bool_type			is_null() const		{ return (pid() == en_pid_null);	}
		/// the packet is set to be null
		void				set_null()			{ pid(en_pid_null);					}

		/// return \true if packet is scrambled
		bool_type			is_scrambling() const				{ return (transport_scrambling_control() != 0);	}

		/// return \true if packet exists error
		bool_type			exists_error() const				{ return (transport_error_indicator() != 0);	}

		/// return \true if the packet exists adaptation field
		bool_type			exists_adaptation_field() const		{ return (adaptation_field_control() == 0x2 || adaptation_field_control() == 0x3);	}
	
		/// return \true if the adaptation field is valid
		bool_type			adaptation_field_is_valid() const	{ return !((adaptation_field_control() == 0x2 && adaptation_field_length() != 183) ||	(adaptation_field_control() == 0x3 && adaptation_field_length() > 182));	}
	/// @}

	/// \name Other Attributes
	/// @{
	public:
		bool_type			is_valid() const	{ return (sync_byte() == en_sync_byte);				}
	/// @}

	/// \name Static Methods
	/// @{
	public:
		static size_type	pid(const_pointer data)	{ return (((data[1] & 0x1F) << 8) | data[2]);	}
	/// @}

	/// \name Protected Helpers
	/// @{
	protected:
		/// reverse byte stream and \note size must be divided by 1, 2, 4
		void				reverse(pointer data, size_type size);
	/// @}
	
};

/* ///////////////////////////////////////////////////////////////////////
 * Implemention 
 */
inline void transport_packet::reverse(pointer data, size_type size)
{
	// \note size must be divided by 1, 2, 4
	EXTL_ASSERT(size == 1 || size == 2 || (size % 4) == 0);

	pointer pb = data;
	pointer pe = pb + size - 1;
	while(pb < pe)
	{
		std_swap(*pb, *pe);
		++pb;
		--pe;
	}
}

inline void transport_packet::attach(const_pointer p)
{
	if (NULL != p)
	{
		// attach packet data
		buffer().attach(p, en_packet_size);

		// adjust header data
		reverse(data(), en_header_size);

		// adjust pcr data
		if (exists_pcr())
		{
			reverse(pcr_data(), 4);
			reverse(pcr_data() + 4, 2);
		}

		// adjust opcr data
		if (exists_opcr())
		{
			reverse(opcr_data(), 4);
			reverse(opcr_data() + 4, 2);
		}

		// adjust ltw data
		if (exists_ltw())
		{
			reverse(ltw_data(), en_ltw_size);
		}
	}
}
inline transport_packet::
const_pointer transport_packet::detach()
{
	if (NULL != data())
	{
		// adjust ltw data
		if (exists_ltw())
		{
			reverse(ltw_data(), en_ltw_size);
		}

		// resume opcr data
		if (exists_opcr())
		{
			reverse(opcr_data() + 4, 2);
			reverse(opcr_data(), 4);
		}

		// resume pcr data
		if (exists_pcr())
		{
			reverse(pcr_data() + 4, 2);
			reverse(pcr_data(), 4);
		}

		// resume header data
		reverse(data(), en_header_size);

		return data();
	}
	else return NULL;
}
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media namespace 
 */
EXTL_MEDIA_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_TRANSPORT_PACKET_H */
/* //////////////////////////////////////////////////////////////////// */
