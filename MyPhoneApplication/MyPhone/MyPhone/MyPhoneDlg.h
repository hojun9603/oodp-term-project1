
// MyPhoneDlg.h : ��� ����
//

#pragma once

#include "PhoneLibs\MyPhoneLibrary.h"


// CMyPhoneDlg ��ȭ ����
class CMyPhoneDlg : public CDHtmlDialog
{
/* Member Variables */
protected :
	CString			m_sAddressBookAppCode;
	CString			m_sAddressListCode;
	MyAddressBook	m_addrBook;

// �����Դϴ�.
public:
	CMyPhoneDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPHONE_DIALOG, IDH = IDR_HTML_MYPHONE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	HRESULT OnButtonGoAddressBook(IHTMLElement *pElement);
	HRESULT OnButtonGoMessages(IHTMLElement *pElement);
	HRESULT OnButtonGoCallLog(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT OnButtonGoMain(IHTMLElement *pElement);
	HRESULT OnButtonAddAddressForm(IHTMLElement *pElement);
	HRESULT OnButtonAddAddress(IHTMLElement *pElement);
	HRESULT OnButtonModifyAddress(IHTMLElement *pElement);

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

/* Methods */
public :
	void		UpdateAddressListCode(void);
	void		NavigateToResource(UINT nResoeurce);
	CString		GetValueFromHTML(CString id);
};
