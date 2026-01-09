#pragma once

#include "../IAxisController.hpp"

namespace ATC {
class IYAxisController : public IAxisController {
public:
    virtual void moveToDetectTip() = 0;
    [[nodiscard]] virtual bool isTipDetected() const = 0;

    virtual void moveToCoatingPosition() = 0;
    [[nodiscard]] virtual bool isAtCoatingPosition() const = 0;
};
}