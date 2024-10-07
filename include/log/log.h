#pragma once

#include <deque>
#include <mutex>
#include <condition_variable>
#include <fstream> 
namespace log {

class Log {
public:
    virtual ~Log() = default;
    virtual void logging(std::string pathSave) = 0;
    virtual void pushLog(std::string &&message) = 0;
};

class LogFile : public Log {
public:
    void logging(std::string pathSave) override;
    void pushLog(std::string &&message) override;

private:
    std::ofstream stream;
    std::deque<std::string> queue_;
    std::mutex mutex_;
    std::condition_variable cond;
};

} // namespace log
