#pragma once
// ��ֹ��ͷ�ļ���ͬһ���뵥Ԫ�б���ΰ���

// CServerDlg �Ի����ඨ��
class CServerDlg : public CDialog
{
    DECLARE_DYNAMIC(CServerDlg)
    // MFC�꣬����������ʱ�ṩ����Ķ�̬������Ϣ��������MFC���������ʱ��������

public:
    // ���캯������ѡ�ؽ���һ��ָ�򸸴��ڵ�ָ�룬Ĭ��ΪNULL��
    // ��ʹ�ÿ����ڴ����Ի���ʱָ���丸���ڡ�
    CServerDlg(CWnd* pParent = NULL);

    // ������������ȷ����ɾ���Ի������ʱ�ܹ������ʵ�������
    virtual ~CServerDlg();

    // �Ի�������
    enum { IDD = IDD_DLG_SERVER };
    // �����˶Ի������Դ��ʶ����IDD_DLG_SERVER��һ������Դ�ļ��ж���ĳ�����
    // ���ڹ����Ի�����Դģ�塣

protected:
    // ��дCDialog����麯��DoDataExchange���������ݽ�������֤��
    // DDX/DDV������MFC���ڽ��ؼ���������������Ļ��ƣ��������Ժ����׵��ڿؼ��ͱ���֮�䴫�����ݡ�
    virtual void DoDataExchange(CDataExchange* pDX);

    // ��Ϣ��������������Ӧ��ť����¼�
    afx_msg void OnClickedBtnListen(); // ������������ť�����ʱ����
    afx_msg void OnClickedBtnLeave(); // �����뿪����ť�����ʱ����

    // ��ʼ���Ի���ʱ���õĺ������������öԻ���ĳ�ʼ״̬����Ĭ��ֵ�ȡ�
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
    // ������Ϣӳ��꣬MFCʹ����Ϣӳ�佫������Ϣ���簴��������¼��ȣ�·�ɵ���Ӧ�Ĵ�������
};
