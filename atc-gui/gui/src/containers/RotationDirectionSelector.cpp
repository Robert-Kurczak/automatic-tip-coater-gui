#include <gui/containers/RotationDirectionSelector.hpp>

RotationDirectionSelector::RotationDirectionSelector()
{

}

void RotationDirectionSelector::initialize()
{
    RotationDirectionSelectorBase::initialize();
}

void RotationDirectionSelector::setClockwiseState(const bool isClockwise)
{
    clockwiseButton.setVisible(isClockwise);
    counterClockwiseButton.setVisible(!isClockwise);
}