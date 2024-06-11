// FiveDlg.cpp : ʵ���ļ�
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
using namespace std;    //����ӣ�����fstream������

//CPoint gRecord[300];

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

// CFiveDlg �Ի���
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


// CFiveDlg ��Ϣ�������
BOOL CFiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CHAT.AddString("������������~");
	CHAT.AddString("����~");
	CHAT.AddString("��һ�����Ǹ߰���");
	CHAT.AddString("����һ����ô����~");
	
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
    // ����˫������
    SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    SetDlgItemText( IDC_ST_ENEMY, _T("�����") );
    // ���á����桱�͡��뿪��
    CMenu *pMenu = GetMenu();
    pMenu->EnableMenuItem( ID_MENU_PLAYAGAIN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );
    pMenu->EnableMenuItem( ID_MENU_LEAVE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );

	m_Table.Clear( TRUE );
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );

	//��������Ϊ�����ս��������
	 // �����������������������س�ʹ��
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
	return FALSE;  // ���ǽ��������õ��ؼ������򷵻�TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CFiveDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CFiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//���ڶԻ���
void CFiveDlg::OnMenuAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
    dlg.DoModal();
}
//�������
void CFiveDlg::OnMenuPlayerfirst()
{
	// TODO: �ڴ���������������
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// ����Զ��ģ���������塢����������
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	::SetCursor(AfxGetApp()->LoadCursor(IDC_BLACK));
	m_Table.Accept( 1 );
}

//���������
void CFiveDlg::OnMenuPcfirst()
{
	// TODO: �ڴ���������������
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// ����Զ��ģ���������塢����������
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	m_Table.SetColor( 1 );
    m_Table.Clear( FALSE );
    m_Table.SetGameMode( 1 );
}
//����
void CFiveDlg::OnBnClickedBtnBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 m_Table.Back();
}


void CFiveDlg::OnMenuServer()
{
	// TODO: �ڴ���������������
	m_pDlg = new CServerDlg;
    m_pDlg->Create( IDD_DLG_SERVER, this );
    m_pDlg->ShowWindow( SW_SHOW );
}


void CFiveDlg::OnMenuClient()
{
	// TODO: �ڴ���������������
    CClientDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        // ���ͼ�������
        MSGSTRUCT msg;
        msg.uMsg = MSG_OPPOSITE;
        lstrcpy( msg.szMsg, m_Table.m_strMe );

        m_Table.m_clientSocket.Send( (LPCVOID)&msg, sizeof( MSGSTRUCT ) );
        // ���ð�ť״̬
        GetDlgItem( IDC_BTN_QHQ )->EnableWindow( TRUE );
        GetDlgItem( IDC_CMB_CHAT )->EnableWindow( TRUE );
        GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
        GetDlgItem( IDC_BTN_LOST )->EnableWindow( TRUE );
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_URGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PRAISE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_QFDS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_YH)->EnableWindow(TRUE);
        // ���ò˵�״̬
        m_Table.SetMenuState( FALSE );
    }
}


void CFiveDlg::OnMenuPlayagain()
{
	// TODO: �ڴ���������������
    m_Table.PlayAgain();
}


void CFiveDlg::OnMenuLeave()
{
	// TODO: �ڴ���������������
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
    // ���ò˵�״̬
    m_Table.SetMenuState( TRUE );
    // �������̵ȴ�״̬
    m_Table.SetWait( TRUE );
    // ������������״̬
    m_Table.m_bConnected = FALSE;
    // �������öԷ�����
    SetDlgItemText( IDC_ST_ENEMY, _T("����Ҽ���") );
}


void CFiveDlg::OnMenuName()
{
	// TODO: �ڴ���������������
	CNameDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    }
}


void CFiveDlg::OnMenuStat()
{
	// TODO: �ڴ���������������
	CStatDlg dlg;
    dlg.DoModal();
}


void CFiveDlg::OnClickedBtnQhq()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Table.DrawGame();
}


void CFiveDlg::OnClickedBtnLost()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		m_Table.GiveUp();
}


BOOL CFiveDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if ( GetDlgItem( IDC_EDT_CHAT ) == pWnd )
    {
        // ���������¼�����ָ��
        SetCursor( LoadCursor( NULL, IDC_ARROW ) );
        return TRUE;
    }
    else
		return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CFiveDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	  // �����������봰�ڵĻس���Ϣ
	    UpdateData(TRUE);
        // ������������
        m_Table.Chat( m_strChat );
        // ���������¼
        CString strAdd;
        strAdd.Format( _T("�� ˵��%s\r\n"), m_strChat );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // ����������봰��
        m_strChat="";
		UpdateData(FALSE);
}


