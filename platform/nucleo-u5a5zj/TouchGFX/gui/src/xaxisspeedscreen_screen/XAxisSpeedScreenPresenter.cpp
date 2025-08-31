#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenPresenter.hpp>
#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenView.hpp>

XAxisSpeedScreenPresenter::XAxisSpeedScreenPresenter(
    XAxisSpeedScreenView& v
) :
    view(v) {}

void XAxisSpeedScreenPresenter::activate() {}

void XAxisSpeedScreenPresenter::deactivate() {}

void XAxisSpeedScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.increaseSpeed();
}

void XAxisSpeedScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.decreaseSpeed();
}

void XAxisSpeedScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.saveSpeed();
}

uint32_t XAxisSpeedScreenPresenter::getXAxisSpeed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    return axisConfigurator.getSpeed();
}
