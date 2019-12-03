/***************************************************************/
//Copyright(c) 2018, Xiang Zhao
//All rights reserved.
//
//Time:   2018.05.05
//Writer: Xiang Zhao
//
//Function��һ����Ϊʵʱϵͳ��ģ��ӿڴ������ݻ��������ṩ���������ݶ�д������
//          û����ӻ����������̰߳�ȫ
//
//Modified: No
//
/***************************************************************/
//Ӧ��ʾ����
//1. �����̼߳�����ݴ���
//2. ����������ջ��壬unsafeMode��GetNndElePtr��Ͽ�ʵ���ش��ͳ�ʱ���
//3. MoveReadPos()��ʵ������ǰ���������ھ������ʱ����ʱ����ʹ��
/***************************************************************/

#ifndef _SRINGBUFFER_H_
#define _SRINGBUFFER_H_

#include "Symbol.h"

typedef struct
{
	uint m_eleMaxNum; //���������Ԫ�ظ���
	uint m_eleSize;   //��������Ԫ�ش�СByte
	int  m_readPos;
	int  m_writePos;

	bool m_isWrap;    //���λ����дͷ���ܴ��ھ���

	void* m_buf;
}SRingBuffer;

SRingBuffer* SRingBufferCalloc(const uint eleMaxNum, const uint eleSize);
void SRingBufferFree(SRingBuffer* pBuffer);

//��ѯ��ǰ���������Ѵ�Ԫ�ظ���
uint GetCurEleNum(SRingBuffer* pBuffer);

//��ȡ��������n��Ԫ�ص��׵�ַ
void* GetNndElePtr(SRingBuffer* pBuffer, uint n);

//��ȡeleNum��Ԫ�أ������¶�ͷ�����سɹ���ȡ��Ԫ�ظ���
uint Read(SRingBuffer* pBuffer, void* const dstMem, const uint eleNum);

//д��eleNum��Ԫ�أ�������дͷ�����سɹ�д���Ԫ�ظ���
//safeModeΪtrue:  д��Ԫ�ظ������ܳ�������Ԫ�ظ�����
//safeModeΪfalse: д��Ԫ�ظ������Գ�������Ԫ�����������ܳ������������Ԫ�ظ���
//                 д�����ݿ��ܻḲ��δ���ľ����ݣ�
uint Write(SRingBuffer* pBuffer, const void* const srcMem, const uint eleNum, bool safeMode);

//ǿ���ƶ���ͷλ�ã�stepΪ������ƶ������Խ�������ݣ�
//stepΪ����ǰ�ƶ������֮ǰ������û�и��ǣ���ָ�ǰ�������
int MoveReadPos(SRingBuffer* pBuffer, const int step);

//ǿ���ƶ�дͷλ�ã�stepΪ������ƶ����ƶ�����λ��ȫ����0��
//stepΪ����ǰ�ƶ����������д�������
int MoveWritePos(SRingBuffer* pBuffer, const int step);
//**************************************************************
//���λ����4��״̬
//
//  |---------------------|   warp == false, ��������
//      ��
//      RW
//  |---------------------|   warp == true,  ��������
//      ��
//      WR
//  |---------------------|   warp == false, ������δ��
//      ��        ��
//      R        W
//  |---------------------|   warp == true,  ������δ��
//      ��        ��
//      W        R
//
//**************************************************************
#endif