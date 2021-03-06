
// shootStock.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "shootStock.h"
#include "shootStockDlg.h"
#include <strsafe.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define OUTPUT_BUFF_LEN 51200 


void DbgStrOutW(const wchar_t *fmt, ...)
{
	wchar_t szOutStr[OUTPUT_BUFF_LEN];

	va_list ap;
	va_start(ap, fmt);
	StringCbVPrintfW(szOutStr, OUTPUT_BUFF_LEN, fmt, ap);
	va_end(ap);
	//LOG(INFO) << szOutStr;




	HWND hWnd = FindWindowA(NULL, "Trace");
	if (hWnd)
	{
		COPYDATASTRUCT pCopy;
		memset(&pCopy, 0, sizeof(COPYDATASTRUCT));
		pCopy.cbData = 51200;
		pCopy.lpData = szOutStr;
		pCopy.dwData = 1;
		SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&pCopy);
	}

	//OutputDebugString(szOutStr);
}

void DbgStrOutA(const char *fmt, ...)
{
	char szOutStr[OUTPUT_BUFF_LEN];
	va_list ap;
	va_start(ap, fmt);
	StringCbVPrintfA(szOutStr, OUTPUT_BUFF_LEN, fmt, ap);
	va_end(ap);


	//LOG(INFO) << szOutStr;
	HWND hWnd = FindWindowA(NULL, "Trace");
	if (hWnd)
	{
		COPYDATASTRUCT pCopy;
		memset(&pCopy, 0, sizeof(COPYDATASTRUCT));
		pCopy.cbData = strlen(szOutStr) + 1;
		pCopy.lpData = szOutStr;
		pCopy.dwData = 0;
		SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&pCopy);
	}
	//OutputDebugStringA(szOutStr);
}

// CshootStockApp

BEGIN_MESSAGE_MAP(CshootStockApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CshootStockApp 생성

CshootStockApp::CshootStockApp()
	: g_MyMoney(400000)
	, g_is_password_success(false)
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CshootStockApp 개체입니다.

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
// CshootStockApp 초기화
BOOL isOdd(UINT x)
{
	if((x % 2) == 0) return TRUE;
	return FALSE;
}
BOOL CshootStockApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));



	CshootStockDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}


//*******************************************************************/
//! Function Name : IsError
//! Function      : 오류 여부
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
		// 일반 조회 오류 처리
	case OP_ERR_SISE_OVERFLOW:		// 시세조회 과부하
		strMsg = "시세조회 과부하";
		break;
	case OP_ERR_RQ_STRUCT_FAIL:		// REQUEST_INPUT_st Failed
		strMsg = "REQUEST_INPUT_st Failed";
		break;
	case OP_ERR_RQ_STRING_FAIL:		// 요청 전문 작성 실패
		strMsg = "요청 전문 작성 실패";
		break;
	case OP_ERR_NO_DATA:			// 데이터가 존재하지 않습니다.
		strMsg = "데이터가 존재하지 않습니다.";
		break;

		////////////////////////////
		// 복수 종목 조회 오류 처리
	case OP_ERR_OVER_MAX_DATA:			// 한번에 조회 가능한 종목개수는 최대 100종목 입니다.
		strMsg = "한번에 조회 가능한 종목개수는 최대 100종목 입니다.";
		break;

		////////////////////////////
		// 주문 오류 처리
	case OP_ERR_ORD_WRONG_INPUT:		// 입력값 오류
		strMsg = "입력값 오류";
		break;
	case OP_ERR_ORD_WRONG_ACCNO:		// 계좌비밀번호를 입력하십시오.
		strMsg = "계좌비밀번호를 입력하십시오.";
		break;
	case OP_ERR_OTHER_ACC_USE:			// 타인계좌는 사용할 수 없습니다.
		strMsg = "타인계좌는 사용할 수 없습니다.";
		break;
	case OP_ERR_MIS_2BILL_EXC:			// 주문가격이 20억원을 초과합니다.
		strMsg = "주문가격이 20억원을 초과합니다.";
		break;
	case OP_ERR_MIS_5BILL_EXC:			// 주문가격이 50억원을 초과합니다.
		strMsg = "주문가격이 50억원을 초과합니다.";
		break;
	case OP_ERR_MIS_1PER_EXC:			// 주문수량이 총발행주수의 1%를 초과합니다.
		strMsg = "주문수량이 총발행주수의 1%를 초과합니다.";
		break;
	case OP_ERR_MIS_3PER_EXC:			// 주문수량은 총발행주수의 3%를 초과할 수 없습니다.
		strMsg = "주문수량은 총발행주수의 3%를 초과할 수 없습니다.";
		break;
	case OP_ERR_SEND_FAIL:				// 주문전송실패
		strMsg = "주문전송에 실패하였습니다..";
		break;
	case OP_ERR_ORD_OVERFLOW:			// 주문전송 과부하
		strMsg = "주문전송 과부하 입니다. 잠시 후 다시 주문하여 주세요.";
		break;
	}

	// 에러 메세지 처리
	if (!strMsg.IsEmpty())
	{
		AfxMessageBox(strMsg);
		return FALSE;
	}

	return TRUE;
}
CString CshootStockApp::removeSign(LPCTSTR szData){
	CString strTmp = szData;
	strTmp.Remove('+');
	strTmp.Remove('-');
	return strTmp;
}
//*******************************************************************/
//! Function Name : ConvDataFormat
//! Function      : 문자열 포멧 설정
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
	case DT_DATE:			// 일자
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
	case DT_TIME:			// 시간
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
	case DT_NUMBER:			// 부호가 보류 있는 숫자
		break;
	case DT_ZERO_NUMBER:	// 숫자(0표시)
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