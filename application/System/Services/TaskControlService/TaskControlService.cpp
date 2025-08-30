#include "TaskControlService.hpp"

namespace ATC {
TaskControlService::TaskControlService(ITaskScheduler& taskScheduler) :
    taskScheduler_(taskScheduler) {}

void TaskControlService::cancelAll() {
    taskScheduler_.cancelAll();
}
}