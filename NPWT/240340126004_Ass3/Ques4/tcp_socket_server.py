#!/usr/bin/env python3

import socket
import threading

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (on-privileged ports are > 1023)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen()

clients = []

def broadcast(message):
    for client in clients:
        client.send(message)

def handle_client(client):
    while True:
        try:
            message = client.recv(1024)
            broadcast(message)
        except:
            index = clients.index(client)
            clients.remove(client)
            client.close()
            break

print("Server is listening...")
while True:
    client, address = server.accept()
    print(f"Connected by {address}")
    clients.append(client)
    client.send("Welcome to the chat!".encode('ascii'))
    thread = threading.Thread(target=handle_client, args=(client,))
    thread.start()
