
// shootStockDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "shootStock.h"
#include "shootStockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <sstream>

#define  COMMISSION	0.00015
#define  COMMISSION1	0.0015
#define  COMMISSION2	0.003
// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstFID[] = 
{
	
	{L"�����ڵ�",	L"9001",	-1,	0,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"�ſ뱸��",	L"917",		-1,	1,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"�����",		L"302",		-1,	2,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"���簡",		L"10",		-1,	3,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"��������",	L"930",		-1,	4,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"�򰡱ݾ�",	L"-1",		-1,	5,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"�򰡼���",	L"-1",		-1,	6,		DT_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"���ͷ�",		L"-1",		-1,	7,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L"%"},
	{L"���Աݾ�",	L"932",		-1,	8,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"���簡",		L"10",		-1,	9,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
	{L"��������",	L"930",		-1,	10,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
	{L"���Աݾ�",	L"932",		-1,	11,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
	{L"�򰡱ݾ�",	L"-1",		-1,	12,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
};


// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPT10001[] = 
{
	{L"�����ڵ�",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"�����",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// ���簡 �׸���
	{L"���簡",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"����ȣ",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"���ϴ��",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"�����",		L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"�ŷ���",		L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"�ŷ����",	L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 1��
	{L"250�ְ�",		L"-1",	0,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250�ְ������",L"-1",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250�ְ���",	L"-1",	0,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"�׸鰡",		L"-1",	0,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" ��"}, 
	{L"�ð��Ѿ�",	L"-1",	0,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" ��"}, 
	{L"EPS",			L"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 2��
	{L"250����",		L"-1",	1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250�����������",L"-1",	1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250��������",	L"-1",	1,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"�ں���",		L"-1",	1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" ��"}, 
	{L"��밡",		L"-1",	1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"PER",			L"-1",	1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 3��
	{L"���μ�����",	L"-1",	2,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"�����ֽ�",	L"-1",	2,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" õ"}, 
	{L"�ſ����",	L"-1",	2,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"����",		L"-1",	2,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"��"}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 4��
	{L"�����ְ�",	L"-1",	3,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"BPS",			L"-1",	3,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 5��
	{L"��������",	L"-1",	4,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"PBR",			L"-1",	4,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
};


// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPT10012[] = 
{
	{L"�ֹ�����",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"�ֹ�����",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// ���簡 �׸���
	{L"��ü�����",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"�ֹ�����",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"�ֹ�����",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"�����",		L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"�ŷ���",		L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"�ŷ����",	L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 1��

};

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPW00013[] = 
{
	{L"�������밡�ɱݾ�",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"���ݱݾ�",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// ���簡 �׸���
	{L"�������ű�",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"��밡������",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"�̼���",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// �ֽı⺻���� �׸��� 1��

};



class MoneyOutputter
{
public:
  MoneyOutputter(const char* const locale_name = "US") : 
      loc(locale_name), 
      output(std::use_facet<std::money_put<char> >(loc)),
      iterator(os)
  {

    os.imbue(loc);
    os.setf(std::ios_base::showbase);
  }

  std::string as_string(double value)
  {
    os.str("");  // clear string
    output.put(iterator, false, os, ' ', value * 100.0);
    return os.str();
  }

private:
  std::locale loc;
  const std::money_put<char>& output;
  std::ostringstream os;
  std::ostreambuf_iterator<char, std::char_traits<char> > iterator;
};

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//*******************************************************************/
// BEGIN_EVENTSINK_MAP
//*******************************************************************/
BEGIN_EVENTSINK_MAP(CshootStockDlg, CDialogEx)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 1, OnReceiveTrDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 2, OnReceiveRealDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 3, OnReceiveMsgKhopenapictrl,		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR )
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 4, OnReceiveChejanData,				VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 5, OnEventConnect,					VTS_I4)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 7, OnReceiveRealCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 8, OnReceiveTrCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 9, OnReceiveConditionVer,			VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()
// CshootStockDlg ��ȭ ����




CshootStockDlg::CshootStockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CshootStockDlg::IDD, pParent)
	, m_staticCode(_T("�����ڵ�"))
	, m_staticName(_T("�����"))
	, m_staticPrice(_T("���簡"))
	, m_boardJongmokCode(_T(""))
{
	m_nRet = 0;
	m_nScrN0 = 0;
	m_nCount				= 0;
	m_bNextFlag			= FALSE;
	m_AccNo = L"";
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CshootStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL, theApp.m_khOpenApi);
	DDX_Control(pDX, IDC_LIST1, m_logList);
	DDX_Control(pDX, IDC_TAB1, m_TabControl);
	DDX_Control(pDX, IDC_DEAL_LIST, m_dealList);
	DDX_Text(pDX, IDC_STATIC_CODE, m_staticCode);
	DDX_Text(pDX, IDC_STATIC_NAME, m_staticName);
	DDX_Text(pDX, IDC_STATIC_PRICE, m_staticPrice);
}

BEGIN_MESSAGE_MAP(CshootStockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UPDATESTATUSBAR, &CshootStockDlg::OnUpdatestatusbar)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CshootStockDlg::OnSelchangeTab)

	ON_COMMAND(ID_LIST_SEARCH, &CshootStockDlg::OnListSearch)
END_MESSAGE_MAP()


// CshootStockDlg �޽��� ó����

BOOL CshootStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	InitStatusBar();
	InitlogList();
	InitTabControl();
	InitDealList();
	theApp.m_khOpenApi.CommConnect();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CshootStockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CshootStockDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CshootStockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CshootStockDlg::MainOnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg){
	CString strRQName = sRQName;

	//���űݼ��γ�����ȸ��û
	if (strRQName == _T("���űݼ��γ�����ȸ��û"))		// �ֽı⺻���� ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt =  sizeof(lstOPW00013) / sizeof(*lstOPW00013);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("���űݼ��γ�����ȸ");
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"�������밡�ɱݾ�" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"���ݱݾ�" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"����������ݾ�" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"����������ݾ�" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"�������ű�" );	strData.Trim();
		TraceOutputW(strData);
		if(!strData.IsEmpty()){
			theApp.g_MyMoney = _wtoi(strData);
			if(!theApp.g_MyMoney) return;
			MoneyOutputter outputter;
			string strMoney  = outputter.as_string(stod(strData.GetBuffer()));
			USES_CONVERSION;
			strData =  A2W(strMoney.c_str());
			strData = L"���ݾ�: "+ strData;
			SendMessage(WM_UPDATESTATUSBAR,1,(LPARAM)strData.GetBuffer());
		}
		//arrData.RemoveAll();
		//for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		//{
		//
		//	strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,lstOPW00013[i].strKey );	strData.Trim();
		//	TraceOutputW(strData);
		//	if(!strData.IsEmpty()){
		//		TraceOutputW(strData);
		//	}
		//	arrData.Add(strData);
		//}
	}
	if (strRQName == _T("�����ݻ���Ȳ��û"))		// �ֽı⺻���� ����
	{
		CString strData;

		strRQName = _T("�����ݻ���Ȳ��û");

		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"������");	strData.Trim();

		theApp.g_MyMoney = _wtoi(strData);
		if(!theApp.g_MyMoney) return;
		MoneyOutputter outputter;
		string strMoney  = outputter.as_string(stod(strData.GetBuffer()));
		USES_CONVERSION;
		strData =  A2W(strMoney.c_str());
		strData = L"������: "+ strData;
		SendMessage(WM_UPDATESTATUSBAR,1,(LPARAM)strData.GetBuffer());

		//SetDlgItemInt(IDC_EDIT1,atoi(strData));


		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+1����������");	strData.Trim();
		//SetDlgItemInt(IDC_EDIT2,atoi(strData));



		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+2����������");	strData.Trim();
		//SetDlgItemInt(IDC_EDIT3,atoi(strData));



		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+1��ݰ��ɱݾ�");	strData.Trim();
		//SetDlgItemInt(IDC_EDIT4,atoi(strData));


		strMoney  = outputter.as_string(stod(strData.GetBuffer()));

		strData =  A2W(strMoney.c_str());
		strData = L"d+1��ݰ���: "+strData;
		SendMessage(WM_UPDATESTATUSBAR,2,(LPARAM)strData.GetBuffer());

		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+2��ݰ��ɱݾ�");	strData.Trim();


		strMoney  = outputter.as_string(stod(strData.GetBuffer()));

		strData =  A2W(strMoney.c_str());
		strData = L"d+2��ݰ���: "+strData;
		SendMessage(WM_UPDATESTATUSBAR,3,(LPARAM)strData.GetBuffer());
		//SetDlgItemInt(IDC_EDIT5,atoi(strData));
		//SetDataJongInfoGrid(arrData);
	}


	CString strPrevNext(sPrevNext);

	if (strRQName == _T("���¼��ͷ�"))			// ���¼��ͷ�
	{
		m_bNextFlag = FALSE;
		CString strData;
		int nFieldCnt = sizeof(lstFID) / sizeof(*lstFID);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("���¼��ͷ�");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);	//������ �Ǽ�
		m_nCount += nCnt;	//������ �Ǽ��� �׸��� ��� �߰�
		//m_grdRate.SetRowCount(m_nCount);
		CString strIndex= L"";
		for (i = 0; i < nCnt; i++)
		{
			CString strCode;
			strIndex.Format(L"%d", i);

			int dwitem = 0;
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstFID[j].strKey);
				strData.Trim();
				if (j == 0)	//�����
				{
					strCode = strData;
					m_mapJongCode.SetAt(strCode, strIndex);

					//m_grdKwanSim.SetRowHeight(i, 20);		// ���� ���� ����
					//m_grdKwanSim.SetItemText(i, 0, strCode);
					int dwCount = m_dealList.GetItemCount();

					dwitem = m_dealList.InsertItem(dwCount,strCode,0);
				}
				else if (j == 1) //�ſ뱸��
				{
					if (strData == _T("00"))
					{
						strData = _T("����");
					} 
					else if (strData == _T("03"))
					{
						strData = _T("����");
					}
					else if (strData == _T("99"))
					{
						strData = _T("������");
					}

					m_dealList.SetItemText(i,j, theApp.ConvDataFormat(lstFID[j].nDataType, strData, lstFID[j].strBeforeData,lstFID[j].strAfterData));
				}
				if (strData != "")
				{
					if(j == 4){
						m_OrderList.SetAt(strCode,strData);
					}

					m_dealList.SetItemText(i,j, theApp.ConvDataFormat(lstFID[j].nDataType, strData, lstFID[j].strBeforeData,lstFID[j].strAfterData));
					//m_grdRate.SetItemFormat(i + 1 + m_nNextRow, lstFID[j].nCol, lstFID[j].nAlign);
					//m_grdRate.SetItemText(i + 1 + m_nNextRow, j, theApp.ConvDataFormat(lstFID[j].nDataType, strData, lstFID[j].strBeforeData, lstFID[j].strAfterData));
				}
			}

			int nRow(0);
			//nRow = i + 1 + m_nNextRow;

			//���� ���ͷ� ���
			//SetRate(nRow, strCode);

			//CString strIndex;
			//strIndex.Format(_T("%d"), nRow);

			//������ Ű������ �ؼ� �ο찪�� �����Ѵ�.
			//m_mapJongCode.SetAt(strCode, strIndex);
		}

		//�� ���ͷ� ���
		//SetTotalRate();

		if (strPrevNext == "2")	//������ȸ
		{
			m_bNextFlag = TRUE;	//������ȸ����
			//m_nCount = m_nCount - 1;	//�׸��� ���Row��/�� ����.
			//m_nNextRow = m_nCount;	//������ȸ�� ������ Row���� ����.

			//CString strAccNo;
			//m_EdtAcc.GetWindowText(strAccNo);	//�Է��� ���¹�ȣ.

			//������ȸ�� �Ѵ�.
			theApp.m_khOpenApi.SetInputValue(L"���¹�ȣ", m_AccNo);
			theApp.m_khOpenApi.CommRqData(L"���¼��ͷ�", L"OPT10085", 2, m_strScrNo);
		}

		//������ȸ�� �ƴҶ��� �ǽð� ����� �Ѵ�.
		if (!m_bNextFlag)
		{
			CString strRQName = _T("��������"), strCodeList, strCode;
			long  nCodeCount(0);

			for (int nRow = 0; nRow < m_nCount; nRow++)
			{
				nCodeCount++;
				strCode = m_dealList.GetItemText(nRow, 0);
				strCode.Trim();
				strCode + ";";
				strCodeList += strCode ;
				//�����ڵ� = ���� ��ȸ�� �����ڵ�
				theApp.m_khOpenApi.SetInputValue(L"�����ڵ�"	,  strCode);
				theApp.m_khOpenApi.CommRqData( L"�ֽı⺻������û",  L"OPT10001", 0, m_strScrNo); 
			}

			long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, 0, strRQName, m_strScrNo);
			if (!lRet)
			{
				return;
			}

		}
	}

	if (strRQName == _T("�ֽı⺻������û"))			// ���¼��ͷ�//if (!lstrcmp(sRealType, L"�ֽ�ü��"))	// �ֽ�ü��
	{

		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10001) / sizeof(*lstOPT10001);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("�ֽı⺻����");




		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, lstOPT10001[nIdx].strKey);	strData.Trim();
			if(nIdx== 0){
				if(strData == m_boardJongmokCode){
					//strData = theApp.m_khOpenApi.GetCommRealData(strData, 10);	strData.Trim(); //���簡
					
					m_staticCode = strData;
					
					m_staticName =   theApp.m_khOpenApi.GetMasterCodeName(strData);
					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"���簡");	strData.Trim();
					m_staticPrice = strData;
					//TraceOutputW(strData);
					UpdateData(FALSE);
				}
			}
			arrData.Add(strData);
		}
		//SetDataJongInfoGrid(arrData);

		//m_grdRate.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
		m_dealList.SetItemText(0, 3, arrData.GetAt(2));

		//���� ���ͷ� ���
		CString strCode = arrData.GetAt(0);

		CString strIndex;
		if (!m_mapJongCode.Lookup(strCode, strIndex))
		{
			return;
		}
		SetRate(_wtoi(strIndex), strCode);

		//�� ���ͷ� ���
		//SetTotalRate();
	}

	if (strRQName == _T("�ֹ�ü���û"))			// ���¼��ͷ�//if (!lstrcmp(sRealType, L"�ֽ�ü��"))	// �ֽ�ü��
	{
		TraceOutputW(strRQName);
		CString strData;
		CStringArray arrData;
		int nFieldCnt = 60;// sizeof(lstOPT10012) / sizeof(*lstOPT10012);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("�ֹ�ü��");
		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData.Format(L"%d",nIdx);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,strData );	strData.Trim();
			if(!strData.IsEmpty()){
				TraceOutputW(strData);
			}
			arrData.Add(strData);
		}
	}
	////end
}



