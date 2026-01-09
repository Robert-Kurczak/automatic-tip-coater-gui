#pragma once

#include "../ITask.hpp"

namespace ATC {
class NullTask : public ITask {
public:
    NullTask() = default;

    void start() override;
    void reset() override;
    void tick() override;
    [[nodiscard]] bool isFinished() const override;
};
}