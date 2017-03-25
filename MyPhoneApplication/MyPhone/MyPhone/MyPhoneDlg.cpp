
// MyPhoneDlg.cpp : 구현 파일
//


#include "stdafx.h"

#include <list>

#include "PhoneLibs\Call.h"
#include "MyPhone.h"
#include "MyPhoneDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMyPhoneDlg 대화 상자

BEGIN_DHTML_EVENT_MAP(CMyPhoneDlg)
	DHTML_EVENT_ONCLICK(_T("BUTTON_ADDRESS_BOOK"), OnButtonGoAddressBook)
	DHTML_EVENT_ONCLICK(_T("BUTTON_MESSAGES"), OnButtonGoMessages)
	DHTML_EVENT_ONCLICK(_T("BUTTON_CALLLOG"), OnButtonGoCallLog)
	DHTML_EVENT_ONCLICK(_T("BUTTON_GO_MAIN"), OnButtonGoMain)
	DHTML_EVENT_ONCLICK(_T("BUTTON_GO_BACK"), OnButtonGoBack)
	DHTML_EVENT_ONCLICK(_T("BUTTON_ADD_ADDRESS"), OnButtonAddAddressForm)
	DHTML_EVENT_ONCLICK(_T("ADD_ADDRESS"), OnButtonAddAddress)
	DHTML_EVENT_ONCLICK(_T("MODIFY_ADDRESS"), OnButtonModifyAddress)
	DHTML_EVENT_ONCLICK(_T("BUTTON_MODIFY_ADDRESS"), OnButtonModifyAddressForm)
	DHTML_EVENT_ONCLICK(_T("DELETE_ADDRESS"), OnButtonDeleteAddress)
	DHTML_EVENT_ONCLICK(_T("BUTTON_SEARCH"), OnButtonSearch)
	DHTML_EVENT_ONCLICK(_T("BUTTON_CALL"), OnButtonCall)
	DHTML_EVENT_ONCLICK(_T("CALL_NUMBER"), OnButtonCallNumber)
	DHTML_EVENT_ONCLICK(_T("BUTTON_PERSONAL_MESSAGE"), OnButtonPersonalMessage)
	DHTML_EVENT_ONCLICK(_T("SEND_MESSAGE"), OnButtonSendMessage)
	DHTML_EVENT_ONCLICK(_T("MESSAGE_VIEW"), OnButtonMessageView)
END_DHTML_EVENT_MAP()


CMyPhoneDlg::CMyPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_MYPHONE_DIALOG, IDR_HTML_MYPHONE_DIALOG, pParent),
	m_addrBook()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_DHtml_ElementInnerHtml(pDX, _T("address_list"), m_sAddressListCode);
	DDX_DHtml_ElementInnerHtml(pDX, _T("address_modify_info_table"), m_sAddressBookModfyCode);
	DDX_DHtml_ElementInnerHtml(pDX, _T("address_where_to_call_table"), m_sWhereToCallCode);
	DDX_DHtml_ElementInnerHtml(pDX, _T("call_log_table"), m_sCallLogCode);
	DDX_DHtml_ElementInnerHtml(pDX, _T("message_log_table"), m_sPersonalMessageBoxCode);
	DDX_DHtml_ElementInnerHtml(pDX, _T("message_table"), m_sMessageListCode);
}

