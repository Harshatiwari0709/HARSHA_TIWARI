import socket

def start_server(port):
    # Create a socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to a specific address and port
    server_address = ('localhost', port)
    server_socket.bind(server_address)

    # Listen for incoming connections
    server_socket.listen(1)
    print(f"Echo server started on port {port}. Waiting for connections...")

    while True:
        # Accept an incoming connection
        connection, client_address = server_socket.accept()
        print(f"Connected to {client_address}")

        try:
            # Receive data from the client
            while True:
                data = connection.recv(1024)
                if not data:
                    break
                print(f"Received: {data.decode()}")

                # Echo the data back to the client
                connection.sendall(data)
        finally:
            # Close the connection
            connection.close()

if __name__ == "__main__":
    port = 8080  # Specify the port to listen on
    start_server(port)