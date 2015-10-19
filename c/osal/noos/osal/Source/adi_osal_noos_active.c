/* $Revision: 18300 $
 * $Date: 2013-03-19 18:57:28 +0800 (Tue, 19 Mar 2013) $ 
******************************************************************************
Copyright (c), 2008-2013 - Analog Devices Inc. All Rights Reserved.
This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
and its licensors.
*****************************************************************************/

/*!
    @file adi_osal_noos_critical.c

    Operating System Abstraction Layer - OSAL for no-OS - Critical section
    functions

    This file contains the critical section & scheduler locking APIs for the
    no-OS implementation of OSAL

    @note 
         Since no scheduler is present in the no-OS implementation,
         SchedulerLock and SchedulerUnlock are equivalent to NOPs.
*/

/*=============  I N C L U D E S   =============*/


#if defined (__ADSP21000__)
#include <sysreg.h>                                                   
#endif

#include "adi_osal.h"

#if defined (__ECC__)
#pragma file_attr(  "libGroup=adi_osal.h")
#pragma file_attr(  "libName=libosal")
#pragma file_attr(  "prefersMem=internal")
#pragma file_attr(  "prefersMemNum=30")
#endif

/*=============  D A T A  =============*/

/*
   variable     : _adi_osal_gbSchedulerActive
   A boolean flag to indicate whether scheduler is active.
*/
const bool _adi_osal_gbSchedulerActive = false;

/*=============  C O D E  =============*/

/*!
  ****************************************************************************
    @brief Determines whether the scheduler is running.

    @return true  - If the scheduler is running,
    @return false - If the scheduler is not running

    @note In the no-OS version of OSAL the function returns always false as
          there is no scheduler active.

*****************************************************************************/

bool adi_osal_IsSchedulerActive(void)
{
    return(false);
}


/*
**
** EOF:
**
*/
