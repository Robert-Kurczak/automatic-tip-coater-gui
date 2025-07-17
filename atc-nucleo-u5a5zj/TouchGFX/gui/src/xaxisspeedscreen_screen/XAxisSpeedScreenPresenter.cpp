#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenPresenter.hpp>
#include <gui/xaxisspeedscreen_screen/XAxisSpeedScreenView.hpp>

XAxisSpeedScreenPresenter::XAxisSpeedScreenPresenter(
    XAxisSpeedScreenView& v
) :
    view(v) {}

void XAxisSpeedScreenPresenter::activate() {}

void XAxisSpeedScreenPresenter::deactivate() {}

void XAxisSpeedScreenPresenter::increaseButtonPressed() {
    model->increaseXAxisSpeed();
}

void XAxisSpeedScreenPresenter::decreaseButtonPressed() {
    model->decreaseXAxisSpeed();
}

void XAxisSpeedScreenPresenter::saveButtonPressed() {
    model->saveXAxisSpeed();
}

uint32_t XAxisSpeedScreenPresenter::getXAxisSpeed() {
    return model->getXAxisSpeed();
}
