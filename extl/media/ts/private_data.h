/* ///////////////////////////////////////////////////////////////////////
 * File:		private_data.h		
 *
 * Created:		09.02.06
 * Updated:		09.03.04
 *
 * Brief:		the private_data class
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_MEDIA_TS_PRIVATE_DATA_H
#define EXTL_MEDIA_TS_PRIVATE_DATA_H

/*!\file private_data.h
 * \brief the private_data class
 */
#ifndef __cplusplus
#	error private_data.h need be supported by c++.
#endif

/* ///////////////////////////////////////////////////////////////////////
 * Includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_BEGIN_WHOLE_NAMESPACE

/*!brief the private_data class
 *
 * \ingroup extl_group_media
 *
 * \code
 *	transport_private_data_length		:	8	;
 *	for (i = 0; i < transport_private_data_length; ++i)
		private_data_byte				: 8		;
 * \endcode
 *
 * \param Ada the adaptation field type
 */
template<typename_param_k Ada>
class private_data
{
	/// \name Public Types
	/// @{
	public:
		typedef Ada								adaptation_type;
		typedef private_data					class_type;
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

	/// \name Private Accessors
	/// @{
	private:
		adaptation_type&		adaptation()		{ return static_cast<adaptation_type&>(*this);				}
		adaptation_type const&	adaptation() const	{ return static_cast<adaptation_type const&>(*this);		}
	/// @}

	/// \name Public Accessors
	/// @{
	public:
		pointer				data()							{ EXTL_ASSERT(exists()); return (adaptation().packet().data() + offset());	}
		const_pointer		data() const					{ EXTL_ASSERT(exists()); return (adaptation().packet().data() + offset());	}
	/// @}

	/// \name Attributes
	/// @{
	public:
		/// the private data length
		size_type			data_length() const		{ EXTL_ASSERT(exists()); return adaptation().packet().data()[offset() - 1];			}

		/// the self size
		size_type			size() const			{ return (1 + data_length());			}

		/// return the offset at the packet
		size_type			offset() const		{ return (adaptation().splicing().offset() + adaptation().splicing().size() + (adaptation().splicing().exists()? 1 : 0));	}

		///  return \true if exists private_data
		bool_type			exists() const		{ return (1 == adaptation().header().private_data_flag());	}
	/// @}
};

/* ///////////////////////////////////////////////////////////////////////
 * ::extl::media::ts namespace 
 */
EXTL_MEDIA_TS_END_WHOLE_NAMESPACE

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_MEDIA_TS_PRIVATE_DATA_H */
/* //////////////////////////////////////////////////////////////////// */
