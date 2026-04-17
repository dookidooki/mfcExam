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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


#include "gPrjDlg.h"
void CDlgImage::OnBnClickedBtnUpParent()
{
	static int nCount = 100; // 버튼 클릭 횟수를 저장하는 정적 변수
	CgPrjDlg* pDlg = (CgPrjDlg*)m_pParent; // 부모 대화 상자 포인터를 CgPrjDlg 형식으로 변환
	pDlg->CallFunc(nCount++);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// AfxMessageBox(_T("CDlgImage 대화 상자가 초기화되었습니다."), MB_OK | MB_ICONINFORMATION);

	MoveWindow(0, 0, 640, 480); // 대화 상자의 위치와 크기를 설정합니다. (x, y, width, height)

	InitImage();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}





	void CDlgImage::OnPaint()
	{
		CPaintDC dc(this); // device context for painting
		// TODO: 여기 에 메시지 처리기 코드를 추가합니다.
		// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
		if (!m_image.IsNull()) {
			m_image.Draw(dc, 0, 0); // 이미지 객체의 Draw 함수를 사용하여 대화 상자에 이미지를 그립니다.
		}
	}

	void CDlgImage::InitImage()
	{
		if (!m_image.IsNull()) { // 이미지 객체가 이미 생성되어 있는지 확인
			m_image.Destroy();
		}

		int nWidth = 640;
		int nHeight = 480;
		int nBpp = 8;

		m_image.Create(nWidth, -nHeight, nBpp); // 설정한 규격대로 메모리에 이미지 공간을 생성합니다.
		if (nBpp == 8) {
			static RGBQUAD rgb[256];

			for (int i = 0; i < 256; i++) //배열 rgb (=팔레트) 채우기
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

			m_image.SetColorTable(0, 256, rgb); //생성한 팔레트를 이미지 객체에 적용 (0번부터 256개)
		}
		unsigned char* fm = (unsigned char*)m_image.GetBits();
		// 포인터 fm - 이미지 객체의 픽셀 데이터에 접근 -  이미지의 픽셀 데이터를 직접 조작 가능

		memset(fm, 0xff, nWidth * nHeight);
		// 이미지의 모든 픽셀을 흰색으로 초기화 (0xff는 255로, 팔레트에서 255번 색상은 흰색입니다.)
	}
