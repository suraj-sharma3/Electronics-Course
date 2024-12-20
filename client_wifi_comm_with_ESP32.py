""" import socket

def get_data_from_server(server_ip, server_port):
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    client_socket.connect((server_ip, server_port))

    try:
        # Send a request to the server
        request = "GET / HTTP/1.1\r\nHost: {}\r\n\r\n".format(server_ip)
        client_socket.sendall(request.encode())

        # Receive data from the server
        response = client_socket.recv(4096).decode()
        print("Received response from server: {}".format(response))
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    server_ip = "192.168.0.194"  # Replace with your ESP32 IP address
    server_port = 80  # Port to connect to the server

    get_data_from_server(server_ip, server_port)
 """
 
import socket
import time

def communicate_with_server(server_ip, server_port):
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    client_socket.connect((server_ip, server_port))

    try:
        while True:
            # Send data to the server
            message = input("Enter message to send to server: ")
            client_socket.sendall(message.encode())
            
            # Receive data from the server
            response = client_socket.recv(4096).decode()
            print("Received response from server: {}".format(response))
            
            time.sleep(1)  # Add a delay to avoid overwhelming the server
    except KeyboardInterrupt:
        print("Client disconnected.")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    server_ip = "192.168.0.194"  # Replace with your ESP32 IP address
    server_port = 80  # Port to connect to the server

    communicate_with_server(server_ip, server_port)
