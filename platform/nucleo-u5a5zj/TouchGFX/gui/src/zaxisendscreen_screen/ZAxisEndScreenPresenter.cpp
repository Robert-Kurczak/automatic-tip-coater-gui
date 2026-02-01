#include <gui/zaxisendscreen_screen/ZAxisEndScreenPresenter.hpp>
#include <gui/zaxisendscreen_screen/ZAxisEndScreenView.hpp>

ZAxisEndScreenPresenter::ZAxisEndScreenPresenter(ZAxisEndScreenView& v) :
    view(v) {}

void ZAxisEndScreenPresenter::activate() {}

void ZAxisEndScreenPresenter::deactivate() {}

void ZAxisEndScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void ZAxisEndScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.increaseEndPosition();
}

void ZAxisEndScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.decreaseEndPosition();
}

void ZAxisEndScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    axisConfigurator.saveEndPosition();
}

uint32_t ZAxisEndScreenPresenter::getZAxisEnd() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.zAxisConfigurator;

    return axisConfigurator.getEndPositionInMicrometers();
}