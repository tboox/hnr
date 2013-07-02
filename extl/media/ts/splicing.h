/* ///////////////////////////////////////////////////////////////////////
 * File:		splicing.h		
 *
 * Created:		09.02.06
 * Updated:		09.03.04
 *
 * Brief:		the splicing class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_SPLICING_H
#define EXTL_MEDIA_TS_SPLICING_H

/*!\file splicing.h
 * \brief the splicing class
 */
#ifndef __cplusplus
#	error splicing.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief the splicing class
 *
 * \ingroup extl_group_media
 *
 * \code
 *	splice_countdown	: 8;
 * \endcode
 *
 * \param Ada the adaptation field type
 */
template<typename_param_k Ada>
class splicing
{
	/// \name Public Types
	/// @{
	public:
		typedef Ada								adaptation_type;
		typedef splicing						class_type;
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

	/// \name Constants
	/// @{
	public:
		enum {	en_splicing_size	=	1	};
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
		pointer				data()							{ return (adaptation().packet().data() + offset());	}
		const_pointer		data() const					{ return (adaptation().packet().data() + offset());	}

		size_type			countdown() const				{ return data()[0];									}
		void				countdown(size_type value)		{ data()[0] = static_cast<byte_type>(value);		}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the splicing size
		size_type			size() const		{ return en_splicing_size;			}

		/// return the offset at the packet
		size_type			offset() const		{ return (adaptation().opcr().offset() + (adaptation().opcr().exists()? adaptation().opcr().size() : 0));	}

		///  return \true if exists splicing
		bool_type			exists() const		{ return (1 == adaptation().header().splicing_point_flag());	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_SPLICING_H */
/* //////////////////////////////////////////////////////////////////// */