BOOL CFiveDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam && m_hChat == pMsg->hwnd )
    {
        // �����������봰�ڵĻس���Ϣ
        TCHAR str[128];
        // ������������
        ::GetWindowText( m_hChat, str, 128 );
        m_Table.Chat( str );
        // ���������¼
        CString strAdd;
        strAdd.Format( _T("�� ˵��%s\r\n"), str );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // ����������봰��
        ::SetWindowText( m_hChat, _T("") );
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CFiveDlg::OnCancel() 
{
    if ( IDYES == MessageBox( _T("ȷ��Ҫ�˳���"), _T("������"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2 ) )
        CDialog::OnCancel();
}


/*�������*/
void CFiveDlg::OnBnClickedBtnSavechess()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strName;
	CFileDialog dlg(FALSE, "chr", "", OFN_OVERWRITEPROMPT, "����ļ�(*.chr)|*.chr||", NULL);
	dlg.m_ofn.lpstrTitle = "�������";
	if (dlg.DoModal())
		strName = dlg.GetPathName();

	ofstream fileout(strName);
	STEP step;
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
			fileout << m_Table.m_data[i][j] << endl;//���������Ϣ���ļ�
	CDialog *pDlg = (CDialog *)GetParent();
	pDlg->MessageBox(_T("�ѳɹ����汾�������ļ�������ʱ�򿪸���Ŷ~"), _T("���������Ϣ"), MB_ICONINFORMATION);
}

/*��֮ǰ��������-����*/
void CFiveDlg::OnBnClickedBtnOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strName;
	CFileDialog dlg(TRUE, "chr", "", OFN_HIDEREADONLY, "����ļ�(*.chr)|*.chr||", NULL);
	dlg.m_ofn.lpstrTitle = "���ļ�";
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

/*������Ϣ*/
void CFiveDlg::OnBnClickedBtnSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ������������
	m_Table.Chat(m_strChat);
	// ���������¼
	CString strAdd;
	strAdd.Format(_T("�� ˵��%s\r\n"), m_strChat);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	// ����������봰��
	m_strChat = "";
	UpdateData(FALSE);
}

/*��ݻ���-�ߴٶԷ�*/
void CFiveDlg::OnBnClickedBtnUrge()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ������������
	CString strUrge="����~�ҵȵ�������Ҫл�ˣ�";

	m_Table.Chat(strUrge);
	// ���������¼
	CString strAdd;
	strAdd.Format(_T("�� ˵��%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_URGE), NULL, SND_SYNC | SND_RESOURCE);
	// ����������봰��
	m_strChat = "";
	UpdateData(FALSE);
}

/*��ݻ���-�佱�Է�*/
void CFiveDlg::OnBnClickedBtnPraise()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ������������
	CString strUrge = "������µ����~����һ��С�컨��";

	m_Table.Chat(strUrge);
	// ���������¼
	CString strAdd;
	strAdd.Format(_T("�� ˵��%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_PRAISE), NULL, SND_SYNC | SND_RESOURCE);
	// ����������봰��
	m_strChat = "";
	UpdateData(FALSE);
}

/*��ݻ���-������*/
void CFiveDlg::OnBnClickedBtnQfds()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ������������
	CString strUrge = "���������������ְ���������һ��ʤ����";

	m_Table.Chat(strUrge);
	// ���������¼
	CString strAdd;
	strAdd.Format(_T("�� ˵��%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_QFDS), NULL, SND_SYNC | SND_RESOURCE);
	// ����������봰��
	m_strChat = "";
	UpdateData(FALSE);
}

/*��ݻ���-�����ɻ�*/
void CFiveDlg::OnBnClickedBtnYh()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ������������
	CString strUrge = "�ţ�������ʲô��~";

	m_Table.Chat(strUrge);
	// ���������¼
	CString strAdd;
	strAdd.Format(_T("�� ˵��%s\r\n"), strUrge);
	m_ChatList.SetSel(-1, -1, TRUE);
	m_ChatList.ReplaceSel(strAdd);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_YH), NULL, SND_SYNC | SND_RESOURCE);
	// ����������봰��
	m_strChat = "";
	UpdateData(FALSE);
}

/*��ʼ��ʱ*/
void CFiveDlg::OnBnClickedTimer()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	if (b_review || b_suspend)
		KillTimer(2);
	b_review = FALSE;
	b_suspend = FALSE;
	n_hour = 0;
	n_minute = 0;
	n_second = 0;
	SetTimer(2, 1000, NULL);		// 2�Ŷ�ʱ����ÿ1000���루1�룩����һ��
}

/*��ʱ��*/
void CFiveDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

/*��ͣ�������ʱ*/
void CFiveDlg::OnBnClickedButtonSuspend()
{
	CString str;
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	b_suspend = !b_suspend;
	if (b_suspend)
	{
		KillTimer(2);      // ֹͣ��ʱ��
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
		SetTimer(2, 1000, NULL);		// ���¿�ʼ��ʱ
	}
}


void CFiveDlg::OnHandsoff()
{
	// TODO:  �ڴ���������������
	CHandsOffDlg dlg;
	dlg.DoModal();
}
