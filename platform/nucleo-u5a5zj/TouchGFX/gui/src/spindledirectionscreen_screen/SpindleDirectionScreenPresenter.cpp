#include <gui/spindledirectionscreen_screen/SpindleDirectionScreenPresenter.hpp>
#include <gui/spindledirectionscreen_screen/SpindleDirectionScreenView.hpp>

SpindleDirectionScreenPresenter::SpindleDirectionScreenPresenter(
    SpindleDirectionScreenView& v
) :
    view(v) {}

void SpindleDirectionScreenPresenter::activate() {}

void SpindleDirectionScreenPresenter::deactivate() {}

void SpindleDirectionScreenPresenter::resetConfigurator() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.resetBufferedConfig();
}

void SpindleDirectionScreenPresenter::clockwiseButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.setDirectionCounterClockwise();
}

void SpindleDirectionScreenPresenter::counterClockwiseButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.setDirectionClockwise();
}

void SpindleDirectionScreenPresenter::saveButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.saveDirection();
}

bool SpindleDirectionScreenPresenter::isSpindleDirectionClockwise() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    return spindleConfigurator.isDirectionClockwise();
}