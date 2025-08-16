#pragma once

#include "../IAxisController.hpp"

#include <stdint.h>

namespace ATC {
class IZAxisController : public IAxisController {
public:
    ~IZAxisController() = default;
};
}