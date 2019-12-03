#include "MyEncoder.h"

MyEncoder::MyEncoder()
{

}

void MyEncoder::Ffmpeg_Encoder_Init()
{
	av_register_all();
	avcodec_register_all();

	m_pRGBFrame = new AVFrame[1];//RGB֡���ݸ�ֵ    
	m_pYUVFrame = new AVFrame[1];//YUV֡���ݸ�ֵ    

								 //m_pRGBFrame = av_frame_alloc();
								 //m_pYUVFrame = av_frame_alloc();

	c = NULL;//������ָ����󸳳�ֵ  
}

void MyEncoder::Ffmpeg_Encoder_Setpara(const char * codec_name, int vwidth, int vheight)
{
	/*  const char  *codec_name;
	codec_name = "libx264";*/
	pCodecH264 = avcodec_find_encoder_by_name(codec_name);  //����h264������  

	if (!pCodecH264)
	{
		fprintf(stderr, "h264 codec not found\n");
		system("pause");
		exit(1);
	}

	width = vwidth;
	height = vheight;

	c = avcodec_alloc_context3(pCodecH264);  //�������ڷ���һ��AVCodecContext������Ĭ��ֵ�����ʧ�ܷ���NULL��������av_free()�����ͷ�  
	if (!c) {
		fprintf(stderr, "Could not allocate video codec context\n");
		system("pause");
		exit(1);
	}
	c->bit_rate = 400000; //���ò�����������������  
	c->width = vwidth;//���ñ�����Ƶ���   
	c->height = vheight; //���ñ�����Ƶ�߶�  
	c->time_base.den = 25;//����֡��,numΪ���Ӻ�denΪ��ĸ�������1/25���ʾ25֡/s  
	c->time_base.num = 1;
	c->gop_size = 10; //����GOP��С,��ֵ��ʾÿ10֡�����һ��I֡  
	c->max_b_frames = 1;//����B֡�����,��ֵ��ʾ��������B֮֡�䣬����������B֡�����֡��  
	c->pix_fmt = AV_PIX_FMT_YUV420P;//�������ظ�ʽ  

	if (pCodecH264->id == AV_CODEC_ID_H264)
	{
		av_opt_set(c->priv_data, "tune", "zerolatency", 0);  ////���ñ���������ʱ�����ǰ��ļ�ʮ֡�������ݵ����
	}


	//�򿪱�����	
	if (avcodec_open2(c, pCodecH264, NULL)<0)
	{
		
		fprintf(stderr, "Could not open codec: %s\n");
		system("pause");
		exit(1);
	}

	nDataLen = vwidth*vheight * 3;//����ͼ��rgb����������  

	yuv_buff = new uint8_t[nDataLen / 2];//��ʼ����������Ϊyuvͼ��֡׼����仺��  
	rgb_buff = new uint8_t[nDataLen];//��ʼ����������Ϊrgbͼ��֡׼����仺��  
	outbuf_size = 100000;////��ʼ���������������  
	outbuf = new uint8_t[outbuf_size];

	scxt = sws_getContext(c->width, c->height, AV_PIX_FMT_BGR24, c->width, c->height, AV_PIX_FMT_YUV420P, SWS_POINT, NULL, NULL, NULL);
	//��ʼ����ʽת������  
	//ת����������  																																	
	//Դͼ��Ŀ�� Դͼ��ĸ߶� Դͼ���ʽ Ŀ��ͼ��Ŀ�� Ŀ��ͼ��ĸ߶� Ŀ��ͼ���ʽ ��־ָ�������������ŵ��㷨��ѡ�� ����������ڵ���ʹ�õĶ�����																																  
}


void MyEncoder::Ffmpeg_Encoder_Encode(FILE *file, uint8_t *data)    //д���ļ�
{
	av_init_packet(&pkt);
	memcpy(rgb_buff, data, nDataLen);//����ͼ�����ݵ�rgbͼ��֡������׼������  
	avpicture_fill((AVPicture*)m_pRGBFrame, (uint8_t*)rgb_buff, AV_PIX_FMT_RGB24, width, height);//��rgb_buff��䵽m_pRGBFrame  
																								 //av_image_fill_arrays((AVPicture*)m_pRGBFrame, (uint8_t*)rgb_buff, AV_PIX_FMT_RGB24, width, height);
	avpicture_fill((AVPicture*)m_pYUVFrame, (uint8_t*)yuv_buff, AV_PIX_FMT_YUV420P, width, height);//��yuv_buff��䵽m_pYUVFrame  
	sws_scale(scxt, m_pRGBFrame->data, m_pRGBFrame->linesize, 0, c->height, m_pYUVFrame->data, m_pYUVFrame->linesize);// ��RGBת��ΪYUV  
	int myoutputlen = 0;
	int returnvalue = avcodec_encode_video2(c, &pkt, m_pYUVFrame, &myoutputlen);
	if (returnvalue == 0)
	{
		fwrite(pkt.data, 1, pkt.size, file);
	}
	av_free_packet(&pkt);
}

void MyEncoder::Ffmpeg_Encoder_Encode_New(uint8_t *data, AVPacket *pkt)   //
{ 
	
	av_init_packet(pkt);

	memcpy(rgb_buff, data, nDataLen);//����ͼ�����ݵ�rgbͼ��֡������׼������  
	avpicture_fill((AVPicture*)m_pRGBFrame, (uint8_t*)rgb_buff, AV_PIX_FMT_RGB24, width, height);
	//��rgb_buff��䵽m_pRGBFrame  
	//av_image_fill_arrays((AVPicture*)m_pRGBFrame, (uint8_t*)rgb_buff, AV_PIX_FMT_RGB24, width, height);
	avpicture_fill((AVPicture*)m_pYUVFrame, (uint8_t*)yuv_buff, AV_PIX_FMT_YUV420P, width, height);
	//��yuv_buff��䵽m_pYUVFrame  
	sws_scale(scxt, m_pRGBFrame->data, m_pRGBFrame->linesize, 0, c->height, m_pYUVFrame->data, m_pYUVFrame->linesize);
	// ��RGBת��ΪYUV  
	int myoutputlen = 0;
	int returnvalue = avcodec_encode_video2(c, pkt, m_pYUVFrame, &myoutputlen);
	if (returnvalue == 0)
	{
		//fwrite(pkt.data, 1, pkt.size, file);
	}

}


void MyEncoder::Ffmpeg_Encoder_Close()
{
	delete[]m_pRGBFrame;
	delete[]m_pYUVFrame;
	delete[]rgb_buff;
	delete[]yuv_buff;
	delete[]outbuf;
	sws_freeContext(scxt);
	avcodec_close(c);//�رձ�����  
	av_free(c);
}