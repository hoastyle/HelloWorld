/* $Revision: 18300 $
 * $Date: 2013-03-19 18:57:28 +0800 (Tue, 19 Mar 2013) $
******************************************************************************
Copyright (c), 2009-2013 - Analog Devices Inc. All Rights Reserved.
This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
and its licensors.
******************************************************************************

Title:      OSAL for no OS Platform specific functions for SHARC

*****************************************************************************/

/*=============  I N C L U D E S   =============*/


/* Rule 17.4(Req): Array indexing shall be the only allowed form of pointer arithmetic. */
#pragma diag(suppress:misra_rule_17_4:"This source needs to use pointer indexing")

#include "adi_osal.h"
#include "osal_common.h"
#include "adi_osal_arch.h"
#include "adi_osal_arch_internal.h"

/*=============  D E F I N E S  =============*/


#pragma file_attr(  "libGroup=adi_osal.h")
#pragma file_attr(  "libName=libosal")
#pragma file_attr(  "prefersMem=internal")
#pragma file_attr(  "prefersMemNum=30")



/*=============  C O D E  =============*/

/*
 * This is an environment-specific interrupt wrapper.
 * I.e. this is the wrapper that is used for interrupts that
 * may call operating system APIs, and hence must support
 * rescheduling. In the no-RTOS OSAL it has essentially the
 * same implementation as the plain wrapper, since there is
 * no rescheduling in this environment. We let the compiler
 * generate the appropriate code for saving and restoring registers,
 * and for setting up the C runtime environment.
 */
EX_DISPATCHED_HANDLER_NESTED(_adi_osal_stdWrapper, iid,  index, arg)
{
	(_adi_osal_gHandlerTable[index])(iid, (void*) arg);
}

/*!
  ****************************************************************************
    @brief Disables interrupts to enable atomic execution of a critical region
    of code.

    Note that critical regions may be nested. A count is maintained to ensure a
    matching number of calls to adi_ExitCriticalRegion are made before
    restoring interrupts. Each critical region is also (implicitly) a scheduler
    lock.

    @see adi_osal_ExitCriticalRegion
*****************************************************************************/

void adi_osal_EnterCriticalRegion( void )
{

    adi_rtl_disable_interrupts();

    return;
}

/*!
  ****************************************************************************
    @brief Re-enables interrupts and restores the interrupt status.

    This function decrements the count of nested critical regions. Use it as a
    closing bracket to adi_osal_EnterCriticalRegion. 
    The Enter/ExitCriticalRegion sequence must be nestable

    @see adi_osal_EnterCriticalRegion
*****************************************************************************/

void adi_osal_ExitCriticalRegion( void )
{
    adi_rtl_reenable_interrupts();
}



/*
**
** EOF: 
**
*/

