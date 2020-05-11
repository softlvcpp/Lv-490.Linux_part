
#include <vector>
#include<iostream>
#include <map>
#include <QStorageInfo>
using namespace std;
//namespace fs = std::filesystem;


const std::string kProcDirectory{"/proc/"};


class XMLClient
{
public:
    void WriteSystemInformation(string& xml_str){};//write client's information in external string

    //Getters
    string  get_os()const { return m_os; }
    string  get_mac_address()const { return m_mac_address; }
    string  get_ip_address()const { return m_ip_address; }

    int  get_total_ram()const { return m_total_ram; }
    int  get_cpu_numbers()const { return m_cpu_numbers; }
    int  get_cpu_speed()const { return m_cpu_speed; }

    string  get_cpu_vendor()const { return m_cpu_vendor; }

    vector<string>   get_hard_disk_type_list()const { return m_hard_disk_type_list; }
    vector<string>   get_hard_disk_media_type()const { return m_hard_disk_media_type; }
    vector<int>      get_hard_disk_total_size()const { return m_hard_disk_total_size; }
    vector<int>      get_hard_disk_used()const { return m_hard_disk_used; }
    vector<int>      get_hard_disk_free()const { return m_hard_disk_free; }

    map <int, string>get_processes()const { return m_processes; }

    //Setters
    void set_os(string other) { m_os = other; }
    void set_mac_address(string other) { m_mac_address = other; }
    void set_ip_address(string other) { m_ip_address = other; }
    void set_total_ram(int other) { m_total_ram = other; }
    void set_cpu_numbers(int other) { m_cpu_numbers = other; }
    void set_cpu_speed(int other) { m_cpu_speed = other; }
    void set_cpu_vendor(string other) { m_cpu_vendor = other; }
    void set_hard_disk_type_list(vector<string> other) { m_hard_disk_type_list = other; }
    void set_hard_disk_media_type(vector<string> other) { m_hard_disk_media_type = other; }
    void set_hard_disk_total_size(vector<int> other) { m_hard_disk_total_size = other; }
    void set_hard_disk_used(vector<int> other) { m_hard_disk_used = other; }
    void set_hard_disk_free(vector<int> other) { m_hard_disk_free = other; }
    void set_processes(std::map <int, string> other) {m_processes = other; }

private:
    //clients' information members
    string m_os;
    string m_mac_address;
    string m_ip_address;

    int m_total_ram;
    int m_cpu_numbers;
    int m_cpu_speed;

    string m_cpu_vendor;

    vector<string>  m_hard_disk_type_list;
    vector<string>  m_hard_disk_media_type;
    vector<int>     m_hard_disk_total_size;
    vector<int>     m_hard_disk_used;
    vector<int>     m_hard_disk_free;

    map <int, string> m_processes;
};









class ClientSysInfo
{

    XMLClient m_client_info;
    std::string m_CPU_model;
public:
    ClientSysInfo();
    void Update();
    void Parse(string& xml_str) const noexcept;

    string  get_os()const;
    string  get_mac_address()const;
    string  get_ip_address()const;

    int  get_total_ram()const;
    int  get_cpu_numbers()const;
    int  get_cpu_speed()const;

    string  get_cpu_vendor()const;

    vector<string>   get_hard_disk_type_list()const;
    vector<string>   get_hard_disk_media_type()const;
    vector<int>      get_hard_disk_total_size()const;
    vector<int>      get_hard_disk_used()const;
    vector<int>      get_hard_disk_free()const;
    string get_CPU_model(){return m_CPU_model;};
    std::map <int, string> get_processes()const;
private:
    std::string CalculateOS();
    int CalculateTotalRAM();

    int CalculateCPUNumbers();

    void CalculateCPUInfo();

    void CalculatevectorLogicDick(std::vector<std::string>& disks,
        vector<std::string>&  hard_disk_media_type,
        vector<int>& hard_disk_total_size,
        vector<int>& hard_disk_used,
        vector<int> &    hard_disk_free);

    std::string CalculateHardDisk_MediaType(string LogicalDisk);
    int CalculateFreeSpace(const QStorageInfo& logic_drive);
    int CalculateCapacity(const QStorageInfo& logic_drive);
    std::string CalculateMacAddress();
    std::string CalculateIPAddress();

    void CalculateProcesses();
};

