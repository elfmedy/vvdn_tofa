/* ether.h	Wed Nov 23 2016 03:45:17 sjpark */

/*

Module:  ether.h

Function:
	Common definitions for Ethernet handling.

Version:
	V3.19a	Wed Nov 23 2016 03:45:17 sjpark	Edit level 6

Copyright notice:
	This file copyright (C) 2000, 2007, 2009, 2011, 2016 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.
	
	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation.
 
Author:
	Terry Moore, MCCI Corporation	May 2000

Revision history:
   1.60d  Wed May  3 2000 23:08:50  tmm
	Module created.

   1.60n  9/23/2000  tmm
	Move USBMACADDR in here.

   1.97g  Sun May 06 2007 11:54:39  tmm
	Add cloaking.  Add USBCDC_ETHFRAME_PHYSICAL_MTU as the
	basic 802.3 MTU size (1514 bytes).

   2.01a  Sun Nov 08 2009 23:30:55 maw
   	9335: Optimize MAC comparison by reordering byte compare

   3.01f  Mon Dec 12 2011 23:28:15  ssyang
   	14578: Added USBCDC_ETHFRAME_MIN_PAYLOAD_SIZE constant

   3.19a  Wed Nov 23 2016 03:45:17  sjpark   	
   	Added VLAN workaround code.
   	
*/

#ifndef _ETHER_H_		/* prevent multiple includes */
#define _ETHER_H_

/****************************************************************************\
|
|	Utility things for handling Ethernet operations
|
\****************************************************************************/

/*
|| The USBETHER_MACADDRESS structure is simply an encapsulation of a
|| 6-byte ethernet MAC address.  It has the following assumed bit order:
||
||	[0].7 .. [0].0; [1].7 .. [1].0, ... [5].7 .. [5].0
||	   a7 ..  a0;     a15 .. a8, ...      a47 .. a40
||
|| Corrsponding to the following bit order:
||
||	<pfx><da0><da1><da2> .. <da47> <sa0> .. <sa47> etc.
*/
#define	__TMS_MACADDRESS_LENGTH	6	/* number of bytes in a MAC addr */

__TMS_TYPE_DEF_STRUCT(USBETHER_MACADDRESS);
struct __TMS_STRUCTNAME(USBETHER_MACADDRESS)
	{
	__TMS_UINT8	addr[__TMS_MACADDRESS_LENGTH];	/* address bytes */
	};

__TMS_TYPE_DEF_STRUCT(ETHERNET_HEADER);

struct __TMS_STRUCTNAME(ETHERNET_HEADER)
	{
	__TMS_UINT8	DestAddr[__TMS_MACADDRESS_LENGTH];
	__TMS_UINT8	SrcAddr[__TMS_MACADDRESS_LENGTH];
	__TMS_UINT8	Type[2];
	};

#define	__TMS_USBCDC_ETHADDR_EQ(pA1, pA2) \
	((pA1)[2] == (pA2)[2] && \
	 (pA1)[1] == (pA2)[1] && \
	 (pA1)[0] == (pA2)[0] && \
	 (pA1)[5] == (pA2)[5] && \
	 (pA1)[4] == (pA2)[4] && \
	 (pA1)[3] == (pA2)[3])

/* calculate a 16-bit hash code */
#define	__TMS_USBCDC_ETHADDR_HASHFRAC(pA1) \
	 ((((((( \
	    (((((((pA1)[0]) << 1) + (pA1)[1]) << 1) + (pA1)[2]) << 1) + \
	          (pA1)[3]) << 1) + (pA1)[4]) << 1) + (pA1)[5]) * 40503) & 0xFFFF)
	
#define	__TMS_USBCDC_ETHADDR_HASH(pA1, nBuckets) \
	(((unsigned) __TMS_USBCDC_ETHADDR_HASHFRAC(pA1) * (nBuckets)) >> 16)

/* is it a multicast address? */
#define	__TMS_USBCDC_ETHADDR_IS_MULTICAST(pAddr)	(((pAddr)[0] & 1) != 0)
#define	__TMS_USBCDC_ETHADDR_IS_UNICAST(pAddr)		(!__TMS_USBCDC_ETHADDR_IS_MULTICAST(pAddr))

#ifndef __TMS_VLAN_WORKAROUND
#define __TMS_VLAN_WORKAROUND 0
#endif

#if __TMS_VLAN_WORKAROUND
#define __TMS_VLAN_LENGTH 4
#else
#define __TMS_VLAN_LENGTH 0
#endif

/* 
|| define the number of bytes needed for an ethernet header -- 6 bytes
|| for dest addr, followed by 6 bytes for source addr, followed by 2 bytes
|| of frame type. if VLAN workaround is used, add that too. Note that changing this length 
|| is not a standard MCCI feature, and should only be done if there are no legacy code 
|| considerations
*/
#define	__TMS_USBCDC_ETHFRAME_HDR_SIZE	(__TMS_MACADDRESS_LENGTH + __TMS_MACADDRESS_LENGTH + 2 + __TMS_VLAN_LENGTH)

/* this must always be the basic MTU size for Ethernet from 802.3: 1514 bytes */
#define	__TMS_USBCDC_ETHFRAME_PHYSICAL_MTU	(1500 + __TMS_USBCDC_ETHFRAME_HDR_SIZE)

#define __TMS_USBCDC_ETHFRAME_MIN_PAYLOAD_SIZE	46u

/****************************************************************************\
|
|	Uncloaked names
|
\****************************************************************************/

/**** uncloaked names generated by uncloak-defs.sh ****/
#if !__TMS_CLOAKED_NAMES_ONLY
# define MACADDRESS_LENGTH	__TMS_MACADDRESS_LENGTH
# define USBCDC_ETHADDR_EQ(pA1, pA2)	__TMS_USBCDC_ETHADDR_EQ(pA1, pA2)
# define USBCDC_ETHADDR_HASHFRAC(pA1)	__TMS_USBCDC_ETHADDR_HASHFRAC(pA1)
# define USBCDC_ETHADDR_HASH(pA1, nBuckets)	__TMS_USBCDC_ETHADDR_HASH(pA1, nBuckets)
# define USBCDC_ETHADDR_IS_MULTICAST(pAddr)	__TMS_USBCDC_ETHADDR_IS_MULTICAST(pAddr)
# define USBCDC_ETHADDR_IS_UNICAST(pAddr)	__TMS_USBCDC_ETHADDR_IS_UNICAST(pAddr)
# define USBCDC_ETHFRAME_HDR_SIZE	__TMS_USBCDC_ETHFRAME_HDR_SIZE
# define USBCDC_ETHFRAME_PHYSICAL_MTU	__TMS_USBCDC_ETHFRAME_PHYSICAL_MTU
# define USBCDC_ETHFRAME_MIN_PAYLOAD_SIZE	__TMS_USBCDC_ETHFRAME_MIN_PAYLOAD_SIZE
#endif /* !__TMS_CLOAKED_NAMES_ONLY */


/**** end of ether.h ****/
#endif /* _ETHER_H_ */
