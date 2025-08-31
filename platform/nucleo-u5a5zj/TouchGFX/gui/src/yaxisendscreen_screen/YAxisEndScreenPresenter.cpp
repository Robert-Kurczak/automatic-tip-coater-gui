#include <gui/yaxisendscreen_screen/YAxisEndScreenPresenter.hpp>
#include <gui/yaxisendscreen_screen/YAxisEndScreenView.hpp>

YAxisEndScreenPresenter::YAxisEndScreenPresenter(YAxisEndScreenView& v) :
    view(v) {}

void YAxisEndScreenPresenter::activate() {}

void YAxisEndScreenPresenter::deactivate() {}

void YAxisEndScreenPresenter::increaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.increaseEndPosition();
}

void YAxisEndScreenPresenter::decreaseButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.decreaseEndPosition();
}

void YAxisEndScreenPresenter::saveButtonPressed() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    axisConfigurator.saveEndPosition();
}

uint32_t YAxisEndScreenPresenter::getYAxisEnd() {
    ATC::IAxisConfiguratorService& axisConfigurator =
        model->getSystemApi().configurators.xAxisConfigurator;

    return axisConfigurator.getEndPosition();
}
