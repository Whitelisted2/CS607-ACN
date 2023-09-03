The goal of this project is to implement a simple talk (2-users) application, between
two users called U1 and U2. Assume that U2 is running the server to which U1 will connect. The
two users can be in two different terminal windows on the same machine or on different
machines.

Google Drive Link for Video Demonstration: https://drive.google.com/drive/folders/1eyGV3BrqBhzQ0rSph_1CSiGAl8VD-MFH?usp=sharing 

## Directory Structure (and brief description of files)

The files included are:
- u1.py: This python file functions as the client user.
- u2.py: This python file functions as the server user.
- README.md: Self-explanatory. Contains info about files, functions, and running code.
- run.sh: This bash script has methods to run the code with pre-defined or user-defined settings.
- output (directory): images and files of sample input/output

## Functions of+in each python script file

- u1.py: This file functions as the client-side of UDP Talk application.
  1. notify(): This function notifies the server about the client's existence, so that the server can end the conversation immediately if it wishes to do so.
  2. sendfunc(): This function deals with sending messages to the server.
  3. recvfunc(): This function deals with receiving messages from the server.
  4. main(): This function is the HQ of all of the file's operations, creating threads for parallel sending and receiving of messages.


- u2.py: This file functions as the server-side of UDP Talk application.
  1. sendfunc(): This function deals with sending messages to the client.
  2. recvfunc(): This function deals with receiving messages from the client.
  3. main(): This function is the HQ of all of the file's operations, creating threads for parallel sending and receiving of messages.


## Instructions on running code

1. Start the server code (u2.py) BEFORE the client code (u1.py) in TWO SEPARATE TERMINALS.
2. To start the server and client with some default settings, run `bash run.sh server` and `bash run.sh client` in separate terminals.
3. To run manually with specific IP/port:
  - Server Usage: `python3 u2.py -p <port-no>`
  - Client Usage: `python3 u1.py -s <server_ip> -p <server_port-no>`
4. To exit the chat program, enter "exit" or "quit" on either terminal.



> "The Network is the Computer" - John Gage