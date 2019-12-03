#include "CWebCam.h"
#include <stdio.h>
#include <string.h>
#include <random>
#include "windows.h"
#include "dshow.h"
#include <iostream>

#include "MyEncoder.h"
#include "MyDecoder.h"

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "quartz.lib")

HANDLE eventCapture;
HANDLE eventShow;

//CWebCam::CWebCam() :CVideoDeviceIO(30, 32, 480, 640, 30, 32, 480, 640)
//{
//
//}

CWebCam::CWebCam() 
{

}

CWebCam::~CWebCam() 
{
}

//CWebCam::~CWebCam()
//{
//
//}
//bool CWebCam::WebCam_LoadInit()
//{
//
//}
//
//bool  CWebCam::WebCam_UserSet()
//{
//
//}
//
//bool CWebCam::WebCam_Start()
//{
//	if (capture.isOpened())
//	{
//		return true;
//	}
//	return false;
//}
//
//bool CWebCam::WebCam_Stop()
//{
//
//}

bool CWebCam::WebCam_Release()
{
	capture.release();
	/*free(captureBuffer[0]);
	free(showBuffer[0]);*/
	return true;
}

//double CWebCam::WebCam_GetFrameRate()   //获取帧率，成功返回帧率，失败返回-1；
//{
//	/*if (GetSampleRateOK == true)
//	{
//	return sampleRate;
//	}
//	return -1;*/
//}

AVPacket pkt; //存储压缩后的包
MyEncoder myencoder;
Ffmpeg_Decoder ffmpegobj;

void CWebCam::WebCam_Encoder()
{
	
	/*myencoder.Ffmpeg_Encoder_Init();
	myencoder.Ffmpeg_Encoder_Setpara("libx264", frame.cols, frame.rows);*/
	/*char * ptrAlloc = (char *)calloc(sizeof(char), 1000 * 1000 * 3);*/
	AVPacket pkt;
	myencoder.Ffmpeg_Encoder_Encode_New((uint8_t *)(frame.data), &pkt);
	cout << frame.size << endl;
	cout << pkt.size << endl;
	/*if (pkt.size == 0)
	{
		continue;
	}*/
	//memcpy(ptrAlloc, pkt.data, pkt.size);
	//
	/*av_free_packet(&pkt);*/
}

long playframecount = 0;

