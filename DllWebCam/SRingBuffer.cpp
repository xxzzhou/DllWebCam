#include "SRingBuffer.h"

#include <stdlib.h>
#include <memory.h>
#include <assert.h>

SRingBuffer* SRingBufferCalloc(const uint eleMaxNum, const uint eleSize)		 //分配缓冲区内存
{
	SRingBuffer* temp = (SRingBuffer*)malloc(sizeof(SRingBuffer));
	if (NULL == temp)
	{
		return NULL;
	}
	temp->m_eleMaxNum = eleMaxNum;
	temp->m_eleSize = eleSize;
	temp->m_readPos = 0;
	temp->m_writePos = 0;

	temp->m_isWrap = false;

	temp->m_buf = malloc(eleMaxNum*eleSize);
	if (NULL == temp->m_buf)
	{
		free(temp);
		return NULL;
	}
	memset(temp->m_buf, 0, eleMaxNum*eleSize);
	return temp;
}
void SRingBufferFree(SRingBuffer* pBuffer)               //释放缓冲区内存
{
	free(pBuffer->m_buf);
	pBuffer->m_buf = NULL;
	free(pBuffer);
	pBuffer = NULL;
}

uint GetCurEleNum(SRingBuffer* pBuffer)
{
	uint num = 0;
	if (false == pBuffer->m_isWrap)
	{
		num = (uint)(pBuffer->m_writePos - pBuffer->m_readPos);
	}
	else
	{
		num = (uint)(pBuffer->m_writePos - pBuffer->m_readPos + pBuffer->m_eleMaxNum);
	}
	return num;
}
void* GetNndElePtr(SRingBuffer* pBuffer, uint n)
{
	uint ans = GetCurEleNum(pBuffer);

	if (n >= ans || 0 == ans)
	{
		return NULL;
	}
	int nPos = pBuffer->m_readPos + n;
	if (nPos >= (int)pBuffer->m_eleMaxNum)
	{
		nPos -= pBuffer->m_eleMaxNum;
	}
	return (void*)((byte*)pBuffer->m_buf + nPos*pBuffer->m_eleSize);
}
uint Read(SRingBuffer* pBuffer, void* const dstMem, const uint eleNum)
{
	byte* ptr = (byte*)pBuffer->m_buf + pBuffer->m_readPos*pBuffer->m_eleSize;

	uint curEleNum = GetCurEleNum(pBuffer);
	uint getEleNum = MIN(eleNum, curEleNum);

	int firstPart = MIN((int)pBuffer->m_eleMaxNum - pBuffer->m_readPos, (int)getEleNum);
	int secondPart = MAX((int)getEleNum - firstPart, 0);

	if (firstPart > 0)
	{
		memcpy(dstMem, ptr, firstPart*pBuffer->m_eleSize);
	}
	if (secondPart > 0)
	{
		memcpy((byte*)dstMem + firstPart*pBuffer->m_eleSize,
			pBuffer->m_buf, secondPart*pBuffer->m_eleSize);
	}
	pBuffer->m_readPos += getEleNum;
	if (pBuffer->m_readPos >= (int)pBuffer->m_eleMaxNum)
	{
		pBuffer->m_readPos -= pBuffer->m_eleMaxNum;
		pBuffer->m_isWrap = false;
	}
	return getEleNum;
}
uint Write(SRingBuffer* pBuffer, const void* const srcMem, const uint eleNum, bool safeMode)
{
	byte* ptr = (byte*)pBuffer->m_buf + pBuffer->m_writePos*pBuffer->m_eleSize;

	uint curFreeNum = 0;
	uint setEleNum = 0;
	int  firstPart = 0;
	int  secondPart = 0;

	curFreeNum = pBuffer->m_eleMaxNum - GetCurEleNum(pBuffer);
	if (safeMode)
	{
		if (eleNum > curFreeNum)
		{
			//            assert(false);
			return 0;
		}
	}
	else
	{
		if (eleNum > pBuffer->m_eleMaxNum)
		{
			//            assert(false);
			return 0;
		}
	}
	setEleNum = eleNum;

	firstPart = MIN((int)pBuffer->m_eleMaxNum - pBuffer->m_writePos, (int)setEleNum);
	secondPart = MAX((int)setEleNum - firstPart, 0);
	if (firstPart > 0)
	{
		memcpy(ptr, srcMem, firstPart*pBuffer->m_eleSize);
	}
	if (secondPart > 0)
	{
		memcpy(pBuffer->m_buf, (byte*)srcMem + firstPart*pBuffer->m_eleSize,
			secondPart*pBuffer->m_eleSize);
	}
	pBuffer->m_writePos += setEleNum;

	if (setEleNum > curFreeNum)
	{
		if (pBuffer->m_writePos >= (int)pBuffer->m_eleMaxNum)
		{
			pBuffer->m_writePos -= pBuffer->m_eleMaxNum;
		}
		pBuffer->m_readPos = pBuffer->m_writePos;
		pBuffer->m_isWrap = true;
	}
	else
	{
		if (pBuffer->m_writePos >= (int)pBuffer->m_eleMaxNum)
		{
			pBuffer->m_writePos -= pBuffer->m_eleMaxNum;
			pBuffer->m_isWrap = true;
		}
	}
	return setEleNum;
}
int MoveReadPos(SRingBuffer* pBuffer, const int step)
{
	int  moveStep = 0;
	uint curFreeNum = 0U;
	uint curEleNum = 0U;

	if (step < 0)//向前移动，恢复数据
	{
		curFreeNum = pBuffer->m_eleMaxNum - GetCurEleNum(pBuffer);
		moveStep = MAX(-(int)curFreeNum, step);
		pBuffer->m_readPos += moveStep;
		if (pBuffer->m_readPos < 0)
		{
			pBuffer->m_readPos += pBuffer->m_eleMaxNum;
			pBuffer->m_isWrap = true;
		}
	}
	if (step > 0)//向后移动，删除数据
	{
		curEleNum = GetCurEleNum(pBuffer);
		moveStep = MIN((int)curEleNum, step);
		pBuffer->m_readPos += moveStep;
		if (pBuffer->m_readPos >= (int)pBuffer->m_eleMaxNum)
		{
			pBuffer->m_readPos -= pBuffer->m_eleMaxNum;
			pBuffer->m_isWrap = false;
		}
	}
	return moveStep;
}
int MoveWritePos(SRingBuffer* pBuffer, const int step)
{
	int  moveStep = 0;
	uint curFreeNum = 0U;
	uint curEleNum = 0U;

	if (step < 0)//向前移动，删除最新数据
	{
		curEleNum = GetCurEleNum(pBuffer);
		moveStep = MAX(-(int)curEleNum, step);
		pBuffer->m_writePos += moveStep;
		if (pBuffer->m_writePos < 0)
		{
			pBuffer->m_writePos += pBuffer->m_eleMaxNum;
			pBuffer->m_isWrap = false;
		}
	}
	if (step > 0)//向后移动，插入0值
	{
		curFreeNum = pBuffer->m_eleMaxNum - GetCurEleNum(pBuffer);
		moveStep = MIN((int)curFreeNum, step);
		pBuffer->m_writePos += moveStep;
		if (pBuffer->m_writePos >= (int)pBuffer->m_eleMaxNum)
		{
			pBuffer->m_writePos -= pBuffer->m_eleMaxNum;
			pBuffer->m_isWrap = true;
		}
	}
	return moveStep;
}