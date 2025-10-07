#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenPresenter.hpp>
#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenView.hpp>

ZAxisSpeedScreenPresenter::ZAxisSpeedScreenPresenter(
    ZAxisSpeedScreenView& v
) :
    view(v) {}

void ZAxisSpeedScreenPresenter::activate() {}

void ZAxisSpeedScreenPresenter::deactivate() {}

void ZAxisSpeedScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void ZAxisSpeedScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.increaseSpeed();
}

void ZAxisSpeedScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.decreaseSpeed();
}

void ZAxisSpeedScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.saveSpeed();
}

uint32_t ZAxisSpeedScreenPresenter::getZAxisSpeed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    return axisConfigurator.getSpeed();
}