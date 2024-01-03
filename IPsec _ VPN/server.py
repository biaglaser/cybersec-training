import socket
import time

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#host = socket.gethostname()
port = 12345

host = socket.gethostbyname(socket.gethostname())

server.bind(("192.168.0.104", port))

server.listen()

client, address = server.accept()
print("Client from address {} connected".format(address))

while True:
    print(client.recv(1024).decode('utf-8'))
