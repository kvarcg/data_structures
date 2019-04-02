// global includes    //////////////////////////////
#include "Global.h"

// includes ////////////////////////////////////////
#include "Logger.h"
#if defined(_WIN32)
#include <strsafe.h>
#else
#include <stdarg.h>
int _vscprintf(const char * format, va_list pargs) {
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(nullptr, 0, format, argcopy);
    va_end(argcopy);
    return retval;
}
#endif
#include <time.h>       /* time_t, struct tm, time, localtime, asctime */
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <mutex>
#include <fstream>
#include <sstream>
// defines /////////////////////////////////////////
static BASELIB::Logger m_logger;

namespace BASELIB
{
    class LoggerImpl final : public BaseLoggerImpl {
    private:
        std::ofstream                        m_ofstream;
        std::string                            m_time_str;
        std::string                            m_name;
        std::mutex                            m_message_mutex;
        friend class Logger;
    public:

        LoggerImpl() = default;
        ~LoggerImpl() override;
        LoggerImpl(const LoggerImpl&) = default;
        LoggerImpl& operator=(const LoggerImpl&) = default;

        std::mutex& getMutex() { return m_message_mutex; }

        void GetLogCurrentTime() override
        {
            std::stringstream m_time_sstr;

#ifdef WIN32
            struct tm newtime;
            __time64_t long_time;
            // Get time as 64-bit integer.
            _time64(&long_time);
            // Convert to local time.
            int err = _localtime64_s(&newtime, &long_time);
            if (err) return;
            if (newtime.tm_mday < 10) m_time_sstr << "0";
            m_time_sstr << newtime.tm_mday << "/";
            if (newtime.tm_mon < 10) m_time_sstr << "0";
            m_time_sstr << newtime.tm_mon << "/";
            m_time_sstr << newtime.tm_year + 1900 << " ";
            if (newtime.tm_hour < 10) m_time_sstr << "0";
            m_time_sstr << newtime.tm_hour << ":";
            if (newtime.tm_min < 10) m_time_sstr << "0";
            m_time_sstr << newtime.tm_min << ":";
            if (newtime.tm_sec < 10) m_time_sstr << "0";
            m_time_sstr << newtime.tm_sec << " ";
#else
            time_t rawtime;
            time(&rawtime);
            struct tm* newtime = localtime(&rawtime);
            if (newtime->tm_mday < 10) m_time_sstr << "0";
            m_time_sstr << newtime->tm_mday << "/";
            if (newtime->tm_mon < 10) m_time_sstr << "0";
            m_time_sstr << newtime->tm_mon << "/";
            m_time_sstr << newtime->tm_year + 1900 << " ";
            if (newtime->tm_hour < 10) m_time_sstr << "0";
            m_time_sstr << newtime->tm_hour << ":";
            if (newtime->tm_min < 10) m_time_sstr << "0";
            m_time_sstr << newtime->tm_min << ":";
            if (newtime->tm_sec < 10) m_time_sstr << "0";
            m_time_sstr << newtime->tm_sec << " ";
#endif

            m_time_str = m_time_sstr.str().c_str();
        }

        void OpenForWriting(const char* name) override
        {
            if (!m_ofstream.is_open())
            {
                m_ofstream.open(name);
                m_name = name;
            }
        }

        void CloseForWriting() override
        {
            if (m_ofstream.is_open()) {
                m_ofstream.close();
            }
        }

        void PreparePrint(const char* text) override {
            GetLogCurrentTime();
#if defined (_WIN32) && defined (_MSC_VER)
            OutputDebugStringA(LPCSTR(m_time_str.c_str()));
            OutputDebugStringA(LPCSTR(text));
#else
#endif
        }
        void AppendFileMessage(const char* text) override {
            if (m_ofstream.is_open())
            {
                m_ofstream << m_time_str.c_str() << text;
                CloseForWriting();
                m_ofstream.open(m_name.c_str(), std::ofstream::app);
            }
        }

        void AppendConsoleMessage(const char* text) override {
            std::cout << text << std::flush;
        }

        void Lock() override {
            m_message_mutex.lock();
        }

        void Unlock() override {
            m_message_mutex.unlock();
        }
    };

    BaseLoggerImpl::~BaseLoggerImpl() {}
    LoggerImpl::~LoggerImpl() {}

    static std::string idstring = std::string("random");

    // Constructor
    Logger::Logger()
    {
        m_impl = my_new LoggerImpl();

        unsigned char log_entry = 0;

        log_entry |= CM_LOGGER_COMMENT;
        log_entry |= CM_LOGGER_WARNING;
        log_entry |= CM_LOGGER_ERROR;
        SetLogConsoleFilter(log_entry);
        SetLogFileFilter(log_entry);

        OpenForWriting("./Logs/Log.txt");

        unsigned char location_entry = 0;
        location_entry |= CM_LOGGER_FILE;
        location_entry |= CM_LOGGER_CONSOLE;

        SetLogLocation(location_entry);

        unsigned char log_all_entry = 0;
        log_all_entry |= CM_LOGGER_COMMENT;
        log_all_entry |= CM_LOGGER_EVENT;
        log_all_entry |= CM_LOGGER_WARNING;
        log_all_entry |= CM_LOGGER_ERROR;
    }

