#include <gui/xaxisendscreen_screen/XAxisEndScreenPresenter.hpp>
#include <gui/xaxisendscreen_screen/XAxisEndScreenView.hpp>

XAxisEndScreenPresenter::XAxisEndScreenPresenter(XAxisEndScreenView& v) :
    view(v) {}

void XAxisEndScreenPresenter::activate() {}

void XAxisEndScreenPresenter::deactivate() {}

void XAxisEndScreenPresenter::increaseButtonPressed() {
    model->increaseXAxisEnd();
}

void XAxisEndScreenPresenter::decreaseButtonPressed() {
    model->decreaseXAxisEnd();
}

void XAxisEndScreenPresenter::saveButtonPressed() {
    model->saveXAxisEnd();
}

uint32_t XAxisEndScreenPresenter::getXAxisEnd() {
    return model->getXAxisEnd();
}