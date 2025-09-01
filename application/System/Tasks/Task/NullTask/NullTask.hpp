#pragma once

#include "../ITask.hpp"

namespace ATC {
class NullTask : public ITask {
public:
    NullTask() = default;

    virtual void start() override;
    virtual void reset() override;
    virtual void tick() override;
    virtual bool isFinished() const override;
};
}