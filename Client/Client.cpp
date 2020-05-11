#include "Client.h"
#include<qdebug.h>
#include<qtimer.h>
#include <QTextEdit>
#include <QScrollBar>
#include <map>
//#include"ClientSysInfo.h"
#include<qgraphicsview.h>
#include<qlayout.h>
//#include"DefineLogger.h"
//#include "../Utility/XML_Parser/XML_Parser.h"
#include<thread>
int numff = 0;
#include <QImageReader>
enum ComboBoxOptions
{
    AllSystemInformation,
    HardDiskInformation,
    CPUInformation,
    RamInformation,
    NetworkInformation,
    ProcessInformation
};

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    qDebug() << QImageReader::supportedImageFormats();

    ui.tableWidget->hide(); //hide process table

   setWindowIcon(QIcon("main_icon.png"));
   settings.setModal(true);

   setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint |
        Qt::WindowCloseButtonHint |	Qt::WindowSystemMenuHint);//different flags for window

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    QGraphicsView view;
    view.setFrameStyle(QFrame::NoFrame);

    timer = new QTimer(this);//for processes
//	client_info2.CalculateProcesses();

    tmr = new QTimer(this); //for socket conection
    //connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(tmr, SIGNAL(timeout()), this, SLOT(runUpdateTime()));
    tmr->start();

    connect(ui.comboBox, SIGNAL(currentIndexChanged(int)),	this, SLOT(indexComboChanged(int))); //signal for changed combo

    connect(ui.actionChange_settings, SIGNAL(triggered()), this, SLOT(open_settings())); //signal for opening settings window

    indexComboChanged(0); // display all info
    qDebug() << "hard disk";

}
void Client::closeEvent(QCloseEvent* event) {
    qDebug()<< "CloseEvent:";
    if (m_th->joinable())
    {
        m_th->join();
    }
    delete m_th;

};

void Client::runUpdateTime()
{
    const unsigned int TimeMeasurement = 1000; // 1000- seconds, 1 = milliseconds, 60000 - minuts...;
tmr->setInterval(3 * TimeMeasurement);
    //tmr->setInterval(settings.get_TimeInterval() * TimeMeasurement); // set time interval
    if (m_th != nullptr)
    {
        if (m_th->joinable())
        {
            m_th->join();
        }
        delete m_th;
    }
    m_th = new std::thread(&Client::updateTime, this);
}

void Client::updateTime()
{
    //
}

void Client::UpdateProccesThread()
{
    if (m_th != nullptr)
    {
        if (m_th->joinable())
        {
            m_th->join();
        }
        delete m_th;
    }
    m_th = new std::thread(&Client::UpdateProcesses, this);
}

void Client::UpdateProcesses() {
    qDebug() << "______________update_processes______________";
    ui.textEdit->hide();
    ui.tableWidget->show();
    //client_info2.CalculateProcesses(); //update data
    std::map<int, std::string> processes_map = client_info2.get_processes();//= client_info2.get_processes();

    ui.tableWidget->setColumnCount(PROCESS_COLUMN_COUNT);//2
    ui.tableWidget->setRowCount(123);
    ui.tableWidget->horizontalScrollBar()->setDisabled(true);
    ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Name");

    ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tableWidget->resizeRowsToContents();
    /*BIG BUG which cause lags is somewhere here
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // cause big delay||LAGGG
    ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//u will dont have permision to edit items
    */

    int i = 0;
    for (std::map<int, std::string>::iterator itr = processes_map.begin(); itr != processes_map.end(); itr++) {
        ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(itr->first)));
        ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString(itr->second.c_str())));
        i++;
    }
}


void Client::open_settings() {

    settings.setModal(true);
    settings.exec();
}


QString DisplayHardDiskInformation(ClientSysInfo client_info2) {
    QString str;
    std::vector<int> free_size = client_info2.get_hard_disk_free();
    std::vector<int> total_size = client_info2.get_hard_disk_total_size();
    std::vector<int> used_size = client_info2.get_hard_disk_used();
    std::vector<std::string> volume_vector = client_info2.get_hard_disk_type_list();//= {"C:\\","D:\\","E:\\" };
    std::vector<std::string> volume_media_type = client_info2.get_hard_disk_media_type();// ={"ssd","hdd","hdd"};

    for (int i = 0; i < volume_vector.size(); i++) {
        str += "Hard Disk (" + QString(volume_vector[i].c_str()) + ") "
            + QString(volume_media_type[i].c_str()) + "\n";
        //+ QString(client_info2.CalculateHardDisk_MediaType(volume_vector[i]).c_str()) + "\n";
        str += " capacity: " + QString::number(total_size[i]) + QString("GB \n");
        str += " used: " + QString::number(used_size[i]) + QString("GB \n");
        str += " free: " + QString::number(free_size[i]) + QString("GB \n");
    }
    return str;
}

QString DisplayCPUInformation(ClientSysInfo client_info2) {
    QString str;
    str += "CPU vendor: " + QString(client_info2.get_cpu_vendor().c_str()) + "\n";
    str += "CPU core number: " + QString::number(client_info2.get_cpu_numbers()) + "\n";
    str += "CPU speed: " + QString::number(client_info2.get_cpu_speed()) + "MHz\n";
    str += QString(client_info2.get_CPU_model().c_str())+"\n";
    return str;
}

QString DisplayRamInformation(ClientSysInfo client_info2) {
    QString str;
    str += "Total RAM: " + QString::number(client_info2.get_total_ram()) + "MB\n";
    return str;
}

QString DisplayNetworkInformation(ClientSysInfo client_info2) {
    QString str;
    str += "MAC address: " + QString(client_info2.get_mac_address().c_str()) + "\n";
    str += "IP address: " + QString(client_info2.get_ip_address().c_str()) + "\n";
    return str;
}


QString DisplayAllInformationString(ClientSysInfo client_info2) {
    QString str = "OS: " + QString(client_info2.get_os().c_str()) + '\n';
    str += DisplayCPUInformation(client_info2);
    str += DisplayRamInformation(client_info2);
    str += DisplayHardDiskInformation(client_info2);
    str += DisplayNetworkInformation(client_info2);
    return str;
}
void Client::indexComboChanged(int index)
{
    if (timer->isActive()) {
        timer->stop();
    }

    //client_info2.Update();
    ui.tableWidget->hide();
    ui.textEdit->show();
    int num = ui.comboBox->currentIndex();

    switch (num)
    {
    case ComboBoxOptions::AllSystemInformation:
        ui.textEdit->setText(DisplayAllInformationString(client_info2));
        break;
    case ComboBoxOptions::CPUInformation:
        ui.textEdit->setText(DisplayCPUInformation(client_info2));
        break;
    case ComboBoxOptions::HardDiskInformation:
        ui.textEdit->setText(DisplayHardDiskInformation(client_info2));
        break;
    case ComboBoxOptions::RamInformation:
        ui.textEdit->setText(DisplayRamInformation(client_info2));
        break;
    case ComboBoxOptions::NetworkInformation:
        ui.textEdit->setText(DisplayNetworkInformation(client_info2));
        break;
    case ComboBoxOptions::ProcessInformation:
        UpdateProcesses(); //display data at first
        connect(timer, SIGNAL(timeout()), this, SLOT(UpdateProccesThread()));//make all info about processes updateble
        timer->start(PROCESS_UPDATE_DURATION);
        break;
    default:
        break;

    }

    //ui.textEdit->ensureCursorVisible();
    // Do something here on ComboBox index change
}
