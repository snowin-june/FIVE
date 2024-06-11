// CFiveSocket 定义
#pragma once
// 确保头文件只被包含一次，避免重复包含导致的编译错误

// CFiveSocket 类继承自 CAsyncSocket，用于处理网络通信
class CFiveSocket : public CAsyncSocket
{
public:
    CFiveSocket(); // 构造函数，用于初始化CFiveSocket对象
    virtual ~CFiveSocket(); // 虚析构函数，确保在销毁对象时能够正确清理资源

protected:
    // 以下为重写自CAsyncSocket的虚函数，用于处理不同的网络事件

    virtual void OnAccept(int nErrorCode);
    // 当套接字准备接受一个连接请求时调用。
    // nErrorCode 参数用于指示操作是否成功完成，0 表示成功。

    virtual void OnConnect(int nErrorCode);
    // 当套接字完成连接请求时调用。
    // nErrorCode 参数用于指示连接尝试是否成功，0 表示成功。

    virtual void OnReceive(int nErrorCode);
    // 当套接字准备好接收数据时调用。
    // nErrorCode 参数用于指示接收操作是否成功，0 表示成功。
    // 通常在这个函数中编写代码来读取从网络上接收的数据。

    virtual void OnClose(int nErrorCode);
    // 当套接字关闭时调用。
    // nErrorCode 参数用于指示关闭操作是否成功，0 表示成功。
    // 在这个函数中通常进行资源释放和清理操作。
};
