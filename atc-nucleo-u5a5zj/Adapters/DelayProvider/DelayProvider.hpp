#pragma once

#include "application/Ports/IDelayProvider.hpp"

namespace ATC {
class DelayProvider : public IDelayProvider {
public:
    virtual void delayMiliseconds(const uint32_t value) override;
};
}