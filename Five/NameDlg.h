#pragma once
// 防止头文件在同一编译单元中被多次包含

// CNameDlg 对话框类定义
class CNameDlg : public CDialog
{
    DECLARE_DYNAMIC(CNameDlg)
    // MFC宏，提供运行时类信息，使得可以在运行时创建对象

    TCHAR m_strName[15]; // 定义一个字符数组，用于存储输入的名称，TCHAR是根据Unicode和ANSI编译设置决定的字符类型

public:
    // 构造函数，可选地接受一个指向父窗口的指针，默认为NULL
    CNameDlg(CWnd* pParent = NULL);

    // 虚析构函数，确保在删除对话框对象时能够进行适当的清理
    virtual ~CNameDlg();

    // 对话框数据
    enum { IDD = IDD_DLG_NAME };
    // 定义了对话框的资源标识符，IDD_DLG_NAME是一个在资源文件中定义的常量，
    // 用于关联对话框资源模板

protected:
    // 重写CDialog类的虚函数DoDataExchange，用于数据交换和验证
    // DDX/DDV机制是MFC用于将控件与变量关联起来的机制，这样可以很容易地在控件和变量之间传递数据
    virtual void DoDataExchange(CDataExchange* pDX);

    // 消息处理函数，用于响应编辑框内容的更新事件
    afx_msg void OnUpdateEditName();

    // 初始化对话框时调用的函数，用于设置对话框的初始状态，如默认值等
    virtual BOOL OnInitDialog();

    // 当用户点击确定按钮时调用的函数，用于处理确定按钮的点击事件
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
    // 声明消息映射宏，MFC使用消息映射将窗口消息（如按键、鼠标事件等）路由到对应的处理函数
};
