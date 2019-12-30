#ifndef OPEN_SERVER_COMMAND_CPP
#define OPEN_SERVER_COMMAND_CPP
#define BUFFSIZE 1024
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex>
#include "../DB.h"
#include "../command.h"
using namespace std;

void getFromServer(int client_socket)
{
    char buffer[BUFFSIZE];
    if (read(client_socket, buffer, BUFFSIZE) > 0)
    {
        DB::getInstance()->setServerValues(buffer);
    }
}

void serverListen(int client_socket)
{
    try
    {
        while (1)
        {
            getFromServer(client_socket);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}
int Command::OpenDataServer(string args[])
{
    int port;
    try
    {
        port = stoi(args[0]);
    }
    catch (const std::exception &e)
    {
        cerr << "No value specified for port." << endl;
        return -1;
    }
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    //bind socket to IP address, Taken from server.cpp from piazza.
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    double wait_time = 0.7;
    while (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        sleep(wait_time);
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1)
    { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    }
    else
    {
    }

    // accepting a client
    auto socket_addr = (struct sockaddr *)&address;
    int client_socket = accept(socketfd, socket_addr, (socklen_t *)&address);
    if (client_socket == -1)
    {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    getFromServer(client_socket);
    auto server_listen_thread = thread(serverListen, client_socket);
    server_listen_thread.detach();
    return 1;
}

#endif