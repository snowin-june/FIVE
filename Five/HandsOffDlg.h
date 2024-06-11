#pragma once
// 防止该头文件在同一编译单元中被包含多次

// CHandsOffDlg 对话框类定义
class CHandsOffDlg : public CDialog
{
    DECLARE_DYNAMIC(CHandsOffDlg)
    // 这是一个MFC宏，用于在运行时提供对象的动态类型信息。
    // 它允许使用运行时类信息来创建对象，这对于实现动态创建对象很有用。

public:
    // 构造函数，可选地接受一个指向父窗口的指针，默认为NULL。
    // 这使得可以在创建对话框时指定其父窗口。
    CHandsOffDlg(CWnd* pParent = NULL);

    // 虚析构函数，确保在删除对话框对象时能够进行适当的清理。
    virtual ~CHandsOffDlg();

    // 对话框数据
    enum { IDD = IDD_HANDSOFF };
    // 定义了对话框的资源标识符，IDD_HANDSOFF是一个在资源文件中定义的常量，
    // 用于关联对话框资源模板。

protected:
    // 重写CDialog类的虚函数DoDataExchange，用于数据交换和验证。
    // DDX/DDV机制是MFC用于将控件与变量关联起来的机制，这样可以很容易地在控件和变量之间传递数据。
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
    // 声明消息映射宏。MFC使用消息映射来将窗口消息(如按键、鼠标事件等)路由到对应的处理函数。
    // 这个宏在类定义的末尾声明，用于实现消息映射的开始。
};
