#include<iostream>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "cv.h" 
#include "highgui.h"
#include <winsock.h>
  #pragma comment(lib, "ws2_32.lib")
/////////////////////////////////////////////////////////
 using namespace std;
 ///////////////////////////////////////////////////////////////
 HANDLE hPort,hPort1;
    int       key = 0;
	int data=0;
	IplImage* img;
int       is_data_ready = 0;
 uchar * data2  ;
/////////////////////////////////////////////////////////////////
WSADATA                            wsaData;
            SOCKET                                ReceivingSocket2;
            SOCKADDR_IN                   ReceiverAddr;
            int                                            Port = 5150;
            char                             ReceiveBuf[20000];
			
			
			char                             raw[940000];
            int                                            BufLength = 20000;
            SOCKADDR_IN                   SenderAddr;
            int                                            SenderAddrSize = sizeof(SenderAddr);
            int                                            ByteReceived = 5;
////////////////////////////////////////////////////////////////////////////////////////////////

			














////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 void initial()
 {
   if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
   {
               cout<<endl<<"Server: WSAStartup failed with error "<< WSAGetLastError()<<endl;
         
   }
   else
                cout<<endl<<"Server: The Winsock DLL status is"<< wsaData.szSystemStatus<<endl;        
           
           ReceivingSocket2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
 
            if (ReceivingSocket2 == INVALID_SOCKET)
            {
                        cout<<endl<<"Server: Error at socket(): "<< WSAGetLastError()<<endl;
                        WSACleanup();
                      
            }
            else
                      cout<<endl<<"erver: socket() is OK: " ;
 
            // Set up a SOCKADDR_IN structure that will tell bind that we
            // want to receive datagrams from all interfaces using port 5150.
 
            // The IPv4 family
            ReceiverAddr.sin_family = AF_INET;
            // Port no. 5150
            ReceiverAddr.sin_port = htons(Port);
            // From all interface (0.0.0.0)
            ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
           
   // Associate the address information with the socket using bind.
   // At this point you can receive datagrams on your bound socket.
   if (bind(ReceivingSocket2, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
   {
               cout<<endl<<"Server: bind() failed! Error: "<< WSAGetLastError()<<endl;
               // Close the socket
               closesocket(ReceivingSocket2);
               // Do the clean up
               WSACleanup();
               // and exit with error
            }
            else
                       cout<<endl<<"Server: bind() is OK!\n"<<endl;
 
  cout<<"Server: I'm ready to receive a datagram...\n";
 }
 int i;
 const int  imgsize = 921600;
    char sockdata[imgsize];
/////////////////////////
DWORD WINAPI StartThre(LPVOID iValue)
{  

	int width=img->width;
	int height=img->height;
	int steps=img->widthStep,ch;
	int channels=3;
    data2      = (uchar *)img->imageData; 
	 int m=0,p=0;
     while(1)
	 {   

   ByteReceived = recvfrom(ReceivingSocket2, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize); 
   if ( ByteReceived > 0 )
   {
	   if(ReceiveBuf[0]=='5')
  {  cout<<"          "<<ReceiveBuf[0];
	  
	  ByteReceived = recvfrom(ReceivingSocket2, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
	 if(ByteReceived>0)
	 { m=0;
is:	   for(int i=0;i<height;i++) for(int j=0;j<width;j++)for(ch=0;ch<channels;ch++)
			 {data2[i*steps+j*channels+ch]=(uchar)ReceiveBuf[m]; 
 next:	   if(m==19999)
			{
again:				ByteReceived = recvfrom(ReceivingSocket2, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
				if( ByteReceived > 0 )
				{m=0;p=1;
					goto next; 
				}
				goto again;
			} if(p==0)m++;else if(p==1) p=0;
 
	   } m=0;
	   is_data_ready = 1; 
 // Sleep(100);
	
	   }
   }
   }
   }
	return 0;
}


///////////////////////////////////////////////////////////////////////
int  main( int argc, char **argv )
{
	initial();   
   img = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
    cvZero(img);cout<<"    "<<img->height;
	 cvNamedWindow("stream_client", CV_WINDOW_AUTOSIZE);
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

 
    while( key != 'q' ) {
      
        if(  is_data_ready )
			{ 
				cvShowImage("stream_client", img);
				  is_data_ready = 0;
		}
 

  
      key = cvWaitKey( 30 );
    }
 

   cvDestroyWindow( "stream_client" );
 WaitForSingleObject(hThread2,INFINITE);
    return 0;
}