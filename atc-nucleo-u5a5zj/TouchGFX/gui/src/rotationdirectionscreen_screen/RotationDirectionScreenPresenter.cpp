#include <gui/rotationdirectionscreen_screen/RotationDirectionScreenPresenter.hpp>
#include <gui/rotationdirectionscreen_screen/RotationDirectionScreenView.hpp>

RotationDirectionScreenPresenter::RotationDirectionScreenPresenter(
    RotationDirectionScreenView& v
) :
    view(v) {}

void RotationDirectionScreenPresenter::activate() {}

void RotationDirectionScreenPresenter::deactivate() {}

bool RotationDirectionScreenPresenter::isRotationClockwise() {
    return model->isRotationClockwise();
}

void RotationDirectionScreenPresenter::clockwiseButtonPressed() {
    model->setCounterClockwiseRotation();
}

void RotationDirectionScreenPresenter::counterClockwiseButtonPressed() {
    model->setClockwiseRotation();
}

void RotationDirectionScreenPresenter::saveButtonPressed() {
    model->saveRotationDirection();
}