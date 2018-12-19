#include <stdio.h>
/*#include "adhocyaya.h"*/
#include <unistd.h>  
#include <stdbool.h>
#include <android/log.h>
/*#include "utils/Log.h"*/
#define ADHOCLOG_SO(fmt, ...) __android_log_print(ANDROID_LOG_WARN, "Adhoc_SO", "%12s:%-5d,%s ," fmt, __FILE__, __LINE__ ,(char*)__FUNCTION__,##__VA_ARGS__)

/*#define  LOG_TAG    "libplasma"*/
/*#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)*/
/*static char mark_label[64] = "yourlog-";*/
/*#define ADHOCLOG_SO(fmt, ...) ALOGI("[%s],tid:%u,%s,F:%s:%d,Fun:%s " fmt,"", (unsigned int)gettid(),mark_label,(char*)__FILE__,__LINE__,(char*)__FUNCTION__,##__VA_ARGS__)*/


///////所有接口如下:
///////////////////////////////////////////////////////////////////////// 
/**
  @param srcAddr 源ip
  @param desAddr 目的ip
  @param data 数据内容
 **/
/*
 *typedef int (*DataRecvCallback)(char *srcAddr, unsigned char *pData);
 *typedef int (*NetWorkStatusCallback)(int statusType, char *pParam);
 *typedef int (*PcmVoiceCallback)(int statusType, char *pParam);
 *
 *struct{
 *    char mPlatform[32];
 *    char mUEKind[32];
 *    char mHW[32];
 *    char mOS[32];
 *    int mType;
 *}ConfigParams;
 *
 *
 *void init(char paras[]);//初始化自组网
 *void tellLocalIpAddr(char ipAddr[]);//设置本机自组网ip
 *void queryNetWorkStatus(char cmd[]);//查询网络状态
 *void setParameters(char paras[]);//设置自组网参数
 *void setPttState (char state[]);//设置ptt状态
 *void sendBDMsg2AdHoc(char  gga[]);//发送北斗消息到自组网
 *void sendExtraData (int type, char data[]);//执行shell命令
 *void setIsNeedHeadForUserData(bool isNeedHead);//设置用户数据是否需要头部
 *
 *
 *int openAdHocDevice();//打开自组网设备 0:打开成功, 非0:打开失败
 *int closeAdHocDevice();//关闭自组网设备
 *int reOpenAdHocDevice();//重打开自组网设备
 *int setEnabled (bool enabled);//设置数据传输模式，ip或非ip true :非ip模式，false :ip模式
 *int sendData( char data[]);//发送数据
 *int sendData3(char srcAddr[], char desAddr[], char data[]);//发送数据
 *int sendDataPri(char srcAddr[],  char desAddr[],  char data[], int pri);//发送数据
 *int sendPcmVoice(char voiceData[]);//发送话音数据
 *int setEthernetIP(char ipAddr[]);//设置以太网ip
 *int updateModem(char fileName[], char data[]);//升级modem
 *
 *
 *ConfigParams getConfigParams();//获取平台信息
 *char* getEthernetIP();//查询以太网ip
 *
 *
 *bool isEnabled();//查询数据传输模式 
 *bool isNetWorkAvailable();//网络是否可用
 *bool addDataRecvListener(DataRecvCallback *pFunc);//添加接收数据回调监听器    
 *bool addNetWorkStatusListener(NetWorkStatusCallback *pFunc);//添加网络状态回调监听器
 *bool addPcmVoiceListener(PcmVoiceCallback *pFunc);//添加接收话音回调监听器
 *
 */

///////////////////////////////////////////////////////////////////////// 




//定义函数指针
////////////////////////////////////////////////////// 

/**
  @param srcAddr 源ip
  @param desAddr 目的ip
  @param data 数据内容
 **/

typedef struct{
	char mPlatform[32];
	char mUEKind[32];
	char mHW[32];
	char mOS[32];
	int mType;
}ConfigParams;

