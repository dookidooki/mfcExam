
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
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CgPrjDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgPrjDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
	ON_EN_CHANGE(IDC_EDIT_CIRCLE_SIZE, &CgPrjDlg::OnEnChangeEditCircleSize)
	ON_BN_CLICKED(IDC_BTN_MAKE_CIRCLE, &CgPrjDlg::OnBnClickedBtnMakeCircle)
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

	if(m_pDlgImage)	delete m_pDlgImage;          // 대화 상자 클래스 객체를 메모리에서 해제합니다. (객체 소멸)
	if(m_pDlgImgResult)	delete m_pDlgImgResult;  // 대화 상자 클래스 객체를 메모리에서 해제합니다. (객체 소멸)
}

void CgPrjDlg::CallFunc(int n)
{
	cout << "수신된 데이터: " << n << endl;

	int nData = n;
	// 출력 창(Output)에 결과 표시
	TRACE(_T("데이터 수신 성공: %d\n"), nData);
}


void CgPrjDlg::OnBnClickedBtnTest() {

	// 1. 이미지 데이터의 시작 지점(포인터)을 가져옵니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();

	// 2. 이미지의 가로, 세로 크기와 데이터 한 줄의 길이(Pitch)를 파악합니다.
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	// 3. 검은색(0)으로 배경 초기화
	memset(fm, 0, nWidth * nHeight);

	// 4. 결과창 데이터 개수 리셋 (필수!)
	m_pDlgImgResult->m_nDataCount = 0;

	// 5. 화면에 랜덤한 위치에 랜덤한 밝기로 점 찍기 (100개)
	for (int k = 0; k < MAX_POINTS; k++) {
		int i = rand() % nWidth; // 랜덤한 x 좌표 생성 (0부터 nWidth-1 사이의 값)
		int j = rand() % nHeight; // 랜덤한 y 좌표 생성 (0부터 nHeight-1 사이의 값)
		fm[j * nPitch + i] = (rand() % 0xff) + 1; // 랜덤한 밝기의 점 

		// fm[y * nPitch + x + 1] = 0; // 검은 점. 위치는 y * nPitch + x 에서 오른쪽으로 한 칸 이동한 곳입니다.	
		// fm[y + 1 * nPitch + x] = 0; // 검은 점. 위치는 y * nPitch + x 에서 아래로 한 칸 이동한 곳입니다.
		// fm[y + 1 * nPitch + x + 1] = 0; // 검은 점. 위치는 y * nPitch + x 에서 대각선으로 한 칸 이동한 곳입니다.

	}

	// 6.지정한 점마다 타원 그리기
	int nThreshold = 100; // 밝기가 100보다 큰 점을 찾기 위한 임계값입니다.
	int nIndex = 0;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] > nThreshold) {							// 밝기가 100보다 큰 점을 찾습니다. (검은색이 아닌 점)
				if (m_pDlgImgResult->m_nDataCount < MAX_POINTS) {		   // 결과창에 저장할 데이터 개수 제한 (최대100개)

					// cout << m_pDlgImgResult->m_nDataCount + 1 << "(" << i << "," << j << ")" << endl; // 콘솔 창에 점의 좌표와 데이터 개수를 출력합니다.

					m_pDlgImgResult->m_ptData[nIndex].x = i;   
					m_pDlgImgResult->m_ptData[nIndex].y = j; 
					m_pDlgImgResult->m_nDataCount = ++nIndex;
				}
			}
		}
	}
	// 7. 대화 상자에 그려진 이미지를 갱신하여 변경된 내용을 화면에 반영합니다.
	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate();
}
#include "CProcess.h"
#include <chrono>
void CgPrjDlg::OnBnClickedBtnProcess()
{
	CProcess process; // CProcess 클래스의 객체를 생성합니다.
	
	auto start = std::chrono::system_clock::now(); // 시작 시간 기록
	
	int nRet = process.getStarInfo(m_pDlgImage->m_image); // default nThreshold = 100 이어서 입력값 생략 가능 
	// int nRet = process.getStarInfo(m_pDlgImage->m_image, nThreshold);

	auto end = std::chrono::system_clock::now(); // 종료 시간 기록

	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // 경과 시간 계산 (밀리초 단위)

	cout << nRet << "\t" << milliseconds.count() << "ms" << endl;

}





void CgPrjDlg::OnBnClickedBtnMakePattern()
{
	
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();         // 1. 이미지 데이터의 시작 지점(포인터)을 가져옵니다.	
	int nWidth = m_pDlgImage->m_image.GetWidth();								// 2. 이미지의 가로, 세로 크기와 데이터 한 줄의 길이(Pitch)를 파악합니다.
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);											// 3. 검은색(0)으로 배경 초기화

	CRect rect(100,100,200,200);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j * nPitch + i] = rand()%0xff; // 0x81							// 4. 지정한 영역에 밝기 정하기
		}
	}
	m_pDlgImage->Invalidate();													// 5. 포인터 접근 / 이미지 갱신 / 화면에 반영

}

void CgPrjDlg::OnBnClickedBtnGetData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();         // 1. 이미지 데이터의 시작 지점(포인터)을 가져옵니다.	
	int nWidth = m_pDlgImage->m_image.GetWidth();								// 2. 이미지의 가로, 세로 크기와 데이터 한 줄의 길이(Pitch)를 파악합니다.
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nThreshold = 0x80; // 3. 밝기가 128보다 큰 점을 찾기 위한 임계값입니다.
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nThreshold) {
				nSumX += i; // 밝기가 128보다 큰 점의 x 좌표를 누적
				nSumY += j; // 밝기가 128보다 큰 점의 y 좌표를 누적
				nCount++;   // 밝기가 128보다 큰 점의 개수를 카운트

			};									
		}
	}

	double DcenterX = double(nSumX) / nCount;
	double DcenterY = double(nSumY) / nCount;

	cout << "Center Coordinate: (" << DcenterX << ", " << DcenterY << ")" << endl;
	// make pattern - rand()%0xff - (149.336, 149.781) - rand 값일 때는 부정확   
	// make pattern - 0x81 -(149.5, 149.5) // 0x81로 패턴을 만들 때는 정확하게 (149.5, 149.5)가 나옴.
}



void CgPrjDlg::OnEnChangeEditCircleSize()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CgPrjDlg::OnBnClickedBtnMakeCircle()
{
	// 1. Edit에서 개수가 아닌 '크기(반지름)'를 읽어옵니다.
	int nSize = GetDlgItemInt(IDC_EDIT_CIRCLE_SIZE);
	if (nSize <= 0) nSize = 5; // 기본값 방어
	m_pDlgImage->m_nCircleSize = nSize; // ★ 자식에게 크기 전달
	// 2. 개수는 일단 1개만 그리거나, 상수로 정합니다. (예: 1개)
	int nNum = 1;
	m_pDlgImage->m_nDataCount = 0;
	double dSumX = 0, dSumY = 0;
	for (int i = 0; i < nNum; i++) {
		int nX = rand() % 640;
		int nY = rand() % 480;
		m_pDlgImage->m_ptData[i].x = nX;
		m_pDlgImage->m_ptData[i].y = nY;
		dSumX += nX; dSumY += nY;
		m_pDlgImage->m_nDataCount++;
	}
	// 3. 출력 및 갱신
	cout << "size: " << nSize << " / center: (" << dSumX / nNum << "," << dSumY / nNum << ")" << endl;
	m_pDlgImage->Invalidate();
}
