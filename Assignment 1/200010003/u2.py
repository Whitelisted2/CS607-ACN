from socket import *
from sys import *
import os
import threading

# some global variables that may come in handy!
addr = ""       # for notify()
reply = ""      # for better display
LINE_CLEAR = '\x1b[2K' # for line clear

def recvfunc(server_socket):
    # deal with arriving messages, similar to recvfunc() in u1.py
    global addr
    global reply
    data, addr = server_socket.recvfrom(1024)
    message = data.decode()
    # if notify() message, do nothing.
    if message == "HELLO-XYZ-KEYWORD-123kexplfcfworhbhcungnnufhlveiztkzrvqgcnpndryjxzvkkcejfhfudsmotkneglowhohgnyfrzlifsjmeztzmtuyrvznommtgggrkltgcyemwugwopsnbhmblmwokgkejhbmcfmwjoxsxvfsqlphjtxagtxehr":
        pass
    else:
        print(end=LINE_CLEAR)
        print("\rU1:", message) 
        print("U2: ", end="")
        
        if message.lower() in ["exit", "quit"]:
            print("quitting ...")
            os._exit(1)

def sendfunc(server_socket):
    # manage sending messages to client, similar to sendfunc() in u1.py
    global reply
    global addr
    reply = input("\rU2: ")
    server_socket.sendto(reply.encode(), addr)
    if reply.lower() in ["exit", "quit"]:
        print("quitting ...")
        os._exit(2)

def main():
    # Parse command line arguments
    if len(argv) != 3 or argv[1] != "-p":
        print("Usage: python3 u2.py -p <port-no>")
        exit(1)
    port = int(argv[2])

    # Create socket
    server_socket = socket(AF_INET, SOCK_DGRAM)
    # server_ip = str(gethostbyaddr(gethostname()))
    # print("ip=",server_ip)
    server_socket.bind(("0.0.0.0", port))
    # server_socket.bind((server_ip, port))
    print("You are U2 (User 2) ready to connect to port number", port, "of the client(s)")

    while True:
        # Run threads for sending and receiving messages
        send_thread = threading.Thread(target=sendfunc, args=(server_socket,))
        recv_thread = threading.Thread(target=recvfunc, args=(server_socket,))
        send_thread.start()
        recv_thread.start()

if __name__ == "__main__":
    main()
