// FiveDlg.cpp : 实现文件
#include "stdafx.h"
#include "Five.h"
#include "FiveDlg.h"
#include "afxdialogex.h"
#include "Game.h"
#include "ServerDlg.h"
#include "ClientDlg.h"
#include "NameDlg.h"
#include "StatDlg.h"
#include "Table.h"
#include "HandsOffDlg.h"
#include <iostream>
#include "fstream"
using namespace std;    //必须加，否则fstream不可用

//CPoint gRecord[300];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{ }

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CFiveDlg 对话框
CFiveDlg::CFiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFiveDlg::IDD, pParent)
	, s_hour(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strChat = _T("");
}

void CFiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_CHAT, m_ChatList);
	DDX_CBString(pDX, IDC_CMB_CHAT, m_strChat);
	DDX_Control(pDX, IDC_CMB_CHAT, CHAT);
	DDX_Control(pDX, IDC_STATIC_Countdown, m_time);
}

BEGIN_MESSAGE_MAP(CFiveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_ABOUT, &CFiveDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_PlayerFirst, &CFiveDlg::OnMenuPlayerfirst)
	ON_COMMAND(ID_MENU_PCFirst, &CFiveDlg::OnMenuPcfirst)
	ON_BN_CLICKED(IDC_BTN_BACK, &CFiveDlg::OnBnClickedBtnBack)
	ON_COMMAND(ID_MENU_SERVER, &CFiveDlg::OnMenuServer)
	ON_COMMAND(ID_MENU_CLIENT, &CFiveDlg::OnMenuClient)
	ON_COMMAND(ID_MENU_PLAYAGAIN, &CFiveDlg::OnMenuPlayagain)
	ON_COMMAND(ID_MENU_LEAVE, &CFiveDlg::OnMenuLeave)
	ON_COMMAND(ID_MENU_NAME, &CFiveDlg::OnMenuName)
	ON_COMMAND(ID_MENU_STAT, &CFiveDlg::OnMenuStat)
	ON_BN_CLICKED(IDC_BTN_QHQ, &CFiveDlg::OnClickedBtnQhq)
	ON_BN_CLICKED(IDC_BTN_LOST, &CFiveDlg::OnClickedBtnLost)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BTN_SAVECHESS, &CFiveDlg::OnBnClickedBtnSavechess)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CFiveDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_SEND, &CFiveDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_URGE, &CFiveDlg::OnBnClickedBtnUrge)
	ON_BN_CLICKED(IDC_BTN_PRAISE, &CFiveDlg::OnBnClickedBtnPraise)
	ON_BN_CLICKED(IDC_BTN_QFDS, &CFiveDlg::OnBnClickedBtnQfds)
	ON_BN_CLICKED(IDC_BTN_YH, &CFiveDlg::OnBnClickedBtnYh)
	ON_BN_CLICKED(IDC_START_count, &CFiveDlg::OnBnClickedTimer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SUSPEND, &CFiveDlg::OnBnClickedButtonSuspend)
	ON_COMMAND(ID_HandsOff, &CFiveDlg::OnHandsoff)
END_MESSAGE_MAP()


