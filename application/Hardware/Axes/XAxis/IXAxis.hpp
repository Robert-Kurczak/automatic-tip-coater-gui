#pragma once

#include "../IAxis.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
class IXAxis : public IAxis {
public:
    virtual void moveTowardsHeaterFrontPosition() = 0;
    virtual bool isAtHeaterFrontPosition() = 0;
    
    virtual ~IXAxis() {};
};
}