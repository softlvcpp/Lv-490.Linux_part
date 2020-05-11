#include <ClientSysInfo.h>
//#include<qnetworkinterface.h>
#include <QApplication>
#include <QStorageInfo>
#include <experimental/filesystem>
#include <QNetworkInterface>


#include "sys/types.h"
#include "sys/sysinfo.h"//for ram



#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>

#include <regex>


#include <fstream>

#include <QApplication>
#include <qdebug.h>
#include <QSysInfo>
#include <QNetworkInterface>
#include <QStorageInfo>
#include <QDebug>
#include <vector>
#include <QtAlgorithms>
#include <fstream>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <QHostAddress>


#include <dirent.h>


namespace fs = std::experimental::filesystem;

ClientSysInfo::ClientSysInfo() {
    Update();
}

void  ClientSysInfo::Update() {

    m_client_info.set_os(CalculateOS());
    //qDebug() << systemInfo.dwNumberOfProcessors;
    string os_name = QSysInfo::productType().toStdString();


        m_client_info.set_total_ram(CalculateTotalRAM());
        m_client_info.set_cpu_numbers(CalculateCPUNumbers());
        CalculateCPUInfo();
        CalculateProcesses();

        vector<string> hard_disk_type_list;
        vector<std::string>  hard_disk_media_type;
        vector<int>     hard_disk_total_size;
        vector<int>     hard_disk_used;
        vector<int>     hard_disk_free;
        CalculatevectorLogicDick(hard_disk_type_list,hard_disk_media_type,hard_disk_total_size,hard_disk_used,hard_disk_free);
        m_client_info.set_hard_disk_type_list(hard_disk_type_list);
        m_client_info.set_hard_disk_total_size(hard_disk_total_size);
        m_client_info.set_hard_disk_free(hard_disk_free);
        m_client_info.set_hard_disk_used(hard_disk_used);
        m_client_info.set_hard_disk_media_type(hard_disk_media_type);
        m_client_info.set_mac_address(CalculateMacAddress());
        m_client_info.set_ip_address(CalculateIPAddress());
if (os_name == "windows") {
    }
    else if (os_name == "linux") {} // For the future :)
    else {
        //undefined m_client_info.OS;
        //TODO logger error
    }

}








string ClientSysInfo::get_os() const
{
    return m_client_info.get_os();
}

string ClientSysInfo::get_mac_address() const
{
    return m_client_info.get_mac_address();
}

string ClientSysInfo::get_ip_address() const
{
    return m_client_info.get_ip_address();
}

int ClientSysInfo::get_total_ram() const
{
    return m_client_info.get_total_ram();
}

int ClientSysInfo::get_cpu_numbers() const
{
    return m_client_info.get_cpu_numbers();
}

int ClientSysInfo::get_cpu_speed() const
{
    return m_client_info.get_cpu_speed();
}

string ClientSysInfo::get_cpu_vendor() const
{
    return m_client_info.get_cpu_vendor();
}

vector<string> ClientSysInfo::get_hard_disk_type_list() const
{
    return m_client_info.get_hard_disk_type_list();
}

vector<string> ClientSysInfo::get_hard_disk_media_type() const
{
    return m_client_info.get_hard_disk_media_type();
}

vector<int> ClientSysInfo::get_hard_disk_total_size() const
{
    return m_client_info.get_hard_disk_total_size();
}

vector<int> ClientSysInfo::get_hard_disk_used() const
{
    return m_client_info.get_hard_disk_used();
}

vector<int> ClientSysInfo::get_hard_disk_free() const
{
    return m_client_info.get_hard_disk_free();
}

map<int, string> ClientSysInfo::get_processes() const
{
    return m_client_info.get_processes();
}


































string ClientSysInfo::CalculateOS() {
    QString OSName = QSysInfo::prettyProductName();
    return OSName.toStdString();
}


