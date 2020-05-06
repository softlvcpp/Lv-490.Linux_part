#ifndef SERVER_TCPSERVER_H
#define SERVER_TCPSERVER_H
#include "PIDController.h"
class IDaemon
{
protected:
    static constexpr int CHILD_MUST_RESTART = 1;
    static constexpr int CHILD_MUST_TERMINATE = 2;
public:
    virtual bool Start() = 0;
    virtual bool Stop() = 0;
    virtual bool Restart() = 0;
};

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
    [[noreturn]] void DaemonMain();
    [[nodiscard]] bool Daemonize();
    [[nodiscard]] bool MonitorProcess();

};


#endif //SERVER_TCPSERVER_H
