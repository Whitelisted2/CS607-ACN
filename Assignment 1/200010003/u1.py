from socket import *
from sys import *
import os
import threading

LINE_CLEAR = '\x1b[2K' # sequence of characters to clear line in console output

def notify(client_socket, server_ip, server_port):
    # use a highly unlikely sequence of characters for this. Perhaps, could do a 'handshake' to establish existence
    message = "HELLO-XYZ-KEYWORD-123kexplfcfworhbhcungnnufhlveiztkzrvqgcnpndryjxzvkkcejfhfudsmotkneglowhohgnyfrzlifsjmeztzmtuyrvznommtgggrkltgcyemwugwopsnbhmblmwokgkejhbmcfmwjoxsxvfsqlphjtxagtxehr"
    client_socket.sendto(message.encode(), (server_ip, server_port))

def sendfunc(client_socket, server_ip, server_port):
    # take user input to send message to server
    message = input("\rU1: ")
    client_socket.sendto(message.encode(), (server_ip, server_port))

    if message.lower() in ["exit", "quit"]:
        # terminate not only the thread, but the entire program process
        os._exit(1)

def recvfunc(client_socket):
    # process arriving messages and display to user
    data, addr = client_socket.recvfrom(1024)
    message = data.decode()
    print(end=LINE_CLEAR)
    print("\rU2:", message)
    print("U1: ", end="")

    if message.lower() in ["exit", "quit"]:
        print("quitting ...")
        os._exit(2)

def main():
    # Parsing command line arguments
    if len(argv) != 5 or (argv[1] != "-s" or argv[3] != "-p"):
        print("Usage: python3 u1.py -s <server_ip> -p <server_port-no>")
        exit(1)
    server_ip = argv[2]
    server_port = int(argv[4])

    # Creating socket
    client_socket = socket(AF_INET, SOCK_DGRAM)

    # Display basic info
    print("You are U1 (User 1) connected to server with IP", server_ip, "at port", server_port)
    print("Type \"exit\" or \"quit\" to terminate.")
    notify(client_socket, server_ip, server_port) # notify server of client's existence

    while True:
        # Run threads for sending and receiving messages
        send_thread = threading.Thread(target=sendfunc, args=(client_socket, server_ip, server_port))
        recv_thread = threading.Thread(target=recvfunc, args=(client_socket,))
        send_thread.start()
        recv_thread.start()
        
if __name__ == "__main__":
    main()