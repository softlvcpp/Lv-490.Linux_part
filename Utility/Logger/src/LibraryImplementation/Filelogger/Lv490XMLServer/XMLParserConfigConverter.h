// Description:
// Adds support for Lv490 XMLParser library XMLServer implementation
// without actually including it's headers
//

#ifndef LOGGERLIBRARY_XMLPARSERCONFIGCONVERTER_H
#define LOGGERLIBRARY_XMLPARSERCONFIGCONVERTER_H
#include "../filelogger.h"

namespace filelog
{ 

    template<typename TConfig>
    struct DefaultXMLServerAccessor
    {
        constexpr static const char* DEFAULT_FILENAME = "logfile.txt";
        static filelog::FileLoggerCreatorParams createParams(const TConfig& config)
        {
            filelog::FileLoggerCreatorParams params;

            params.nameTemplate = config.get_filename();
            params.setRTLevel(static_cast<log490::level_t>(config.get_loglevel()));
            params.isForceFlushed = static_cast<bool>(config.get_flush());
            params.logStoringDirectory = filelog::Utils::getDefaultPath();
            params.useExactSameName = true;

            return params;
        }
    };

    template <typename TConfig, typename TAccessor = DefaultXMLServerAccessor<TConfig>>
    struct ConfigToFileLoggerParams
    {
        static filelog::FileLoggerCreatorParams convert(const TConfig& conf)
        {
            return TAccessor::createParams(conf);
        }
    };

}

#endif //LOGGERLIBRARY_XMLPARSERCONFIGCONVERTER_H
