#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenPresenter.hpp>
#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenView.hpp>

YAxisSpeedScreenPresenter::YAxisSpeedScreenPresenter(
    YAxisSpeedScreenView& v
) :
    view(v) {}

void YAxisSpeedScreenPresenter::activate() {}

void YAxisSpeedScreenPresenter::deactivate() {}

void YAxisSpeedScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void YAxisSpeedScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.increaseSpeed();
}

void YAxisSpeedScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.decreaseSpeed();
}

void YAxisSpeedScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.saveSpeed();
}

uint32_t YAxisSpeedScreenPresenter::getYAxisSpeed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    return axisConfigurator.getSpeed();
}
