#include <gui/yaxisendscreen_screen/YAxisEndScreenPresenter.hpp>
#include <gui/yaxisendscreen_screen/YAxisEndScreenView.hpp>

YAxisEndScreenPresenter::YAxisEndScreenPresenter(YAxisEndScreenView& v) :
    view(v) {}

void YAxisEndScreenPresenter::activate() {}

void YAxisEndScreenPresenter::deactivate() {}

void YAxisEndScreenPresenter::resetConfigurator() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.resetBufferedConfig();
}

void YAxisEndScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.increaseEndPosition();
}

void YAxisEndScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.decreaseEndPosition();
}

void YAxisEndScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    axisConfigurator.saveEndPosition();
}

uint32_t YAxisEndScreenPresenter::getYAxisEnd() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.yAxisConfigurator;

    return axisConfigurator.getEndPositionInMicrometers();
}
