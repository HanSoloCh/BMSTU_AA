#include "dataprocess.h"
#include "databaseproc.h"
#include "taskqueue.h"

#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

std::vector<std::string> GetFileNames(const std::string& directoryPath) {
    std::vector<std::string> fileNames;

    // Проверка существования папки и чтение её содержимого
    if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.status())) {
                fileNames.push_back(entry.path().filename().string());
            }
        }
    } else {
        throw std::runtime_error("Unable to open directory: " + directoryPath);
    }

    return fileNames;
}
int main()
{
    TaskQueue<StringTask> q1, q2;
    TaskQueue<RecipeTask> q3;
    TaskQueue<Task> final;

    std::vector<std::string> file_names = GetFileNames("./recipes");
    for (size_t i = 0; i < file_names.size(); ++i) {
        StringTask task(file_names[i], i + 1);
        task.StartWait(0);
        q1.Push(task);
    }
    q1.Push(StringTask());


    Logger log1("log_1.txt"), log2("log_2.txt"), log3("log_3.txt");

    std::thread reader_thread([&] {ReadFile(q1, q2, log1); });
    std::thread parcer_thread([&] {ParceData(q2, q3, log2); });
    std::thread writer_thread([&] {WriteToDataBase(q3, final, log3); });

    reader_thread.join();
    parcer_thread.join();
    writer_thread.join();


    size_t count = 0;
    std::array<clock_t, 3> wait_time_;
    std::array<clock_t, 3> work_time_;

    for (size_t i = 0; i < 3; ++i) {
        wait_time_[i] = 0;
        work_time_[i] = 0;
    }

    while (!final.IsEmpty()) {
        Task task = final.Pop();
        if (task.GetTaskIndex() == -1) {
            break;
        }
        ++count;
        for (size_t i = 0; i < 3; ++i) {
            wait_time_[i] += task.GetWaitTime()[i];
            work_time_[i] += task.GetWorkTime()[i];
        }
    }
    std::ofstream last_log("final_log.txt");

    for (size_t i = 0; i < 3; ++i) {
        last_log << "Work time in " << i + 1 << " " << work_time_[i] * 1000 / count / CLOCKS_PER_SEC << std::endl;
        last_log << "Wait time in " << i + 1 << " " << wait_time_[i] * 1000 / count / CLOCKS_PER_SEC << std::endl;
    }
}