BEGIN_MESSAGE_MAP(CMyPhoneDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyPhoneDlg 메시지 처리기

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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	UpdateData(FALSE);

	int failedToLoadCnt = 0;
	CString errorMsg;

	try
	{
		failedToLoadCnt = m_addrBook.LoadAddressFile(ADDRESS_DATA_FILE);
		if (failedToLoadCnt > 0)
		{
			errorMsg.Format(_T("Failed to load %d number(s) due to wrong syntax or duplicated phone numbers..\nThey are ignored!"),
				failedToLoadCnt);
			AfxMessageBox(errorMsg);
		}
	}
	catch (AddressLoadFailException e)
	{
		int ret = AfxMessageBox(_T("Error while loading address data file.. Renew the data file or exit program?"), MB_OKCANCEL);
		if (ret != IDOK) return FALSE;
	}
	
	failedToLoadCnt = m_addrBook.LoadCallsFile(CALL_DATA_FILE);
	failedToLoadCnt = m_addrBook.LoadMessageFile(MESSAGE_DATA_FILE);

	MoveWindow(0, 0, 393, 714);

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
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
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

///////////////////////////////////////////////////////////////////////////////////////
//
//  Event Handlings
//
///////////////////////////////////////////////////////////////////////////////////////

HRESULT CMyPhoneDlg::OnButtonGoAddressBook(IHTMLElement* /*pElement*/)
{
	// update address list from address book and go to the list
	UpdateAddressListCode();
	m_previousHTMLResource = IDR_HTML_ADDRESS_BOOK;
	NavigateToResource(IDR_HTML_ADDRESS_BOOK);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonGoMessages(IHTMLElement *pElement)
{
	UpdateMessageListCode();
	NavigateToResource(IDR_HTML_MESSAGE);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonGoCallLog(IHTMLElement *pElement)
{
	UpdateCallLogListCode();
	m_previousHTMLResource = IDR_HTML_CALL_LOG;
	NavigateToResource(IDR_HTML_CALL_LOG);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonGoBack(IHTMLElement *pElement)
{
	NavigateToResource(m_previousHTMLResource);
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

	// check address form and if not valid return failed
	if(CheckSetAddressFromForm(address) == S_FALSE) return S_FALSE;

	// if valid form syntax, add the address
	m_addrBook.AddAddress(address);
	UpdateAddressListCode();
	NavigateToResource(IDR_HTML_ADDRESS_BOOK);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonModifyAddress(IHTMLElement *pElement)
{
	// get access key for getting the index of address
	int key = GetAccessKeyFromHTML(_T("ModifyTable"));

	MyAddress address, copy = *(m_addrBook.GetAddress(key));

	// check the modified data
	m_addrBook.DeleteAddress(key);
	if (CheckSetAddressFromForm(address) == S_FALSE)
	{
		m_addrBook.AddAddress(copy);
		NavigateToResource(IDR_HTML_ADDRESS_BOOK);
		return S_OK;
	}

	// remove the data and recreate the data
	m_addrBook.AddAddress(address);
	UpdateAddressListCode();
	NavigateToResource(IDR_HTML_ADDRESS_BOOK);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonDeleteAddress(IHTMLElement* pElement)
{
	// get access key for getting the index of address
	int key = GetAccessKeyFromHTML(_T("ModifyTable"));
	m_addrBook.DeleteAddress(key);
	UpdateAddressListCode();
	NavigateToResource(IDR_HTML_ADDRESS_BOOK);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonModifyAddressForm(IHTMLElement *pElement)
{
	
	int key = GetAccessKeyFromHTML(pElement);
	MyAddress* pAddress;

	const static CString MODIFY_ID[] = {
		_T("ADDRESS_ADD_NAME"), _T("ADDRESS_ADD_NUMBER1"), _T("ADDRESS_ADD_NUMBER2"), _T("ADDRESS_ADD_NUMBER3"),
		_T("ADDRESS_ADD_HOME"), _T("ADDRESS_ADD_OFFICE"), _T("ADDRESS_ADD_EMAIL"), _T("ADDRESS_ADD_URL")
	};

	const static CString MODIFY_NAME[] = {
		_T("Name"), _T("Number 1"), _T("Number 2"), _T("Number 3"),
		_T("Home"), _T("Office"), _T("E-mail"), _T("URL")
	};

	
	pAddress = m_addrBook.GetAddress(key - 1);

	if (pAddress == nullptr) return S_FALSE;
	
	CString sData[8];

	// load the data
	sData[0] = pAddress->GetName().data();
	sData[1] = pAddress->GetPhoneNumber(0).GetPhoneNumber().data();
	sData[2] = pAddress->GetPhoneNumber(1).GetPhoneNumber().data();
	sData[3] = pAddress->GetPhoneNumber(2).GetPhoneNumber().data();
	sData[4] = pAddress->GetHomeAddress().data();
	sData[5] = pAddress->GetOfficeAddress().data();
	sData[6] = pAddress->GetEmail().data();
	sData[7] = pAddress->GetURL().data();

	// construct the code
	m_sAddressBookModfyCode.Format(_T("<table id=\"ModifyTable\" accesskey=\"%d\">"), key - 1);

	for (int i = 0; i < 8; ++i)
	{
		m_sAddressBookModfyCode += "<tr><td>" + MODIFY_NAME[i] + "</td><td><input type=\"text\" id=\"" + MODIFY_ID[i] +
			"\" value=\"" + sData[i] + "\"</td></tr>";
	}

	m_sAddressBookModfyCode += "</table>";

	// go to the modification form
	NavigateToResource(IDR_HTML_ADDRESS_MODIFY);

	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonSearch(IHTMLElement* pElement)
{
	CString searchName = GetValueFromHTML(_T("search"));
	UpdateAddressListCode(searchName);
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonCall(IHTMLElement* pElement)
{
	MyAddress* pAddress;
	int key = GetAccessKeyFromHTML(_T("ModifyTable"));
	size_t i;
	CString maker;
	pAddress = m_addrBook.GetAddress(key);

	maker.Format(_T("%d"), key);
	m_sWhereToCallCode = _T("<table id=\"CallTable\" accesskey=\"" + maker + "\">");

	for (i = 0; i < pAddress->GetPhoneNumbersSize(); ++i)
	{
		maker.Format(_T("%d"), i);
		m_sWhereToCallCode += _T("<td><a href=\"#\" id=\"CALL_NUMBER\" accesskey=\"") + maker +
			_T("\">") + pAddress->GetPhoneNumber(i).GetPhoneNumber().data() +
			_T("</td></tr>");
	}

	m_sWhereToCallCode += _T("</table>");
	NavigateToResource(IDR_HTML_WHERE_TO_CALL);
	
	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonCallNumber(IHTMLElement* pElement)
{
	MyAddress* pAddress;
	int key = GetAccessKeyFromHTML(_T("CallTable"));
	int callIndex = GetAccessKeyFromHTML(pElement);
	CString sPhoneNumber;
	PhoneNumber number;
	pAddress = m_addrBook.GetAddress(key);
	number = pAddress->GetPhoneNumber(callIndex);

	sPhoneNumber.Format(_T("%s"), number.GetPhoneNumber().data());
	AfxMessageBox(_T("You call ") + sPhoneNumber + _T(".\n Log is created in call log."));
	
	Call callLog;
	callLog.SetCurrentTime();
	callLog.SetReceiver(number);
	m_addrBook.AddCall(callLog);
	NavigateToResource(IDR_HTML_ADDRESS_BOOK);
	m_previousHTMLResource = IDR_HTML_ADDRESS_BOOK;

	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonPersonalMessage(IHTMLElement* pElement)
{
	int key = GetAccessKeyFromHTML(_T("ModifyTable"));
	UpdatePersonalMessageListCode(key);
	NavigateToResource(IDR_HTML_PERSONAL_MESSAGE);

	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonSendMessage(IHTMLElement* pElement)
{
	CString value = GetValueFromHTML(_T("SEND_MESSAGE_TEXT"));
	int key = GetAccessKeyFromHTML(_T("ModifyTable"));
	PhoneNumber number = m_addrBook.GetAddress(key)->GetPhoneNumber(0);
	SMSMessage message;
	
	message.SetReceiver(number);
	message.SetMessage(value.GetBuffer());
	message.SetCurrentTime();
	value.ReleaseBuffer();
	m_addrBook.AddMessage(message);

	UpdatePersonalMessageListCode(key);
	UpdateData(FALSE);
	NavigateToResource(IDR_HTML_PERSONAL_MESSAGE);

	return S_OK;
}

HRESULT CMyPhoneDlg::OnButtonMessageView(IHTMLElement* pElement)
{
	int key = GetAccessKeyFromHTML(pElement);
	m_previousHTMLResource = IDR_HTML_MESSAGE;
	UpdatePersonalMessageListCode(key);
	NavigateToResource(IDR_HTML_PERSONAL_MESSAGE);
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////

HRESULT CMyPhoneDlg::CheckSetAddressFromForm(MyAddress& address)
{
	CString input;
	std::string buffer;

	// static variables for processing by loop
	const static CString ADDRESS_INFO[] = {
		_T("ADDRESS_ADD_NAME"), _T("ADDRESS_ADD_HOME"), _T("ADDRESS_ADD_OFFICE"), _T("ADDRESS_ADD_EMAIL"), _T("ADDRESS_ADD_URL"),
	};

	const static CString ERROR_MESSAGE[] = {
		_T("Name is not valid syntax."), _T("Home is not valid syntax."), _T("Office is not valid syntax."),
		_T("Email is not valid syntax."), _T("URL is not valid syntax")
	};

	int(MyAddress::*SetFunctions[])(std::string) = {
		&MyAddress::SetName, &MyAddress::SetHomeAddress, &MyAddress::SetOfficeAddress, &MyAddress::SetEmail, &MyAddress::SetURL
	};

	// check and set data respectively
	for (int i = 0; i < sizeof(SetFunctions) / sizeof(void*); ++i)
	{
		input = GetValueFromHTML(ADDRESS_INFO[i]);
		input = input.Trim();

		if (!i && input.Find(_T('\'')) >= 0 || input.Find(_T('\"')) >= 0)
		{
			AfxMessageBox(_T("Name is not valid syntax."));
			return S_FALSE;
		}

		if (input.Trim().IsEmpty())
		{
			if (i != 0) continue;

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

	// set the number
	int addCount = 0;
	for (int i = 1; i <= 3; ++i)
	{
		CString id;
		id.Format(_T("ADDRESS_ADD_NUMBER%d"), i);
		input = GetValueFromHTML(id); input = input.Trim();
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

		if (!m_addrBook.CheckValidAddress(address))
		{
			AfxMessageBox(_T("The number already exists in your book."));
			return S_FALSE;
		}

		input.ReleaseBuffer();
		addCount++;
	}

	if (!addCount)	// if there is no phone number written
	{
		AfxMessageBox(_T("You should input more than one phone number."));
		return S_FALSE;
	}

	return S_OK;
}

void CMyPhoneDlg::UpdateAddressListCode(void)
{
	MyAddress* addr;
	size_t index = 0;

	m_sAddressListCode = "<table>";

	// load the addresses from phone address book
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

void CMyPhoneDlg::UpdateAddressListCode(CString search)
{
	if (search.Trim() == "")
	{
		UpdateAddressListCode();
		return;
	}

	MyAddress* addr;
	LPSTR searchingName = search.GetBuffer();
	size_t index = m_addrBook.SearchAddress(searchingName);
	
	m_sAddressListCode = "<table>";

	// load the addresses from phone address book
	while (addr = m_addrBook.GetAddress(index++))
	{
		if (addr->GetName() != searchingName) break;

		CString name, phoneNumber, accessKey;
		name.Format(_T("%s"), addr->GetName().data());
		phoneNumber.Format(_T("%s"), addr->GetPhoneNumber(0).GetPhoneNumber().data());
		accessKey.Format(_T("%d"), index);
		m_sAddressListCode += "<tr><td><a href=\"#\" id=\"BUTTON_MODIFY_ADDRESS\" accesskey=\"" + accessKey
			+ "\">" + name + "</a></td><td>" + phoneNumber + "</tr>";
	}

	m_sAddressListCode += "</table>";

	search.ReleaseBuffer();
}

void CMyPhoneDlg::UpdateCallLogListCode(void)
{
	Call* pLog;
	size_t index = 0;
	int addrIndex;
	PhoneNumber sender, receiver, number;
	CString maker, date, tmp;
	m_sCallLogCode = _T("<table>");

	while (pLog = m_addrBook.GetCall(index++))
	{
		maker = _T("<tr><td>");
		
		sender = pLog->GetSender();
		receiver = pLog->GetReceiver();
		
		if (sender.IsEmpty() && !receiver.IsEmpty()) {
			maker += _T("To");
			number = receiver;
		}
		else if (!sender.IsEmpty() && receiver.IsEmpty())
		{
			maker += _T("From");
			number = sender;
		}
		else continue;
		
		addrIndex = m_addrBook.SearchAddress(number);

		tmp.Format(_T("%d"), addrIndex + 1);

		if (addrIndex >= 0)
			maker += CString(_T("</td><td><a href=\"#\" id=\"BUTTON_MODIFY_ADDRESS\" accesskey=\""))
			+ tmp + _T("\">");
		else
			maker += CString(_T("</td><td>"));

		if (addrIndex < 0) maker += number.GetPhoneNumber().data();
		else maker += CString(m_addrBook.GetAddress((size_t)addrIndex)->GetName().data()) + _T("</a>");

		maker += _T("</td><td>");
		date.Format(_T("%04d.%02d.%02d %02d:%02d:%02d"), pLog->GetYear(), pLog->GetMonth(), pLog->GetDay(),
			pLog->GetHour(), pLog->GetMinute(), pLog->GetSecond());

		maker += date + _T("</td></tr>");
		m_sCallLogCode += maker;
	}

	m_sCallLogCode += _T("</table>");
}

void CMyPhoneDlg::UpdatePersonalMessageListCode(int key)
{
	MyAddress* pAddress;
	//int key = GetAccessKeyFromHTML(_T("ModifyTable"));
	int index;
	CString maker, date;
	SMSMessage* msg;
	pAddress = m_addrBook.GetAddress(key);

	maker.Format(_T("%d"), key);
	maker = "<table id=\"ModifyTable\" accesskey=\"" + maker + "\">";

	index = m_addrBook.SearchFirstMessage(pAddress->GetPhoneNumber(0));

	while (index >= 0 && (msg = m_addrBook.GetMessage(index)))
	{
		msg = m_addrBook.GetMessage(index);
		if (msg->GetSender() == pAddress->GetPhoneNumber(0) || msg->GetReceiver() == pAddress->GetPhoneNumber(0))
		{
			maker += _T("<tr><td class=\"");
			if (msg->GetSender().IsEmpty()) maker += _T("send");
			else maker += _T("receive");
			maker += CString(_T("\">")) + msg->GetMessage().data() + _T("<br /><span>");
			date.Format(_T("%04d.%02d.%02d %02d:%02d:%02d"), msg->GetYear(), msg->GetMonth(), msg->GetDay(),
				msg->GetHour(), msg->GetMinute(), msg->GetSecond());
			maker += date + _T("</span></td></tr>");
		}

		else break;
		index++;
	}
	
	maker += "</table>";
	m_sPersonalMessageBoxCode = maker;
}

void CMyPhoneDlg::UpdateMessageListCode(void)
{
	std::list<std::pair<std::string, int> > msgList;
	std::vector<CommunicationObject> msgSorted;
	size_t i;
	int index = 0;
	PhoneNumber number;
	CString maker;
	
	// copy all messages
	msgSorted.resize(m_addrBook.GetMessageCount());
	for (i = 0; i < m_addrBook.GetMessageCount(); ++i)
	{
		msgSorted[i] = *(m_addrBook.GetMessage(i));
	}

	// sorts by time
	std::sort(msgSorted.begin(), msgSorted.end());

	for (auto it = msgSorted.rbegin(); it != msgSorted.rend(); ++it)
	{
		number = it->GetSender();
		if (number.IsEmpty()) number = it->GetReceiver();

		bool bExist = false;
		for (auto it2 = msgList.begin(); it2 != msgList.end(); ++it2)
		{
			if (it2->first == number.GetPhoneNumber()) {
				++(it2->second);
				bExist = true;
				break;
			}
		}

		if (!bExist) msgList.push_back(std::make_pair<std::string, int>(number.GetPhoneNumber(), 1));
	}

	m_sMessageListCode = _T("<table>");

	for (auto it = msgList.begin(); it != msgList.end(); ++it)
	{
		PhoneNumber number;
		
		try {
			number.SetPhoneNumber(it->first);
		}
		catch (NotPhoneNumberException e)
		{
			continue;
		}

		m_sMessageListCode += _T("<tr><td><span>");

		if ((index = m_addrBook.SearchAddress(number)) < 0)
		{
			m_sMessageListCode += it->first.data();
		}

		else
		{
			maker.Format(_T("%d"), index);
			m_sMessageListCode += _T("<a href=\"#\" id=\"MESSAGE_VIEW\" accesskey=\"") + maker + _T("\">");
			m_sMessageListCode += CString(m_addrBook.GetAddress(index)->GetName().data()) + _T("</a>");
		}

		m_sMessageListCode += _T("</span><br />");

		maker.Format(_T("%d Message"), it->second);
		if (it->second >= 2) maker += _T("s");

		m_sMessageListCode += maker + _T("</td></tr>");
	}

	m_sMessageListCode += _T("</table>");
}


void CMyPhoneDlg::NavigateToResource(UINT nResource)
{
	// go to the HTML site in resource
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
	// get a value from elemeent by ID
	IHTMLElement *psrcElement;
	VARIANT vData;

	GetElement(id, &psrcElement);
	psrcElement->getAttribute(L"value", 2, &vData);

	BSTR strTemp = vData.bstrVal;
	CString ret = (CString)strTemp;

	return ret;
}

int CMyPhoneDlg::GetAccessKeyFromHTML(CString id)
{
	// get an access key from element by ID
	IHTMLElement *psrcElement;
	VARIANT vData;
	int ret;

	GetElement(id, &psrcElement);
	psrcElement->getAttribute(L"accesskey", 2, &vData);

	BSTR strTemp = vData.bstrVal;
	CString sOut = (CString)strTemp;
	LPTSTR stringNumber = sOut.GetBuffer();
	ret = atoi(stringNumber);
	sOut.ReleaseBuffer();

	return ret;
}

int	CMyPhoneDlg::GetAccessKeyFromHTML(IHTMLElement *pElement)
{
	// get an access key from element by an instance
	VARIANT vData;
	int ret;

	pElement->getAttribute(L"accesskey", 2, &vData);
	 
	BSTR strTemp = vData.bstrVal;
	CString sOut = (CString)strTemp;
	LPTSTR stringNumber = sOut.GetBuffer();
	ret = atoi(stringNumber);
	sOut.ReleaseBuffer();

	return ret;
}

void CMyPhoneDlg::OnClose()
{
	m_addrBook.SaveAddressFile(ADDRESS_DATA_FILE);
	m_addrBook.SaveCallsFile(CALL_DATA_FILE);
	m_addrBook.SaveMessageFile(MESSAGE_DATA_FILE);
	CDHtmlDialog::OnClose();
}


BOOL CMyPhoneDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN) return TRUE;
	return CDHtmlDialog::PreTranslateMessage(pMsg);
}
