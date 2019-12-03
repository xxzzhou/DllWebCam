#pragma once
/*
* ժ Ҫ��
* ���ļ�����CVideoDeviceIO�࣬�������������ƵIO�ĸ��࣬������ƵIO�й��������Ժͷ�����
* �����в��ܰ�����ƽ̨��ص�API�ͱ�������֤����ֲ�ԡ�
*
* ��ǰ�汾��1.0
* �� �ߣ��ܿ³�ӱ
* ������ڣ�
*
* ȡ���汾��
* ԭ���� ��
* ������ڣ�
*/


#ifndef _CVIDEODEVICEIO_H_
#define _CVIDEODEVICEIO_H_

#include <Windows.h>
#include "SRingBuffer.h"     //���λ�����

#define PER_BUFFER_SIZE 96000        //????��СΪʲôΪ96000

class  CVideoDeviceIO
{
public:
	unsigned int   m_captureFrameRate;                  //������   ??֡��
	unsigned short m_captureDigitalizingBits;           //����λ��
	unsigned short m_captureResolutionRratioHeight;     //ͼ��ֱ��ʸ�  ��������ʾ�ֱ���
	unsigned short m_captureResolutionRratioWidth;      //ͼ��ֱ��ʿ�  ��������ʾ�ֱ���

	unsigned int   m_showFrameRate;
	unsigned short m_showDigitalizingBits;
	unsigned short m_showResolutionRratioHeight;     //ͼ��ֱ��ʸ�  ��������ʾ�ֱ���
	unsigned short m_showResolutionRratioWidth;      //ͼ��ֱ��ʿ�  ��������ʾ�ֱ���    

	static CRITICAL_SECTION* m_captureBufferLock;    //����??
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
	~CVideoDeviceIO();       //��������
	bool GetVideoData(void* destMem, const unsigned int nSample);//nSampleSizeΪ��ȡ���ݵĲ�������
	bool SetVideoData(void* sourMem, const unsigned int nSample);//nSampleSizeΪ�������ݵĲ�������
	void CleanVideoData();
	virtual void Wait() = 0;
};

#endif


//��Ҫд���������ٸ��ĵı�����GetVideoData: nSample   SetVideoData: nSample 
//                            PER_BUFFER_SIZE   destMem   sourMem