typedef int (*DataRecvCallback)(char *srcAddr, unsigned char *pData);
typedef int (*NetWorkStatusCallback)(int statusType, char *pParam);
typedef int (*PcmVoiceCallback)(int statusType, char *pParam);

/*
 *typedef void (*DataRecvCallback)(char *srcAddr, unsigned char *pData);
 *typedef void (*NetWorkStatusCallback)(int statusType, char *pParam);
 *typedef void (*PcmVoiceCallback)(int statusType, char *pParam);
 */

/*
 *typedef void (*RegCallBackFuncPointer_data)(DataRecvCallback acall);
 *typedef void (*RegCallBackFuncPointer_network)(NetWorkStatusCallback acall);
 *typedef void (*RegCallBackFuncPointer_voice)(PcmVoiceCallback acall);
 */

typedef int (*RegCallBackFuncPointer_data)(DataRecvCallback acall);
typedef int (*RegCallBackFuncPointer_network)(NetWorkStatusCallback acall);
typedef int (*RegCallBackFuncPointer_voice)(PcmVoiceCallback acall);

//8 void
typedef void (*Init_ptr)(char paras[]);//初始化自组网
typedef void (*TellLocalIpAddr_ptr)(char ipAddr[]);//设置本机自组网ip
typedef void (*QueryNetWorkStatus_ptr)(char cmd[]);//查询网络状态
typedef void (*SetParameters_ptr)(char paras[]);//设置自组网参数
typedef void (*SetPttState_ptr)(char state[]);//设置ptt状态
typedef void (*SendBDMsg2AdHoc_ptr)(char gga[]);//发送北斗消息到自组网
//typedef void (*SendExtraData_ptr)(int type, char data[]);//执行shell命令TODO
typedef void (*SendExtraData_ptr)(char type[], char data[]);//执行shell命令 TODO
typedef void (*SetIsNeedHeadForUserData_ptr)(bool isNeedHead);//设置用户数据是否需要头部

//10 int 
typedef int (*OpenAdHocDevice_ptr)();//打开自组网设备 0:打开成功, 非0:打开失败
typedef int (*CloseAdHocDevice_ptr)();//关闭自组网设备
typedef int (*ReOpenAdHocDevice_ptr)();//重打开自组网设备
typedef int (*SetEnabled_ptr)(bool enabled);//设置数据传输模式，ip或非ip true :非ip模式，false :ip模式
typedef int (*SendData_ptr)( char data[]);//发送数据
typedef int (*SendData3_ptr)(char srcAddr[], char desAddr[], char data[]);//发送数据
//typedef int (*SendDataPri_ptr)(char srcAddr[],  char desAddr[],  char data[], int pri);//发送数据 TODO
typedef int (*SendDataPri_ptr)(char srcAddr[],  char desAddr[],  char data[], char pri[]);//发送数据
typedef int (*SendPcmVoice_ptr)(char voiceData[]);//发送话音数据
typedef int (*SetEthernetIP_ptr)(char ipAddr[]);//设置以太网ip
typedef int (*UpdateModem_ptr)(char fileName[], char data[]);//升级modem

//2 diff 
typedef ConfigParams (*GetConfigParams_ptr)();//获取平台信息
typedef char* (*GetEthernetIP_ptr)();//查询以太网ip

// 5 bool TODO
typedef bool (*IsEnabled_ptr)();//查询数据传输模式 
typedef bool (*IsNetWorkAvailable_ptr)();//网络是否可用
typedef bool (*AddDataRecvListener_ptr)(DataRecvCallback *pFunc);//添加接收数据回调监听器    
typedef bool (*AddNetWorkStatusListener_ptr)(NetWorkStatusCallback *pFunc);//添加网络状态回调监听器
typedef bool (*AddPcmVoiceListener_ptr)(PcmVoiceCallback *pFunc);//添加接收话音回调监听器


/////////////////////////////////////////////////// 

