#include <gui/xaxisendscreen_screen/XAxisEndScreenPresenter.hpp>
#include <gui/xaxisendscreen_screen/XAxisEndScreenView.hpp>

XAxisEndScreenPresenter::XAxisEndScreenPresenter(XAxisEndScreenView& v) :
    view(v) {}

void XAxisEndScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.xAxisConfigurator;
}

void XAxisEndScreenPresenter::deactivate() {}

void XAxisEndScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseEndPosition();
}

void XAxisEndScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseEndPosition();
}

void XAxisEndScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveEndPosition();
}

uint32_t XAxisEndScreenPresenter::getXAxisEnd() {
    return axisConfigurator->getEndPosition();
}
