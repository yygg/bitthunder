#ifndef __BT_NET_H__
#define __BT_NET_H__

#include <bitthunder.h>
#include "bt_phy.h"

typedef struct _BT_NET_IF {
	BT_LIST_ITEM			oItem;
	BT_HANDLE 				hIF;
	BT_HANDLE 				hPhy;
	BT_HANDLE 				hTxFifo;
	BT_u32 					ulFlags;

#define	DATA_READY			0x00000001

	BT_u32 					ulIFFlags;

#define	BT_NETIF_FLAG_UP				NETIF_FLAG_UP
#define BT_NETIF_FLAG_BROADCAST			NETIF_FLAG_BROADCAST
#define BT_NETIF_FLAG_POINTTOPOINT		NETIF_FLAG_POINTTOPOINT
#define BT_NETIF_FLAG_DHCP				NETIF_FLAG_DHCP
#define BT_NETIF_FLAG_LINK_UP			NETIF_FLAG_LINK_UP
#define BT_NETIF_FLAG_ETHARP			NETIF_FLAG_ETHARP
#define BT_NETIF_FLAG_ETHERNET			NETIF_FLAG_ETHERNET
#define BT_NETIF_FLAG_IGMP				NETIF_FLAG_IGMP

	BT_u32 					smFlags;

#define	NET_IF_ADDED		0x00000001
#define	NET_IF_REMOVED		0x00000002

	const BT_DEV_IF_EMAC   *pOps;

	BT_u32					ulID;
} BT_NET_IF;


BT_ERROR BT_RegisterNetworkInterface(BT_HANDLE hIF);

#endif
