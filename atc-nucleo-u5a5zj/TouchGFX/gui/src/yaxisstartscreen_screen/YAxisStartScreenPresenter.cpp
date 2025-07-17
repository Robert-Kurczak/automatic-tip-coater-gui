#include <gui/yaxisstartscreen_screen/YAxisStartScreenPresenter.hpp>
#include <gui/yaxisstartscreen_screen/YAxisStartScreenView.hpp>

YAxisStartScreenPresenter::YAxisStartScreenPresenter(
    YAxisStartScreenView& v
) :
    view(v) {}

void YAxisStartScreenPresenter::activate() {}

void YAxisStartScreenPresenter::deactivate() {}

void YAxisStartScreenPresenter::increaseButtonPressed() {
    model->increaseYAxisStart();
}

void YAxisStartScreenPresenter::decreaseButtonPressed() {
    model->decreaseYAxisStart();
}

void YAxisStartScreenPresenter::saveButtonPressed() {
    model->saveYAxisStart();
}

uint32_t YAxisStartScreenPresenter::getYAxisStart() {
    return model->getYAxisStart();
}