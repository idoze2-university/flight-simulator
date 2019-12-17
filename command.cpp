#include "command.h"
map<const char *, pair<Command, int>> getCommandToStrMap()
{
    map<const char *, pair<Command, int>> cmdMap;
    cmdMap.emplace(OpenDataServerStr, pair<Command, int>(Command(OpenDataServer), ARGC_OpenDataServer));
    // cmdMap.emplace(ConnectControlClientStr, pair<Command, int>(Command(ConnectControlClient), ARGC_ConnectControlClient));
    // cmdMap.emplace(VarMethStr, pair<Command, int>(Command(VarMeth), ARGC_VarMeth));
    // cmdMap.emplace(PrintMethStr, pair<Command, int>(Command(PrintMeth), ARGC_PrintMeth));
    // cmdMap.emplace(SleepMethStr, pair<Command, int>(Command(SleepMeth), ARGC_SleepMeth));
    // cmdMap.emplace(WhileMethStr, pair<Command, int>(Command(WhileMeth), ARGC_WhileMeth));
    return cmdMap;
}

int OpenDataServer(string args[])
{
    int port;
    try
    {
        port = stoi(args[0]);
    }
    catch (const std::exception &e)
    {
        cout << "Using Default Port" << endl;
        port = DEF_PORT;
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
    int trying = 0;
    int wait_time = 1;
    while (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        std::cerr << "Could not bind the socket to an IP, retrying in " << wait_time << "s [" << trying++ << "]" << std::endl;
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
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t *)&address);
    if (client_socket == -1)
    {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }

    thread server_listen_thread = thread(serverListen, client_socket, 0);
    server_listen_thread.join();
    std::cout << "Client Connected Successfuly" << endl;
    close(socketfd); //closing the listening socket
    server_listen_thread = thread(serverListen, client_socket, 1);
    server_listen_thread.detach();
    return 1;
}
void serverListen(int client_socket, int loop = 0)
{
    try
    {
        int valread = 1;
        while (valread > 0)
        {
            char buffer[1024] = {0};
            valread = read(client_socket, buffer, 1024);
            std::cout << '\r' << buffer << std::endl;
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
