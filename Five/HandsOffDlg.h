#pragma once
// ��ֹ��ͷ�ļ���ͬһ���뵥Ԫ�б��������

// CHandsOffDlg �Ի����ඨ��
class CHandsOffDlg : public CDialog
{
    DECLARE_DYNAMIC(CHandsOffDlg)
    // ����һ��MFC�꣬����������ʱ�ṩ����Ķ�̬������Ϣ��
    // ������ʹ������ʱ����Ϣ���������������ʵ�ֶ�̬������������á�

public:
    // ���캯������ѡ�ؽ���һ��ָ�򸸴��ڵ�ָ�룬Ĭ��ΪNULL��
    // ��ʹ�ÿ����ڴ����Ի���ʱָ���丸���ڡ�
    CHandsOffDlg(CWnd* pParent = NULL);

    // ������������ȷ����ɾ���Ի������ʱ�ܹ������ʵ�������
    virtual ~CHandsOffDlg();

    // �Ի�������
    enum { IDD = IDD_HANDSOFF };
    // �����˶Ի������Դ��ʶ����IDD_HANDSOFF��һ������Դ�ļ��ж���ĳ�����
    // ���ڹ����Ի�����Դģ�塣

protected:
    // ��дCDialog����麯��DoDataExchange���������ݽ�������֤��
    // DDX/DDV������MFC���ڽ��ؼ���������������Ļ��ƣ��������Ժ����׵��ڿؼ��ͱ���֮�䴫�����ݡ�
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
    // ������Ϣӳ��ꡣMFCʹ����Ϣӳ������������Ϣ(�簴��������¼���)·�ɵ���Ӧ�Ĵ�������
    // ��������ඨ���ĩβ����������ʵ����Ϣӳ��Ŀ�ʼ��
};
