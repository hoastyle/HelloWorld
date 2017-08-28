#include <stdio.h>
#include "../include/kbhit.h"

typedef unsigned char uint8_t;

/* FSM */
typedef struct {
	QHsm super;

	double operand1;
	uint8_t operator;
} Calc;

typedef unsigned char QState;
typedef QState (*QStateHandler)(Calc *self, QEvt *e);

enum calc_signals {
	C_SIG = Q_USER_SIG,
	// 清除屏幕
	CE_SIG,
	DIGIT_0_SIG,
	DIGIT_1_9_SIG,
	POINT_SIG,
	OPER_SIG,
	EQUALS_SIG,
	OFF_SIG
};

QStateHandler calc_initial;
QStateHandler calc_on;
QStateHandler calc_error;
QStateHandler calc_ready;
QStateHandler calc_begin;
QStateHandler calc_result;
QStateHandler calc_negated1;
QStateHandler calc_operand1;
QStateHandler calc_zero1;
QStateHandler calc_int1;
QStateHandler calc_frac1;
QStateHandler calc_opentered;
QStateHandler calc_negated2;
QStateHandler calc_operand2;
QStateHandler calc_zero2;
QStateHandler calc_int2;
QStateHandler calc_frac2;

void main()
{
    calc_ctor(); /* explicitly instantiate the calculator object */

    printf("Calculator example, QEP version: 111\n"
           "Press '0' .. '9'     to enter a digit\n"
           "Press '.'            to enter the decimal point\n"
           "Press '+'            to add\n"
           "Press '-'            to subtract or negate a number\n"
           "Press '*'            to multiply\n"
           "Press '/'            to divide\n"
           "Press '=' or <Enter> to get the result\n"
           "Press 'c' or 'C'     to Cancel\n"
           "Press 'e' or 'E'     to Cancel Entry\n"
           "Press <Esc>          to quit.\n\n",
           );

    QHSM_INIT(the_calc, (QEvt *)0); /* trigger initial transition */

    for (;;) { /* event loop */
        CalcEvt e; /* Calculator event */

        switch (kbhid()) {
            case 'c': /* intentionally fall through */
            case 'C': {
                ((QEvt *)&e)->sig = C_SIG;
                break;
            }
            case 'e': /* intentionally fall through */
            case 'E': {
                ((QEvt *)&e)->sig = CE_SIG;
                break;
            }
            case '0': {
                ((QEvt *)&e)->sig = DIGIT_0_SIG;
                break;
            }
            case '1': /* intentionally fall through */
            case '2': /* intentionally fall through */
            case '3': /* intentionally fall through */
            case '4': /* intentionally fall through */
            case '5': /* intentionally fall through */
            case '6': /* intentionally fall through */
            case '7': /* intentionally fall through */
            case '8': /* intentionally fall through */
            case '9': {
                ((QEvt *)&e)->sig = DIGIT_1_9_SIG;
                break;
            }
            case '.': {
                ((QEvt *)&e)->sig = POINT_SIG;
                break;
            }
            case '+': /* intentionally fall through */
            case '-': /* intentionally fall through */
            case '*': /* intentionally fall through */
            case '/': {
                ((QEvt *)&e)->sig = OPER_SIG;
                break;
            }
            case '=': /* intentionally fall through */
            case '\r': { /* Enter key */
                ((QEvt *)&e)->sig = EQUALS_SIG;
                break;
            }
            case '\33': { /* ESC key */
                ((QEvt *)&e)->sig = OFF_SIG;
                break;
            }
            default: {
                ((QEvt *)&e)->sig = 0; /* invalid event */
                break;
            }
        }

        if (((QEvt *)&e)->sig != 0) {  /* valid event generated? */
            QHSM_DISPATCH(the_calc, (QEvt *)&e); /* dispatch event */
        }
    }
    return 0;
}
