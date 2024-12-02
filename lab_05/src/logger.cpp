#include "logger.h"

#include <chrono>
#include <sstream>
#include <iomanip>


Logger::Logger(const std::string &file_name) {
    log_file_.open(file_name);
    if (!log_file_) {
        throw std::runtime_error("Unable to open log file: " + file_name);
    }
}

Logger::~Logger() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

std::string Logger::GetTime() {
    std::ostringstream oss;

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()
                            ) % 1000;
    oss << std::put_time(std::localtime(&time_t_now), "%H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();

    // auto time = clock();
    // oss << time;

    return oss.str();
}


void Logger::log(const std::string &message) {
    std::string time_stamp = GetTime();
    log_file_ << "[" + time_stamp + "] " + message << std::endl;
}
