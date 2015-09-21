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
	//HWND g_hWnd 이거 extern 말고 포인터로 받아서 사용해도되는지 확인..

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

