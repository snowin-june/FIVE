#pragma once
// ȷ��ͷ�ļ�ֻ������һ�Σ������ظ��������µı������

#include "Table.h"  // ����Table���������������ڱ��Ի������н����õ�

// CClientDlg �Ի����ඨ�壬�̳���MFC��CDialog�࣬���ڴ����͹���Ի������
class CClientDlg : public CDialog
{
    DECLARE_DYNAMIC(CClientDlg) // ��������ʱ����Ϣ������̬��������

public:
    // ���캯������ѡ�ؽ���һ��ָ�򸸴��ڵ�ָ�룬Ĭ��ΪNULL
    CClientDlg(CWnd* pParent = NULL);

    // ��������������֤��������ʱ����ȷ�������������������
    virtual ~CClientDlg();

    // �Ի������ݣ�IDDΪ�Ի�����Դ��ʶ�������ڹ����Ի���ģ��
    enum { IDD = IDD_DLG_CLIENT };

protected:
    // DDX/DDV֧�֣��������ݽ�������֤��ͨ���ڴ˺����й����ؼ�����
    virtual void DoDataExchange(CDataExchange* pDX);

    // ������Ϣӳ��꣬���ڽ���Ϣ����������Ϣӳ�䵽һ��
    DECLARE_MESSAGE_MAP()

protected:
    // ��Ϣ��������������Ӧ��ť������¼�
    afx_msg void OnClickedBtnConnect(); // �������Ӱ�ť����¼�
    afx_msg void OnClickedBtnOut(); // �����˳���ť����¼�
    afx_msg void OnUpdateEditHost(); // �������ڴ���༭�����ݸ����¼�
    virtual BOOL OnInitDialog(); // ��ʼ���Ի���ʱ���ã��������ó�ʼ״̬
    afx_msg void OnTimer(UINT_PTR nIDEvent); // ����ʱ���¼�
    virtual void OnOK(); // ����ȷ����ť����¼������ܻ���дĬ����Ϊ

private:
    int m_nTimer; // ��ʱ����ʶ�������ڹ���ʱ��
    CTable* m_pTable; // ָ��CTable�����ָ�룬���������ڶԻ�������ʾ�͹���������
};
