#include "TCPServer.h"
#include <cstring>

int main(int argc, char** argv)
{
    TCPServer server;
    if(strcmp(argv[1], "start") == 0)
    {
        if(!server.Start())
        {
            //Log that unable to start server;
            return -1;
        }
    }
    else if(strcmp(argv[1], "stop") == 0)
    {
        if(!server.Stop())
        {
            //Log that unable to stop server;
            return -1;
        }
    }
    else if(strcmp(argv[1], "restart") == 0)
    {
        if(!server.Restart())
        {
            //Log that unable to restart server;
            return -1;
        }
    }

}