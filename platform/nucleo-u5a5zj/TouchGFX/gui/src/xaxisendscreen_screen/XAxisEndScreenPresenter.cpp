#include <gui/xaxisendscreen_screen/XAxisEndScreenPresenter.hpp>
#include <gui/xaxisendscreen_screen/XAxisEndScreenView.hpp>

XAxisEndScreenPresenter::XAxisEndScreenPresenter(XAxisEndScreenView& v) :
    view(v) {}

void XAxisEndScreenPresenter::activate() {}

void XAxisEndScreenPresenter::deactivate() {}

void XAxisEndScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void XAxisEndScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.increaseEndPosition();
}

void XAxisEndScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.decreaseEndPosition();
}

void XAxisEndScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.saveEndPosition();
}

uint32_t XAxisEndScreenPresenter::getXAxisEnd() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    return axisConfigurator.getEndPosition();
}
