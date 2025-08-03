#include <gui/zaxisstartscreen_screen/ZAxisStartScreenPresenter.hpp>
#include <gui/zaxisstartscreen_screen/ZAxisStartScreenView.hpp>


ZAxisStartScreenPresenter::ZAxisStartScreenPresenter(
    ZAxisStartScreenView& v
) :
    view(v) {}

void ZAxisStartScreenPresenter::activate() {}

void ZAxisStartScreenPresenter::deactivate() {}

void ZAxisStartScreenPresenter::increaseButtonPressed() {
    model->increaseZAxisStart();
}

void ZAxisStartScreenPresenter::decreaseButtonPressed() {
    model->decreaseZAxisStart();
}

void ZAxisStartScreenPresenter::saveButtonPressed() {
    model->saveZAxisStart();
}

uint32_t ZAxisStartScreenPresenter::getZAxisStart() {
    return model->getZAxisStart();
}
