# ChatProgram

# Introduction

ChatProgram is a simple client/server application. Users can send and receive messages to each other through a Terminal interface. TCP is the protocol used to handle the connections in the application.

The purpose of the server is to handle connected sockets. The server maintains a list of connected sockets, receives incoming messages and sends these messages according to the list. The client establishes a connection to the server, sends messages to the server, and reads continuously for responses from the server. 

Select() and system calls are used in both the client and server side. On the server side, both types of calls are used to service and multiplex incoming messages. On the client side, these calls are used to prompt the use for input and handling the “save conversation” command in a non-blocking manner.
Instructions

# Server

1. Go to the directory that contains the source files.
2. Open the Terminal in the directory
3. The usage pattern to run the server is as follows: ./all server <ip_address>:<port>

# Client

1. Go to the directory that contains the source files.
2. Open the Terminal in the directory
3. Make sure that the server is running.
4. The usage pattern to run the server is as follows: ./all client <username>  <ip_address>:<port>



