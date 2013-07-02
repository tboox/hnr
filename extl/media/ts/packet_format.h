/* ///////////////////////////////////////////////////////////////////////
 * File:		packet_format.h		
 *
 * Created:		09.03.06
 * Updated:		09.03.06
 *
 * Brief:		the packet format - TS packet for iso/iec 13818-1 2000-12-01
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_TRANSPORT_PACKET_FORMAT_H
#define EXTL_MEDIA_TS_TRANSPORT_PACKET_FORMAT_H

/*!brief packet_format
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
				}

				// adaptation field extension
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
 */

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_TRANSPORT_PACKET_FORMAT_H */
/* //////////////////////////////////////////////////////////////////// */