int ClientSysInfo::CalculateTotalRAM() {
    //return (size_t)sysconf( _SC_PHYS_PAGES ) *  (size_t)sysconf( _SC_PAGESIZE );
    struct sysinfo memInfo;

    sysinfo (&memInfo);
   // long long totalVirtualMem = memInfo.totalram;
   // long long totalPhysMem = memInfo.totalram;
    //Multiply in next statement to avoid int overflow on right hand side...
    long int totalPhysMem = memInfo.totalram;
     qDebug() <<totalPhysMem;
    //Multiply in next statement to avoid int overflow on right hand side...
    totalPhysMem *= memInfo.mem_unit;
    long int physMemUsed = memInfo.totalram - memInfo.freeram;
    //Multiply in next statement to avoid int overflow on right hand side...
    physMemUsed *= memInfo.mem_unit;
    qDebug() <<physMemUsed;
    return totalPhysMem/1024/1024;
}

void ClientSysInfo::CalculateCPUInfo(){
        regex CPU_vendor_id_regex("vendor_id[\\s]*: (.*)");//GenuineIntel
        regex CPU_model_name_regex("model name[\\s]*: (.*)");//Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
        regex CPU_speed_regex("cpu MHz[\\s]*: ([\\d]+.[\\d]+)");//1991.999 MHz
        bool found_vendor_id = false, found_model_name = false, found_CPU_speed = false;
        cmatch sm1;
        cmatch sm2;
        cmatch sm3;
        string line;
        ifstream finfo("/proc/cpuinfo");
        while(getline(finfo,line)) {
             // qDebug() << "!"+QString(line.c_str() );
            if (found_vendor_id==false && regex_search(line.c_str(), sm1, CPU_vendor_id_regex)) {
                qDebug() << line.c_str() ;
                string r=sm1[1].str();
               qDebug() << r.c_str() ;
               m_client_info.set_cpu_vendor(r);
                found_vendor_id = true;
                qDebug() << "1" ;
            }
            if (found_model_name==false && regex_search(line.c_str(), sm2, CPU_model_name_regex)) {
               qDebug() << line.c_str() << endl;
               string r=sm2[1].str();
              qDebug() << r.c_str() ;
                 m_CPU_model=r;
                found_model_name = true;
                qDebug() << "2" ;
            }
            if (found_CPU_speed==false&&regex_search(line.c_str(), sm3, CPU_speed_regex)) {
               qDebug() << line.c_str() ;
               string r=sm3[1].str();
              qDebug() << r.c_str() ;
              float val = std::stof(r);
              m_client_info.set_cpu_speed(val);
                found_CPU_speed = true;
                qDebug() << "3" ;
            }
            //if (!found_vendor_id && !found_model_name && !found_CPU_speed) {  qDebug() << "IN SHEET" ;break; } //all found
            //if(T.find())


        }
}






int ClientSysInfo::CalculateCapacity(const QStorageInfo& logic_drive) {

    int size_in_GB = logic_drive.bytesTotal() / 1024 / 1024 / 1024;

    return size_in_GB;
}

