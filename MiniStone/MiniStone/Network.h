//#include"preCompile.h"
//
//void recv_thread(void*);	// 스레드 수행 함수의 프로토 타입
//
//int ret = 0;				// 리턴 값
//int s = 0;					// 소켓 값
//char buff[1024];
//
//struct pass {
//	int		turn;
//	char	c_num[4];
//	int		f_n;
//	int		attacker;
//	int		damage_num;
//	int		count;
//}info;
//
//class Network{
//private:
//	pass a;
//public:
//	//	Network();
//	//	~Network();
//	static int init()
//	{
//		// 윈속 초기화
//		WSADATA wsd;
//
//		if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
//		{
//		//	printf("Winsock 오류\n");
//			return 1;
//		}
//
//		// 서버로 접속하기 위한 소켓 생성
//		sockaddr_in server;
//
//		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		if (s == SOCKET_ERROR)
//		{
//	//		printf("socket() 오류\n");
//			closesocket(s);
//			WSACleanup();
//			return 1;
//		}
//
//		server.sin_addr.s_addr = inet_addr(IP);
//		server.sin_family = AF_INET;
//		server.sin_port = htons(PORT);
//
//		// 서버와 연결
//		if (connect(s, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
//		{
////			printf("connect() 오류\n");
//			closesocket(s);
//			WSACleanup();
//			return 1;
//
//		}
//
////		printf("서버와 연결이 되었음.\n");
//
//		// 서버에서 우선 주는 Welcome 메시지 분석
//		ret = recv(s, buff, 1024, 0);
////		printf("%s", buff);
//
//		// 가득 찼다고 메시지가 왔다면
//		if (!strcmp("가득찼습니다.\n", buff))
//		{
//			closesocket(s);
//			WSACleanup();
//			return 0;			// 접속을 종료
//		}
//
//		// 정상 접속이 되면 스레드 작동 - 받는 메시지를 스레드로 실시간 수행
//		_beginthread(recv_thread, 0, NULL);
//		// 보내는 메시지는 스레드로 넣을 필요가 없습니다.
//	}
//
////	static void send_message(){
//////		while (ret != INVALID_SOCKET || ret != SOCKET_ERROR)
////		if (ret != INVALID_SOCKET || ret != SOCKET_ERROR)
////		{
////
////			// 딜레이 : CPU 점유율 감소용
//////			Sleep(10);
//////			printf("보낼 메시지 입력 : ");
////			//		fgets(buff, 1024, stdin);
//////			fgets((char*)&info, sizeof(info), stdin);
////
////
////			// 전송 결과 잘못 된 결과를 얻었을때 탈출
////	//		if (ret == INVALID_SOCKET || ret == SOCKET_ERROR) break;
////
////			ret = send(s, (char*)&info, sizeof(info), 0); //여기서 저장된 구조체를 보낸다.
////
////			// 버퍼 초기화
////			memset(buff, 0, 1024); //구조체 초기화
////		}
////
////		// 정상/비정상으로 서버와 통신 결과값이 틀린 값을 받았을 때
////	//	printf("서버와 연결이 끊겼습니다.\n");
//////		closesocket(s);
////	//	WSACleanup();
////	}
//
//	static void send_message(){
//		if (ret != INVALID_SOCKET || ret != SOCKET_ERROR)
//		{
//			ret = send(s, (char*)&info, sizeof(info), 0); //여기서 저장된 구조체를 보낸다.
//
//			// 버퍼 초기화
//			memset(buff, 0, 1024); //구조체 초기화
//		}
//
//	}
//
//
//	// 받는 스레드 부분
//	static void recv_thread(void* pData)
//	{
//		int ret_thread = 65535;
//		char buff_thread[1024] = "";
//		pass b;
//		// 스레드용 리턴 값이 우너하는 값이 아니면 받는 중에 서버와 통신이 끊겼다고 보고 나감
//		while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
//		{
//			Sleep(10);	// CPU 점유률 100% 방지용
//
//			// 서버에서 주는 메시지를 실시간으로 기다렸다가 받습니다.
//			//	ret_thread = recv(s, buff_thread, sizeof(buff_thread), 0);
//
//			ret_thread = recv(s, (char*)&info, sizeof(info), 0);
//
//			// 서버에서 받는 작업을 한 결과 비정상일 때 탈출
//			if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR)
//				break;
////			a = info;
//			// 정상적으로 받은 버퍼를 출력
//			b = info;
////			printf("\n%d 메시지 받음 : %s", ret_thread, (char*)&info);
////			memset(buff_thread, 0, 1024);	// 받은 버퍼를 초기와
//		}
//
//		// 작업이 끝난 소켓을 무효화시킴
//		ret = INVALID_SOCKET;
//
//		return;
//	}
//
//	void start(){
//		init();
//		send_message();
//	}
//};
