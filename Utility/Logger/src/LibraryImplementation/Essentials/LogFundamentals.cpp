#if defined(USES_MSVC)
#include "Other/pch.h"
#endif
#include "LogFundamentals.h"

namespace log490
{
    const VoidMessage VoidMessage::voidMsg{};
    Logger Logger::dummyInstance;

    // --------------- Fixed message buffer ---------------------
    Utils::FixedMessageBuffer::FixedMessageBuffer()
    {
        // Use allocated buffer as backing store.
        setp(buffer, buffer + bufferSize);
        // Insert terminator at buffer end.
        buffer[bufferSize] = '\0';
    }

    std::streamsize Utils::FixedMessageBuffer::length()
    {
        return pptr() - pbase(); // offset of the put pointer
    }

    std::streamsize Utils::FixedMessageBuffer::capacity()
    {
        return bufferSize;       
    }

    bool Utils::FixedMessageBuffer::empty()
    {
        return length() == 0;
    }

    bool Utils::FixedMessageBuffer::full()
    {
        return length() == capacity();
    }

    Utils::FixedMessageBuffer::base_class::int_type Utils::FixedMessageBuffer::sunputc()
    {
        if( (!pptr()) || (pptr() == pbase()) )
            return pbackfail();

        pbump(-1);

        return traits_type::to_int_type(*(pptr()+1));
    }

    int Utils::FixedMessageBuffer::peek() const

    {
        if( (!pptr()) || (pptr() == pbase()) )
            return std::char_traits<logchar_t>::eof();

        return static_cast<int>(*(pptr()-1));
    }

    const logchar_t * Utils::FixedMessageBuffer::c_str() const
    {
        *pptr() = '\0';
        return pbase();
    }

    std::streampos Utils::FixedMessageBuffer::seekpos(std::streampos sp, std::ios_base::openmode which)
    {
        return seekoff(sp - pos_type(off_type(0)), std::ios_base::beg, which);
    }

