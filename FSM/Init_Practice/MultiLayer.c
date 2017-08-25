/* Multi Layer FSM */

#include "MultiLayer.h"
#include "Layer.h"

#define MAX_FSM_NUM 2
#define MAX_FSM_STACK 2

enum {
	FSM_L1 = 1,
	FSM_L2,
};

typedef struct FSM_REGIST_s {
	int FsmId;
	STATE_TABLE_t *FsmTable;
	int NumStateTable;
} FSM_REGIST_t;

typedef struct FSM_STACK_s {
	STATE_t state;
	STATE_TABLE_t *pFsmTable;
	int NumStateTable;
} FSM_STACK_t;

typedef struct FSM_s {
	int curState;
	// initialize in FSM_Begin()
	int curFsmNumStateTable;
	STATE_TABLE_t *curFsmTable;
	/* Store multiple state table, initialized by FSM_Rgist() */
	FSM_REGIST_t registFsm[MAX_FSM_NUM];
	int registFsmNum;
	FSM_STACK_t stack[MAX_FSM_STACK];
	int curStackTop;
} FSM_t;

void FSM_Init(FSM_t * pFsm);
void FSM_Regist(FSM_t * pFsm, STATE_TABLE_t * pStateTable, int FsmId,
		int curFsmTableSize);
void FSM_Begin(FSM_t * pFsm, int FsmId);
void FSM_MoveState(FSM_t * pFsm, STATE_t state);
void FSM_EventHandle(FSM_t * pFsm, EVENT_t event);
void FSM_Push(FSM_t * pFsm);
void FSM_Pop(FSM_t * pFsm);

ACT_TABLE_t *FSM_getActTable(FSM_t * pFsm)
{
	int i;
	STATE_t curState = pFsm->curState;
	int max_state_num = pFsm->curFsmNumStateTable;
	ACT_TABLE_t *ActTable;

	for (i = 0; i < max_state_num; i++) {
		if (pFsm->curFsmTable[i].state == curState)
			break;
	}

	ActTable = pFsm->curFsmTable[i].StateTable;
	return ActTable;
}

/* 客户端提供的状态处理函数 */
/* Layer + State _ Event */
/* L1 Event */
void L1state1_L1Event1Fun(void *pFsm)
{
	FSM_MoveState((FSM_t *) pFsm, L1_STATE2);
	return;
}

void L1state1_L1Event3Fun(void *pFsm)
{
	FSM_MoveState((FSM_t *) pFsm, L1_STATE3);
	return;
}

void L1state2_L1Event2Fun(void *pFsm)
{
	FSM_MoveState((FSM_t *) pFsm, L1_STATE3);
	return;
}

/* L2 Event */
void L2state1_L2Event1Fun(void *pFsm)
{
	FSM_MoveState((FSM_t *) pFsm, L2_STATE2);
	return;
}

/* Cross Event between L1 & L2 */
void L1state2_L1L2Event1Fun(void *pFsm)
{
	FSM_Push((FSM_t *) pFsm);
	FSM_Begin((FSM_t *) pFsm, FSM_L2);
	FSM_MoveState((FSM_t *) pFsm, L2_STATE1);

	return;
}

void L2state2_L1L2Event2Fun(void *pFsm)
{
	FSM_Pop((FSM_t *) pFsm);
	FSM_MoveState((FSM_t *) pFsm, L1_STATE3);

	return;
}

/*L1 状态机定义*/
ACT_TABLE_t L1state1ActTable[] = {
	{L1_EVENT1, L1state1_L1Event1Fun}
	,
	{L1_EVENT3, L1state1_L1Event3Fun}
	,
};

ACT_TABLE_t L1state2ActTable[] = {
	{L1_EVENT2, L1state2_L1Event2Fun}
	,
	{L1_L2_EVENT1, L1state2_L1L2Event1Fun}
	,
};

STATE_TABLE_t L1FsmTable[] = {
	{L1_STATE1, sizeof(L1state1ActTable)/sizeof(ACT_TABLE_t), L1state1ActTable}
	,
	{L1_STATE2, sizeof(L1state2ActTable)/sizeof(ACT_TABLE_t), L1state2ActTable}
	,
};

/*L2 状态机定义*/
ACT_TABLE_t L2state1ActTable[] = {
	{L2_EVENT1, L2state1_L2Event1Fun}
	,
};

ACT_TABLE_t L2state2ActTable[] = {
	{L1_L2_EVENT2, L2state2_L1L2Event2Fun}
	,
};

