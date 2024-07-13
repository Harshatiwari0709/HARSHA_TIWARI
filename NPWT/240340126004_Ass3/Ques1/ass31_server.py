import socket

def start_server():
    host = '127.0.0.1'
    port = 12345

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print('Server started. Listening for incoming connections...')

    connection, address = server_socket.accept()
    print('Connected by', address)

    while True:
        message = connection.recv(1024).decode('utf-8')
        if not message:
            break
        reversed_message = message[::-1]
        connection.sendall(reversed_message.encode('utf-8'))

    connection.close()

if __name__ == '__main__':
    start_server()