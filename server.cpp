#include "server.h"
#include <iostream>

int TcpServer::Read()
{
	const int max_buf = 10;
	char data_buf[max_buf];

	int mRead = read(clientSock, data_buf, sizeof(data_buf));
	uint num;

	if (mRead <= 0) {
		// perror("read error");

	} else if (mRead >= max_buf) {
		std::cout << "data over" << mRead << std::endl;

	} else
		std::cout << "read data = " << (uint)data_buf[0] << std::endl;

	num = (uint)data_buf[0];
	if (num == 0) {
		std::cout << "stop server" << std::endl;
		close(our_sock);
		close(clientSock);
	}

	return num;
}

void TcpServer::Init()
{
	// サーバー用変数
	int port = 9999;  // ポート用

	// AF_INETアドレスファミリーを使用する時は
	// sockaddr_inの構造体を使用する
	struct sockaddr_in server;

	our_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (our_sock < 0) {  // 失敗
		std::cout << "socket failed" << std::endl;
	} else
		std::cout << "socket create" << std::endl;

	// サーベーのデータ
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	// IPアドレスの指定(どんなアドレスでも可)
	server.sin_addr.s_addr = INADDR_ANY;

	// サーバーを切った後にタイムウェイトにしない
	int t = 1;
	setsockopt(our_sock, SOL_SOCKET, SO_REUSEADDR, (const sockaddr*)&t,
		   sizeof(int));

	// サーバー設定
	int Baind = bind(our_sock, (struct sockaddr*)&server, sizeof(server));
	// 失敗
	if (Baind != 0) {
		// perror("bind error");
	}

	// サーバーを接続可能にする
	// ２つ目の引数が接続可能なクライアント数 大体５から１０
	int sListen = listen(our_sock, 5);
	// 失敗
	if (sListen != 0) {
		// perror("listen error")
	}

	std::cout << "waiting connect from client" << std::endl;

	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	clientSock = accept(our_sock, (struct sockaddr*)&client, &len);
	if (clientSock < 0) {
		// perror("client error");
	}

	// サーバーに接続したクライアントのアドレスとポートの情報
	std::cout << "server status" << std::endl;
	std::cout << "addr = " << inet_ntoa(client.sin_addr) << std::endl;
	std::cout << "port = " << ntohs(client.sin_port) << std::endl;
}
