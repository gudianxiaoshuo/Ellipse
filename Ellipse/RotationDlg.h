// RotationDlg.h : ͷ�ļ�
//

#define EllipseA 128
#define EllipseB 25

#pragma once


// CRotationDlg �Ի���
class CRotationDlg : public CDialog
{
// ����
public:
	CRotationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ROTATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
