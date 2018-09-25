/* uhilalign.h	Mon Aug 20 2012 14:58:11 chwon */

/*

Module:  uhilalign.h

Function:
	Home for the common alignment structures and constants.

Version:
	V3.11a	Mon Aug 20 2012 14:58:11 chwon	Edit level 7

Copyright notice:
	This file copyright (C) 2000-2002, 2005, 2012 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.

	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation

Author:
	Terry Moore, MCCI Corporation	December 2000

Revision history:
   1.60w  Tue Dec 26 2000 18:36:31  tmm
	Module created.

   1.79a  6/5/2002  tmm
	Header file bloat reduction.  Merge in DIAB changes.

   1.87a Thu Dec 11 2003 12:20:00 maw
	Add cloaking.

   1.91g  2005-07-21  tmm
	Bring in ALIGN_SIZE() from utask.h

   1.93a  Fri Oct 07 2005 09:39:28  chwon
	Pull out union definition inside of struct

   3.11a  Mon Aug 20 2012 14:58:11  chwon
	15828: Fixed aligned pointer calculation for 64-bits compiler.

*/

#ifndef _UHILALIGN_H_		/* prevent multiple includes */
#define _UHILALIGN_H_

#ifndef _BASEHILENV_H_
# include "basehilenv.h"
#endif

/*
|| The DataPump manages a memory pool.  For portability, we need to be able
|| to make sure that our memory pool returns aligned objects.  This structure
|| allows us to determine the required alignment automaticallyh.
*/
__TMS_TYPE_DEF_STRUCT(test_alignment_struct);
__TMS_TYPE_DEF_UNION(test_alignment_union);

union __TMS_UNIONNAME(test_alignment_union)
	{
	char	j1;
	short	j2;
	int	j3;
	long	j4;
	float	j5;
	double	j6;
	};

struct __TMS_STRUCTNAME(test_alignment_struct)
	{
	/* this gets us on an odd address */
	char				c1;

	/* then this will have to be aligned */
	__TMS_test_alignment_union	aligned;
	};

/* __TMS_USBPUMP_ALIGNMENT is the required alignment constant */
#define __TMS_USBPUMP_ALIGNMENT				\
	__TMS_OFFSET(					\
		__TMS_test_alignment_struct,		\
		aligned					\
		)

/*
|| __TMS_USBPUMP_ALIGN_POINTER returns a pointer that is rounded up,
|| if necessary, to be properly aligned.
*/
#define	__TMS_USBPUMP_MAKE_ALIGN_POINTER(p, t, a)	\
	((t)(((__TMS_ADDRBITS)(p) + (a) - 1) & (1 + ~((__TMS_ADDRBITS)(a)))))

/*
|| __TMS_USBPUMP_ALIGN_POINTER returns a pointer that is rounded up,
|| if necessary, to be properly aligned.
*/
#define	__TMS_USBPUMP_ALIGN_POINTER(p, t)	\
	__TMS_USBPUMP_MAKE_ALIGN_POINTER(p, t, __TMS_USBPUMP_ALIGNMENT)

/*
|| __TMS_USBPUMP_MAKE_ALIGN_SIZE returns a aligned size.
*/
#define	__TMS_USBPUMP_MAKE_ALIGN_SIZE(s, a)	\
	(((__TMS_BYTES)(s) + (a) - 1) & (1 + ~((__TMS_BYTES)(a))))

#define	__TMS_USBPUMP_ALIGN_SIZE(s)		\
	__TMS_USBPUMP_MAKE_ALIGN_SIZE(s, __TMS_USBPUMP_ALIGNMENT)


/* following macross are defined for backward compatibility */
#define __TMS_ALIGNMENT			__TMS_USBPUMP_ALIGNMENT
#define	__TMS_ALIGN_POINTER(p, t)	__TMS_USBPUMP_ALIGN_POINTER(p, t)
#define	__TMS_ALIGN_SIZE(s)		__TMS_USBPUMP_ALIGN_SIZE(s)


/****************************************************************************\
|
|	Uncloaked names
|
\****************************************************************************/

/**** uncloaked names generated by uncloak-defs.sh ****/
#if !__TMS_CLOAKED_NAMES_ONLY
# define USBPUMP_ALIGNMENT	\
   __TMS_USBPUMP_ALIGNMENT
# define USBPUMP_MAKE_ALIGN_POINTER(p, t, a)	\
   __TMS_USBPUMP_MAKE_ALIGN_POINTER(p, t, a)
# define USBPUMP_ALIGN_POINTER(p, t)	\
   __TMS_USBPUMP_ALIGN_POINTER(p, t)
# define USBPUMP_MAKE_ALIGN_SIZE(s, a)	\
   __TMS_USBPUMP_MAKE_ALIGN_SIZE(s, a)
# define USBPUMP_ALIGN_SIZE(s)	\
   __TMS_USBPUMP_ALIGN_SIZE(s)
# define ALIGNMENT	\
   __TMS_ALIGNMENT
# define ALIGN_POINTER(p, t)	\
   __TMS_ALIGN_POINTER(p, t)
# define ALIGN_SIZE(s)	\
   __TMS_ALIGN_SIZE(s)
#endif /* !__TMS_CLOAKED_NAMES_ONLY */

/**** end of uhilalign.h ****/
#endif /* _UHILALIGN_H_ */
