#include "MyDecoder.h"

void Ffmpeg_Decoder::Ffmpeg_Decoder_Init()
{
	//avcodec_register_all();     //注册编解码器
	av_init_packet(&avpkt);     //初始化包结构
								//m_pRGBFrame = new AVFrame[1];//RGB帧数据赋值 
	m_pYUVFrame = av_frame_alloc();
	filebuf = new uint8_t[1024 * 1024];//初始化文件缓存数据区

									   //yuv_buff = new uint8_t[width * height * 2];//初始化YUV图像数据区
									   //rgb_buff = new uint8_t[width * height * 3];//初始化RGB图像帧数据区
									   //data[0] = rgb_buff;
									   //linesize[0] = width * 3;
	pCodecH264 = avcodec_find_decoder(AV_CODEC_ID_H264);     //查找h264解码器
	if (!pCodecH264)
	{
		fprintf(stderr, "h264 codec not found\n");
		exit(1);
	}
	avParserContext = av_parser_init(AV_CODEC_ID_H264);

	c = avcodec_alloc_context3(pCodecH264);//函数用于分配一个AVCodecContext并设置默认值，如果失败返回NULL，并可用av_free()进行释放

	if (pCodecH264->capabilities&AV_CODEC_CAP_TRUNCATED)
		c->flags |= AV_CODEC_FLAG_TRUNCATED;	/* we do not send complete frames */
	if (avcodec_open2(c, pCodecH264, NULL) < 0)return;
	nDataLen = 0;
	finishInitScxt = false;//将格式转换器初始化标志设为否
}

void Ffmpeg_Decoder::Ffmpeg_Decoder_Show(char *pFrame, int width, int height)
{

#if 0
	CvSize  rectangle_img_size;
	rectangle_img_size.height = height;
	rectangle_img_size.width = width;

	img = cvCreateImage(rectangle_img_size, IPL_DEPTH_8U, 3);
	uchar* imgdata = (uchar*)(img->imageData);     //图像的数据指针

	for (int y = 0; y<height; y++)
	{
		memcpy(imgdata + y*width * 3, pFrame + y*width * 3, width * 3);
	}
	cvShowImage("解码图像", img);
	cvWaitKey(90);//可以将图像停留时间设的长点以便观察
	cvReleaseImage(&img);
	imgdata = NULL;
#else
	Mat image = Mat(height, width, CV_8UC3, pFrame);
	//cv::flip(image, image, 1);
	//cv::putText(image, // 图像矩阵
	//	fpsString,                  // string型文字内容
	//	cv::Point(5, 20),           // 文字坐标，以左下角为原点
	//	cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
	//	0.5, // 字体大小
	//	cv::Scalar(0, 0, 0));       // 字体颜色              // 在"FPS:"后加入帧率数值字符串
	imshow("recv", image);
	if (waitKey(5) == 27);//ESC for quit
						  /*imshow("recv", image);
						  waitKey(1);*/


#endif
}

void Ffmpeg_Decoder::Ffmpeg_Decoder_Close()
{
	sws_freeContext(scxt);//释放格式转换器资源
	finishInitScxt = false;//将格式转换器初始化标志设为否
	delete[]filebuf;
	delete[]yuv_buff;
	delete[]rgb_buff;
	av_free(m_pYUVFrame);//释放帧资源
	avcodec_close(c);//关闭解码器
	av_free(c);
}
