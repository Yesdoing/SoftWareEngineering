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

		// 윈속 초기화
		WSADATA wsa;

		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("Winsock()\n");
			return 1;
		}

		// 서버로 접속하기 위한 소켓 생성
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

		// 서버와 연결
		if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
		{
			printf("connect()\n");
			closesocket(sock);
			WSACleanup();
			return 1;

		}

		printf("Connection Complete\n");

		// 서버에서 우선 주는 Welcome 메시지 분석
		retval = recv(sock, buff, 1024, 0);
		printf("%s", buff);

		//if (strcmp("0", buff))// 0 이 먼저 들어오는 놈 , 1이 나중에 들어오는 놈. buff strcmpy
		//	Myturn = false;
		//else if (strcmp("1", buff))
		//	Myturn = true;

		// 가득 찼다고 메시지가 왔다면
		if (!strcmp("FULL\n", buff))
		{
			closesocket(sock);
			WSACleanup();
			return 0;			// 접속을 종료
		}

		

		// 정상 접속이 되면 스레드 작동 - 받는 메시지를 스레드로 실시간 수행
		_beginthread(recv_thread, 0, NULL);

		
	}

	void send_message(pass _info){
		if (retval != INVALID_SOCKET || retval != SOCKET_ERROR)
		{

			// 딜레이 : CPU 점유율 감소용
			//Sleep(10);
			//printf("보낼 메시지 입력 : ");
			//		fgets(buff, 1024, stdin);
			//fgets((char*)&info, sizeof(info), stdin);


			// 전송 결과 잘못 된 결과를 얻었을때 탈출
			//	if (retval == INVALID_SOCKET || retval == SOCKET_ERROR) break;

			// 서버로 보내는 글은 fgets 을 받고 나서 순차적으로 보냄
			//ret = send(s, (char*)buff, strlen(buff), 0);
			retval = send(sock, (char*)&_info, sizeof(struct pass), 0);

			// 버퍼 초기화
			//memset(buff, 0, 1024);

		}

		// 정상/비정상으로 서버와 통신 결과값이 틀린 값을 받았을 때
		//	printf("서버와 연결이 끊겼습니다.\n");
		//	closesocket(sock);
		//	WSACleanup();
	}
	
	// 받는 스레드 부분
	static void recv_thread(void* pData)
	{
		pass recvpss;
		int ret_thread = 65535;
		char buff_thread[1024] = "";

		// 스레드용 리턴 값이 우너하는 값이 아니면 받는 중에 서버와 통신이 끊겼다고 보고 나감
		while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
		{
			Sleep(10);	// CPU 점유률 100% 방지용

			// 서버에서 주는 메시지를 실pass recvpss;
			int ret_thread = 65535;
			char buff_thread[1024] = "";
			//	ret_thread = recv(s, buff_thread, sizeof(buff_thread), 0);

			ret_thread = recv(sock, (char*)&recvpss, sizeof(recvpss), 0);

			// 서버에서 받는 작업을 한 결과 비정상일 때 탈출
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
			// 정상적으로 받은 버퍼를 출력
			//		printf("\n%d 메시지 받음 : %s", ret_thread, (char*)&info);



			memset(buff_thread, 0, 1024);	// 받은 버퍼를 초기와
		}

		// 작업이 끝난 소켓을 무효화시킴
		retval = INVALID_SOCKET;

		return;
	}

	static Network *getInstance(){
		if (!myInstance)
			myInstance = new Network;

		return myInstance;
	}

};