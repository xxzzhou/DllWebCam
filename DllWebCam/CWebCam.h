#pragma once
/*
* ժ Ҫ��
* ���ļ�����CWebCam�࣬�������������ƵIO��һ�����࣬�ڱ�ϵͳ��������������ͷ�����ݽ��вɼ�����Ⱦ
*
* ��ǰ�汾��1.0
* �� �ߣ��ܿ³�ӱ
* ������ڣ�
*
* ȡ���汾��
* ԭ���� ��
* ������ڣ�
*/


/*
* �����ʶ��˵��
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
#include <opencv2/core/core.hpp>     //OpenCV����ͷ�ļ�  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/opencv.hpp>  

using namespace cv;
using namespace std;

extern volatile unsigned int curPlayNo;
extern volatile unsigned int playWaitCount;

//class CWebCam : public CVideoDeviceIO     //�̳�
class CWebCam 
{
public:
	CWebCam();
	~CWebCam();

	VideoCapture capture;
	cv::Mat frame;
	//AVPacket pkt; //�洢ѹ����İ�
	
	//bool WebCam_LoadInit();
	//bool WebCam_UserSet();
	//bool WebCam_Start();
	//bool WebCam_Stop();   //δʵ��
	bool WebCam_Release();

	//double  WebCam_GetFrameRate();     //��ȡ֡�ʣ��ɹ�����֡�ʣ�ʧ�ܷ���-1��
	//int     WebCam_GetBufferSize();                       //��ȡÿ֡��С(�Բ�����Ϊ��λ)���ɹ����ػ�������С��ʧ�ܷ���-1��
	//int     WebCam_GetAvailableCaptureResolutionRratioHeight();          //��ȡ����¼�������������ɹ����ؿ���¼������������ʧ�ܷ���-1��
	//int     WebCam_GetAvailableCaptureResolutionRratioWidth();           //��ȡ���ò��������������ɹ����ؿ��ò�������������ʧ�ܷ���-1��
	//int     WebCam_GetAvailableShowResolutionRratioHeight();            //��ȡ�����¼�������������ɹ����������¼������������ʧ�ܷ���-1��
	//int     WebCam_GetAvailableShowResolutionRratioWidth();            //��ȡ����Ĳ��������������ɹ���������Ĳ�������������ʧ�ܷ���-1��
	//int     WebCam_GetDigitalizingBit();                            //��ȡ����λ�����ɹ���������λ����ʧ�ܷ���-1��

	int   WebCam_ListInitWebCamDevice(vector<string>& list);        //��õ�ǰ����ͷ����

																	/*
																	**���ü��㺯�����ú����Ĳ����Ǹ�����ָ�룬��������ָ���ԭ�����£�
																	**playChannel[]����������ô�������ݵĻ������׵�ַ��ÿ��ͨ����Ӧһ�������±�
																	**recordChannel[]�����������δ�������ݵĻ������׵�ַ��ÿ��ͨ����Ӧһ�������±�
																	**bufferSize��ÿ������ÿ֡��С
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