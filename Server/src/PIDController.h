#ifndef SERVER_PIDCONTROLLER_H
#define SERVER_PIDCONTROLLER_H
#include <string>
#include <string_view>

/*
 * The class is responsible for saving the daemon`s pid
 * into file.
 * The file is located in the same directory as the
 * daemon`s executable.
 */
class PIDController
{
    const std::string m_filename{"/daemon_pid.pid"};

    std::string GetFilePath()const;
public:
    [[nodiscard]] pid_t ReadPIDFromFile()const;
    [[nodiscard]] bool SavePIDToFile()const;
};


#endif //SERVER_PIDCONTROLLER_H
