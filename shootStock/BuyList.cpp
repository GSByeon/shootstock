// BuyList.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "BuyList.h"
#include "afxdialogex.h"
#include "../CIni_Src/Ini.h"
#include "shootStockDlg.h"
// CBuyList dialog
const CString m_strRealSet = L"�ֽĽü�;�ֽ�ü��;�ֽĿ���ü��";

// {��ȸ Ű,		���� Ű,	��, ��, Ÿ��,			�� ����, ����, �� ����, �� ����}
const stGRID lstOPTKWFID[] = 
{

	{L"�����ڵ�",		L"-1",	-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"�����",			L"-1",	-1,	2,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"���簡",			L"0",	-1,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"���ϴ���ȣ",	L"10",	-1,	-1,	DT_SIGN,		TRUE,	DT_CENTER,	L"",	L""}, 
	{L"�����",			L"2",	-1,	4,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, 
	{L"�ŷ���",			L"5",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"�ð�",			L"16",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"��",			L"17",	-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"����",			L"18",	-1,	8,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"����",			L"18",	-1,9,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"�ż�ȣ��",			L"18",	-1,	10,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"�ŵ�ȣ��",			L"18",	-1,	11,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	/*{L"�ż�ȣ��",		L"0",	-1,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"���ϰŷ������",	L"13",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, */
};

// �ǽð� �ֹ�ü��(���簡 ǥ�ÿ�)
const stGRID lstOPTKWFID_B[] = 
{
	{L"�����ڵ�",		L"-1",	-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"�����",			L"-1",	-1,	2,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"���簡",			L"10",	-1,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"���ϴ���ȣ",	L"25",	-1,	-1,	DT_SIGN,		TRUE,	DT_CENTER,	L"",	L""}, 
	{L"�����",			L"12",	-1,	4,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, 
	{L"�ŷ���",			L"13",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"�ð�",			L"16",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"��",			L"17",	-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"����",			L"18",	-1,	8,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"����",			L"10",	-1,9,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"�ż�ȣ��",		L"28",	-1,	10,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"�ŵ�ȣ��",		L"27",	-1,	11,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	/*{L"���ϴ��",		L"11",	-1,	-1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"���ϰŷ������",	L"30",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, */
};




IMPLEMENT_DYNAMIC(CBuyList, CDialogEx)

CBuyList::CBuyList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBuyList::IDD, pParent)
{

}

CBuyList::~CBuyList()
{
}

void CBuyList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_COMBO1, m_SearchComboList);
}


BEGIN_MESSAGE_MAP(CBuyList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CBuyList::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CBuyList::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CBuyList::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CBuyList::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_ORDER1, &CBuyList::OnBnClickedOrder1)
	ON_BN_CLICKED(IDC_ORDER2, &CBuyList::OnBnClickedOrder2)
	ON_BN_CLICKED(IDC_ORDER3, &CBuyList::OnBnClickedOrder3)
	ON_BN_CLICKED(IDC_BUTTON_SELLALL, &CBuyList::OnBnClickedButtonSellall)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CBuyList::OnBnClickedButtonTest)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CBuyList::OnNMClickList)
	ON_BN_CLICKED(IDC_BUTTON_CHATVIEW, &CBuyList::OnBnClickedButtonChatview)
	ON_BN_CLICKED(IDC_BUTTON_ALL_CANCEL, &CBuyList::OnBnClickedButtonAllCancel)
END_MESSAGE_MAP()


// CBuyList message handlers


