
// gPrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"

#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgPrjDlg 대화 상자



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CgPrjDlg::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CgPrjDlg 메시지 처리기

BOOL CgPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	MoveWindow(0, 0, 1280, 800); // 대화 상자의 위치와 크기를 설정합니다. (x, y, width, height)

	// 켜짐과	동시에
	m_pDlgImage = new CDlgImage();			// 1. (객체 생성)
	m_pDlgImage->Create(IDD_CDlgImage, this);   	// 2. (관계 설정)
	m_pDlgImage->ShowWindow(SW_SHOW);		// 3.  (시각적 노출)
	m_pDlgImage->MoveWindow(0, 0, 640, 480); // 대화 상자의 위치와 크기를 설정합니다. (x, y, width, height)

	m_pDlgImgResult = new CDlgImage();			// 1. (객체 생성)
	m_pDlgImgResult->Create(IDD_CDlgImage, this);   	// 2. (관계 설정)
	m_pDlgImgResult->ShowWindow(SW_SHOW);		// 3.  (시각적 노출)
	m_pDlgImgResult->MoveWindow(640, 0, 640, 480); // 대화 상자의 위치와 크기를 설정합니다. (x, y, width, height)



	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_pDlgImage;  // 대화 상자 클래스 객체를 메모리에서 해제합니다. (객체 소멸)
}

void CgPrjDlg::CallFunc(int n)
{
	cout << "수신된 데이터: " << n << endl;

	int nData = n;
	// 출력 창(Output)에 결과 표시
	TRACE(_T("데이터 수신 성공: %d\n"), nData);
}


void CgPrjDlg::OnBnClickedBtnTest()
{
	// 1. 이미지 데이터의 시작 지점(포인터)을 가져옵니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();

	// 2. 이미지의 가로, 세로 크기와 데이터 한 줄의 길이(Pitch)를 파악합니다.
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch(); 

	// 3. 화면에 랜덤하게 100개의 검은 점을 찍습니다.
	for (int k = 0; k < 100; k++) {
		int x = rand() % nWidth; 
		int y = rand() % nHeight; 
		// y * nPitch + x 공식으로 정확한 픽셀 위치를 찾아 0(검은색)을 대입합니다.
		fm[y * nPitch + x] = 0;
	}
	
	// 4. 이미지 전체를 훑으며 검은 점의 개수와 좌표를 찾아냅니다.
	int nSum = 0;
	for (int y = 0; y < nHeight; y++) {
		for (int x = 0; x < nWidth; x++) {
			if (fm[y * nPitch + x] == 0) { 
				cout << nSum << " : (" << x << "," << y << ")" << endl; // 해당 좌표를 콘솔에 출력
				nSum++; // 검은 점 발견 시 카운트 증가

			}
		}
	}
		
	// 5. 최종적으로 발견된 검은 점의 총 개수를 출력합니다.
	cout << "full dot count: " << nSum << endl; 

	// 6. 데이터는 바뀌었지만 화면은 아직 옛날 상태이므로, 화면을 다시 그리라고 명령합니다.
	m_pDlgImage->Invalidate();
}
