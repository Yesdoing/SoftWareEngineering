#pragma once
#include "preCompile.h"
#include "ImageDB.h"
#include "define.h"
#include<algorithm>

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;


class ImageManager
{
	struct Ani
	{
		int cur;
		ImageVec* img;
		POINT position;
	};

private:

	typedef std::list<ImageVec*> LISTOFVECTOR;

	static ImageManager			*myInstance;

	typedef std::map<std::string, ImageVec*> MAPEFFECTDB;
	MAPEFFECTDB EffectMap;


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

	//======================
private:
	std::list<Ani>	loof;
	std::list<Ani>	once;
	DWORD tick;
	DWORD CURtick;
	DWORD value;

public:
	void SetAni(std::string key, POINT pos){
		loof.push_back(Ani());
		loof.back().position.x = pos.x;
		loof.back().position.y = pos.y;
		loof.back().cur = 0;
		loof.back().img = EffectMap[key];
	}

	void init(){
		tick = GetTickCount();
		value = 100;
	}

	void update(){
		CURtick = GetTickCount();
		if (CURtick - tick > value){
			tick = CURtick;
			for (std::list<Ani>::iterator iter = loof.begin(); iter != loof.end(); iter++){
				(iter->cur)++;
				if (iter->cur >= iter->img->size())
					iter->cur = 0;
			}
		}
	}

	void Maprender(const HDC& dc){
		for (std::list<Ani>::iterator iter = loof.begin(); iter != loof.end(); iter++){
			TransparentBlt(dc, iter->position.x, iter->position.y, (*(iter->img))[iter->cur]->Bit.bmWidth, (*(iter->img))[iter->cur]->Bit.bmHeight, (*(iter->img))[iter->cur]->mDC, 0, 0, (*(iter->img))[iter->cur]->Bit.bmWidth, (*(iter->img))[iter->cur]->Bit.bmHeight, RGB(255, 0, 255));
		}
	}
	//==========================
	void EffectControl(char* _path){
		char pathBuf[_MAX_PATH] = { 0, };	// 디렉토리 경로용
		strcat_s(pathBuf, _MAX_PATH, _path);
		strcat_s(pathBuf, _MAX_PATH, "/*.*");

		struct _finddata_t c_file;
		intptr_t hFile = _findfirst(pathBuf, &c_file);
		ImageVec* tempimg = new ImageVec();
		//if (hFile == -1) { 
		//	MYDBG_LOG("effect 폴더 디렉토리 읽기 실패");      // no files
		//	return;
		//}

		_findnext(hFile, &c_file); // .
		_findnext(hFile, &c_file); // ..

		

		do  {
			char pathnameBuf[_MAX_PATH] = { 0, };
			strcat_s(pathnameBuf, _MAX_PATH, _path);
			strcat_s(pathnameBuf, _MAX_PATH, "/");
			strcat_s(pathnameBuf, _MAX_PATH, c_file.name);

			EffectMap[c_file.name] = addImageVector(pathnameBuf);
		} while (_findnext(hFile, &c_file) == 0);

		int a = 10;
	}

	ImageVec* addImageVector(char* _path){
	
		ImageVec *tempimg = new ImageVec();

		char pathBuf[_MAX_PATH] = { 0, };	// 디렉토리 경로용
		strcat_s(pathBuf, _MAX_PATH, _path);
		strcat_s(pathBuf, _MAX_PATH, "/*.*");

		struct _finddata_t c_file;
		intptr_t hFile = _findfirst(pathBuf, &c_file);

		//if (hFile == -1) { 
		//	MYDBG_LOG("effect 폴더 디렉토리 읽기 실패");      // no files
		//	return;
		//}


		_findnext(hFile, &c_file); // .
		_findnext(hFile, &c_file); // ..

		do{	
			SImageDB* pimg = new SImageDB();

			// _pathnameOfEffects 디렉토리 내 디렉토리명 검색 
			char pathnameBuf[_MAX_PATH] = { 0, };
			strcat_s(pathnameBuf, _MAX_PATH, _path);
			strcat_s(pathnameBuf, _MAX_PATH, "/");
			strcat_s(pathnameBuf, _MAX_PATH, c_file.name);

			HDC hdc = GetDC(g_hWnd);
			pimg->hBit = (HBITMAP)LoadImage(NULL, pathnameBuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			pimg->mDC = CreateCompatibleDC(GetDC(GetFocus()));
			GetObject(pimg->hBit, sizeof(pimg->Bit), &pimg->Bit);
			SelectObject(pimg->mDC, pimg->hBit);
			
			tempimg->push_back(pimg);
		} while (_findnext(hFile, &c_file) == 0);

		_findclose(hFile);

		return tempimg;
	}

public:
	ImageManager(){}
	~ImageManager(){}
};

