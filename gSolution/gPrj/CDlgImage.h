#pragma once

#include "afxdialogex.h"

#define MAX_POINTS 100 // 최대 데이터 포인트 수를 정의합니다.

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CImage m_image;				// CImage 객체를 멤버 변수로 선언
	CWnd* m_pParent;			//	부모 대화 상자 포인터를 멤버 변수로 선언
	int m_nDataCount=0;			// 데이터 개수를 저장하는 멤버 변수 선언
	CPoint m_ptData[MAX_POINTS];		// 데이터 좌표를 저장하는 배열 멤버 변수 선언 (최대 MAX_POINTS개까지 저장 가능)

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	void InitImage();
	void drawData(CDC* pDC);
};
