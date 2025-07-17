#include <gui/yaxisendscreen_screen/YAxisEndScreenPresenter.hpp>
#include <gui/yaxisendscreen_screen/YAxisEndScreenView.hpp>

YAxisEndScreenPresenter::YAxisEndScreenPresenter(YAxisEndScreenView& v) :
    view(v) {}

void YAxisEndScreenPresenter::activate() {}

void YAxisEndScreenPresenter::deactivate() {}

void YAxisEndScreenPresenter::increaseButtonPressed() {
    model->increaseYAxisEnd();
}

void YAxisEndScreenPresenter::decreaseButtonPressed() {
    model->decreaseYAxisEnd();
}

void YAxisEndScreenPresenter::saveButtonPressed() {
    model->saveYAxisEnd();
}

uint32_t YAxisEndScreenPresenter::getYAxisEnd() {
    return model->getYAxisEnd();
}
