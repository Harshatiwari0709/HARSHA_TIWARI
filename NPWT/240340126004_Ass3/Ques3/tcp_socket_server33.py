#!/usr/bin/env python3

import socket
import datetime

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (on-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print(f'Connected by {addr}')
        while True:
            current_datetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            conn.sendall(current_datetime.encode('utf-8'))
            data = conn.recv(1024)
            if not data:
                break
            conn.sendall(data)
            print(data)
