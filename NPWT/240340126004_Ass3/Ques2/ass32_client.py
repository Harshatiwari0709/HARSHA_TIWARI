import socket

def send_message(host, port, message):
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    server_address = (host, port)
    client_socket.connect(server_address)

    try:
        # Send the message to the server
        client_socket.sendall(message.encode())

        # Receive the echoed message from the server
        response = client_socket.recv(1024)
        print(f"Received response: {response.decode()}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    host = 'localhost'
    port = 8080
    message = "Hello Harsha...... echo server is started!!!!!1"
    send_message(host, port, message)