#ifndef SERVER_TCPSERVER_H
#define SERVER_TCPSERVER_H
#include "PIDController.h"
#include "IDaemon.h"

/*
 * This is an implementation of linux TCP server that runs as daemon.
 * Class methods do not throw any exceptions.
 */
class TCPServer : public IDaemon
{
    PIDController m_pid_controller;
public:
    TCPServer() = default;
    [[nodiscard]] bool Start() override;
    [[nodiscard]] bool Stop() override;
    [[nodiscard]] bool Restart() override;
private:
    [[nodiscard]] bool Daemonize();
    [[nodiscard]] bool RunDaemon();
    [[noreturn]] void DaemonMain();

};


#endif //SERVER_TCPSERVER_H
