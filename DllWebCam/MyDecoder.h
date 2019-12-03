#pragma once
#include <opencv2/core/core.hpp>//OpenCV包含头文件  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/opencv.hpp>  

using namespace cv;

//#include <string.h>//字符串操作头文件

#ifndef INT64_C 
#define INT64_C(c) (c ## LL) 
#define UINT64_C(c) (c ## ULL) 
#endif 

#ifdef __cplusplus 
extern "C" {
#endif 
	/*Include ffmpeg header file*/
#include <libavformat/avformat.h> 
#include <libavcodec/avcodec.h> 
#include <libswscale/swscale.h> 

#include <libavutil/imgutils.h>  
#include <libavutil/opt.h>     
#include <libavutil/mathematics.h>   
#include <libavutil/samplefmt.h>

#ifdef __cplusplus 
}
#endif 

class Ffmpeg_Decoder
{
public:
	AVCodecParserContext *avParserContext;
	AVPacket avpkt;			//数据包结构体
	AVFrame *m_pYUVFrame;	//帧对象
	AVCodec *pCodecH264;	//解码器
	AVCodecContext *c;		//解码器数据结构对象
	uint8_t *yuv_buff;      //yuv图像数据区
	uint8_t *rgb_buff;		//rgb图像数据区
	SwsContext *scxt;		//图像格式转换对象
	uint8_t *filebuf;		//读入文件缓存
	int nDataLen;			//rgb图像数据区长度

	IplImage* img;			//OpenCV图像显示对象
	int nOutSize;			//用以记录帧数据长度
	int haveread;			//用以记录已读buf长度
	int decodelen;			//解码器返回长度
	int piclen;				//解码器返回图片长度

	bool finishInitScxt;    //完成格式转换器初始化标志

	int linesize[1];//存放图像像素区宽度
	uint8_t* data[1];//图像像素区指针
public:
	void Ffmpeg_Decoder_Init();//初始化
	void Ffmpeg_Decoder_Show(char*pFrame, int width, int height);//显示图片
	void Ffmpeg_Decoder_Close();//关闭
};

