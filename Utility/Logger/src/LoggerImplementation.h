#ifndef LOGGERLIBRARY_LOGGERIMPLEMENTATION_H
#define LOGGERLIBRARY_LOGGERIMPLEMENTATION_H

/* Implementation of filelogger classes */
#include "LibraryImplementation/Essentials/LogFundamentals.h"
#include "LibraryImplementation/Filelogger/filelogger.h"
#include "LibraryImplementation/Filelogger/filelogger_Messages.h"

#include "LibraryImplementation/Filelogger/Lv490XMLServer/XMLParserConfigConverter.h"

namespace filelog
{
	using flogger_message_type = filelog::FilteredFileLogMessage;
}

#ifndef SLOG_LEVEL
#define SLOG_LEVEL(logger, level) filelog::flogger_message_type{ logger, logbase::LoggerBasicLoggingInfo { LOG_FUNCTION_MACRO, LOG_LINE_MACRO, level } }
#endif

#ifndef SLOG_ENDL
#define SLOG_ENDL filelog::MsgEndl()
#endif

#ifndef VOID_LOG
/* Message object that does nothing */
#define VOID_LOG log490::VoidMessage::voidMsg
#endif // !VOID_LOG

#ifndef SLOG_NOTHING
/* Message macro that does cretes VOID_LOG */
#define SLOG_NOTHING VOID_LOG
#endif // !SLOD_NOTHING

#define LOGGER_OPERATOR(typeSig) template <>\
inline filelog::flogger_message_type & filelog::flogger_message_type ::operator<<<typeSig>

LOGGER_OPERATOR(std::string)(std::string&& param)
{
(*this) << param.c_str();
return *this;
}
LOGGER_OPERATOR(std::string)(const std::string& param)
{
(*this) << param.c_str();
return *this;
}

#endif //LOGGERLIBRARY_LOGGERIMPLEMENTATION_H
