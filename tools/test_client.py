import socket

# Server's IP address and port
SERVER_IP = '127.0.0.1'  
SERVER_PORT = 6969       

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
client_socket.connect((SERVER_IP, SERVER_PORT))
print("Connected to the server.")
