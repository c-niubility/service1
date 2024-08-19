#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>  //WindowsSocket编程头文件
#include<iostream>
#include<cstring>
#include<string.h>
#include"cJSON.h"
#pragma comment(lib,"ws2_32.lib")//链接ws2_32.lib库文件到此项目中
using namespace std;

//================全局常量==================
		 //创建缓冲区
const int BUF_SIZE = 2048;
//================全局变量==================
SOCKET sockSer, sockCli;
SOCKADDR_IN addrSer, addrCli; //address
int naddr = sizeof(SOCKADDR_IN);

int ret=0;
char sendbuf[BUF_SIZE];
char inputbuf[BUF_SIZE];
char recvbuf[BUF_SIZE];
//================函数声明==================

//将字符串转化为Unicode
int toUnicode(const char* str)
{
	return str[0] + (str[1] ? toUnicode(str + 1) : 0);
}
//将Unicode转化为字符串
constexpr inline int U(const char* str)
{
	return str[0] + (str[1] ? U(str + 1) : 0);
}



int main() {
	cout << "服务器启动" << endl;
	//加载socket库
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		//输出出错信息
		cout << "载入socket库失败!" << endl;
		system("pause");
		return 0;
	}
	else {
		cout << "载入socket库成功!" << endl;
	}
	//创建Soucket;
	sockSer = socket(AF_INET, SOCK_STREAM, 0);
	//描述协议族,INET属于ipv4；
	//sock_stream创建套接字类型：tcp；
	//0不指定协议，常用的协议有tcp、udp等

	//初始化地址包
	addrSer.sin_addr.s_addr = inet_addr("192.168.10.8");
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(1111);

	//绑定Socket(bind)
	bind(sockSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));
	//强制将SOCKADDR_INET转化成SOCKEADDR



	cJSON* root = cJSON_CreateObject();
	
	cJSON* item11 = cJSON_CreateString("breath 1.0.bin");
	cJSON* item12 = cJSON_CreateString("breath 2.0.bin");
	cJSON* item13 = cJSON_CreateString("breath 3.0.bin");
	cJSON* item14 = cJSON_CreateString("breath 4.0.bin");
	cJSON_AddItemToObject(root, "breath 1.0.bin",item11);
	cJSON_AddItemToObject(root, "breath 2.0.bin",item12),
	cJSON_AddItemToObject(root, "breath 3.0.bin",item13);
	cJSON_AddItemToObject(root, "breath 4.0.bin",item14);

	cJSON* item21 = cJSON_CreateString("height 1.0.bin");
	cJSON* item22 = cJSON_CreateString("height 2.0.bin");
	cJSON* item23 = cJSON_CreateString("height 3.0.bin");
	cJSON_AddItemToObject(root, "height 1.0.bin",item21);
	cJSON_AddItemToObject(root, "height 2.0.bin",item22),
	cJSON_AddItemToObject(root, "height 3.0.bin",item23);

	cJSON* item31 = cJSON_CreateString("human 1.0.bin");
	cJSON* item32 = cJSON_CreateString("human 2.0.bin");
	cJSON* item33 = cJSON_CreateString("human 3.0.bin");
	cJSON_AddItemToObject(root, "human 1.0.bin",item31);
	cJSON_AddItemToObject(root, "human 2.0.bin",item32),
	cJSON_AddItemToObject(root, "human 3.0.bin",item33);

	char* json_str = cJSON_Print(root);

	cout << "固件信息：" << json_str << endl;

	//监听
	while (true) {
		cout << "开始连接!" << endl;
		//监听连接请求;
		listen(sockSer, 5);
		//等待连接最大数：5

		//接受连接
		sockCli = accept(sockSer, (SOCKADDR*)&addrCli, &naddr);
		if (sockCli != INVALID_SOCKET) {
			cout << "连接成功" << endl;
			while (true)
			{
				
				recv(sockCli, recvbuf, sizeof(recvbuf), 0);
				cout << "客户端发来的信息：" << recvbuf << endl;
				
				ret=strcmp(recvbuf, "QueryFirmwareVersion");

				if (ret== 0)
				{
					cout << "客户端请求固件信息" << endl;
					send(sockCli, json_str, sizeof(json_str), 0);									
					cout << "已发送固件信息" << endl;
				}



				recv(sockCli, recvbuf, sizeof(recvbuf), 0);
				cout << "客户端选择的固件版本：" << recvbuf << endl;
			
				switch (toUnicode(recvbuf))
				{
				  case U("breath 1.0"):
						strcpy(sendbuf, "breath 1.0版本的固件网址：breath 1.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
				  case U("breath 2.0"):
						strcpy(sendbuf, "breath 2.0版本的固件网址：breath 2.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;														
				  case U("height 1.0"):
						strcpy(sendbuf, "height 1.0版本的固件网址：height 1.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
				  case U("height 2.0"):
						strcpy(sendbuf, "height 2.0版本的固件网址：height 2.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;				
				  case U("human 1.0"):
						strcpy(sendbuf, "human 1.0版本的固件网址：human 1.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
				  case U("human 2.0"):
						strcpy(sendbuf, "human 2.0版本的固件网址：human 2.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
			      case U("human 3.0"):
						strcpy(sendbuf, "human 3.0版本的固件网址：human 3.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;					
				  default:
					    strcpy(sendbuf, "输入错误，请重新输入");
					    send(sockCli, sendbuf, sizeof(sendbuf), 0);
					    break;
				} 
 


				cout << "请输入要发送给客户端的信息：" << endl;
				cin >> sendbuf;
				send(sockCli, sendbuf, sizeof(sendbuf), 0);
				//strcpy(sendbuf, "hello");
				//send(sockCli, sendbuf, sizeof(sendbuf), 0);

				//接收客户端发来信息
				recv(sockCli, recvbuf, sizeof(recvbuf), 0);
				cout << "客户端发来的信息：" << recvbuf << endl;
			}

		}
		else
		{
			cout << "连接失败!" << endl;
		}
	}
	closesocket(sockSer);
	closesocket(sockCli);
	return 0;

}