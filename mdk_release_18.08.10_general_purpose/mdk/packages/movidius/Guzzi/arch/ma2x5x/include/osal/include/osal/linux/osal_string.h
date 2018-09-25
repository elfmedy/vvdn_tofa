/* =============================================================================
* Copyright (c) 2013-2014 MM Solutions AD
* All rights reserved. Property of MM Solutions AD.
*
* This source code may not be used against the terms and conditions stipulated
* in the licensing agreement under which it has been supplied, or without the
* written permission of MM Solutions. Rights to use, copy, modify, and
* distribute or disclose this source code and its documentation are granted only
* through signed licensing agreement, provided that this copyright notice
* appears in all copies, modifications, and distributions and subject to the
* following conditions:
* THIS SOURCE CODE AND ACCOMPANYING DOCUMENTATION, IS PROVIDED AS IS, WITHOUT
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED. MM SOLUTIONS SPECIFICALLY DISCLAIMS
* ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN
* NO EVENT SHALL MM SOLUTIONS BE LIABLE TO ANY PARTY FOR ANY CLAIM, DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
* PROFITS, OR OTHER LIABILITY, ARISING OUT OF THE USE OF OR IN CONNECTION WITH
* THIS SOURCE CODE AND ITS DOCUMENTATION.
* =========================================================================== */
/**
* @file osal_string.h
*
* @author ( MM Solutions AD )
*
*/
/* -----------------------------------------------------------------------------
*!
*! Revision History
*! ===================================
*! 05-Nov-2013 : Author ( MM Solutions AD )
*! Created
* =========================================================================== */

#ifndef  __OSAL_STRING_LINUX_H__
#define  __OSAL_STRING_LINUX_H__

#include <string.h>
#include <ctype.h>

#define osal_memcpy                     memcpy
#define osal_memmove                    memmove
#define osal_memset                     memset
#define osal_memcmp                     memcmp

#define osal_strcpy                     strcpy
#define osal_strncpy                    strncpy
#define osal_strncmp                    strncmp
#define osal_strncasecmp                strncasecmp
#define osal_strspn                     strspn
#define osal_strpbrk                    strpbrk
#define osal_strlen                     strlen
#define osal_isspace                    isspace
#define osal_strtok                     strtok
#define osal_strcat                     strcat
#define osal_strchr                     strchr
#define osal_strcmp                     strcmp

#endif /* __OSAL_STRING_LINUX_H__ */

