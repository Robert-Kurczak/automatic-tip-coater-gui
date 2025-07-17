#include <gui/zaxisendscreen_screen/ZAxisEndScreenPresenter.hpp>
#include <gui/zaxisendscreen_screen/ZAxisEndScreenView.hpp>

ZAxisEndScreenPresenter::ZAxisEndScreenPresenter(ZAxisEndScreenView& v) :
    view(v) {}

void ZAxisEndScreenPresenter::activate() {}

void ZAxisEndScreenPresenter::deactivate() {}

void ZAxisEndScreenPresenter::increaseButtonPressed() {
    model->increaseZAxisEnd();
}

void ZAxisEndScreenPresenter::decreaseButtonPressed() {
    model->decreaseZAxisEnd();
}

void ZAxisEndScreenPresenter::saveButtonPressed() {
    model->saveZAxisEnd();
}

uint32_t ZAxisEndScreenPresenter::getZAxisEnd() {
    return model->getZAxisEnd();
}