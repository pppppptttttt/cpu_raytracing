#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

enum class Severity
{
    DEBUG=0, INFO=1, WARNING=2, ERROR=3, DEFAULT=4
};

struct LoggerConfig
{
    bool OutputToConsole;
    bool OutputToFile;
    std::string FilePath;
    Severity Sev;
    LoggerConfig() : OutputToConsole(true), OutputToFile(false), Sev(Severity::DEBUG) {}
};

class LOG
{
public:
    LOG( Severity sev = Severity::DEFAULT ) : msg_sev(sev) {}
   ~LOG()
    {
        log(oss.str());
    }

    template<typename Type>
    LOG& operator<<( const Type& s )
    {
        oss << s;
        return *this;
    }

private:
    void log( const std::string& msg )
    {
        if (msg_sev < LoggerConfigInstance().Sev)
            return;
        std::string Header;
        switch(msg_sev)
        {
        case Severity::DEBUG:
            Header = "[DEBUG]";
            break;
        case Severity::INFO:
            Header = "[INFO]";
            break;
        case Severity::WARNING:
            Header = "[WARNING]";
            break;
        case Severity::ERROR:
            Header = "[ERROR]";
            break;
        default:
            Header = "";
            break;
        }

        if (LoggerConfigInstance().OutputToConsole)
            std::clog << Header << msg << std::endl;
        if (LoggerConfigInstance().OutputToFile)
        {
            std::ofstream f;
            static bool first_entrance = true;
            if (first_entrance)
            {
                first_entrance = false;
                f.open(LoggerConfigInstance().FilePath, std::ios::trunc);
            }
            else
                f.open(LoggerConfigInstance().FilePath, std::ios::app);
            if (f)
                f << Header << msg << std::endl;
            else
                std::clog << "[ERROR]Can't open " << LoggerConfigInstance().FilePath << " log file" << std::endl;
        }
    }

    std::ostringstream oss;
    Severity msg_sev;

public:
    static LoggerConfig& LoggerConfigInstance()
    {
        static LoggerConfig instance;
        return instance;
    }
};