#include <gui/xaxisstartscreen_screen/XAxisStartScreenPresenter.hpp>
#include <gui/xaxisstartscreen_screen/XAxisStartScreenView.hpp>

XAxisStartScreenPresenter::XAxisStartScreenPresenter(
    XAxisStartScreenView& v
) :
    view(v) {}

void XAxisStartScreenPresenter::activate() {
    configuratorService =
        &model->getSystemApi().configurators.xAxisConfigurator;
}

void XAxisStartScreenPresenter::deactivate() {}

void XAxisStartScreenPresenter::increaseButtonPressed() {
    configuratorService->increaseStartPosition();
}

void XAxisStartScreenPresenter::decreaseButtonPressed() {
    configuratorService->decreaseStartPosition();
}

void XAxisStartScreenPresenter::saveButtonPressed() {
    configuratorService->saveStartPosition();
}

uint32_t XAxisStartScreenPresenter::getXAxisStart() {
    return configuratorService->getStartPosition();
}
