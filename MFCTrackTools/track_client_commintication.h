#pragma onece
#include "tch_params.h"
#include "communtication.h"
#include "share_stream.h"
#include <list>
using namespace std;
#define STU_SETTRACK_CMD  0x100
#define TEA_SETTRACK_CMD  0x101
#define STU_GETTRACK_CMD  0x102
#define TEA_GETTRACK_CMD  0x103
#define TIMEOUT 500
typedef int(*Stream_Call_Back)(char *pBuf, void*param);
#define TEACH_STREAM_PORT 21303
#define STUDENT_STREAM_PORT  21302
typedef enum
{
	STREAMCLINT_START = 0,
	STREAMCLINT_STOP,
	STREAM_STATUS_ERR,

}StreamClient_Status_t;
typedef struct Stream_Message
{
	RH_FRAMEHEAD_t fh;
	void *stream_data;//����
}Stream_Message_t;
typedef list<Stream_Message_t *> LISTSTREAM;

typedef struct _TRACK_CMD_INFO_T{
	int cmd;
	char cmd_name[64];
}Track_cmd_info_t;
typedef struct _Client_Handle
{
	LISTSTREAM list_Handle;
	StreamClient_Status_t nRun_Status;
	int first_frame;
	int nChannel;
	pthread_mutex_t lock;

}Client_Handle_t;
typedef struct Stream_Handle
{
	int channel;
	int port;
	char iP[16];
	Stream_Call_Back call_back_fun;//�����ݻص���video����
	void *outParm;//��չ(�����ڲ��Լ����)
	void* param1;//��չ����,��ʹ���ߴ���ȥ��ͨ���ص�����call_back������
}RecvStream_Handle_t;
int init_stream_recv(RecvStream_Handle_t* pRecv_stream_handle);
int ctrlClient_init_trackCommuntication();
int ctrlClient_set_teach_params(TeaITRACK_Params * tec_param);