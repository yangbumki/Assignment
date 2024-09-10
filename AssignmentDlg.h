
// AssignmentDlg.h: 헤더 파일
#pragma once

typedef struct CRICLE_INFO {
	CImage circle{};
	unsigned int radius;
	POINT centerPoint{};
}CircleInfo;

// CAssignmentDlg 대화 상자
class CAssignmentDlg : public CDialogEx
{
// 생성입니다.
public:
	CAssignmentDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASSIGNMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
private:
	CEdit startPosEdit;
	CEdit endPosEdit;
	const char posSign = '/';

	CStatic screen{};
	
	CircleInfo ci{};

	//원만 만들어내는 함수
	/*void CreateCircle(CImage& circle, int maxRadius = 100);*/

	//원과 배경을 만들어내는 함수
	unsigned int CreateCircle(CImage& circle, RECT backgroundRect, POINT centerPoint);
	bool MoveCircle(CircleInfo& ci,POINT movCenterPoint);
	bool UpdateScreen(const CImage& image);

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeStartPosition();
	afx_msg void OnBnClickedDrawBtn();
	afx_msg void OnEnChangeEndPosition();
	afx_msg void OnBnClickedActionBtn();
	afx_msg void OnBnClickedOpenBtn();
};
