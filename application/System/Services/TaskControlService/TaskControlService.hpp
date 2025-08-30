#pragma once

#include "ITaskControlService.hpp"
#include "application/System/Tasks/TaskScheduler/ITaskScheduler.hpp"

namespace ATC {
class TaskControlService : public ITaskControlService {
private:
    ITaskScheduler& taskScheduler_;

public:
    TaskControlService(ITaskScheduler& taskScheduler);

    virtual void cancelAll() override;
};
}