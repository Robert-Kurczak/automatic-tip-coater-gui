#pragma once

namespace ATC {
class IGpioPin {
public:
    virtual void setInputMode() = 0;
    virtual void setInputPullUpMode() = 0;
    virtual void setInputPullDownMode() = 0;
    virtual bool isHigh() = 0;

    virtual void setOutputMode() = 0;
    virtual void setHigh() = 0;
    virtual void setLow() = 0;
};
}