    std::streampos Utils::FixedMessageBuffer::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which)
    {
        if (dir == std::ios_base::cur || dir == std::ios_base::beg)
        {
            #ifdef _MSC_VER
            setp(pbase(), pptr() + off, epptr());
            #else
            // Don't know a better way yet
            pbump(off);
            #endif
        }        
        else if (dir == std::ios_base::end)
        {
            #ifdef _MSC_VER
            setp(pbase(), pptr() - off, epptr());
            #else
            // Don't know a better way yet
            pbump(-((signed)(off)));
            #endif
        }
        return length();
    }


    // --------------- LogMessage class -------------------------
    LogMessage::LogMessage(Logger& lgr) : mLogger{std::ref(lgr)}, flushed{ true }
    {
    }

    LogMessage::LogMessage(Logger& output, level_t level, signature_t signature, line_t line)
        : mLogger{ output }, mLogData{ level, signature, line }, flushed{ false }
    {
    }

    LogMessage::LogMessage(LogMessage&& source) noexcept
        : mLogger(source.mLogger), mLogData{std::move(source.mLogData)}, flushed{ source.flushed }
    {
        source.flushed = true;
    }

    LogMessage::~LogMessage()
    {           
    }

    void LogMessage::flush()
    {
        if (!flushed)
        {
            this->mLogger.get().sendLogMessage(mLogData);
            if (mLogData.message() != nullptr)
                mLogData.message().reset(nullptr);
            flushed = true;
        }
    }

    void LogMessage::free()
    {
        if (!flushed)
        {
            if (mLogData.message() != nullptr)
                mLogData.message().reset(nullptr);
            flushed = true;
        }
    }

    bool LogMessage::isFlushed() const
    {
        return flushed;
    }


    bool LogMessage::hasMessage()
    {
        return mLogData.message() != nullptr;
    }

    const LogData& LogMessage::getData() const
    {
        return mLogData;
    }

    LogData& LogMessage::getDataRef()
    {
        return mLogData;
    }

    Logger& LogMessage::getLogger()
    {
        return mLogger;
    }

    LogMessage& LogMessage::operator=(LogMessage&& right) noexcept
    {
        if (this != &right)
        {
            this->mLogData = std::move(right.mLogData);
            this->flushed = right.flushed;
            this->mLogger = right.mLogger;
            right.flushed = true;
        }
        return *this;
    }

	LogMessage& LogMessage::operator<<(const char* str)
	{
        mLogData.message()->messageStream << str;
        return *this;
	}

	LogMessage& LogMessage::operator<<(const wchar_t* str)
	{
        mLogData.message()->messageStream << str;
        return *this;
	}

	LogMessage& LogMessage::operator<<(std::string&& str)
	{
        return (*this) << str.c_str();
	}

	LogMessage& LogMessage::operator<<(const std::string& str)
	{
        return (*this) << str.c_str();
	}

	LogMessage& LogMessage::operator<<(std::wstring&& str)
	{
        return (*this) << str.c_str();
	}

	LogMessage& LogMessage::operator<<(const std::wstring& str)
	{
        return (*this) << str.c_str();
	}

    LogMessage& LogMessage::operator<<(MsgEndl& mendl)
    {
        mendl.flush(*this);
        return *this;
    }

    LogMessage& LogMessage::operator<<(MsgEndl&& mendl)
    {
        return (*this) << mendl;
    }

    // --------------- LogData struct ---------------------------
    LogData::LogData() 
        : _msgTime{}, _msgUTCTime{}
    {
        callerSignature = "";
        msgLevel = 0;
        msgLine = UINT32_MAX;
    }

	LogData::LogData(level_t level, signature_t signature, line_t line) noexcept
        : msgLevel{level}, msgLine{ line }, callerSignature{ signature },
          _threadID{ std::this_thread::get_id() }, _msgTime(0), _msgUTCTime{}
    {
        _message = std::move(std::make_unique<Utils::FixedBuffStream>());
        //Utils::getUTCTime(_msgUTCTime, _msgTime);
    }

    LogData::LogData(LogData&& source) noexcept
    {
        this->callerSignature = source.callerSignature;
        this->msgLevel = source.msgLevel;
        this->msgLine = source.msgLine;
        this->_msgTime = source._msgTime;
        this->_msgUTCTime = source._msgUTCTime;
        this->_msgHighResTime = source._msgHighResTime;
        this->_threadID = source._threadID;
        this->_message = std::move(source._message);
    }

    LogData& LogData::operator=(LogData&& right) noexcept
    {
        if (this != &right)
        {
            this->callerSignature = right.callerSignature;
            this->msgLevel = right.msgLevel;
            this->msgLine = right.msgLine;
            this->_msgTime = right._msgTime;
            this->_msgUTCTime = right._msgUTCTime;
            this->_msgHighResTime = right._msgHighResTime;
            this->_threadID = right._threadID;
            this->_message = std::move(right._message);
        }
        return *this;
    }

    std::thread::id& LogData::threadID()
    {
        return _threadID;
    }

    logtime_t& LogData::msgTime()
    {
        return _msgTime;
    }

    std::chrono::time_point<highres_t>& LogData::msgHighResTime()
    {
        return _msgHighResTime;
    }

    logtimestruct_t& LogData::msgUTCTime()
    {
        return _msgUTCTime;
    }

    uptr_t<Utils::FixedBuffStream>& LogData::message()
    {
        return _message;
    }

    const std::thread::id& LogData::threadID() const
    {
        return _threadID;
    }

    const logtime_t& LogData::msgTime() const
    {
        return _msgTime;
    }

	const std::chrono::time_point<highres_t>& LogData::msgHighResTime() const
	{
        return _msgHighResTime;
	}

    const logtimestruct_t& LogData::msgUTCTime() const
    {
        return _msgUTCTime;
    }

    const uptr_t<Utils::FixedBuffStream>& LogData::message() const
    {
        return _message;
    }

    void LogData::updateTime()
    {
        #if defined(USES_MSVC)
        _msgHighResTime = std::chrono::high_resolution_clock::now();
        #elif defined(USES_CMAKE)
        _msgHighResTime = std::chrono::steady_clock::now();
        #endif
        _msgTime = time(0);
        Utils::getUTCTime(_msgUTCTime, _msgTime);  
    }


    level_t Logger::getRTLevel() const
    {
        return runtimeLevel;
    }

    bool Logger::logThisLevel(level_t lvl) const
	{
		return (runtimeLevel != 0) && (lvl != 0) && (lvl <= runtimeLevel);
	}

    Logger::Logger() : runtimeLevel{ 0 }
    { }

	bool Logger::sendLogMessage(LogData& data)
	{
		return false;
	}

	void Logger::setRTLevel(level_t newLevel)
    {
        runtimeLevel = newLevel;
    }

    // --------------- Utility ----------------------------------
    void Utils::getLocaltime(logtimestruct_t& to, logtime_t& from)
    {
        // I've read that localtime is kind of finicky with multithreading
        #ifndef _MSC_VER
        to = *localtime(&from);
        #else
        localtime_s(&to, &from);
        #endif //  _C     
    }

    void Utils::getUTCTime(logtimestruct_t& to, logtime_t& from)
    {          
        // gmtime is kind of finicky with multithreading too
        #ifndef _MSC_VER
        to = *gmtime(&from);
        #else
        gmtime_s(&to, &from);
        #endif //  _C       
    }


    Utils::FixedBuffStream::FixedBuffStream()
        : messageBuffer{}, messageStream{ &messageBuffer }
    { }

    void MsgEndl::flush(LogMessage& msg) const
    {
        if (!msg.isFlushed())
            msg.flush();
    }

    void MsgEndl::cancel(LogMessage& msg) const
    {
        if (!msg.isFlushed())
            msg.free();
    }

    void VoidMessage::flush()
    {
    }

    void VoidMessage::free()
    {
    }

    bool VoidMessage::isFlushed() const
    {
        return false;
    }

}

