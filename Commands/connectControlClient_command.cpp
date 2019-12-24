#ifndef CONNECT_CONTROL_CLIENT_COMMAND_CPP
#define CONNECT_CONTROL_CLIENT_COMMAND_CPP
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include "../command.h"
#include "../DB.h"

void clientSend(int client_socket)
{
    try
    {
        int is_sent = 1;
        while (is_sent > 0)
        {
            auto query = DB::getInstance()->getNextUpdateQuery();
            while (query)
            {
                DB::getInstance()->lockMutex();
                is_sent = send(client_socket, query, BUFFER_SIZE, 0);
                if (is_sent == -1)
                {
                    std::cout << "Error sending message" << std::endl;
                }
                query = DB::getInstance()->getNextUpdateQuery();
                DB::getInstance()->unlockMutex();
                // sleep(3);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
int Command::ConnectControlClient(string args[])
{
    string ip;
    try
    {
        ip = args[0];
    }
    catch (const std::exception &e)
    {
        cerr << "No value specified for ip." << endl;
        return -1;
    }
    int port;
    try
    {
        port = stoi(args[1]);
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
    strcpy(ip_addr, ip.c_str());
    address.sin_addr.s_addr = inet_addr(ip_addr); //the localhost address
    address.sin_port = htons(port);

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1)
    {
        std::cerr << "Could not connect to host server" << std::endl;
        return -4;
    }

    thread client_listen_thread = thread(clientSend, client_socket);
    client_listen_thread.detach();
    std::cout << "Client Connected Successfuly" << endl;
    return 1;
}

#endif