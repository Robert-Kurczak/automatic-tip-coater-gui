#include <gui/spindlerotationtimescreen_screen/SpindleRotationTimeScreenPresenter.hpp>
#include <gui/spindlerotationtimescreen_screen/SpindleRotationTimeScreenView.hpp>

SpindleRotationTimeScreenPresenter::SpindleRotationTimeScreenPresenter(
    SpindleRotationTimeScreenView& v
) :
    view(v) {}

void SpindleRotationTimeScreenPresenter::activate() {}

void SpindleRotationTimeScreenPresenter::deactivate() {}

void SpindleRotationTimeScreenPresenter::resetConfigurator() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.resetBufferedConfig();
}

void SpindleRotationTimeScreenPresenter::increaseButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.increaseRotationTimeInMillis();
}

void SpindleRotationTimeScreenPresenter::decreaseButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.decreaseRotationTimeInMillis();
}

void SpindleRotationTimeScreenPresenter::saveButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.saveRotationTimeInMillis();
}

uint32_t SpindleRotationTimeScreenPresenter::
    getSpindleRotationTimeInMillis() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    return spindleConfigurator.getRotationTimeInMillis();
}
