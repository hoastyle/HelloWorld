/* $Revision: 26543 $
 * $Date: 2014-07-30 22:54:06 +0800 (Wed, 30 Jul 2014) $
******************************************************************************
Copyright (c), 2009-2013 - Analog Devices Inc. All Rights Reserved.
This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
and its licensors.
******************************************************************************

Title:      OSAL for no OS Platform specific functions for ARM Cortex A series

*****************************************************************************/

/*=============  I N C L U D E S   =============*/

#include "adi_osal.h"
#include "osal_common.h"
#include "adi_osal_arch.h"
#include "adi_osal_arch_internal.h"

/*=============  D E F I N E S  =============*/


/*=============  C O D E  =============*/

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
    
    return;
}



/*
**
** EOF: 
**
*/

