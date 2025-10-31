#include "NullTask.hpp"

namespace ATC {
void NullTask::start() {}

void NullTask::reset() {}

void NullTask::tick() {}

bool NullTask::isFinished() const {
    return false;
}
}