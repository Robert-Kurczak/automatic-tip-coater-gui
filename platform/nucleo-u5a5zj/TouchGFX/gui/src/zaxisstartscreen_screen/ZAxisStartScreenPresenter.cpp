#include <gui/zaxisstartscreen_screen/ZAxisStartScreenPresenter.hpp>
#include <gui/zaxisstartscreen_screen/ZAxisStartScreenView.hpp>

ZAxisStartScreenPresenter::ZAxisStartScreenPresenter(
    ZAxisStartScreenView& v
) :
    view(v) {}

void ZAxisStartScreenPresenter::activate() {}

void ZAxisStartScreenPresenter::deactivate() {}

void ZAxisStartScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void ZAxisStartScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.increaseStartPosition();
}

void ZAxisStartScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.decreaseStartPosition();
}

void ZAxisStartScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.saveStartPosition();
}

uint32_t ZAxisStartScreenPresenter::getZAxisStart() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    return axisConfigurator.getStartPosition();
}
