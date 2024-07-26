import socket
import time
import subprocess

#设置全局变量host=10.100.7.10
host="10.100.7.10"
port=12345
id="0001"

def tcp_client(server_host, server_port):
    # 创建一个socket对象
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    global port
    try:
        # 连接到服务器
        client_socket.connect((server_host, server_port))
        print(f"连接到公共服务器 {server_host}:{server_port}")
        
        while True:
            # 发送数据
            message = "GJSK0001"+id+"0000"
            client_socket.sendall(message.encode('utf-8'))
            print(f"发送数据: {message}")
            
            # 接收响应
            response = client_socket.recv(1024).decode('utf-8')
            print(f"接收到的响应: {response}")
            #如果接收到的是数字，那么把port改成这个数字
            if response.isdigit():  
                port=int(response)  
                print(f"接收到的端口号: {port}")  
                # 关闭客户端socket  
                client_socket.close() 
                #执行/home/lxq目录下的脚本文件champ.sh
                subprocess.Popen(["/home/lxq/champ.sh"])
                break 
            else:
                client_socket.close()  
                break


    except socket.error as e:
        print(f"连接或通信时发生错误: {e}")
    
    finally:
        # 关闭客户端socket
        client_socket.close()
        print("客户端socket已关闭")


    #创建一个函数，使用更新后的port连接到服务器10.100.7.10
def connect_server(host,port):
        # 创建一个socket对象
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:    
            # 连接到服务器
        client_socket.connect((host, port))
        print(f"连接到服务器 {host}:{port}")
   






        while True:
            message0="DATA"
            #发送/home/lxq/Desktop目录下sp.txt文件中最后一行的数据

            with open("/home/lxq/Desktop/sp.txt","r") as f:
                lines=f.readlines()
                last_line=lines[-1]
                message1=last_line.strip()  

            client_socket.sendall(message0+id+"0001"+message1.encode('utf-8'))
            print(f"发送数据: {message1}")
            sleep(100)


    except socket.error as e:
        print(f"连接或通信时发生错误: {e}")
    
    finally:
        # 关闭客户端socket
        client_socket.close()
        print("客户端socket已关闭")

            
if __name__ == "__main__":
    tcp_client(host,port)
    connect_server(host,port)