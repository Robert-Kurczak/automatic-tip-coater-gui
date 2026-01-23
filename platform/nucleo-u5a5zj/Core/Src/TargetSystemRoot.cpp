#include "TargetSystemRoot.hpp"

namespace ATC {
TargetSystemRoot::TargetSystemRoot() :
    SystemRoot(targetComponents_, systemApi_) {}

TargetSystemRoot& TargetSystemRoot::getSystemRoot() {
    static TargetSystemRoot systemRoot;
    return systemRoot;
}
};