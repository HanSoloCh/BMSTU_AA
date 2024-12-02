#include "task.h"

#include <sstream>

#include <regex>

static std::string prepareSentence(const std::string &str) {
    auto startIt = str.begin();
    auto endIt = str.rbegin();
    while (std::isspace(*startIt))
        ++startIt;
    while (std::isspace(*endIt))
        ++endIt;
    return std::string(startIt, endIt.base());
}



Task::Task(ssize_t task_index)
    : task_index_(task_index) {};

Task::~Task() {}

ssize_t Task::GetTaskIndex() const {
    return task_index_;
}

#include <iostream>

void Task::StartWait(size_t queue_ind) {
    wait_time_[queue_ind] = clock();
};

void Task::StartWork(size_t queue_ind) {
    work_time_[queue_ind] = clock();
};

void Task::StopWait(size_t queue_ind) {
    wait_time_[queue_ind] = clock() - wait_time_[queue_ind];
};

void Task::StopWork(size_t queue_ind) {
    work_time_[queue_ind] = clock() - work_time_[queue_ind];
};

StringTask::StringTask(const RecipeTask &recipe_task, const std::string &string_data)
    : Task(recipe_task)
    , string_data_(string_data) {}

StringTask::StringTask(const std::string &string_data, ssize_t task_index)
    : Task(task_index),
    string_data_(string_data) {};


std::string StringTask::GetStringData() const {
    return string_data_;
}

void StringTask::SetStringData(const std::string &str) {
    string_data_ = str;
}


RecipeTask::RecipeTask(const StringTask &string_task, const std::string &recipe_data)
    : Task(string_task) {
    std::istringstream iss(recipe_data);
    std::getline(iss, recipe_url_);
    std::getline(iss, recipe_name_);
    ParseIngredients(iss);
    ParseRecipe(iss);
}

RecipeTask::RecipeTask(const std::string &recipe_data, ssize_t task_index)
    : Task(task_index) {
    std::istringstream iss(recipe_data);
    std::getline(iss, recipe_url_);
    std::getline(iss, recipe_name_);
    ParseIngredients(iss);
    ParseRecipe(iss);
}

void RecipeTask::ParseIngredients(std::istringstream &iss) {
    std::string line;
    std::getline(iss, line);
    std::regex pattern(R"((.+?)\s+((\d+|\bпо вкусу\b))\s+(\S+|\b-\b))");
    std::smatch match;

    while (std::getline(iss, line) && line != "Рецепт:") {

        if (std::regex_match(line, match, pattern)) {
            std::string name = match[1].str();
            std::string amount = match[2].str();
            std::string unit = match[4].str();

            if (amount == "по вкусу") {
                amount = "-";
                unit = "-";
            }
            recipe_ingredients_.push_back({name, amount, unit});
        }
    }

}

void RecipeTask::ParseRecipe(std::istringstream &iss) {
    std::string recipe_line, full_recipe;

    while (std::getline(iss, recipe_line)) {
        full_recipe += recipe_line + " ";
    }
    std::regex pattern(R"(([^.]+?\.)\s*)");
    std::sregex_iterator begin(full_recipe.begin(), full_recipe.end(), pattern);
    std::sregex_iterator end;
    for (auto it = begin; it != end; ++it) {
        recipe_steps_.push_back(prepareSentence(it->str()));
    }
}
std::array<clock_t, 3> Task::GetWaitTime() const { return wait_time_; }

std::array<clock_t, 3> Task::GetWorkTime() const {return work_time_; }