//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 0:		// ����â
			{
				((CshootStockDlg *)pWnd)->MainOnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
			}
			break;
		case 1:
			{
				
				((CBuyList *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 2:
			{

				((CCurPrice *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 3:
			{

				((CTopPrice *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 4:
			{

				((CDailyReport *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strRQ = sRQName;
	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		CString strData;
		strData.Format(_T("[%s] [%s] ����"), sRQName, sTrCode);

		CString strRQName = strRQ.Mid(4);
		switch (_wtoi(strScrType))
		{
		case 0:		// ���簡
			{
				//((CCurrentPriceDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
				//pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
				TraceOutputW(sMsg);
			}
			break;


		}
	}
}
//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : �ǽð� ó��
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::MainOnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	
	//���űݼ��γ�����ȸ��û

	if (!lstrcmp(sRealType, L"�ֽĽü�"))		// �ֽĽü�
	{
		TraceOutputW(sRealType);
	}
	else if (!lstrcmp(sRealType, L"�ֽ�ü��"))	// �ֽ�ü��
	{



		CString strIndex, strData;


		if(sJongmokCode == m_boardJongmokCode){
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 10);	strData.Trim(); //���簡
			m_staticPrice = strData;
			m_staticCode = sJongmokCode;
			m_staticName =   theApp.m_khOpenApi.GetMasterCodeName(sJongmokCode);
			//TraceOutputW(strData);
			UpdateData(FALSE);
		}

		if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
		{
			return;
		}



		CString strCode;

		int i, nFieldCnt = sizeof(lstFID) / sizeof(*lstFID);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 0; i < nFieldCnt; i++)
		{
			if (_wtoi(lstFID[i].strRealKey) < 0)
			{
				continue;
			}

			//�ǽð� �����͸� �׸� �°� �����´�.
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstFID[i].strRealKey));	strData.Trim();

			//�׸� �´� �����Ͱ� �������� �׸��忡 ǥ���Ѵ�.
			if (strData != "")
			{
				//m_grdRate.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
				m_dealList.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
			}
		}

		//���� ���ͷ� ���
		strCode = sJongmokCode;
		SetRate(_ttoi(strIndex), strCode);

		//�� ���ͷ� ���
		//SetTotalRate();
	}
}
//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : �ǽð� ó��
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 0:		// main window
				{
					//TraceOutputW(sRealType);
					this->MainOnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					//this->onrecvrea
					
				}
				break;
			case 1:		// ��������
				{
					
					 ((CBuyList *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 2:		// ���簡
				{

					((CCurPrice *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 3:		// �����
				{

					((CTopPrice *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 4:		// �����
				{

					((CDailyReport *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			}
		}
	}

	// �� ���� ó��
	if (!lstrcmp(sRealType, L"����۽ð�"))
	{
		int i;
		CString strData[3], strMsg;
		// 0: ������, 1:�ð�, 2:����� �����ܿ��ð�
		for (i = 0; i < 3; i++)
		{
			strData[i] = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, i);	strData[i].Trim();
		}
		strMsg.Format(L"������ : %s\r\n�ð� : %s\r\n�����ܿ��ð� : %s", strData[0], strData[1], strData[2]);

		if (_wtoi(strData[2]) == 10)
		{
			ReplyMessage(S_OK);		// SendMessage Ǯ��
			MessageBox(strMsg, L"�� ����", MB_ICONINFORMATION | MB_OK);
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : ü���ܰ� �ǽð� ó��
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 0:		// ���簡
				{
					//((CCurrentPriceDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);

					CString strGuBun(sGubun), strAccNo, strAcc;

					strAccNo	= theApp.m_khOpenApi.GetChejanData(9201);	// ü��� ������ ���¹�ȣ
												// ���� ���¹�ȣ
					TraceOutputW(strAccNo);
					
					CString orderNo =  theApp.m_khOpenApi.GetChejanData(9201); //9203 �ֹ���ȣ
					TraceOutputW(orderNo);

					CString orderStatus =  theApp.m_khOpenApi.GetChejanData(913); //913 �ֹ�����
					TraceOutputW(orderStatus);
					//���� ���ͷ� ��ȸ�� ���¹�ȣ�� �ִ� ü��� ���� ���� �� �ְ� ó��.
					if (strAccNo == strAcc)
					{
						if (strGuBun == "4")
						{
							TraceOutputW(L"�������� ����ȸ");
							//OnBtnSearch(); //���������� ����ȸ�Ѵ�.
						}
					}

				}
				break;

			}
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveRealCondition
//! Function      : ���ǰ˻� �ǽð� ���� ����/����
//! Param         : LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 3:		// ���ǰ˻�
				{
					//((CRealAddDlg *)pWnd)->OnReceiveRealCondition(strCode, strType, strConditionName, strConditionIndex);
				}
				break;
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveTrCondition
//! Function			: ���ǰ˻� ������ȸ ����
//! Param				: LPCTSTR sScrNo					- ȭ���ȣ
//!						: LPCTSTR strCodeList			- ���񸮽�Ʈ
//!						: LPCTSTR strConditionName	- ���Ǹ�
//!						: int nIndex								- ���Ǹ��ε���
//!						: int nNext								- ������ȸ����(2: ������ȸ, 0:������ȸ����)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 3:	//���ǰ˻�
			{
				//((CRealAddDlg *)pWnd)->OnReceiveTrCondition(sScrNo, strCodeList, strConditionName, nIndex, nNext);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveConditionVer
//! Function			: ����� ���ǽ� ����
//! Param				: BOOL bRet							- ����(TRUE), ����(FALSE)
//!						: LPCTSTR sMsg					- �޼���(reserved)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	if(lRet != 1)
	{// ����� ���ǰ˻��� ������û�� ������ �߻��� ���...
		CString		strErr; strErr.Format(_T("%s [%d]"), sMsg, lRet);
		AfxMessageBox(strErr);
		return;
	}

	int nScrNo = GetNextScreenNum(3);
	CString strScrNo;
	strScrNo.Format(L"%04d", nScrNo);

	CString strScrType, strKey = strScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 3:	//���ǰ˻�
			{
				//((CRealAddDlg *)pWnd)->OnReceiveConditionVer(lRet, sMsg);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnEventConnect
//! Function      : ���� �뺸 ó��
//! Param         : LONG nItemCnt
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnEventConnect(LONG nItemCnt)
{
	if (nItemCnt == 0)
	{
		// ���� ����ó��
		OutputDebugString(L"connect successs");

		
		SendMessage(WM_UPDATESTATUSBAR,0,(LPARAM)L"���Ἲ��.");
		this->OnBtnGetAccData();
		m_buyList.GetDataSearch();
		//���ͷ���� ��ȸ //8100875411

		//theApp.m_khOpenApi.SetInputValue(L"���¹�ȣ", m_AccNo);
		//long lRet = theApp.m_khOpenApi.CommRqData(L"�������ܰ�����û", L"OPW00018", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}

		//theApp.m_khOpenApi.SetInputValue(L"���¹�ȣ", m_AccNo);
		// lRet = theApp.m_khOpenApi.CommRqData(L"���¼��ͷ�", L"OPT10085", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}
		//theApp.m_khOpenApi.SetInputValue(L"���¹�ȣ", m_AccNo);
		//lRet = theApp.m_khOpenApi.CommRqData(L"�ֹ�ü���û", L"OPT10012", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}
	}
	else
	{
		// ���� ������ ó��
		EndDialog(IDCANCEL);
	}
}

//*******************************************************************/
//! Function Name : GetNextScreenNum
//! Function      : ���� ȭ�� ��ȣ ���
//! Param         : int nScreenType
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CshootStockDlg::GetNextScreenNum(int nScreenType)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	static int nRepeat = 0;
	m_nScrN0++;
	if (m_nScrN0 > 9999)
	{
		nRepeat++;
		m_nScrN0 = 1;
	}

	if (nRepeat > 1)
	{
		nRepeat = 0;
		AfxMessageBox(L"�� �̻� ȭ���� ���� �����ϴ�.�ٸ� ȭ���� �ݰ� ���� �� �ּ���~!");
		return FALSE;
	}

	CString strKey, strTemp;
	strKey.Format(L"%04d", m_nScrN0);
	if (m_mapScreenNum.Lookup(strKey, strTemp))
	{
		return GetNextScreenNum(nScreenType);
	}

	nRepeat = 0;
	strTemp.Format(L"%d", nScreenType);
	m_mapScreenNum.SetAt(strKey, strTemp);
	return TRUE;
}



afx_msg LRESULT CshootStockDlg::OnUpdatestatusbar(WPARAM wParam, LPARAM lParam)
{
	return m_StatusBar.SetPaneText(wParam,(LPCTSTR)lParam);
}


void CshootStockDlg::InitStatusBar(void)
{
	UINT m_IsCreated =  m_StatusBar.Create(this);


	UINT  Indicates[5]; 
	for (int i = 1; i<5;i++)
	{
		Indicates[i] = 50+i;
	}

	m_StatusBar.SetIndicators(Indicates,5);
	CRect rect;
	GetClientRect(&rect);
	UINT PaneWidth = rect.Width();

	m_StatusBar.SetPaneInfo(0,0,SBPS_NORMAL,PaneWidth * 10 / 100);
	m_StatusBar.SetPaneInfo(1,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(2,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(3,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(4,0,SBPS_NORMAL,PaneWidth * 27 / 100);

	m_StatusBar.SetPaneText(0,L" ������..");
	m_StatusBar.SetPaneText(1,L"������: N/A");
	m_StatusBar.SetPaneText(2,L"d+1��ݰ��� N/A");
	m_StatusBar.SetPaneText(3,L"d+2��ݰ��� N/A");
	m_StatusBar.SetPaneText(4,L"����ð�");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
}


void CshootStockDlg::OnBtnGetAccData(void)
{

	m_AccNo = theApp.m_khOpenApi.GetLoginInfo(L"ACCLIST");
	m_AccNo.Replace(L";",L"");
	CString   strSafeKeyStatus = theApp.m_khOpenApi.GetLoginInfo(L"KEY_BSECGB" );

	//HWND pWnd = ::FindWindow(NULL,L"���º�й�ȣ �Է� (����: 3.72)");
	CWnd *pWnd = FindWindowEx(this->m_hWnd,NULL,NULL,L"���º�й�ȣ �Է� (����: 3.72)");
	//FindWindowEx(this)	::SetWindowPos (pWnd,NULL,0,0,0,0,SWP_SHOWWINDOW);
	CString strServerType =  theApp.m_khOpenApi.KOA_Functions(_T("GetServerGubun"), _T(""));
	if(strServerType == L"1"){//��������
		AfxMessageBox(L"���� ������ ������ �������ڼ����Դϴ�,��й�ȣ �ƹ��ų� �Է��ϼŵ� �˴ϴ� !",MB_ICONINFORMATION);
		theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
	}else{
		MessageBox(L"���!����!����!",L"���� ������ ������ ���󼭹��Դϴ�,\n��й�ȣ ������ ���°� ���� �˴ϴ�\n�������ֽñ�ٶ��ϴ� !",MB_ICONWARNING);
		theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
	}
	
	


// 	���⼭ strAcctList�� ';'�� �и��� �������� �����
// 		��) "3040525910;567890;3040526010"

	if (!GetNextScreenNum(0))
	{
		return;
	}


	this->m_strScrNo.Format(_T("%04d"), m_nScrN0);


	m_mapScreen.SetAt(m_strScrNo, this);

	theApp.g_MyMoney = 100000;
	//CString strRQName = _T("���űݼ��γ�����ȸ��û");
	//CString strTRCode = TR_OPW00013;
	////theApp.theApp.m_khOpenApi.SetInputValue("�����ڵ�", "113810");
	////���¹�ȣ = ���� ��ȸ�� �������¹�ȣ  //51653280
	//theApp.m_khOpenApi.SetInputValue(_T("���¹�ȣ")	, m_AccNo);
	////theApp.theApp.m_khOpenApi.SetInputValue("���¹�ȣ"	,  "5165328010");
	////��й�ȣ = ������(����)
	//theApp.m_khOpenApi.SetInputValue(_T("��й�ȣ")	,  _T(""));

	//long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	//CString		strErr;
	//if (!theApp.IsError(lRet))
	//{
	//	strErr.Format(_T("�ֽı⺻������û ���� [%s][%d]"), strTRCode, lRet);
	//	OutputDebugString(strErr);
	//};

	//CString strRQName = _T("�����ݻ���Ȳ��û");
	//CString strTRCode = TR_OPW00001;
	////theApp.theApp.m_khOpenApi.SetInputValue("�����ڵ�", "113810");
	////���¹�ȣ = ���� ��ȸ�� �������¹�ȣ  //51653280
	//theApp.m_khOpenApi.SetInputValue(_T("���¹�ȣ")	, m_AccNo);
	////theApp.theApp.m_khOpenApi.SetInputValue("���¹�ȣ"	,  "5165328010");
	////��й�ȣ = ������(����)
	//theApp.m_khOpenApi.SetInputValue(_T("��й�ȣ")	,  _T("2419"));

	////��й�ȣ�Է¸�ü���� = 00
	//theApp.m_khOpenApi.SetInputValue(_T("��й�ȣ�Է¸�ü����")	,  _T("2419"));

	////��ȸ���� = 1:������ȸ, 2:�Ϲ���ȸ
	//theApp.m_khOpenApi.SetInputValue(_T("��ȸ����")	,  _T("2"));
	//long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	//CString		strErr;
	//if (!theApp.IsError(lRet))
	//{
	//	strErr.Format(_T("�ֽı⺻������û ���� [%s][%d]"), strTRCode, lRet);
	//	OutputDebugString(strErr);
	//};
}


void CshootStockDlg::InitlogList(void)
{
	CRect rect;
	m_logList.GetClientRect(&rect);//��ȡ�б���ͼ�ؼ��Ŀ��

	int nWidth = rect.Width();

	m_logList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
	m_logList.InsertColumn(0, _T("No"), LVCFMT_LEFT);
	m_logList.InsertColumn(1, _T("Time"), LVCFMT_LEFT);
	m_logList.InsertColumn(2, _T("Information"), LVCFMT_LEFT);

	//���ø��еĿ��

	m_logList.GetClientRect(&rect);//��ȡ�б���ͼ�ؼ��Ŀ��

	nWidth = rect.Width();
	m_logList.SetColumnWidth(0, nWidth * 7 / 100);//����ռ25%
	m_logList.SetColumnWidth(1, nWidth * 15 / 100);//����ռ13%
	m_logList.SetColumnWidth(2, nWidth * 78 / 100);//��ַռ25%


	m_logList.SetBkColor(RGB(0,0,0)); 
	m_logList.SetTextColor(RGB(0,255,102)); 
	m_logList.SetTextBkColor(RGB(0,0,0)); 
}
void CshootStockDlg::TraceOutputA(const char* fmt,...)
{
	string str = fmt;
	str += "\r\n";
	USES_CONVERSION;
	//m_RichEdit.SetSel(-1, -1);
	//m_RichEdit.ReplaceSel( (LPCTSTR)A2W(str.c_str()) );
	//m_RichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM,0); 
	//InitRichEdit();
	// 

	//���������Ŀ����1000��ɵ�
	//if(t_loglistControl.GetItemCount() > 1000 )
	//t_loglistControl.DeleteAllItems();

	CString time; //��ȡϵͳʱ��
	CTime tm; 

	tm = CTime::GetCurrentTime(); 

	time=tm.Format("%X"); 

	//OutputDebugString(time);
	//���
	CString l_index;

	int dwCount = m_logList.GetItemCount();

	l_index.Format(_T("%d"),dwCount+1);

	int dwitem = m_logList.InsertItem(dwCount,l_index,0);
	m_logList.SetItem(dwitem,1,1,time,0,0,0,0);
	m_logList.SetItem(dwitem,2,1,A2W(str.c_str()),0,0,0,0);
	m_logList.EnsureVisible(dwitem,TRUE);
}

void CshootStockDlg::TraceOutputW(const TCHAR* fmt,...)
{
	CString time; //��ȡϵͳʱ��
	CTime tm; 

	tm = CTime::GetCurrentTime(); 

	time=tm.Format("%X"); 

	//OutputDebugString(time);
	//���
	CString l_index;

	int dwCount = m_logList.GetItemCount();

	l_index.Format(_T("%d"),dwCount+1);

	int dwitem = m_logList.InsertItem(dwCount,l_index,0);
	m_logList.SetItem(dwitem,1,1,time,0,0,0,0);
	m_logList.SetItem(dwitem,2,1,fmt,0,0,0,0);
	m_logList.EnsureVisible(dwitem,TRUE);
}

void CshootStockDlg::InitTabControl(void)
{
	TCITEM   tm;   
	CImageList pImageList;


	pImageList.Create(16, 16, ILC_COLOR16|ILC_MASK,0,2);
	pImageList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	//this->m_hWnd = 0;

	m_TabControl.SetImageList(&pImageList);
	m_TabControl.InsertItem(0, _T("��������"));
	m_TabControl.InsertItem(1, _T("���簡"));
	m_TabControl.InsertItem(2, _T("���ϵ����"));
	m_TabControl.InsertItem(3, _T("���ں��ü�"));
	pImageList.Detach();

	tm.mask = TCIF_IMAGE;   //   �������Ϳ�����   
	for(int i=0; i<3; i++)   
	{   
		m_TabControl.GetItem(i,&tm);   
		tm.iImage=i;   
		m_TabControl.SetItem(i,&tm);   
	}


	if (!GetNextScreenNum(1))
	{
		return;
	}

	m_buyList.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_buyList.Create(IDD_BUY_LIST, &m_TabControl);
	
	m_mapScreen.SetAt(m_buyList.m_strScrNo, &m_buyList);


	if (!GetNextScreenNum(2))
	{
		return;
	}

	m_curPrice.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_curPrice.Create(IDD_CUR_PRICE,&m_TabControl);
	
	m_mapScreen.SetAt(m_curPrice.m_strScrNo, &m_curPrice);

	if (!GetNextScreenNum(3))
	{
		return;
	}


	m_topPrice.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_topPrice.Create(IDD_TOP_PRICE,&m_TabControl);

	m_mapScreen.SetAt(m_topPrice.m_strScrNo, &m_topPrice);
	//m_BenXOut.Create(IDD_DIALOG_OUT,&m_TabControl);


	if (!GetNextScreenNum(4))
	{
		return;
	}


	m_DailyReport.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_DailyReport.Create(IDD_DIALOG_DAILY,&m_TabControl);

	m_mapScreen.SetAt(m_DailyReport.m_strScrNo, &m_DailyReport);

	CRect r;
	m_TabControl.GetClientRect (&r);

	m_buyList.SetWindowPos (NULL,3,22,r.right -8 ,r.bottom-28,SWP_SHOWWINDOW);
	m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
}


void CshootStockDlg::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CRect r;
	m_TabControl.GetClientRect (&r);

	switch(m_TabControl.GetCurSel())
	{
	case 0:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28 ,SWP_SHOWWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 1:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 2:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	case 3:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_DailyReport.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	}
	*pResult = 0;
}


//{L"�����ڵ�",	L"9001",	-1,	0,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
//{L"�ſ뱸��",	L"917",		-1,	1,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
//{L"�����",		L"302",		-1,	2,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
//{L"���簡",		L"10",		-1,	3,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"��������",	L"930",		-1,	4,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"�򰡱ݾ�",	L"-1",		-1,	5,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"�򰡼���",	L"-1",		-1,	6,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"���ͷ�",		L"-1",		-1,	7,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L"%"},
//{L"���Աݾ�",	L"932",		-1,	8,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"���簡",		L"10",		-1,	9,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
//{L"��������",	L"930",		-1,	10,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
//{L"���Աݾ�",	L"932",		-1,	11,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
//{L"�򰡱ݾ�",	L"-1",		-1,	12,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(�������� ����)
void CshootStockDlg::InitDealList(void)
{
	m_dealList.SetExtendedStyle(LVS_EX_FULLROWSELECT );
	m_dealList.ModifyStyle(0,LVS_SINGLESEL); 
	m_dealList.SetGridLines();
	m_dealList.InsertColumn(0,L"�����ڵ�",0,70);
	m_dealList.InsertColumn(1,L"�ſ뱸��",0,80);
	m_dealList.InsertColumn(2,L"�����",0,100);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_dealList.InsertColumn(3,L"���簡",0,80);
	m_dealList.InsertColumn(4,L"��������",0,80);
	m_dealList.InsertColumn(5,L"�򰡱ݾ�",0,80);
	m_dealList.InsertColumn(6,L"�򰡼���",0,80);
	m_dealList.InsertColumn(7,L"���ͷ�",0,80);
	m_dealList.InsertColumn(8,L"���Աݾ�",0,100);
}
//*******************************************************************/
//! Function Name	: SetRate
//! Function			: ���� ���ͷ� ���
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CshootStockDlg::SetRate(int nRow, CString strCode)
{
	//�ֽ� ���� ���� ���ͷ� ����̶� �ֽĿ� ������ ���ͷ��� �ٸ��� ������ �˷��帳�ϴ�.

	//���簡
	CString strData, strTmp;
	strData = m_dealList.GetItemText(nRow, 3);
	strData.Replace(L",",L"");
	strTmp = strData.Left(1);
	if (strTmp == "-" || strTmp == "+")
	{
		strData = strData.Mid(1);
	}
	double nPrice = _ttof(strData);

	//����
	double nQty = _ttof(m_dealList.GetItemText(nRow, 4));

	//���Աݾ�
	strTmp =  m_dealList.GetItemText(nRow, 8);
	strTmp.Replace(L",",L"");
	double nPurchase = _ttof(strTmp);

	int nCount(0);
	nCount = m_dealList.GetItemCount();

	//�ż������ ������ = ���Աݾ� * ��ü������(0.015%) (10���̸� ����)
	m_BuyComm = nPurchase * COMMISSION;
	m_BuyComm = floor(m_BuyComm / 10) * 10;	//(10���̸� ����)

	//�ŵ������ ������ = ���簡 * ���� * ��ü������(0.015%) (10���̸� ����)
	m_SellComm = nPrice * nQty * COMMISSION;
	m_SellComm = floor(m_SellComm / 10) * 10;	//(10���̸� ����)

	//������
	long lMarketType = theApp.m_khOpenApi.GetMarketType(strCode);
	if (lMarketType == 0) //�ŷ���
	{
		//������(�ŷ���) = ���簡 * ���� * 0.15%(���̸� ����) * 2
		m_Tax = nPrice * nQty * COMMISSION1;
		m_Tax = floor(m_Tax) * 2;
	} 
	else if (lMarketType == 10)//�ڽ���
	{
		//������(�ڽ���) = ���簡 * ���� * 0.3%(���̸� ����)
		m_Tax = floor(nPrice * nQty * COMMISSION2);
	}

	CString strTemp;

	//���� �򰡱ݾ� = (���簡 * ����) - �ż������ ������ - �ŵ������ ������ - ������ �����
	m_Eval = (nPrice * nQty) - m_BuyComm - m_SellComm - m_Tax;
	strTemp.Format(_T("%0.lf"), m_Eval);
	
	m_dealList.SetItemText(nRow, 5,  theApp.ConvDataFormat(lstFID[5].nDataType, strTemp, lstFID[5].strBeforeData, lstFID[5].strAfterData));
	//m_dealList.SetItemText(nRow, 12,  theApp.ConvDataFormat(lstFID[12].nDataType, strTemp, lstFID[12].strBeforeData, lstFID[12].strAfterData));

	COLORREF tempC = RGB(0,0,255);
	//���� �򰡼��� = �򰡱ݾ� - ���Աݾ�
	m_Profit = m_Eval - nPurchase;
	strTemp.Format(_T("%0.lf"), m_Profit);

	if (strTemp.GetAt(0) == '+' )	// ��ȣ�� ���� ���󺯰�
	{
		tempC =  RGB(255,0,0);
	}
	else if (strTemp.GetAt(0) == '-')	// ��ȣ�� ���� ���󺯰�
	{
		tempC =  RGB(0,0,255);
	}
	else
	{
		tempC =  RGB(0,0,0);
	}

	m_dealList.SetItemText(nRow, 6,  theApp.ConvDataFormat(lstFID[6].nDataType, strTemp, lstFID[6].strBeforeData, lstFID[6].strAfterData));
	m_dealList.SetItemTextColor(nRow, 6,tempC);
	//���� ���ͷ� = �򰡼��� / ���Աݾ� * 100
	if (nPurchase == 0)
	{
		m_Rate = 0;
	}
	else
	{
		m_Rate = m_Profit / nPurchase * 100;
	}
	strTemp.Format(_T("%0.2lf"), m_Rate);

	
	if (strTemp.GetAt(0) == '+' )	// ��ȣ�� ���� ���󺯰�
	{
		tempC =  RGB(255,0,0);
	}
	else if (strTemp.GetAt(0) == '-')	// ��ȣ�� ���� ���󺯰�
	{
		tempC =  RGB(0,0,255);
	}
	else
	{
		tempC =  RGB(0,0,0);
	}
	m_dealList.SetItemText(nRow, 7,  theApp.ConvDataFormat(lstFID[7].nDataType, strTemp, lstFID[7].strBeforeData, lstFID[7].strAfterData));
	m_dealList.SetItemTextColor(nRow, 7,tempC);


}

//*******************************************************************/
//! Function Name	: SetRate
//! Function			: ���� ���ͷ� ���
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CshootStockDlg::SetTotalRate()
{
// 	int nCnt = m_grdRate.GetRowCount();	//�׸��� Row ���� ���ϱ�
// 	double dTotalEval(0), dTotalPurchase(0), dTotalProfit, dTotalRate(0);
// 	CString strTotalEval, strTotalPurchase, strTotalProfit, strTotalRate;
// 
// 	for (int i = 1; i < nCnt; i++)
// 	{
// 		dTotalEval += _ttof(m_grdRate.GetItemText(i, 12));			// �� �򰡱ݾ�
// 		dTotalPurchase += _ttof(m_grdRate.GetItemText(i, 11));	// �� ���Աݾ�
// 	}
// 
// 	strTotalEval.Format(_T("%0.lf"), dTotalEval);
// 	strTotalEval = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalEval);
// 	m_EdtTotalEval.SetWindowText(strTotalEval);
// 
// 	strTotalPurchase.Format(_T("%0.lf"), dTotalPurchase);
// 	strTotalPurchase = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalPurchase);
// 	m_EdtTotalPurchase.SetWindowText(strTotalPurchase);
// 
// 
// 	// �� �򰡼���
// 	dTotalProfit = dTotalEval - dTotalPurchase;
// 	strTotalProfit.Format(_T("%0.lf"), dTotalProfit);
// 	strTotalProfit = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalProfit);
// 	m_EdtTotalProfit.SetWindowText(strTotalProfit);
// 
// 	// �� ���ͷ�
// 	dTotalRate = dTotalProfit / dTotalPurchase * 100;
// 	strTotalRate.Format(_T("%0.2lf"), dTotalRate);
// 	strTotalRate = theApp.ConvDataFormat(DT_NONE, strTotalRate, "", "%");
// 	m_EdtTotalRate.SetWindowText(strTotalRate);
}



void CshootStockDlg::OnListSearch()
{
	// TODO: Add your command handler code here
	if (!GetNextScreenNum(1))
	{
		return;
	}

	CJongDlg *pJongDlg = new CJongDlg(this);
	pJongDlg->m_strScrNo.Format(L"%04d", m_nScrN0);
	pJongDlg->Create(IDD_JONG_LIST);

	m_mapScreen.SetAt(pJongDlg->m_strScrNo, pJongDlg);
}


BOOL CshootStockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
