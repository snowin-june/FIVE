#pragma once
// ��ֹͷ�ļ���ͬһ���뵥Ԫ�б���ΰ���

#include "Game.h" // ������Ϸ����Ķ���
#include "FiveSocket.h" // ��������ͨ���׽�����Ķ���

class CTable : public CWnd // CTable��̳���CWnd����ʾ����һ��������
{
    CImageList m_iml; // ���ڴ洢�͹�������ͼ���ͼ���б�
    int m_color; // ��ʾ��ǰ��ҵ�������ɫ
    BOOL m_bWait; // ���ڱ�ʾ�Ƿ��ڵȴ��Է����ӵ�״̬
    void Draw(int x, int y, int color); // ��ָ��λ�û���ָ����ɫ������

    CGame* m_pGame; // ָ����Ϸ�߼���������ָ�룬���ڶ�̬�ش�����Ϸ�߼�

public:
    // �����ս��س�Ա
    CFiveSocket m_serverSocket; // �������׽��֣����ڼ����ͽ��ܿͻ�������
    CFiveSocket m_clientSocket; // �ͻ����׽��֣��������ӷ�����
    BOOL m_bConnected; // ��ʾ�Ƿ��Ѿ��ɹ����ӵ��Է�

    void PlayAgain(); // ���¿�ʼ��Ϸ
    void GiveUp(); // ����
    void Chat(LPCTSTR lpszMsg); // ����������Ϣ
    void DrawGame(); // ������Ϸ����
    void Connect(int nGameMode); // ������Ϸģʽ��������
    void SetMenuState(BOOL bEnable); // ���ò˵�״̬

    void RestoreWait(); // �ָ��ȴ�״̬
    BOOL m_bOldWait; // �洢֮ǰ�ĵȴ�״̬
    CString m_strMe; // ����Լ�������
    CString m_strAgainst; // ���ֵ�����
    int m_data[15][15]; // �������ݣ��洢�����ϸ���λ�õ�����״̬

    CTable(); // ���캯��
    ~CTable(); // ��������
    void Clear(BOOL bWait); // �������
    void SetColor(int color); // ���������ɫ
    int GetColor() const; // ��ȡ�����ɫ
    BOOL SetWait(BOOL bWait); // ���õȴ�״̬
    void SetData(int x, int y, int color); // ����������ĳλ�õ�����״̬
    BOOL Win(int color) const; // �ж�ָ����ɫ������Ƿ��ʤ
    void SetGameMode(int nGameMode); // ������Ϸģʽ
    void Back(); // ����
    void StepOver(); // ������ǰ����
    void Accept(int nGameMode); // ������Ϸ����
    void Receive(); // ������������

protected:
    afx_msg void OnPaint(); // ���ƴ�������
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point); // ����������̧���¼�
    DECLARE_MESSAGE_MAP() // ������Ϣӳ���
};
