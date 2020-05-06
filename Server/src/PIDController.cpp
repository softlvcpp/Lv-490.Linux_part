#include <memory>
#include <climits>
#include <fstream>

#include <zconf.h>
#include <libgen.h>

#include "PIDController.h"

std::string PIDController::GetFilePath() const
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
//    std::unique_ptr<char> dir_path = std::make_unique(dirname(result));
    std::string pid_file_path = dirname(result) + m_filename;
    return pid_file_path;
}

bool PIDController::SavePIDToFile() const
{
    std::ofstream pid_file{GetFilePath()};
    if(!pid_file.is_open())
    {
        // GLOG_T << "Cannot open pid file for writing"
        return false;
    }
    pid_file << getpid();
    pid_file.close();
}



pid_t PIDController::ReadPIDFromFile() const
{
    std::ifstream pid_file(GetFilePath());
    if(!pid_file.is_open())
    {
        //GLOG
        return -1;
    }
    pid_t pid;
    pid_file >> pid;
    pid_file.close();
    return pid;
}