BOOL CBuyList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CBuyList::InitList(void)
{
	m_ListBox.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_DOUBLEBUFFER );
	m_ListBox.ModifyStyle(0,LVS_SINGLESEL); 
	m_ListBox.SetGridLines();
	m_ListBox.InsertColumn(0,L"#",0,50);
	m_ListBox.InsertColumn(1,L"�ڵ�",0,50);
	m_ListBox.InsertColumn(2,L"�����",0,80);
	m_ListBox.InsertColumn(3,L"���簡",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_ListBox.InsertColumn(4,L"�����",0,80);
	m_ListBox.InsertColumn(5,L"�ŷ���",0,80);
	m_ListBox.InsertColumn(6,L"�ð�",0,80);
	m_ListBox.InsertColumn(7,L"��",0,80);
	m_ListBox.InsertColumn(8,L"����",0,80);
	m_ListBox.InsertColumn(9,L"����",0,80);
	m_ListBox.InsertColumn(10,L"�ż�ȣ��",0,80);
	m_ListBox.InsertColumn(11,L"�ŵ�ȣ��",0,80);
}





//*******************************************************************/
//! Function Name : SendJongSearch
//! Function      : ���� ��ȸ ��û
//! Param         : int nCodeCount/* = 0*/, CString strCodeList/* = ""*/ : ���� - "000660;005930;", int nAddType/*= 0*/ ���� ������ȸ���� �߰��� ������ ��ȸ�Ҷ� ����(0:�⺻, 5:�߰�)
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CBuyList::SendJongSearch(int nCodeCount/* = 0*/, CString strCodeList/* = ""*/, int nAddType/*= 0*/)
{
	if (nCodeCount < 1 || strCodeList.GetLength() < 1)
	{
		int i, nCnt = m_ListBox.GetItemCount();
		if (nCnt < 3)
		{
			return;
		}
		nCodeCount = 0;
		for (i = 1; i < nCnt; i++)
		{
			nCodeCount++;
			CString temp = m_ListBox.GetItemText(i, 1) + ";";
			strCodeList += temp;
		}
	}

	if (nCodeCount > 0 && strCodeList.GetLength() > 0)
	{
		CString strRQName = _T("��������");
		long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, nAddType, strRQName, m_strScrNo);
		if (!theApp.IsError(lRet))
		{
			return;
		}
	}
}
void CBuyList::GetDataSearch(void)
{

	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);
	int i, nCnt =Jongmok.GetInt(L"JONG_CODE",L"COUNT",0)+ 1;
	CString strCode, strIndex, strCodeList = L"";

	
	m_mapJongCode.RemoveAll();

	for (i = 1; i < nCnt; i++)
	{
		strIndex.Format(L"%d", i);
	
		
		CString szItem =  Jongmok.GetString(L"JONG_CODE",strIndex);
		strCode = szItem;		
		strCode.Trim();

		// �����ڵ� �߰�
		m_mapJongCode.SetAt(strCode, strIndex);

		//m_grdKwanSim.SetRowHeight(i, 20);		// ���� ���� ����
		//m_grdKwanSim.SetItemText(i, 0, strCode);
		int dwCount = m_ListBox.GetItemCount();

		CString strConstruction =  theApp.m_khOpenApi.GetMasterConstruction(strCode);
		CString strState =  theApp.m_khOpenApi.GetMasterStockState(strCode);
		CString strStatus = strConstruction + L"|"  + strState;
		int dwitem = m_ListBox.InsertItem(dwCount,strStatus,0);
		
 		m_ListBox.SetItem(dwitem,1,1,strCode,0,0,0,0);
// 		m_ListBox.SetItem(dwitem,2,1,usrMgr->strData2,0,0,0,0);
// 		m_ListBox.SetItem(dwitem,3,1,usrMgr->strData3,0,0,0,0);
// 		m_ListBox.SetItem(dwitem,4,1,usrMgr->strData4,0,0,0,0);
		//m_ListCtrl.SetItem(dwitem,4,1,ch,0,0,0,0);
		m_ListBox.SetItemData(dwitem,(DWORD)strCode.GetBuffer());

		if(isOdd(dwitem))
			m_ListBox.SetItemBkColor(dwitem, -1, RGB(241,244,248), FALSE);
		strCodeList += strCode + L";";
	}
	if (!strCodeList.IsEmpty())
	{
		// ���� ��ȸ ��û
		SendJongSearch(nCnt - 1, strCodeList,0);
	}
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CBuyList::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("��������"))			// ������������ ����
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPTKWFID) / sizeof(*lstOPTKWFID);		// ��üũ�� / ����ũ�� = ���Ұ���
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
// 
// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("������������");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPTKWFID[j].strKey);	strData.Trim();
// 				pListCtrl->SetItem(i,j,1,strData,0,0,0,0);
// 				if(j == 2){
// 					if(strData.GetAt(0) == '-')
// 						pListCtrl->SetItemTextColor(i,j,RGB(0,0,255));
// 					else
// 						pListCtrl->SetItemTextColor(i,j,RGB(255,0,0));
// 				}
				//pListCtrl->SetItemBkColor(i,j,RGB(255,0,0)); red
				
				//m_grdKwanSim.SetItemFormat(i + 1, lstOPTKWFID[j].nCol, lstOPTKWFID[j].nAlign);
				//m_ListBox.SetItemText(0,j,strData);
				//m_ListBox.SetItem(i,j,1,strData,0,0,0,0);
				arrData.Add(strData);
				
			}
			OnUpdateListData(arrData);
			//SetDataKwanSimGrid(arrData);
		}