STATE_TABLE_t L2FsmTable[] = {
	{L2_STATE1, sizeof(L2state1ActTable)/sizeof(ACT_TABLE_t), L2state1ActTable}
	,
	{L2_STATE2, sizeof(L2state2ActTable)/sizeof(ACT_TABLE_t), L2state2ActTable}
	,
};

void FSM_Init(FSM_t * pFsm)
{
	pFsm->registFsmNum = 0;
	pFsm->curStackTop = -1;
	pFsm->curState = 0;
}

void FSM_Regist(FSM_t * pFsm, STATE_TABLE_t * pStateTable, int FsmId,
		int curFsmTableSize)
{
	pFsm->registFsm[pFsm->registFsmNum].FsmId = FsmId;
	pFsm->registFsm[pFsm->registFsmNum].FsmTable = pStateTable;
	pFsm->registFsm[pFsm->registFsmNum].NumStateTable = curFsmTableSize;

	pFsm->registFsmNum++;
	return;
}

void FSM_Begin(FSM_t * pFsm, int FsmId)
{
	int i;
	for (i = 0; i < pFsm->registFsmNum; i++) {
		if (FsmId == pFsm->registFsm[i].FsmId) {
			pFsm->curFsmTable = pFsm->registFsm[i].FsmTable;
			pFsm->curFsmNumStateTable =
			    pFsm->registFsm[i].NumStateTable;
			break;
		}
	}

	return;
}

/* 状态迁移 */
void FSM_MoveState(FSM_t * pFsm, STATE_t state)
{
	printf("From %s to %s\n", s_state[pFsm->curState], s_state[state]);
	pFsm->curState = state;
	return;
}

void FSM_Push(FSM_t * pFsm)
{
	if (pFsm->curStackTop < MAX_FSM_STACK) {
		pFsm->curStackTop++;
		pFsm->stack[pFsm->curStackTop].state = pFsm->curState;
		pFsm->stack[pFsm->curStackTop].pFsmTable = pFsm->curFsmTable;
		pFsm->stack[pFsm->curStackTop].NumStateTable =
		    pFsm->curFsmNumStateTable;
	}

	return;
}

void FSM_Pop(FSM_t * pFsm)
{
	if (pFsm->curStackTop > -1) {
		pFsm->curState = pFsm->stack[pFsm->curStackTop].state;
		pFsm->curFsmTable = pFsm->stack[pFsm->curStackTop].pFsmTable;
		pFsm->curFsmNumStateTable =
		    pFsm->stack[pFsm->curStackTop].NumStateTable;
		pFsm->curStackTop--;
	}

	return;
}

void FSM_EventHandle(FSM_t * pFsm, EVENT_t event)
{
	int max_act_num = 0;
	int i = 0;
	ACT_TABLE_t *pActTable = NULL;
	ActFun eventActFun = NULL;

	printf("Event %s\n", s_event[event]);
	/* 获取当前状态动作表 */
	pActTable = FSM_getActTable(pFsm);
	if (pActTable == NULL) {
		printf("pActTable is NULL\n");
		exit(-1);
	}

	max_act_num = FSM_getNumActTable(pFsm->curFsmTable);

	/* 获取当前动作函数 */
	for (i = 0; i < max_act_num; i++) {
		if (event == pActTable[i].event) {
			eventActFun = pActTable[i].eventActFun;
			if (eventActFun == NULL)
				printf("eventActFun is NULL\n");
			break;
		}
	}

	/* 动作执行 */
	if (eventActFun) {
		eventActFun(pFsm);
	}

	return;
}

int main(int argc, char *argv[])
{
	FSM_t pFsm;

	FSM_Init(&pFsm);

	/* 状态机注册 */
	FSM_Regist(&pFsm, L1FsmTable, FSM_L1,
		   sizeof(L1FsmTable) / sizeof(STATE_TABLE_t));
	FSM_Regist(&pFsm, L2FsmTable, FSM_L2,
		   sizeof(L2FsmTable) / sizeof(STATE_TABLE_t));

	/* 开始L1状态机 */
	/* Initialize current part of PSM_t according to FsmId */
	while (1) {
		FSM_Begin(&pFsm, FSM_L1);
		FSM_MoveState(&pFsm, L1_STATE1);
		FSM_EventHandle(&pFsm, L1_EVENT1);
		/* push 状态机 */
		FSM_EventHandle(&pFsm, L1_L2_EVENT1);
		/* L2状态机处理 */
		FSM_EventHandle(&pFsm, L2_EVENT1);
		/* pop 状态机 */
		FSM_EventHandle(&pFsm, L1_L2_EVENT2);
		/* L1状态机处理 */
		FSM_EventHandle(&pFsm, L1_EVENT2);
		sleep(1);
		printf("-------- One more round --------\n");
	}
	return 0;
}
