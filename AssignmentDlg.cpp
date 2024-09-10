
// AssignmentDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Assignment.h"
#include "AssignmentDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "ImageProcessing.h"

#define	POS_EDIT_MAX_LEN			9
#define MIN_RADIUS_VAL				1

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


// CAssignmentDlg 대화 상자



CAssignmentDlg::CAssignmentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASSIGNMENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_START_POSITION, startPosEdit);
	DDX_Control(pDX, IDC_END_POSITION, endPosEdit);
	DDX_Control(pDX, IDC_SCREEN, screen);
}

BEGIN_MESSAGE_MAP(CAssignmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_START_POSITION, &CAssignmentDlg::OnEnChangeStartPosition)
	ON_BN_CLICKED(IDC_DRAW_BTN, &CAssignmentDlg::OnBnClickedDrawBtn)
	ON_EN_CHANGE(IDC_END_POSITION, &CAssignmentDlg::OnEnChangeEndPosition)
	ON_BN_CLICKED(IDC_ACTION_BTN, &CAssignmentDlg::OnBnClickedActionBtn)
	ON_BN_CLICKED(IDC_OPEN_BTN, &CAssignmentDlg::OnBnClickedOpenBtn)
END_MESSAGE_MAP()


// CAssignmentDlg 메시지 처리기

BOOL CAssignmentDlg::OnInitDialog()
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
	startPosEdit.LimitText(POS_EDIT_MAX_LEN);
	endPosEdit.LimitText(POS_EDIT_MAX_LEN);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAssignmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAssignmentDlg::OnPaint()
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
HCURSOR CAssignmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//개인 함수

//void CAssignmentDlg::CreateCircle(CImage& circle, int maxRadius) {
//	//random
//	std::random_device rd;
//	std::mt19937_64 gen(rd());
//	std::uniform_int_distribution<> dis(1, maxRadius);
//
//	unsigned int radius = dis(gen);
//
//
//	circle.Create(radius * 2, radius * 2, 8);
//
//	RGBQUAD rgb[256];
//
//	for (int i = 0; i < 256; i++) {
//		rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
//		circle.SetColorTable(0, 256, rgb);
//	}
//
//	unsigned char* fm = (unsigned char*)circle.GetBits();
//
//	POINT currentPoint{},
//		centerPoint{ radius, radius };
//
//	for (int row = 0; row < radius * 2; row++) {
//		for (int col = 0; col < radius * 2; col++) {
//			currentPoint = { row, col };
//
//			radius >= sqrt(pow(abs(currentPoint.x - centerPoint.x), 2) + pow(abs(currentPoint.y - centerPoint.y), 2))
//				? fm[row * circle.GetPitch() + col] = 255 : fm[row * circle.GetPitch() + col] = 0;
//		}
//	}
//}

unsigned int CAssignmentDlg::CreateCircle(CImage& circle, RECT backgroundRect, POINT centerPoint) {
	if (!circle.IsNull()) {
		circle.Destroy();
	}

	unsigned int cols = backgroundRect.right - backgroundRect.left;
	unsigned int rows = backgroundRect.bottom - backgroundRect.top;
	//random
	std::random_device rd;
	std::mt19937_64 gen(rd());

	unsigned int maxRadius = (backgroundRect.right >= backgroundRect.bottom
		? cols : rows) / 2;

	unsigned int minCp = centerPoint.x >= centerPoint.y ? centerPoint.y : centerPoint.x;

	maxRadius = maxRadius >= minCp ? minCp : maxRadius;

	if (maxRadius + centerPoint.x > rows) {
		maxRadius = rows - centerPoint.x;
	}

	if (maxRadius + centerPoint.y > cols) {
		maxRadius = cols - centerPoint.y;
	}

	std::uniform_int_distribution<> dis(MIN_RADIUS_VAL, maxRadius = maxRadius == 0 ? 1 : maxRadius);

	unsigned int radius = dis(gen);


	circle.Create(cols, rows, 8);

	RGBQUAD rgb[256];

	for (int i = 0; i < 256; i++) {
		rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
		circle.SetColorTable(0, 256, rgb);
	}

	unsigned char* fm = (unsigned char*)circle.GetBits();

	POINT currentPoint{};

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			currentPoint = { row, col };

			radius >= sqrt(pow(abs(currentPoint.x - centerPoint.x), 2) + pow(abs(currentPoint.y - centerPoint.y), 2))
				? fm[row * circle.GetPitch() + col] = 255 : fm[row * circle.GetPitch() + col] = 0;
		}
	}

	return radius;
}

