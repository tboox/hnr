/* ///////////////////////////////////////////////////////////////////////
 * File:		adaptation_field_extension.h		
 *
 * Created:		09.03.08
 * Updated:		09.03.08
 *
 * Brief:		the adaptation_field_extension class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_ADAPTATION_FIELD_EXTENSION_H
#define EXTL_MEDIA_TS_ADAPTATION_FIELD_EXTENSION_H

/*!\file adaptation_field_extension.h
 * \brief the adaptation_field_extension class 
 */
#ifndef __cplusplus
#	error adaptation_field_extension.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"
#include "adaptation_field_extension_header.h"
/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief adaptation field extension
 *
 * \ingroup extl_group_media
 *
 * \code
 *	// adaptation field extension
 *  struct adaptation_field_extension
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
	};
 * \endcode
 *
 * \param Ada the adaptation field type
 */
template<typename_param_k Ada>
class adaptation_field_extension
	: private adaptation_field_extension_header<adaptation_field_extension<Ada> >
{
	/// \name Public Types
	/// @{
	public:
		typedef Ada												adaptation_type;
		typedef adaptation_field_extension						class_type;
		typedef e_byte_t										byte_type;
		typedef e_uint16_t										word_type;
		typedef e_uint32_t										dword_type;
		typedef e_uint64_t										qword_type;
		typedef byte_type*										pointer;
		typedef byte_type const*								const_pointer;
		typedef e_size_t										size_type;
		typedef size_type										index_type;
		typedef e_bool_t										bool_type;
		typedef adaptation_field_extension_header<class_type>	header_type;
		friend													header_type;
	/// @}

	/// \name Member Type
	/// @{
	private:
		/// ltw_type
		struct													ltw_type
		{
			// \note defined in reverse order by word_type
			word_type ltw_offset						: 15	;
			word_type ltw_valid_flag					: 1		;
		};

		/// seamless_splice_type
		struct													seamless_splice_type
		{
			/// \note defined in reverse order by qword_type
			/// dts_next_au = dts_next_au_32_30 . dts_next_au_29_15 . dts_next_au_14_00
			qword_type reserved										: 24	;

			qword_type marker_bit1									: 1		;
			qword_type dts_next_au_14_00							: 15	;	//!< [14..0]	
			qword_type marker_bit2									: 1		;
			qword_type dts_next_au_29_15							: 15	;	//!< [29..15]
			qword_type marker_bit3									: 1		;
			qword_type dts_next_au_32_30							: 3		;	//!< [32..30]
			qword_type splice_type									: 4		;
		};
	/// @}

	/// \name Private Accessors
	/// @{
	private:
		adaptation_type&		adaptation()		{ return static_cast<adaptation_type&>(*this);				}
		adaptation_type const&	adaptation() const	{ return static_cast<adaptation_type const&>(*this);		}
	/// @}

	/// \name Public Accessors
	/// @{
	public:
		pointer				data()										{ return (adaptation().packet().data() + offset());		}
		const_pointer		data() const								{ return (adaptation().packet().data() + offset());		}

		header_type&		header()									{ return static_cast<header_type&>(*this);				}
		header_type const&	header() const								{ return static_cast<header_type const&>(*this);		}

		pointer				ltw_data()									{ return (data() + header().size());					}
		const_pointer		ltw_data() const							{ return (data() + header().size());					}

		ltw_type&			ltw()										{ return *reinterpret_cast<ltw_type*>(ltw_data());			}
		ltw_type const&		ltw() const									{ return *reinterpret_cast<ltw_type const*>(ltw_data());	}

		pointer				piecewise_rate_data()						{ return (ltw_data() + (exists_ltw()? 2 : 0));	}
		const_pointer		piecewise_rate_data() const					{ return (ltw_data() + (exists_ltw()? 2 : 0));	}

		size_type			piecewise_rate() const						{ return static_cast<size_type>(((dword_type*)(piecewise_rate_data()))[0] >> 2);			}
		void				piecewise_rate(size_type value)				{ reinterpret_cast<dword_type*>(piecewise_rate_data())[0] = dword_type(value << 2);		}
	
		pointer				seamless_splice_data()						{ return (piecewise_rate_data() + (exists_piecewise_rate()? 3 : 0));	}
		const_pointer		seamless_splice_data() const				{ return (piecewise_rate_data() + (exists_piecewise_rate()? 3 : 0));	}

		seamless_splice_type&		seamless_splice()					{ return *reinterpret_cast<seamless_splice_type*>(seamless_splice_data());			}
		seamless_splice_type const&	seamless_splice() const				{ return *reinterpret_cast<seamless_splice_type const*>(seamless_splice_data());	}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the adaptation field size
		size_type			size() const					{ return header().extension_length();							}

		/// return the offset at the packet
		size_type			offset() const					{ return (adaptation().private_data().offset() + adaptation().private_data().size());	}

		/// return \true if exists adaptation field 
		bool_type			exists() const					{ return (adaptation().header().extension_flag() == 1);	}

		/// return \true if the adaptation field is valid
		bool_type			is_valid() const				{ return (data() != NULL) && (size() < adaptation().size());	}

		///  return \true if exists adaptation field extension
		bool_type			exists_extension() const		{ return (1 == header().extension_flag());			}

		///  return \true if exists ltw
		bool_type			exists_ltw() const				{ return (1 == header().ltw_flag());				}

		///  return \true if exists piecewise_rate
		bool_type			exists_piecewise_rate() const	{ return (1 == header().piecewise_rate_flag());		}

		///  return \true if exists seamless_splice
		bool_type			exists_seamless_splice() const	{ return (1 == header().seamless_splice_flag());	}
	/// @}

	/// \name Attach & Detach
	/// @{
	public:
		/// decodes 
		void				decode()			
		{ 
			if (exists()) 
			{
				// decode ltw
				adaptation().packet().buffer().reverse(header().size(), 2); 
			}
		}
		/// encodes
		void				encode()		
		{ 
			if (exists()) 
			{
				// encode ltw
				adaptation().packet().buffer().reverse(header().size(), 2); 
			}
		}
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_ADAPTATION_FIELD_EXTENSION_H */
/* //////////////////////////////////////////////////////////////////// */
