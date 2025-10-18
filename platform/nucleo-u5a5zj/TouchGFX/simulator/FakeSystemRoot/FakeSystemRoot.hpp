#pragma once

#include "application/System/Root/SystemRoot.hpp"

namespace ATC {
class TargetSystemRoot : public SystemRoot {
private:
    SystemComponents targetComponents_;
    SystemApi systemApi_;

    TargetSystemRoot();

public:
    static TargetSystemRoot& getSystemRoot();
};
}