/*
 *void
 *[>int <]
 *addRecvDataListener(DataRecvCallback pCallBack)
 *{
 *    ADHOCLOG_SO("===register successed! waitting to call by peers === ");
 *    //call1 = pCallBack;
 *    char aa[] = "hello-";
 *    unsigned char bb[] = "world";
 *    pCallBack(aa,bb);
 *}
 *void
 *[>int <]
 *addNetWorkStatusListener(NetWorkStatusCallback pFunc)//添加网络状态回调监听器
 *{
 *    ADHOCLOG_SO("===register successed! waitting to call by peers === ");
 *    [>call2 =  pFunc;<]
 *    int aa = 110;
 *    char bb[] = "world";
 *    pFunc(aa,bb);
 *    [>return 1;<]
 *}
 *
 *void 
 *[>int <]
 *addPcmVoiceListener(PcmVoiceCallback pFunc)//添加接收话音回调监听器
 *{
 *    ADHOCLOG_SO("===register successed! waitting to call by peers === ");
 *    [>call3 =  pFunc;<]
 *    int aa = 110;
 *    char bb[] = "world";
 *    pFunc(aa,bb);
 *
 *    [>return 1;<]
 *}
 */
////////////////////////////////////////////////////////////////////////



///////////////////////////////////void////////////////////////////////////// 


void init(char paras[])
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//初始化自组网


void tellLocalIpAddr(char ipAddr[])
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//设置本机自组网ip


void queryNetWorkStatus(char cmd[])
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//查询网络状态


void setParameters(char paras[])
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//设置自组网参数


void setPttState (char state[])
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//设置ptt状态


void sendBDMsg2AdHoc(char  gga[])
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//发送北斗消息到自组网


void sendExtraData (int type, char data[])
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//执行shell命令


void setIsNeedHeadForUserData(bool isNeedHead)
{

ADHOCLOG_SO("====enter so====");
/*return 1;*/

}//设置用户数据是否需要头部


//////////////////////////////////int/////////////////////////////////////// 


int openAdHocDevice()
{

ADHOCLOG_SO("====enter so====");
return 1;

}//打开自组网设备 0:打开成功, 非0:打开失败


int closeAdHocDevice()
{

ADHOCLOG_SO("====enter so====");
return 1;

}//关闭自组网设备


int reOpenAdHocDevice()
{

ADHOCLOG_SO("====enter so====");
return 1;

}//重打开自组网设备


int setEnabled (bool enabled)
{

ADHOCLOG_SO("====enter so====");
return 1;

}//设置数据传输模式，ip或非ip true :非ip模式，false :ip模式


int sendData( char data[])
{

ADHOCLOG_SO("====enter so====");
return 1;

}//发送数据


int sendData3(char srcAddr[], char desAddr[], char data[])
{

ADHOCLOG_SO("====enter so====");
return 1;

}//发送数据


int sendDataPri(char srcAddr[],  char desAddr[],  char data[], int pri)
{

ADHOCLOG_SO("====enter so====");
return 1;

}//发送数据


int sendPcmVoice(char voiceData[])
{

ADHOCLOG_SO("====enter so====");
return 1;

}//发送话音数据


int setEthernetIP(char ipAddr[])
{

ADHOCLOG_SO("====enter so====");
return 1;

}//设置以太网ip


int updateModem(char fileName[], char data[])
{

ADHOCLOG_SO("====enter so====");
return 1;

}//升级modem

///////////////////////////////////char*////////////////////////////////////// 

ConfigParams getConfigParams()
{

ADHOCLOG_SO("====enter so====");
ConfigParams test;
return test;

}//获取平台信息


char* getEthernetIP()
{

ADHOCLOG_SO("====enter so====");
char* test = "hello im so,ip 192.168.110.110";
return test;

}//查询以太网ip


///////////////////////////////////bool////////////////////////////////////// 


bool isEnabled()
{

ADHOCLOG_SO("====enter so====");
return 1;

}//查询数据传输模式 


