#ifndef HEATERSTATESELECTOR_HPP
#define HEATERSTATESELECTOR_HPP

#include <gui_generated/containers/HeaterStateSelectorBase.hpp>

class HeaterStateSelector : public HeaterStateSelectorBase
{
public:
    HeaterStateSelector();
    virtual ~HeaterStateSelector() {}

    virtual void initialize();

    void setStateOn(const bool isOn);
protected:
};

#endif // HEATERSTATESELECTOR_HPP
