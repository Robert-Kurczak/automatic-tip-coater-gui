#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenPresenter.hpp>
#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenView.hpp>

ZAxisSpeedScreenPresenter::ZAxisSpeedScreenPresenter(
    ZAxisSpeedScreenView& v
) :
    view(v) {}

void ZAxisSpeedScreenPresenter::activate() {}

void ZAxisSpeedScreenPresenter::deactivate() {}

void ZAxisSpeedScreenPresenter::increaseButtonPressed() {
    model->increaseZAxisSpeed();
}

void ZAxisSpeedScreenPresenter::decreaseButtonPressed() {
    model->decreaseZAxisSpeed();
}

void ZAxisSpeedScreenPresenter::saveButtonPressed() {
    model->saveZAxisSpeed();
}

uint32_t ZAxisSpeedScreenPresenter::getZAxisSpeed() {
    return model->getZAxisSpeed();
}