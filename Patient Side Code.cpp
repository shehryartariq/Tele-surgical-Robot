

#include <winsock2.h>
#include<iostream>
#include <stdio.h>
#include<string>
#include<time.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
void transmitbutton(int);

WSADATA              wsaData;
SOCKET               SendingSocket, ReceivingSocket;
SOCKADDR_IN          ReceiverAddr;
int                  Port = 80;
int allow=1;
int xp1=0,yp1=0,bp1=0,xp2=0,yp2=0,bp2=0;

char k,h;
		unsigned int l;
char                 *SendBuf;
char				 sendbuf[256];
int                  BufLength = 1024;
int					 TotalByteSent;
char				 ipAddress[30];
char				 *IPAddress;
char                 ReceiveBuf[1024];
SOCKADDR_IN          Sender1Addr;
SOCKADDR_IN          SenderAddr;
int                  SenderAddrSize = sizeof(SenderAddr);
int                  ByteReceived = 1024;
int					 x=1,i1,i2,i3,i4;
char      axx='x';
int					 seq=0; 
char				 *resend;
char				 *buffer;
int					 *m;
int					 r=0,wop=1;
string				 store[256];
char				 putback[20];
int					 received[256];
int					 check=0,selectline =2;
HANDLE hPort,hPort1,hPort2;
void transmit(int);
void write (char* );
void write2 (char* );

