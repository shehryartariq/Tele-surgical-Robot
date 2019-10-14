#include<stdlib.h>
#include<glut.h>

#include "glui.h"
#include <string>
#include <winsock2.h>

#include<time.h>
#include <windows.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int z1,xp=0,yp=0;
 HANDLE hThread2;
 int xy=1;
 int disconnect=1;
 float Val;
char delay[31];
 int dataa;
char datarate[31];
int allow=1;
int xxx=1,sbit=1;
 ////////////////////////////////////////
 int initial( );
  void close(int );
 void controls(int  );
  void thread();
 int   control = 1;
 int   cont = 1;
 int   control2 = 1;
 int exita=1;
 int sers=1;
int mode=3;
 int k=3;
 int both=0;
 int lastvalue=0;
  int xvalue[10]={160,160,160,160,160,160,160,160,160,160};
 int window_id;
GLUI_Checkbox   *checkbox;
/////////////////////////////////////////////////////////////////////////


WSADATA              wsaData;
SOCKET               SendingSocket, ReceivingSocket;
SOCKADDR_IN          ReceiverAddr;
int                  Port = 80;
char                 ReceiveBuf[1024];
int                  BufLength = 1024;
SOCKADDR_IN          SenderAddr;
SOCKADDR_IN          Sender1Addr;
int                  SenderAddrSize = sizeof(SenderAddr);
int                  ByteReceived = 10;
char                 *SendBuf;
char				 sendbuf[256];
int					 TotalByteSent;
int					 x=0;
string				 store[256];
const char			 *resend;
char				 *seq;
int					 y;
char				 *reseq;






//////////////////////////////////////////////////////////////////////////////
void control_cb( int control )
{ 
  
cout<< "callback: \n"<< control ;

if(control==0)
{   if(k==3)
{
//	initial();
	//thread(); k=2;
} 
}
}
 ///////////////////////////////////////////////////////
void controls( int control2 )
{ 
  
	allow=0;
	cout<<control2;
	sers=0;
}

///////////////////////////////////////////////
void close( int cont )
{ 
  
	
	cout<<control2;
	disconnect=0;
}

//////////////////////////////////////////////////////////////
 
DWORD WINAPI StartThre(LPVOID iValue)
{
  while(1)
	{
		int BufLengths=20;
		ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLengths, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
		ReceiveBuf[ByteReceived]='\0';
		if(ReceiveBuf[0]=='~')
		//	exit(0);
		if(ReceiveBuf[0]=='o')
		{
cout<<"Data received at "<<ReceiveBuf[1]<<" is: "<<ReceiveBuf<<endl;

		}
		
		if(ReceiveBuf[0]=='o')
		{
			
			y = static_cast<int>(ReceiveBuf[1]);
			resend=store[y].c_str();
				
			reseq = const_cast<char*> (resend);
			BufLength=strlen(reseq);
			TotalByteSent = sendto(SendingSocket, reseq, BufLength, 0, (SOCKADDR *)&Sender1Addr, sizeof(Sender1Addr));
			
			
		}
		
	}

	  return 0;
} 
 
///////////////////////////////////////////////////////////////

 
 
 
 
 
 
 
 
 
 
 
 //////////////////////////////////////////////////////////
 
 void thread()
 {
	
      DWORD dwGenericThread;
      char lszThreadParam[3];

      
      //Second thread creation
       strcpy(lszThreadParam,"30");
       hThread2 = CreateThread(NULL,0,StartThre,&lszThreadParam,0,&dwGenericThread);
       if(hThread2 == NULL)
       {
            DWORD dwError = GetLastError();
            cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
            return;
        }

 }






 /////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////


