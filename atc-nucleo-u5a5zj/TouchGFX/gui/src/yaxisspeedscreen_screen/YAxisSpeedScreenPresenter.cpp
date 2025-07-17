#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenPresenter.hpp>
#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenView.hpp>

YAxisSpeedScreenPresenter::YAxisSpeedScreenPresenter(
    YAxisSpeedScreenView& v
) :
    view(v) {}

void YAxisSpeedScreenPresenter::activate() {}

void YAxisSpeedScreenPresenter::deactivate() {}

void YAxisSpeedScreenPresenter::increaseButtonPressed() {
    model->increaseYAxisSpeed();
}

void YAxisSpeedScreenPresenter::decreaseButtonPressed() {
    model->decreaseYAxisSpeed();
}

void YAxisSpeedScreenPresenter::saveButtonPressed() {
    model->saveYAxisSpeed();
}

uint32_t YAxisSpeedScreenPresenter::getYAxisSpeed() {
    return model->getYAxisSpeed();
}
