#ifndef DATABASEPROC_H
#define DATABASEPROC_H

#include <sqlite3.h>


#include "task.h"
#include "taskqueue.h"
#include "logger.h"

sqlite3 *createDataBase(const char *database_name);

void saveRecipeToDatabase(sqlite3 *db, const RecipeTask &recipe);

void WriteToDataBase(TaskQueue<RecipeTask> &input_queue,
               TaskQueue<Task> &output_queue,
               Logger &logger);



#endif // DATABASEPROC_H