int initial()
{
	
	
	// Initialize Winsock version 2.2
	if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		printf("Server: WSAStartup failed with error %ld\n", WSAGetLastError());
		return -1;
	}
	
	SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendingSocket == INVALID_SOCKET)
	{
		printf("Client: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	
	// Create a new socket to receive datagrams on.
	ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (ReceivingSocket == INVALID_SOCKET)
	{
		printf("Server: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(Port);
	ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// Associate the address information with the socket using bind.
	// At this point you can receive datagrams on your bound socket.
	if (bind(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
	{
		printf("Server: bind() failed! Error: %ld.\n", WSAGetLastError());
		closesocket(ReceivingSocket);	
		WSACleanup();	
		return -1;
	}
	
	
	ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
	ReceiveBuf[ByteReceived]='\0';
	cout<<"Length of Byte Received is: "<<ByteReceived<<endl;
	cout<<"Data received is: "<<ReceiveBuf<<endl;
	getpeername(ReceivingSocket, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
	
	Sender1Addr.sin_family = AF_INET;
	Sender1Addr.sin_port = htons(Port);
	Sender1Addr.sin_addr.s_addr = SenderAddr.sin_addr.s_addr;


	////////////////////////////////////////////////
SendBuf=ReceiveBuf;
__int64 ctrBefore = 0, ctrAfter = 0;
__int64 freq = 0;

BufLength=strlen(SendBuf);
		TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&Sender1Addr, sizeof(Sender1Addr));
		cout<<"sent"<<endl;
QueryPerformanceCounter( (LARGE_INTEGER *) &ctrBefore );


	ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
	ReceiveBuf[ByteReceived]='\0';

QueryPerformanceCounter( (LARGE_INTEGER *) &ctrAfter );
	QueryPerformanceFrequency( (LARGE_INTEGER *) &freq );
Val=	((((ctrAfter - ctrBefore)*1000) * 1.0 / freq) )/2;
	sprintf(delay,"%f",Val);
cout<<"\n\n\tTime = "<<((((ctrAfter - ctrBefore)*1000) * 1.0 / freq) )<<" milliseconds"<<endl<<endl;

/////////////////////////////////////////////////////
	int BuffingLength=256;
	int f=0;
clock_t endwait;
		endwait = clock () + 10 * CLK_TCK ;


		while(clock()<endwait)
		{


	ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BuffingLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
	ReceiveBuf[ByteReceived]='\0';

f=f+1;
cout<<"clock is: "<<clock()<<endl;
cout<<"endwait is: "<<endwait<<endl;


		}


		
		 dataa=f*256*8/10000;
		cout<<"Data Rate is: "<<dataa<<" kbps "<<endl;
		sprintf(datarate,"%d",dataa);
		

//////////////////////////////////////////
return 0;
}
/////////////////////////////////////////






HWND    hWnd;       // Window's Handle
// Global variables for the Joystick
bool    joy_ok;         
UINT    joy_ID;         
UINT    joy_num;        
JOYCAPS joy_caps;       
JOYINFO joy_info;       
DWORD   joy_xcenter; // joy x axis center
DWORD   joy_ycenter; // joy y axis center
DWORD   joy_Zcenter; // joy Z axis center

//JoyStick Functions
bool InitJoystick();
void ReleaseJoystick();
void server(int, int );

/////////////////////////////////////////////////
void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
   joy_ok=InitJoystick();
}
////////////////////////////////////
static void Reshape(int w, int h)
{glClear(GL_COLOR_BUFFER_BIT);
	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho( 0.0, 100.0, 0.0, 100.0, -100.0, 100.0);

}
///////////////////////////////////////////////////

void JoyFunc(unsigned int buttonMask,int x, int y, int z)
{   int as=0;
	joyGetPos(joy_ID,&joy_info);
//cout<<"  "<<joy_info.wXpos<<" ,  "<<joy_info.wYpos<<" ,  "<<joy_info.wZpos<<endl;//cout<<"up";

int x1= joy_info.wXpos;
int y1= joy_info.wYpos;
int z1= joy_info.wZpos;
int button=joy_info. wButtons;
if(button==256)
{ mode=3; button=0;}
else if (button==512)
{ mode=2; button=0;}

y1=65535-y1;

//if(x1<=(xp+800) && x1>=(xp-800))
//	x1=xp;
if(y1<=(yp+800) && y1>=(yp-800))
	y1=yp;
////////////////////////////////
as=0;
	xvalue[lastvalue]=x1;
	if(lastvalue==9)
		lastvalue=0;
	else
		lastvalue++;
	for(int st=0; st<10; st++)
{
	as=as+xvalue[st];

}

	as=as/10;
	x1=as;







/////////////////////////////////
if(z1<=1000)
{
	x1=xp;
}
if(z1>=65000)
{
	y1=yp;
}
if(button==1024)
{ both=1;
  button=0;
}
if(button==2048)
{both=0; button=0;
}
if(both==1)
{
	x1=xp;
	y1=yp;
}
////////////////////////////////////
if(button==64)
{ sbit=1;
  button=0;
}
if(button==128)
{sbit=2; button=0;
}
if(both==1)
{
	x1=xp;
	y1=yp;
}


 server(sbit,1);
 Sleep(70);
//////////////////////////////////////
server(y1,1);
Sleep(70);

server(x1, mode  );
Sleep(70);

//server(z1);
xp=x1;
yp=y1;
if(button==2)
{ button=0;}

if(button==8)
{ button=2;}
if(button==9)
{button=3;}
server (button,1);
 Sleep(70);
 cout<<button<<endl;

}
/////////////////////////////////////////////////////////////////



void display(void)
{
	glutForceJoystickFunc();
}

void myGlutIdle( void ) {
glutSetWindow( window_id);
glutPostRedisplay();
}
///////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{ initial();
thread();

	glutInit(&argc, argv);
	
	init();
  //
      GLUI *glui = GLUI_Master.create_glui( "GLUI", 0, 800 ,400);    		
	 
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (00, 00); 
 window_id =  glutCreateWindow ("joystick");  // change the title of the window 


       glutReshapeFunc(Reshape);
   glutDisplayFunc(display);


  
	


  
   GLUI_Master.set_glutIdleFunc( myGlutIdle );
   
  // glutIdleFunc(display);  
   glutJoystickFunc(JoyFunc,10);
 /* name, flags,
								 x, and y */
const char* show="all";
  // glui->add_statictext(delay);
  glui->add_statictext( "Surgeon side" );
  glui->add_separator();
 
 glui->add_button( "Quit", 0,(GLUI_Update_CB)exit );
 //glui->add_button( "Connect", 0, control_cb);
 glui->add_button( "Transmit", 0, controls);
 glui->add_button( "Disconnect", 0, close);
 glui->add_column(true);
 GLUI_Panel *obj_panel = glui->add_panel ( "Delay in millisecond" );
 GLUI_StaticText   *edit ;
edit =	 glui->add_statictext_to_panel(obj_panel, delay);
edit->set_text(delay);
  GLUI_Panel *obj_panels = glui->add_panel ( "Data rate in kb/s" );
 glui->add_statictext_to_panel(obj_panels, datarate);
//glui->set_text(100);
 
 
 //glui->add_edittext_to_panel(
//obj_panel, delay,
//GLUI_EDITTEXT_TEXT,
//delay,-1 );
// glui->add_edittext_to_panel(obj_panel, "", GLUI_EDITTEXT_TEXT, delay, -1 );
//GLUI_StaticText::set_text(show);
 glui->set_main_gfx_window( window_id );
   glutMainLoop();
  WaitForSingleObject(hThread2,INFINITE);
   return 0;	
   return 0;
}


/////////////////////////////////////////////
// Quit and Release Joystick
/////////////////////////////////////////////

void ReleaseJoystick()
{
   
   if (joy_ok) 
	  joyReleaseCapture(joy_ID);// release joystick

}



///////////////////////////////////////
// Initialize Joystick
///////////////////////////////////////

bool InitJoystick()
{
   if ((joy_num = joyGetNumDevs()) == 0)
	   return FALSE; 
  
   if (joyGetPos(JOYSTICKID1, &joy_info) != JOYERR_UNPLUGGED) 
	   joy_ID = JOYSTICKID1; 
   else
	   return FALSE;

   joyGetDevCaps(joy_ID, &joy_caps, sizeof(JOYCAPS));
   joy_xcenter  = ((DWORD)joy_caps.wXmin + joy_caps.wXmax) / 2;
   joy_ycenter  = ((DWORD)joy_caps.wYmin + joy_caps.wYmax) / 2;
   joy_Zcenter  = ((DWORD)joy_caps.wZmin + joy_caps.wZmax) / 2; 

    joySetCapture(hWnd, joy_ID, NULL, TRUE);  
   

   return TRUE;
} 





////////////////////////////////////

void server (int r ,  int sent)
{
	
	if(allow==0)
	{ 

//////////////////////////////////////////////////////////////////////////////////
		if(sent==2)
		{r=r/364;
		r=r+70;}
		else if(sent==3)
		{ r=r/1092;
		r=r+140;
		}
		else if (sent==1)
		{ 
		r=r;
		}
		//////////////////////////////////////////////////////////////////////////
		char buffer[100];
	 itoa (r,buffer,10);
	int *m=new int (xy);
		
		seq = reinterpret_cast<char*>(m);
		
	
		SendBuf=buffer;
		if(disconnect==0)
		{ buffer[0]='~';} 
		SendBuf=buffer;
		char end=*SendBuf;
		if(xxx==1)
		{strcat(seq,"s");
			
			xxx=2;
		}
		else if(xxx==2)
		{
			strcat(seq,"y");
			xxx=3;
		}
		
		else if (xxx==3)
		{
			strcat(seq,"x");
			xxx=4;
		}
		else if (xxx==4)
		{
			strcat(seq,"b");
			xxx=1;
		}


	strcat(seq,SendBuf);
		store[xy]=seq;
	BufLength=strlen(seq);
	//cout<<"Seq is : "<<xy<<" ";
	 TotalByteSent = sendto(SendingSocket, seq, BufLength, 0, (SOCKADDR *)&Sender1Addr, sizeof(Sender1Addr));
	//if(end=='~')
		//exit(0);
		
		if(xy<=126)
		{
					
		
			xy=xy+1;
		}
		else xy=1;		
	
	}
	
}