#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenPresenter.hpp>
#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenView.hpp>

HeaterTemperatureScreenPresenter::HeaterTemperatureScreenPresenter(
    HeaterTemperatureScreenView& v
) :
    view(v) {}

void HeaterTemperatureScreenPresenter::activate() {}

void HeaterTemperatureScreenPresenter::deactivate() {}

void HeaterTemperatureScreenPresenter::resetConfigurator() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.resetBufferedConfig();
}

void HeaterTemperatureScreenPresenter::increaseButtonPressed() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.increaseTemperatureInCelsius();
}

void HeaterTemperatureScreenPresenter::decreaseButtonPressed() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.decreaseTemperatureInCelsius();
}

void HeaterTemperatureScreenPresenter::saveButtonPressed() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.saveTemperatureInCelsius();
}

uint32_t HeaterTemperatureScreenPresenter::getHeaterTemperature() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    return heaterConfigurator.getTemperatureInCelsius();
}
