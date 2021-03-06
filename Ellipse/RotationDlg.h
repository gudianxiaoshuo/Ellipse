// RotationDlg.h : 头文件
//

#define EllipseA 128
#define EllipseB 25

#pragma once


// CRotationDlg 对话框
class CRotationDlg : public CDialog
{
// 构造
public:
	CRotationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ROTATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	int step;
public:
	int speed;
public:
	int ring;
public:
	bool flag;
};
