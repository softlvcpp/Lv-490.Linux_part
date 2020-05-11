#include <cstring>
#include <algorithm>

#include "TCPServer.h"

int main(int argc, char** argv)
{
    std::string command;
    if(argv[1])
    {
        command = argv[1];
        std::transform(command.begin(), command.end(), command.begin(),
                       [](char c){ return std::tolower(c); });
    }
    else
    {
        return -1;
    }

    TCPServer server;
    if(strcmp(argv[1], "start") == 0)
    {
        if(!server.Start())
        {
            //Log that unable to start the server;
            return -1;
        }
    }
    else if(strcmp(argv[1], "stop") == 0)
    {
        if(!server.Stop())
        {
            //Log that unable to stop the server;
            return -1;
        }
    }
    else if(strcmp(argv[1], "restart") == 0)
    {
        if(!server.Restart())
        {
            //Log that unable to restart  the server;
            return -1;
        }
    }

}