#include<iostream>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "cv.h"
#include "highgui.h"
#include <winsock.h>
//////////////////////
 
#pragma comment(lib, "ws2_32.lib")
/////////////////////////////////////////////////////////
 using namespace std;
 ///////////////////////////////////////////////////////////////
 HANDLE hPort,hPort1;
    IplImage  *frame = 0;
	IplImage  *frames ;
    CvCapture *capture = 0;
    int       key = 0,all=0;
	int datas=0;
 uchar * data  ;
 int height,width,step;  //
///////////////////////////////////////////////////////////////////////////
 char                 *SendBuf = "5";
 WSADATA              wsaData;
            SOCKET               SendingSocket2;
            SOCKADDR_IN          ReceiverAddr, SrcInfo;
            int                  Port = 5150;
            int                  BufLength1 = 2;
            int                  BufLength = 20000;
            int len;
            int TotalByteSent=0;
 /////////////////////////////////////////////////////////////////////////////
			void initial()
 {
	          if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
            {
                      cout<<endl<<"Client: WSAStartup failed with error "<< WSAGetLastError()<<endl;
					  WSACleanup();
                  
                  
            }
            else
                cout<<endl<<"Client: The Winsock DLL status is  "<<  wsaData.szSystemStatus<<endl;     
				         
            SendingSocket2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (SendingSocket2 == INVALID_SOCKET)
            {
                      cout<<endl<<"Client: Error at socket(): "<< WSAGetLastError()<<endl;
                      WSACleanup();
                                     
            }
            else
                   cout<<endl<<"Client: socket() is OK\n";
 
            ReceiverAddr.sin_family = AF_INET;
            ReceiverAddr.sin_port = htons(Port);
            ReceiverAddr.sin_addr.s_addr = inet_addr("10.3.54.199");//192.168.1.2//127.0.0.1
  		
 
 }
 //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
DWORD WINAPI StartThre(LPVOID iValue)
{  
int k=5,p=0,i,j,ch;
	int  imgsize = frames->imageSize;
   char sockdata[20000];
int width=frames->width;
int height=frames->height;int m=0;int t=0;
int channels  = frames->nChannels;
int steps      =frames->widthStep;
  data      = (uchar *)frames->imageData;SYSTEMTIME  lt;
     while(1)
	 { 

		 if(datas)
		 { 
         for(i=0;i<height;i++) for( j=0;j<width;j++)for(ch=0;ch<channels;ch++)
			 {
			  sockdata[m]=data[i*step+j*channels+ch];
			  k=2;
				  if(m==19999)
				  {
					  TotalByteSent = sendto(SendingSocket2, sockdata, BufLength, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));
					  m=0; k=3;p=1;
				  }
				if(p==0)m++;else if(p==1) p=0;  
		 } if(k==2)
		 {TotalByteSent = sendto(SendingSocket2, sockdata, BufLength, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));
			 k=5;}
		 m=0; 
	   TotalByteSent = sendto(SendingSocket2, SendBuf, BufLength1, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));
	   datas=0;  //if (t==20){GetLocalTime(&lt);cout<<"tym"<<lt.wSecond;cout<<"milli"<<lt.wMilliseconds;t=60;}t++;
		Sleep(300);
		 }
	 } 
return 0;
}


///////////////////////////////////////////////////////////////////////
int  main( int argc, char **argv )
{
	initial();
	capture = cvCaptureFromCAM( -1 );
    if ( !capture ) {
        cout<<"Cannot open initialize webcam!\n"<<stderr;
        return 1;
    }
    frame= cvQueryFrame(capture);
	
    frames = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
	cvZero(frames);
	int imgsize = frame->imageSize;
	cout<<imgsize;cout<<"   "<<frame->width<<"    "<<frame->height;
    cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );
///////////////////////////////////////////////////////////////////////////	
	 HANDLE hThread1,hThread2;
     DWORD dwGenericThread;
     char lszThreadParam[3];
     strcpy(lszThreadParam,"30");
     hThread2 = CreateThread(NULL,0,StartThre,&lszThreadParam,0,&dwGenericThread);
     if(hThread2 == NULL)
      {
            DWORD dwError = GetLastError();
            cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
            
        }
/////////////////////////////////////////////////////////////////////////
     height    = frame->height;
     width     = frame->width;
     step      =frame->widthStep;
	 cout<<frame->imageSize<<endl;
    while( key != 'q' ) 
	{
		frame = cvQueryFrame( capture  );
	    frame->origin = 0;
        cvFlip(frame,frame, 1);
        if( !frame ) break;

	if(datas==0)
	{
		cvCopy(frame,  frames, NULL );
		 datas=1;

	}
 cvShowImage( "result", frames); 
        key = cvWaitKey( 30 );
    }
 

    cvDestroyWindow( "result" );
    cvReleaseCapture( &capture );
 WaitForSingleObject(hThread2,INFINITE);
    return 0;
}