// CFiveDlg 消息处理程序
BOOL CFiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CHAT.AddString("哈哈哈哈哈哈~");
	CHAT.AddString("快点吧~");
	CHAT.AddString("这一步真是高啊！");
	CHAT.AddString("再来一局怎么样？~");
	
	n_hour = 0;
	n_minute = 0;
	n_second = 0;
	s_hour = "00";
	s_minute = "00";
	s_second = "00";
	UpdateData(FALSE);

	b_review = FALSE;
	b_suspend = FALSE;

    m_pDlg = NULL;
    CRect rect(0, 0, 200, 200);
    m_Table.CreateEx( WS_EX_CLIENTEDGE, _T("ChessTable"), NULL, WS_VISIBLE | WS_BORDER | WS_CHILD,
        CRect( 0, 0, 480, 509 ), this, IDC_TABLE );
    // 设置双方姓名
    SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    SetDlgItemText( IDC_ST_ENEMY, _T("计算机") );
    // 禁用“再玩”和“离开”
    CMenu *pMenu = GetMenu();
    pMenu->EnableMenuItem( ID_MENU_PLAYAGAIN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );
    pMenu->EnableMenuItem( ID_MENU_LEAVE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );

	m_Table.Clear( TRUE );
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );

	//下面五行为网络对战新增部分
	 // 捕获聊天输入框句柄，供处理回车使用
	m_hChat = (HWND)FindWindowEx( GetDlgItem( IDC_CMB_CHAT )->GetSafeHwnd(), NULL, _T("Edit"), NULL );
	 ::SendMessage( m_hChat, EM_LIMITTEXT, (WPARAM)128, 0);
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );  
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	GetDlgItem(IDC_BTN_SAVECHESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_URGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PRAISE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_QFDS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_YH)->EnableWindow(FALSE);
	GetDlgItem(IDC_TABLE)->SetFocus();
	return FALSE;  // 除非将焦点设置到控件，否则返回TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CFiveDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CFiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//关于对话框
void CFiveDlg::OnMenuAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
    dlg.DoModal();
}
//玩家先走
void CFiveDlg::OnMenuPlayerfirst()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// 与电脑对弈，不允许和棋、聊天与认输
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	::SetCursor(AfxGetApp()->LoadCursor(IDC_BLACK));
	m_Table.Accept( 1 );
}

//计算机先走
void CFiveDlg::OnMenuPcfirst()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// 与电脑对弈，不允许和棋、聊天与认输
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	m_Table.SetColor( 1 );
    m_Table.Clear( FALSE );
    m_Table.SetGameMode( 1 );
}
//悔棋
void CFiveDlg::OnBnClickedBtnBack()
{
	// TODO: 在此添加控件通知处理程序代码
	 m_Table.Back();
}


void CFiveDlg::OnMenuServer()
{
	// TODO: 在此添加命令处理程序代码
	m_pDlg = new CServerDlg;
    m_pDlg->Create( IDD_DLG_SERVER, this );
    m_pDlg->ShowWindow( SW_SHOW );
}


void CFiveDlg::OnMenuClient()
{
	// TODO: 在此添加命令处理程序代码
    CClientDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        // 发送己方姓名
        MSGSTRUCT msg;
        msg.uMsg = MSG_OPPOSITE;
        lstrcpy( msg.szMsg, m_Table.m_strMe );

        m_Table.m_clientSocket.Send( (LPCVOID)&msg, sizeof( MSGSTRUCT ) );
        // 设置按钮状态
        GetDlgItem( IDC_BTN_QHQ )->EnableWindow( TRUE );
        GetDlgItem( IDC_CMB_CHAT )->EnableWindow( TRUE );
        GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
        GetDlgItem( IDC_BTN_LOST )->EnableWindow( TRUE );
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_URGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PRAISE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_QFDS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_YH)->EnableWindow(TRUE);
        // 设置菜单状态
        m_Table.SetMenuState( FALSE );
    }
}


void CFiveDlg::OnMenuPlayagain()
{
	// TODO: 在此添加命令处理程序代码
    m_Table.PlayAgain();
}


void CFiveDlg::OnMenuLeave()
{
	// TODO: 在此添加命令处理程序代码
	m_Table.m_serverSocket.Close();
    GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_URGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PRAISE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_QFDS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_YH)->EnableWindow(FALSE);
    // 设置菜单状态
    m_Table.SetMenuState( TRUE );
    // 设置棋盘等待状态
    m_Table.SetWait( TRUE );
    // 设置网络连接状态
    m_Table.m_bConnected = FALSE;
    // 重新设置对方名称
    SetDlgItemText( IDC_ST_ENEMY, _T("无玩家加入") );
}


void CFiveDlg::OnMenuName()
{
	// TODO: 在此添加命令处理程序代码
	CNameDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    }
}


void CFiveDlg::OnMenuStat()
{
	// TODO: 在此添加命令处理程序代码
	CStatDlg dlg;
    dlg.DoModal();
}


