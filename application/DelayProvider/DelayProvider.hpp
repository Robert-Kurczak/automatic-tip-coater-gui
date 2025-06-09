#pragma once

#include <stdint.h>

namespace ATC {
class DelayProvider {
public:
    void delayMiliseconds(const uint32_t value);
};
}