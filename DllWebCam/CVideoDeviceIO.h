#pragma once
/*
* 摘 要：
* 本文件包含CVideoDeviceIO类，是整个框架中视频IO的父类，保存视频IO中公共的属性和方法，
* 该类中不能包含与平台相关的API和变量，保证可移植性。
*
* 当前版本：1.0
* 作 者：周柯辰颖
* 完成日期：
*
* 取代版本：
* 原作者 ：
* 完成日期：
*/


#ifndef _CVIDEODEVICEIO_H_
#define _CVIDEODEVICEIO_H_

#include <Windows.h>
#include "SRingBuffer.h"     //环形缓冲区

#define PER_BUFFER_SIZE 96000        //????大小为什么为96000

class  CVideoDeviceIO
{
public:
	unsigned int   m_captureFrameRate;                  //采样率   ??帧率
	unsigned short m_captureDigitalizingBits;           //量化位数
	unsigned short m_captureResolutionRratioHeight;     //图像分辨率高  区别于显示分辨率
	unsigned short m_captureResolutionRratioWidth;      //图像分辨率宽  区别于显示分辨率

	unsigned int   m_showFrameRate;
	unsigned short m_showDigitalizingBits;
	unsigned short m_showResolutionRratioHeight;     //图像分辨率高  区别于显示分辨率
	unsigned short m_showResolutionRratioWidth;      //图像分辨率宽  区别于显示分辨率    

	static CRITICAL_SECTION* m_captureBufferLock;    //互斥??
	static CRITICAL_SECTION* m_showBufferLock;

	static SRingBuffer* m_captureBuffer;
	static SRingBuffer* m_showBuffer;


public:
	CVideoDeviceIO(
		unsigned int   captureFrameRate,
		unsigned short captureDigitalizingBits,
		unsigned short captureResolutionRratioHeight,
		unsigned short captureResolutionRratioWidth,
		unsigned int   showFrameRate,
		unsigned short showDigitalizingBits,
		unsigned short showResolutionRratioHeight,
		unsigned short showResolutionRratioWidth
	);
	~CVideoDeviceIO();       //析构函数
	bool GetVideoData(void* destMem, const unsigned int nSample);//nSampleSize为获取数据的采样点数
	bool SetVideoData(void* sourMem, const unsigned int nSample);//nSampleSize为置入数据的采样点数
	void CleanVideoData();
	virtual void Wait() = 0;
};

#endif


//需要写完其他类再更改的变量：GetVideoData: nSample   SetVideoData: nSample 
//                            PER_BUFFER_SIZE   destMem   sourMem