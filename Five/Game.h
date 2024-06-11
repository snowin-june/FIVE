#pragma once
// 防止头文件重复包含

#include <list>
#include "Message.h" // 包含消息类定义文件，可能用于游戏消息传递
class CTable; // 前置声明CTable类，避免循环依赖

// CGame类定义，继承自CObject，提供基本游戏功能的抽象
class CGame : public CObject
{
protected:
    CTable* m_pTable; // 指向游戏表格的指针，可能用于管理游戏中的棋盘或其他布局

public:
    // 使用标准模板库中的list来存储游戏的落子步骤
    std::list<STEP> m_StepList;

public:
    // 构造函数，初始化游戏时接受一个CTable指针
    CGame(CTable* pTable) : m_pTable(pTable) {}

    // 虚析构函数，确保派生类对象能被正确析构
    virtual ~CGame();

    // 纯虚函数Init，用于初始化游戏，具体实现由派生类提供
    virtual void Init() = 0;

    // 虚函数Win，处理游戏胜利逻辑，可以被派生类重写
    virtual void Win(const STEP& stepSend);

    // 纯虚函数SendStep，用于发送玩家的落子步骤，具体实现由派生类提供
    virtual void SendStep(const STEP& stepSend) = 0;

    // 纯虚函数ReceiveMsg，用于接收消息，具体实现由派生类提供
    virtual void ReceiveMsg(MSGSTRUCT* pMsg) = 0;

    // 纯虚函数Back，用于处理悔棋请求，具体实现由派生类提供
    virtual void Back() = 0;
};


// COneGame类定义，继承自CGame，实现单人游戏逻辑
class COneGame : public CGame
{
    bool m_Computer[15][15][572]; // 电脑获胜组合数组
    bool m_Player[15][15][572]; // 玩家获胜组合数组
    int m_Win[2][572]; // 各个获胜组合中填入的棋子数，用于评估游戏状态

    bool m_bStart; // 游戏是否开始的标志
    STEP m_step; // 保存最近一次的落子结果

    // 悔棋相关成员变量，保存悔棋前的状态
    bool m_bOldPlayer[572];
    bool m_bOldComputer[572];
    int m_nOldWin[2][572];

public:
    COneGame(CTable* pTable) : CGame(pTable) {} // 构造函数
    virtual ~COneGame(); // 虚析构函数

    virtual void Init(); // 初始化游戏
    virtual void SendStep(const STEP& stepSend); // 发送落子步骤
    virtual void ReceiveMsg(MSGSTRUCT* pMsg); // 接收消息
    virtual void Back(); // 处理悔棋请求

private:
    int GiveScore(const STEP& stepPut); // 给出落子后的分数，用于评估落子的好坏
    void GetTable(int tempTable[][15], int nowTable[][15]); // 获取当前棋盘状态
    bool SearchBlank(int& i, int& j, int nowTable[][15]); // 搜索棋盘上的空位
};


// CTwoGame类定义，继承自CGame，实现双人游戏逻辑
class CTwoGame : public CGame
{
public:
    CTwoGame(CTable* pTable) : CGame(pTable) {} // 构造函数
    virtual ~CTwoGame(); // 虚析构函数

    virtual void Init(); // 初始化游戏
    virtual void Win(const STEP& stepSend); // 处理胜利逻辑，重写基类Win函数
    virtual void SendStep(const STEP& stepSend); // 发送落子步骤
    virtual void ReceiveMsg(MSGSTRUCT* pMsg); // 接收消息
    virtual void Back(); // 处理悔棋请求
};
