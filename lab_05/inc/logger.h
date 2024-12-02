#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger
{
public:
    explicit Logger(const std::string &file_name);
    ~Logger();

    void log(const std::string &message);


private:
    std::string GetTime();

    std::ofstream log_file_;
};

#endif // LOGGER_H
