#include <gui/rotationdirectionscreen_screen/RotationDirectionScreenView.hpp>

void RotationDirectionScreenView::updateDisplayedValue() {
    const bool isClockwise = presenter->isRotationClockwise();
    rotationDirectionSelector.setClockwiseState(isClockwise);
}

RotationDirectionScreenView::RotationDirectionScreenView() {}

void RotationDirectionScreenView::setupScreen() {
    RotationDirectionScreenViewBase::setupScreen();
    updateDisplayedValue();
}

void RotationDirectionScreenView::tearDownScreen() {
    RotationDirectionScreenViewBase::tearDownScreen();
}

void RotationDirectionScreenView::clockwiseButtonPressed() {
    presenter->clockwiseButtonPressed();
    updateDisplayedValue();
}

void RotationDirectionScreenView::counterClockwiseButtonPressed() {
    presenter->counterClockwiseButtonPressed();
    updateDisplayedValue();
}

void RotationDirectionScreenView::saveButtonPressed() {
    presenter->saveButtonPressed();
}