#ifndef CONNECT_CONTROL_CLIENT_COMMAND_CPP
#define CONNECT_CONTROL_CLIENT_COMMAND_CPP
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "command.h"
const string ConnectControlClientStr = "connectControlClient";

int Command::ConnectControlClient(string args[])
{
    string ip;
    try
    {
        ip = args[1];
    }
    catch (const std::exception &e)
    {
        cerr << "No value specified for ip." << endl;
        return -1;
    }
    int port;
    try
    {
        port = stoi(args[0]);
    }
    catch (const std::exception &e)
    {
        cerr << "No value specified for port." << endl;
        return -2;
    }
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -3;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address;          //in means IP4
    address.sin_family = AF_INET; //IP4
    char *ip_addr = new char[ip.size()];
    copy(ip.begin(), ip.end(), ip_addr);
    address.sin_addr.s_addr = inet_addr(ip_addr); //the localhost address
    address.sin_port = htons(port);

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1)
    {
        std::cerr << "Could not connect to host server" << std::endl;
        return -4;
    }
    else
    {
        std::cout << "Client is now connected to server" << std::endl;
    }
    return 1;
}

void serverSend(int client_socket, int loop = 0)
{
    try
    {
        int valread = 1;
        while (valread > 0)
        {
            char *hello = "Hi from client";
            int is_sent = send(client_socket, hello, /*SIZE*/ 0, 0);
            if (is_sent == -1)
            {
                std::cout << "Error sending message" << std::endl;
            }
            else
            {
                std::cout << "Hello message sent to server" << std::endl;
            }
            if (!loop)
                break;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

#endif