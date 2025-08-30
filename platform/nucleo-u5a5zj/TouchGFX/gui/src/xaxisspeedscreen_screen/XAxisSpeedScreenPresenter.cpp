#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenPresenter.hpp>
#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenView.hpp>

XAxisSpeedScreenPresenter::XAxisSpeedScreenPresenter(
    XAxisSpeedScreenView& v
) :
    view(v) {}

void XAxisSpeedScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.xAxisConfigurator;
}

void XAxisSpeedScreenPresenter::deactivate() {}

void XAxisSpeedScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseSpeed();
}

void XAxisSpeedScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseSpeed();
}

void XAxisSpeedScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveSpeed();
}

uint32_t XAxisSpeedScreenPresenter::getXAxisSpeed() {
    return axisConfigurator->getSpeed();
}
