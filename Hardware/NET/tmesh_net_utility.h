// tmesh_net_utility.h:  created at 2017-7-19 by Bell Zhong

#ifndef TMESH_NET_UTILITY_H_INCLUDED
#define TMESH_NET_UTILITY_H_INCLUDED
#include "stm32l1xx_hal.h"
#include <stdbool.h>



#define EEPROM_ADDR_BASE_VENDER    (0x0c00)
#define EEPROM_ADDR_SIZE_VENDER    (0x0004)
#define EEPROM_ADDR_BASE_MACSN     (0x0c04)
#define EEPROM_ADDR_SIZE_MACSN     (0x0004)

// only 4 bits in uart interactive protocol
typedef enum
{
	MSG_CONFIG 	= 0,			// ������ص�һЩ��������
	MSG_PROTOBUF = 2,
	MSG_PLAIN 	= 3,
	MSG_TO_RF 	= 4,			//����ͨ��RF��ת��
	MSG_DIRECT 	= 5,			//����ֱ���´�������豸
	MSG_NB_CMD 	= 6,			//the command sent to NB-IOT model
	MSG_NB_DATA = 7,		//the data sent to NB-IOT model
} UART_msg_type;


typedef enum tmesh_ret_code
{

	TMESH_OK = 0,
	TMESH_UNKNOWNERROR = 1,					//δ֪����
	TMESH_VERSIONNOTSUPPORT = 2,			//�汾��֧��
	TMESH_COMMANDNOTVALID = 3,				//�Ƿ�����
	TMESH_LOGINED = 4,						//���û��Ѿ���¼
	TMESH_UNLOGINED = 5,					//���û�δ��¼
	TMESH_USERORPWDERROR = 6,				//�û����������
	TMESH_NOAUTHORITY = 7,					//��Ȩ��
	TMESH_TIMEOUT = 8,						//��ʱ
	//NETIP_FILENOTFOUND = 109,				//����ʧ�ܣ�û���ҵ���Ӧ�ļ�
	//NETIP_FILEFOUND = 110,				//���ҳɹ�������ȫ���ļ�
	//NETIP_FILEFOUNDPART = 111,			//���ҳɹ������ز����ļ�
	//NETIP_USEREXIST = 112,				//���û��Ѿ�����
	//NETIP_USENOTEXIST = 113,				//���û�������
	//NETIP_GROUPEXIST = 114,				//���û����Ѿ�����
	//NETIP_GROUPNOTEXIST = 115,			//���û��鲻����
	TMESH_NOTLINKEDIN	= 16,				// device is not linked in the gateway.
	TMESH_OFFLINE		= 17,				// notify the device to update the firmware.
	TMESH_NOTMACHED		= 18,				// device has not matched to the gateway,but is offline.
	TMESH_CACHEDSUCCESS	= 19,
	TMESH_CACHEDFAIL	= 20,
	TMESH_NEEDUPDATE	= 21,				// device has linked in the gateway,but is offline.
	TMESH_NEEDREBOOT	= 50,				//�ɹ����豸��Ҫ����
	//NET_OPERATION_UPGRADE_ALAREADY_START	= 511,//�ظ�����
	//NET_OPERATION_UPGRADE_NOT_START		= 512,//δ��ʼ����
	//NET_OPERATION_UPGRADE_FAILED			= 514,//����ʧ��
	//NET_OPERATION_UPGRADE_FAILED_BUSY		= 516,//�豸æ���߷�����æ
	//NET_OPERATION_UPGRADE_NO_POWER		= 517 //���������������ӿ������޷�ֹͣ
} TMESH_RET_CODE;


typedef enum ret_code
{
	NETIP_OK = 100,
	NETIP_UNKNOWNERROR = 101,			//δ֪����
	NETIP_NOTSUPPORT = 102,				//�汾��֧��
	NETIP_NOTVALID = 103,				//�Ƿ�����
	NETIP_LOGINED = 104,				//���û��Ѿ���¼
	NETIP_UNLOGINED = 105,				//���û�δ��¼
	NETIP_USERORPWDERROR = 106,			//�û����������
	NETIP_NOPOWER = 107,				//��Ȩ��
	NETIP_TIMEOUT = 108,				//��ʱ
	NETIP_NOTFOUND = 109,				//����ʧ�ܣ�û���ҵ���Ӧ�ļ�
	NETIP_FOUND = 110,					//���ҳɹ�������ȫ���ļ�
	NETIP_FOUNDPART = 111,				//���ҳɹ������ز����ļ�
	NETIP_USEREXIST = 112,				//���û��Ѿ�����
	NETIP_USENOTEXIST = 113,			//���û�������
	NETIP_GROUPEXIST = 114,				//���û����Ѿ�����
	NETIP_GROUPNOTEXIST = 115,			//���û��鲻����
	NETIP_NOTLINKEDIN	= 116,			// device has not linked in the gateway
	NETIP_OFFLINE		= 117,			// device has linked in the gateway,but is offline.
	NETIP_NOTMACHED		= 118,			// device has linked in the gateway,but is offline.
	NETIP_CACHEDSUCCESS	= 119,
	NETIP_CACHEDFAIL	= 120,
	NETIP_NEEDUPDATE	= 121,
	NETIP_NEEDREBOOT 	= 150,			//�ɹ����豸��Ҫ����
	NET_OPERATION_UPGRADE_ALAREADY_START = 511,//�ظ�����
	NET_OPERATION_UPGRADE_NOT_START		 = 512,//δ��ʼ����
	NET_OPERATION_UPGRADE_FAILED		 = 514,//����ʧ��
	NET_OPERATION_UPGRADE_FAILED_BUSY	 = 516,//�豸æ���߷�����æ
	NET_OPERATION_UPGRADE_NO_POWER		 = 517 //���������������ӿ������޷�ֹͣ
} RET_CODE;


// 1 Byte in cloud interactive protocol
typedef enum
{
	MSG_JSON 	= '1',
	MSG_FIRMWARE = '3',		// used for upgrading
} TCLD_msg_type;

uint8_t tnet_utility_get_packetnum(void);
void delay_ms(uint16_t xms);
char* tnet_utility_get_sn_with_prefix(void);
char* tnet_utility_get_sn_without_prefix(void);
char* tnet_utility_get_sn(void);
char* tnet_utility_get_vender(void);
char* tnet_utility_get_spotid(void);
char* tnet_utility_get_hardware(void);
char* tnet_utility_get_software(void);
char* tnet_utility_get_buildtime(void);
int tnet_utility_get_runtime(void);
int tnet_utility_get_rssi(void);
char* tnet_utility_get_sim(void);
int tnet_utility_get_batt(void);
char* tnet_utility_get_imei(void);
char* tnet_utility_get_model(void);
uint32_t tnet_utility_get_mac_sn(void);

#endif

