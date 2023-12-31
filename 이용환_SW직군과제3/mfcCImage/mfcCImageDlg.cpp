﻿
// mfcCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfcCImage.h"
#include "mfcCImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CmfcCImageDlg 대화 상자



CmfcCImageDlg::CmfcCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CmfcCImageDlg::OnBnClickedBtnImage)	
	ON_BN_CLICKED(IDC_BTN_DRAW, &CmfcCImageDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CmfcCImageDlg::OnBnClickedBtnDraw)
END_MESSAGE_MAP()


// CmfcCImageDlg 메시지 처리기

BOOL CmfcCImageDlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmfcCImageDlg::OnPaint()
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
HCURSOR CmfcCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcCImageDlg::OnBnClickedBtnImage()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_image != NULL) {
		m_image.Destroy();
	}
	
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}


	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth*nHeight);


	UpdateDisplay();	


}



void CmfcCImageDlg::UpdateDisplay() 
{
	CClientDC dc(this);

	if(m_image)
		m_image.Draw(dc, 0, 0);

}

void CmfcCImageDlg::DrawCircle(unsigned char* pBits, int width, int height, int pitch, int centerX, int centerY, int radius)
{
	CClientDC dc(this);

	CPen penYellow(PS_SOLID, 1, RGB(255, 255, 0)); // 노란색 펜 생성 (굵기: 2)
	CPen* pOldPen = dc.SelectObject(&penYellow); // 노란색 펜 설정

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int xOffset = x - centerX;
			int yOffset = y - centerY;
			int distanceSquared = xOffset * xOffset + yOffset * yOffset;

			// 배경 (흰색) 설정
			pBits[y * pitch + x] = 0xff;

			// 원의 외곽선 (노란색) 그리기
			if (distanceSquared >= (radius - 5) * (radius - 5) && distanceSquared <= (radius + 5) * (radius + 5)) {
				pBits[y * pitch + x] = 0xffff00; // 노란색 픽셀로 설정
				dc.SetPixel(x, y, RGB(255, 255, 0)); // 노란색 픽셀로 그리기
			}
			int crossSize = 5; // + 기호의 크기
			int crossHalf = crossSize / 2;
			if ((x >= centerX - crossHalf && x <= centerX + crossHalf && y == centerY) ||
				(y >= centerY - crossHalf && y <= centerY + crossHalf && x == centerX)) {
				pBits[y * pitch + x] = 0; // 검은색 픽셀로 설정
				dc.SetPixel(x, y, RGB(0, 0, 0)); // 검은색 픽셀로 그리기
			}
		}
	}


	

	dc.SelectObject(pOldPen); // 이전 펜 설정으로 복구



}



void CmfcCImageDlg::OnBnClickedBtnDraw()
{
	
	if (m_image != NULL) {
		m_image.Destroy();
	}

	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// Edit 컨트롤에서 값을 읽어옴
	CString strRadius;
	GetDlgItemText(IDC_EDIT_SIZE, strRadius);
	int radius = _ttoi(strRadius);


	// 원의 중심 랜덤 좌표 생성
	int centerX = rand() % nWidth;
	int centerY = rand() % nHeight;


	memset(fm, 0xff, nWidth * nHeight);

	UpdateDisplay();	
	

	// 원 그리기
	DrawCircle(fm, nWidth, nHeight, nPitch, centerX, centerY, radius);



}
