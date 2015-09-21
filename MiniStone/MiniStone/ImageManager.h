#pragma once
#include "ImageDB.h"
#include "define.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;


class ImageManager
{
private:
	typedef std::list<ImageVec*> LISTOFVECTOR;

	static ImageManager			*myInstance;

	LISTOFVECTOR				listImgVec;
	//HWND g_hWnd �̰� extern ���� �����ͷ� �޾Ƽ� ����ص��Ǵ��� Ȯ��..

public:
	static ImageManager *getInstance(){
		if (!myInstance)
			myInstance = new ImageManager();
		
		return myInstance;
	}
	
	void setHandle();
	static void Release();
	
	ImageVec* imgInit(const char* _str);

public:
	ImageManager(){}
	~ImageManager(){}
};

