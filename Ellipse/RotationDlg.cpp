// RotationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Rotation.h"
#include "RotationDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRotationDlg 对话框




CRotationDlg::CRotationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotationDlg::IDD, pParent)
	, step(0)
	, speed(0)
	, ring(1)
	, flag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRotationDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRotationDlg 消息处理程序

BOOL CRotationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	SetTimer(1,20,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRotationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRotationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rt;
		GetClientRect(&rt);
		Image img(_T("card1.png"));
		Image imgbg(_T("ReviewBk.bmp"));

		CDC m_memDC;
		m_memDC.CreateCompatibleDC(&dc);

		CBitmap btScreen;
		btScreen.CreateCompatibleBitmap(&dc,rt.Width(),rt.Height());
		m_memDC.SelectObject(&btScreen);

		Graphics g(m_memDC);
		g.DrawImage(&imgbg,0,0,rt.Width(),rt.Height());

		int x1,x2,x3,y1,y2,y3;
		if(step>256)
		{
			ring++;
			speed = 0;
			step = 256;
			KillTimer(1);
			SetTimer(2,20,NULL);
			flag = !flag;
		}
		else if(step < 0)
		{
			ring ++;
			speed = 0;
			step = 0;
			KillTimer(2);
			SetTimer(1,20,NULL);
			flag = !flag;
		}
		if (flag)
		{
			x1 = step;
			y1 = sqrt((1-((step-EllipseA)*(step-EllipseA)*1.0/(EllipseA*EllipseA)))*EllipseB*EllipseB)+EllipseB;

			x2 = EllipseA*2-step;
			y2 = EllipseB*2-y1;

			x3 = x1;
			y3 = y1+img.GetHeight();
		}
		else
		{
			x1 = step;
			y1 = sqrt((1-((step-EllipseA)*(step-EllipseA)*1.0/(EllipseA*EllipseA)))*EllipseB*EllipseB)*(-1)+EllipseB;

			x2 = EllipseA*2-step;
			y2 = EllipseB*2-y1;

			x3 = x1;
			y3 = y1+img.GetHeight();
		
		
		}
		Point destinationPoints[] = {
			Point(x1, y1),   // destination for upper-left point of original
			Point(x2, y2),  // destination for upper-right point of original
			Point(x3, y3)}; 

		

		g.DrawImage(&img,destinationPoints, 3);

		dc.BitBlt(0,0,rt.Width(),rt.Height(),&m_memDC,0,0,SRCCOPY);
		m_memDC.DeleteDC();
 		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CRotationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRotationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(ring > 60)
		ring = 1;
 	speed+=ring;

	switch(nIDEvent)
	{
	case 1:
		step+=speed;
		break;
	case 2:
		step-=speed;
		break;
	}
	Invalidate(FALSE);
	CDialog::OnTimer(nIDEvent);
}
