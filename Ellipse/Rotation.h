// Rotation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRotationApp:
// �йش����ʵ�֣������ Rotation.cpp
//

class CRotationApp : public CWinApp
{
public:
	CRotationApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	ULONG_PTR m_pTr;
public:
	virtual int ExitInstance();
};

extern CRotationApp theApp;