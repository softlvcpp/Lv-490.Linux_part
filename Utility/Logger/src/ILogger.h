#pragma once
#include <stdint.h>
#include <time.h>
#include <memory>

#ifndef LOG_FUNCTION_MACRO
#define LOG_FUNCTION_MACRO __FUNCTION__
#endif 

#ifndef LOG_LINE_MACRO
#define LOG_LINE_MACRO __LINE__
#endif 

#define LOG_LINE_TYPE decltype(LOG_LINE_MACRO)
#define LOG_LEVEL_TYPE uint64_t

namespace logbase
{
    using logline_type = LOG_LINE_TYPE;
    using loglevel_type = LOG_LEVEL_TYPE;

    class ILogger
    {
    public:
        virtual ~ILogger() { }
        virtual bool setLevel(loglevel_type lvl) = 0;
        virtual loglevel_type getLevel() const = 0;
        virtual void stopLogging() = 0;
    };

    template <typename TDataType>
	class ILoggerWDataType : public ILogger
	{
	public:
        virtual ~ILoggerWDataType() { }
        virtual bool processMessage(TDataType& data) = 0;
	};

	struct LoggerBasicLoggingInfo
	{
		constexpr LoggerBasicLoggingInfo(const char* mF, logline_type mLine, loglevel_type mLvl)
			: mFunction{ mF }, mLine { mLine }, mLevel{ mLvl } { }
		const char* mFunction;
		const logline_type mLine;
		const loglevel_type mLevel;
	};

	struct LoggerCreationParamsBase
	{
		virtual ~LoggerCreationParamsBase() { }
        loglevel_type minimumLevel;
	};

    struct AnyConfigConverter
    {
    public:
        template<class TConfig, class TConverter>
        auto convert(const TConfig& config, TConverter converter)
        {
            return converter.convert(config);
        }
    };

    template <typename TDataType>
	class LoggerCreatorBase
	{
	public:
		virtual ~LoggerCreatorBase() { }
		virtual std::unique_ptr<ILoggerWDataType<TDataType>> create(const LoggerCreationParamsBase& params) = 0;
	};

    template <class TMessageType, class TLoggerType>
    class LoggerMessageCreatorBase
    {
        virtual TMessageType createMessage(TLoggerType&, const LoggerBasicLoggingInfo&) = 0;
        virtual TMessageType createMessage(TLoggerType&, LoggerBasicLoggingInfo&&) = 0;
    };


    // Dummy base classes
    class LoggerDummy : public ILogger
    {
    public:
        void stopLogging() override { }
        bool setLevel(loglevel_type lvl) override { return false; }
        loglevel_type getLevel() const override { return 0; }
    };
    template <typename TDataType>
    class LoggerWDataTypeDummy : public ILoggerWDataType <TDataType>
    {
    public:
        bool processMessage(TDataType& data) override { return false; }
        void stopLogging() override { }
        bool setLevel(loglevel_type lvl) override { return false; }
        loglevel_type getLevel() const override { return 0; }
    };
}

#define LOGGER_CAPTURE_INFO(lvl) logbase::LoggerBasicLoggingInfo( LOG_FUNCTION_MACRO, LOG_LINE_MACRO, lvl )
