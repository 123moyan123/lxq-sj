#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
int main() {
	//1.加载库
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA data;
	int err = WSAStartup(wVersion, &data);
	if (err != 0) {
		cout << "加载库失败" << endl;
		return 1;
	}
	else if (LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion) != 2) {
		cout << "库版本号错误" << endl;
		WSACleanup();//卸载错误的库
		return 1;
	}
	else {
		cout << "加载库成功" << endl;
	}
	//2.创建socket
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//阅读帮助文档了解具体含义，三个参数均为宏定义或枚举类型
	if (sock == INVALID_SOCKET) {
		cout << "创建套接字失败：" << WSAGetLastError() << endl;
		//如果日志中出现错误，上方工具栏->错误查找->输入编号
		WSACleanup();//卸载库
		return 1;
	}
	else {
		cout << "创建套接字成功" << endl;
	}
	//3.创建服务端sockaddr，socket绑定服务端的IP和端口号
	sockaddr_in addrUDPServer;
	addrUDPServer.sin_family = AF_INET;
	addrUDPServer.sin_port = htons(12345);
	addrUDPServer.sin_addr.S_un.S_addr = INADDR_ANY;//用这宏定义绑定所有网卡
	err = bind(sock, (sockaddr*)&addrUDPServer, sizeof(addrUDPServer));
	if (err == SOCKET_ERROR) {
		cout << "绑定失败：" << WSAGetLastError() << endl;
		closesocket(sock);//关闭套接字
		WSACleanup();//卸载库
		return 1;
	}
	else {
		cout << "绑定成功" << endl;
	}
	//4.做收发的准备，创建客户端sockaddr(不用赋值)
	int nRecvNum = 0;//储存接收到的数据的大小
	int nSendNum = 0;//储存要发送数据的大小
	char recvBuf[1024] = "";//储存接收的数据
	char SendBuf[1024] = "";//储存发送的数据
	sockaddr_in addrUDPClient;
	int addrUDPClientSize = sizeof(addrUDPClient);
	while (true)
	{
		//5.接收数据
		nRecvNum = recvfrom(sock, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&addrUDPClient, &addrUDPClientSize);
		//注意recvfrom的最后一个参数是int*类型，接收数据时，由于接收到的数据长度是动态变化的，因此使用指针传递长度信息能够更好地应对这种情况（动态更新）。
		if (nRecvNum > 0) {
			//代表数据接收成功，打印接收到的数据		
			cout << "Client " << inet_ntoa(addrUDPClient.sin_addr) << "：" << recvBuf << endl;
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
		//6.发送数据
		cin >> SendBuf;
		nSendNum = sendto(sock, SendBuf, sizeof(SendBuf), 0, (sockaddr*)&addrUDPClient, addrUDPClientSize);
		//注意sendto的最后一个参数是int类型，在发送数据时，通常已经知道目标地址结构体的长度，所以用int就行
		if (nSendNum == SOCKET_ERROR) {
			cout << "发送数据失败：" << WSAGetLastError() << endl;
			break;
		}
	}
 
	//7.关闭套接字
	closesocket(sock);
	//8.卸载库
	WSACleanup();
}