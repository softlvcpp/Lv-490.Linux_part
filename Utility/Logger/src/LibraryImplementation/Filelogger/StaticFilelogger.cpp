#include "../../LoggerImplementation.h"
#include "../../StaticLogging.h"
#include <filesystem>

namespace glog 
{
#define GLOG_CASTED_INTANCE static_cast<filelog::FileLogger&>(*glog::GlobalLogging::instance)

    logbase::ILogger& GlobalLogging::getInstance()
    {
        return *instance;
    }

    bool GlobalLogging::resetInstance(const logbase::LoggerCreationParamsBase &params)
    {
        static std::mutex mtx;
        std::scoped_lock lck { mtx };
           
        if (instance)
        {
            auto fname = GLOG_CASTED_INTANCE.getCurrentFilename();
            GLOG_CASTED_INTANCE.stopLogging();

            std::error_code errc;
            std::filesystem::path fPath = fname.c_str();
            auto fileSize = std::filesystem::file_size(fPath, errc);
            if (!errc && (fileSize == 0))
                std::filesystem::remove(fPath);
        }
        
        instance = filelog::FileLoggerCreator{}.create(params);
        return !GLOG_CASTED_INTANCE.isInterrupted();
    }

    void GlobalLogging::setLevel(logbase::loglevel_type loglvl)
    {
        auto lvl = static_cast<filelog::LogLevel>(loglvl);
        if (lvl > filelog::LogLevel::Trace)
            lvl = filelog::LogLevel::Trace;
        else if (lvl < filelog::LogLevel::NoLogs)
            lvl = filelog::LogLevel::NoLogs;

        GLOG_CASTED_INTANCE.setRTLevel(static_cast<log490::level_t>(lvl));
    }

    bool GlobalLogging::exists()
    {
        return instance != nullptr;
    }
    bool GlobalLogging::isValid()
    {
        return GLOG_CASTED_INTANCE.isInterrupted() == false;
    }

    GlobalLogging::StaticConstructor::StaticConstructor() {
    #ifdef GLOG_NO_DEFAULT_CONGIG
        return;
    #endif
        filelog::FileLoggerCreatorParams params;
        params.logStoringDirectory = filelog::Utils::getDefaultPath();
        params.useExactSameName = true;
        params.setRTLevel(DEFAULT_LOGGER_LEVEL);
        instance = filelog::FileLoggerCreator{}.create(params);

        lastParams = std::make_unique<filelog::FileLoggerCreatorParams>(params);
    }
}