// 		if (m_cellSelect.row > 0)
// 		{
// 			if (m_cellSelect.row >= m_grdKwanSim.GetRowCount())
// 			{
// 				m_cellSelect.row = m_grdKwanSim.GetRowCount() - 1;
// 			}
// 			m_grdKwanSim.SetFocusCell(m_cellSelect);
// 			m_grdKwanSim.SetSelectedRange(m_cellSelect.row, m_cellSelect.col, m_cellSelect.row, m_cellSelect.col);
// 		}
	}
	else if(strRQName == _T("���ű������ֹ����ɼ�����ȸ��û")){
		CString strData;
		CStringArray arrData;
		int nFieldCnt = 35;// sizeof(lstOPT10012) / sizeof(*lstOPT10012);		// ��üũ�� / ����ũ�� = ���Ұ���

		strRQName = _T("���ű������ֹ����ɼ�����ȸ");
		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData.Format(L"%d",nIdx);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,strData );	strData.Trim();
			if(!strData.IsEmpty()){
				//TraceOutputW(strData);
				OutputDebugString(strData);
			}
			arrData.Add(strData);
		}
	}
	if (strRQName == _T("�ֽı⺻������û"))			// ���¼��ͷ�//if (!lstrcmp(sRealType, L"�ֽ�ü��"))	// �ֽ�ü��
	{


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
void CBuyList::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	/*CString strIndex, strData;
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
	{
		return;
	}

	CString strCode;*/
	
	
	//pMain->TraceOutputW(sRealType);
	CString strIndex;
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex) || m_strRealSet.Find(sRealType) < 0 )
	{
		return;
	}

	CString strData;
	CStringArray arrData;
	if (!lstrcmp(sRealType, L"�ֽĽü�"))		// �ֽĽü�
	{
		arrData.Add(sJongmokCode);

		int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 1; i < nFieldCnt; i++)
		{
			if (_wtoi(lstOPTKWFID_B[i].strRealKey) < 0)
			{
				arrData.Add(L"");
				continue;
			}

			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
			arrData.Add(strData);
		}
		//SetDataKwanSimGrid(arrData, sRealType);
		OnUpdateListData(arrData,sRealType);
	}
	else if (!lstrcmp(sRealType, L"�ֽ�ü��"))	// �ֽ�ü��
	{
		arrData.Add(sJongmokCode);
	
		int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// ��üũ�� / ����ũ�� = ���Ұ���
		for (i = 1; i < nFieldCnt; i++)
		{
			if (_wtoi(lstOPTKWFID_B[i].strRealKey) < 0)
			{
				arrData.Add(L"");
				continue;
			}

			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
			arrData.Add(strData);
		}
		//SetDataKwanSimGrid(arrData, sRealType);
		OnUpdateListData(arrData,sRealType);
	}
