
///////////////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////////////

#include "PhoneLibs\MyPhoneLibrary.h"

///////////////////////////////////////////////////////////////////////////////////////


#define DATA_DIRECTORY			".\data"
#define ADDRESS_DATA_FILE		".\\data\\addresses.txt"
#define MESSAGE_DATA_FILE		".\\data\\messages.txt"
#define CALL_DATA_FILE			".\\data\\calls.txt"

///////////////////////////////////////////////////////////////////////////////////////

class CMyPhoneDlg : public CDHtmlDialog
{
/* Member Variables */
protected :
	UINT			m_previousHTMLResource;
	CString			m_sAddressBookModfyCode;
	CString			m_sAddressListCode;
	CString			m_sWhereToCallCode;
	CString			m_sCallLogCode;
	CString			m_sPersonalMessageBoxCode;
	CString			m_sMessageListCode;
	MyAddressBook	m_addrBook;

	HICON			m_hIcon;

/* Constructor */
public:
	CMyPhoneDlg(CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPHONE_DIALOG, IDH = IDR_HTML_MYPHONE_DIALOG };
#endif

/* Methods */
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	// Event Handlers
	HRESULT		OnButtonGoAddressBook(IHTMLElement *pElement);
	HRESULT		OnButtonGoMessages(IHTMLElement *pElement);
	HRESULT		OnButtonGoCallLog(IHTMLElement *pElement);
	HRESULT		OnButtonGoBack(IHTMLElement *pElement);
	HRESULT		OnButtonGoMain(IHTMLElement *pElement);
	HRESULT		OnButtonAddAddressForm(IHTMLElement *pElement);
	HRESULT		OnButtonAddAddress(IHTMLElement *pElement);
	HRESULT		OnButtonModifyAddress(IHTMLElement *pElement);
	HRESULT		OnButtonDeleteAddress(IHTMLElement* pElement);
	HRESULT		OnButtonModifyAddressForm(IHTMLElement *pElement);
	HRESULT		OnButtonSearch(IHTMLElement* pElement);
	HRESULT		OnButtonCall(IHTMLElement* pElement);
	HRESULT		OnButtonCallNumber(IHTMLElement* pElement);
	HRESULT		OnButtonPersonalMessage(IHTMLElement* pElement);
	HRESULT		OnButtonSendMessage(IHTMLElement* pElement);
	HRESULT		OnButtonMessageView(IHTMLElement* pElement);


	// Message Procedure functions
public :
	virtual BOOL				OnInitDialog();
	virtual BOOL				PreTranslateMessage(MSG* pMsg);
	afx_msg void				OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void				OnPaint();
	afx_msg HCURSOR				OnQueryDragIcon();
	afx_msg void				OnClose();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

	// Methods for using internally
protected :
	HRESULT		CheckSetAddressFromForm(MyAddress& address);
	void		UpdateAddressListCode(void);
	void		UpdateAddressListCode(CString search);

	void		UpdateCallLogListCode(void);
	void		UpdatePersonalMessageListCode(int key);
	void		UpdateMessageListCode(void);

	void		NavigateToResource(UINT nResoeurce);
	CString		GetValueFromHTML(CString id);
	int			GetAccessKeyFromHTML(CString id);
	int			GetAccessKeyFromHTML(IHTMLElement *pElement);
	
};

///////////////////////////////////////////////////////////////////////////////////////