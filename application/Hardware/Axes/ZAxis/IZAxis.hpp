#pragma once

#include "../IAxis.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
class IZAxis : public IAxis {
public:
    // TODO declare Y axis specific funtionality

    virtual ~IZAxis() {};
};
}