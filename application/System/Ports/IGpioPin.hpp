#pragma once

namespace ATC {
class IGpioPin {
public:
    IGpioPin() = default;
    IGpioPin(const IGpioPin&) = delete;
    IGpioPin& operator=(const IGpioPin&) = delete;
    IGpioPin(IGpioPin&&) = delete;
    IGpioPin& operator=(IGpioPin&&) = delete;
    virtual ~IGpioPin() = default;

    virtual void setInputMode() = 0;
    virtual void setInputPullUpMode() = 0;
    virtual void setInputPullDownMode() = 0;
    [[nodiscard]] virtual bool isHigh() = 0;

    virtual void setOutputMode() = 0;
    virtual void setHigh() = 0;
    virtual void setLow() = 0;
};
}