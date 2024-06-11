// Five.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once
// 确保头文件只被包含一次，避免重复包含导致的编译错误

#include "resource.h" // 包含资源文件，通常包含应用程序的图标、菜单等资源的定义

// CFiveApp 类定义，继承自 CWinApp，CWinApp 是MFC中用于表示应用程序实例的类
class CFiveApp : public CWinApp
{
public:
    CFiveApp(); // 构造函数，用于初始化应用程序实例

    TCHAR m_szIni[MAX_PATH]; // 用于存储INI文件路径的字符数组，MAX_PATH是Windows API中定义的最大路径长度常量
    int m_nWin;  // 用于记录胜利的次数
    int m_nDraw; // 用于记录平局的次数
    int m_nLost; // 用于记录失败的次数

    // 重写
public:
    virtual BOOL InitInstance(); // 重写CWinApp的InitInstance方法，通常用于应用程序的初始化操作，如创建主窗口等

    // 实现
    DECLARE_MESSAGE_MAP() // 声明消息映射宏，用于将消息处理函数和消息映射到一起
};

extern CFiveApp theApp; // 声明一个全局的应用程序实例对象，通常在应用程序的cpp文件中定义，允许在整个程序中访问应用程序实例
