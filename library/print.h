#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <source_location>
#include <string_view>

// std::cout << "Class " << typeid(Application).name() << std::endl;
// int status;
// char * demangled = abi::__cxa_demangle(typeid(this).name(),0,0,&status);
// std::cout << "Class " << demangled << std::endl;
// free(demangled);

// void log(const std::string_view message = "",
//          const std::source_location location =
//                std::source_location::current())
// {
//     std::clog << "file: "
//               << location.file_name() << '('
//               << location.line() << ':'
//               << location.column() << ") `"
//               << location.function_name() << "`: "
//               << message << '\n';
// }

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include "thread_sync.h"

#define FUNCTION_NAME __PRETTY_FUNCTION__

/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

class ConsolePrintI
{
public:
    explicit ConsolePrintI() {}
    virtual ~ConsolePrintI() {}

    virtual void SetLevel(int xArg) {}
    virtual void SetTimestamp(bool xArg) {}
    virtual void Print(const char* fmt, ...) {}
    virtual void Print(const std::string& str) {}
    virtual void PrintError(const char* fmt, ...) {}
    virtual void PrintError(const std::string& str) {}
    virtual void PrintNotice(const char* fmt, ...) {}
    virtual void PrintWarning(const char* fmt, ...) {}
    virtual void PrintTrace(const char* fmt, ...) {}

private:
};

class ConsolePrint : public ConsolePrintI
{
public:
    explicit ConsolePrint() {}
    virtual ~ConsolePrint() {}

    static constexpr int ALL = 5;
    static constexpr int NOTICE_LEVEL = 4;
    static constexpr int WARNING_LEVEL = 3;
    static constexpr int CRITICAL_LEVEL = 2;
    static constexpr int FATAL_LEVEL = 1;
    static constexpr int NONE_LEVEL = 0;

    void SetLevel(int xArg)
    {
        level = xArg;
    }

    void Print(const char* fmt, ...) final
    {
        mutex.Acquire();

        if (level >= ALL)
        {
            va_list args;
            va_start(args, fmt);
            int len = vsnprintf(NULL, 0, fmt, args);
            va_end(args);

            va_start(args, fmt);
            vsnprintf(msg, len + 1, fmt, args);
            va_end(args);
            
            if (timestampIsEnable)
            {
                printf("%ld:%ld:%ld:%ld:%ld %s\r\n",
                        timestamp.hour,
                        timestamp.min,
                        timestamp.sec,
                        timestamp.msec,
                        timestamp.usec,
                        msg);
            }
            else
            {
                printf("%s\r\n", msg);
            }
        }

        mutex.Release();
    }

    void Print(const std::string& str) final
    {
        mutex.Acquire();
        std::cout.flush();
        std::cout << str << std::endl;
        std::cout.flush();
        mutex.Release();
    }

    void PrintError(const char* fmt, ...) final
    {
        mutex.Acquire();

        if (level >= FATAL_LEVEL)
        {
            va_list args;
            va_start(args, fmt);
            int len = vsnprintf(NULL, 0, fmt, args);
            va_end(args);

            va_start(args, fmt);
            vsnprintf(msg, len + 1, fmt, args);
            va_end(args);
            
            printf("\n\033[1;31m%s\033[0m\n\n", msg);
        }

        mutex.Release();
    }

    void PrintError(const std::string& str) final
    {
        mutex.Acquire();
        std::cout.flush();
        std::cout << "\n\033[1;31m" << str << "\033[0m\n" << std::endl;
        std::cout.flush();
        mutex.Release();
    }

    void PrintNotice(const char* fmt, ...) final
    {
        mutex.Acquire();

        if (level >= NOTICE_LEVEL)
        {
            va_list args;
            va_start(args, fmt);
            int len = vsnprintf(NULL, 0, fmt, args);
            va_end(args);

            va_start(args, fmt);
            vsnprintf(msg, len + 1, fmt, args);
            va_end(args);
            
            printf("\033[0;35m%s\033[0m\n", msg);
        }

        mutex.Release();
    }

    void PrintWarning(const char* fmt, ...) final
    {
        mutex.Acquire();

        if (level >= WARNING_LEVEL)
        {
            va_list args;
            va_start(args, fmt);
            int len = vsnprintf(NULL, 0, fmt, args);
            va_end(args);

            va_start(args, fmt);
            vsnprintf(msg, len + 1, fmt, args);
            va_end(args);
            
            printf("\033[0;33m%s\033[0m\n", msg);
        }

        mutex.Release();
    }

    void PrintTrace(const char* fmt, ...) final
    {
        mutex.Acquire();

        if (level >= ALL)
        {
            va_list args;
            va_start(args, fmt);
            int len = vsnprintf(NULL, 0, fmt, args);
            va_end(args);

            va_start(args, fmt);
            vsnprintf(msg, len + 1, fmt, args);
            va_end(args);
            
            printf("\033[0;32m%s\033[0m\n", msg);
        }

        mutex.Release();
    }

    void SetTimestamp(bool xArg) { timestampIsEnable = xArg; }

private:
    char msg[1024];
    Mutex mutex;
    int level = 0;
    struct {
        uint64_t hour;
        uint64_t min;
        uint64_t sec;
        uint64_t msec;
        uint64_t usec;
    } timestamp;
    bool timestampIsEnable = true;
};

extern ConsolePrintI* console;
#define Print(...) console->Print(__VA_ARGS__);
#define PrintError(...) console->PrintError(__VA_ARGS__);
#define PrintNotice(...) console->PrintNotice(__VA_ARGS__);
#define PrintWarning(...) console->PrintWarning(__VA_ARGS__);
#define PrintTrace(...) console->PrintTrace(__VA_ARGS__);
#define EnableTimestamp console->SetTimestamp(true);
#define DisableTimestamp console->SetTimestamp(false);

#endif

