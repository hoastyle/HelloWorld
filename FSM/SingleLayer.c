/* Single Layer FSM
 * Be implemented based on table.
 * Major elements:
 * - switch table
 * - curState
 * - state machine handler to receive events
 */

#include "SingleLayer.h"
#include "Layer.h"

typedef struct FSM_s {
	STATE_TABLE_t *FsmTable;
	STATE_t curState;
} FSM_t;

void FSM_Regist(FSM_t * pFsm, STATE_TABLE_t * pStateTable)
{
	pFsm->FsmTable = pStateTable;
	return;
}

/*状态迁移*/
void FSM_MoveState(FSM_t * pFsm, STATE_t state)
{
	printf("From %s to %s\n", s_state[pFsm->curState], s_state[state]);
	pFsm->curState = state;
	return;
}

/*客户端提供的状态处理函数*/
void state1Event1Fun(void *pFsm)
{
	FSM_MoveState((FSM_t *) pFsm, STATE2);
	return;
}

void state1Event3Fun(void *pFsm)
{
	FSM_MoveState((FSM_t *) pFsm, STATE3);
	return;
}

void state2Event2Fun(void *pFsm)
{
	FSM_MoveState((FSM_t *) pFsm, STATE3);
	return;
}

/*状态1的动作表*/
ACT_TABLE_t state1ActTable[] = {
	{EVENT1, state1Event1Fun}
	,
	{EVENT3, state1Event3Fun}
	,
};

/*状态2的动作表*/
ACT_TABLE_t state2ActTable[] = {
	{EVENT2, state2Event2Fun}
	,
};

/*状态表*/
// state table 嵌套 event table，每个state对应多个event
STATE_TABLE_t FsmTable[] = {
	{STATE1, sizeof(state1ActTable)/sizeof(ACT_TABLE_t), state1ActTable}
	,
	{STATE2, sizeof(state2ActTable)/sizeof(ACT_TABLE_t), state2ActTable}
	,
};

ACT_TABLE_t *FSM_getActTable(FSM_t * pFsm)
{
	int i;
	STATE_t curState = pFsm->curState;
	int max_state_num = FSM_getNumStateTable(pFsm->FsmTable);
	ACT_TABLE_t *ActTable;

	for (i = 0; i < max_state_num; i++) {
		if (pFsm->FsmTable[i].state == curState)
			break;
	}

	ActTable = pFsm->FsmTable[i].StateTable;
	return ActTable;
}

/*事件处理*/
void FSM_EventHandle(FSM_t * pFsm, EVENT_t event)
{
	int max_act_num;
	int i;
	ACT_TABLE_t *pActTable = NULL;
	ActFun eventActFun = NULL;

	/*获取当前状态动作表 */
	pActTable = FSM_getActTable(pFsm);
	if (pActTable == NULL)
		printf("error\n");
	max_act_num = FSM_getNumActTable(pFsm->FsmTable);

	/*获取当前动作函数 */
	for (i = 0; i < max_act_num; i++) {
		if (event == pActTable[i].event) {
			eventActFun = pActTable[i].eventActFun;
			if (eventActFun == NULL)
				printf("event pointer is null, error\n");
			break;
		}
	}
	/*动作执行 */
	if (eventActFun) {
		eventActFun(pFsm);
	}
}

int main(int argc, char *argv[])
{
	FSM_t fsm;
	/*状态表注册 */
	FSM_Regist(&fsm, FsmTable);
	FSM_MoveState(&fsm, STATE1);
	while (1) {
		FSM_EventHandle(&fsm, EVENT1);
		FSM_EventHandle(&fsm, EVENT2);
		FSM_MoveState(&fsm, STATE1);
		FSM_EventHandle(&fsm, EVENT3);
		FSM_MoveState(&fsm, STATE1);
		printf("One more round.\n");
		sleep(1);
	}
	return 0;
}
