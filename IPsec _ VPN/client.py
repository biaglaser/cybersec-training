import socket
import time


socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip = '2.tcp.eu.ngrok.io'
port = 13728
socket.connect((ip, port))
print('Connected')

while True:
    socket.send("Hello World!".encode('utf-8'))
    print(socket.recv(1024).decode('utf-8'))
    time.sleep(3)

