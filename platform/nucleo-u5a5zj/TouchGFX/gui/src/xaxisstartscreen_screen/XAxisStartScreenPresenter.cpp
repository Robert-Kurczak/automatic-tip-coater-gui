#include <gui/xaxisstartscreen_screen/XAxisStartScreenPresenter.hpp>
#include <gui/xaxisstartscreen_screen/XAxisStartScreenView.hpp>

XAxisStartScreenPresenter::XAxisStartScreenPresenter(
    XAxisStartScreenView& v
) :
    view(v) {}

void XAxisStartScreenPresenter::activate() {}

void XAxisStartScreenPresenter::deactivate() {}

void XAxisStartScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void XAxisStartScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.increaseStartPosition();
}

void XAxisStartScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.decreaseStartPosition();
}

void XAxisStartScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.saveStartPosition();
}

uint32_t XAxisStartScreenPresenter::getXAxisStart() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    return axisConfigurator.getStartPosition();
}
