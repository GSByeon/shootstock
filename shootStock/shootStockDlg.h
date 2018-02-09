
// shootStockDlg.h : ��� ����
//

#pragma once

#include "afxcmn.h"

#include "BuyList.h"
#include "CurPrice.h"
#include "TopPrice.h"
#include "JongDlg.h"
#include "DailyReport.h"
#include "ChartView.h"

#define WM_UPDATESTATUSBAR WM_USER + 255

// CshootStockDlg ��ȭ ����
class CshootStockDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CshootStockDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHOOTSTOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
public:
	CMapStringToPtr m_mapScreen;
	CMapStringToString m_OrderList;
	CString							m_strScrNo;
	CMapStringToString		m_mapJongCode;		// ������ ����
	CMapStringToString		m_mapOrderNo;
	int m_nScrN0;
	CMapStringToString m_mapScreenNum;
	long								m_nCount;					// �׸��� Row ����.
	BOOL							m_bNextFlag;				// ������ȸ ���� �÷���.

	CString							m_AccNo;

	double							m_BuyComm;			// �ż������ ������(���)
	double							m_SellComm;			// �ŵ������ ������(���)
	double							m_Tax;						// ������(���)
	double							m_Eval;						// �򰡱ݾ�(����, �ſ�/����)
	double							m_Profit;					// �򰡼���(����, �ſ�/����)
	double							m_Rate;						// ���ͷ�


	BOOL GetNextScreenNum(int nScreenType);
	long		m_nRet;
// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void MainOnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void MainOnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void MainOnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);
	void OnEventConnect(LONG nItemCnt);
	void OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex);			//���ǰ˻� �ǽð� ����,�����Ǵ� ������ �޴´�
	void OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext);	//���ǰ˻� ���񸮽�Ʈ�� �޴´�.
	void OnReceiveConditionVer(long lRet, LPCTSTR sMsg);
	DECLARE_EVENTSINK_MAP()
public:
	
protected:
	afx_msg LRESULT OnUpdatestatusbar(WPARAM wParam, LPARAM lParam);
public:
	CBuyList m_buyList;
	CCurPrice m_curPrice;
	CTopPrice m_topPrice;
	CJongDlg  m_JongDlg;
	CDailyReport m_DailyReport;
	CChartView m_ChartView;
	CStatusBar m_StatusBar;
	void InitStatusBar(void);
	void OnBtnGetAccData(void);
	CListCtrl m_logList;
	void InitlogList(void);
	void TraceOutputA(const char* fmt,...);
	void TraceOutputW(const TCHAR* fmt,...);
	CTabCtrl m_TabControl;
	void InitTabControl(void);
	afx_msg void OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	CReportCtrl m_dealList;
	void InitDealList(void);
	void SetRate(int nRow, CString strCode);
	void SetTotalRate();

	afx_msg void OnListSearch();
	CString m_staticCode;
	CString m_staticName;
	CString m_staticPrice;
	CString m_boardJongmokCode;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	float m_sellPercentage;
	int m_FuckPercentage;
	bool isRunning;
	// �ż� ü�ᰡ
	int m_boughtPrice;
	// ü��� ����
	int m_checkedCount;
	CString m_checkedCode;
	int m_boughtCount;
};
