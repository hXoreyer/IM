#include <stdio.h>
#include <winsock2.h>
 
#pragma comment(lib,"ws2_32.lib")
#define	BUF_SIZE	1024
#define PORT_		5500
 
int main(void)
{
	WSADATA wsd;
	int iRet = 0;
 
	// 初始化套接字动态库
	if(WSAStartup(MAKEWORD(2,2), &wsd)!= 0){
		printf("WSAStartup failed:%d!\n", WSAGetLastError());
		return -1;
	}
 
	SOCKET socketSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	SOCKADDR_IN addrClient;
	char strRecv[BUF_SIZE] = {0}, strSend[BUF_SIZE] = "udp server send";
	int len = sizeof(SOCKADDR);
 
	// 设置服务器地址
	ZeroMemory(strRecv,BUF_SIZE);
	//addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT_);
 
	// 绑定套接字
	iRet = bind(socketSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if(SOCKET_ERROR == iRet)
	{ 
		printf("bind failed%d!\n", WSAGetLastError());
		closesocket(socketSrv);
		WSACleanup();
	}
 
	// 从客户端接收数据
	printf("udp server start...\n");
	while(TRUE)
	{
		iRet = recvfrom(socketSrv,strRecv,BUF_SIZE,0,(SOCKADDR*)&addrClient,&len);
		if(SOCKET_ERROR == iRet){ 
			printf("recvfrom failed !\n");
			closesocket(socketSrv);
			WSACleanup();
			return -1;
		}
 
		printf("Recv From Client:%s\n", strRecv);
 
		// 向客户端发送数据
		sendto(socketSrv, strSend, sizeof(strSend), 0, (SOCKADDR*)&addrClient, len);
	}
	
	closesocket(socketSrv);
	WSACleanup();
 
	return 0;
}