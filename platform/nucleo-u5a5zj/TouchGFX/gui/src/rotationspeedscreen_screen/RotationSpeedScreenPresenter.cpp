#include <gui/rotationspeedscreen_screen/RotationSpeedScreenPresenter.hpp>
#include <gui/rotationspeedscreen_screen/RotationSpeedScreenView.hpp>

RotationSpeedScreenPresenter::RotationSpeedScreenPresenter(
    RotationSpeedScreenView& v
) :
    view(v) {}

void RotationSpeedScreenPresenter::activate() {
    spindleConfigurator =
        &model->getSystemApi().configurators.spindleConfigurator;
}

void RotationSpeedScreenPresenter::deactivate() {}

void RotationSpeedScreenPresenter::increaseButtonPressed() {
    spindleConfigurator->increaseSpeedPercent();
}

void RotationSpeedScreenPresenter::decreaseButtonPressed() {
    spindleConfigurator->decreaseSpeedPercent();
}

void RotationSpeedScreenPresenter::saveButtonPressed() {
    spindleConfigurator->saveSpeedPercent();
}

uint32_t RotationSpeedScreenPresenter::getRotationSpeed() {
    return spindleConfigurator->getSpeedPercent();
}