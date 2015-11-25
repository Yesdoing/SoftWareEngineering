#pragma once
#include "define.h"
#include "preCompile.h"
#include "ImageDB.h"

static int retval;
static int sock;
extern pass E_recv;
//extern bool Myturn;

class Network{
private:
	static Network	*myInstance;
	char buff[1024];

private:
	Network(){}
	~Network(){}

public:

	

	int init()
	{

		// ���� �ʱ�ȭ
		WSADATA wsa;

		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("Winsock()\n");
			return 1;
		}

		// ������ �����ϱ� ���� ���� ����
		sockaddr_in server;

		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == SOCKET_ERROR)
		{
			printf("socket()n");
			closesocket(sock);
			WSACleanup();
			return 1;
		}

		server.sin_addr.s_addr = inet_addr(IP);
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);

		// ������ ����
		if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
		{
			printf("connect()\n");
			closesocket(sock);
			WSACleanup();
			return 1;

		}

		printf("Connection Complete\n");

		// �������� �켱 �ִ� Welcome �޽��� �м�
		retval = recv(sock, buff, 1024, 0);
		printf("%s", buff);

		//if (strcmp("0", buff))// 0 �� ���� ������ �� , 1�� ���߿� ������ ��. buff strcmpy
		//	Myturn = false;
		//else if (strcmp("1", buff))
		//	Myturn = true;

		// ���� á�ٰ� �޽����� �Դٸ�
		if (!strcmp("FULL\n", buff))
		{
			closesocket(sock);
			WSACleanup();
			return 0;			// ������ ����
		}

		

		// ���� ������ �Ǹ� ������ �۵� - �޴� �޽����� ������� �ǽð� ����
		_beginthread(recv_thread, 0, NULL);

		
	}

	void send_message(pass _info){
		if (retval != INVALID_SOCKET || retval != SOCKET_ERROR)
		{

			// ������ : CPU ������ ���ҿ�
			//Sleep(10);
			//printf("���� �޽��� �Է� : ");
			//		fgets(buff, 1024, stdin);
			//fgets((char*)&info, sizeof(info), stdin);


			// ���� ��� �߸� �� ����� ������� Ż��
			//	if (retval == INVALID_SOCKET || retval == SOCKET_ERROR) break;

			// ������ ������ ���� fgets �� �ް� ���� ���������� ����
			//ret = send(s, (char*)buff, strlen(buff), 0);
			retval = send(sock, (char*)&_info, sizeof(struct pass), 0);

			// ���� �ʱ�ȭ
			//memset(buff, 0, 1024);

		}

		// ����/���������� ������ ��� ������� Ʋ�� ���� �޾��� ��
		//	printf("������ ������ ������ϴ�.\n");
		//	closesocket(sock);
		//	WSACleanup();
	}
	
	// �޴� ������ �κ�
	static void recv_thread(void* pData)
	{
		pass recvpss;
		int ret_thread = 65535;
		char buff_thread[1024] = "";

		// ������� ���� ���� ����ϴ� ���� �ƴϸ� �޴� �߿� ������ ����� ����ٰ� ���� ����
		while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
		{
			Sleep(10);	// CPU ������ 100% ������

			// �������� �ִ� �޽����� ��pass recvpss;
			int ret_thread = 65535;
			char buff_thread[1024] = "";
			//	ret_thread = recv(s, buff_thread, sizeof(buff_thread), 0);

			ret_thread = recv(sock, (char*)&recvpss, sizeof(recvpss), 0);

			// �������� �޴� �۾��� �� ��� �������� �� Ż��
			if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR)
				break;

			E_recv = recvpss;
			int a = 10;

			for (int i = 0; i < 8; i++){
				recvpss.Cfield[i] = -1;

				for (int j = 0; j < 2; j++){
					recvpss.Attackflag[i][j] = -1;
				}
			}

			recvpss.E_Hand = -1;
			recvpss.cTurn = false;
			// ���������� ���� ���۸� ���
			//		printf("\n%d �޽��� ���� : %s", ret_thread, (char*)&info);



			memset(buff_thread, 0, 1024);	// ���� ���۸� �ʱ��
		}

		// �۾��� ���� ������ ��ȿȭ��Ŵ
		retval = INVALID_SOCKET;

		return;
	}

	static Network *getInstance(){
		if (!myInstance)
			myInstance = new Network;

		return myInstance;
	}

};