#include <gui/xaxisstartscreen_screen/XAxisStartScreenPresenter.hpp>
#include <gui/xaxisstartscreen_screen/XAxisStartScreenView.hpp>

XAxisStartScreenPresenter::XAxisStartScreenPresenter(
    XAxisStartScreenView& v
) :
    view(v) {}

void XAxisStartScreenPresenter::activate() {}

void XAxisStartScreenPresenter::deactivate() {}

void XAxisStartScreenPresenter::increaseButtonPressed() {
    model->increaseXAxisStart();
}

void XAxisStartScreenPresenter::decreaseButtonPressed() {
    model->decreaseXAxisStart();
}

void XAxisStartScreenPresenter::saveButtonPressed() {
    model->saveXAxisStart();
}

uint32_t XAxisStartScreenPresenter::getXAxisStart() {
    return model->getXAxisStart();
}
