#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include "taskqueue.h"
#include "logger.h"

void ReadFile(TaskQueue<StringTask> &input_queue,
                  TaskQueue<StringTask> &output_queue,
                  Logger &logger);

void ParceData(TaskQueue<StringTask> &input_queue,
                  TaskQueue<RecipeTask> &output_queue,
                  Logger &logger);


#endif // DATAPROCESS_H
