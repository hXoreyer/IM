
#include <stdio.h>
#include <winsock2.h>
 
#pragma comment(lib,"ws2_32.lib")
#define	BUF_SIZE	1024
 
#pragma pack(4)
enum MSG_TYPE
{
    LOGIN_,
    CHAR_,
    FILE_,
    IMG_,
	CHAT_
};

struct MSG_CONTENT
{
    MSG_TYPE TYPE;
    char send_char[1024];
    char recv_user[20];
    char send_user[20];
	sockaddr_in addr;
};
#pragma pack()

int  PORT_ = 5500;
int main(void)
{
	WSADATA wsd;
	int iRet = 0;
 
	// 初始化套接字动态库
	if(WSAStartup(MAKEWORD(2,2), &wsd) != 0){
		iRet = WSAGetLastError();
		printf("WSAStartup failed !\n");
		return -1;
	}
 
	char strSend[BUF_SIZE] = "test udp send", strRecv[BUF_SIZE] = {0};
	SOCKADDR_IN servAddr;
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
 
	// 设置服务器地址
	servAddr.sin_family = AF_INET;
	//servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.104");
	servAddr.sin_addr.S_un.S_addr = inet_addr("47.106.14.185");
	servAddr.sin_port = htons(PORT_);
 
	// 向服务器发送数据
	MSG_CONTENT msg;
	msg.TYPE = LOGIN_;
	strcpy(msg.send_user,"1067374087@qq.com");
	char sendmsg[sizeof(MSG_CONTENT)];
	memcpy(sendmsg,&msg,sizeof(MSG_CONTENT));
	int nServAddLen = sizeof(servAddr);
	iRet = sendto(sockClient, sendmsg, sizeof(MSG_CONTENT), 0, (sockaddr *)&servAddr, nServAddLen);
	if(iRet == SOCKET_ERROR){
		printf("sendto() failed:%d\n", WSAGetLastError());
		closesocket(sockClient);
		WSACleanup();
		return -1;
	}

	msg.TYPE = CHAT_;
	strcpy(msg.send_user,"1067374087@qq.com");
	strcpy(msg.recv_user,"1067374087@qq.com");
	memset(sendmsg,0,sizeof(MSG_CONTENT));
	memcpy(sendmsg,&msg,sizeof(MSG_CONTENT));
	iRet = sendto(sockClient, sendmsg, sizeof(MSG_CONTENT), 0, (sockaddr *)&servAddr, nServAddLen);
	if(iRet == SOCKET_ERROR){
		printf("sendto() failed:%d\n", WSAGetLastError());
		closesocket(sockClient);
		WSACleanup();
		return -1;
	}

	memset(&msg,0,sizeof(MSG_CONTENT));
	memset(sendmsg,0,sizeof(MSG_CONTENT));
	iRet = recvfrom(sockClient,sendmsg,sizeof(MSG_CONTENT),0,reinterpret_cast<sockaddr*>(&servAddr),&nServAddLen);
	memcpy(&msg,sendmsg,sizeof(MSG_CONTENT));
	if(iRet > 0)
	{
		printf("recv msg: %s",msg.send_char);
	}else{
		printf("recv error");
	}
	closesocket(sockClient);
	WSACleanup();
	
	return 0;
}