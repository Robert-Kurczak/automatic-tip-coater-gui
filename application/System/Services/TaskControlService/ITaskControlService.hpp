#pragma once

namespace ATC {
class ITaskControlService {
public:
    virtual ~ITaskControlService() = default;

    virtual void cancelAll() = 0;
};
}