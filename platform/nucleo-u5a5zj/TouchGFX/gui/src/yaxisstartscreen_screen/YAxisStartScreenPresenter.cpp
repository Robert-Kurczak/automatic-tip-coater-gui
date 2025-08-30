#include <gui/yaxisstartscreen_screen/YAxisStartScreenPresenter.hpp>
#include <gui/yaxisstartscreen_screen/YAxisStartScreenView.hpp>

YAxisStartScreenPresenter::YAxisStartScreenPresenter(
    YAxisStartScreenView& v
) :
    view(v) {}

void YAxisStartScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.yAxisConfigurator;
}

void YAxisStartScreenPresenter::deactivate() {}

void YAxisStartScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseStartPosition();
}

void YAxisStartScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseStartPosition();
}

void YAxisStartScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveStartPosition();
}

uint32_t YAxisStartScreenPresenter::getYAxisStart() {
    return axisConfigurator->getStartPosition();
}