/////////////////////////////////////////////////////////////
void initials()
{
	DCB dcb;
	hPort = CreateFile("\\\\.\\COM13",GENERIC_WRITE|GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	if (!GetCommState(hPort,&dcb))
	{ cout<<"can't get rate "<<endl;
	}
	dcb.BaudRate = CBR_38400; //9600 Baud
	dcb.ByteSize = 8; //8 data bits
	dcb.Parity = NOPARITY; //no parity
	dcb.StopBits = ONESTOPBIT; //1 stop
	if (SetCommState(hPort,&dcb) == 0)
	{
		cout<<"can't set rate @ com13"<<endl;
	}
	COMMTIMEOUTS comTimeOut;                   
// Specify time-out between charactor for receiving.

    comTimeOut.ReadIntervalTimeout = 5;
// Specify value that is multiplied 

// by the requested number of bytes to be read. 

    comTimeOut.ReadTotalTimeoutMultiplier = 5;
// Specify value is added to the product of the 

// ReadTotalTimeoutMultiplier member

    comTimeOut.ReadTotalTimeoutConstant = 5;
// Specify value that is multiplied 

// by the requested number of bytes to be sent. 

   comTimeOut.WriteTotalTimeoutMultiplier = 5;
// Specify value is added to the product of the 

// WriteTotalTimeoutMultiplier member

   comTimeOut.WriteTotalTimeoutConstant = 5;
// set the time-out parameter into device control.

    SetCommTimeouts(hPort,&comTimeOut);
	if (!SetCommState(hPort,&dcb))
	{  
		cout<<"can't set time "<<endl;
		
	}
}
////////////////////////////////////////////////////////////////////
void initials2()
{
	DCB dcb;
	hPort2 = CreateFile("\\\\.\\COM14",GENERIC_WRITE|GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	if (!GetCommState(hPort,&dcb))
	{ cout<<"can't get rate "<<endl;
	}
	dcb.BaudRate = CBR_19200; //9600 Baud
	dcb.ByteSize = 8; //8 data bits
	dcb.Parity = NOPARITY; //no parity
	dcb.StopBits = ONESTOPBIT; //1 stop
	if (SetCommState(hPort,&dcb) == 0)
	{
		cout<<"can't set rate "<<endl;
	}
	COMMTIMEOUTS comTimeOut;                   
// Specify time-out between charactor for receiving.

    comTimeOut.ReadIntervalTimeout = 5;
// Specify value that is multiplied 

// by the requested number of bytes to be read. 

    comTimeOut.ReadTotalTimeoutMultiplier = 5;
// Specify value is added to the product of the 

// ReadTotalTimeoutMultiplier member

    comTimeOut.ReadTotalTimeoutConstant = 5;
// Specify value that is multiplied 

// by the requested number of bytes to be sent. 

   comTimeOut.WriteTotalTimeoutMultiplier = 5;
// Specify value is added to the product of the 

// WriteTotalTimeoutMultiplier member

   comTimeOut.WriteTotalTimeoutConstant = 5;
// set the time-out parameter into device control.

    SetCommTimeouts(hPort,&comTimeOut);
	if (!SetCommState(hPort,&dcb))
	{  
		cout<<"can't set time "<<endl;
		
	}
}


//////////////////////////////////////////////////////////////
DWORD WINAPI StartThre(LPVOID iValue)
{
	while(1)
	{
			if(allow==1)
			{
				write(&axx);
				write2(&axx);
				allow=2;
			}
			if (putback[0]=='s' && wop==1)
		{
			
			putback[0]='0';
			 i1 = atoi (putback);
			 cout<<i1<<"  "<<endl;
			 wop=2;
			 if(i1==1)   selectline=4;  
			 else if (i1==2)   selectline=5;
			
		}

		
		if (putback[0]=='y' && wop==2)
		{
			
			putback[0]='0';
			 i2 = atoi (putback);
			// cout<<i2<<"  ";
			 wop=3;
			 l=i2;
		     k=l;
			 h=l>>8;
		 if(selectline==4)  {  write(&h);     cout<<"  y1  "<<i2<<"  y2  "<<yp2;
		 write(&k); yp1=i2;
		 	 l=yp2;
		     k=l;
			 h=l>>8;
		 write2(&h);
		 write2(&k);
		 
		 }
		 else if(selectline==5)
		 {  yp2=i2;     cout<<"\n  y1  "<<yp1<<"  y2  "<<i2<<endl;
			  write2(&h);
		 write2(&k); 
		  l=yp1;
		     k=l;
			 h=l>>8;
		 write(&h);
		 write(&k);

		 }
		}
		
			
		
		if (putback[0]=='x' && wop==3)
		{
			putback[0]='0';
			 i3 = atoi (putback);
		//	 cout<<i3<<"   ";
			 l=i3;
		     k=l;
			 if(selectline==4){ write(&k); xp1=i3; cout<<"  x1  "<<i3<<"  x2  "<<xp2<<endl;
			 l=xp2;
		     k=l;
			 write2(&k);
			 
			 }
			 else if(selectline==5) {write2(&k);xp2=i3;
			 l=xp1;  cout<<"  x1  "<<xp1<<"  x2  "<<i3<<endl;
		     k=l;
			 write(&k);
			 
			 
			 
			 }
			 wop=4;
		}
		
		if (putback[0]=='b' && wop==4)
		{
			putback[0]='0';
			 i4 = atoi (putback);
			// cout<<i4<<endl;
			  l=i4;
		      k=l;
			  if(selectline==4) {write(&k); bp1=i4;
			   l=bp2;
		      k=l;     cout<<"  b1  "<<i4<<"  b2  "<<bp2<<endl;
			  write2(&k);
			  
			  
			  }
			  else if(selectline==5){ write2(&k); bp2=i4;
			  l=bp1;
		      k=l;
			  write(&k);  cout<<"  b1  "<<bp1<<"  b2  "<<i4<<endl;
			  }
			 wop=1;
		}
	}
	return 0;
} 
//////////////////////////////////////////////////////////////////
DWORD WINAPI StartThreads(LPVOID iValue)
{ int i=1;
	DWORD dwRead;
	char  chRead;
    while(1)
	{ cin>>i;
		if(i==1)
	{ //write(&xx); 
		i=2;}
		if (ReadFile(hPort, &chRead, 1, &dwRead, NULL))
		{
			if(chRead!='~')
			{
				cout<<chRead;
				dwRead=0;
				chRead='~';
			}	
		}
	}
	return 0;
}



///////////////////////////////////////////////////////////////
DWORD WINAPI StartThread(LPVOID iValue)
{
	
	while(1)
	{
		
		// At this point you can receive datagrams on your bound socket.
		int BufLengths=20;

		ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLengths, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
		ReceiveBuf[ByteReceived]='\0';
	//	cout<<"ReceiveBuf at "<<x<<" is: "<<ReceiveBuf<<endl;
		if(ReceiveBuf[2]=='~')
			break;
		buffer=ReceiveBuf;
		seq = static_cast<int>(ReceiveBuf[0]);
		if(seq<=0)
		{seq=seq+256;
		}
		if(check<seq)
		{
			check=seq;
		}
		received[seq]=1;
		
		store[seq]=buffer;
		
again:	
		
		if(x<check && received[x]!=1)
		{
			
			m=new int (x);
			
			
			resend = reinterpret_cast<char*>(m);
			
			char				 sending[256]="o";
			strcat(sending,resend);
			SendBuf=sending;
			BufLength=strlen(SendBuf);
						
			TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&Sender1Addr, sizeof(Sender1Addr));
			
	
	

		}
		
		
		
		else if(x<check && received[x]==1)
		{
			
			for(int z=1; z<store[x].size(); z++) 
			{
				if(z<=18)
					putback[z-1] = (char)store[x].at(z);
				
			}
			putback[store[x].size()-1]='\0';
			//cout<<"Putback at "<<x<<" is: "<<putback<<endl;
			received[x]=0;
			if(x<=126)	
				x=x+1;
			else
				x=1;
			
			goto again;	
			
		}
		
		
		
		else if(x==check)
			
		{
			
			for(int z=1; z<store[x].size(); z++) 
			{
				if(z<=18)
					putback[z-1] = (char)store[x].at(z);
				
			}
			putback[store[x].size()-1]='\0';
			//cout<<"Putback at "<<x<<" is: "<<putback<<endl;
			received[x]=0;
			if(x<=126)	
				x=x+1;
			else
				x=1;
			
		}
		
		
		
		if(check==127)
			check=0;
	} 
	
	return 0;
	
	
	
}


//////////////////////////////////////////////////////////

void thread()
{
	HANDLE hThread1,hThread2,hThread3;
	DWORD dwGenericThread;
	char lszThreadParam[3];
	strcpy(lszThreadParam,"3");
	hThread1 = CreateThread(NULL,0,StartThread,&lszThreadParam,0,&dwGenericThread);
	if(hThread1 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Eror in Creating thread"<<dwError<<endl ;
		return;
	}
	/////////////////////////////////////////////////////////
	DWORD dwGenericThreads;
	char lszThreadParams[3];
	strcpy(lszThreadParams,"3");
	hThread3 = CreateThread(NULL,0,StartThreads,&lszThreadParams,0,&dwGenericThreads);
	if(hThread3 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Eror in Creating thread"<<dwError<<endl ;
		return;
	}





	//////////////////////////////////////////////////////////////////
	//Second thread creation
	strcpy(lszThreadParam,"30");
	hThread2 = CreateThread(NULL,0,StartThre,&lszThreadParam,0,&dwGenericThread);
	if(hThread1 == NULL)
	{
		DWORD dwError = GetLastError();
		cout<<"SCM:Error in Creating thread"<<dwError<<endl ;
		return;
	}
	WaitForSingleObject(hThread2,INFINITE);
	WaitForSingleObject(hThread1,INFINITE);
	WaitForSingleObject(hThread3,INFINITE);
}


/////////////////////////////////////////////////////////////////////





int initial()
{
	// Initialize Winsock version 2.2
	if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		printf("Client: WSAStartup failed with error %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	
	// Create a new socket to receive datagrams on.
	SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendingSocket == INVALID_SOCKET)
	{
		printf("Client: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	
	ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (ReceivingSocket == INVALID_SOCKET)
	{
		printf("Server: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
		// Exit with error
		return -1;
	}
	
	
	cout<<"Enter IP Address: ";
	cin>>ipAddress;
	IPAddress=ipAddress;
	
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(Port);
	ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
	{
		printf("Server: bind() failed! Error: %ld.\n", WSAGetLastError());
		// Close the socket
		closesocket(ReceivingSocket);
		// Do the clean up
		WSACleanup();
		// and exit with error
		return -1;
	}
	
	Sender1Addr.sin_family = AF_INET;
	Sender1Addr.sin_port = htons(Port);
	Sender1Addr.sin_addr.s_addr = inet_addr(IPAddress);
	SendBuf="Start";
	BufLength=strlen(SendBuf);
	TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&Sender1Addr, sizeof(Sender1Addr));
	////////////////////////////
	int BufLengths=256;
	ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLengths, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
	ReceiveBuf[ByteReceived]='\0';
	
	SendBuf=ReceiveBuf;
	BufLength=strlen(SendBuf);
	TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&Sender1Addr, sizeof(Sender1Addr));
	
	
	//////////////////////////////////
	
	
	clock_t endwait;
	endwait = clock () + 10 * CLK_TCK ;
	char datarate[256];
	datarate[0]='&';
	for(int i=1; i<256; i++)
	{
		datarate[i]='&';
	}
	char * datarates;
	datarates=datarate;
	
	
	BufLength=strlen(datarates);
	while(clock()<endwait)
	{
		
		TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&Sender1Addr, sizeof(Sender1Addr));
		
		
	}
	
	
	cout<<"Done"<<endl;
	
	
	/////////////////////////////////////
	return 0;
	
	
	
}
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void write (char* data)
{ 
	DWORD byteswritten;
	bool retVal = WriteFile(hPort,data,1,&byteswritten,NULL);
}
//////////////////////////////////////////////
void write2 (char* data)
{ 
	DWORD byteswritten;
	bool retVal = WriteFile(hPort2,data,1,&byteswritten,NULL);
}
////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	initials2();
	initials();
	initial();
	
	thread();  
	
	return 0;
}
///////////////////////////////////////////////////////////
void transmit(int r)
{ char k,h;
unsigned int l;
l=r;
k=l;
	h=l>>8;

		 write(&h);
		 write(&k);
	
}



/////////////////////////////////////////////////////
void transmitbutton(int pp)
{

	unsigned int pl=pp;

	char kkkk=pl;


	//cout<<kkkk;
	 write(&kkkk);


}

