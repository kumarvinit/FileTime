
// FileTime.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileTimeApp:
// �йش����ʵ�֣������ FileTime.cpp
//

class CFileTimeApp : public CWinApp
{
public:
	CFileTimeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileTimeApp theApp;