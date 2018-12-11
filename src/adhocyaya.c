#include <stdio.h>
/*#include "adhocyaya.h"*/
#include <unistd.h> 
#include <android/log.h>
/*#include "utils/Log.h"*/
#define ADHOCLOG_SO(fmt, ...) __android_log_print(ANDROID_LOG_WARN, "Adhoc_SO", "%12s:%-5d,%s ," fmt, __FILE__, __LINE__ ,(char*)__FUNCTION__,##__VA_ARGS__)

/*#define  LOG_TAG    "libplasma"*/
/*#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)*/
/*static char mark_label[64] = "yourlog-";*/
/*#define ADHOCLOG_SO(fmt, ...) ALOGI("[%s],tid:%u,%s,F:%s:%d,Fun:%s " fmt,"", (unsigned int)gettid(),mark_label,(char*)__FILE__,__LINE__,(char*)__FUNCTION__,##__VA_ARGS__)*/

typedef void(*PF)();
PF g_pf = NULL;


typedef int (*DataRecvCallback)(char *srcAddr, unsigned char *pData);
typedef int (*NetWorkStatusCallback)(int statusType, char *pParam);
typedef int (*PcmVoiceCallback)(int statusType, char *pParam);

DataRecvCallback call1 = NULL;
NetWorkStatusCallback call2 = NULL;
PcmVoiceCallback  call3 = NULL;




int add(int a, int b)
{
    return (a + b);
}
 
int subtract(int a, int b)
{
    return (a - b);
}
 
int multiply(int a, int b)
{
    return (a * b);
}
 
int divide(int a, int b)
{
    return (a / b);
}



void init(char paras[])//初始化自组网
 {
     /*char paras[] = "testfunc"; */
     /*paras[0] = "testfunc"; */
     ADHOCLOG_SO("===init===%s",paras);
 }
 
 
/**********************************/
// B模块
 
// B模块向外提供的回调函数注册接口， 也就是说，提供注册服务， 想注册的，调用该接口即可
void registerFun(PF pf)
{
     ADHOCLOG_SO("===register successed! waitting to call by peers === ");
	g_pf = pf;
}


/*void*/
int 
addrecvdatalistener(DataRecvCallback pCallBack)
{
     ADHOCLOG_SO("===register successed! waitting to call by peers === ");
     call1 = pCallBack;
    /*sleep(5);*/
    /*char* aaa = "hello";*/
    /*unsigned char* bbb = "world";*/
    /*pCallBack(11,22);*/
    /*pCallBack(aaa,bbb);*/
    return 1;
}
/*void*/
int 
addNetWorkStatusListener(NetWorkStatusCallback pFunc)//添加网络状态回调监听器
{
     ADHOCLOG_SO("===register successed! waitting to call by peers === ");
     call2 =  pFunc;
    return 1;
}

/*void */
int 
addPcmVoiceListener(PcmVoiceCallback pFunc)//添加接收话音回调监听器
{
     ADHOCLOG_SO("===register successed! waitting to call by peers === ");
     call3 =  pFunc;
    return 1;
}

// B模块的某函数， 在一定条件下被触发
void fun()
{
	// 执行别的模块注册过来的回调函数
     ADHOCLOG_SO("=== call callback func from  ==== ");
	(*g_pf)(); // or g_pf();
}
 
/**********************************/
 









/*
 *void init(char paras[])//初始化自组网
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *int openAdHocDevice()//打开自组网设备 0:打开成功, 非0:打开失败
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *int setEnabled (bool enabled)//设置数据传输模式，ip或非ip true :非ip模式，false :ip模式
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *bool isEnabled()//查询数据传输模式 
 *{
 *    ADHOCLOG_SO("===init===");
 *    return true;
 *}
 *
 *bool isNetWorkAvailable()//网络是否可用
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *int sendData( char data[])//发送数据
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 */


/**
@param srcAddr 源ip
@param desAddr 目的ip
@param data 数据内容
**/
/*
 *int sendData(char srcAddr[], char desAddr[], byte data[])//发送数据
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 */


/*
 *int sendDataPri(char srcAddr[],  char desAddr[],  char data[], int pri)//发送数据
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *void tellLocalIpAddr(char ipAddr[])//设置本机自组网ip
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *void queryNetWorkStatus(char cmd[])//查询网络状态
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *int sendPcmVoice(char voiceData[])//发送话音数据
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *void setParameters(char paras[])//设置自组网参数
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *void setPttState (char state[])//设置ptt状态
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *void sendBDMsg2AdHoc(char  gga[])//发送北斗消息到自组网
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 */
/*
 *
 *void sendExtraData (int type, char data[])//执行shell命令
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *void setIsNeedHeadForUserData(bool isNeedHead)//设置用户数据是否需要头部
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *    
 *int setEthernetIP(char ipAddr[])//设置以太网ip
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *char* getEthernetIP()//查询以太网ip
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *    
 *int closeAdHocDevice()//关闭自组网设备
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *int reOpenAdHocDevice()//重打开自组网设备
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 */

/*
 *    
 *bool addDataRecvListener(DataRecvCallback *pFunc)//添加接收数据回调监听器    
 *{
 *    ADHOCLOG_SO("===sleep 5 then return===");
 *    sleep(5);
 *    return true;
 *}
 *
 *bool addNetWorkStatusListener(NetWorkStatusCallback *pFunc)//添加网络状态回调监听器
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *bool addPcmVoiceListener(PcmVoiceCallback *pFunc)//添加接收话音回调监听器
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *    
 *ConfigParams getConfigParams()//获取平台信息
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 *
 *int updateModem(char fileName[], in char data[])//升级modem
 *{
 *    ADHOCLOG_SO("===init===");
 *}
 */





