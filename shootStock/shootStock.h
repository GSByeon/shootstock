
// shootStock.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once
#include "khopenapictrl.h"
#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

#define OP_ERR_SISE_OVERFLOW	-200			//"�ü���ȸ ������"
#define OP_ERR_RQ_STRUCT_FAIL	-201			//"REQUEST_INPUT_st Failed"
#define OP_ERR_RQ_STRING_FAIL	-202			//"��û ���� �ۼ� ����"
#define OP_ERR_NO_DATA			-203			//"�����Ͱ� �������� �ʽ��ϴ�."
#define OP_ERR_OVER_MAX_DATA	-204			//"�ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�."


#define OP_ERR_ORD_WRONG_INPUT	-300			//"�Է°� ����"
#define OP_ERR_ORD_WRONG_ACCNO	-301			//"���º�й�ȣ�� �Է��Ͻʽÿ�."
#define OP_ERR_OTHER_ACC_USE	-302			//"Ÿ�ΰ��´� ����� �� �����ϴ�."
#define OP_ERR_MIS_2BILL_EXC	-303			//"�ֹ������� 20����� �ʰ��մϴ�."
#define OP_ERR_MIS_5BILL_EXC	-304			//"�ֹ������� 50����� �ʰ��մϴ�."
#define OP_ERR_MIS_1PER_EXC		-305			//"�ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�."
#define OP_ERR_MIS_3PER_EXC		-306			//"�ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�."
#define OP_ERR_SEND_FAIL		-307			//"�ֹ����۽���"
#define OP_ERR_ORD_OVERFLOW		-308			//"�ֹ����� ������"

#define UM_SCRENN_CLOSE		1000


#define TR_OPT10001		_T("OPT10001")
#define TR_OPT10003		_T("OPT10003")
#define TR_OPT10004		_T("OPT10004")
#define TR_OPT10080		_T("OPT10080")
#define TR_OPT10081		_T("OPT10081")
#define TR_OPT10015		_T("OPT10015")

#define TR_OPT10027		_T("OPT10027")
#define TR_OPT10086		_T("OPT10086")

#define TR_OPW00001     _T("OPW00001")
#define TR_OPW00013     _T("OPW00013")

#define DT_NONE			0		// �⺻���� ����
#define DT_DATE			1		// ���� ����
#define DT_TIME			2		// �ð� ����
#define DT_NUMBER		3		// ���� ���� ����
#define DT_ZERO_NUMBER	4		// ���� ����(0ǥ��) ����
#define DT_SIGN			5		// ����ȣ ����
#define DT_SIGN_NUMBER  6
#define DT_UNSIGN_NUMBER 7

typedef struct
{
	CString	strKey;				// ��ȸ Ű
	CString	strRealKey;			// ���� Ű
	int		nRow;				// �׸��� ��
	int		nCol;				// �׸��� ��
	int		nDataType;			// ����Ÿ Ÿ��(0:�⺻����, 1:����, 2:�ð�, 3:���� ����, 4:���� ����(0ǥ��), 5:����ȣ)
	BOOL		bTextColor;			// ���ڿ� �� ����(���, �϶���)
	UINT		nAlign;				// ���ڿ� ����(DT_LEFT, DT_CENTER, DT_RIGHT)
	CString	strBeforeData;		// ���ڿ� �� ���� �ֱ�
	CString	strAfterData;		// ���ڿ� �� ���� �ֱ�
} stGRID;


// CshootStockApp:
// �� Ŭ������ ������ ���ؼ��� shootStock.cpp�� �����Ͻʽÿ�.
//
extern CString QueryExePath();
extern BOOL isOdd(UINT x);
class CshootStockApp : public CWinApp
{
public:
	CshootStockApp();
	CKhopenapictrl m_khOpenApi;
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	BOOL IsError(long lErrCode);		// ���� ����
	CString ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData = L"", LPCTSTR szAfterData = L"");
	CString removeSign(LPCTSTR szData);
	DECLARE_MESSAGE_MAP()
public:
	int g_MyMoney;
	bool g_is_password_success;
};

extern CshootStockApp theApp;