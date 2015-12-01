#pragma once
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_CLASSNAME "MiniStone"
#define PORT 5000			// 사용할 포트는 5000
#define IP "165.229.86.107"		// 접속할 서버는 로컬 호스트



#ifdef _DEBUG
#define __DEV_MODE__
#endif



enum MYKEY_FLAG {
	MK_NONE = 0,
	MK_LEFT = 0x01 << 0,
	MK_RIGHT = 0x01 << 1,
	MK_UP = 0x01 << 2,
	MK_DOWN = 0x01 << 3,
	MK_ENTER = 0x01 << 4,
	MK_SPACE = 0x01 << 5,
	MK_A = 0x01 << 6,
	MK_S = 0x01 << 7,
	MK_D = 0x01 << 8,
	MK_F = 0x01 << 9,
	MK_Q = 0x01 << 10,
	MK_W = 0x01 << 11,
	MK_E = 0x01 << 12,
	MK_R = 0x01 << 13,
	MK_1 = 0x01 << 14,
	MK_2 = 0x01 << 15,
	MK_3 = 0x01 << 16,
	MK_4 = 0x01 << 17,
	MK_5 = 0x01 << 18,
	MK_6 = 0x01 << 19,
	MK_7 = 0x01 << 20,
	MK_I = 0x01 << 21,
	MK_T = 0x01 << 22,
	MK_Y = 0x01 << 23,
	MK_SHIF = 0x01 << 24,


	MK_LEFT_END = 0x01 << 25, // <- 키 누르다 뗐을때 검출
	MK_RIGHT_END = 0x01 << 26, // -> 키 누르다 뗐을때 검출

	MK_LCLK = 0x01 << 29,
	MK_RCLK = 0x01 << 30,

	MK_MAX_SIZE = 0x01 << 31 // 32자리
};