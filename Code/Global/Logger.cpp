// global includes    //////////////////////////////
#include "Global.h"

// includes ////////////////////////////////////////
#include "Logger.h"
#include <iomanip>
#if defined(_WIN32)
#include <strsafe.h>
#else
#include <stdio.h>
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
#include <chrono>
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
            std::time_t now = std::time(nullptr);
            std::tm tm = *std::localtime(&now);
            m_time_sstr << std::setfill('0') << std::setw(2) << tm.tm_mday << "/";
            m_time_sstr << std::setfill('0') << std::setw(2) << tm.tm_mon << "/";
            m_time_sstr << tm.tm_year + 1900 << " ";
            m_time_sstr << std::setfill('0') << std::setw(2) << tm.tm_hour << ":";
            m_time_sstr << std::setfill('0') << std::setw(2) << tm.tm_min << ":";
            m_time_sstr << std::setfill('0') << std::setw(2) << tm.tm_sec << " ";
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

    bool MessageConsole(unsigned char type, const char* fmt, ...)
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

        char* text;
        va_list args;

        va_start(args, fmt);
        int len = _vscprintf(fmt, args) + 1;
        if (len <= 0) { va_end(args); return false; }
        text = my_new char[len];
#ifdef _WIN32
        vsnprintf(text, len, fmt, args);
#else
        vsnprintf(text, len, fmt, args);
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