int ClientSysInfo::CalculateFreeSpace(const QStorageInfo& logic_drive)
//int ClientSysInfo::CalculateFreeSpace(const std::string& logic_drive)
{
    int size_in_GB = logic_drive.bytesFree() / 1024 / 1024 / 1024;

    return size_in_GB;
}
std::string ClientSysInfo::CalculateHardDisk_MediaType(string LogicalDisk)
//string ClientSysInfo::CalculateHardDisk_MediaType(string LogicalDisk)
{
    const std::string FIRST_PART_ROTATION_PATH = "/sys/block/";
    const std::string SECOND_PART_ROTATION_PATH = "/queue/rotational";
    std::string path = FIRST_PART_ROTATION_PATH;
    path += LogicalDisk.substr(LogicalDisk.find("sd"), 3);
    path += SECOND_PART_ROTATION_PATH;
    ifstream rotational(path);
    if (!rotational.is_open() && rotational.eof()) {
        //loger
        qDebug()<<"EROOR rotational.is_open()";
        return "";
    }
    string l;
    char is_hdd = 0;
    rotational >> is_hdd;
      qDebug()<<"HERREEEEE="+QString(is_hdd);
    return (is_hdd ? "HDD" : "SSD");

}
void ClientSysInfo::CalculatevectorLogicDick(std::vector<std::string>& disks,
    vector<std::string>&  hard_disk_media_type,
    vector<int>& hard_disk_total_size,
    vector<int>& hard_disk_used,
    vector<int> &    hard_disk_free)
    //std::vector<std::string> ClientSysInfo::CalculatevectorLogicDick()
{
    QList<QStorageInfo> listVolumes = QStorageInfo::mountedVolumes();
    qSort(listVolumes.begin(), listVolumes.end(), [](QStorageInfo a, QStorageInfo b)->bool {
        return (a.device() < b.device());
    });
    for (size_t i = 0; i < listVolumes.size(); i++) {
        if (listVolumes[i].isValid()                                                         //check if filesystem is exist
            && listVolumes[i].isReady()                                                  //check if filesystem is ready to work
            && !listVolumes[i].isReadOnly()                                               //check if filesystem is not protected from writing
            && CalculateCapacity(listVolumes[i]) > 0)                                             //check if filesystem is not empty
        {
            disks.push_back(listVolumes[i].device().toStdString());
            hard_disk_media_type.push_back(CalculateHardDisk_MediaType(listVolumes[i].device().toStdString()));
            hard_disk_total_size.push_back(CalculateCapacity(listVolumes[i]));
            hard_disk_free.push_back(CalculateFreeSpace(listVolumes[i]));
            hard_disk_used.push_back(hard_disk_total_size.back() - hard_disk_free.back());

            //qDebug()<<listVolumes[i].device().toStdString().c_str();
        }
    }
}





#include <QtNetwork>
#include <QNetworkInterface>
std::string ClientSysInfo::CalculateMacAddress()
{
    QNetworkInterface res;
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for (size_t i = 0; i < list.size(); i++) {
        if (list[i].type() == QNetworkInterface::Ethernet || list[i].type() == QNetworkInterface::Wifi)
        {
            if (list[i].flags().testFlag(QNetworkInterface::IsRunning)) {
                //qDebug()<<list[i].hardwareAddress();
                res = list[i];
                break;
            }
            else
            {
                res = list[i];
            }
        }
    }
    return res.hardwareAddress().toStdString();
}
std::string ClientSysInfo::CalculateIPAddress()
{
    QNetworkInterface mac_interface = QNetworkInterface::interfaceFromName(CalculateMacAddress().c_str());
    QList<QHostAddress> list_ip = mac_interface.allAddresses();
    QString res;
    QHostAddress fd;
    for (size_t i = 0; i < list_ip.size(); i++)
    {
        if (!list_ip[i].isLinkLocal() && !list_ip[i].isLoopback()) {
            res = list_ip[i].toString();
        }
    }
    return res.toStdString();
}







//std::map <int, string> m_processes;


int ClientSysInfo::CalculateCPUNumbers() {
    //return boost::thread::physical_concurrency(); if have boost
    return  get_nprocs_conf();
}



std::vector<int> Pids() {
  std::vector<int> pids;

  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      std::string filename(file->d_name);
      all_of(filename.begin(), filename.end(), ::isdigit);
      if(all_of(filename.begin(), filename.end(), ::isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}
void ClientSysInfo::CalculateProcesses() {

    std::vector<int> pids = Pids();
    std::map<int, std::string> map;

    for (int i = 0; i < pids.size(); i++) {

        std::string line;
        string filename = "/proc/" + to_string(pids[i]) + "/comm";
        std::ifstream myfile(filename);
        if (myfile.is_open())
        {
            std::getline(myfile, line);

                //qDebug() << line.c_str();

            myfile.close();
        }
        else qDebug() << "Unable to open file";
       // qDebug() <<"TOADD  " + QString(line.c_str());
        map.insert(pair<int, string>(pids[i], line));
    }
   m_client_info.set_processes(map);

}
