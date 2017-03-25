
// MyPhoneDlg.h : 헤더 파일
//

#pragma once

#include "PhoneLibs\MyPhoneLibrary.h"


// CMyPhoneDlg 대화 상자
class CMyPhoneDlg : public CDHtmlDialog
{
/* Member Variables */
protected :
	CString			m_sAddressBookAppCode;
	CString			m_sAddressListCode;
	MyAddressBook	m_addrBook;

// 생성입니다.
public:
	CMyPhoneDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPHONE_DIALOG, IDH = IDR_HTML_MYPHONE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	HRESULT OnButtonGoAddressBook(IHTMLElement *pElement);
	HRESULT OnButtonGoMessages(IHTMLElement *pElement);
	HRESULT OnButtonGoCallLog(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT OnButtonGoMain(IHTMLElement *pElement);
	HRESULT OnButtonAddAddressForm(IHTMLElement *pElement);
	HRESULT OnButtonAddAddress(IHTMLElement *pElement);
	HRESULT OnButtonModifyAddress(IHTMLElement *pElement);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
