#include <gui/rotationtimescreen_screen/RotationTimeScreenPresenter.hpp>
#include <gui/rotationtimescreen_screen/RotationTimeScreenView.hpp>

RotationTimeScreenPresenter::RotationTimeScreenPresenter(
    RotationTimeScreenView& v
) :
    view(v) {}

void RotationTimeScreenPresenter::activate() {}

void RotationTimeScreenPresenter::deactivate() {}

void RotationTimeScreenPresenter::increaseButtonPressed() {
    model->increaseRotationTime();
}

void RotationTimeScreenPresenter::decreaseButtonPressed() {
    model->decreaseRotationTime();
}

void RotationTimeScreenPresenter::saveButtonPressed() {
    model->saveRotationTime();
}

uint32_t RotationTimeScreenPresenter::getRotationTime() {
    return model->getRotationTime();
}