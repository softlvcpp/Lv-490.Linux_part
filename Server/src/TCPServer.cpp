#include <signal.h>
#include <zconf.h>
#include <sys/stat.h>
#include <wait.h>
#include <string.h>

//temp
#include <fstream>

#include "PIDController.h"
#include "TCPServer.h"

bool TCPServer::Start()
{
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
    return true;
}

void TCPServer::DaemonMain()
{
    //Олег, тут пиши код сервера.
    std::ofstream ofs("/home/danylo/file.txt");
    ofs << "hello from daemon";

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
        int status = MonitorProcess();
        return status;
    }
    else
    {
        return 0;
    }



}

bool TCPServer::MonitorProcess()
{
    bool need_start{true};
    sigset_t sigset;
    siginfo_t siginfo;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGQUIT);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTERM);
    sigaddset(&sigset, SIGCHLD);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    if(!m_pid_controller.SavePIDToFile())
    {
        //LOG, but the program can keep working
    }

    pid_t pid;
    int status;
    while(true)
    {
        if (need_start)
        {
            pid = fork();
        }
        need_start = true;
        if(pid == -1)
        {
            //GLOG_T
            return false;
        }
        else if(pid == 0)
        {
            DaemonMain();
        }
        else
        {
            sigwaitinfo(&sigset, &siginfo);
            if (siginfo.si_signo == SIGCHLD)
            {
                wait(&status);
                status = WEXITSTATUS(status);

                if (status == CHILD_MUST_TERMINATE)
                {
                    // Log that daemon terminated
                    break;
                }
                else if (status == CHILD_MUST_RESTART)
                {
                    // Log that child must restart
                }
            }
            else if (siginfo.si_signo == SIGUSR1)
            {
                kill(pid, SIGUSR1);
                need_start = 0;
            }
            else
            {
                // Log the signal that just came, using strsignal(siginfo.si_signo)
                kill(pid, SIGTERM);
                status = 0;
                break;
            }
        }
    }
    //Log that the daemon monitor stopped working
    return true;
}
