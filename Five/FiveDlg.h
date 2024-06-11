// FiveDlg.h : 头文件
#pragma once
// 确保该头文件只被包含一次，避免重复包含导致的编译错误

#include "Table.h"        // 包含Table类的头文件
#include "FiveSocket.h"   // 包含FiveSocket类的头文件，自定义添加
#include "afxwin.h"       // 包含MFC核心和标准组件的头文件

// CFiveDlg 对话框类定义，继承自CDialogEx，CDialogEx提供了对话框功能的扩展
class CFiveDlg : public CDialogEx
{
    // 构造
public:
    CDialog* m_pDlg;   // 指向另一个对话框的指针，可能用于显示额外信息或进行交互
    CTable m_Table;     // CTable对象，用于在对话框中表示某种表格或布局
    CFiveDlg(CWnd* pParent = NULL); // 构造函数，可选地接受一个父窗口的指针

    SOCKET m_sClient;   // 客户端套接字，用于网络通信

    // 对话框数据
    enum { IDD = IDD_FIVE_DIALOG }; // 对话框的资源标识符

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV支持，用于数据交换和验证

protected:
    HICON m_hIcon; // 对话框图标

    // 生成的消息映射函数
    virtual BOOL OnInitDialog(); // 初始化对话框时调用
    afx_msg void OnPaint(); // 绘制对话框时调用
    afx_msg HCURSOR OnQueryDragIcon(); // 请求拖动图标时调用
    DECLARE_MESSAGE_MAP() // 声明消息映射宏

public:
    // 消息处理函数，用于响应用户操作，如菜单选项、按钮点击等
    afx_msg void OnMenuAbout(); // “关于”菜单项
    afx_msg void OnMenuPlayerfirst(); // “玩家先手”菜单项
    afx_msg void OnMenuPcfirst(); // “电脑先手”菜单项
    afx_msg void OnBnClickedBtnBack(); // “返回”按钮
    afx_msg void OnMenuServer(); // “作为服务器”菜单项
    afx_msg void OnMenuClient(); // “作为客户端”菜单项
    afx_msg void OnMenuPlayagain(); // “再玩一局”菜单项
    afx_msg void OnMenuLeave(); // “离开游戏”菜单项
    afx_msg void OnMenuName(); // “更改名称”菜单项
    afx_msg void OnMenuStat(); // “查看统计”菜单项
    afx_msg void OnClickedBtnQhq(); // 可能是某个自定义功能的按钮
    afx_msg void OnClickedBtnLost(); // “认输”按钮
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); // 设置光标时调用
    virtual void OnOK(); // 确定按钮被点击时调用
    virtual void OnCancel(); // 取消按钮被点击时调用
    virtual BOOL PreTranslateMessage(MSG* pMsg); // 在消息循环中翻译消息之前调用
    BOOL RecvFile(void); // 接收文件的函数

    SOCKET m_s; // 套接字，用于网络通信
    CEdit m_ChatList; // 聊天列表编辑框控件
    HWND m_hChat; // 聊天窗口的句柄
    CString m_strChat; // 聊天字符串
    afx_msg void OnBnClickedBtnSavechess(); // “保存棋局”按钮
    afx_msg void OnBnClickedBtnOpen(); // “打开棋局”按钮
    afx_msg void OnBnClickedBtnSend(); // “发送消息”按钮
    afx_msg void OnBnClickedBtnUrge(); // “催促对手”按钮
    afx_msg void OnBnClickedBtnPraise(); // “表扬对手”按钮
    afx_msg void OnBnClickedBtnQfds(); // 可能是某个自定义功能的按钮
    afx_msg void OnBnClickedBtnYh(); // 可能是某个自定义功能的按钮
    CComboBox CHAT; // 聊天下拉框控件
    CStatic m_time; // 显示时间的静态文本控件
    afx_msg void OnBnClickedTimer(); // 定时器按钮点击事件
    afx_msg void OnTimer(UINT_PTR nIDEvent); // 定时器事件处理函数

    // 时间相关的成员变量
    int n_hour; // 小时
    int n_minute; // 分钟
    int n_second; // 秒
    CString s_hour; // 小时（字符串格式）
    CString s_minute; // 分钟（字符串格式）
    CString s_second; // 秒（字符串格式）

    BOOL b_review; // 是否处于回顾模式
    BOOL b_suspend; // 是否处于挂起状态
    afx_msg void OnBnClickedButtonSuspend(); // “挂起游戏”按钮
    afx_msg void OnHandsoff(); // “交换手权”功能
};
