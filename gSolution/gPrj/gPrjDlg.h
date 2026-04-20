
// gPrjDlg.h: 헤더 파일
//
#include "CDlgImage.h"

#pragma once
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


// CgPrjDlg 대화 상자
class CgPrjDlg : public CDialogEx
{
// 생성입니다.
public:
	CgPrjDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	CDlgImage* m_pDlgImage;
	CDlgImage* m_pDlgImgResult;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPRJ_DIALOG }; 
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg); // 이 줄을 추가합니다.


public:
//	afx_msg void OnBnClickedBtnDlg();
	afx_msg void OnDestroy();

	void CallFunc(int n); // 대화 상자에서 호출할 함수 선언
	void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnBnClickedBtnMakePattern();
	afx_msg void OnBnClickedBtnGetData();
	afx_msg void OnEnChangeEditCircleSize();
	afx_msg void OnBnClickedBtnMakeCircle();
	afx_msg void OnBnClickedBtnThread();
	int processImage(CRect rect);
};

