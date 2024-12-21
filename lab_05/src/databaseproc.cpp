#include "databaseproc.h"


#include <sqlite3.h>
#include <iostream>


void saveRecipeToDatabase(sqlite3 *db, const RecipeTask &recipe) {
    std::string ingredients_str;
    for (const auto &ingredient : recipe.GetIngredients()) {
        ingredients_str += ingredient[0] + "(" + ingredient[1] + " " + ingredient[2] + ")|";
    }
    if (!ingredients_str.empty()) {
        ingredients_str.pop_back();
    }
    std::string steps_str;
    for (const auto &step : recipe.GetSteps()) {
        steps_str += step + " ";
    }
    if (!steps_str.empty()) {
        steps_str.pop_back();
    }
    std::string url = recipe.GetUrl();
    std::string name = recipe.GetName();
    std::string sql = "INSERT INTO recipes (id, issue_id, url, title, ingredients, steps) VALUES (?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, recipe.GetTaskIndex());
    sqlite3_bind_int(stmt, 2, 9171);
    sqlite3_bind_text(stmt, 3, url.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, ingredients_str.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, steps_str.c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

sqlite3 *createDataBase(const char *database_name) {
    sqlite3 *db;
    if (sqlite3_open(database_name, &db)) {
        throw std::runtime_error("Error creating table" + std::string(sqlite3_errmsg(db)));
    }

    const char *create_table = R"(
        CREATE TABLE IF NOT EXISTS recipes (
            id INTEGER PRIMARY KEY,
            issue_id INTEGER,
            url TEXT,
            title TEXT,
            ingredients TEXT,
            steps TEXT
        );
    )";
    char *error_message = nullptr;
    int rc = sqlite3_exec(db, create_table, nullptr, nullptr, &error_message);
    if (rc != SQLITE_OK) {
        std::string err_msg(error_message);
        sqlite3_free(error_message);
        sqlite3_close(db);
        throw std::runtime_error("Error creating table" + err_msg);
    }
    return db;
}



void WriteToDataBase(TaskQueue<RecipeTask> &input_queue, TaskQueue<Task> &output_queue, Logger &logger) {
    sqlite3 *db = createDataBase("recipes.db");
    while (!Flags::is_finished.load()) {
        if (!input_queue.IsEmpty()) {
            RecipeTask task = input_queue.Pop();
            ssize_t task_index = task.GetTaskIndex();
            if (task_index == -1) {
                output_queue.Push(StringTask());
                continue;
            }
            task.StopWait(2);
            task.StartWork(2);
            logger.log("task " + std::to_string(task_index) + " 3 stage processing");
            saveRecipeToDatabase(db, task);
            task.StopWork(2);
            Task final_task(task);
            output_queue.Push(final_task);
            logger.log("task " + std::to_string(task_index) + " 3 stage complete");
        }
    }
    sqlite3_close(db);
}

