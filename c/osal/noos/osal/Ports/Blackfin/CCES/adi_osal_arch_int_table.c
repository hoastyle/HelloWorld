/* $Revision: 10952 $
 * $Date: 2011-07-29 00:26:10 +0800 (Fri, 29 Jul 2011) $
******************************************************************************
Copyright (c), 2009-2011 - Analog Devices Inc. All Rights Reserved.
This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
and its licensors.
******************************************************************************

Title:      OSAL interrupt table definition on Blackfin

Description:
           This is the definition of the OSAL interrupt table in which pointers
           to handlers written in C for the given interrupt are stored.

*****************************************************************************/

/*=============  I N C L U D E S   =============*/
#include "adi_osal.h"

/*=============  D E F I N E S  =============*/


#pragma file_attr(  "libGroup=adi_osal.h")
#pragma file_attr(  "libName=libosal")


/*!
    @internal
    @var _adi_osal_gHandlerTable
	This is the OSAL dispatch table. It is an array of function pointers, of the
	type corresponding to OSAL's plain C interrupt handlers (i.e. the high-level
	handlers). The table needs to be large enough for any index that we can get
	back from adi_rtl_register_dispatched_handler(). 
    @endinternal
 */

#define OSAL_HANDLER_TABLE_SIZE 64u

uint32_t _adi_osal_gHandlerTableSize = OSAL_HANDLER_TABLE_SIZE;

/*!
    @internal
    @var _adi_osal_gHandlerTableSize
	The size of the OSAL dispatch table. The size needs to be large enough for 
    any index that we can get back from adi_rtl_register_dispatched_handler(). 
    At the moment this table needs to be mapped into a section which is in
    a CPLB locked area.
    @endinternal
 */

#pragma section("L1_scratchpad", DOUBLEANY, NO_INIT)
ADI_OSAL_HANDLER_PTR _adi_osal_gHandlerTable[OSAL_HANDLER_TABLE_SIZE];


/*
**
** EOF: 
**
*/

