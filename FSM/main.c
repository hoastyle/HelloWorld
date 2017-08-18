#include <stdio.h>

enum
{
	STATE1 = 1,
	STATE2,
	STATE3,
};

enum
{
	EVENT1 = 1,
	EVENT2,
	EVENT3,
};

typedef void (*ActFun)(void *);

typedef struct ACT_TABLE_s
{
	int event;
	ActFun eventActFun;
} ACT_TABLE_t;

typedef struct STATE_TABLE_s
{
	int state;
	ACT_TABLE_t *StateTable;
} STATE_TABLE_t;

typedef struct FSM_s
{
	STATE_TABLE_t *FsmTable;
	int curState;
} FSM_t;

void FSM_Regist(FSM_t* pFsm, STATE_TABLE_t *pStateTable)
{
   pFsm->FsmTable =  pStateTable;
   return;
}
/*状态迁移*/
void FSM_MoveState(FSM_t* pFsm,int state)
{
   pFsm->curState = state;
   return;
}

/*客户端提供的状态处理函数*/
void state1Event1Fun(void* pFsm)
{
    FSM_MoveState((FSM_t*)pFsm, STATE2);
	printf("state1 - event1: to state2\n");
    return;
}

void state1Event3Fun(void* pFsm)
{
    FSM_MoveState((FSM_t*)pFsm, STATE3);
	printf("state1 - event3: to state3\n");
    return;
}

void state2Event2Fun(void* pFsm)
{
    FSM_MoveState((FSM_t*)pFsm, STATE3);
	printf("state2 - event2: to state3\n");
    return;
}

/*状态1的动作表*/
ACT_TABLE_t state1ActTable[] = {
    {EVENT1,state1Event1Fun},
    {EVENT3,state1Event3Fun},
};

/*状态2的动作表*/
ACT_TABLE_t state2ActTable[] = {
    {EVENT2,state2Event2Fun},
};

/*状态表*/
// state table 嵌套 event table，每个state对应多个event
STATE_TABLE_t FsmTable[] = {
    {STATE1,state1ActTable},
    {STATE2,state2ActTable},
};

ACT_TABLE_t *FSM_getActTable(FSM_t *pFsm)
{
	int i;
	int curState = pFsm->curState;
	int max_state_num = sizeof(FsmTable) / sizeof(STATE_TABLE_t);
	ACT_TABLE_t *ActTable;
	 
	for (i = 0; i < max_state_num; i++) {
		if (pFsm->FsmTable[i].state == curState)
			break;
	}

	ActTable = pFsm->FsmTable[i].StateTable;
	return ActTable;
}

/*事件处理*/
void FSM_EventHandle(FSM_t* pFsm,int event)
{
	int max_act_num;
	int i;
    ACT_TABLE_t* pActTable = NULL;
    ActFun eventActFun = NULL;
    /*获取当前状态动作表*/
    pActTable = FSM_getActTable(pFsm);
	if (pActTable == NULL) printf("error\n");
	max_act_num = sizeof(*pActTable) / sizeof(ACT_TABLE_t);
	
    /*获取当前动作函数*/
    for(i=0; i < max_act_num; i++)
    {
        if(event == pActTable[i].event)
        {
            eventActFun = pActTable[i].eventActFun;
			if (eventActFun == NULL)
				printf("event pointer is null, error\n");
            break;
        }
    }
    /*动作执行*/
    if(eventActFun)
    {
        eventActFun(pFsm);
    }
}

int main(int argc, char* argv[])
{
    FSM_t fsm;
    /*状态表注册*/
    FSM_Regist(&fsm, FsmTable);
    FSM_MoveState(&fsm, STATE1);
	while (1) {
    	FSM_EventHandle(&fsm, EVENT1);
    	FSM_EventHandle(&fsm, EVENT2);
    	FSM_MoveState(&fsm, STATE1);
		printf("One more round.\n");
		sleep(1);
    }
	return 0;
}
