#include "ImageManager.h"

ImageManager* ImageManager::myInstance = NULL;


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