// 	else if (!lstrcmp(sRealType, L"�ֽ�ȣ���ܷ�"))	// �ֽ�ü��
// 	{
// 		arrData.Add(sJongmokCode);
// 		int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// ��üũ�� / ����ũ�� = ���Ұ���
// 		for (i = 1; i < nFieldCnt; i++)
// 		{
// 			if (_wtoi(lstOPTKWFID[i].strRealKey) < 0)
// 			{
// 				arrData.Add(L"");
// 				continue;
// 			}
// 			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
// 			arrData.Add(strData);
// 		}
// 		//SetDataKwanSimGrid(arrData, sRealType);
// 		//OnUpdateListData(arrData,sRealType);
// 	}
	CshootStockDlg* pMain =  (CshootStockDlg*)AfxGetApp()->GetMainWnd();
	if(!pMain->isStockMarketOpen){ //¡�̿����� ����ü���� �ʿ� ����  ȭ���� �������ϱ� 
		if (!lstrcmp(sRealType, L"�ֽĿ���ü��"))	// �ֽ�ü��
		{
			arrData.Add(sJongmokCode);
			int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// ��üũ�� / ����ũ�� = ���Ұ���
			for (i = 1; i < nFieldCnt; i++)
			{
				if (_wtoi(lstOPTKWFID[i].strRealKey) < 0)
				{
					arrData.Add(L"");
					continue;
				}
				strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
				arrData.Add(strData);
			}
			//SetDataKwanSimGrid(arrData, sRealType);
			OnUpdateListData(arrData,sRealType);
		}
	}

};

//*******************************************************************/
//! Function Name : SetDataKwanSimGrid
//! Function      : ���� �׸��� ����Ÿ ����(������������ ����)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CBuyList::OnUpdateListData(CStringArray &arrData, CString strRealType/* = ""*/)
{
	// �����ڵ忡 �´� �� ã��

	CString strData, strTemp;
	strData = arrData.GetAt(0);
	if (!m_mapJongCode.Lookup(strData, strTemp))
	{
		return;
	}
	m_ListBox.SetRedraw(FALSE);
	// �����
	int i, nRow = _wtol(strTemp) -1, nCnt = arrData.GetSize();
 	if (strRealType == "")
 	{
 		CString strName = arrData.GetAt(1);
 		//((CStatic*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(strTemp);	// �����ڵ� �Է¶�
//  		if (strTemp == strData)
//  		{
//  			((CStatic*)GetDlgItem(IDC_STC_JONGNAME))->SetWindowText(strName);
//  		}
 		//m_grdKwanSim.SetItemText(nRow, lstOPTKWFID[1].nCol, theApp.ConvDataFormat(lstOPTKWFID[1].nDataType, strName, lstOPTKWFID[1].strBeforeData, lstOPTKWFID[1].strAfterData));
		//m_ListBox.SetItemText(nRow,lstOPTKWFID[0].nCol, theApp.ConvDataFormat(lstOPTKWFID[0].nDataType, strData, lstOPTKWFID[0].strBeforeData, lstOPTKWFID[0].strAfterData));
		m_ListBox.SetItemText(nRow, lstOPTKWFID[1].nCol, theApp.ConvDataFormat(lstOPTKWFID[1].nDataType, strName, lstOPTKWFID[1].strBeforeData, lstOPTKWFID[1].strAfterData));
 	}

	// ����Ÿ ����
	CString strTempData;
	for (i = 2; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		/////////////////////////////////////////////
		// ���� �� ������ ���� ó������������
		if (strRealType != "" && (i == 2 || i == 4 || i == 5))
		{
			strTempData = strData;
			strTempData.Replace(L"+", L"");	strTempData.Replace(L"-", L"");	strTempData.Replace(L".", L"");

			//strTemp = m_grdKwanSim.GetItemText(nRow, lstOPTKWFID[i].nCol);
			strTemp.Replace(L"%", L"");	strTemp.Replace(L"+", L"");	strTemp.Replace(L"-", L"");
			strTemp.Replace(L",", L"");	strTemp.Replace(L".", L"");
			if (strTempData != strTemp)
			{
// 				m_cellSelect.col = lstOPTKWFID[i].nCol;
// 				m_grdKwanSim.SetFocusCell(m_cellSelect);
// 				m_grdKwanSim.SetSelectedRange(nRow, m_cellSelect.col, nRow, m_cellSelect.col);
// 				m_grdKwanSim.Invalidate();
			}
		}
		// ���� �� ������ ���� ó������������
		/////////////////////////////////////////////
		if (lstOPTKWFID_B[i].bTextColor)
		{
			strTemp = arrData.GetAt(i);

			COLORREF tempC = RGB(0,0,255);

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
			if(lstOPTKWFID_B[i].nCol != -1)
				m_ListBox.SetItemTextColor(nRow,lstOPTKWFID_B[i].nCol,tempC);
			//theApp.SetDataFgColour(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strTemp);
		}
		if (lstOPTKWFID_B[i].nDataType == DT_SIGN)
		{
			//theApp.SetSignData(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strData);
		}
		else
		{
			if (strData.IsEmpty())
			{
				continue;
			}
			if(lstOPTKWFID_B[i].nCol < 2){
				OutputDebugStringA("fuck");
			}
			m_ListBox.SetItemText(nRow,lstOPTKWFID_B[i].nCol, theApp.ConvDataFormat(lstOPTKWFID_B[i].nDataType, strData, lstOPTKWFID_B[i].strBeforeData, lstOPTKWFID_B[i].strAfterData));
			//m_grdKwanSim.SetItemText(nRow, lstOPTKWFID[i].nCol, theApp.ConvDataFormat(lstOPTKWFID[i].nDataType, strData, lstOPTKWFID[i].strBeforeData, lstOPTKWFID[i].strAfterData));
		}
	}
	//m_grdKwanSim.Invalidate();
	//m_ListBox.Invalidate();
	m_ListBox.SetRedraw(true);
}