bool CAssignmentDlg::MoveCircle(CircleInfo& ci, POINT movCenterPoint) {
	if (ci.circle.IsNull()) return false;

	byte* fm = (byte*)ci.circle.GetBits();

	int pitch = ci.circle.GetPitch();
	unsigned int cols = ci.circle.GetWidth();
	unsigned int rows = ci.circle.GetHeight();

	unsigned int radius = ci.radius;

	movCenterPoint.y = movCenterPoint.y < (rows - radius) ? movCenterPoint.y : rows - radius;
	movCenterPoint.x = movCenterPoint.x < (cols - radius) ? movCenterPoint.x : cols - radius;

	POINT startPos{ ci.centerPoint.x - ci.radius, ci.centerPoint.y - ci.radius };
	POINT endPos{ ci.centerPoint.x + ci.radius, ci.centerPoint.y + ci.radius };

	std::vector<byte> cpyImages{};

	for (int row = startPos.y; row <= endPos.y; row++) {
		for (int col = startPos.x; col <= endPos.x; col++) {
			cpyImages.push_back(fm[row * pitch + col]);
			fm[row * pitch + col] = 0;
		}
	}


	startPos.x = movCenterPoint.x - radius;
	startPos.y = movCenterPoint.y - radius;

	endPos.x = movCenterPoint.x + radius;
	endPos.y = movCenterPoint.y + radius;

	int i = 0;

	for (int row = startPos.y; row <= endPos.y; row++) {
		for (int col = startPos.x; col <= endPos.x; col++) {
			fm[row * pitch + col] = cpyImages.at(i++);
		}
	}

	cpyImages.clear();

	ci.centerPoint = movCenterPoint;

	static int titleNum = 1;

	std::wstring title{ L".\\Images\\Circle_Images" };

	title.append(std::to_wstring(titleNum++) + L".bmp");
	ci.circle.Save(title.c_str());

	return true;
}

bool CAssignmentDlg::UpdateScreen(const CImage& image) {
	if (image.IsNull()) return false;

	auto screenDC = screen.GetDC();
	image.Draw(*screenDC, 0, 0);

	return true;
}

//UI 함수
void CAssignmentDlg::OnEnChangeStartPosition()
{
	CString startPosText{};

	startPosEdit.GetWindowTextW(startPosText);

	unsigned int len = startPosText.GetLength();

	for (int i = 0; i < len; i++) {
		char c = startPosText[i];

		'0' > c || c > '9' ? c != posSign ? startPosEdit.SetWindowTextW(L"") : NULL : NULL;
	}
}

void CAssignmentDlg::OnEnChangeEndPosition()
{
	CString endPosText{};

	endPosEdit.GetWindowTextW(endPosText);

	unsigned int len = endPosText.GetLength();

	for (int i = 0; i < len; i++) {
		char c = endPosText[i];

		'0' > c || c > '9' ? c != posSign ? endPosEdit.SetWindowTextW(L"") : NULL : NULL;
	}
}

void CAssignmentDlg::OnBnClickedDrawBtn()
{
	if (!ci.circle.IsNull()) {
		ci.circle.Destroy();
	}

	CString startPosText{};

	startPosEdit.GetWindowTextW(startPosText);

	int signPos = startPosText.Find(posSign, 0);
	int len = startPosText.GetLength();

	if (signPos != -1 && signPos != len - 1) {
		ci.centerPoint.x = _wtoi(startPosText.Left(signPos));
		ci.centerPoint.y = _wtoi(startPosText.Mid(signPos + 1, len - signPos));
	}

	RECT screenRect{};

	screen.GetWindowRect(&screenRect);

	ci.radius = CreateCircle(ci.circle, screenRect, ci.centerPoint);
	if (ci.circle.IsNull()) {
		std::cerr << "Failed to create circle \n";
		return;
	}

	UpdateScreen(ci.circle);
}

void CAssignmentDlg::OnBnClickedActionBtn()
{
	if (ci.circle.IsNull()) return;

	CString endPosText{};

	endPosEdit.GetWindowTextW(endPosText);

	int signPos = endPosText.Find(posSign, 0);
	int len = endPosText.GetLength();

	POINT movePoint{};

	auto screenDC = screen.GetDC();

	if (signPos != -1 && signPos != len - 1) {
		movePoint.x = _wtoi(endPosText.Left(signPos));
		movePoint.y = _wtoi(endPosText.Mid(signPos + 1, len - signPos));
	}

	//x,y 좌표가 원의 중점에서 둘다 커질 떄, 작아질 때만 동작
	//쓰레드 적용이 없어 포그라운드 잠시 멈춤
	if (movePoint.x < ci.centerPoint.x&& movePoint.y < ci.centerPoint.y) {
		for (int y = ci.centerPoint.y; y > movePoint.y; y--) {
			for (int x = ci.centerPoint.x; x > movePoint.x; x--) {
				MoveCircle(ci, POINT{ x,y });
				UpdateScreen(ci.circle);
				Sleep(10);
			}
		}
	}
	else {
		for (int y = ci.centerPoint.y; y < movePoint.y; y++) {
			for (int x = ci.centerPoint.x; x < movePoint.x; x++) {
				MoveCircle(ci, POINT{ x,y });
				UpdateScreen(ci.circle);
				Sleep(10);
			}
		}
	}
}

void CAssignmentDlg::OnBnClickedOpenBtn()
{
	CFileDialog cfDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("Bitmap Files (*.bmp)|*.bmp||"));

	cfDlg.m_ofn.lpstrInitialDir = L".\\Images";
	
	if (cfDlg.DoModal() == IDOK) {

		if (!ci.circle.IsNull()) ci.circle.Destroy();

		ci.circle.Load(cfDlg.GetPathName().GetString());

		ImageProcessing ip{};
		CImage colorCircle{};

		ip.GetAnalyzedCircle(ci.circle, colorCircle);

		UpdateScreen(colorCircle);

		colorCircle.Destroy();
	}
}