void CWebCam::WebCam_Decoder() 
{
	//int bufferSize = 640 * 480 * 3;
	///*char * revBuffer = (char *)malloc(sizeof(char) * bufferSize);*/
	//char * ptrAlloc = (char *)calloc(sizeof(char), 1000 * 1000 * 3);
	//
	//memcpy(ptrAlloc, pkt.data, pkt.size);
	///*Ffmpeg_Decoder ffmpegobj;*/
	///*ffmpegobj.Ffmpeg_Decoder_Init(); */
	//
	//ffmpegobj.nDataLen = pkt.size;
	//memcpy(ffmpegobj.filebuf, ptrAlloc, ffmpegobj.nDataLen);
	//if (ffmpegobj.nDataLen <= 0)
	//{
	//	/*printf("a");*/
	//}
	//else
	//{
	//	ffmpegobj.haveread = 0;
	//	while (ffmpegobj.nDataLen > 0)
	//	{
	//		int nLength = av_parser_parse2(ffmpegobj.avParserContext, ffmpegobj.c, &ffmpegobj.yuv_buff,
	//			&ffmpegobj.nOutSize, ffmpegobj.filebuf + ffmpegobj.haveread, ffmpegobj.nDataLen, 0, 0, 0);//查找帧头
	//		ffmpegobj.nDataLen -= nLength;//查找过后指针移位标志
	//		ffmpegobj.haveread += nLength;
	//		if (ffmpegobj.nOutSize <= 0)
	//		{
	//			break;
	//		}
	//		ffmpegobj.avpkt.size = ffmpegobj.nOutSize;//将帧数据放进包中
	//		ffmpegobj.avpkt.data = ffmpegobj.yuv_buff;
	//		playframecount++;

	//		//解码
	//		ffmpegobj.decodelen = avcodec_decode_video2(ffmpegobj.c, ffmpegobj.m_pYUVFrame, &ffmpegobj.piclen, &ffmpegobj.avpkt);

	//		if (ffmpegobj.decodelen < 0)
	//		{
	//			printf("error\n");
	//			break;
	//		}
	//		if (ffmpegobj.piclen)
	//		{
	//			if (ffmpegobj.finishInitScxt == false)//初始化格式转换函数  
	//			{
	//				ffmpegobj.finishInitScxt = true;
	//				ffmpegobj.scxt = sws_getContext(ffmpegobj.c->width, ffmpegobj.c->height, ffmpegobj.c->pix_fmt,
	//					ffmpegobj.c->width, ffmpegobj.c->height, AV_PIX_FMT_BGR24, SWS_POINT, NULL, NULL, NULL);

	//				int width = ffmpegobj.c->width;
	//				int height = ffmpegobj.c->height;
	//				ffmpegobj.yuv_buff = new uint8_t[width * height * 2];//初始化YUV图像数据区
	//				ffmpegobj.rgb_buff = new uint8_t[width * height * 3];//初始化RGB图像帧数据区
	//				ffmpegobj.data[0] = ffmpegobj.rgb_buff;
	//				ffmpegobj.linesize[0] = width * 3;
	//			}
	//			if (ffmpegobj.scxt != NULL)
	//			{
	//				//YUV转rgb  
	//				sws_scale(ffmpegobj.scxt, ffmpegobj.m_pYUVFrame->data, ffmpegobj.m_pYUVFrame->linesize, 0,
	//					ffmpegobj.c->height, ffmpegobj.data, ffmpegobj.linesize);

	//				/*ffmpegobj.Ffmpeg_Decoder_Show((char*)ffmpegobj.rgb_buff, ffmpegobj.c->width, ffmpegobj.c->height);*/
	//				Mat image = Mat(ffmpegobj.c->height, ffmpegobj.c->width, CV_8UC3, (char*)ffmpegobj.rgb_buff);
	//				/*cv::flip(image, image, 1);*/
	//				/*cout << "a" << endl;*/
	//				//cv::putText(image, // 图像矩阵
	//				//	fpsString,                  // string型文字内容
	//				//	cv::Point(5, 20),           // 文字坐标，以左下角为原点
	//				//	cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
	//				//	0.5, // 字体大小
	//				//	cv::Scalar(0, 0, 0));       // 字体颜色              // 在"FPS:"后加入帧率数值字符串
	//				imshow("recv", image);
	//				if (waitKey(5) == 27);//ESC for quit
	//									  //解码图像显示   	
	//			}
	//		}
	//	}
	//}
}

int CWebCam::WebCam_ListInitWebCamDevice(vector<string>& list)
{
	//COM Library Initialization
	//comInit();

	//if (!silent) DebugPrintOut("\nVIDEOINPUT SPY MODE!\n\n");

	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	int deviceCounter = 0;
	CoInitialize(NULL);

	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
		CLSCTX_INPROC_SERVER, IID_ICreateDevEnum,
		reinterpret_cast<void**>(&pDevEnum));

	if (SUCCEEDED(hr))
	{
		// Create an enumerator for the video capture category.
		hr = pDevEnum->CreateClassEnumerator(
			CLSID_VideoInputDeviceCategory,
			&pEnum, 0);

		if (hr == S_OK) {

			printf("SETUP: Looking For Capture Devices\n");
			IMoniker *pMoniker = NULL;

			while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {

				IPropertyBag *pPropBag;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
					(void**)(&pPropBag));

				if (FAILED(hr)) {
					pMoniker->Release();
					continue;  // Skip this one, maybe the next one will work.
				}


				// Find the description or friendly name.
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"Description", &varName, 0);

				if (FAILED(hr)) hr = pPropBag->Read(L"FriendlyName", &varName, 0);

				if (SUCCEEDED(hr))
				{

					hr = pPropBag->Read(L"FriendlyName", &varName, 0);

					int count = 0;
					char tmp[255] = { 0 };
					//int maxLen = sizeof(deviceNames[0]) / sizeof(deviceNames[0][0]) - 2;
					while (varName.bstrVal[count] != 0x00 && count < 255)
					{
						tmp[count] = (char)varName.bstrVal[count];
						count++;
					}
					list.push_back(tmp);
					//deviceNames[deviceCounter][count] = 0;

					//if (!silent) DebugPrintOut("SETUP: %i) %s\n", deviceCounter, deviceNames[deviceCounter]);
				}

				pPropBag->Release();
				pPropBag = NULL;

				pMoniker->Release();
				pMoniker = NULL;

				deviceCounter++;
			}

			pDevEnum->Release();
			pDevEnum = NULL;

			pEnum->Release();
			pEnum = NULL;
		}

		//if (!silent) DebugPrintOut("SETUP: %i Device(s) found\n\n", deviceCounter);
	}

	//comUnInit();

	return deviceCounter;
}


