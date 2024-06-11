// FiveDlg.h : ͷ�ļ�
#pragma once
// ȷ����ͷ�ļ�ֻ������һ�Σ������ظ��������µı������

#include "Table.h"        // ����Table���ͷ�ļ�
#include "FiveSocket.h"   // ����FiveSocket���ͷ�ļ����Զ������
#include "afxwin.h"       // ����MFC���ĺͱ�׼�����ͷ�ļ�

// CFiveDlg �Ի����ඨ�壬�̳���CDialogEx��CDialogEx�ṩ�˶Ի����ܵ���չ
class CFiveDlg : public CDialogEx
{
    // ����
public:
    CDialog* m_pDlg;   // ָ����һ���Ի����ָ�룬����������ʾ������Ϣ����н���
    CTable m_Table;     // CTable���������ڶԻ����б�ʾĳ�ֱ��򲼾�
    CFiveDlg(CWnd* pParent = NULL); // ���캯������ѡ�ؽ���һ�������ڵ�ָ��

    SOCKET m_sClient;   // �ͻ����׽��֣���������ͨ��

    // �Ի�������
    enum { IDD = IDD_FIVE_DIALOG }; // �Ի������Դ��ʶ��

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV֧�֣��������ݽ�������֤

protected:
    HICON m_hIcon; // �Ի���ͼ��

    // ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog(); // ��ʼ���Ի���ʱ����
    afx_msg void OnPaint(); // ���ƶԻ���ʱ����
    afx_msg HCURSOR OnQueryDragIcon(); // �����϶�ͼ��ʱ����
    DECLARE_MESSAGE_MAP() // ������Ϣӳ���

public:
    // ��Ϣ��������������Ӧ�û���������˵�ѡ���ť�����
    afx_msg void OnMenuAbout(); // �����ڡ��˵���
    afx_msg void OnMenuPlayerfirst(); // ��������֡��˵���
    afx_msg void OnMenuPcfirst(); // ���������֡��˵���
    afx_msg void OnBnClickedBtnBack(); // �����ء���ť
    afx_msg void OnMenuServer(); // ����Ϊ���������˵���
    afx_msg void OnMenuClient(); // ����Ϊ�ͻ��ˡ��˵���
    afx_msg void OnMenuPlayagain(); // ������һ�֡��˵���
    afx_msg void OnMenuLeave(); // ���뿪��Ϸ���˵���
    afx_msg void OnMenuName(); // ���������ơ��˵���
    afx_msg void OnMenuStat(); // ���鿴ͳ�ơ��˵���
    afx_msg void OnClickedBtnQhq(); // ������ĳ���Զ��幦�ܵİ�ť
    afx_msg void OnClickedBtnLost(); // �����䡱��ť
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); // ���ù��ʱ����
    virtual void OnOK(); // ȷ����ť�����ʱ����
    virtual void OnCancel(); // ȡ����ť�����ʱ����
    virtual BOOL PreTranslateMessage(MSG* pMsg); // ����Ϣѭ���з�����Ϣ֮ǰ����
    BOOL RecvFile(void); // �����ļ��ĺ���

    SOCKET m_s; // �׽��֣���������ͨ��
    CEdit m_ChatList; // �����б�༭��ؼ�
    HWND m_hChat; // ���촰�ڵľ��
    CString m_strChat; // �����ַ���
    afx_msg void OnBnClickedBtnSavechess(); // ��������֡���ť
    afx_msg void OnBnClickedBtnOpen(); // ������֡���ť
    afx_msg void OnBnClickedBtnSend(); // ��������Ϣ����ť
    afx_msg void OnBnClickedBtnUrge(); // ���ߴٶ��֡���ť
    afx_msg void OnBnClickedBtnPraise(); // ��������֡���ť
    afx_msg void OnBnClickedBtnQfds(); // ������ĳ���Զ��幦�ܵİ�ť
    afx_msg void OnBnClickedBtnYh(); // ������ĳ���Զ��幦�ܵİ�ť
    CComboBox CHAT; // ����������ؼ�
    CStatic m_time; // ��ʾʱ��ľ�̬�ı��ؼ�
    afx_msg void OnBnClickedTimer(); // ��ʱ����ť����¼�
    afx_msg void OnTimer(UINT_PTR nIDEvent); // ��ʱ���¼�������

    // ʱ����صĳ�Ա����
    int n_hour; // Сʱ
    int n_minute; // ����
    int n_second; // ��
    CString s_hour; // Сʱ���ַ�����ʽ��
    CString s_minute; // ���ӣ��ַ�����ʽ��
    CString s_second; // �루�ַ�����ʽ��

    BOOL b_review; // �Ƿ��ڻع�ģʽ
    BOOL b_suspend; // �Ƿ��ڹ���״̬
    afx_msg void OnBnClickedButtonSuspend(); // ��������Ϸ����ť
    afx_msg void OnHandsoff(); // ��������Ȩ������
};
