#pragma once
// ��ֹͷ�ļ���ͬһ���뵥Ԫ�б��������

// ����һ��������ݽṹ
typedef struct tagStep {
    int x;      // ���ӵ�x���꣨ˮƽλ�ã�
    int y;      // ���ӵ�y���꣨��ֱλ�ã�
    int color;  // ���ӵ���ɫ����������ң�
} STEP;

// ������Ϣ�ṹ����������Ϸ�д�����Ϣ
typedef struct tagMsgStruct {
    UINT uMsg;       // ��ϢID���������ֲ�ͬ���͵���Ϣ
    int x;           // ���ӵ�x����
    int y;           // ���ӵ�y����
    int color;       // ���ӵ���ɫ
    TCHAR szMsg[128];// ��Ϣ���ݣ����ڴ����ı���Ϣ��������
} MSGSTRUCT;

// ����ͻ���֮�佻�������ݰ��ṹ
typedef struct _clientpacket {
    int     type;   // ���ݰ�������
    u_short len;    // ���ݰ����ȣ�����������ĳ��ȣ�
    u_short xPos;   // �����ˮƽλ��
    u_short yPos;   // ����Ĵ�ֱλ��
} CLIENTPACKET, * PCLIENTPACKET;

// ���������Ϣ�꣬���ڱ�ʶ��Ϸ�еĲ�ͬ�������¼�
#define MSG_DROPDOWN     0x01 // ����
#define MSG_ROLLBACK     0x02 // ��������
#define MSG_AGREEBACK    0x03 // ͬ�����
#define MSG_REFUSEDBACK  0x04 // �ܾ�����
#define MSG_DRAW         0x05 // �������
#define MSG_AGREEDRAW    0x06 // ͬ�����
#define MSG_REFUSEDRAW   0x07 // �ܾ�����
#define MSG_GIVEUP       0x08 // ����
#define MSG_CHAT         0x09 // ������Ϣ
#define MSG_OPPOSITE     0x0a // ������Ϣ���������ڽ���������ҵ�����
#define MSG_PLAYAGAIN    0x0b // �����ٴο���
#define MSG_AGREEAGAIN   0x0c // ͬ���ٴο���
#define WENJIAN          153  // �ļ����䣨δ��ע������ȷ��;��
#define SEND_BUFFER_SIZE 512  // ���ͻ�������С
#define RECV_BUFFER_SIZE 4096 // ���ջ�������С
#define CLIENTPACKETLEN  (sizeof(CLIENTPACKET)) // ���ݰ����ȣ���CLIENTPACKET�ṹ��Ĵ�С
