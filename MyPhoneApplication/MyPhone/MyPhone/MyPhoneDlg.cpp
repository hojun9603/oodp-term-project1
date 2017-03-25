
// MyPhoneDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MyPhone.h"
#include "MyPhoneDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyPhoneDlg ��ȭ ����

BEGIN_DHTML_EVENT_MAP(CMyPhoneDlg)
	DHTML_EVENT_ONCLICK(_T("BUTTON_ADDRESS_BOOK"), OnButtonGoAddressBook)
	DHTML_EVENT_ONCLICK(_T("BUTTON_MESSAGES"), OnButtonGoAddressBook)
	DHTML_EVENT_ONCLICK(_T("BUTTON_CALLLOG"), OnButtonGoAddressBook)
	DHTML_EVENT_ONCLICK(_T("BUTTON_GO_MAIN"), OnButtonGoMain)
	DHTML_EVENT_ONCLICK(_T("BUTTON_ADD_ADDRESS"), OnButtonAddAddressForm)
	DHTML_EVENT_ONCLICK(_T("ADD_ADDRESS"), OnButtonAddAddress)
	DHTML_EVENT_ONCLICK(_T("BUTTON_MODIFY_ADDRESS"), OnButtonModifyAddress)
END_DHTML_EVENT_MAP()


CMyPhoneDlg::CMyPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_MYPHONE_DIALOG, IDR_HTML_MYPHONE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_DHtml_ElementInnerHtml(pDX, _T("address_book_app"), m_sAddressBookAppCode);
	DDX_DHtml_ElementInnerHtml(pDX, _T("address_list"), m_sAddressListCode);
}

BEGIN_MESSAGE_MAP(CMyPhoneDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CMyPhoneDlg �޽��� ó����

BOOL CMyPhoneDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	UpdateData(FALSE);

	return TRUE;
}

void CMyPhoneDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}


void CMyPhoneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

HCURSOR CMyPhoneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CMyPhoneDlg::OnButtonGoAddressBook(IHTMLElement* /*pElement*/)
{
	UpdateAddressListCode();
	NavigateToResource(IDR_HTML_ADDRESS_BOOK);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonGoMessages(IHTMLElement *pElement)
{
	NavigateToResource(IDR_HTML_MESSAGE);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonGoCallLog(IHTMLElement *pElement)
{
	NavigateToResource(IDR_HTML_CALL_LOG);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonGoMain(IHTMLElement *pElement)
{
	NavigateToResource(IDR_HTML_MYPHONE_DIALOG);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonAddAddressForm(IHTMLElement *pElement)
{
	NavigateToResource(IDR_HTML_ADDRESS_ADD);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonAddAddress(IHTMLElement *pElement)
{
	MyAddress address;
	CString input;
	std::string buffer;

	const static CString ADDRESS_INFO[] = {
		_T("ADDRESS_ADD_NAME"),
		_T("ADDRESS_ADD_HOME"),
		_T("ADDRESS_ADD_OFFICE"),
		_T("ADDRESS_ADD_EMAIL"),
		_T("ADDRESS_ADD_URL"),
	};

	const static CString ERROR_MESSAGE[] = {
		_T("Name is not valid syntax."),
		_T("Home is not valid syntax."),
		_T("Office is not valid syntax."),
		_T("Email is not valid syntax."),
		_T("URL is not valid syntax")
	};

	int(MyAddress::*SetFunctions[])(std::string) = {
		&MyAddress::SetName,
		&MyAddress::SetHomeAddress,
		&MyAddress::SetOfficeAddress,
		&MyAddress::SetEmail,
		&MyAddress::SetURL
	};

	for (int i = 0; i < sizeof(SetFunctions) / sizeof(void*); ++i)
	{
		
		input = GetValueFromHTML(ADDRESS_INFO[i]);
		input = input.Trim();
		if (input.Trim().IsEmpty())
		{
			if(i != 0) continue;
			AfxMessageBox(_T("You should input the name!"));
			return S_FALSE;
		}
		buffer = input.GetBuffer();
		if (((&address)->*(SetFunctions[i]))(input.GetBuffer()))
		{
			AfxMessageBox(ERROR_MESSAGE[i]);
			return S_FALSE;
		}
		input.ReleaseBuffer();
	}

	int addCount = 0;
 	for (int i = 1; i <= 3; ++i)
	{
		CString id;
		id.Format(_T("ADDRESS_ADD_NUMBER%d"), i);
		input = GetValueFromHTML(id);
		input = input.Trim();
		if (input.IsEmpty()) continue;
		buffer = input.GetBuffer();
		
		try
		{
			PhoneNumber number(buffer);
			address.AddPhoneNumber(number);
		}
		catch (NotPhoneNumberException e)
		{
			AfxMessageBox(_T("The phone number is invalid"));
			return S_FALSE;
		}

		input.ReleaseBuffer();
		addCount++;
	}

	if (!addCount)
	{
		AfxMessageBox(_T("You should input more than one phone number."));
		return S_FALSE;
	}

	m_addrBook.AddAddress(address);
	UpdateAddressListCode();
	NavigateToResource(IDR_HTML_ADDRESS_BOOK);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonModifyAddress(IHTMLElement *pElement)
{
	BSTR tmp;
	VARIANT vData;
	pElement->getAttribute(L"accesskey", 2, &vData);
	tmp = vData.bstrVal;
	
	AfxMessageBox((CString)tmp);
	return S_OK;
}

void CMyPhoneDlg::UpdateAddressListCode(void)
{
	m_sAddressListCode = "<table>";

	size_t index = 0;
	MyAddress* addr;

	while (addr = m_addrBook.GetAddress(index++))
	{
		CString name, phoneNumber, accessKey;
		name.Format(_T("%s"), addr->GetName().data());
		phoneNumber.Format(_T("%s"), addr->GetPhoneNumber(0).GetPhoneNumber().data());
		accessKey.Format(_T("%d"), index);
		m_sAddressListCode += "<tr><td><a href=\"#\" id=\"BUTTON_MODIFY_ADDRESS\" accesskey=\"" + accessKey 
			+ "\">" + name + "</a></td><td>" + phoneNumber + "</tr>";
	}

	m_sAddressListCode += "</table>";
}

void CMyPhoneDlg::NavigateToResource(UINT nResource)
{
	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);

	CString strResourceURL;
	LPTSTR lpszModule = new TCHAR[MAX_PATH];

	if (GetModuleFileName(hInstance, lpszModule, MAX_PATH))
	{
		strResourceURL.Format(_T("res://%s/%d"), lpszModule, nResource);
		Navigate(strResourceURL, 0, 0, 0);
	}
}

CString CMyPhoneDlg::GetValueFromHTML(CString id)
{
	IHTMLElement *psrcElement;
	VARIANT vData;

	GetElement(id, &psrcElement);
	psrcElement->getAttribute(L"value", 2, &vData);

	BSTR strTemp = vData.bstrVal;
	CString ret = (CString)strTemp;

	return ret;
}