#include "ImageManager.h"

ImageManager* ImageManager::myInstance = NULL;

void ImageManager::setHandle(){

}

void ImageManager::Release()
{
	ImageManager::LISTOFVECTOR::iterator parentIter;
	parentIter = (myInstance->listImgVec).begin();

	for (; parentIter != (myInstance->listImgVec).end();){
		for (ImageVec::iterator iter = (*parentIter)->begin(); iter != (*parentIter)->end();)
		{
			delete *iter;
			*iter = NULL;

			iter = (*parentIter)->erase(iter);
		}

		(*parentIter)->clear();

		delete *parentIter;
		*parentIter = NULL;

		myInstance->listImgVec.erase(parentIter++);
	}

	myInstance->listImgVec.clear();

	if (myInstance)
		delete myInstance;
}

ImageVec* ImageManager::imgInit(const char* _str){

	SImageDB tmpImg;

	char pathBuf[_MAX_DIR] = { 0, };

	tmpImg.str = _str;
	tmpImg.Source.left = 0;
	tmpImg.Source.top = 0;

	strcat_s(pathBuf, _MAX_DIR, _str);
	strcat_s(pathBuf, _MAX_DIR,	"/*.*");

	struct _finddata_t c_file;
	intptr_t hFile = _findfirst(pathBuf, &c_file);

	if (hFile == -1){
		return NULL;
	}

	ImageVec	*tmpImgVec = new ImageVec();

	do{
		if (c_file.attrib & _A_SUBDIR)
		{
			continue;
		}
		else{
			SImageDB* pimg = new SImageDB();
			*pimg = tmpImg;

			char filenameBuf[_MAX_DIR] = { 0, };
			strcat_s(filenameBuf, _MAX_DIR, _str);
			strcat_s(filenameBuf, _MAX_DIR, _str);
			strcat_s(filenameBuf, _MAX_DIR, "/");
			strcat_s(filenameBuf, _MAX_DIR, c_file.name);

			HDC hdc = GetDC(g_hWnd);
			pimg->hBit = (HBITMAP)LoadImage(NULL, "./CardResouce/001.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			pimg->mDC = CreateCompatibleDC(GetDC(GetFocus()));
			GetObject(pimg->hBit, sizeof(pimg->Bit), &pimg->Bit);
			SelectObject(pimg->mDC, pimg->hBit);

			pimg->Source.right = pimg->Bit.bmWidth;
			pimg->Source.bottom = pimg->Bit.bmHeight;

			tmpImgVec->push_back(pimg);
		}
	} while (_findnext(hFile, &c_file) == 0);
	
	_findclose(hFile);

	listImgVec.push_back(tmpImgVec);

	return tmpImgVec;
}