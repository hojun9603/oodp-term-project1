
// MyPhone.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMyPhoneApp:
// �� Ŭ������ ������ ���ؼ��� MyPhone.cpp�� �����Ͻʽÿ�.
//

class CMyPhoneApp : public CWinApp
{
public:
	CMyPhoneApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMyPhoneApp theApp; 