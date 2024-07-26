#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
int main() {
	//1.加载库
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA data;
	int err = WSAStartup(wVersionRequested, &data);
	if (err != 0) {
		cout << "加载库失败" << endl;
		return 1;
	}
	if (LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion) != 2) {
		cout << "库版本号错误" << endl;
		WSACleanup();//卸载错误的库
		return 1;
	}
	else {
		cout << "加载库成功" << endl;
	}
	//2.创建套接字
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		cout << "创建套接字失败：" << WSAGetLastError() << endl;
		WSACleanup();//卸载库
		return 1;
	}
	else {
		cout << "创建套接字成功" << endl;
	}
	//3.做收发的准备，创建服务端sockaddr(用服务端IP和端口号赋值)
	int nRecvNum = 0;
	int nSendNum = 0;
	char recvBuf[1024] = "";
	char SendBuf[1024] = "";
	sockaddr_in addrUDPServer;
	addrUDPServer.sin_family = AF_INET;
	addrUDPServer.sin_port = htons(12345);
	addrUDPServer.sin_addr.S_un.S_addr = inet_addr("服务端IP");
	//服务端IP，这个端口号要与服务端绑定的一致
	int addrUDPServerSize = sizeof(addrUDPServer);
	while (true)
	{
		//4.发送数据
		cin >> SendBuf;
		nSendNum = sendto(sock, SendBuf, sizeof(SendBuf), 0, (sockaddr*)&addrUDPServer, addrUDPServerSize);
		if (nSendNum == SOCKET_ERROR) {
			cout << "发送数据失败：" << WSAGetLastError() << endl;
			break;
		}
		//5.接收数据
		nRecvNum = recvfrom(sock, recvBuf, sizeof(recvBuf), 0, nullptr, nullptr);
		if (nRecvNum > 0) {
			//代表数据接收成功，打印接收到的数据
			cout << "Server " << inet_ntoa(addrUDPServer.sin_addr) << "：" << recvBuf << endl;
		}
		else if (nRecvNum == 0) {
			//连接已正常关闭，返回值为 0
			cout << "连接已断开" << endl;
			break;
		}
		else {
			cout << "接收数据失败：" << WSAGetLastError() << endl;
			break;
		}
	}
	//6.关闭套接字
	closesocket(sock);
	//7.卸载库
	WSACleanup();
}