void CWebCam::WebCamInitialize()
{
	//listDevice
	vector<string> list;
	int device_num = 0;
	device_num = WebCam_ListInitWebCamDevice(list);//设备列表
	int devID;
	cout << "divice_num:" << device_num << endl;

	for (int i = 0; i < list.size(); i++)
	{
		cout << "Device[" << i << "]:" << list[i] << endl;
	    cout<< "the camera ID is :" << i << endl;
	}
	printf("Now type the ID of the Camera to be uesd:\n");
	devID = _getch() - '0';
	while (devID<0 || devID>device_num)
	{
		printf("please choose correct device ID !\n");
		printf("Now type the ID of the Camera to be uesd:\n");
		devID = _getch() - '0';
	}
	printf("\n\n");
	/*printf("The WebCam information are shown as follows:\n\n");*/
	//printf("SampleRate:%lf\n", this->WebCam_GetFrameRate);
	//printf("BufferSize:%d\n", this->WebCam_GetBufferSize);
	//printf("AvailableShowResolutionRratioHeight:%d\n", this->WebCam_GetAvailableShowResolutionRratioHeight);
	//printf("WebCam_GetAvailableShowResolutionRratioWidth:%d\n", this->WebCam_GetAvailableShowResolutionRratioWidth);
	//printf("DigitalizingBit:%d\n", this->WebCam_GetDigitalizingBit());
	
}

