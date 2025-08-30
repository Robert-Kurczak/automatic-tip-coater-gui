#include <gui/zaxisendscreen_screen/ZAxisEndScreenPresenter.hpp>
#include <gui/zaxisendscreen_screen/ZAxisEndScreenView.hpp>

ZAxisEndScreenPresenter::ZAxisEndScreenPresenter(ZAxisEndScreenView& v) :
    view(v) {}

void ZAxisEndScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.zAxisConfigurator;
}

void ZAxisEndScreenPresenter::deactivate() {}

void ZAxisEndScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseEndPosition();
}

void ZAxisEndScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseEndPosition();
}

void ZAxisEndScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveEndPosition();
}

uint32_t ZAxisEndScreenPresenter::getZAxisEnd() {
    return axisConfigurator->getEndPosition();
}