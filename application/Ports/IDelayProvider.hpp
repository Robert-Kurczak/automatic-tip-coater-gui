#pragma once

#include <stdint.h>

namespace ATC {
class IDelayProvider {
public:
    virtual void delayMiliseconds(const uint32_t value) = 0;
};
}