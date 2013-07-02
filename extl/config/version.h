/* ///////////////////////////////////////////////////////////////////////
 * File:		version.h		
 *
 * Created:		08.07.28				
 * Updated:		08.07.28
 *
 * Brief: The version definition of Extl
 *
 * [<Home>]
 * Copyright (c) 2008-2020, Waruqi All rights reserved.
 * //////////////////////////////////////////////////////////////////// */

#ifndef EXTL_CONFIG_VERSION_H
#define EXTL_CONFIG_VERSION_H

/*!\file version.h
 * \brief The version definition of Extl
 */

/*!\def EXTL_VERSION_MAJOR
 * \brief The major version number of Extl
 *
 * A dramatic change has occurred in the library
 */

/*!\def EXTL_VERSION_MINOR
 * \brief The minor version number of Extl
 *
 * A significant change has occurred in the library
 * e.g. Some significant bugs have been fixed.
 */

/*!\def EXTL_VERSION_RELEASE
 * \brief The release version number of Extl
 *
 * The library has been released because some slightly bugs have been fixed in the library
 */

/*!\def EXTL_VERSION_REVISION
 * \brief The revision version number of Extl
 *
 * Some codes have been modified in the libraries before being released
 */
#define EXTL_VERSION_MAJOR			1			
#define EXTL_VERSION_MINOR			0		
#define EXTL_VERSION_RELEASE		1			
#define EXTL_VERSION_REVISION		1033	

/*!\def EXTL_CURRENT_VERSION
 * \brief The current composite version number of Extl
 *
 * - bits 24-31: the major version
 * - bits 16-23: the minor version
 * - bits 8-15: the release version
 * - bits 0-7: the beta number; if not a beta, it is 0xFF
 */
#define EXTL_VERSION_1_0_1		0x010001FF	/*!< version 1.0.1 */

#define EXTL_CURRENT_VERSION	EXTL_VERSION_1_0_0

/* //////////////////////////////////////////////////////////////////// */
#endif /* EXTL_CONFIG_VERSION_H */
/* //////////////////////////////////////////////////////////////////// */
