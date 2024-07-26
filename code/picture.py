import cv2  
import os  
import time  
  
def capture_images(save_path, interval=10):  
    # 确保保存路径存在  
    if not os.path.exists(save_path):  
        os.makedirs(save_path)  
  
    # 初始化摄像头  
    cap = cv2.VideoCapture(0)  
  
    if not cap.isOpened():  
        print("Error: Unable to open camera")  
        exit()  
  
    # 计数器，用于生成文件名  
    count = 0  
  
    try:  
        while True:  
            # 读取一帧  
            ret, frame = cap.read()  
  
            if not ret:  
                print("Error: Unable to fetch frame from camera")  
                break  
  
            # 构造文件名  
            filename = f"image_{count}.jpg"  
            file_path = os.path.join(save_path, filename)  
  
            # 保存图片  
            cv2.imwrite(file_path, frame)  
            print(f"Image saved: {file_path}")  
  
            # 等待一定时间  
            time.sleep(interval)  
  
            # 更新计数器  
            count += 1  
  
    finally:  
        # 释放摄像头资源  
        cap.release()  
  
if __name__ == "__main__":  
    save_path = "D:/picture"  
    capture_images(save_path)