#pragma once
// ��ֹͷ�ļ��ظ�����

#include <list>
#include "Message.h" // ������Ϣ�ඨ���ļ�������������Ϸ��Ϣ����
class CTable; // ǰ������CTable�࣬����ѭ������

// CGame�ඨ�壬�̳���CObject���ṩ������Ϸ���ܵĳ���
class CGame : public CObject
{
protected:
    CTable* m_pTable; // ָ����Ϸ����ָ�룬�������ڹ�����Ϸ�е����̻���������

public:
    // ʹ�ñ�׼ģ����е�list���洢��Ϸ�����Ӳ���
    std::list<STEP> m_StepList;

public:
    // ���캯������ʼ����Ϸʱ����һ��CTableָ��
    CGame(CTable* pTable) : m_pTable(pTable) {}

    // ������������ȷ������������ܱ���ȷ����
    virtual ~CGame();

    // ���麯��Init�����ڳ�ʼ����Ϸ������ʵ�����������ṩ
    virtual void Init() = 0;

    // �麯��Win��������Ϸʤ���߼������Ա���������д
    virtual void Win(const STEP& stepSend);

    // ���麯��SendStep�����ڷ�����ҵ����Ӳ��裬����ʵ�����������ṩ
    virtual void SendStep(const STEP& stepSend) = 0;

    // ���麯��ReceiveMsg�����ڽ�����Ϣ������ʵ�����������ṩ
    virtual void ReceiveMsg(MSGSTRUCT* pMsg) = 0;

    // ���麯��Back�����ڴ���������󣬾���ʵ�����������ṩ
    virtual void Back() = 0;
};


// COneGame�ඨ�壬�̳���CGame��ʵ�ֵ�����Ϸ�߼�
class COneGame : public CGame
{
    bool m_Computer[15][15][572]; // ���Ի�ʤ�������
    bool m_Player[15][15][572]; // ��һ�ʤ�������
    int m_Win[2][572]; // ������ʤ����������������������������Ϸ״̬

    bool m_bStart; // ��Ϸ�Ƿ�ʼ�ı�־
    STEP m_step; // �������һ�ε����ӽ��

    // ������س�Ա�������������ǰ��״̬
    bool m_bOldPlayer[572];
    bool m_bOldComputer[572];
    int m_nOldWin[2][572];

public:
    COneGame(CTable* pTable) : CGame(pTable) {} // ���캯��
    virtual ~COneGame(); // ����������

    virtual void Init(); // ��ʼ����Ϸ
    virtual void SendStep(const STEP& stepSend); // �������Ӳ���
    virtual void ReceiveMsg(MSGSTRUCT* pMsg); // ������Ϣ
    virtual void Back(); // �����������

private:
    int GiveScore(const STEP& stepPut); // �������Ӻ�ķ����������������ӵĺû�
    void GetTable(int tempTable[][15], int nowTable[][15]); // ��ȡ��ǰ����״̬
    bool SearchBlank(int& i, int& j, int nowTable[][15]); // ���������ϵĿ�λ
};


// CTwoGame�ඨ�壬�̳���CGame��ʵ��˫����Ϸ�߼�
class CTwoGame : public CGame
{
public:
    CTwoGame(CTable* pTable) : CGame(pTable) {} // ���캯��
    virtual ~CTwoGame(); // ����������

    virtual void Init(); // ��ʼ����Ϸ
    virtual void Win(const STEP& stepSend); // ����ʤ���߼�����д����Win����
    virtual void SendStep(const STEP& stepSend); // �������Ӳ���
    virtual void ReceiveMsg(MSGSTRUCT* pMsg); // ������Ϣ
    virtual void Back(); // �����������
};
