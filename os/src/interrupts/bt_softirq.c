/**
 *	BitThunder SoftIRQ implementation.
 *
 *	The API is modelled after the linux softirq implementation, to allow
 *	kernel developer skills to be relatively easily transferred.
 *
 **/

#include <bt_types.h>
#include <intterupts/bt_softirq.h>

static BT_SOFTIRQ 	g_SoftIRQ[BT_CONFIG_SOFTIRQ_MAX];
static BT_u32 		ulIRQPending;
static BT_HANDLE	g_hMutex;

BT_ERROR BT_OpenSoftIRQ(BT_u32 ulSoftIRQ, BT_SOFTIRQ_HANDLER pfnHandler, void *pData) {
	g_SoftIRQ[ulSoftIRQ].pfnHandler = pfnHandler;
	g_SoftIRQ[ulSoftIRQ].pData		= pData;
	return BT_ERR_NONE;
}

BT_ERROR BT_RaiseSoftIRQ(BT_u32 ulSoftIRQ) {

	BT_ERROR Error;

	// Enter Critical Section
	{
		Error = BT_RaiseSoftIRQFromISR(ulSoftIRQ);
	}
	// Exit Critical Section
	return Error;
}

BT_ERROR BT_RaiseSoftIRQFromISR(BT_u32 ulSoftIRQ) {
	if(ulSoftIRQ < BT_CONFIG_SOFTIRQ_MAX) {
		ulIRQPending |= (1 << ulSoftIRQ);
		return BT_ERR_NONE;
	}

	BT_ReleaseMutexFromISR(g_hMutex);

	return BT_ERR_GENERIC;
}


static void softirq_dispatcher(void *pParam) {
	while(1) {


	}
}

static BT_ERROR bt_softirq_init() {
	BT_ERROR Error;
	BT_THREAD_CONFIG oConfig;

	oConfig.ulStackDepth 	= 128;
	oConfig.ulPriority 		= BT_CONFIG_SOFTIRQ_PRIORITY;

	g_hMutex = BT_CreateMutex(&Error);
	if(!g_hMutex) {
		return BT_ERR_GENERIC;
	}

	BT_PendMutex(g_hMutex, 0);

	BT_kTaskCreate(softirq_dispatcher, "ksoftirqd", &oConfig, &Error);

	return BT_ERR_NONE;
}

BT_MODULE_INIT_DEF oModuleEntry = {
	BT_MODULE_NAME,
	bt_softirq_init,
};
