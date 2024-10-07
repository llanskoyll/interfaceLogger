#include <log/log.h>

#include <iostream> 

void log::LogFile::logging(std::string pathSave) {
    stream.open(pathSave);
    if (!stream.is_open()) {
        std::cerr << "Failed to open log file" << std::endl;
        exit(1);
    }

    std::string message;
    while (1) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cond.wait(lock, [this]() -> bool {
                return !queue_.empty();
            });

            message = queue_.front();
            queue_.pop_front();
        }
        stream << message << std::endl;
    }

    stream.close();
}

void log::LogFile::pushLog(std::string &&message) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push_back(message);
    cond.notify_one();
}
