// DailyReport.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "DailyReport.h"
#include "afxdialogex.h"
#include "shootStockDlg.h"

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPT10086[] = 
{
	{L"��¥",				L"20",	-1,	0,	DT_DATE,	FALSE,	DT_CENTER,	L"",	L""}, 
	{L"�ð�",				L"20",	-1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_CENTER,	L"",	L""}, 
	{L"��",				L"10",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"����",				L"25",	-1,	3,	DT_ZERO_NUMBER,		TRUE,	DT_CENTER,	L"",	L""}, 
	{L"����",				L"11",	-1,	4,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"���Ϻ�",				L"13",	-1,	5,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"�����",				L"14",	-1,	6,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, 
	{L"�ŷ���",				L"14",	-1,	7,	DT_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"���μ��ż�",			L"14",	-1,	8,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"������ż�",			L"14",	-1,	9,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"���μ��ż�",			L"14",	-1,	10,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 

};
// CDailyReport dialog

IMPLEMENT_DYNAMIC(CDailyReport, CDialogEx)

CDailyReport::CDailyReport(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDailyReport::IDD, pParent)
{

}

CDailyReport::~CDailyReport()
{
}

void CDailyReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_RepotCtrl);
}


BEGIN_MESSAGE_MAP(CDailyReport, CDialogEx)
END_MESSAGE_MAP()


// CDailyReport message handlers


BOOL CDailyReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//*******************************************************************/
//! Function Name	: OnReceiveRealDataKhopenapictrl
//! Function			: �ǽð� ó��
//! Param				: LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CDailyReport::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDailyReport::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("�Ϻ��ְ���û"))			// ������������ ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10086) / sizeof(*lstOPT10086);		// ��üũ�� / ����ũ�� = ���Ұ���
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 
		// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("�Ϻ��ְ�");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		m_RepotCtrl.SetRedraw(FALSE);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			int dwitem = 0;
			for (j = 0; j < nFieldCnt; j++)
			{
				
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10086[j].strKey);	strData.Trim();
				

				
				if(j == 0){
					int dwCount = m_RepotCtrl.GetItemCount();

					dwitem = m_RepotCtrl.InsertItem(dwCount,strData,0);
				}
				if(lstOPT10086[j].nCol != -1){
					//m_RepotCtrl.SetItem(i,j,1,theApp.removeSign(strData),0,0,0,0);
					m_RepotCtrl.SetItemText(i,j, theApp.ConvDataFormat(lstOPT10086[j].nDataType, strData, lstOPT10086[j].strBeforeData, lstOPT10086[j].strAfterData));
					if(lstOPT10086[j].bTextColor){
						if(strData.GetAt(0) == '+')
							m_RepotCtrl.SetItemTextColor(dwitem,j,RGB(255,0,0));
						else if(strData.GetAt(0) == '-')
							m_RepotCtrl.SetItemTextColor(dwitem,j,RGB(0,0,255));
						else
							m_RepotCtrl.SetItemTextColor(dwitem,j,RGB(0,0,0));
					}
				}
				
			}
		}
		m_RepotCtrl.SetRedraw();
	}
}

void CDailyReport::InitList(void)
{
	m_RepotCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_DOUBLEBUFFER );
	m_RepotCtrl.ModifyStyle(0,LVS_SINGLESEL); 
	m_RepotCtrl.SetGridLines();
	m_RepotCtrl.InsertColumn(0,L"����",0,70);
	m_RepotCtrl.InsertColumn(1,L"�ð�",0,80);
	m_RepotCtrl.InsertColumn(2,L"��",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_RepotCtrl.InsertColumn(3,L"����",0,80);
	m_RepotCtrl.InsertColumn(4,L"����",0,80);
	m_RepotCtrl.InsertColumn(5,L"���ϴ��",0,80);
	m_RepotCtrl.InsertColumn(6,L"�����",0,80);
	m_RepotCtrl.InsertColumn(7,L"�ŷ���",LVCFMT_RIGHT,80);

	m_RepotCtrl.InsertColumn(8,L"����",LVCFMT_RIGHT,80);
	m_RepotCtrl.InsertColumn(9,L"���",LVCFMT_RIGHT,80);
	m_RepotCtrl.InsertColumn(10,L"����",LVCFMT_RIGHT,80);
	
}


void CDailyReport::SendSearch(void)
{
		m_RepotCtrl.DeleteAllItems();
		CString strRQName = _T("�Ϻ��ְ���û");
		CString strTRCode = TR_OPT10086;
		//theApp.m_khOpenApi.SetInputValue("�����ڵ�", "113810");
		//���¹�ȣ = ���� ��ȸ�� �������¹�ȣ  //51653280
		//theApp.m_khOpenApi.SetInputValue(L"���¹�ȣ"	,  L"8100875411");
		//theApp.m_khOpenApi.SetInputValue("���¹�ȣ"	,  "5165328010");
		//��й�ȣ = ������(����)
		//���屸�� = 000:��ü, 001:�ڽ���, 101:�ڽ���
		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		theApp.m_khOpenApi.SetInputValue(L"�����ڵ�"	,pMain->m_staticCode );

		COleDateTime tm = COleDateTime::GetCurrentTime();
		CString curDate = tm.Format(L"%Y%m%d");

		//�ŷ�������� = 0:��ü��ȸ, 3:3õ�����̻�, 5:5õ�����̻�, 10:1����̻�, 30:3����̻�, 50:5����̻�, 100:10����̻�, 300:30����̻�, 500:50����̻�, 1000:100����̻�, 3000:300����̻�, 5000:500����̻�
		theApp.m_khOpenApi.SetInputValue(L"��ȸ����"	,  curDate);

		theApp.m_khOpenApi.SetInputValue(L"ǥ�ñ���"	,  L"0");
		long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
		CString		strErr;
		if (!theApp.IsError(lRet))
		{
			strErr.Format(_T("�ֽı⺻������û ���� [%s][%d]"), strTRCode, lRet);
			OutputDebugString(strErr);
		};
	

}