void CBuyList::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here
	// �����ڵ� �Է� ����
	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);

	CString strCode, strIndex;
	m_SearchComboList.GetWindowTextW(strCode);
	
	if (strCode.GetLength() != 6)
	{
		AfxMessageBox(L"�����ڵ� 6�ڸ� �Է� �� �ּ���~!");
		m_SearchComboList.SetFocus();
		return;
	}

	if (m_mapJongCode.Lookup(strCode, strIndex))
	{
		AfxMessageBox(L"�̹� ��� �� �����Դϴ�.");
		/*CCellID cureentCell(atoi(strIndex), 0);
		m_grdKwanSim.SetFocusCell(cureentCell);
		m_grdKwanSim.SetSelectedRange(cureentCell.row, 0, cureentCell.row, 7);*/
		m_SearchComboList.SetFocus();
		return;
	}

// 	CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
// 	int nCnt = ::GetPrivateProfileInt("JONG_CODE", "COUNT", 0,strFileName) + 1;
	int nCnt =Jongmok.GetInt(L"JONG_CODE",L"COUNT",0)+ 1;
	// �����ڵ� ���� �߰�
	strIndex.Format(L"%d", nCnt);
	//::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);
	Jongmok.WriteString(L"JONG_CODE", L"COUNT", strIndex);
	// �����ڵ� �߰�
	Jongmok.WriteString(L"JONG_CODE", strIndex, strCode);
	
	m_mapJongCode.SetAt(strCode, strIndex);

	// �� �߰�
	//m_grdKwanSim.InsertRow("", -1);
	//m_grdKwanSim.SetRowHeight(1, 20);		// ���� ���� ����
	//m_grdKwanSim.SetItemFormat(lstOPTKWFID[nCnt].nRow, lstOPTKWFID[nCnt].nCol, lstOPTKWFID[nCnt].nAlign);
	//m_grdKwanSim.SetItemText(nCnt, 0, strCode);
	int dwCount = m_ListBox.GetItemCount();

	CString strConstruction =  theApp.m_khOpenApi.GetMasterConstruction(strCode);
	CString strState =  theApp.m_khOpenApi.GetMasterStockState(strCode);
	CString strStatus = strConstruction + L"|"  + strState;
	int dwitem = m_ListBox.InsertItem(dwCount,strStatus,0);

	m_ListBox.SetItem(dwitem,1,1,strCode,0,0,0,0);

	m_ListBox.SetItemData(dwitem,(DWORD)strCode.GetBuffer());

	if(isOdd(dwitem))
		m_ListBox.SetItemBkColor(dwitem, -1, RGB(241,244,248), FALSE);

	// ���� ��ȸ ��û
	SendJongSearch(1, strCode, 5);
}