bool isNetWorkAvailable()
{

ADHOCLOG_SO("====enter so====");
return 1;

}//网络是否可用


bool addDataRecvListener(DataRecvCallback pFunc)
{

ADHOCLOG_SO("====enter so====");
ADHOCLOG_SO("===register successed! waitting to call by peers === ");
	//call1 = pCallBack;
	char aa[] = "hello-";
	unsigned char bb[] = "world";
	pFunc(aa,bb);

return 1;

}//添加接收数据回调监听器    


bool addNetWorkStatusListener(NetWorkStatusCallback pFunc)
{

ADHOCLOG_SO("====enter so====");
ADHOCLOG_SO("===register successed! waitting to call by peers === ");
	/*call2 =  pFunc;*/
	int aa = 110;
	char bb[] = "world";
	pFunc(aa,bb);

return 1;

}//添加网络状态回调监听器


bool addPcmVoiceListener(PcmVoiceCallback pFunc)
{

ADHOCLOG_SO("====enter so====");
ADHOCLOG_SO("===register successed! waitting to call by peers === ");
	/*call3 =  pFunc;*/
	int aa = 110;
	char bb[] = "world";
	pFunc(aa,bb);

return 1;

}//添加接收话音回调监听器



///////////////////////////////////////////////////////////////////////// 
/**
  @param srcAddr 源ip
  @param desAddr 目的ip
  @param data 数据内容
 **/
/*
 *typedef int (*DataRecvCallback)(char *srcAddr, unsigned char *pData);
 *typedef int (*NetWorkStatusCallback)(int statusType, char *pParam);
 *typedef int (*PcmVoiceCallback)(int statusType, char *pParam);
 *
 *struct{
 *    char mPlatform[32];
 *    char mUEKind[32];
 *    char mHW[32];
 *    char mOS[32];
 *    int mType;
 *}ConfigParams;
 *
 *
 *void init(char paras[]);//初始化自组网
 *void tellLocalIpAddr(char ipAddr[]);//设置本机自组网ip
 *void queryNetWorkStatus(char cmd[]);//查询网络状态
 *void setParameters(char paras[]);//设置自组网参数
 *void setPttState (char state[]);//设置ptt状态
 *void sendBDMsg2AdHoc(char  gga[]);//发送北斗消息到自组网
 *void sendExtraData (int type, char data[]);//执行shell命令
 *void setIsNeedHeadForUserData(bool isNeedHead);//设置用户数据是否需要头部
 *
 *
 *int openAdHocDevice();//打开自组网设备 0:打开成功, 非0:打开失败
 *int closeAdHocDevice();//关闭自组网设备
 *int reOpenAdHocDevice();//重打开自组网设备
 *int setEnabled (bool enabled);//设置数据传输模式，ip或非ip true :非ip模式，false :ip模式
 *int sendData( char data[]);//发送数据
 *int sendData3(char srcAddr[], char desAddr[], char data[]);//发送数据
 *int sendDataPri(char srcAddr[],  char desAddr[],  char data[], int pri);//发送数据
 *int sendPcmVoice(char voiceData[]);//发送话音数据
 *int setEthernetIP(char ipAddr[]);//设置以太网ip
 *int updateModem(char fileName[], char data[]);//升级modem
 *
 *
 *ConfigParams getConfigParams();//获取平台信息
 *char* getEthernetIP();//查询以太网ip
 *bool isEnabled();//查询数据传输模式 
 *bool isNetWorkAvailable();//网络是否可用
 *bool addDataRecvListener(DataRecvCallback *pFunc);//添加接收数据回调监听器    
 *bool addNetWorkStatusListener(NetWorkStatusCallback *pFunc);//添加网络状态回调监听器
 *bool addPcmVoiceListener(PcmVoiceCallback *pFunc);//添加接收话音回调监听器
 *
 */

///////////////////////////////////////////////////////////////////////// 

