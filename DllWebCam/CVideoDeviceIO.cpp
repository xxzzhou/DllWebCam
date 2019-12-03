#include "CVideoDeviceIO.h"

#include <assert.h>


CRITICAL_SECTION* CVideoDeviceIO::m_captureBufferLock = nullptr;          //临界区
CRITICAL_SECTION* CVideoDeviceIO::m_showBufferLock = nullptr;
SRingBuffer*      CVideoDeviceIO::m_captureBuffer = nullptr;             //模块接口处的数据缓冲区
SRingBuffer*      CVideoDeviceIO::m_showBuffer = nullptr;

CVideoDeviceIO::CVideoDeviceIO
(
	unsigned int   captureFrameRate,
	unsigned short captureDigitalizingBits,
	unsigned short captureResolutionRratioHeight,
	unsigned short captureResolutionRratioWidth,
	unsigned int   showFrameRate,
	unsigned short showDigitalizingBits,
	unsigned short showResolutionRratioHeight,
	unsigned short showResolutionRratioWidth
)
{
	this->m_captureFrameRate = captureFrameRate;
	this->m_captureDigitalizingBits = captureDigitalizingBits;
	this->m_captureResolutionRratioHeight = captureResolutionRratioHeight;
	this->m_captureResolutionRratioWidth = captureResolutionRratioWidth;

	this->m_showFrameRate = showFrameRate;
	this->m_showDigitalizingBits = showDigitalizingBits;
	this->m_showResolutionRratioHeight = showResolutionRratioHeight;
	this->m_showResolutionRratioWidth = showResolutionRratioWidth;

	if (nullptr == CVideoDeviceIO::m_captureBufferLock)
	{
		CVideoDeviceIO::m_captureBufferLock = new CRITICAL_SECTION;
		InitializeCriticalSection(CVideoDeviceIO::m_captureBufferLock);
	}
	if (nullptr == CVideoDeviceIO::m_captureBufferLock)
	{
		CVideoDeviceIO::m_showBufferLock = new CRITICAL_SECTION;
		InitializeCriticalSection(CVideoDeviceIO::m_showBufferLock);
	}
	if (nullptr == CVideoDeviceIO::m_captureBuffer)
	{                                                          //缓冲区最大元素个数   元素大小
		CVideoDeviceIO::m_captureBuffer = SRingBufferCalloc(PER_BUFFER_SIZE,
			captureDigitalizingBits*captureResolutionRratioHeight*captureResolutionRratioWidth / 8);
	}
	if (nullptr == CVideoDeviceIO::m_showBuffer)
	{
		CVideoDeviceIO::m_showBuffer = SRingBufferCalloc(PER_BUFFER_SIZE,
			showDigitalizingBits*showResolutionRratioHeight*showResolutionRratioWidth / 8);
	}
}

CVideoDeviceIO::~CVideoDeviceIO()
{
	if (nullptr != CVideoDeviceIO::m_captureBufferLock)
	{
		DeleteCriticalSection(CVideoDeviceIO::m_captureBufferLock);
		CVideoDeviceIO::m_captureBufferLock = nullptr;
	}
	if (nullptr != CVideoDeviceIO::m_captureBufferLock)
	{
		DeleteCriticalSection(CVideoDeviceIO::m_captureBufferLock);
		CVideoDeviceIO::m_captureBufferLock = nullptr;
	}
	if (nullptr != CVideoDeviceIO::m_captureBuffer)
	{
		SRingBufferFree(CVideoDeviceIO::m_captureBuffer);
	}
	if (nullptr != CVideoDeviceIO::m_showBuffer)
	{
		SRingBufferFree(CVideoDeviceIO::m_showBuffer);
	}
}


bool CVideoDeviceIO::GetVideoData(void* destMem, const unsigned int nSample)
{
	EnterCriticalSection(CVideoDeviceIO::m_captureBufferLock);
	while (GetCurEleNum(CVideoDeviceIO::m_captureBuffer) < nSample)
	{
		LeaveCriticalSection(CVideoDeviceIO::m_captureBufferLock);
		this->Wait();
		EnterCriticalSection(CVideoDeviceIO::m_captureBufferLock);
	}
	Read(CVideoDeviceIO::m_captureBuffer, destMem, nSample);
	LeaveCriticalSection(CVideoDeviceIO::m_captureBufferLock);
	return true;
}


bool CVideoDeviceIO::SetVideoData(void* sourMem, const unsigned int nSample)
{
	EnterCriticalSection(CVideoDeviceIO::m_showBufferLock);
	Write(CVideoDeviceIO::m_showBuffer, sourMem, nSample, false);
	LeaveCriticalSection(CVideoDeviceIO::m_showBufferLock);
	return true;
}

void CVideoDeviceIO::CleanVideoData()
{
	while (0 < GetCurEleNum(m_captureBuffer))
	{
		MoveReadPos(m_captureBuffer, 1);
	}
	while (0 < GetCurEleNum(m_showBuffer))
	{
		MoveReadPos(m_showBuffer, 1);
	}
}
