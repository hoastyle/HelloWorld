#include <stdlib.h>     /* for NULL definition */
#include <limits.h>
#include "adi_osal.h"
#include "adi_osal_arch.h"
#include "adi_osal_arch_internal.h"
#include "osal_common.h"

/*=============  D A T A  =============*/
/*!
    @internal
    @var _adi_osal_gnCriticalRegionState
         Holds the state of the interrupt mask as of the first call to
         adi_osal_EnterCriticalRegion
    @endinternal
*/
uint32_t _adi_osal_gnCriticalRegionState = 0u;

/*!
    @internal
    @var _adi_osal_gnCriticalRegionNestingCnt
         This variable is a counter which is incremented when
         adi_osal_EnterCriticalRegion() is called and decremented when
         adi_osal_ExitCriticalRegion is called.
         Initially we are not in a critical region.
    @endinternal
*/

int32_t _adi_osal_gnCriticalRegionNestingCnt = 0;

/*=============  C O D E  =============*/

void _adi_osal_stdWrapper (void)
{
    /* Get the interrupt number */
    uint32_t nIntNum = __get_IPSR();
    
     /* Call the higher level callback */
    _adi_osal_gHandlerTable[nIntNum].pfOSALHandler(ADI_NVIC_IRQ_SID(nIntNum),  _adi_osal_gHandlerTable[nIntNum].pOSALArg);
   
    return;
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

    /* accessing the global count variable needs to be protected from thread
     * switches so cli() is called at the very beginning. The value of the
     * interrupts state is only saved the first time. */

    uint32_t istate = _adi_osal_InterruptsDisable();

    if (0==_adi_osal_gnCriticalRegionNestingCnt)
    {
        /* only lock the interrupts the first time the function is called */
        _adi_osal_gnCriticalRegionState = istate;
    }

    _adi_osal_gnCriticalRegionNestingCnt++;


    return;
}

/*!
  ****************************************************************************
    @brief Re-enables interrupts and restores the interrupt status.

    This function decrements the count of nested critical regions. Use it as a
    closing bracket to adi_osal_EnterCriticalRegion. OSAL ignores additional
    calls to adi_osal_ExitCriticalRegion while interrupts are enabled.

    @see adi_osal_EnterCriticalRegion
*****************************************************************************/

void adi_osal_ExitCriticalRegion( void )
{
    _adi_osal_gnCriticalRegionNestingCnt--;

    /* when the last nesting level is reached, reenable the interrupts */
    if (_adi_osal_gnCriticalRegionNestingCnt <= 0)
    {
        _adi_osal_gnCriticalRegionNestingCnt = 0;
        _adi_osal_InterruptsEnable(_adi_osal_gnCriticalRegionState);
    }

    return;
}



