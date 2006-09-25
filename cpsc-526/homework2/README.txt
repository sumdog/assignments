cpsc-526 / Assignment #2 / Sumit Khanna

Overview

Program #2 is designed to be a client for the PingServer class given to us in the excursive. It uses a UDP/Datagram packet to determine packet loss. The Server has been designed to disregard random packets to simulate packet loss.

Specifications

The PingServer Client is designed to ping one hosts with 10 UDP requests on a given port. It will output to the user as each reply is received. It does this by starting a Java thread that sends a request and then sleeps for one second. The primary thread sits and waits for the response. Once all ten packets have been sent, the primary thread waits two seconds before displaying the statistics (average round trip times, packet loss, etc.) 

Compiling

Simply type the following to compile the program:

javac JavaClient.java


Usage

java JavaClient <hostname> <port>