void CBuyList::OnBnClickedButtonDel()
{
	// TODO: Add your control notification handler code here
	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);
	CString strJongCode = L"";
	TCHAR strIndex[10] ={0};
	int nCnt = m_ListBox.GetItemCount();
	for(int i=0; i<m_ListBox.GetItemCount(); i++)
	{
		if( m_ListBox.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			_itow(i+1,strIndex,10);
			strJongCode = m_ListBox.GetItemText(i,1);
			//Jongmok.DeleteKey(L"JONG_CODE",strIndex);
			//AfxMessageBox(strText);
			CString strTemp;
			strTemp.Format(L"�������� [%s %s] �� ���� �ϰڽ��ϱ�?", 
				 m_ListBox.GetItemText(i,1), 
				 m_ListBox.GetItemText(i,2));
			if (MessageBox(strTemp, L"�������� ����", MB_ICONQUESTION | MB_YESNO) == IDNO)
			{
				return;
			}

			nCnt--;
			//m_grdKwanSim.DeleteRow(m_cellSelect.row);
			m_ListBox.DeleteItem(i);
			m_ListBox.Invalidate();
			m_mapJongCode.RemoveAll();
			theApp.m_khOpenApi.DisconnectRealData(m_strScrNo);
			//Jongmok.DeleteKey(L"JOMG_CODE",strIndex);
			DeleteFile(strFileIniPath);
			//m_mapJongCode.RemoveAll();

			//
			//// �����ڵ� ���� �߰�
			CString strIndex, strCode;
			strIndex.Format(L"%d", nCnt);
			//::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);
			Jongmok.WriteString(L"JONG_CODE",L"COUNT",strIndex);
			// ���� �缳��
			int i;
			for (i = 1; i <= nCnt; i++)
			{
				strIndex.Format(L"%d", i);
				strCode = m_ListBox.GetItemText(i-1, 1);

				// �����ڵ� �߰�
				//::WritePrivateProfileString("JONG_CODE", strIndex, strCode, strFileName);
				Jongmok.WriteString(L"JONG_CODE",strIndex,strCode);
				m_mapJongCode.SetAt(strCode, strIndex);
			}

			//SendJongSearch();		// ���� ��ȸ ��û
		}
	}
}


void CBuyList::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
}


void CBuyList::OnBnClickedButtonRefresh()
{
	// TODO: Add your control notification handler code here
}


BOOL CBuyList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CBuyList::OnBnClickedButtonSellall()
{
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();

	CString strRQName = _T("�ֽ��ֹ�");

	int nCount = pMain->m_OrderList.GetSize();

	CString strHavingCount = L"";
	CString strKey, strScrType;
	POSITION pos =  pMain->m_OrderList.GetStartPosition();
	while (pos != NULL)
	{
		strHavingCount= L"";
		pMain->m_OrderList.GetNextAssoc(pos, strKey, strScrType);
		if (pMain->m_OrderList.Lookup(strKey, strHavingCount) && _wtoi(strHavingCount))
		{
			 int sellCount = _wtoi(strHavingCount);
			theApp.m_khOpenApi.SendOrder(strRQName,pMain->m_strScrNo, pMain->m_AccNo, 2, strKey, sellCount, 0, L"03", L"");
		}
	}
	//CString strData =  theApp.m_khOpenApi.GetChejanData(9001);
	//CString strRQName = _T("�ֽ��ֹ�");
	//theApp.m_khOpenApi.SendOrder(strRQName,pMain->m_strScrNo, L"8100875411", 1, strJongCode, buyCount, 0, L"03", L"")
}

