import socket
import time
import subprocess

script_path = "./champ.sh"
#47.237.25.85
def tcp_client(server_host='47.237.25.85', server_port=12345):
    # 创建一个socket对象
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        # 连接到服务器
        client_socket.connect((server_host, server_port))
        print(f"连接到服务器 {server_host}:{server_port}")
        
        while True:
            # 发送数据
            message = "0x01"
            client_socket.sendall(message.encode('utf-8'))
            print(f"发送数据: {message}")
            
            # 接收响应
            response = client_socket.recv(1024).decode('utf-8')
            print(f"接收到的响应: {response}")
            #如果接收到的数据是0x01，则启动同级目录下的111.sh脚本
            if response == "Server received data: 0x01":
                subprocess.Popen(script_path, shell=True)
                print("启动脚本")

            
                #关闭tcp连接，并退出循环
                client_socket.close()
                print("TCP连接已关闭")
                break
            # 等待1秒
            time.sleep(1)
    
    except socket.error as e:
        print(f"连接或通信时发生错误: {e}")
    
    finally:
        # 关闭客户端socket
        client_socket.close()
        print("客户端socket已关闭")

if __name__ == "__main__":
    tcp_client()

