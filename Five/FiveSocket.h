// CFiveSocket ����
#pragma once
// ȷ��ͷ�ļ�ֻ������һ�Σ������ظ��������µı������

// CFiveSocket ��̳��� CAsyncSocket�����ڴ�������ͨ��
class CFiveSocket : public CAsyncSocket
{
public:
    CFiveSocket(); // ���캯�������ڳ�ʼ��CFiveSocket����
    virtual ~CFiveSocket(); // ������������ȷ�������ٶ���ʱ�ܹ���ȷ������Դ

protected:
    // ����Ϊ��д��CAsyncSocket���麯�������ڴ���ͬ�������¼�

    virtual void OnAccept(int nErrorCode);
    // ���׽���׼������һ����������ʱ���á�
    // nErrorCode ��������ָʾ�����Ƿ�ɹ���ɣ�0 ��ʾ�ɹ���

    virtual void OnConnect(int nErrorCode);
    // ���׽��������������ʱ���á�
    // nErrorCode ��������ָʾ���ӳ����Ƿ�ɹ���0 ��ʾ�ɹ���

    virtual void OnReceive(int nErrorCode);
    // ���׽���׼���ý�������ʱ���á�
    // nErrorCode ��������ָʾ���ղ����Ƿ�ɹ���0 ��ʾ�ɹ���
    // ͨ������������б�д��������ȡ�������Ͻ��յ����ݡ�

    virtual void OnClose(int nErrorCode);
    // ���׽��ֹر�ʱ���á�
    // nErrorCode ��������ָʾ�رղ����Ƿ�ɹ���0 ��ʾ�ɹ���
    // �����������ͨ��������Դ�ͷź����������
};