void CWebCam::WebCamRun()
{   
	capture = VideoCapture(CV_CAP_DSHOW);	//使用DirectShow
	capture.open(0);//这是我的USB摄像头

	double fps = 0;
	char string[10];    // 帧率字符串
	double t = 0;
	
	
    
	capture >> frame;
	myencoder.Ffmpeg_Encoder_Init();
	myencoder.Ffmpeg_Encoder_Setpara("libx264", frame.cols, frame.rows);
	printf("Image size: [%d %d ]\n", frame.cols, frame.rows);
	/*cv::namedWindow("recv");*/

	Ffmpeg_Decoder ffmpegobj;
	ffmpegobj.Ffmpeg_Decoder_Init();

	int bufferSize = 640 * 480 * 3;
	char * ptrAlloc = (char *)calloc(sizeof(char), 1000 * 1000 * 3);


	while (1)
	{
		//std::string fpsString("FPS:");
		//sprintf_s(string, "%.2f", fps);      // 帧率保留两位小数
		//									 /*  std::string fpsString("FPS:");*/
		//fpsString += string;
		//double start = (double)cv::getTickCount();    /*cout << "开始时间 " <<start << endl;*/
		//for (int i = 0; i < 10; i++)                 //Is not accuracy when I count once.
		/*{*/
		  capture >> frame;
			/*cv::flip(frame, frame, 1);*/
			//cv::putText(frame, // 图像矩阵
			//	fpsString,                  // string型文字内容
			//	cv::Point(5, 20),           // 文字坐标，以左下角为原点
			//	cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
			//	0.5, // 字体大小
			//	cv::Scalar(0, 0, 0));       // 字体颜色              // 在"FPS:"后加入帧率数值字符串

			/*imshow("Camera FPS", frame);*/
			/*WebCam_Encoder();*/
		  AVPacket pkt;
		  memset(&pkt, 0, sizeof(AVPacket));
		  myencoder.Ffmpeg_Encoder_Encode_New((uint8_t *)(frame.data), &pkt);
		  cout << "frame.size is"<<frame.size << endl;
		  cout << "pkt.size is"<<pkt.size << endl;
		 /* WebCam_Decoder();*/

		  memcpy(ptrAlloc, pkt.data, pkt.size);
		  /*Ffmpeg_Decoder ffmpegobj;*/
		  /*ffmpegobj.Ffmpeg_Decoder_Init(); */

		  ffmpegobj.nDataLen = pkt.size;
		  memcpy(ffmpegobj.filebuf, ptrAlloc, ffmpegobj.nDataLen);
		  if (ffmpegobj.nDataLen <= 0)
		  {
			/*  printf("a");
			  system("pause");
			  break;*/
			  continue;
		  }
		  else
		  {
			  //ffmpegobj.haveread = 0;
			  //while (ffmpegobj.nDataLen > 0)
			  //{
				 // int nLength = av_parser_parse2(ffmpegobj.avParserContext, ffmpegobj.c, &ffmpegobj.yuv_buff,
					//  &ffmpegobj.nOutSize, ffmpegobj.filebuf + ffmpegobj.haveread, ffmpegobj.nDataLen, 0, 0, 0);//查找帧头
				 // ffmpegobj.nDataLen -= nLength;//查找过后指针移位标志
				 // ffmpegobj.haveread += nLength;
				 // if (ffmpegobj.nOutSize <= 0)
				 // {
					//  break;
				 // }
				 // ffmpegobj.avpkt.size = ffmpegobj.nOutSize;//将帧数据放进包中
				 // ffmpegobj.avpkt.data = ffmpegobj.yuv_buff;
				 // playframecount++;

				 // //解码
				 // ffmpegobj.decodelen = avcodec_decode_video2(ffmpegobj.c, ffmpegobj.m_pYUVFrame, &ffmpegobj.piclen, &ffmpegobj.avpkt);

				 // if (ffmpegobj.decodelen < 0)
				 // {
					//  printf("error\n");
					//  break;
				 // }
				 // if (ffmpegobj.piclen)
				 // {
					//  if (ffmpegobj.finishInitScxt == false)//初始化格式转换函数  
					//  {
					//	  ffmpegobj.finishInitScxt = true;
					//	  ffmpegobj.scxt = sws_getContext(ffmpegobj.c->width, ffmpegobj.c->height, ffmpegobj.c->pix_fmt,
					//		  ffmpegobj.c->width, ffmpegobj.c->height, AV_PIX_FMT_BGR24, SWS_POINT, NULL, NULL, NULL);

					//	  int width = ffmpegobj.c->width;
					//	  int height = ffmpegobj.c->height;
					//	  ffmpegobj.yuv_buff = new uint8_t[width * height * 2];//初始化YUV图像数据区
					//	  ffmpegobj.rgb_buff = new uint8_t[width * height * 3];//初始化RGB图像帧数据区
					//	  ffmpegobj.data[0] = ffmpegobj.rgb_buff;
					//	  ffmpegobj.linesize[0] = width * 3;
					//  }
					//  if (ffmpegobj.scxt != NULL)
					//  {
					//	  //YUV转rgb  
					//	  sws_scale(ffmpegobj.scxt, ffmpegobj.m_pYUVFrame->data, ffmpegobj.m_pYUVFrame->linesize, 0,
					//		  ffmpegobj.c->height, ffmpegobj.data, ffmpegobj.linesize);

					//	  /*ffmpegobj.Ffmpeg_Decoder_Show((char*)ffmpegobj.rgb_buff, ffmpegobj.c->width, ffmpegobj.c->height);*/
					//	  Mat image = Mat(ffmpegobj.c->height, ffmpegobj.c->width, CV_8UC3, (char*)ffmpegobj.rgb_buff);
					//	  cv::flip(image, image, 1);
					//	  /*cout << "a" << endl;*/
					//	  //cv::putText(image, // 图像矩阵
					//	  //	fpsString,                  // string型文字内容
					//	  //	cv::Point(5, 20),           // 文字坐标，以左下角为原点
					//	  //	cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
					//	  //	0.5, // 字体大小
					//	  //	cv::Scalar(0, 0, 0));       // 字体颜色              // 在"FPS:"后加入帧率数值字符串
					//	  imshow("recv", image);
					//	  if (waitKey(5) == 27);//ESC for quit
					//							//解码图像显示   	
					//  }
				 // }
			  //}
			 /* while (ffmpegobj.nDataLen > 0)
			  {*/
			  ffmpegobj.avpkt.size = pkt.size;//将帧数据放进包中
			  ffmpegobj.avpkt.data = pkt.data;
			  playframecount++;
			  ffmpegobj.decodelen = avcodec_decode_video2(ffmpegobj.c, ffmpegobj.m_pYUVFrame, &ffmpegobj.piclen, &ffmpegobj.avpkt);
			  if (ffmpegobj.decodelen < 0)
			  {
				  printf("error\n");
				  system("pause");
				  break;
			  }
			  if (ffmpegobj.piclen)
			  {
				  if (ffmpegobj.finishInitScxt == false)//初始化格式转换函数  
				  {
					  ffmpegobj.finishInitScxt = true;
					  ffmpegobj.scxt = sws_getContext(ffmpegobj.c->width, ffmpegobj.c->height, ffmpegobj.c->pix_fmt,
						  ffmpegobj.c->width, ffmpegobj.c->height, AV_PIX_FMT_BGR24, SWS_POINT, NULL, NULL, NULL);

					  int width = ffmpegobj.c->width;
					  int height = ffmpegobj.c->height;
					  ffmpegobj.yuv_buff = new uint8_t[width * height * 2];//初始化YUV图像数据区
					  ffmpegobj.rgb_buff = new uint8_t[width * height * 3];//初始化RGB图像帧数据区
					  ffmpegobj.data[0] = ffmpegobj.rgb_buff;
					  ffmpegobj.linesize[0] = width * 3;
				  }
				  if (ffmpegobj.scxt != NULL)
				  {
					  //YUV转rgb  
					  sws_scale(ffmpegobj.scxt, ffmpegobj.m_pYUVFrame->data, ffmpegobj.m_pYUVFrame->linesize, 0,
						  ffmpegobj.c->height, ffmpegobj.data, ffmpegobj.linesize);

					  ffmpegobj.Ffmpeg_Decoder_Show((char*)ffmpegobj.rgb_buff, ffmpegobj.c->width, ffmpegobj.c->height);
					  Mat image = Mat(ffmpegobj.c->height, ffmpegobj.c->width, CV_8UC3, (char*)ffmpegobj.rgb_buff);
					  cv::flip(image, image, 1);
					  /*cout << "a" << endl;*/
					  //cv::putText(image, // 图像矩阵
					  //	fpsString,                  // string型文字内容
					  //	cv::Point(5, 20),           // 文字坐标，以左下角为原点
					  //	cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
					  //	0.5, // 字体大小
					  //	cv::Scalar(0, 0, 0));       // 字体颜色              // 在"FPS:"后加入帧率数值字符串
					  //imshow("recv", image);
					  if (waitKey(5) == 27);//ESC for quit
											/*解码图像显示 */
				  }
				  /*}*/
			 //}
			  }

		  }




		  av_free_packet(&pkt);
			if (waitKey(5) == 27);//ESC for quit
		/*}*/

		//double end = (double)cv::getTickCount();    /*cout << "结束时间" << end << endl;*/
		//t = (end - start) / cv::getTickFrequency();
		//t = t / 10;     //一帧所需的时间
		//fps = 1.0 / t;
		//cout << fps << endl;

		/*printf("fps: %.2f\n", fps); 		*/

     }
}



void CWebCam::Wait()
{
	WaitForSingleObject(eventCapture, INFINITE);
	ResetEvent(eventCapture);
}