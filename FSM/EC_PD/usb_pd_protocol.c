typedef struct pd_instance_s {

} pd_instance_t;

enum cc_states {

};

enum pe_states {

};

enum pd_events {
	PD_EVENT_RX,
	PD_EVENT_TX,
	PD_EVENT_CC,
	PD_EVENT_PHY,
	// Question: 需要区分soft reset和hard reset 吗？
	PD_EVENT_RESET,
};

void pd_init(void)
{

}

void process_event(pd_instance_t *pd_instance, int evt)
{

}

/* 
 * 两种方案
 * 1 state machine只包含FSM的内容，循环和初始化在外部，那么就需要全局变量存储
 * 2 state machine是整个循环，则无需太多的全局变量
 */
void pd_state_macchine(pd_instance_t *pd_instance)
{
	int evt;
	// current timeout
	int timeout = 10 ms;

	// 相关变量的初始化，设置为初始状态
	state_machine_init():
	// 包括通用的tcpc phy init以及board specific的部分，通过call back实现
	phy_init();

	while (1) {
	// 真正state machine的部分
		evt = task_wait_event(timeout);

		// 处理重要的event事件
		process_event(pd_instance, evt);

		timeout = 500 ms;

		// 
		connect_state_machine(pd_instance);
		cc_status = connect_status(pd_instance);
		pe_state_machine();
		switch (cur_state) {
			case PD_STATE_DISABLED:
				break;
			case PD_STATE_SRC_DISCONNECTED:
		}
	}
}