void CBuyList::OnBnClickedButtonTest()
{
	// TODO: Add your control notification handler code here

	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strRQName = _T("���ű������ֹ����ɼ�����ȸ��û");
	theApp.m_khOpenApi.SetInputValue(L"���¹�ȣ"	, pMain->m_AccNo);

	//��й�ȣ = ������(����)
		theApp.m_khOpenApi.SetInputValue(L"��й�ȣ"	,  L"");

	//��й�ȣ�Է¸�ü���� = 00
		theApp.m_khOpenApi.SetInputValue(L"��й�ȣ�Է¸�ü����"	,  L"2419");

	theApp.m_khOpenApi.SetInputValue(L"�����ȣ"	,  L"007370");
	theApp.m_khOpenApi.SetInputValue(L"�ż�����"	,  L"7230");

	long ret =  theApp.m_khOpenApi.CommRqData(strRQName,L"OPW00011",0,m_strScrNo);
	theApp.IsError(ret);
}

void CBuyList::OnBnClickedOrder1()
{
	// TODO: Add your control notification handler code here
	// �Ÿű��� ���(1:�űԸż�, 2:�űԸŵ� 3:�ż����, 4:�ŵ����, 5:�ż�����, 6:�ŵ�����)
	// �ŷ����� ���
	// 0:������, 3:���尡, 5:���Ǻ�������, 6:������������, 7:�ֿ켱������, 
	// 10:������IOC, 13:���尡IOC, 16:������IOC, 20:������FOK, 23:���尡FOK, 
	// 26:������FOK, 61:�尳�����ð���, 62:�ð��ܴ��ϰ��Ÿ�, 81:���Ľð�������
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strJongCode = L"";
	CString nowPrice = L"";
	for(int i=0; i<m_ListBox.GetItemCount(); i++)
	{
		if( m_ListBox.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			strJongCode = m_ListBox.GetItemText(i,1);
			nowPrice = m_ListBox.GetItemText(i,3);
			
			//AfxMessageBox(strText);
		}
	}
	if(!theApp.g_MyMoney){
		AfxMessageBox(L"you have no money or not input the password dammit! fuck!");
		return;
	}
	CString strRQName = _T("�ֽ��ֹ�");
	long lRet;
	nowPrice.Replace(L",",L"");
	int buyCount = theApp.g_MyMoney / _wtoi(nowPrice) -1;
	//pMain->m_boughtCount = buyCount;



	//pMain->m_checkedSubject.SetAt(strJongCode,)

	CString fmt;
	fmt.Format(L"�ֽ����� %s ,�ֽİ��ɼ� %d, �ֽ� ���簡 %s",strJongCode,buyCount,nowPrice);
	pMain->TraceOutputW(fmt);
	CSubject * subject =new CSubject;
	subject->set_total(buyCount);
	pMain->m_checkedSubject.SetAt(strJongCode,subject);
	lRet = theApp.m_khOpenApi.SendOrder(strRQName, pMain->m_strScrNo,pMain->m_AccNo, 1, strJongCode, buyCount, 0, L"03", L"");
}


void CBuyList::OnBnClickedOrder2()
{
	// TODO: Add your control notification handler code here
}


void CBuyList::OnBnClickedOrder3()
{
	// TODO: Add your control notification handler code here
}


