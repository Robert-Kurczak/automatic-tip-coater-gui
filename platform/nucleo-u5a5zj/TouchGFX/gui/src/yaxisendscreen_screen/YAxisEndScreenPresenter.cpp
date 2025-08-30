#include <gui/yaxisendscreen_screen/YAxisEndScreenPresenter.hpp>
#include <gui/yaxisendscreen_screen/YAxisEndScreenView.hpp>

YAxisEndScreenPresenter::YAxisEndScreenPresenter(YAxisEndScreenView& v) :
    view(v) {}

void YAxisEndScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.xAxisConfigurator;
}

void YAxisEndScreenPresenter::deactivate() {}

void YAxisEndScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseEndPosition();
}

void YAxisEndScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseEndPosition();
}

void YAxisEndScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveEndPosition();
}

uint32_t YAxisEndScreenPresenter::getYAxisEnd() {
    return axisConfigurator->getEndPosition();
}
