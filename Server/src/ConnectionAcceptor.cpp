#include <string>
#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

#include "ConnectionAcceptor.h"

constexpr int ERROR = -1;
constexpr int SUCCESS = 0;
constexpr int REQUEST_NUM = 5;
constexpr int VALUE = 0;

void ConnectionAcceptor::operator()()
{
    struct addrinfo hints;
    memset(&hints, VALUE, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result, *rp;
    if (getaddrinfo(NULL, m_port.c_str(), &hints, &result) != SUCCESS)
    {
        //log "Error getting address info"
        return;
    }
    int sfd = 0;
    int optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        fcntl(sfd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/
        if (sfd == ERROR)
        {
            continue;
        }
        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == ERROR)
        {
            //log "Error setting SO_REUSEADDR option"
        }
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == SUCCESS)
        {
            //log "Socket " + sfd + " bound to " + rp->ai_addr
            break; //SUCCESS
        }
        close(sfd);
        //log "Error when binding the socket"
        return;
    }
    if (listen(sfd, REQUEST_NUM) == ERROR)
    {
        //log "Error when listening"
        return;
    }
    freeaddrinfo(result);
    while (true)
    {
        int cfd = accept(sfd, NULL, NULL);
        fcntl(cfd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/
        if (cfd == ERROR)
        {
            //log "Accept() failed"
            //TODO massage reading for registered handle
        }
        else
        {
            //log "Connection created"
            m_traffic_manager->RegisterEventHandler(cfd, nullptr);
        }
    }
}
