#include <gui/spindlespeedscreen_screen/SpindleSpeedScreenPresenter.hpp>
#include <gui/spindlespeedscreen_screen/SpindleSpeedScreenView.hpp>

SpindleSpeedScreenPresenter::SpindleSpeedScreenPresenter(
    SpindleSpeedScreenView& v
) :
    view(v) {}

void SpindleSpeedScreenPresenter::activate() {}

void SpindleSpeedScreenPresenter::deactivate() {}

void SpindleSpeedScreenPresenter::resetConfigurator() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.increaseSpeedPercent();
}

void SpindleSpeedScreenPresenter::increaseButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.resetBufferedConfig();
}

void SpindleSpeedScreenPresenter::decreaseButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.decreaseSpeedPercent();
}

void SpindleSpeedScreenPresenter::saveButtonPressed() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    spindleConfigurator.saveSpeedPercent();
}

uint32_t SpindleSpeedScreenPresenter::getSpindleSpeedPercent() {
    ATC::ISpindleConfiguratorService& spindleConfigurator =
        model->getSystemApi().configurators.spindleConfigurator;

    return spindleConfigurator.getSpeedPercent();
}
