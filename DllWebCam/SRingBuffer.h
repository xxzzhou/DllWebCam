/***************************************************************/
//Copyright(c) 2018, Xiang Zhao
//All rights reserved.
//
//Time:   2018.05.05
//Writer: Xiang Zhao
//
//Function：一般作为实时系统中模块接口处的数据缓冲区，提供基本的数据读写操作，
//          没有添加互斥锁，非线程安全
//
//Modified: No
//
/***************************************************************/
//应用示例：
//1. 用于线程间的数据传输
//2. 用于网络接收缓冲，unsafeMode和GetNndElePtr组合可实现重传和超时检测
//3. MoveReadPos()可实现数据前向搜索，在卷积、延时对齐时可以使用
/***************************************************************/

#ifndef _SRINGBUFFER_H_
#define _SRINGBUFFER_H_

#include "Symbol.h"

typedef struct
{
	uint m_eleMaxNum; //缓冲区最大元素个数
	uint m_eleSize;   //缓冲区中元素大小Byte
	int  m_readPos;
	int  m_writePos;

	bool m_isWrap;    //环形缓冲读写头可能存在卷绕

	void* m_buf;
}SRingBuffer;

SRingBuffer* SRingBufferCalloc(const uint eleMaxNum, const uint eleSize);
void SRingBufferFree(SRingBuffer* pBuffer);

//查询当前缓冲区中已存元素个数
uint GetCurEleNum(SRingBuffer* pBuffer);

//获取缓冲区第n个元素的首地址
void* GetNndElePtr(SRingBuffer* pBuffer, uint n);

//读取eleNum个元素，并更新读头，返回成功读取的元素个数
uint Read(SRingBuffer* pBuffer, void* const dstMem, const uint eleNum);

//写入eleNum个元素，并更新写头，返回成功写入的元素个数
//safeMode为true:  写入元素个数不能超过空闲元素个数；
//safeMode为false: 写入元素个数可以超过空闲元素数，但不能超过缓冲区最大元素个数
//                 写入数据可能会覆盖未读的旧数据，
uint Write(SRingBuffer* pBuffer, const void* const srcMem, const uint eleNum, bool safeMode);

//强制移动读头位置，step为正向后移动，忽略较早的数据；
//step为负向前移动，如果之前的数据没有覆盖，则恢复前面的数据
int MoveReadPos(SRingBuffer* pBuffer, const int step);

//强制移动写头位置，step为正向后移动，移动过的位置全部置0；
//step为负向前移动，忽略最后写入的数据
int MoveWritePos(SRingBuffer* pBuffer, const int step);
//**************************************************************
//环形缓冲的4种状态
//
//  |---------------------|   warp == false, 缓冲区空
//      ↑
//      RW
//  |---------------------|   warp == true,  缓冲区满
//      ↑
//      WR
//  |---------------------|   warp == false, 缓冲区未满
//      ↑        ↑
//      R        W
//  |---------------------|   warp == true,  缓冲区未满
//      ↑        ↑
//      W        R
//
//**************************************************************
#endif