void CBuyList::OnBnClickedButtonAdd(CString t_strCode)
{
	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);

	CString strCode = t_strCode, strIndex;
	
	
	if (strCode.GetLength() != 6)
	{
		AfxMessageBox(L"�����ڵ� 6�ڸ� �Է� �� �ּ���~!");
		m_SearchComboList.SetFocus();
		return;
	}

	if (m_mapJongCode.Lookup(strCode, strIndex))
	{
		AfxMessageBox(L"�̹� ��� �� �����Դϴ�.");
		/*CCellID cureentCell(atoi(strIndex), 0);
		m_grdKwanSim.SetFocusCell(cureentCell);
		m_grdKwanSim.SetSelectedRange(cureentCell.row, 0, cureentCell.row, 7);*/
		m_SearchComboList.SetFocus();
		return;
	}

// 	CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
// 	int nCnt = ::GetPrivateProfileInt("JONG_CODE", "COUNT", 0,strFileName) + 1;
	int nCnt =Jongmok.GetInt(L"JONG_CODE",L"COUNT",0)+ 1;
	// �����ڵ� ���� �߰�
	strIndex.Format(L"%d", nCnt);
	//::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);
	Jongmok.WriteString(L"JONG_CODE", L"COUNT", strIndex);
	// �����ڵ� �߰�
	Jongmok.WriteString(L"JONG_CODE", strIndex, strCode);
	
	m_mapJongCode.SetAt(strCode, strIndex);


	int dwCount = m_ListBox.GetItemCount();

	CString strConstruction =  theApp.m_khOpenApi.GetMasterConstruction(strCode);
	CString strState =  theApp.m_khOpenApi.GetMasterStockState(strCode);
	CString strStatus = strConstruction + L"|"  + strState;
	int dwitem = m_ListBox.InsertItem(dwCount,strStatus,0);

	m_ListBox.SetItem(dwitem,1,1,strCode,0,0,0,0);

	m_ListBox.SetItemData(dwitem,(DWORD)strCode.GetBuffer());

	if(isOdd(dwitem))
		m_ListBox.SetItemBkColor(dwitem, -1, RGB(241,244,248), FALSE);

	// ���� ��ȸ ��û
	SendJongSearch(1, strCode, 5);
}









void CBuyList::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strJongCode = L"";
	CString nowPrice = L"";
	for(int i=0; i<m_ListBox.GetItemCount(); i++)
	{
		if( m_ListBox.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			strJongCode = m_ListBox.GetItemText(i,1);
			pMain->m_boardJongmokCode = strJongCode;
			theApp.m_khOpenApi.SetInputValue(L"�����ڵ�",strJongCode);
			theApp.m_khOpenApi.CommRqData(L"�ֽı⺻������û",L"OPT10001",0,pMain->m_strScrNo);
		}
	}

	*pResult = 0;
}


void CBuyList::OnBnClickedButtonChatview()
{
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	if (!pMain->GetNextScreenNum(5))
	{
		return;
	}
	
	CChartView *pChartView = new CChartView(this);
	pChartView->m_strScrNo.Format(_T("%04d"), pMain->m_nScrN0);
	pChartView->Create(IDD_DIALOG_CHART);

	pMain->m_mapScreen.SetAt(pChartView->m_strScrNo, pChartView);
	pChartView->SendSearch();
}


void CBuyList::OnBnClickedButtonAllCancel()
{
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();

	CString strRQName = _T("�ֽ��ֹ�");

	int nCount = pMain->m_mapOrderNo.GetSize();

	CString strOrderNo = L"";
	CString strKey, strScrType;
	POSITION pos =  pMain->m_mapOrderNo.GetStartPosition();
	while (pos != NULL)
	{
		strOrderNo= L"";
		pMain->m_mapOrderNo.GetNextAssoc(pos, strKey, strScrType);
		if (pMain->m_mapOrderNo.Lookup(strKey, strOrderNo))
		{
			theApp.m_khOpenApi.SendOrder(strRQName,pMain->m_strScrNo, pMain->m_AccNo, 4, strKey, 0, 0, L"00",strOrderNo);
			pMain->isManual = true;
		}
	}
}
