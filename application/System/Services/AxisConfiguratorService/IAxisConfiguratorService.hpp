#pragma once

#include <stdint.h>

namespace ATC {
class IAxisConfiguratorService {
public:
    virtual ~IAxisConfiguratorService() = default;

    virtual void showcaseStartPosition() = 0;
    virtual void increaseStartPosition() = 0;
    virtual void decreaseStartPosition() = 0;
    virtual void saveStartPosition() = 0;
    virtual uint32_t getStartPosition() const = 0;

    virtual void showcaseEndPosition() = 0;
    virtual void increaseEndPosition() = 0;
    virtual void decreaseEndPosition() = 0;
    virtual void saveEndPosition() = 0;
    virtual uint32_t getEndPosition() const = 0;

    virtual void showcaseSpeed() = 0;
    virtual void increaseSpeed() = 0;
    virtual void decreaseSpeed() = 0;
    virtual void saveSpeed() = 0;
    virtual uint32_t getSpeed() const = 0;
};
}