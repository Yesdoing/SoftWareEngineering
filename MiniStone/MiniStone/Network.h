//#include"preCompile.h"
//
//void recv_thread(void*);	// ������ ���� �Լ��� ������ Ÿ��
//
//int ret = 0;				// ���� ��
//int s = 0;					// ���� ��
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
//		// ���� �ʱ�ȭ
//		WSADATA wsd;
//
//		if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
//		{
//		//	printf("Winsock ����\n");
//			return 1;
//		}
//
//		// ������ �����ϱ� ���� ���� ����
//		sockaddr_in server;
//
//		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		if (s == SOCKET_ERROR)
//		{
//	//		printf("socket() ����\n");
//			closesocket(s);
//			WSACleanup();
//			return 1;
//		}
//
//		server.sin_addr.s_addr = inet_addr(IP);
//		server.sin_family = AF_INET;
//		server.sin_port = htons(PORT);
//
//		// ������ ����
//		if (connect(s, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
//		{
////			printf("connect() ����\n");
//			closesocket(s);
//			WSACleanup();
//			return 1;
//
//		}
//
////		printf("������ ������ �Ǿ���.\n");
//
//		// �������� �켱 �ִ� Welcome �޽��� �м�
//		ret = recv(s, buff, 1024, 0);
////		printf("%s", buff);
//
//		// ���� á�ٰ� �޽����� �Դٸ�
//		if (!strcmp("����á���ϴ�.\n", buff))
//		{
//			closesocket(s);
//			WSACleanup();
//			return 0;			// ������ ����
//		}
//
//		// ���� ������ �Ǹ� ������ �۵� - �޴� �޽����� ������� �ǽð� ����
//		_beginthread(recv_thread, 0, NULL);
//		// ������ �޽����� ������� ���� �ʿ䰡 �����ϴ�.
//	}
//
////	static void send_message(){
//////		while (ret != INVALID_SOCKET || ret != SOCKET_ERROR)
////		if (ret != INVALID_SOCKET || ret != SOCKET_ERROR)
////		{
////
////			// ������ : CPU ������ ���ҿ�
//////			Sleep(10);
//////			printf("���� �޽��� �Է� : ");
////			//		fgets(buff, 1024, stdin);
//////			fgets((char*)&info, sizeof(info), stdin);
////
////
////			// ���� ��� �߸� �� ����� ������� Ż��
////	//		if (ret == INVALID_SOCKET || ret == SOCKET_ERROR) break;
////
////			ret = send(s, (char*)&info, sizeof(info), 0); //���⼭ ����� ����ü�� ������.
////
////			// ���� �ʱ�ȭ
////			memset(buff, 0, 1024); //����ü �ʱ�ȭ
////		}
////
////		// ����/���������� ������ ��� ������� Ʋ�� ���� �޾��� ��
////	//	printf("������ ������ ������ϴ�.\n");
//////		closesocket(s);
////	//	WSACleanup();
////	}
//
//	static void send_message(){
//		if (ret != INVALID_SOCKET || ret != SOCKET_ERROR)
//		{
//			ret = send(s, (char*)&info, sizeof(info), 0); //���⼭ ����� ����ü�� ������.
//
//			// ���� �ʱ�ȭ
//			memset(buff, 0, 1024); //����ü �ʱ�ȭ
//		}
//
//	}
//
//
//	// �޴� ������ �κ�
//	static void recv_thread(void* pData)
//	{
//		int ret_thread = 65535;
//		char buff_thread[1024] = "";
//		pass b;
//		// ������� ���� ���� ����ϴ� ���� �ƴϸ� �޴� �߿� ������ ����� ����ٰ� ���� ����
//		while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
//		{
//			Sleep(10);	// CPU ������ 100% ������
//
//			// �������� �ִ� �޽����� �ǽð����� ��ٷȴٰ� �޽��ϴ�.
//			//	ret_thread = recv(s, buff_thread, sizeof(buff_thread), 0);
//
//			ret_thread = recv(s, (char*)&info, sizeof(info), 0);
//
//			// �������� �޴� �۾��� �� ��� �������� �� Ż��
//			if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR)
//				break;
////			a = info;
//			// ���������� ���� ���۸� ���
//			b = info;
////			printf("\n%d �޽��� ���� : %s", ret_thread, (char*)&info);
////			memset(buff_thread, 0, 1024);	// ���� ���۸� �ʱ��
//		}
//
//		// �۾��� ���� ������ ��ȿȭ��Ŵ
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
