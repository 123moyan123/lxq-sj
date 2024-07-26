import socket
import os

def send_file(file_path, server_ip, server_port):
    try:
        # 创建一个TCP/IP套接字
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((server_ip, server_port))

        # 打开文件并读取数据
        with open(file_path, 'rb') as file:
            file_data = file.read()

        # 发送文件数据
        sock.sendall(file_data)

        # 关闭连接
        sock.close()

        print("success")
    except Exception as e:
        print("failed")
        print(e)

if __name__ == "__main__":
    server_ip = "10.0.8.211"
    server_port = 8080
    file_path = "/home/lxq/1.jpg"

    send_file(file_path, server_ip, server_port)
