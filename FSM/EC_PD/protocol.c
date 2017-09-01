void pd_state_machine(void)
{
	int state;
	int port;
	// 表示PD Contract是否已经建立
	int pd_connected;

	while (1) {
		// timeout是用来延时的
		// event优先级高，timeout低
		task_wait_event(timeout);

		state = pd[port].state;
		timeout = 500 * MSEC;

		switch () {
		case PD_STATE_DISABLED:
			// Pass
			break;
		case PD_STATE_DISCONNECTED:

			break;
		case PD_STATE_DISCONNECTED_DEBOUNCE:

			break;
		case PD_STATE_SRC_ACCESSORY:

			break;
		// Any other states after debounce ?
		//case PD_STATE_SRC_
		case PD_STATE_SRC_STARTUP:
		/* 
		 * summary: reset to prepare environment
		 * enter: reset CapsCounter and reset PL (including reset Message id)
		 * exit: NULL 
		 * event: PL reset complete or SwapSourceStartTimer times out 
		 */
			caps_count = 0;
			msg_id = 0;

			// 在文档中，只需要超时即可，在ec中，需要等待一段时间使Power稳定，直到稳定进入discovery
			// 没有实现swap的部分
			set_state_timeout(port, get_time().val + PD_POWER_SUPPLY_TURN_ON_DELAY, PD_STATE_SRC_DISCOVERY);
			
			break;
		case PD_SRC_SEND_CAPABILITIES:

			break;
		case PD_STATE_SRC_DISCOVERY:

			break;
		case PD_SRC_NEGOTIATE_CAPABILITY:

			break;
		case PD_SRC_TRANSITION_SUPPLY:

			break;
		case PD_SRC_READY:

			break;
		case PD_STATE_ERRORRECOVERY:

			break;
		}
	}
}
