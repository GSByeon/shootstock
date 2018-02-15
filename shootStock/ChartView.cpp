﻿// ChartView.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "ChartView.h"
#include "afxdialogex.h"
#include "chartdir.h"
#include "FinanceChart.h"
#include <math.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <strsafe.h>
#include "shootStockDlg.h"
// CChartView dialog
#define OUTPUT_BUFF_LEN 51200 
static int nrst = 0;
void DbgStrOutW(const wchar_t *fmt, ...)
{
	wchar_t szOutStr[OUTPUT_BUFF_LEN];

	va_list ap;
	va_start(ap, fmt);
	StringCbVPrintfW(szOutStr, OUTPUT_BUFF_LEN, fmt, ap);
	va_end(ap);


	OutputDebugString(szOutStr);
}

void DbgStrOutA(const char *fmt, ...)
{
	char szOutStr[OUTPUT_BUFF_LEN];
	va_list ap;
	va_start(ap, fmt);
	StringCbVPrintfA(szOutStr, OUTPUT_BUFF_LEN, fmt, ap);
	va_end(ap);


	//g_logger.puts(JsCPPUtils::Logger::LOGTYPE_INFO, szOutStr);
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

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPT10081[] = 
{
	{L"종목코드",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"현재가",				L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"거래량",				L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"거래대금",			L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"일자",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"시가",				L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"고가",				L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"저가",				L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"수정주가구분",		L"-1",	0,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"수정비율",			L"-1",	0,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"대업종구분",			L"-1",	0,	8,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"소업종구분",			L"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" 원"}, 
	{L"종목정보",			L"-1",	0,	10,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" 억"}, 
	{L"수정주가이벤트",		L"-1",	0,	11,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"전일종가",			L"-1",	1,	12,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 

};

IMPLEMENT_DYNAMIC(CChartView, CDialogEx)

CChartView::CChartView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChartView::IDD, pParent)
{

}

CChartView::~CChartView()
{
}

void CChartView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_VIEWER, m_ChartViewer);
	DDX_Control(pDX, IDC_VIEW_PORT_CTRL, m_ViewPortControl);
}


BEGIN_MESSAGE_MAP(CChartView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CChartView::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CChartView::OnBnClickedButtonAdd)
	 ON_CONTROL(CVN_MouseMovePlotArea, IDC_CHART_VIEWER, OnMouseMovePlotArea)
	  ON_CONTROL(CVN_ViewPortChanged, IDC_CHART_VIEWER, OnViewPortChanged)
END_MESSAGE_MAP()


// CChartView message handlers
//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CChartView::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("주식일봉차트조회요청"))			// 관심종목정보 설정
	{
		CString strData;
		CStringArray arrData;
		
		
		int nFieldCnt = sizeof(lstOPT10081) / sizeof(*lstOPT10081);		// 전체크기 / 원소크기 = 원소개수
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 
		// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("주식일봉차트");

		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"종목코드");	strData.Trim();
		if(strData.IsEmpty()){
			return; //종목코드가 비여있으면 차트데이터도 비여있음
		}
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		//nCnt = 150;
		double * open = new double[nCnt];
		double * high = new double[nCnt];
		double * low = new double[nCnt];
		double * close = new double[nCnt];
		double * vol = new double[nCnt];
		double * time = new double[nCnt];
		//double open[nCnt],high[nCnt],low[nCnt],close[nCnt],vol[nCnt];
		for (i = 0; i <= nCnt; i++)
		{
			int k = nCnt - i -1;
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10081[j].strKey);	strData.Trim();
				if(j == 2)
					vol[k] = _wtof(strData);
				if(j == 4){
					int y = _wtoi(strData.Mid(0,4));
					int m = _wtoi(strData.Mid(4,2));
					int d = _wtoi(strData.Mid(6,2));
					//DbgStrOutA("%d,%d,%d,%0.2f,k=%d",y,m,d,Chart::chartTime(y,m,d),k);
					time[k] = Chart::chartTime(y,m,d);
				}
					
				if(j == 5)
					open[k] = _wtof(strData);
				if(j == 6)
					high[k] = _wtof(strData);
				if(j == 7)
					low[k] = _wtof(strData);
				if(j == 1)
					close[k] = _wtof(strData);
 			}
		}
		nCnt-=1;
		DoubleArray t_vol(vol,nCnt);
		DoubleArray t_open(open,nCnt);
		DoubleArray t_high(high,nCnt);
		DoubleArray t_low(low,nCnt);
		DoubleArray t_close(close,nCnt);
		DoubleArray t_time(time,nCnt);
		//CChartView * viewer = m_ChartViewer;
		m_timeStamps = t_time;
		m_openData = t_open;
		m_highData = t_high;
		m_lowData = t_low;
		m_closeData = t_close;
		m_volData = t_vol;
		// Set the full x range to be the duration of the data
		//DbgStrOutA("t_time.len = %d",t_time.len);
		m_ChartViewer.setFullRange("x", t_time[0], t_time[t_time.len]+1);

		// Initialize the view port to show the latest 20% of the time range
		m_ChartViewer.setViewPortWidth(0.2);
		
		m_ChartViewer.setViewPortLeft(1 - m_ChartViewer.getViewPortWidth());

		// Set the maximum zoom to 10 points
		m_ChartViewer.setZoomInWidthLimit(10.0 / t_time.len);

		// Initially set the mouse to drag to scroll mode.
		//m_PointerPB.SetCheck(1);
		m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);

		// Enable mouse wheel zooming by setting the zoom ratio to 1.1 per wheel event
		//m_ChartViewer.setMouseWheelZoomRatio(1.1);
		m_ChartViewer.updateViewPort(true, true);

 		CRect r;
 		GetWindowRect(&r);
 
 		FinanceChart *c = new FinanceChart(r.Width()-50);
 		// Create an XYChart object of size 640 x 70 pixels   
 		// Disable default legend box, as we are using dynamic legend
 		c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);
 
 		// Set the data into the finance chart object
 		c->setData(m_timeStamps, m_highData, m_lowData, m_openData, m_closeData, m_volData, 30);
 
 		// Add the main chart with 240 pixels in height
 		c->addMainChart(70);
 
 		// Add candlestick symbols to the main chart, using green/red for up/down days
 		c->addCandleStick(0x00ff00, 0xff0000);

		 //Output the chart
		m_ViewPortControl.setChart(c);
		// Output the chart
		
		 m_ViewPortControl.setViewer(&m_ChartViewer);
	}
}
//*******************************************************************/
//! Function Name	: OnReceiveRealDataKhopenapictrl
//! Function			: 실시간 처리
//! Param				: LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CChartView::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

