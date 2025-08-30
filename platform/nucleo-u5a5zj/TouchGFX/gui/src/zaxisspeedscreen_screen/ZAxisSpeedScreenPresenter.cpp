#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenPresenter.hpp>
#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenView.hpp>

ZAxisSpeedScreenPresenter::ZAxisSpeedScreenPresenter(
    ZAxisSpeedScreenView& v
) :
    view(v) {}

void ZAxisSpeedScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.zAxisConfigurator;
}

void ZAxisSpeedScreenPresenter::deactivate() {}

void ZAxisSpeedScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseSpeed();
}

void ZAxisSpeedScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseSpeed();
}

void ZAxisSpeedScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveSpeed();
}

uint32_t ZAxisSpeedScreenPresenter::getZAxisSpeed() {
    return axisConfigurator->getSpeed();
}