#include <vector>
#include <string.h>
#include <unistd.h>  // read関数を使う為

#include <sys/socket.h>  // ソケット通信用 serverとclientの両方で必要
#include <error.h>  // エラー解析用
#include <netinet/in.h>  // sockaddr_in用
#include <arpa/inet.h>  // inet_addr用

// 受信とデータの表示
class TcpServer {
    public:
	TcpServer() {};

	virtual ~TcpServer() {};
	void Init();
	int Read();

    private:
	int our_sock;
	int clientSock;
};

