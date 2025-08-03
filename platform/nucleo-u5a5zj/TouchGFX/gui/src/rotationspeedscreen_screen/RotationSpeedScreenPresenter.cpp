#include <gui/rotationspeedscreen_screen/RotationSpeedScreenPresenter.hpp>
#include <gui/rotationspeedscreen_screen/RotationSpeedScreenView.hpp>


RotationSpeedScreenPresenter::RotationSpeedScreenPresenter(
    RotationSpeedScreenView& v
) :
    view(v) {}

void RotationSpeedScreenPresenter::activate() {}

void RotationSpeedScreenPresenter::deactivate() {}

void RotationSpeedScreenPresenter::increaseButtonPressed() {
    model->increaseRotationSpeed();
}

void RotationSpeedScreenPresenter::decreaseButtonPressed() {
    model->decreaseRotationSpeed();
}

void RotationSpeedScreenPresenter::saveButtonPressed() {
    model->saveRotationSpeed();
}

uint32_t RotationSpeedScreenPresenter::getRotationSpeed() {
    return model->getRotationSpeed();
}