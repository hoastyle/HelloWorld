/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#include <FreeRTOSConfig.h>

	RSEG    CODE:CODE(2)
	thumb

	EXTERN pxCurrentTCB
	EXTERN vTaskSwitchContext

	PUBLIC xPortPendSVHandler
	PUBLIC vPortSVCHandler
	PUBLIC vPortStartFirstTask



/*-----------------------------------------------------------*/

//什么情况进入pendSVHandler?
//pendSV的作用应该是在合适的时候（中断处理完之后），进行上下文切换。
xPortPendSVHandler:
	mrs r0, psp
	isb
	//获取TCB结构体的地址
	ldr	r3, =pxCurrentTCB			/* Get the location of the current TCB. */
	//获取TCB的首成员stack头
	ldr	r2, [r3]

	//r0 - r3, xPSR, r12, lr, pc由Cortex-m3保存
	stmdb r0!, {r4-r11}				/* Save the remaining registers. */
	str r0, [r2]					/* Save the new top of stack into the first member of the TCB. */
	//以上是保存当前任务的上下文

	//为什么要保存r3和r14? 因为要调用函数
	//r14中保存特殊退出代码，那r3呢？
	//r3中保存pxCurrentTCB的指针
	stmdb sp!, {r3, r14}
	//优先级分界线，是否使用freertos api
	//优先级低于configMAX_SYSCALL_INTERRUPT_PRIORITY的将无法打断中断上下文的切换
	mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
	msr basepri, r0
	dsb
	isb
	bl vTaskSwitchContext
	mov r0, #0
	//enable isr
	msr basepri, r0
	ldmia sp!, {r3, r14}

	ldr r1, [r3]
	ldr r0, [r1]					/* The first item in pxCurrentTCB is the task top of stack. */
	ldmia r0!, {r4-r11}				/* Pop the registers. */
	msr psp, r0
	isb
	bx r14


/*-----------------------------------------------------------*/

//用来做任务切换
//可以通过检测LR得知调用者使用的是主堆栈1还是用户堆栈0
//获知堆栈后，使用堆栈地址+24获取pc地址，通过pc地址从SVC指令中获取SVC号，参考Cortex-m3权威指南
vPortSVCHandler:
	/* Get the location of the current TCB. */
	ldr	r3, =pxCurrentTCB
	ldr r1, [r3]
	ldr r0, [r1]
	/* Pop the core registers. */
	ldmia r0!, {r4-r11}
	msr psp, r0
	isb
	mov r0, #0
	//enable interrupt
	msr	basepri, r0
	//设置r14最后四位为1101，也就是进入线程模式，从psp作出栈操作，返回Thumb模式
	orr r14, r14, #13
	bx r14
	//执行bx r14后，任务获得cpu执行权，调度器正式开始工作

/*-----------------------------------------------------------*/

vPortStartFirstTask
	/* Use the NVIC offset register to locate the stack. */
	//向量偏移寄存器
	ldr r0, =0xE000ED08
	ldr r0, [r0]
	ldr r0, [r0]
	/* Set the msp back to the start of the stack. */
	//设置msp为向量表首地址的栈顶
	msr msp, r0
	/* Call SVC to start the first task, ensuring interrupts are enabled. */
	//开中断
	cpsie i
	//开异常，关闭时只有NMI可以响应
	cpsie f
	dsb
	isb
	svc 0

	END
