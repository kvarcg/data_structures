#ifndef LOGGER_H
#define LOGGER_H

// includes ////////////////////////////////////////


// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace BASELIB
{
    class BaseLoggerImpl {
    public:
        virtual ~BaseLoggerImpl();
        virtual void Lock() = 0;
        virtual void Unlock() = 0;
        virtual void GetLogCurrentTime() = 0;
        virtual void OpenForWriting(const char* name) = 0;
        virtual void CloseForWriting() = 0;
        virtual void PreparePrint(const char* text) = 0;
        virtual void AppendFileMessage(const char* text) = 0;
        virtual void AppendConsoleMessage(const char* text) = 0;
    };

    class Logger
    {
    protected:
        // protected variable declarations

        class BaseLoggerImpl*                m_impl;
        unsigned char                        m_file_filter_mask;
        unsigned char                        m_console_filter_mask;
        unsigned char                        m_location_mask;

        // protected function declarations


    private:
        // private variable declarations


        // private function declarations


    public:

        // Constructor
        Logger(void);

        // Destructor
        ~Logger(void);

        // public function declarations

        bool                                PrintMessage(const char* text, bool valid_file, bool valid_console);

        void                                OpenForWriting(const char* name);
        void                                CloseForWriting(void);

        void                                Clear(void);
        void                                Destroy(void);
        void                                Lock(void)                                  { m_impl->Lock(); }
        void                                Unlock(void)                                { m_impl->Unlock(); }

        // get functions
        unsigned char                        GetLogConsoleFilter(void)                  {return m_console_filter_mask;}
        unsigned char                        GetLogFileFilter(void)                     {return m_file_filter_mask;}
        unsigned char                        GetLogLocation(void)                       {return m_location_mask;}


        // set functions
        void                                SetLogConsoleFilter(unsigned char filter_mask);
        void                                SetLogFileFilter(unsigned char filter_mask);
        void                                SetLogLocation(unsigned char location_mask);
        bool                                IsWriteToFileEnabled(void);
        bool                                IsWriteToConsoleEnabled(void);
        bool                                IsConsoleFilterTypeEnabled(unsigned char type);
        bool                                IsFileFilterTypeEnabled(unsigned char type);

    };

    bool                                 MessageConsole(unsigned char type, const char* fmt, ...);

} // namespace BASELIB

#endif //LOGGER_H

// eof ///////////////////////////////// class Logger
