#pragma once

#include "../IAxisController.hpp"

#include <stdint.h>

namespace ATC {
class IYAxisController : public IAxisController {
public:
    ~IYAxisController() = default;

    virtual void moveToDetectTip() = 0;
    virtual bool isTipDetected() const = 0;

    virtual void moveToCoatingPosition() = 0;
    virtual bool isAtCoatingPosition() const = 0;
};
}