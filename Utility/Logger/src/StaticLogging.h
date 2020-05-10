#pragma once

#include "ExportConfig.h"
#include <type_traits>
#include <typeinfo>
#include <memory>
#include "ILogger.h"

#if !defined(GLOG_DEFAULT_LEVEL)
#define GLOG_DEFAULT_LEVEL 99
#endif

namespace glog
{
    namespace glogutils
    {
        template <typename T>
        struct is_unique_ptr : std::false_type {};
        template <typename T, typename D>
        struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type {};
        template <typename T>
        struct is_shared_ptr : std::false_type {};
        template <typename T>
        struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

        template <typename T>
        constexpr auto& toRef(T& obj)
        {
            if constexpr(std::is_pointer<T>::value)
                return *obj;
            if constexpr(is_unique_ptr<T>::value)
                return *obj;
            if constexpr(is_shared_ptr<T>::value)
                return *obj;
            else
                return obj;
        }
    }

	struct GlobalLogging
	{
        static constexpr auto DEFAULT_LOGGER_LEVEL = 1;

        LOGGER_API static void setLevel(logbase::loglevel_type loglvl);
        LOGGER_API static logbase::loglevel_type getLevel(logbase::loglevel_type loglvl);
        LOGGER_API static bool exists();
        LOGGER_API static bool isValid();
        LOGGER_API static logbase::ILogger& getInstance();

        /* Resets global logger instance using give parameters */
        LOGGER_API static bool resetInstance(const logbase::LoggerCreationParamsBase& params);
    private:
        inline static struct StaticConstructor
        {
            LOGGER_API StaticConstructor();
        } stcon;
        inline static std::unique_ptr<logbase::ILogger> instance;
        inline static std::unique_ptr<logbase::LoggerCreationParamsBase> lastParams;
	};

    /*  NOTE:
     *  SLOG_LEVEL should be supplied from any header before inclusion of this one
    */
#if !defined SLOG_GLOBAL
#define SLOG_GLOBAL(level) SLOG_LEVEL(glog::GlobalLogging::getInstance(), level)
#endif

#define GLOG_P SLOG_GLOBAL(CTLVL_PROD)
#define GLOG_D SLOG_GLOBAL(CTLVL_DEBUG)
#define GLOG_T SLOG_GLOBAL(CTLVL_TRACE)

}
