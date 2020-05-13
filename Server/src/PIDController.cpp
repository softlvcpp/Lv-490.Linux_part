#include <memory>
#include <climits>
#include <fstream>

//#include <zconf.h>
#include <libgen.h>
#include <unistd.h>

#include "PIDController.h"

std::string PIDController::get_file_path() const
{
    static std::string file_path;
    if(file_path.empty())
    {
        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        file_path = std::string(dirname(result)) + m_filename;
    }
    return file_path;

}

bool PIDController::SavePIDToFile() const
{
    std::string file_path = get_file_path();
    std::ofstream pid_file{ file_path };
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
    std::ifstream pid_file(get_file_path());
    pid_t pid = -1;
    if(!pid_file.is_open())
    {
        //GLOG
        return pid;
    }
    try
    {
        pid_file >> pid;
    }
    catch(std::ifstream::failure& e)
    {
        //Log that file was corrupted.
    }
    pid_file.close();
    return pid;
}

bool PIDController::DeletePIDFile() const
{
//    if(std::remove(GetFilePath().c_str()) == 0)
//    {
//        return true;
//    }
//    return false;
return true;
}


