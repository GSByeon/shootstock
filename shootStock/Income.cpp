// Income.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "Income.h"
#include "afxdialogex.h"
#include "shootStockDlg.h"
// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPT10074[] = 
{
	{L"����",				L"20",	-1,	0,	DT_DATE,	FALSE,	DT_CENTER,	L"",	L""}, 
	{L"�ż��ݾ�",			L"20",	-1,	1,	DT_NUMBER,	FALSE,	DT_CENTER,	L"",	L""}, 
	{L"�ŵ��ݾ�",			L"10",	-1,	2,	DT_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"���ϸŵ�����",		L"25",	-1,	3,	DT_NUMBER,	TRUE,	DT_CENTER,	L"",	L""}, 
	{L"���ϸŸż�����",		L"11",	-1,	4,	DT_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"���ϸŸż���",		L"13",	-1,	5,	DT_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 

};
// CIncome dialog

IMPLEMENT_DYNAMIC(CIncome, CDialogEx)

CIncome::CIncome(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIncome::IDD, pParent)
{

}

CIncome::~CIncome()
{
}

void CIncome::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_IncomeList);
}


BEGIN_MESSAGE_MAP(CIncome, CDialogEx)
	
	
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CIncome message handlers


BOOL CIncome::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 18;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, (LPCWSTR)"Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC1)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC2)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC3)->SetFont(&fnt);
	fnt.Detach();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CIncome::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CIncome::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("���ں��������Ϳ�û"))			// ������������ ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10074) / sizeof(*lstOPT10074);	;		// ��üũ�� / ����ũ�� = ���Ұ���
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 
		// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("���ں��������ʹ���");
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"��������");	strData.Trim();
		SetDlgItemText(IDC_STATIC1,strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"�Ÿż�����");	strData.Trim();
		SetDlgItemText(IDC_STATIC2,strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"�Ÿż���");	strData.Trim();
		SetDlgItemText(IDC_STATIC3,strData);

		strRQName = _T("���ں���������");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10074[j].strKey);	strData.Trim();
				if(j==0){

					int dwitem = 0;
					int dwCount = m_IncomeList.GetItemCount();
					dwitem = m_IncomeList.InsertItem(dwCount,theApp.ConvDataFormat(lstOPT10074[j].nDataType, strData, lstOPT10074[j].strBeforeData, lstOPT10074[j].strAfterData),0);
				}else{
					m_IncomeList.SetItemText(i,j,strData );
					m_IncomeList.SetItemText(i,j, theApp.ConvDataFormat(lstOPT10074[j].nDataType, strData, lstOPT10074[j].strBeforeData, lstOPT10074[j].strAfterData));
					if(lstOPT10074[j].bTextColor){
						if(strData.GetAt(0) == '-')
							m_IncomeList.SetItemTextColor(i,j,RGB(0,0,255));
							
						else
							m_IncomeList.SetItemTextColor(i,j,RGB(255,0,0));
					}

				}
				// 				pListCtrl->SetItem(i,j,1,strData,0,0,0,0);
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveRealDataKhopenapictrl
//! Function			: �ǽð� ó��
//! Param				: LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CIncome::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

void CIncome::GetDailyIncome(void)
{
	m_IncomeList.DeleteAllItems();
	m_IncomeList.DeleteAllColumns();
	m_IncomeList.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_DOUBLEBUFFER);
	m_IncomeList.ModifyStyle(0,LVS_SINGLESEL); 
	m_IncomeList.SetGridLines();
	m_IncomeList.InsertColumn(0,L"����",0,70);
	m_IncomeList.InsertColumn(1,L"�ż��ݾ�",0,70);
	m_IncomeList.InsertColumn(2,L"�ŵ��ݾ�",0,80);
	m_IncomeList.InsertColumn(3,L"���ϸŵ�����",0,80);
	m_IncomeList.InsertColumn(4,L"���ϸŸż�����",0,80);
	m_IncomeList.InsertColumn(5,L"���ϸŸż���",0,80);
	

	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strRQName = _T("���ں��������Ϳ�û");
	theApp.m_khOpenApi.SetInputValue(L"���¹�ȣ"	, pMain->m_AccNo);

	//��й�ȣ = ������(����)

	SYSTEMTIME stTime;

	GetLocalTime(&stTime);

	CTime nextDay(stTime); //Local Time�� CTime���� ��ȯ
	nextDay += CTimeSpan(-7,0,0,0); //Ctime + �Ϸ�

	stTime.wYear = (WORD)nextDay.GetYear();

	stTime.wMonth = (WORD)nextDay.GetMonth();

	stTime.wDay = (WORD)nextDay.GetDay();

	CString strDate;
	strDate.Format(L"%04d%02d%02d",stTime.wYear,stTime.wMonth,stTime.wDay);

	theApp.m_khOpenApi.SetInputValue(L"��������"	,  strDate);

	CString t = COleDateTime::GetCurrentTime().Format(L"%Y%m%d");
	theApp.m_khOpenApi.SetInputValue(L"��������"	, t);


	long ret =  theApp.m_khOpenApi.CommRqData(strRQName,L"OPT10074",0,m_strScrNo);
	theApp.IsError(ret);

}






HBRUSH CIncome::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		pDC->SetTextColor(RGB(0, 0, 255)); //redRGB(255, 0, 0)
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);;
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
