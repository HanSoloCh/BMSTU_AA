#include "dataprocess.h"

#include <sstream>
#include <string>
#include <codecvt>

void ReadFile(TaskQueue<StringTask> &input_queue,
              TaskQueue<StringTask> &output_queue,
              Logger &logger) {
    while (true) {
        if (!input_queue.IsEmpty()) {
            StringTask task = input_queue.Pop();
            ssize_t task_index = task.GetTaskIndex();
            if (task_index == -1) {
                output_queue.Push(StringTask());
                break;
            }
            task.StopWait(0);
            task.StartWork(0);
            logger.log("task " + std::to_string(task_index) + " 1 stage processing");
            // Обработка задачи

            std::ifstream file(task.GetStringData());
            file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
            std::stringstream wss;
            wss << file.rdbuf();
            task.SetStringData(wss.str());
            file.close();
            task.StopWork(0);
            task.StartWait(1);
            output_queue.Push(task);
            logger.log("task " + std::to_string(task_index) + " 1 stage complete");
        }
    }
}

void ParceData(TaskQueue<StringTask> &input_queue,
               TaskQueue<RecipeTask> &output_queue,
               Logger &logger) {
    while (true) {
        if (!input_queue.IsEmpty()) {
            StringTask task = input_queue.Pop();
            ssize_t task_index = task.GetTaskIndex();
            if (task_index == -1) {
                output_queue.Push(RecipeTask());
                break;
            }
            task.StopWait(1);

            task.StartWork(1);
            logger.log("task " + std::to_string(task_index) + " 2 stage processing");
            // Обработка задачи
            RecipeTask recipe_task(task, task.GetStringData());
            task.StopWork(1);

            task.StartWait(2);
            output_queue.Push(recipe_task);
            logger.log("task " + std::to_string(task_index) + " 2 stage complete");
        }
    }
}
