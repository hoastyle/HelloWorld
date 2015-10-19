/* $Revision: 26149 $
 * $Date: 2014-06-26 18:15:49 +0800 (Thu, 26 Jun 2014) $
******************************************************************************
Copyright (c), 2009-2013 - Analog Devices Inc. All Rights Reserved.
This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
and its licensors.
******************************************************************************

Title:      OSAL for no-OS

Description:
              Operating System Abstraction Layer for the environment where
              there is no OS(Operating System) running.
*****************************************************************************/
#ifdef _MISRA_RULES
/*Rule 14.7 indicates that a function shall have a single exit point */
#pragma diag(suppress:misra_rule_14_7:"Allowing several point of exit (mostly for handling parameter error checking) increases the code readability and therefore maintainability")
/* Rule-5.1 indicates that all identifiers shall not rely on more than 31 characters of significance */
#pragma diag(suppress:misra_rule_5_1:"prefixes added in front of identifiers quickly increases their size. In order to keep the code self explanatory, and since ADI tools are the main targeted tools, this restriction is not really a necessity")
#endif

#include <stdlib.h>                                                             /* for NULL definition */

#include "adi_osal.h"
#include "osal_common.h"
#include "osal_noos.h"

/*=============  D A T A  =============*/

#ifdef OSAL_DEBUG
/*!
    @internal
    @var _adi_osal_gnSchedulerLockCnt
         Indicates if the code is within a Scheduler lock section. It is only
         used in debug mode to check if Unlock is called with Lock being called
         first. This needs to be a counter to allow for nesting
         Initially the scheduler is not locked
    @endinternal
*/
uint32_t _adi_osal_gnSchedulerLockCnt = 0u ;

#endif /* OSAL_DEBUG */


/*!
  *****************************************************************************
  Function: adi_osal_Init
   @brief Initializes OSAL

   @details Initialization function for OSAL. This function will be called 
            from system startup.  

   @return  ADI_OSAL_SUCCESS - Initialization is done successfully.
   @return  ADI_OSAL_FAILED  - OSAL has already been initialized
   @return ADI_OSAL_MEM_ALLOC_FAILED - Error initializing dynamic memory heap

*****************************************************************************/

ADI_OSAL_STATUS adi_osal_Init( void )
{

/* static variable    : snOsalInitializationState 
 * Flag to record if OSAL has already been initialized
 */

    uint32_t*  pHeapMemory = NULL;   /* ptr to the memory to use for the heap */
    uint32_t   nHeapMemorySize = 0u; /* size of memory pointed by pHeapMemory */

#ifdef OSAL_DEBUG
    static uint32_t snOsalInitializationState = 0u ;

    /* Check if already initialized. If the parameters are the same then the
     * call succeeds. Otherwise the call fails. The priority inheritance
     * setting is not recorded so we cannot check it
     */
    if (OSAL_INITIALIZED == snOsalInitializationState) 
    {
       return (ADI_OSAL_SUCCESS);
    }
#endif

    if (ADI_OSAL_SUCCESS != _adi_osal_HeapInstall(pHeapMemory,nHeapMemorySize))
    {
        return (ADI_OSAL_MEM_ALLOC_FAILED);
    }
        

#ifdef OSAL_DEBUG
   snOsalInitializationState = OSAL_INITIALIZED;
#endif

    return( ADI_OSAL_SUCCESS);
}



/*
**
** EOF: 
**
*/

