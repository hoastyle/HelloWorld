/* $Revision: 31348 $
 * $Date: 2015-06-09 22:38:16 +0800 (Tue, 09 Jun 2015) $
******************************************************************************
Copyright (c), 2009-2011 - Analog Devices Inc. All Rights Reserved.
This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
and its licensors.
******************************************************************************

Title:      OSAL interrupt table definition on SHARC

Description:
           This is the definition of the OSAL interrupt table in which pointers
           to handlers written in C for the given interrupt are stored.

*****************************************************************************/

/*=============  I N C L U D E S   =============*/
#include "adi_osal.h"
#include "adi_osal_arch_internal.h"


/*=============  D E F I N E S  =============*/


#pragma file_attr(  "libGroup=adi_osal.h")
#pragma file_attr(  "libName=libosal")
#pragma file_attr(  "prefersMem=internal")
#pragma file_attr(  "prefersMemNum=30")

/* defines the size of the OSAL interrupt handler table,
 * used for the definition of the handler array.
 */

#if defined(__ADI_HAS_SEC__)
#define OSAL_HANDLER_TABLE_SIZE ((uint32_t) (___ADI_NUM_CIDS + 256))
#else
#define OSAL_HANDLER_TABLE_SIZE ((uint32_t) (___ADI_NUM_CIDS))
#endif

/*!
    @internal
    @var _adi_osal_gHandlerTableSize
	The size of the OSAL dispatch table. The size needs to be large enough for 
    any index that we can get back from adi_rtl_register_dispatched_handler(). 
    At the moment this table needs to be mapped into a section which is in
    a CPLB locked area.
    @endinternal
 */

uint32_t _adi_osal_gHandlerTableSize = OSAL_HANDLER_TABLE_SIZE;

/*!
    @internal
    @var _adi_osal_gHandlerTable
    This is the OSAL dispatch table. It is an array of function pointers, of
    the type corresponding to OSAL's plain C interrupt handlers (i.e. the
    high-level handlers). The table needs to be large enough for any index
    that we can get back from register_dispatched_handler().  
    @endinternal
 */

ADI_OSAL_HANDLER_PTR _adi_osal_gHandlerTable[OSAL_HANDLER_TABLE_SIZE];

/*
**
** EOF: 
**
*/

