
// shootStock.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "shootStock.h"
#include "shootStockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CshootStockApp

BEGIN_MESSAGE_MAP(CshootStockApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CshootStockApp ����

CshootStockApp::CshootStockApp()
	: g_MyMoney(500000)
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CshootStockApp ��ü�Դϴ�.

CshootStockApp theApp;

CString QueryExePath()
{
	TCHAR path[MAX_PATH];
	::GetModuleFileName(NULL,path,MAX_PATH);
	CString p(path);
	CString subp;
	int nPos = p.ReverseFind('\\');
	//ASSERT(-1!=nPos);
	return p.Left(nPos+1);
}
// CshootStockApp �ʱ�ȭ
BOOL isOdd(UINT x)
{
	if((x % 2) == 0) return TRUE;
	return FALSE;
}
BOOL CshootStockApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));



	CshootStockDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}


//*******************************************************************/
//! Function Name : IsError
//! Function      : ���� ����
//! Param         : long lErrCode
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CshootStockApp::IsError(long lErrCode)
{
	CString strMsg = _T("");
	switch (lErrCode)
	{
		////////////////////////////
		// �Ϲ� ��ȸ ���� ó��
	case OP_ERR_SISE_OVERFLOW:		// �ü���ȸ ������
		strMsg = "�ü���ȸ ������";
		break;
	case OP_ERR_RQ_STRUCT_FAIL:		// REQUEST_INPUT_st Failed
		strMsg = "REQUEST_INPUT_st Failed";
		break;
	case OP_ERR_RQ_STRING_FAIL:		// ��û ���� �ۼ� ����
		strMsg = "��û ���� �ۼ� ����";
		break;
	case OP_ERR_NO_DATA:			// �����Ͱ� �������� �ʽ��ϴ�.
		strMsg = "�����Ͱ� �������� �ʽ��ϴ�.";
		break;

		////////////////////////////
		// ���� ���� ��ȸ ���� ó��
	case OP_ERR_OVER_MAX_DATA:			// �ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�.
		strMsg = "�ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�.";
		break;

		////////////////////////////
		// �ֹ� ���� ó��
	case OP_ERR_ORD_WRONG_INPUT:		// �Է°� ����
		strMsg = "�Է°� ����";
		break;
	case OP_ERR_ORD_WRONG_ACCNO:		// ���º�й�ȣ�� �Է��Ͻʽÿ�.
		strMsg = "���º�й�ȣ�� �Է��Ͻʽÿ�.";
		break;
	case OP_ERR_OTHER_ACC_USE:			// Ÿ�ΰ��´� ����� �� �����ϴ�.
		strMsg = "Ÿ�ΰ��´� ����� �� �����ϴ�.";
		break;
	case OP_ERR_MIS_2BILL_EXC:			// �ֹ������� 20����� �ʰ��մϴ�.
		strMsg = "�ֹ������� 20����� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_5BILL_EXC:			// �ֹ������� 50����� �ʰ��մϴ�.
		strMsg = "�ֹ������� 50����� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_1PER_EXC:			// �ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�.
		strMsg = "�ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_3PER_EXC:			// �ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�.
		strMsg = "�ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�.";
		break;
	case OP_ERR_SEND_FAIL:				// �ֹ����۽���
		strMsg = "�ֹ����ۿ� �����Ͽ����ϴ�..";
		break;
	case OP_ERR_ORD_OVERFLOW:			// �ֹ����� ������
		strMsg = "�ֹ����� ������ �Դϴ�. ��� �� �ٽ� �ֹ��Ͽ� �ּ���.";
		break;
	}

	// ���� �޼��� ó��
	if (!strMsg.IsEmpty())
	{
		AfxMessageBox(strMsg);
		return FALSE;
	}

	return TRUE;
}

//*******************************************************************/
//! Function Name : ConvDataFormat
//! Function      : ���ڿ� ���� ����
//! Param         : int nType, LPCTSTR szData, LPCTSTR szBeforeData/* = ""*/, LPCTSTR szAfterData/* = ""*/
//! Return        : CString
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
CString CshootStockApp::ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData/* = ""*/, LPCTSTR szAfterData/* = ""*/)
{
	CString strReturn, strData, strTemp = strData = szData;
	switch (nType)
	{
	case DT_DATE:			// ����
		{
			if (strTemp.GetLength() == 6)
			{
				strData.Format(L"%02s/%02s/%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
			}
			else if (strTemp.GetLength() == 8)
			{
				strData.Format(L"%04s/%02s/%02s", strTemp.Left(4), strTemp.Mid(4, 2), strTemp.Right(2));
			}
		}
		break;
	case DT_TIME:			// �ð�
		{
			if (strTemp.GetLength() == 6)
			{
				strData.Format(L"%02s:%02s:%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
			}
			else if (strTemp.GetLength() == 8)
			{
				strData.Format(L"%02s:%02s:%02s:%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Mid(4, 2), strTemp.Right(2));
			}
		}
		break;
	case DT_NUMBER:			// ����
		break;
	case DT_ZERO_NUMBER:	// ����(0ǥ��)
		{
			strTemp.Replace(L"+", L"");
			strTemp.Replace(L"-", L"");
			if (_wtof(strTemp) == 0.00)
			{
				strData = nType == DT_ZERO_NUMBER ? strTemp : L"";
				break;
			}

			int nFind = strTemp.Find(L".");
			if (nFind < 0)
			{
				strData = strTemp;
			}
			else
			{
				strData = strTemp.Left(nFind);
				strTemp = strTemp.Mid(nFind);
			}

			TCHAR szFormatData[1024] = {0,};
			NUMBERFMT fmt={0, 0, 3, _T("."), _T(","), 1};
			::GetNumberFormat(NULL, 0, strData, &fmt, szFormatData, 1024);

			if (nFind < 0)
			{
				nType == DT_ZERO_NUMBER ? strData.Format(L"%01s", szFormatData) : strData.Format(L"%s", szFormatData);
			}
			else
			{
				strData.Format(L"%01s%s", szFormatData, strTemp);
			}
		}
		break;
	}

	strReturn.Format(L"%s%s%s", szBeforeData, strData, szAfterData);

	return strReturn;
}