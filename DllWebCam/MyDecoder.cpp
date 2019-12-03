#include "MyDecoder.h"

void Ffmpeg_Decoder::Ffmpeg_Decoder_Init()
{
	//avcodec_register_all();     //ע��������
	av_init_packet(&avpkt);     //��ʼ�����ṹ
								//m_pRGBFrame = new AVFrame[1];//RGB֡���ݸ�ֵ 
	m_pYUVFrame = av_frame_alloc();
	filebuf = new uint8_t[1024 * 1024];//��ʼ���ļ�����������

									   //yuv_buff = new uint8_t[width * height * 2];//��ʼ��YUVͼ��������
									   //rgb_buff = new uint8_t[width * height * 3];//��ʼ��RGBͼ��֡������
									   //data[0] = rgb_buff;
									   //linesize[0] = width * 3;
	pCodecH264 = avcodec_find_decoder(AV_CODEC_ID_H264);     //����h264������
	if (!pCodecH264)
	{
		fprintf(stderr, "h264 codec not found\n");
		exit(1);
	}
	avParserContext = av_parser_init(AV_CODEC_ID_H264);

	c = avcodec_alloc_context3(pCodecH264);//�������ڷ���һ��AVCodecContext������Ĭ��ֵ�����ʧ�ܷ���NULL��������av_free()�����ͷ�

	if (pCodecH264->capabilities&AV_CODEC_CAP_TRUNCATED)
		c->flags |= AV_CODEC_FLAG_TRUNCATED;	/* we do not send complete frames */
	if (avcodec_open2(c, pCodecH264, NULL) < 0)return;
	nDataLen = 0;
	finishInitScxt = false;//����ʽת������ʼ����־��Ϊ��
}

void Ffmpeg_Decoder::Ffmpeg_Decoder_Show(char *pFrame, int width, int height)
{

#if 0
	CvSize  rectangle_img_size;
	rectangle_img_size.height = height;
	rectangle_img_size.width = width;

	img = cvCreateImage(rectangle_img_size, IPL_DEPTH_8U, 3);
	uchar* imgdata = (uchar*)(img->imageData);     //ͼ�������ָ��

	for (int y = 0; y<height; y++)
	{
		memcpy(imgdata + y*width * 3, pFrame + y*width * 3, width * 3);
	}
	cvShowImage("����ͼ��", img);
	cvWaitKey(90);//���Խ�ͼ��ͣ��ʱ����ĳ����Ա�۲�
	cvReleaseImage(&img);
	imgdata = NULL;
#else
	Mat image = Mat(height, width, CV_8UC3, pFrame);
	//cv::flip(image, image, 1);
	//cv::putText(image, // ͼ�����
	//	fpsString,                  // string����������
	//	cv::Point(5, 20),           // �������꣬�����½�Ϊԭ��
	//	cv::FONT_HERSHEY_SIMPLEX,   // ��������
	//	0.5, // �����С
	//	cv::Scalar(0, 0, 0));       // ������ɫ              // ��"FPS:"�����֡����ֵ�ַ���
	imshow("recv", image);
	if (waitKey(5) == 27);//ESC for quit
						  /*imshow("recv", image);
						  waitKey(1);*/


#endif
}

void Ffmpeg_Decoder::Ffmpeg_Decoder_Close()
{
	sws_freeContext(scxt);//�ͷŸ�ʽת������Դ
	finishInitScxt = false;//����ʽת������ʼ����־��Ϊ��
	delete[]filebuf;
	delete[]yuv_buff;
	delete[]rgb_buff;
	av_free(m_pYUVFrame);//�ͷ�֡��Դ
	avcodec_close(c);//�رս�����
	av_free(c);
}
