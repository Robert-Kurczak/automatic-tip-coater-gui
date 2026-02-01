#include <gui/yaxisstartscreen_screen/YAxisStartScreenPresenter.hpp>
#include <gui/yaxisstartscreen_screen/YAxisStartScreenView.hpp>

YAxisStartScreenPresenter::YAxisStartScreenPresenter(
    YAxisStartScreenView& v
) :
    view(v) {}

void YAxisStartScreenPresenter::activate() {}

void YAxisStartScreenPresenter::deactivate() {}

void YAxisStartScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void YAxisStartScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.increaseStartPosition();
}

void YAxisStartScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.decreaseStartPosition();
}

void YAxisStartScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.saveStartPosition();
}

uint32_t YAxisStartScreenPresenter::getYAxisStart() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    return axisConfigurator.getStartPositionInMicrometers();
}