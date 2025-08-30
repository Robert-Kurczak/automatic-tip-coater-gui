#include <gui/zaxisstartscreen_screen/ZAxisStartScreenPresenter.hpp>
#include <gui/zaxisstartscreen_screen/ZAxisStartScreenView.hpp>

ZAxisStartScreenPresenter::ZAxisStartScreenPresenter(
    ZAxisStartScreenView& v
) :
    view(v) {}

void ZAxisStartScreenPresenter::activate() {
    axisConfigurator =
        &model->getSystemApi().configurators.zAxisConfigurator;
}

void ZAxisStartScreenPresenter::deactivate() {}

void ZAxisStartScreenPresenter::increaseButtonPressed() {
    axisConfigurator->increaseStartPosition();
}

void ZAxisStartScreenPresenter::decreaseButtonPressed() {
    axisConfigurator->decreaseStartPosition();
}

void ZAxisStartScreenPresenter::saveButtonPressed() {
    axisConfigurator->saveStartPosition();
}

uint32_t ZAxisStartScreenPresenter::getZAxisStart() {
    return axisConfigurator->getStartPosition();
}
