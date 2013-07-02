/* ///////////////////////////////////////////////////////////////////////
 * File:		adaptation_field_extension_header.h		
 *
 * Created:		09.03.08
 * Updated:		09.03.08
 *
 * Brief:		the adaptation_field_extension_header class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_ADAPTATION_FIELD_EXTENSION_HEADER_H
#define EXTL_MEDIA_TS_ADAPTATION_FIELD_EXTENSION_HEADER_H

/*!\file adaptation_field_extension_header.h
 * \brief the adaptation_field_extension_header class 
 */
#ifndef __cplusplus
#	error adaptation_field_extension_header.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief adaptation field extension_header
 *
 * \ingroup extl_group_media
 *
 * \code
 *	// adaptation field extension_header
 *  struct adaptation_field_extension_header
	{
		adaptation_field_extension_header_length	: 8		;
		ltw_flag							: 1		;
		piecewise_rate_flag					: 1		;
		seamless_splice_flag				: 1		;
		reserved							: 5		;

		[ltw]
		[piecewise_rate]
		[seamless_splice]

		for (i = 0; i < N; ++i)
			reserved						: 8		;
		}
	};
 * \endcode
 *
 * \param AdaExt the adaptation field extension type
 */
template<typename_param_k AdaExt>
class adaptation_field_extension_header
{
	/// \name Public Types
	/// @{
	public:
		typedef AdaExt									extension_type;
		typedef adaptation_field_extension_header		class_type;
		typedef e_byte_t								byte_type;
		typedef e_uint16_t								word_type;
		typedef e_uint32_t								dword_type;
		typedef e_uint64_t								qword_type;
		typedef byte_type*								pointer;
		typedef byte_type const*						const_pointer;
		typedef e_size_t								size_type;
		typedef size_type								index_type;
		typedef e_bool_t								bool_type;
	/// @}

	/// \name Member Type
	/// @{
	private:
		// program_clock_reference
		// base + base1 + reseved + pcr_extension
		// |=> 33bit <=|      6            9
		struct											members_type
		{
			byte_type extension_length						;

			// \note defined in reverse order by byte_type
			byte_type reserved								: 5		;
			byte_type seamless_splice_flag					: 1		;
			byte_type piecewise_rate_flag					: 1		;
			byte_type ltw_flag								: 1		;
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
		extension_type&			extension()			{ return static_cast<extension_type&>(*this);			}
		extension_type const&	extension() const	{ return static_cast<extension_type const&>(*this);		}

		members_type&			members()			{ return *reinterpret_cast<members_type*>(data());			}
		members_type const&		members() const		{ return *reinterpret_cast<members_type const*>(data());	}
	/// @}

	/// \name Public Accessors
	/// @{
	public:
		pointer				data()									{ return (extension().data());		}
		const_pointer		data() const							{ return (extension().data());		}
	
		size_type			extension_length() const				{ return static_cast<size_type>(members().extension_length);		}
		void				extension_length(size_type value)		{ members().extension_length = static_cast<byte_type>(value);		}

		size_type			ltw_flag() const						{ return static_cast<size_type>(members().ltw_flag);				}
		void				ltw_flag(size_type value)				{ members().ltw_flag = static_cast<byte_type>(value);				}

		size_type			piecewise_rate_flag() const				{ return static_cast<size_type>(members().piecewise_rate_flag);		}
		void				piecewise_rate_flag(size_type value)	{ members().piecewise_rate_flag = static_cast<byte_type>(value);	}

		size_type			seamless_splice_flag() const			{ return static_cast<size_type>(members().seamless_splice_flag);	}
		void				seamless_splice_flag(size_type value)	{ members().seamless_splice_flag = static_cast<byte_type>(value);	}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the adaptation_field_header size
		size_type			size() const		{ return en_header_size;			}

		/// return the offset at the packet
		size_type			offset() const		{ return extension().offset();		}
	/// @}

};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_ADAPTATION_FIELD_EXTENSION_HEADER_H */
/* //////////////////////////////////////////////////////////////////// */
