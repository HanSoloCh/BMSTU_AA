#ifndef TASK_H
#define TASK_H

#include <array>
#include <string>
#include <sys/types.h>
#include <vector>
#include <sstream>

class Task
{
public:
    explicit Task(ssize_t task_index = -1);

    virtual ~Task();

    ssize_t GetTaskIndex() const;
    std::array<clock_t, 3> GetWaitTime() const;
    std::array<clock_t, 3> GetWorkTime() const;

    void StartWait(size_t queue_ind);
    void StopWait(size_t queue_ind);

    void StartWork(size_t queue_ind);
    void StopWork(size_t queue_ind);

    std::array<clock_t, 3> wait_time_;
    std::array<clock_t, 3> work_time_;
private:
    ssize_t task_index_;

};

class RecipeTask;

class StringTask : public Task {
public:
    explicit StringTask(ssize_t task_index = -1): Task(task_index) {}
    StringTask(const RecipeTask &recipe_task, const std::string &string_data);
    StringTask(const std::string &string_data, ssize_t task_index = -1);

    std::string GetStringData() const;
    void SetStringData(const std::string &str);

private:
    std::string string_data_;
};


class RecipeTask : public Task {
public:
    explicit RecipeTask(ssize_t task_index = -1): Task(task_index) {}
    RecipeTask(const StringTask &string_task, const std::string &recipe_data);
    RecipeTask(const std::string &recipe_data, ssize_t task_index = -1);

    std::string GetUrl() const {
        return recipe_url_;
    };

    std::string GetName() const {
        return recipe_name_;
    };

    std::vector<std::array<std::string, 3>> GetIngredients() const {
        return recipe_ingredients_;
    };

    std::vector<std::string> GetSteps() const {
        return recipe_steps_;
    }


private:
    void ParseIngredients(std::istringstream &iss);
    void ParseRecipe(std::istringstream &iss);

    std::string recipe_url_;
    std::string recipe_name_;
    std::vector<std::array<std::string, 3>> recipe_ingredients_;
    std::vector<std::string> recipe_steps_;
};

#endif // TASK_H
