// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "afxdialogex.h"
#include "CDlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


#include "gPrjDlg.h"
void CDlgImage::OnBnClickedBtnUpParent()
{
	static int nCount = 0; // 버튼 클릭 횟수를 저장하는 정적 변수
	CgPrjDlg* pDlg = (CgPrjDlg*)m_pParent; // 부모 대화 상자 포인터를 CgPrjDlg 형식으로 변환
	pDlg->CallFunc(nCount++);
}

