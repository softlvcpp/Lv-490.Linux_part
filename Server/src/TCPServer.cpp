#define TIMEOUT  2
#define  HOST "localhost"
#define  PORT "8080"

#include <signal.h>
//#include <zconf.h>
#include <sys/stat.h>
#include <wait.h>
#include <string.h>

//temp
#include <fstream>
#include <thread>
#include <unistd.h>

#include "PIDController.h"
#include "TCPServer.h"
#include "ConnectionAcceptor.h"
#include "ReactorInterface.h"
#include "ReactorSelectImpl.h"



bool TCPServer::Start()
{
    //If the daemon is currently running
    if(m_pid_controller.ReadPIDFromFile() != -1)
    {
        Stop();
    }
    if(!Daemonize())
    {
        //Log that cannot start
        return false;
    }
    //Log that started
    return true;
}

bool TCPServer::Stop()
{
    pid_t pid = m_pid_controller.ReadPIDFromFile();
    if(pid == -1)
    {
        return false;
    }
    if(kill(pid, SIGTERM) == -1)
    {
       //Log that cannot terminate the daemon
       return false;
    }
    if(!m_pid_controller.DeletePIDFile())
    {
        // Log that could not delete the file
        // This error is not crucial.
    }
    // Log that successfully terminated
    return true;
}

bool TCPServer::Restart()
{
    if(!Stop())
    {
        return false;
    }
    if(Start())
    {
        return false;
    }
    //Log that service restarted
    return true;
}

void TCPServer::DaemonMain()
{
    auto traffic_manager = std::make_shared<reactor::ReactorSelectImpl>();
    traffic_manager->set_timeout(TIMEOUT);

    ConnectionAcceptor connection_acceptor{HOST, PORT, traffic_manager};
    std::thread acceptor_thread(connection_acceptor);
    std::thread manager_thread(*traffic_manager);
    acceptor_thread.join();
    manager_thread.join();
}

bool TCPServer::Daemonize()
{
    pid_t pid;

    // ReadConfig() here

    pid = fork();

    if(pid == -1)
    {
        // Log that cannot create daemon
        return false;
    }
    if(pid == 0)
    {
        umask(0);
        setsid();
        chdir("/");
        if(!RunDaemon())
        {
            // Log that cannot run daemon
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool TCPServer::RunDaemon()
{
//    close(STDIN_FILENO);
//    close(STDOUT_FILENO);
//    close(STDERR_FILENO);

    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        // Log that cannot fork
        return false;
    }
    else if (pid == 0)
    {
        if (!m_pid_controller.SavePIDToFile())
        {
            //LOG, but the program can keep working
        }
        DaemonMain();
    }
    return true;
}