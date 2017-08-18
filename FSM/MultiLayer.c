/* Multi Layer FSM */

#include "Layer.h"

#define MAX_FSM_NUM 2
#define MAX_FSM_STACK 2

enum {
	L1_STATE1 = 1,
	L1_STATE2,
	L1_STATE3,
	L2_STATE1,
	L2_STATE2,
};

enum {
	L1_EVENT1,
	L1_EVENT2,
	L1_EVENT3,
	L2_EVENT1,
	L1_L2_EVENT1,
	L1_L2_EVENT2,
};

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
	int state;
	STATE_TABLE_t *pFsmTable;
	int NumStateTable;
} FSM_STACK_t;

typedef struct FSM_s
{
	int curState;
	int curFsmNumStateTable;
	STATE_TABLE_t *curFsmTable;
	/* Store multiple state table */
	FSM_REGIST_t registFsm[MAX_FSM_NUM];
	int registFsmNum;
	FSM_STACK_t stack[MAX_FSM_STACK];
	int curStackTop;
} FSM_t;

void FSM_Init(FSM_t* pFsm);
void FSM_Regist(FSM_t* pFsm, STATE_TABLE_t *pStateTable,int FsmId,int curFsmTableSize);
void FSM_Begin(FSM_t* pFsm,int FsmId);
void FSM_MoveState(FSM_t* pFsm,int state);
void FSM_EventHandle(FSM_t* pFsm,int event);
void FSM_Push(FSM_t* pFsm);
void FSM_Pop(FSM_t* pFsm);

/*状态迁移*/
void FSM_MoveState(FSM_t* pFsm, int state)
{
   pFsm->curState = state;
   return;
}

/*客户端提供的状态处理函数*/               
void L1state1_Event1Fun(void* pFsm)
{                                          
    FSM_MoveState((FSM_t*)pFsm, L1_STATE2);   
    printf("L1 event1 : L1 state1 - state2\n");
    return;                                
}                                          
                                           
void L1state1_Event3Fun(void* pFsm)           
{                                          
    FSM_MoveState((FSM_t*)pFsm, L1_STATE3);   
    printf("L1 event3 : L1 state1 - state3\n");
    return;                                
}                                          
                                           
void L1state2_Event2Fun(void* pFsm)           
{                                          
    FSM_MoveState((FSM_t*)pFsm, L1_STATE3);   
    printf("L1 event2 : L1 state2 - state3\n");
    return;                                
}

void L2state1_L2Event1Fun(void *pFsm)
{
    FSM_MoveState((FSM_t*)pFsm, L2_STATE2);   
    printf("L2 event1 : L2 state1 - state1\n");
    return;                                
}

void L1state2_L1L2Event1Fun(void* pFsm)
{
    FSM_Push((FSM_t*) pFsm);
    FSM_Begin((FSM_t*)pFsm, FSM_L2);
    FSM_MoveState((FSM_t*)pFsm, L2_STATE1);
    printf("L1L2 event1 : L1 state2 - L2 state1\n");

    return;
}

void L2state2_L1L2Event2Fun(void* pFsm)
{
    FSM_Pop((FSM_t*)pFsm);
    printf("L1L2 event2 : L2 state2 - L2 state2\n");

    return;
}

/*L1 状态机定义*/
ACT_TABLE_t L1state1ActTable[] = {
    {L1_EVENT1, L1state1_Event1Fun},
    {L1_EVENT3, L1state1_Event3Fun},
};

ACT_TABLE_t L1state2ActTable[] = {
    {L1_EVENT2, L1state2_Event2Fun},
    {L1_L2_EVENT1, L1state2_L1L2Event1Fun},
};

STATE_TABLE_t L1FsmTable[] = {
    {L1_STATE1, L1state1ActTable},
    {L1_STATE2, L1state2ActTable},
};

/*L2 状态机定义*/
ACT_TABLE_t L2state1ActTable[] = {
    {L2_EVENT1,L2state1_L2Event1Fun},
};

ACT_TABLE_t L2state2ActTable[] = {
    {L1_L2_EVENT2, L2state2_L1L2Event2Fun},
};

STATE_TABLE_t L2FsmTable[] = {
    {L2_STATE1, L2state1ActTable},
    {L2_STATE2, L2state2ActTable},
};

void FSM_Regist(FSM_t* pFsm, STATE_TABLE_t* pStateTable, int FsmId, int curFsmTableSize)
{
    pFsm->registFsm[pFsm->registFsmNum].FsmId = FsmId;
    pFsm->registFsm[pFsm->registFsmNum].FsmTable = pStateTable;
    pFsm->registFsm[pFsm->registFsmNum].NumStateTable= curFsmTableSize;

    pFsm->registFsmNum++;
    return;
}

void FSM_Begin(FSM_t* pFsm,int FsmId)
{
	int i;
	for(i = 0; i < pFsm->registFsmNum; i++)
	{
		if(FsmId == pFsm->registFsm[i].FsmId)
		{
			pFsm->curFsmTable = pFsm->registFsm[i].FsmTable;
			pFsm->curFsmNumStateTable = pFsm->registFsm[i].NumStateTable;
			break;
		}
	}

	return;
}

void FSM_Push(FSM_t* pFsm)
{
	if(pFsm->curStackTop < MAX_FSM_STACK)
	{
		pFsm->curStackTop++;
		pFsm->stack[pFsm->curStackTop].state     = pFsm->curState;
		pFsm->stack[pFsm->curStackTop].pFsmTable = pFsm->curFsmTable;
		pFsm->stack[pFsm->curStackTop].NumStateTable = pFsm->curFsmNumStateTable;
	}

	return;
}

void FSM_Pop(FSM_t* pFsm)
{
    if(pFsm->curStackTop > -1)
	{
		pFsm->curState   = pFsm->stack[pFsm->curStackTop].state;
		pFsm->curFsmTable = pFsm->stack[pFsm->curStackTop].pFsmTable;
		pFsm->curFsmNumStateTable = pFsm->stack[pFsm->curStackTop].NumStateTable;
		pFsm->curStackTop--;
	}

	return;
}

int main(int argc, char *argv[])
{
    FSM_t pFsm;

    FSM_Init(&pFsm);
    /*状态机注册*/
    FSM_Regist(&pFsm, L1FsmTable, FSM_L1, sizeof(L1FsmTable)/sizeof(STATE_TABLE_t));
    FSM_Regist(&pFsm, L2FsmTable, FSM_L2, sizeof(L2FsmTable)/sizeof(STATE_TABLE_t));
    /*开始L1状态机*/
    FSM_Begin(&pFsm, FSM_L1);
    FSM_MoveState(&pFsm, L1_STATE1);
    FSM_EventHandle(&pFsm, L1_EVENT1);
    /*push 状态机*/
    FSM_EventHandle(&pFsm, L1_L2_EVENT1);
    /*L2状态机处理*/
    FSM_EventHandle(&pFsm, L2_EVENT1);
    /*pop 状态机*/
    FSM_EventHandle(&pFsm, L1_L2_EVENT2);
    /*L1状态机处理*/
    FSM_EventHandle(&pFsm, L1_EVENT2);
    return 0;
}
