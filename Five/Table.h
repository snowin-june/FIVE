#pragma once
// 防止头文件在同一编译单元中被多次包含

#include "Game.h" // 包含游戏基类的定义
#include "FiveSocket.h" // 包含网络通信套接字类的定义

class CTable : public CWnd // CTable类继承自CWnd，表示它是一个窗口类
{
    CImageList m_iml; // 用于存储和管理棋子图像的图像列表
    int m_color; // 表示当前玩家的棋子颜色
    BOOL m_bWait; // 用于表示是否处于等待对方落子的状态
    void Draw(int x, int y, int color); // 在指定位置绘制指定颜色的棋子

    CGame* m_pGame; // 指向游戏逻辑处理基类的指针，用于多态地处理游戏逻辑

public:
    // 网络对战相关成员
    CFiveSocket m_serverSocket; // 服务器套接字，用于监听和接受客户端连接
    CFiveSocket m_clientSocket; // 客户端套接字，用于连接服务器
    BOOL m_bConnected; // 表示是否已经成功连接到对方

    void PlayAgain(); // 重新开始游戏
    void GiveUp(); // 认输
    void Chat(LPCTSTR lpszMsg); // 发送聊天消息
    void DrawGame(); // 绘制游戏界面
    void Connect(int nGameMode); // 根据游戏模式连接网络
    void SetMenuState(BOOL bEnable); // 设置菜单状态

    void RestoreWait(); // 恢复等待状态
    BOOL m_bOldWait; // 存储之前的等待状态
    CString m_strMe; // 玩家自己的名字
    CString m_strAgainst; // 对手的名字
    int m_data[15][15]; // 棋盘数据，存储棋盘上各个位置的棋子状态

    CTable(); // 构造函数
    ~CTable(); // 析构函数
    void Clear(BOOL bWait); // 清除棋盘
    void SetColor(int color); // 设置玩家颜色
    int GetColor() const; // 获取玩家颜色
    BOOL SetWait(BOOL bWait); // 设置等待状态
    void SetData(int x, int y, int color); // 设置棋盘上某位置的棋子状态
    BOOL Win(int color) const; // 判断指定颜色的玩家是否获胜
    void SetGameMode(int nGameMode); // 设置游戏模式
    void Back(); // 悔棋
    void StepOver(); // 结束当前步骤
    void Accept(int nGameMode); // 接受游戏邀请
    void Receive(); // 接收网络数据

protected:
    afx_msg void OnPaint(); // 绘制窗口内容
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point); // 处理鼠标左键抬起事件
    DECLARE_MESSAGE_MAP() // 声明消息映射宏
};