BOOL CChartView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	ShowWindow(SW_SHOW);
	// drawChart(&m_ChartViewer);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in or 
// out the chart by dragging or clicking on the chart. It can also be triggered by calling
// CChartViewer.updateViewPort.
//
void CChartView::OnViewPortChanged()
{
	// Update the chart if necessary
	if (m_ChartViewer.needUpdateChart())
		drawChart(&m_ChartViewer);
}
/////////////////////////////////////////////////////////////////////////////
// Data source

/// <summary>
/// Get the timeStamps, highData, lowData, openData, closeData and volData.
/// </summary>
/// <param name="ticker">The ticker symbol for the data series.</param>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
/// <param name="durationInDays">The number of trading days to get.</param>
/// <param name="extraPoints">The extra leading data points needed in order to
/// compute moving averages.</param>
/// <returns>True if successfully obtain the data, otherwise false.</returns>
bool CChartView::getData(const CString &ticker, double startDate,
	double endDate, int durationInDays, int extraPoints)
{
	// This method should return false if the ticker symbol is invalid. In this
	// sample code, as we are using a random number generator for the data, all
	// ticker symbol is allowed, but we still assumed an empty symbol is invalid.
	//if (ticker.IsEmpty())
	//	return false;

	//// In this demo, we can get 15 min, daily, weekly or monthly data depending on
	//// the time range.
	//m_resolution = 86400;
	//if (durationInDays <= 10) 
	//{
	//	// 10 days or less, we assume 15 minute data points are available
	//	m_resolution = 900;

	//	// We need to adjust the startDate backwards for the extraPoints. We assume 
	//	// 6.5 hours trading time per day, and 5 trading days per week.
	//	double dataPointsPerDay = 6.5 * 3600 / m_resolution;
	//	double adjustedStartDate = startDate - fmod(startDate, 86400) - 
	//		(int)(extraPoints / dataPointsPerDay * 7 / 5 + 2.9999999) * 86400;

	//	// Get the required 15 min data
	//	get15MinData(ticker, adjustedStartDate, endDate);
	//}
	//else if (durationInDays >= 4.5 * 360)
	//{
	//	// 4 years or more - use monthly data points.
	//	m_resolution = 30 * 86400;

	//	// Adjust startDate backwards to cater for extraPoints
	//	int YMD = Chart::getChartYMD(startDate);
	//	int adjustedMonth = (YMD / 100) % 100 - extraPoints;
	//	int adjustedYear = YMD / 10000;
	//	while (adjustedMonth < 1)
	//	{
	//		--adjustedYear;
	//		adjustedMonth += 12;
	//	}
	//	double adjustedStartDate = Chart::chartTime(adjustedYear, adjustedMonth, 1);

	//	// Get the required monthly data
	//	getMonthlyData(ticker, adjustedStartDate, endDate);
	//}
	//else if (durationInDays >= 1.5 * 360)
	//{
	//	// 1 year or more - use weekly points. 
	//	m_resolution = 7 * 86400;

	//	//Note that we need to add extra points by shifting the starting weeks backwards
	//	double adjustedStartDate = startDate - (extraPoints * 7 + 6) * 86400;

	//	// Get the required weekly data
	//	getWeeklyData(ticker, adjustedStartDate, endDate);
	//}
	//else
	{
		// Default - use daily points
		m_resolution = 86400;

		// Adjust startDate backwards to cater for extraPoints. We multiply the days 
		// by 7/5 as we assume 1 week has 5 trading days.
		double adjustedStartDate = startDate - fmod(startDate, 86400) - 
			((extraPoints * 7 + 4) / 5 + 2) * 86400;

		// Get the required daily data
		getDailyData(ticker, adjustedStartDate, endDate);
	}

	return true;
}

/// <summary>
/// Get 15 minutes data series into the timeStamps, highData, lowData, openData, closeData 
/// and volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::get15MinData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. If you do not have 15 
	// minute data, you may modify the "drawChart" method below to not using 15 minute
	// data.
	//
