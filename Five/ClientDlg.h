#pragma once
// 确保头文件只被包含一次，避免重复包含导致的编译错误

#include "Table.h"  // 包含Table类的声明，这个类在本对话框类中将被用到

// CClientDlg 对话框类定义，继承自MFC的CDialog类，用于创建和管理对话框界面
class CClientDlg : public CDialog
{
    DECLARE_DYNAMIC(CClientDlg) // 启用运行时类信息，允许动态创建对象

public:
    // 构造函数，可选地接受一个指向父窗口的指针，默认为NULL
    CClientDlg(CWnd* pParent = NULL);

    // 虚析构函数，保证对象析构时能正确调用派生类的析构函数
    virtual ~CClientDlg();

    // 对话框数据，IDD为对话框资源标识符，用于关联对话框模板
    enum { IDD = IDD_DLG_CLIENT };

protected:
    // DDX/DDV支持，用于数据交换和验证，通常在此函数中关联控件变量
    virtual void DoDataExchange(CDataExchange* pDX);

    // 声明消息映射宏，用于将消息处理函数和消息映射到一起
    DECLARE_MESSAGE_MAP()

protected:
    // 消息处理函数，用于响应按钮点击等事件
    afx_msg void OnClickedBtnConnect(); // 处理连接按钮点击事件
    afx_msg void OnClickedBtnOut(); // 处理退出按钮点击事件
    afx_msg void OnUpdateEditHost(); // 可能用于处理编辑框内容更新事件
    virtual BOOL OnInitDialog(); // 初始化对话框时调用，用于设置初始状态
    afx_msg void OnTimer(UINT_PTR nIDEvent); // 处理定时器事件
    virtual void OnOK(); // 处理确定按钮点击事件，可能会重写默认行为

private:
    int m_nTimer; // 定时器标识符，用于管理定时器
    CTable* m_pTable; // 指向CTable对象的指针，可能用于在对话框中显示和管理表格数据
};
