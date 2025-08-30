#include <gui/rotationtimescreen_screen/RotationTimeScreenPresenter.hpp>
#include <gui/rotationtimescreen_screen/RotationTimeScreenView.hpp>

RotationTimeScreenPresenter::RotationTimeScreenPresenter(
    RotationTimeScreenView& v
) :
    view(v) {}

void RotationTimeScreenPresenter::activate() {
    spindleConfigurator =
        &model->getSystemApi().configurators.spindleConfigurator;
}

void RotationTimeScreenPresenter::deactivate() {}

void RotationTimeScreenPresenter::increaseButtonPressed() {
    spindleConfigurator->increaseRotationTime();
}

void RotationTimeScreenPresenter::decreaseButtonPressed() {
    spindleConfigurator->decreaseRotationTime();
}

void RotationTimeScreenPresenter::saveButtonPressed() {
    spindleConfigurator->saveRotationTime();
}

uint32_t RotationTimeScreenPresenter::getRotationTime() {
    return spindleConfigurator->getRotationTimeMillis();
}