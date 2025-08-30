#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenPresenter.hpp>
#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenView.hpp>

YAxisSpeedScreenPresenter::YAxisSpeedScreenPresenter(
    YAxisSpeedScreenView& v
) :
    view(v) {}

void YAxisSpeedScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.yAxisConfigurator;
}

void YAxisSpeedScreenPresenter::deactivate() {}

void YAxisSpeedScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseSpeed();
}

void YAxisSpeedScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseSpeed();
}

void YAxisSpeedScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveSpeed();
}

uint32_t YAxisSpeedScreenPresenter::getYAxisSpeed() {
    return axisConfigurator->getSpeed();
}
