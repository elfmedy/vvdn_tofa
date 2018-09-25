/* usbpump_classkit_session.h	Fri Apr 12 2013 14:14:44 chwon */

/*

Module:  usbpump_classkit_session.h

Function:
	Definition of USBPUMP_CLASSKIT_SESSION

Version:
	V3.11c	Fri Apr 12 2013 14:14:44 chwon	Edit level 3

Copyright notice:
	This file copyright (C) 2008, 2013 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.

	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation

Author:
	ChaeHee Won, MCCI Corporation	April 2008

Revision history:
   1.97k  Thu Apr 24 2008 12:36:23 chwon
	Module created.

   1.97k  Thu Jul 17 2008 11:48:09  chwon
	4301: remove USBPUMP_CLASSKIT_SESSION_FLAG_CLASS_REGISTER
	4303: use USBPUMP_SESSION_HANDLE instead of USBPUMP_CLASSKIT_SESSION *

   3.11c  Fri Apr 12 2013 14:14:44  chwon
	17015: add pClientObject in the session.

*/

#ifndef _USBPUMP_CLASSKIT_SESSION_H_	/* prevent multiple includes */
#define _USBPUMP_CLASSKIT_SESSION_H_

#ifndef _USBPUMP_CLASSKIT_TYPES_H_
# include "usbpump_classkit_types.h"
#endif

#ifndef _USBPUMP_CLASSKIT_API_H_
# include "usbpump_classkit_api.h"
#endif

/****************************************************************************\
|
|	Definition of USBPUMP_CLASSKIT_SESSION
|
\****************************************************************************/

struct __TMS_STRUCTNAME(USBPUMP_CLASSKIT_SESSION)
	{
	__TMS_USBPUMP_OBJECT_HEADER *			pObjectHeader;

	__TMS_UINT32					Flag;

	__TMS_USBPUMP_CLASSKIT_SESSION *		pNext;
	__TMS_USBPUMP_CLASSKIT_SESSION *		pLast;

	__TMS_USBPUMP_CLASSKIT_NOTIFICATION_FN *	pNotificationFn;
	__TMS_VOID *					pClientHandle;
	__TMS_USBPUMP_OBJECT_HEADER *			pClientObject;
	};

#define	__TMS_USBPUMP_CLASSKIT_SESSION_FLAG_FREE		0x00u
#define	__TMS_USBPUMP_CLASSKIT_SESSION_FLAG_CLASS_OPEN		0xC1u
#define	__TMS_USBPUMP_CLASSKIT_SESSION_FLAG_FUNCTION		0xF1u


/****************************************************************************\
|
|	API functions
|
\****************************************************************************/

__TMS_BEGIN_DECLS

__TMS_VOID *
UsbPumpClassKitI_ValidateSessionHandle(
	__TMS_USBPUMP_SESSION_HANDLE	SessionHandle,
	__TMS_BOOL			fClassHandle
	);

__TMS_END_DECLS


/****************************************************************************\
|
|	Uncloaked names
|
\****************************************************************************/

/**** uncloaked names generated by uncloak-defs.sh ****/
#if !__TMS_CLOAKED_NAMES_ONLY
# define USBPUMP_CLASSKIT_SESSION_FLAG_FREE	\
   __TMS_USBPUMP_CLASSKIT_SESSION_FLAG_FREE
# define USBPUMP_CLASSKIT_SESSION_FLAG_CLASS_OPEN	\
   __TMS_USBPUMP_CLASSKIT_SESSION_FLAG_CLASS_OPEN
# define USBPUMP_CLASSKIT_SESSION_FLAG_FUNCTION	\
   __TMS_USBPUMP_CLASSKIT_SESSION_FLAG_FUNCTION
#endif /* !__TMS_CLOAKED_NAMES_ONLY */

/**** end of usbpump_classkit_session.h ****/
#endif /* _USBPUMP_CLASSKIT_SESSION_H_ */