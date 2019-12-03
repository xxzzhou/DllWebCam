#pragma once
/*
* 摘 要：
* 本文件包含CWebCam类，是整个框架中视频IO的一个子类，在本系统中用于网络摄像头的数据进行采集和渲染
*
* 当前版本：1.0
* 作 者：周柯辰颖
* 完成日期：
*
* 取代版本：
* 原作者 ：
* 完成日期：
*/


/*
* 特殊标识符说明
*/
#ifndef _CWebCam_H_
#define _CWebCam_H_

#include <conio.h>
//#include <queue>
//#include <Windows.h>
#include <vector>
//#include <string>
#include <stdint.h> 

#include "CVideoDeviceIO.h"
#include <opencv2/core/core.hpp>     //OpenCV包含头文件  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/opencv.hpp>  

using namespace cv;
using namespace std;

extern volatile unsigned int curPlayNo;
extern volatile unsigned int playWaitCount;

//class CWebCam : public CVideoDeviceIO     //继承
class CWebCam 
{
public:
	CWebCam();
	~CWebCam();

	VideoCapture capture;
	cv::Mat frame;
	//AVPacket pkt; //存储压缩后的包
	
	//bool WebCam_LoadInit();
	//bool WebCam_UserSet();
	//bool WebCam_Start();
	//bool WebCam_Stop();   //未实现
	bool WebCam_Release();

	//double  WebCam_GetFrameRate();     //获取帧率，成功返回帧率，失败返回-1；
	//int     WebCam_GetBufferSize();                       //获取每帧大小(以采样点为单位)，成功返回缓冲区大小，失败返回-1；
	//int     WebCam_GetAvailableCaptureResolutionRratioHeight();          //获取可用录音声道数量，成功返回可用录音声道数量，失败返回-1；
	//int     WebCam_GetAvailableCaptureResolutionRratioWidth();           //获取可用播放声道数量，成功返回可用播放声道数量，失败返回-1；
	//int     WebCam_GetAvailableShowResolutionRratioHeight();            //获取申请的录音声道数量，成功返回申请的录音声道数量，失败返回-1；
	//int     WebCam_GetAvailableShowResolutionRratioWidth();            //获取申请的播放声道数量，成功返回申请的播放声道数量，失败返回-1；
	//int     WebCam_GetDigitalizingBit();                            //获取量化位数，成功返回量化位数，失败返回-1；

	int   WebCam_ListInitWebCamDevice(vector<string>& list);        //获得当前摄像头名称

																	/*
																	**设置计算函数，该函数的参数是个函数指针，参数函数指针的原型如下：
																	**playChannel[]：该数组放置处理后数据的缓冲区首地址，每个通道对应一个数组下标
																	**recordChannel[]：该数组放置未处理数据的缓冲区首地址，每个通道对应一个数组下标
																	**bufferSize：每个声道每帧大小
																	*/
	void WebCam_Encoder();
	void WebCam_Decoder();


	//void   WebCam_SetComputeFunc();

//private:
//	double           frameRate;
//	static long      bufferSize;
//	//long             minSize;
//	//long             maxSize;
//	long             granularity;
//	static long      availableRecordChannelNum;
//	static long      availablePlayChannelNum;
//	static int       digitalizingBit;
//	static int       recordChannelNum;
//	static int       playChannelNum;

	//bool             create_asio_buffers();
	//static ASIOTime* bufferSwitchTimeInfo(ASIOTime *timeInfo, long index, ASIOBool processNow);
	//static void      bufferSwitch(long index, ASIOBool processNow);
	//static void      sampleRateChanged(ASIOSampleRate sRate);
	//static long      asioMessages(long selector, long value, void* message, double* opt);
	//static void      readbuf(void  *p, int buffsize, int inchannelindex);
	//static void      writebuf(void  *p, int buffsize, int outchannelindex);

	/*ASIODriverInfo           driverInfo;
	static ASIOBufferInfo    bufferInfos[kMaxInputChannels + kMaxOutputChannels];
	ASIOChannelInfo          channelInfos[kMaxInputChannels + kMaxOutputChannels];*/

public:

	//// Open ASIO4ALL control panel Note that only ASIO4ALL driver is supported
	//void ASIO4ALLControlPanel(char* drvName, int drvNameLe

	void WebCamInitialize();
	void WebCamRun();
	///*int WebCamEnd();

	void Wait();
};

#endif