void CFiveDlg::OnClickedBtnQhq()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Table.DrawGame();
}


void CFiveDlg::OnClickedBtnLost()
{
	// TODO: 在此添加控件通知处理程序代码
		m_Table.GiveUp();
}


BOOL CFiveDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    if ( GetDlgItem( IDC_EDT_CHAT ) == pWnd )
    {
        // 处理聊天记录的鼠标指针
        SetCursor( LoadCursor( NULL, IDC_ARROW ) );
        return TRUE;
    }
    else
		return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CFiveDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	  // 处理聊天输入窗口的回车消息
	    UpdateData(TRUE);
        // 发送聊天内容
        m_Table.Chat( m_strChat );
        // 加入聊天记录
        CString strAdd;
        strAdd.Format( _T("你 说：%s\r\n"), m_strChat );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // 清空聊天输入窗口
        m_strChat="";
		UpdateData(FALSE);
}


BOOL CFiveDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam && m_hChat == pMsg->hwnd )
    {
        // 处理聊天输入窗口的回车消息
        TCHAR str[128];
        // 发送聊天内容
        ::GetWindowText( m_hChat, str, 128 );
        m_Table.Chat( str );
        // 加入聊天记录
        CString strAdd;
        strAdd.Format( _T("你 说：%s\r\n"), str );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // 清空聊天输入窗口
        ::SetWindowText( m_hChat, _T("") );
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CFiveDlg::OnCancel() 
{
    if ( IDYES == MessageBox( _T("确定要退出吗？"), _T("五子棋"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2 ) )
        CDialog::OnCancel();
}


/*保存棋局*/
void CFiveDlg::OnBnClickedBtnSavechess()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strName;
	CFileDialog dlg(FALSE, "chr", "", OFN_OVERWRITEPROMPT, "棋局文件(*.chr)|*.chr||", NULL);
	dlg.m_ofn.lpstrTitle = "保存棋局";
	if (dlg.DoModal())
		strName = dlg.GetPathName();

	ofstream fileout(strName);
	STEP step;
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
			fileout << m_Table.m_data[i][j] << endl;//保存棋局信息到文件
	CDialog *pDlg = (CDialog *)GetParent();
	pDlg->MessageBox(_T("已成功保存本局棋盘文件！可随时打开复盘哦~"), _T("保存棋局信息"), MB_ICONINFORMATION);
}

/*打开之前保存的棋局-复盘*/
void CFiveDlg::OnBnClickedBtnOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strName;
	CFileDialog dlg(TRUE, "chr", "", OFN_HIDEREADONLY, "棋局文件(*.chr)|*.chr||", NULL);
	dlg.m_ofn.lpstrTitle = "打开文件";
	if (dlg.DoModal())
		strName = dlg.GetPathName();

	ifstream filein(strName);
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
			filein >> m_Table.m_data[i][j];
	/*for (i = 0; i<300; i++)
		gRecord[i] = CPoint(0, 0);*/
	Invalidate();
	UpdateWindow();
}

/*发送消息*/
void CFiveDlg::OnBnClickedBtnSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 发送聊天内容
	m_Table.Chat(m_strChat);
	// 加入聊天记录
	CString strAdd;
	strAdd.Format(_T("你 说：%s\r\n"), m_strChat);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	// 清空聊天输入窗口
	m_strChat = "";
	UpdateData(FALSE);
}

