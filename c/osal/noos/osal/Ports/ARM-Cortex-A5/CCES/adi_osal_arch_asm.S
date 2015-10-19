/* $Revision: 23339 $
 * $Date: 2013-10-01 11:45:32 -0400 (Tue, 01 Oct 2013) $
******************************************************************************
Copyright (c), 2009-2013 - Analog Devices Inc. All Rights Reserved.
This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
and its licensors.
******************************************************************************

Title:      OSAL functions specific to ARM which are not specific to an 
            OSAL environment (valid for no-OS)

Description:


              Operating System Abstraction Layer for the environment where
              there is no OS(Operating System) running.

*****************************************************************************/

#include "runtime/int/interrupt.h"
#include "adi_osal_noos_arch.h"

.text
.code 32

.global _adi_osal_stdWrapper
.global _adi_osal_plainWrapper
.extern _adi_osal_gHandlerTable
.type _adi_osal_stdWrapper, %function
.type _adi_osal_plainWrapper, %function

/*
 * This is an environment-specific interrupt wrapper.
 * I.e. this is the wrapper that is used for interrupts that
 * may call operating system APIs, and hence must support
 * rescheduling. In the no-RTOS OSAL it has essentially the
 * same implementation as the plain wrapper, since there is
 * no rescheduling in this environment. We only save and restore
 * registers that are not saved by the low level dispatcher.
 *
 * Assumes that R0-R4 registers are already saved by low level dispatacher.
 *
 * TODO: Save and restore floating point registers.
 */

_adi_osal_stdWrapper:
_adi_osal_plainWrapper:
    STMFD SP!, {R5-R12, LR}
    
    MSR     CPSR_c, #(ADI_RTL_ARM_MODE_SVC )                            		/* Enable the interrupts back */
    
    LDR     R7,  =_adi_osal_gHandlerTable                                       /* Point to the OSAL handler table */
                                                                                
    LDR     R5, =__ADI_OSAL_HANDLER_ENTRY_SIZE                                  /* Get to the exception entry */                                                                            
    MUL     R6,  R5, R1                                                        
    ADD     R5,  R6, R7
    MOV     R1,  R2                                                             /* Make the pArg as second argument to the handler */

    LDR     R7,  [R5]                                                           /* Load the address of the handler */
    BLX     R7                                                                  /* Call the handler */
    
    LDMFD   SP!, {R5-R12, LR};                                                  /* Pop the saved register contents and jump back to the interrupted location */
    BX      LR
