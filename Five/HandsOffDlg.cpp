// HandsOffDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Five.h"
#include "HandsOffDlg.h"
#include "afxdialogex.h"


// CHandsOffDlg 对话框

IMPLEMENT_DYNAMIC(CHandsOffDlg, CDialog)

CHandsOffDlg::CHandsOffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHandsOffDlg::IDD, pParent)
{

}

CHandsOffDlg::~CHandsOffDlg()
{
}

void CHandsOffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHandsOffDlg, CDialog)
END_MESSAGE_MAP()


// CHandsOffDlg 消息处理程序
