// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "CProcess.h"
#include "CDlgImage.h"

// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

int CProcess::getStarInfo(CImage& pImage, int nThreshold)
{
	// 1. 이미지 데이터의 시작 지점(포인터)을 가져옵니다.
	unsigned char* fm = (unsigned char*)pImage.GetBits();
	// 2. 이미지의 가로, 세로 크기와 데이터 한 줄의 길이(Pitch)를 파악합니다.
	int nWidth = pImage.GetWidth();
	int nHeight = pImage.GetHeight();
	int nPitch = pImage.GetPitch();

	int nSum = 0;
	for (int k = 0; k < nWidth * nHeight; k++) {
		if(fm[k] > nThreshold)
			//nSum += fm[k]; 밝기 합산
			nSum++; // 밝기가 nThreshold보다 큰 점의 개수 카운트
	}
	return nSum;
}
int CProcess::getStarInfo(CImage& pImage, int nThreshold, CRect rect)
{
	// 1. 이미지 데이터의 시작 지점(포인터)을 가져옵니다.
	unsigned char* fm = (unsigned char*)pImage.GetBits();
	// 2. 이미지의 가로, 세로 크기와 데이터 한 줄의 길이(Pitch)를 파악합니다.
	int nWidth = pImage.GetWidth();
	int nHeight = pImage.GetHeight();
	int nPitch = pImage.GetPitch();

	int nSum = 0;
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) { 
			if (fm[j*nPitch + i] > nThreshold)
				nSum++; // 밝기가 nThreshold보다 큰 점의 개수 카운트
		}
	}
	return nSum;
}


// CProcess 멤버 함수
