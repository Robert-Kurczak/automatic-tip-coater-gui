#include <gui/containers/HeaterStateSelector.hpp>

HeaterStateSelector::HeaterStateSelector()
{

}

void HeaterStateSelector::initialize()
{
    HeaterStateSelectorBase::initialize();
}

void HeaterStateSelector::setStateOn(const bool isOn)
{
    stateOnButton.setVisible(isOn);
    stateOffButton.setVisible(!isOn);
}
