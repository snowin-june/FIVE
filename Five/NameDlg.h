#pragma once
// ��ֹͷ�ļ���ͬһ���뵥Ԫ�б���ΰ���

// CNameDlg �Ի����ඨ��
class CNameDlg : public CDialog
{
    DECLARE_DYNAMIC(CNameDlg)
    // MFC�꣬�ṩ����ʱ����Ϣ��ʹ�ÿ���������ʱ��������

    TCHAR m_strName[15]; // ����һ���ַ����飬���ڴ洢��������ƣ�TCHAR�Ǹ���Unicode��ANSI�������þ������ַ�����

public:
    // ���캯������ѡ�ؽ���һ��ָ�򸸴��ڵ�ָ�룬Ĭ��ΪNULL
    CNameDlg(CWnd* pParent = NULL);

    // ������������ȷ����ɾ���Ի������ʱ�ܹ������ʵ�������
    virtual ~CNameDlg();

    // �Ի�������
    enum { IDD = IDD_DLG_NAME };
    // �����˶Ի������Դ��ʶ����IDD_DLG_NAME��һ������Դ�ļ��ж���ĳ�����
    // ���ڹ����Ի�����Դģ��

protected:
    // ��дCDialog����麯��DoDataExchange���������ݽ�������֤
    // DDX/DDV������MFC���ڽ��ؼ���������������Ļ��ƣ��������Ժ����׵��ڿؼ��ͱ���֮�䴫������
    virtual void DoDataExchange(CDataExchange* pDX);

    // ��Ϣ��������������Ӧ�༭�����ݵĸ����¼�
    afx_msg void OnUpdateEditName();

    // ��ʼ���Ի���ʱ���õĺ������������öԻ���ĳ�ʼ״̬����Ĭ��ֵ��
    virtual BOOL OnInitDialog();

    // ���û����ȷ����ťʱ���õĺ��������ڴ���ȷ����ť�ĵ���¼�
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
    // ������Ϣӳ��꣬MFCʹ����Ϣӳ�佫������Ϣ���簴��������¼��ȣ�·�ɵ���Ӧ�Ĵ�����
};
