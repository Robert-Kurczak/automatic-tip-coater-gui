#pragma once

#include "IAxisController.hpp"

namespace ATC {
class CommonAxisController : public IAxisController {
protected:
    uint32_t startPosition_ = 0;
    uint32_t endPosition_ = 0;
    uint32_t speed_ = 0;

public:
    virtual void setStartPosition(uint32_t value) override;
    virtual uint32_t getStartPosition() const override;

    virtual void setEndPosition(uint32_t value) override;
    virtual uint32_t getEndPosition() const override;

    virtual void setSpeed(uint32_t value) override;
    virtual uint32_t getSpeed() const override;
};
}