//	generateRandomData(ticker, startDate, endDate, 900);
}

/// <summary>
/// Get daily data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::getDailyData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. Replace the code below
	// with your own data acquisition code.
	//

//	generateRandomData(ticker, startDate, endDate, 86400);
}


/// <summary>
/// Add an indicator chart to the FinanceChart object. In this demo example, the indicator
/// parameters (such as the period used to compute RSI, colors of the lines, etc.) are hard
/// coded to commonly used values. You are welcome to design a more complex user interface 
/// to allow users to set the parameters.
/// </summary>
/// <param name="m">The FinanceChart object to add the line to.</param>
/// <param name="indicator">The selected indicator.</param>
/// <param name="height">Height of the chart in pixels</param>
static XYChart* addIndicator(FinanceChart *m, CString indicator, int height)
{
	if (indicator == _T("RSI"))
		return m->addRSI(height, 14, 0x800080, 20, 0xff6666, 0x6666ff);
	else if (indicator == _T("StochRSI"))
		return m->addStochRSI(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
	else if (indicator == _T("MACD"))
		return m->addMACD(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
	else if (indicator == _T("FStoch"))
		return m->addFastStochastic(height, 14, 3, 0x6060, 0x606000);
	else if (indicator == _T("SStoch"))
		return m->addSlowStochastic(height, 14, 3, 0x6060, 0x606000);
	else if (indicator == _T("ATR"))
		return m->addATR(height, 14, 0x808080, 0xff);
	else if (indicator == _T("ADX"))
		return m->addADX(height, 14, 0x8000, 0x800000, 0x80);
	else if (indicator == _T("DCW"))
		return m->addDonchianWidth(height, 20, 0xff);
	else if (indicator == _T("BBW"))
		return m->addBollingerWidth(height, 20, 2, 0xff);
	else if (indicator == _T("DPO"))
		return m->addDPO(height, 20, 0xff);
	else if (indicator == _T("PVT"))
		return m->addPVT(height, 0xff);
	else if (indicator == _T("Momentum"))
		return m->addMomentum(height, 12, 0xff);
	else if (indicator == _T("Performance"))
		return m->addPerformance(height, 0xff);
	else if (indicator == _T("ROC"))
		return m->addROC(height, 12, 0xff);
	else if (indicator == _T("OBV"))
		return m->addOBV(height, 0xff);
	else if (indicator == _T("AccDist"))
		return m->addAccDist(height, 0xff);
	else if (indicator == _T("CLV"))
		return m->addCLV(height, 0xff);
	else if (indicator == _T("WilliamR"))
		return m->addWilliamR(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
	else if (indicator == _T("Aroon"))
		return m->addAroon(height, 14, 0x339933, 0x333399);
	else if (indicator == _T("AroonOsc"))
		return m->addAroonOsc(height, 14, 0xff);
	else if (indicator == _T("CCI"))
		return m->addCCI(height, 20, 0x800080, 100, 0xff6666, 0x6666ff);
	else if (indicator == _T("EMV"))
		return m->addEaseOfMovement(height, 9, 0x6060, 0x606000);
	else if (indicator == _T("MDX"))
		return m->addMassIndex(height, 0x800080, 0xff6666, 0x6666ff);
	else if (indicator == _T("CVolatility"))
		return m->addChaikinVolatility(height, 10, 10, 0xff);
	else if (indicator == _T("COscillator"))
		return m->addChaikinOscillator(height, 0xff);
	else if (indicator == _T("CMF"))
		return m->addChaikinMoneyFlow(height, 21, 0x8000);
	else if (indicator == _T("NVI"))
		return m->addNVI(height, 255, 0xff, 0x883333);
	else if (indicator == _T("PVI"))
		return m->addPVI(height, 255, 0xff, 0x883333);
	else if (indicator == _T("MFI"))
		return m->addMFI(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
	else if (indicator == _T("PVO"))
		return m->addPVO(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
	else if (indicator == _T("PPO"))
		return m->addPPO(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
	else if (indicator == _T("UO"))
		return m->addUltimateOscillator(height, 7, 14, 28, 0x800080, 20, 0xff6666, 0x6666ff);
	else if (indicator == _T("Vol"))
		return m->addVolIndicator(height, 0x99ff99, 0xff9999, 0xc0c0c0);
	else if (indicator == _T("TRIX"))
		return m->addTRIX(height, 12, 0xff);
	else
		return 0;
}

/// <summary>
/// Get weekly data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::getWeeklyData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. If you do not have weekly
	// data, you may call "getDailyData" to get daily data first, and then call 
	// "convertDailyToWeeklyData" to convert it to weekly data, like:
	//
	//      getDailyData(startDate, endDate);
	//      convertDailyToWeeklyData();
	//
//	generateRandomData(ticker, startDate, endDate, 86400 * 7);
}

/// <summary>
/// Get monthly data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::getMonthlyData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. If you do not have monthly
	// data, you may call "getDailyData" to get daily data first, and then call 
	// "convertDailyToMonthlyData" to convert it to monthly data, like:
	//
	//      getDailyData(startDate, endDate);
	//      convertDailyToMonthlyData();
	//
//	generateRandomData(ticker, startDate, endDate, 86400 * 30);
}


/// <summary>
/// Creates a dummy chart to show an error message.
/// </summary>
/// <param name="viewer">The WinChartViewer to display the error message.</param>
/// <param name="msg">The error message</param>
static void errMsg(CChartViewer* viewer, const char *msg)
{
	MultiChart m(400, 200);
	m.addTitle(Chart::Center, msg, "Arial", 10)->setMaxWidth(m.getWidth());
	viewer->setChart(&m);
}


/////////////////////////////////////////////////////////////////////////////
// Chart Creation

/// <summary>
/// Add a moving average line to the FinanceChart object.
/// </summary>
/// <param name="m">The FinanceChart object to add the line to.</param>
/// <param name="avgType">The moving average type (SMA/EMA/TMA/WMA).</param>
/// <param name="avgPeriod">The moving average period.</param>
/// <param name="color">The color of the line.</param>
static LineLayer* addMovingAvg(FinanceChart *m, CString avgType, int avgPeriod, int color)
{
	if (avgPeriod > 1)
	{
		if (avgType == _T("SMA"))
			return m->addSimpleMovingAvg(avgPeriod, color);
		else if (avgType == _T("EMA"))
			return m->addExpMovingAvg(avgPeriod, color);
		else if (avgType == _T("TMA"))
			return m->addTriMovingAvg(avgPeriod, color);
		else if (avgType == _T("WMA"))
			return m->addWeightedMovingAvg(avgPeriod, color);
	}

	return 0;
}
static void CvtToKorean(char ch[256], string str)
{
	wstring wstr;
	USES_CONVERSION;
	wstr = wstring(A2W(str.c_str()));
	const wchar_t* strUni = wstr.c_str();
	WideCharToMultiByte(CP_UTF8, 0, strUni, -1, ch, sizeof(char) * 255, 0, 0);
}
/*[출처] [ChartDir] 차트디렉터 한글 사용 (변수를 이용한)|작성자 Many Photos*/


/// <summary>
/// Draw the chart according to user selection and display it in the ChartViewer.
/// </summary>
/// <param name="viewer">The ChartViewer object to display the chart.</param>
void CChartView::drawChart(CChartViewer *viewer)
{
	

//	double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
//	double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() +
//		viewer->getViewPortWidth());
//
//	DbgStrOutA("viewPortStartDate = %0.2f,viewPortEndDate = %0.2f",viewPortStartDate,viewPortEndDate);
//	// Get the array indexes that corresponds to the visible start and end dates
//	int startIndex = (int)floor(Chart::bSearch(m_timeStamps, viewPortStartDate));
//	int endIndex = (int)ceil(Chart::bSearch(m_timeStamps, viewPortEndDate));
//	int noOfPoints = endIndex - startIndex + 1;
//
//	DbgStrOutA("startIndex = %d,endIndex = %d,noOfPoints %d",startIndex,endIndex,noOfPoints);
//	//XYChart *c = new XYChart(640, 400);
//
//	DoubleArray viewPortTimeStamps = DoubleArray(m_timeStamps.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesA = DoubleArray(m_highData.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesB = DoubleArray(m_lowData.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesC = DoubleArray(m_openData.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesD = DoubleArray(m_closeData.data + startIndex, noOfPoints);
//	
	CRect r;
	GetWindowRect(&r);
//	XYChart *c = new XYChart(r.Width()-50, r.Height()-350);
//
//
//	CandleStickLayer *layer = c->addCandleStickLayer(viewPortDataSeriesA, viewPortDataSeriesB,
//		viewPortDataSeriesC,viewPortDataSeriesD, 0x00ff00, 0xff0000);
//
//	// Set the line width to 2 pixels
//	layer->setLineWidth(2);
//
//	// Create a FinanceChart object of width 720 pixels
//	//FinanceChart *c = new FinanceChart(r.Width()-50);
//	//XYChart*pl = c->addMainChart(r.Height()-350);
//	//XYChart * pl = (XYChart*)c->getChart();
//	//pl->setPlotArea(0,0, pl->getWidth() - 300, pl->getHeight() - 92, 0xffffff, -1, Chart::Transparent, 0xffffff, 0xffffff);
//	// Add a title to the chart
//	//c->addTitle("Finance Chart Demonstration");
//	
//	// Disable default legend box, as we are using dynamic legend
//	//c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);
//
//	// Set the data into the finance chart object
//	//c->setData(m_timeStamps, m_highData, m_lowData, m_openData, m_closeData, m_volData, 30);
//
//
//	// Add the main chart with 240 pixels in height
//
//	
//
//	//Axis * ppp = ((XYChart*)c->getChart())->xAxis();
//	//viewer->syncDateAxisWithViewPort("x",ppp);
//
//	// Add a 10 period simple moving average to the main chart, using brown color
//	//c->addSimpleMovingAvg(5, 0x1A8D21);
//
//	// Add a 20 period simple moving average to the main chart, using purple color
//	//c->addSimpleMovingAvg(20, 0x9900ff);
//	//c->addSimpleMovingAvg(60, 0x8C85E4);
//	// Add candlestick symbols to the main chart, using green/red for up/down days
//	//c->addCandleStick( 0xff0000,0x0000ff);
//
//	// Add 20 days bollinger band to the main chart, using light blue (9999ff) as the border and
//	// semi-transparent blue (c06666ff) as the fill color
//	//c->addBollingerBand(20, 2, 0x9999ff, 0xc06666ff);
//
//	// Add a 75 pixels volume bars sub-chart to the bottom of the main chart, using green/red/grey for
//	// up/down/flat days
//	//c->addVolBars(75, 0xff0000, 0x0000ff, 0x808080);
//
//	// Append a 14-days RSI indicator chart (75 pixels high) after the main chart. The main RSI line
//	// is purple (800080). Set threshold region to +/- 20 (that is, RSI = 50 +/- 25). The upper/lower
//	// threshold regions will be filled with red (ff0000)/blue (0000ff).
//	//c->addRSI(75, 14, 0x800080, 20, 0xff0000, 0x0000ff);
//
//	// Append a MACD(26, 12) indicator chart (75 pixels high) after the main chart, using 9 days for
//	// computing divergence.
//	//c->addMACD(75, 26, 12, 9, 0x0000ff, 0xff00ff, 0x008000);
//
//	// Include track line with legend for the latest data values
//	//trackFinance(c, ((XYChart *)c->getChart(0))->getPlotArea()->getRightX());
//
//	// Assign the chart to the WinChartViewer
//	//viewer->setChart(c);
//	
//// 	c->setPlotArea(55, 55, c->getWidth() - 80, c->getHeight() - 92, c->linearGradientColor(0, 55, 0, 
//// 		c->getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);
//
//	delete viewer->getChart();
//	viewer->setChart(c);
	double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
	double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() +
		viewer->getViewPortWidth());

	// Get the array indexes that corresponds to the visible start and end dates
	int startIndex = (int)floor(Chart::bSearch(m_timeStamps, viewPortStartDate));
	int endIndex = (int)ceil(Chart::bSearch(m_timeStamps, viewPortEndDate));
	int noOfPoints = endIndex - startIndex + 2;
		//DbgStrOutA("startIndex = %d,endIndex = %d,noOfPoints %d",startIndex,endIndex,noOfPoints);
	//	//XYChart *c = new XYChart(640, 400);
	// Extract the part of the data array that are visible.
	DoubleArray viewPortTimeStamps = DoubleArray(m_timeStamps.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesA = DoubleArray(m_openData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesB = DoubleArray(m_closeData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesC = DoubleArray(m_highData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesD = DoubleArray(m_lowData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesE = DoubleArray(m_volData.data + startIndex, noOfPoints);
	//
	// At this stage, we have extracted the visible data. We can use those data to plot the chart.
	//
	FinanceChart *c = new FinanceChart(r.Width()-50);

	// Add a title to the chart
	c->addTitle("Finance Chart Demonstration");

	// Disable default legend box, as we are using dynamic legend
	//c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);

	// Set the data into the finance chart object
	c->setData(viewPortTimeStamps, viewPortDataSeriesC, viewPortDataSeriesD, viewPortDataSeriesA, viewPortDataSeriesB, viewPortDataSeriesE, 30);

	// Add the main chart with 240 pixels in height
	c->addMainChart(r.Height()-350);
	 c->addCandleStick(0xff0000,0x0000ff);
	 c->addVolBars(75, 0xff0000, 0x0000ff, 0x808080);
	 trackFinance(c, ((XYChart *)c->getChart(0))->getPlotArea()->getRightX());
	///////////////////////////////////////////////////////////////////////////////////////
	// Configure overall chart appearance. 
	///////////////////////////////////////////////////////////////////////////////////////

	// Create an XYChart object of size 650 x 350 pixels, with a white (ffffff) background and grey 
	// (aaaaaa) border
	//XYChart *c = new XYChart(r.Width()-50, r.Height()-350, 0xffffff, 0xaaaaaa);

	// Set the plotarea at (55, 55) with width 90 pixels less than chart width, and height 90 pixels
	// less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
	// as background. Set border to transparent and grid lines to white (ffffff).
	//c->setPlotArea(55, 55, c->getWidth() - 90, c->getHeight() - 90, 0xffffff, -1, Chart::Transparent, 0xffffff, 0xffffff);

	// As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
	//c->setClipping();

	//// Add a title to the chart using 18 pts Times New Roman Bold Italic font
	//c->addTitle("   Zooming and Scrolling with Track Line (2)", "timesbi.ttf", 18);

	//// Add a legend box at (55, 30) using horizontal layout. Use 8pts Arial Bold as font. Set the
	//// background and border color to Transparent and use line style legend key.
	//LegendBox *b = c->addLegend(55, 30, false, "arialbd.ttf", 8);
	//b->setBackground(Chart::Transparent);
	//b->setLineStyleKey();

	//// Set the axis stem to transparent
	//c->xAxis()->setColors(Chart::Transparent);
	//c->yAxis()->setColors(Chart::Transparent);

	//// Add axis title using 10pts Arial Bold Italic font
	//c->yAxis()->setTitle("Ionic Temperature (C)", "arialbi.ttf", 10);

	///////////////////////////////////////////////////////////////////////////////////////
	// Add data to chart
	///////////////////////////////////////////////////////////////////////////////////////
		//CRect r;
		//GetWindowRect(&r);
		//XYChart *c = new XYChart(r.Width()-50, r.Height()-350);
	
	
	/*	CandleStickLayer *layer = c->addCandleStickLayer(viewPortDataSeriesC, viewPortDataSeriesD,
			viewPortDataSeriesA,viewPortDataSeriesB, 0x0000ff, 0xff0000);*/

		
	
		// Set the line width to 2 pixels
		//layer->setLineWidth(2);
		//c->addBarLayer(viewPortDataSeriesE, 0x00c000
		//	)->setUseYAxis2();
		// c->xAxis()->setDateScale(m_timeStamps.data[startIndex],m_timeStamps.data[startIndex + noOfPoints]);
		////c->xAxis()->
		// c->xAxis()->setLabelFormat("{value|yy/mm}");
	// 
	// In this example, we represent the data by lines. You may modify the code below to use other
	// representations (areas, scatter plot, etc).
	//

	// Add a line layer for the lines, using a line width of 2 pixels
	//LineLayer *layer = c->addLineLayer();
	//layer->setLineWidth(2);

	//// In this demo, we do not have too many data points. In real code, the chart may contain a lot
	//// of data points when fully zoomed out - much more than the number of horizontal pixels in this
	//// plot area. So it is a good idea to use fast line mode.
	//layer->setFastLineMode();

	//// Now we add the 3 data series to a line layer, using the color red (ff0000), green
	//// (00cc00) and blue (0000ff)
	//layer->setXData(viewPortTimeStamps);
	//layer->addDataSet(viewPortDataSeriesA, 0xff3333, "Alpha");
	//layer->addDataSet(viewPortDataSeriesB, 0x008800, "Beta");
	//layer->addDataSet(viewPortDataSeriesC, 0x3333CC, "Gamma");

	///////////////////////////////////////////////////////////////////////////////////////
	// Configure axis scale and labelling
	///////////////////////////////////////////////////////////////////////////////////////

	// Set the x-axis as a date/time axis with the scale according to the view port x range.
	//viewer->syncDateAxisWithViewPort("x", c->xAxis());

	//
	// In this demo, the time range can be from a few years to a few days. We demonstrate how to set
	// up different date/time format based on the time range.
	//

	// If all ticks are yearly aligned, then we use "yyyy" as the label format.
	//c->xAxis()->setFormatCondition("align", 360 * 86400);
	//c->xAxis()->setLabelFormat("{value|yyyy}");

	//// If all ticks are monthly aligned, then we use "mmm yyyy" in bold font as the first 
	//// label of a year, and "mmm" for other labels.
	//c->xAxis()->setFormatCondition("align", 30 * 86400);
	//c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*font=bold*>{value|mmm yyyy}", 
	//	Chart::AllPassFilter(), "{value|mmm}");

	//// If all ticks are daily algined, then we use "mmm dd<*br*>yyyy" in bold font as the 
	//// first label of a year, and "mmm dd" in bold font as the first label of a month, and
	//// "dd" for other labels.
	//c->xAxis()->setFormatCondition("align", 86400);
	//c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), 
	//	"<*block,halign=left*><*font=bold*>{value|mmm dd<*br*>yyyy}", 
	//	Chart::StartOfMonthFilter(), "<*font=bold*>{value|mmm dd}");
	//c->xAxis()->setMultiFormat(Chart::AllPassFilter(), "{value|dd}");

	//// For all other cases (sub-daily ticks), use "hh:nn<*br*>mmm dd" for the first label of
	//// a day, and "hh:nn" for other labels.
	//c->xAxis()->setFormatCondition("else");
	//c->xAxis()->setMultiFormat(Chart::StartOfDayFilter(), 
	//	"<*font=bold*>{value|hh:nn<*br*>mmm dd}", Chart::AllPassFilter(), "{value|hh:nn}");

	///////////////////////////////////////////////////////////////////////////////////////
	// Output the chart
	///////////////////////////////////////////////////////////////////////////////////////

	// We need to update the track line too. If the mouse is moving on the chart (eg. if 
	// the user drags the mouse on the chart to scroll it), the track line will be updated
	// in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
	/*if ((!viewer->isInMouseMoveEvent()) && viewer->isMouseOnPlotArea())
		trackLineLabel(c, viewer->getPlotAreaMouseX());*/

	delete viewer->getChart();
	viewer->setChart(c);

}




void CChartView::OnBnClickedButtonRefresh()
{
	// TODO: Add your control notification handler code here
	//
	// Sample data for the CandleStick chart.
	//
	drawChart(&m_ChartViewer);
	return;
	double highData[] = {2043, 2039, 2076, 2064, 2048, 2058, 2070, 2033, 2027, 2029, 2071, 2085,
		2034, 2031, 2056, 2128, 2180, 2183, 2192, 2213, 2230, 2281, 2272};

	double lowData[] = {1931, 1921, 1985, 2028, 1986, 1994, 1999, 1958, 1943, 1944, 1962, 2011,
		1975, 1962, 1928, 2059, 2112, 2103, 2151, 2127, 2123, 2152, 2212};

	double openData[] = {2000, 1957, 1993, 2037, 2018, 2021, 2045, 2009, 1959, 1985, 2008, 2048,
		2006, 2010, 1971, 2080, 2116, 2137, 2170, 2172, 2171, 2191, 2240};

	double closeData[] = {1950, 1991, 2026, 2029, 2004, 2053, 2011, 1962, 1987, 2019, 2040, 2016,
		1996, 1985, 2006, 2113, 2142, 2167, 2158, 2201, 2188, 2231, 2242};

	// The labels for the CandleStick chart
	const char *labels[] = {"Mon 1", "Tue 2", "Wed 3", "Thu 4", "Fri 5", "Mon 8", "Tue 9", "Wed 10",
		"Thu 11", "Fri 12", "Mon 15", "Tue 16", "Wed 17", "Thu 18", "Fri 19", "Mon 22", "Tue 23",
		"Wed 24", "Thu 25", "Fri 26", "Mon 29", "Tue 30", "Wed 31"};

	// Create a XYChart object of size 600 x 350 pixels
	XYChart *c = new XYChart(600, 350);

	// Set the plotarea at (50, 25) and of size 500 x 250 pixels. Enable both the horizontal and
	// vertical grids by setting their colors to grey (0xc0c0c0)
	c->setPlotArea(50, 25, 500, 250)->setGridColor(0xc0c0c0, 0xc0c0c0);

	// Add a title to the chart
	c->addTitle("Universal Stock Index on Jan 2001");

	// Add a custom text at (50, 25) (the upper left corner of the plotarea). Use 12pt Arial
	// Bold/blue (4040c0) as the font.
	c->addText(50, 25, "(c) Global XYZ ABC Company", "arialbd.ttf", 12, 0x4040c0);

	// Add a title to the x axis
	c->xAxis()->setTitle("Jan 2001");

	// Set the labels on the x axis. Rotate the labels by 45 degrees.
	c->xAxis()->setLabels(StringArray(labels, (int)(sizeof(labels) / sizeof(labels[0])))
		)->setFontAngle(45);

	// Add a title to the y axis
	c->yAxis()->setTitle("Universal Stock Index");

	// Draw the y axis on the right hand side of the plot area
	c->setYAxisOnRight(true);

	// Add a CandleStick layer to the chart using green (00ff00) for up candles and red (ff0000) for
	// down candles
	CandleStickLayer *layer = c->addCandleStickLayer(DoubleArray(highData, (int)(sizeof(highData) /
		sizeof(highData[0]))), DoubleArray(lowData, (int)(sizeof(lowData) / sizeof(lowData[0]))),
		DoubleArray(openData, (int)(sizeof(openData) / sizeof(openData[0]))), DoubleArray(closeData,
		(int)(sizeof(closeData) / sizeof(closeData[0]))), 0x00ff00, 0xff0000);

	// Set the line width to 2 pixels
	layer->setLineWidth(2);

	// Output the chart
	//c->makeChart("candlestick.png");
	

	m_ChartViewer.setChart(c);
	
	// Output the chart
	//c->makeChart("simplepie.png");

	//free up resources
	delete c;
	

}

//
// Draw finance chart track line with legend
//
void CChartView::trackFinance(MultiChart *m, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = m->initDynamicLayer();

    // It is possible for a FinanceChart to be empty, so we need to check for it.
    if (m->getChartCount() == 0)
        return ;

    // Get the data x-value that is nearest to the mouse
    int xValue = (int)(((XYChart *)m->getChart(0))->getNearestXValue(mouseX));

    // Iterate the XY charts (main price chart and indicator charts) in the FinanceChart
    XYChart *c = 0;
    for(int i = 0; i < m->getChartCount(); ++i) {
        c = (XYChart *)m->getChart(i);

        // Variables to hold the legend entries
        ostringstream ohlcLegend;
        vector<string> legendEntries;

        // Iterate through all layers to find the highest data point
        for(int j = 0; j < c->getLayerCount(); ++j) {
            Layer *layer = c->getLayerByZ(j);
            int xIndex = layer->getXIndexOf(xValue);
            int dataSetCount = layer->getDataSetCount();

            // In a FinanceChart, only layers showing OHLC data can have 4 data sets
            if (dataSetCount == 4) {
                double highValue = layer->getDataSet(0)->getValue(xIndex);
                double lowValue = layer->getDataSet(1)->getValue(xIndex);
                double openValue = layer->getDataSet(2)->getValue(xIndex);
                double closeValue = layer->getDataSet(3)->getValue(xIndex);

                if (closeValue != Chart::NoValue) {
                    // Build the OHLC legend
					ohlcLegend << "      <*block*>";
					ohlcLegend << "Open: " << c->formatValue(openValue, "{value|P4}");
					ohlcLegend << ", High: " << c->formatValue(highValue, "{value|P4}"); 
					ohlcLegend << ", Low: " << c->formatValue(lowValue, "{value|P4}"); 
					ohlcLegend << ", Close: " << c->formatValue(closeValue, "{value|P4}");

                    // We also draw an upward or downward triangle for up and down days and the %
                    // change
                    double lastCloseValue = layer->getDataSet(3)->getValue(xIndex - 1);
                    if (lastCloseValue != Chart::NoValue) {
                        double change = closeValue - lastCloseValue;
                        double percent = change * 100 / closeValue;
                        string symbol = (change >= 0) ?
                            "<*font,color=cc0000*><*img=@triangle,width=8,color=cc0000*>" :
                            "<*font,color=0000ff*><*img=@invertedtriangle,width=8,color=0000ff*>";

                        ohlcLegend << "  " << symbol << " " << c->formatValue(change, "{value|P4}");
						ohlcLegend << " (" << c->formatValue(percent, "{value|2}") << "%)<*/font*>";
                    }

					ohlcLegend << "<*/*>";
                }
            } else {
                // Iterate through all the data sets in the layer
                for(int k = 0; k < layer->getDataSetCount(); ++k) {
                    DataSet *dataSet = layer->getDataSetByZ(k);

                    string name = dataSet->getDataName();
                    double value = dataSet->getValue(xIndex);
                    if ((0 != name.size()) && (value != Chart::NoValue)) {

                        // In a FinanceChart, the data set name consists of the indicator name and its
                        // latest value. It is like "Vol: 123M" or "RSI (14): 55.34". As we are
                        // generating the values dynamically, we need to extract the indictor name
                        // out, and also the volume unit (if any).

						// The volume unit
						string unitChar;

                        // The indicator name is the part of the name up to the colon character.
						int delimiterPosition = (int)name.find(':');
                        if (name.npos != delimiterPosition) {
							
							// The unit, if any, is the trailing non-digit character(s).
							int lastDigitPos = (int)name.find_last_of("0123456789");
							if ((name.npos != lastDigitPos) && (lastDigitPos + 1 < (int)name.size()) &&
								(lastDigitPos > delimiterPosition))
								unitChar = name.substr(lastDigitPos + 1);

							name.resize(delimiterPosition);
                        }

                        // In a FinanceChart, if there are two data sets, it must be representing a
                        // range.
                        if (dataSetCount == 2) {
                            // We show both values in the range in a single legend entry
                            value = layer->getDataSet(0)->getValue(xIndex);
                            double value2 = layer->getDataSet(1)->getValue(xIndex);
                            name = name + ": " + c->formatValue(min(value, value2), "{value|P3}");
							name = name + " - " + c->formatValue(max(value, value2), "{value|P3}");
                        } else {
                            // In a FinanceChart, only the layer for volume bars has 3 data sets for
                            // up/down/flat days
                            if (dataSetCount == 3) {
                                // The actual volume is the sum of the 3 data sets.
                                value = layer->getDataSet(0)->getValue(xIndex) + layer->getDataSet(1
                                    )->getValue(xIndex) + layer->getDataSet(2)->getValue(xIndex);
                            }

                            // Create the legend entry
                            name = name + ": " + c->formatValue(value, "{value|P3}") + unitChar;
                        }

                        // Build the legend entry, consist of a colored square box and the name (with
                        // the data value in it).
						ostringstream legendEntry;
						legendEntry << "<*block*><*img=@square,width=8,edgeColor=000000,color=" 
							<< hex << dataSet->getDataColor() << "*> " << name << "<*/*>";
                        legendEntries.push_back(legendEntry.str());
                    }
                }
            }
        }

        // Get the plot area position relative to the entire FinanceChart
        PlotArea *plotArea = c->getPlotArea();
        int plotAreaLeftX = plotArea->getLeftX() + c->getAbsOffsetX();
        int plotAreaTopY = plotArea->getTopY() + c->getAbsOffsetY();

		// The legend begins with the date label, then the ohlcLegend (if any), and then the
		// entries for the indicators.
		ostringstream legendText;
		legendText << "<*block,valign=top,maxWidth=" << (plotArea->getWidth() - 5) 
			<< "*><*font=arialbd.ttf*>[" << c->xAxis()->getFormattedLabel(xValue, "mmm dd, yyyy")
			<< "]<*/font*>" << ohlcLegend.str();
		for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i) {
			legendText << "      " << legendEntries[i];
		}
		legendText << "<*/*>";

        // Draw a vertical track line at the x-position
        d->vline(plotAreaTopY, plotAreaTopY + plotArea->getHeight(), c->getXCoor(xValue) +
            c->getAbsOffsetX(), d->dashLineColor(0x000000, 0x0101));

        // Display the legend on the top of the plot area
        TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
        t->draw(plotAreaLeftX + 5, plotAreaTopY + 3, 0x000000, Chart::TopLeft);
		t->destroy();
    }
}

void CChartView::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	m_ChartViewer.updateViewPort(true, false);      
}
//
// Draw track cursor when mouse is moving over plotarea
//
void CChartView::OnMouseMovePlotArea()
{
	trackFinance((MultiChart *)m_ChartViewer.getChart(), m_ChartViewer.getPlotAreaMouseX());
	m_ChartViewer.updateDisplay();
}

void CChartView::SendSearch(void)
{
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strRQName = _T("주식일봉차트조회요청");
	theApp.m_khOpenApi.SetInputValue(L"종목코드"	, pMain->m_boardJongmokCode);
	CString t = COleDateTime::GetCurrentTime().Format(L"%Y%m%d");
	//비밀번호 = 사용안함(공백)
	theApp.m_khOpenApi.SetInputValue(L"기준일자"	, t);

	//비밀번호입력매체구분 = 00
	theApp.m_khOpenApi.SetInputValue(L"수정주가구분"	,  L"0");

	long ret =  theApp.m_khOpenApi.CommRqData(strRQName,L"OPT10081",0,m_strScrNo);
	theApp.IsError(ret);
}