    // Destructor
    Logger::~Logger()
    {
        Destroy();
    }

    // other functions
    void Logger::OpenForWriting(const char* name)
    {
        m_impl->OpenForWriting(name);
    }

    void Logger::Clear()
    {

    }

    void Logger::Destroy()
    {
        XE_SAFE_DELETE(m_impl);
    }

    void Logger::CloseForWriting()
    {
        m_impl->CloseForWriting();
    }

    void Logger::SetLogConsoleFilter(unsigned char filter_mask)
    {
        m_console_filter_mask = filter_mask;
    }

    void Logger::SetLogFileFilter(unsigned char filter_mask)
    {
        m_file_filter_mask = filter_mask;
    }

    void Logger::SetLogLocation(unsigned char location_mask)
    {
        m_location_mask = location_mask;
    }

    bool Logger::IsWriteToFileEnabled()
    {
        return (m_location_mask & CM_LOGGER_FILE) > 0;
    }

    bool Logger::IsWriteToConsoleEnabled()
    {
        return (m_location_mask & CM_LOGGER_CONSOLE) > 0;
    }

    bool Logger::IsConsoleFilterTypeEnabled(unsigned char type)
    {
        return (m_console_filter_mask & type) > 0;
    }

    bool Logger::IsFileFilterTypeEnabled(unsigned char type)
    {
        return (m_file_filter_mask & type) > 0;
    }

    bool MessageConsole(unsigned char type, const char * fmt, ...)
    {
        m_logger.Lock();

        bool valid_file = m_logger.IsFileFilterTypeEnabled(type);
        bool valid_console = m_logger.IsConsoleFilterTypeEnabled(type);
        if (!valid_console && !valid_file) {
            m_logger.Unlock();
            return true;
        }

        if (fmt == nullptr) {
            m_logger.Unlock();
            return false;
        }

        auto myid = std::this_thread::get_id();
        std::stringstream ss;
        ss << myid;
        std::string curidstring = ss.str();

        if (curidstring.compare(idstring) != 0)
        {
            if (idstring.compare("random") != 0)
            {
                bool valid_file = m_logger.IsFileFilterTypeEnabled(CM_LOGGER_COMMENT);
                bool valid_console = m_logger.IsConsoleFilterTypeEnabled(CM_LOGGER_COMMENT);
                if (valid_console || valid_file)
                {
                    std::string print = "Comment: Changed thread from: ";
                    print.append(idstring).append(" to ").append(curidstring).append("\n");
                    m_logger.PrintMessage(print.c_str(), valid_file, valid_console);
                }
            }
            else
            {
                bool valid_file = m_logger.IsFileFilterTypeEnabled(CM_LOGGER_COMMENT);
                bool valid_console = m_logger.IsConsoleFilterTypeEnabled(CM_LOGGER_COMMENT);
                std::string print = "Started Logger\n";
                m_logger.PrintMessage(print.c_str(), valid_file, valid_console);
                if (valid_console || valid_file)
                {
                    print = "Comment: Current thread is: ";
                    print.append(curidstring).append("\n");
                    m_logger.PrintMessage(print.c_str(), valid_file, valid_console);
                }
            }
            idstring = curidstring;
        }

#ifdef _WIN32
        char* text;                                    // Holds Our String
        va_list args;                                // Pointer To List Of Arguments

        va_start(args, fmt);                        // Parses The String For Variables
        int len = _vscprintf(fmt, args) + 1;        // _vscprintf doesn't count
        text = my_new char[len];
        vsprintf_s(text, len, fmt, args);            // And Converts Symbols To Actual Numbers
        va_end(args);                                // Results Are Stored In Text
#else
        char* text;                                    // Holds Our String
        va_list args;                                // Pointer To List Of Arguments

        va_start(args, fmt);                        // Parses The String For Variables
        int len = _vscprintf(fmt, args) + 1;        // _vscprintf doesn't count
        text = my_new char[len];
        vsprintf_s(text, len, fmt, args);            // And Converts Symbols To Actual Numbers
        va_end(args);                                // Results Are Stored In Text
#endif

        m_logger.PrintMessage(text, valid_file, valid_console);

        XE_SAFE_DELETE_POINTER(text)

        m_logger.Unlock();

        return true;
    }

    bool Logger::PrintMessage(const char* text, bool valid_file, bool valid_console)
    {
        if (m_location_mask != CM_LOGGER_NOWHERE)
        {
            m_impl->PreparePrint(text);
        }

        if (m_location_mask & CM_LOGGER_FILE && valid_file)
        {
            m_impl->AppendFileMessage(text);
        }

        if (m_location_mask & CM_LOGGER_CONSOLE && valid_console)
        {
            m_impl->AppendConsoleMessage(text);
        }

        return true;
    }

} // namespace BASELIB

// eof ///////////////////////////////// class Logger
