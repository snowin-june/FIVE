// Five.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
// ȷ��ͷ�ļ�ֻ������һ�Σ������ظ��������µı������

#include "resource.h" // ������Դ�ļ���ͨ������Ӧ�ó����ͼ�ꡢ�˵�����Դ�Ķ���

// CFiveApp �ඨ�壬�̳��� CWinApp��CWinApp ��MFC�����ڱ�ʾӦ�ó���ʵ������
class CFiveApp : public CWinApp
{
public:
    CFiveApp(); // ���캯�������ڳ�ʼ��Ӧ�ó���ʵ��

    TCHAR m_szIni[MAX_PATH]; // ���ڴ洢INI�ļ�·�����ַ����飬MAX_PATH��Windows API�ж�������·�����ȳ���
    int m_nWin;  // ���ڼ�¼ʤ���Ĵ���
    int m_nDraw; // ���ڼ�¼ƽ�ֵĴ���
    int m_nLost; // ���ڼ�¼ʧ�ܵĴ���

    // ��д
public:
    virtual BOOL InitInstance(); // ��дCWinApp��InitInstance������ͨ������Ӧ�ó���ĳ�ʼ���������紴�������ڵ�

    // ʵ��
    DECLARE_MESSAGE_MAP() // ������Ϣӳ��꣬���ڽ���Ϣ����������Ϣӳ�䵽һ��
};

extern CFiveApp theApp; // ����һ��ȫ�ֵ�Ӧ�ó���ʵ������ͨ����Ӧ�ó����cpp�ļ��ж��壬���������������з���Ӧ�ó���ʵ��
