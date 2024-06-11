#pragma once
// 防止头文件在同一编译单元中被包含多次

// 定义一步棋的数据结构
typedef struct tagStep {
    int x;      // 棋子的x坐标（水平位置）
    int y;      // 棋子的y坐标（垂直位置）
    int color;  // 棋子的颜色（或所属玩家）
} STEP;

// 定义消息结构，用于在游戏中传递消息
typedef struct tagMsgStruct {
    UINT uMsg;       // 消息ID，用于区分不同类型的消息
    int x;           // 棋子的x坐标
    int y;           // 棋子的y坐标
    int color;       // 棋子的颜色
    TCHAR szMsg[128];// 消息内容，用于传递文本消息，如聊天
} MSGSTRUCT;

// 定义客户端之间交换的数据包结构
typedef struct _clientpacket {
    int     type;   // 数据包的类型
    u_short len;    // 数据包长度（仅包含包体的长度）
    u_short xPos;   // 下棋的水平位置
    u_short yPos;   // 下棋的垂直位置
} CLIENTPACKET, * PCLIENTPACKET;

// 定义各种消息宏，用于标识游戏中的不同动作和事件
#define MSG_DROPDOWN     0x01 // 落子
#define MSG_ROLLBACK     0x02 // 悔棋请求
#define MSG_AGREEBACK    0x03 // 同意悔棋
#define MSG_REFUSEDBACK  0x04 // 拒绝悔棋
#define MSG_DRAW         0x05 // 请求和棋
#define MSG_AGREEDRAW    0x06 // 同意和棋
#define MSG_REFUSEDRAW   0x07 // 拒绝和棋
#define MSG_GIVEUP       0x08 // 认输
#define MSG_CHAT         0x09 // 聊天消息
#define MSG_OPPOSITE     0x0a // 对手信息，可能用于交换对手玩家的数据
#define MSG_PLAYAGAIN    0x0b // 请求再次开局
#define MSG_AGREEAGAIN   0x0c // 同意再次开局
#define WENJIAN          153  // 文件传输（未在注释中明确用途）
#define SEND_BUFFER_SIZE 512  // 发送缓冲区大小
#define RECV_BUFFER_SIZE 4096 // 接收缓冲区大小
#define CLIENTPACKETLEN  (sizeof(CLIENTPACKET)) // 数据包长度，即CLIENTPACKET结构体的大小