/*快捷互动-催促对方*/
void CFiveDlg::OnBnClickedBtnUrge()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 发送聊天内容
	CString strUrge="快点吧~我等到花儿都要谢了！";

	m_Table.Chat(strUrge);
	// 加入聊天记录
	CString strAdd;
	strAdd.Format(_T("你 说：%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_URGE), NULL, SND_SYNC | SND_RESOURCE);
	// 清空聊天输入窗口
	m_strChat = "";
	UpdateData(FALSE);
}

/*快捷互动-夸奖对方*/
void CFiveDlg::OnBnClickedBtnPraise()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 发送聊天内容
	CString strUrge = "你的棋下得真好~奖励一朵小红花！";

	m_Table.Chat(strUrge);
	// 加入聊天记录
	CString strAdd;
	strAdd.Format(_T("你 说：%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_PRAISE), NULL, SND_SYNC | SND_RESOURCE);
	// 清空聊天输入窗口
	m_strChat = "";
	UpdateData(FALSE);
}

/*快捷互动-棋逢对手*/
void CFiveDlg::OnBnClickedBtnQfds()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 发送聊天内容
	CString strUrge = "看来今天是棋逢对手啊！让我们一决胜负！";

	m_Table.Chat(strUrge);
	// 加入聊天记录
	CString strAdd;
	strAdd.Format(_T("你 说：%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_QFDS), NULL, SND_SYNC | SND_RESOURCE);
	// 清空聊天输入窗口
	m_strChat = "";
	UpdateData(FALSE);
}

/*快捷互动-发出疑惑*/
void CFiveDlg::OnBnClickedBtnYh()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 发送聊天内容
	CString strUrge = "嗯？发生了什么？~";

	m_Table.Chat(strUrge);
	// 加入聊天记录
	CString strAdd;
	strAdd.Format(_T("你 说：%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_YH), NULL, SND_SYNC | SND_RESOURCE);
	// 清空聊天输入窗口
	m_strChat = "";
	UpdateData(FALSE);
}

/*开始计时*/
void CFiveDlg::OnBnClickedTimer()
{
	// TODO:  在此添加控件通知处理程序代码
	
	if (b_review || b_suspend)
		KillTimer(2);
	b_review = FALSE;
	b_suspend = FALSE;
	n_hour = 0;
	n_minute = 0;
	n_second = 0;
	SetTimer(2, 1000, NULL);		// 2号定时器，每1000毫秒（1秒）触发一次
}

/*计时器*/
void CFiveDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString str;
	switch (nIDEvent)
	{
	case 2:
	{
			  if (b_review == FALSE)
			  {
				  str.Format(_T("%d:%d:%d"), n_hour, n_minute, n_second);
				  m_time.SetWindowText(str);
				  n_second++;
				  if (n_second == 60)
				  {
					  n_second = 0;
					  n_minute++;
				  }
				  if (n_minute == 60)
				  {
					  n_minute = 0;
					  n_hour++;
				  }
				  if (n_hour == 1)
					  n_hour = 0;
				  if (n_minute == 5)
					  b_review = TRUE;
			  }
			  else if (b_review)
			  {

				  n_hour = 0;
				  n_minute = 0;
				  n_second = 0;
				  s_hour.Format("%s", "Re");
				  s_minute.Format("%s", "vi");
				  s_second.Format("%s", "ew");
				  str.Format(_T("%d:%d:%d"), n_hour, n_minute, n_second);
				  m_time.SetWindowText(str);
			  } 
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

/*暂停或继续计时*/
void CFiveDlg::OnBnClickedButtonSuspend()
{
	CString str;
	// TODO:  在此添加控件通知处理程序代码
	b_suspend = !b_suspend;
	if (b_suspend)
	{
		KillTimer(2);      // 停止计时器
		int h1, h2, m1, m2, s1, s2;
		h1 = n_hour / 10;
		h2 = n_hour % 10;
		m1 = n_minute / 10;
		m2 = n_minute % 10;
		s1 = n_second / 10;
		s2 = n_second % 10;
		s_hour.Format("%d%d", h1, h2);
		s_minute.Format("%d%d", m1, m2);
		s_second.Format("%d%d", s1, s2);
		str.Format(_T("%d:%d:%d"), n_hour, n_minute, n_second);
		m_time.SetWindowText(str);
		UpdateData(FALSE);
	}
	else
	{
		SetTimer(2, 1000, NULL);		// 重新开始计时
	}
}


void CFiveDlg::OnHandsoff()
{
	// TODO:  在此添加命令处理程序代码
	CHandsOffDlg dlg;
	dlg.DoModal();
}
