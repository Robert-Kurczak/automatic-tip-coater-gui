#include <gui/rotationdirectionscreen_screen/RotationDirectionScreenPresenter.hpp>
#include <gui/rotationdirectionscreen_screen/RotationDirectionScreenView.hpp>

RotationDirectionScreenPresenter::RotationDirectionScreenPresenter(
    RotationDirectionScreenView& v
) :
    view(v) {}

void RotationDirectionScreenPresenter::activate() {
    spindleConfigurator =
        &model->getSystemApi().configurators.spindleConfigurator;
}

void RotationDirectionScreenPresenter::deactivate() {}

bool RotationDirectionScreenPresenter::isRotationClockwise() {
    return spindleConfigurator->isDirectionClockwise();
}

void RotationDirectionScreenPresenter::clockwiseButtonPressed() {
    spindleConfigurator->setDirectionCounterClockwise();
}

void RotationDirectionScreenPresenter::counterClockwiseButtonPressed() {
    spindleConfigurator->setDirectionClockwise();
}

void RotationDirectionScreenPresenter::saveButtonPressed() {
    spindleConfigurator->saveDirection();
}