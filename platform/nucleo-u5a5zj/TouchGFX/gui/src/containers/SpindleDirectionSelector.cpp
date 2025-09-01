#include <gui/containers/SpindleDirectionSelector.hpp>

SpindleDirectionSelector::SpindleDirectionSelector() {}

void SpindleDirectionSelector::initialize() {
    SpindleDirectionSelectorBase::initialize();
}

void SpindleDirectionSelector::setClockwiseState(const bool isClockwise) {
    clockwiseButton.setVisible(isClockwise);
    counterClockwiseButton.setVisible(!isClockwise);
}