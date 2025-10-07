#include <gui/spindledirectionscreen_screen/SpindleDirectionScreenView.hpp>

void SpindleDirectionScreenView::updateDisplayedValue() {
    const bool isClockwise = presenter->isSpindleDirectionClockwise();

    spindleDirectionSelector.setClockwiseState(isClockwise);
}

SpindleDirectionScreenView::SpindleDirectionScreenView() {}

void SpindleDirectionScreenView::setupScreen() {
    SpindleDirectionScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void SpindleDirectionScreenView::tearDownScreen() {
    SpindleDirectionScreenViewBase::tearDownScreen();
}

void SpindleDirectionScreenView::resetConfigurator() {
    presenter->resetConfigurator();
}

void SpindleDirectionScreenView::clockwiseButtonPressed() {
    presenter->clockwiseButtonPressed();
    updateDisplayedValue();
}

void SpindleDirectionScreenView::counterClockwiseButtonPressed() {
    presenter->counterClockwiseButtonPressed();
    updateDisplayedValue();
}

void SpindleDirectionScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}