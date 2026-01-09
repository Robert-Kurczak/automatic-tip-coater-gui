#pragma once

namespace ATC {
class ITaskControlService {
public:
    ITaskControlService() = default;
    ITaskControlService(const ITaskControlService&) = delete;
    ITaskControlService& operator=(const ITaskControlService&) = delete;
    ITaskControlService(ITaskControlService&&) = delete;
    ITaskControlService& operator=(ITaskControlService&&) = delete;
    virtual ~ITaskControlService() = default;

    virtual void cancelAll() = 0;
};
}