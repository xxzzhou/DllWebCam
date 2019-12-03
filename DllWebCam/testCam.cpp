#include <iostream>
#include <windows.h>
#include "CWebCam.h"

int main()
{
	
	CWebCam CwebCam;
	CwebCam.WebCamInitialize();
	CwebCam.WebCamRun();

}