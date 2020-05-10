#pragma once
#ifndef LOGGERLIBRARY_H
#define LOGGERLIBRARY_H


//
// Compile time log levels
#ifndef CTLVL_NOLOGS
#define CTLVL_NOLOGS  0 
#endif 

#ifndef CTLVL_PROD
#define CTLVL_PROD    1 
#endif

#ifndef CTLVL_DEBUG
#define CTLVL_DEBUG   2
#endif 

#ifndef CTLVL_TRACE
#define CTLVL_TRACE   3
#endif 
//
//

#ifndef CTIME_LOG_LEVEL
/* Current compile time log level */
#define CTIME_LOG_LEVEL CTLVL_TRACE
#endif // !CTIME_LOG_LEVEL

//
//
//
//
//
//
//
//
//
//
//

#include "ILogger.h"

#if !defined(LOGGER_DISABLE_DEFAULT_FILELOGGER)
/* This header MUST define LOGGER_INTERFACE_TYPE SLOG_LEVEL */
#include "LoggerImplementation.h"
#endif

#if !defined(SLOG_LEVEL)
static_assert(false, "Logger library requires definition SLOG_LEVEL macro!"); }
#endif

/* This header uses defines LOGGER_INTERFACE_TYPE and SLOG_LEVEL
 * They should be supplied by some header before inclusion of these one */
#include "StaticLogging.h"


#if CTLVL_PROD <= CTIME_LOG_LEVEL
#ifndef SLOG_PROD
/* Creates message with Prod level value */
#define SLOG_PROD(logger) SLOG_LEVEL(logger, CTLVL_PROD)
#endif
#else
#ifndef SLOG_PROD
/* Creates VOID_LOG */
#define SLOG_PROD(logger) SLOG_NOTHING
#endif
#endif

#if CTLVL_DEBUG <= CTIME_LOG_LEVEL
#ifndef SLOG_DEBUG
/* Creates message with Debug level value */
#define SLOG_DEBUG(logger) SLOG_LEVEL(logger, CTLVL_DEBUG)
#endif
#else
#ifndef SLOG_DEBUG
#define SLOG_DEBUG(logger) SLOG_NOTHING
#endif
#endif

#if CTLVL_TRACE <= CTIME_LOG_LEVEL
#ifndef SLOG_TRACE
/* Creates message with Trace level value */
#define SLOG_TRACE(logger) SLOG_LEVEL(logger, CTLVL_TRACE)
#endif
#else
#ifndef SLOG_TRACE
/* Creates VOID_LOG */
#define SLOG_TRACE(logger) SLOG_NOTHING
#endif
#endif

#endif // !LOGGERLIBRARY_H

