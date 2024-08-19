#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>  //WindowsSocket���ͷ�ļ�
#include<iostream>
#include<cstring>
#include<string.h>
#include"cJSON.h"
#pragma comment(lib,"ws2_32.lib")//����ws2_32.lib���ļ�������Ŀ��
using namespace std;

//================ȫ�ֳ���==================
		 //����������
const int BUF_SIZE = 2048;
//================ȫ�ֱ���==================
SOCKET sockSer, sockCli;
SOCKADDR_IN addrSer, addrCli; //address
int naddr = sizeof(SOCKADDR_IN);

int ret=0;
char sendbuf[BUF_SIZE];
char inputbuf[BUF_SIZE];
char recvbuf[BUF_SIZE];
//================��������==================

//���ַ���ת��ΪUnicode
int toUnicode(const char* str)
{
	return str[0] + (str[1] ? toUnicode(str + 1) : 0);
}
//��Unicodeת��Ϊ�ַ���
constexpr inline int U(const char* str)
{
	return str[0] + (str[1] ? U(str + 1) : 0);
}



int main() {
	cout << "����������" << endl;
	//����socket��
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		//���������Ϣ
		cout << "����socket��ʧ��!" << endl;
		system("pause");
		return 0;
	}
	else {
		cout << "����socket��ɹ�!" << endl;
	}
	//����Soucket;
	sockSer = socket(AF_INET, SOCK_STREAM, 0);
	//����Э����,INET����ipv4��
	//sock_stream�����׽������ͣ�tcp��
	//0��ָ��Э�飬���õ�Э����tcp��udp��

	//��ʼ����ַ��
	addrSer.sin_addr.s_addr = inet_addr("192.168.10.8");
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(1111);

	//��Socket(bind)
	bind(sockSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));
	//ǿ�ƽ�SOCKADDR_INETת����SOCKEADDR



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

	cout << "�̼���Ϣ��" << json_str << endl;

	//����
	while (true) {
		cout << "��ʼ����!" << endl;
		//������������;
		listen(sockSer, 5);
		//�ȴ������������5

		//��������
		sockCli = accept(sockSer, (SOCKADDR*)&addrCli, &naddr);
		if (sockCli != INVALID_SOCKET) {
			cout << "���ӳɹ�" << endl;
			while (true)
			{
				
				recv(sockCli, recvbuf, sizeof(recvbuf), 0);
				cout << "�ͻ��˷�������Ϣ��" << recvbuf << endl;
				
				ret=strcmp(recvbuf, "QueryFirmwareVersion");

				if (ret== 0)
				{
					cout << "�ͻ�������̼���Ϣ" << endl;
					send(sockCli, json_str, sizeof(json_str), 0);									
					cout << "�ѷ��͹̼���Ϣ" << endl;
				}



				recv(sockCli, recvbuf, sizeof(recvbuf), 0);
				cout << "�ͻ���ѡ��Ĺ̼��汾��" << recvbuf << endl;
			
				switch (toUnicode(recvbuf))
				{
				  case U("breath 1.0"):
						strcpy(sendbuf, "breath 1.0�汾�Ĺ̼���ַ��breath 1.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
				  case U("breath 2.0"):
						strcpy(sendbuf, "breath 2.0�汾�Ĺ̼���ַ��breath 2.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;														
				  case U("height 1.0"):
						strcpy(sendbuf, "height 1.0�汾�Ĺ̼���ַ��height 1.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
				  case U("height 2.0"):
						strcpy(sendbuf, "height 2.0�汾�Ĺ̼���ַ��height 2.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;				
				  case U("human 1.0"):
						strcpy(sendbuf, "human 1.0�汾�Ĺ̼���ַ��human 1.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
				  case U("human 2.0"):
						strcpy(sendbuf, "human 2.0�汾�Ĺ̼���ַ��human 2.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;
			      case U("human 3.0"):
						strcpy(sendbuf, "human 3.0�汾�Ĺ̼���ַ��human 3.0.com");
						send(sockCli, sendbuf, sizeof(sendbuf), 0);
						break;					
				  default:
					    strcpy(sendbuf, "�����������������");
					    send(sockCli, sendbuf, sizeof(sendbuf), 0);
					    break;
				} 
 


				cout << "������Ҫ���͸��ͻ��˵���Ϣ��" << endl;
				cin >> sendbuf;
				send(sockCli, sendbuf, sizeof(sendbuf), 0);
				//strcpy(sendbuf, "hello");
				//send(sockCli, sendbuf, sizeof(sendbuf), 0);

				//���տͻ��˷�����Ϣ
				recv(sockCli, recvbuf, sizeof(recvbuf), 0);
				cout << "�ͻ��˷�������Ϣ��" << recvbuf << endl;
			}

		}
		else
		{
			cout << "����ʧ��!" << endl;
		}
	}
	closesocket(sockSer);
	closesocket(sockCli);
	return 0;

}