#pragma once

#include "../IAxis.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
class IYAxis : public IAxis {
public:
    virtual void detectTip() = 0;
    virtual bool tipDetected() = 0;

    virtual void moveTowardsCoatingPosition() = 0;
    virtual bool isAtCoatingPosition() = 0;

    virtual ~IYAxis() {};
};
}