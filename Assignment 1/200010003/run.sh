#!/bin/bash

### Instructions (IMPORTANT). Note that these would generally be in the README, but is also placed here due to the mildly unconventional assignment instructions.
# 1. Start the server code (u2.py) BEFORE the client code (u1.py) in TWO SEPARATE TERMINALS.
# 2. To start the server and client with some default settings, run "bash run.sh server" and "bash run.sh client" in separate terminals.
# 3. To run manually with specific IP/port, refer to instructions provided at the end of this file.
# 4. To exit the chat program, type "exit" or "quit" on either terminal.

which=$1
port_num=7902;
ip_addr="127.0.1.1";

if [ $1 == "server" ]; then
    python3 u2.py -p $port_num;
elif [ $1 == "client" ]; then
    python3 u1.py -s $ip_addr -p $port_num;
fi

### MANUAL RUN INSTRUCTIONS (also provided in markdown)
# Server Usage: python3 u2.py -p <port-no>
# Client Usage: python3 u1.py -s <server_ip> -p <server_port-no>
