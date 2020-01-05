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

    int is_sent = 1;
    while (is_sent > 0)
    {
        auto command = DB::getInstance()->getNextUpdateQuery();
        if (!command.empty())
        {

            DB::getInstance()->lockMutex();
            while (!command.empty())
            {
                is_sent = send(client_socket, command.c_str(), (u_int)command.length(), 0);
                if (is_sent == -1)
                {
                    std::cout << "Error sending message" << std::endl;
                }
                try
                {

                    command = DB::getInstance()->getNextUpdateQuery();
                }
                catch (const std::exception &e)
                {
                    break;
                }
            }
            DB::getInstance()->unlockMutex();
        }
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
    return 1;
}

#endif