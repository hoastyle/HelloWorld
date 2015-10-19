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


// Tesla M0 has numerous instances of multiple interrupts sharing the
// same physical vector (because the M0 has only 32 perifheral vectors),
// so we need a secondary dispatcher, defined here.

// individual shared interrupt tables, named by the IVT offset,
// and sized by the number of interrupts being shared on that vector.
siVectorInfo  si0Vectors[5] = {NULL};
siVectorInfo  si3Vectors[3] = {NULL};
siVectorInfo  si5Vectors[7] = {NULL};
siVectorInfo  si6Vectors[3] = {NULL};
siVectorInfo  si7Vectors[2] = {NULL};
siVectorInfo  si8Vectors[3] = {NULL};
siVectorInfo si10Vectors[2] = {NULL};
siVectorInfo si11Vectors[2] = {NULL};
siVectorInfo si12Vectors[7] = {NULL};
siVectorInfo si15Vectors[9] = {NULL};
siVectorInfo si16Vectors[3] = {NULL};
siVectorInfo si17Vectors[2] = {NULL};
siVectorInfo si18Vectors[2] = {NULL};
siVectorInfo si19Vectors[3] = {NULL};
siVectorInfo si22Vectors[2] = {NULL};
siVectorInfo si25Vectors[2] = {NULL};
siVectorInfo si28Vectors[3] = {NULL};

/* shared handler table, spanning both shared and dedicated IVT entries */
/* NOTE: this table EXCLUDES the exception space                        */
SHARED_INTERRUPT_TABLE_TYPE _adi_osal_gSharedHandlerTable[] = {
    {REG_C0_SISTAT0, si0Vectors},   // shared interrupt group,
    {NULL, NULL},                   // dedicated interrupt,
    {NULL, NULL},                   // dedicated interrupt,
    {REG_C0_SISTAT3,  si3Vectors},  // shared interrupt group...
    {NULL, NULL},
    {REG_C0_SISTAT5,  si5Vectors},
    {REG_C0_SISTAT6,  si6Vectors},
    {REG_C0_SISTAT7,  si7Vectors},
    {REG_C0_SISTAT8,  si8Vectors},
    {NULL, NULL},
    {REG_C0_SISTAT10, si10Vectors},
    {REG_C0_SISTAT11, si11Vectors},
    {REG_C0_SISTAT12, si12Vectors},
    {NULL, NULL},
    {NULL, NULL},
    {REG_C0_SISTAT15, si15Vectors},
    {REG_C0_SISTAT16, si16Vectors},
    {REG_C0_SISTAT17, si17Vectors},
    {REG_C0_SISTAT18, si18Vectors},
    {REG_C0_SISTAT19, si19Vectors},
    {NULL, NULL},
    {NULL, NULL},
    {REG_C0_SISTAT22, si22Vectors},
    {NULL, NULL},
    {NULL, NULL},
    {REG_C0_SISTAT25, si25Vectors},
    {NULL, NULL},
    {NULL, NULL},
    {REG_C0_SISTAT28, si28Vectors},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
};


/*=============  C O D E  =============*/


/* standard interrupt dispatcher */
void _adi_osal_stdWrapper (void)
{
    /* Get the interrupt number */
    uint32_t nIntNum = __get_IPSR();

     /* Call the higher level callback */
    _adi_osal_gHandlerTable[nIntNum].pfOSALHandler(ADI_NVIC_IRQ_SID(nIntNum),  _adi_osal_gHandlerTable[nIntNum].pOSALArg);

    return;
}


/* Tesla M0 shared interrupts land here for subdispatching */
void _adi_osal_sharedWrapper (void)
{
    // get the active interrupt index from the system's Interrupt Program Status Register (IPSR)
    register uint32_t ivtIndex = __get_IPSR() -  16;
    register uint32_t siIndex;

    // read the shared interrupt's SISTAT register to see which shared interrupt actually fired
    register uint32_t siStat = *(uint32_t*)_adi_osal_gSharedHandlerTable[ivtIndex].siStatReg;

    // translate SISTAT bitfield to an index we can use
    switch (siStat) {
        case 0x0001: siIndex = 0; break;
        case 0x0002: siIndex = 1; break;
        case 0x0004: siIndex = 2; break;
        case 0x0008: siIndex = 3; break;
        case 0x0010: siIndex = 4; break;
        case 0x0020: siIndex = 5; break;
        case 0x0040: siIndex = 6; break;
        case 0x0080: siIndex = 7; break;
        case 0x0100: siIndex = 8; break;
#ifdef ADI_DEBUG
		default: while(1);  // trap on unexpected status
#endif
    }

    // get the vector
    register siVectorInfo *pSharedInterrupt = &_adi_osal_gSharedHandlerTable[ivtIndex].siVectors[siIndex];

    // dispatch the subvector
    if (pSharedInterrupt)
        pSharedInterrupt->pfOSALHandler(pSharedInterrupt->iid, pSharedInterrupt->pOSALArg);
#ifdef ADI_DEBUG
	else
		while(1);  // trap on missing vector
#endif

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



