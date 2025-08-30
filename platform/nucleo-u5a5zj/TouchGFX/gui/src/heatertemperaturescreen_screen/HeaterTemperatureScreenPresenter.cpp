#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenPresenter.hpp>
#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenView.hpp>

HeaterTemperatureScreenPresenter::HeaterTemperatureScreenPresenter(
    HeaterTemperatureScreenView& v
) :
    view(v) {}

void HeaterTemperatureScreenPresenter::activate() {
    heaterConfigurator =
        &model->getSystemApi().configurators.heaterConfigurator;
}

void HeaterTemperatureScreenPresenter::deactivate() {}

void HeaterTemperatureScreenPresenter::increaseButtonPressed() {
    heaterConfigurator->increaseTemperatureInCelsius();
}

void HeaterTemperatureScreenPresenter::decreaseButtonPressed() {
    heaterConfigurator->decreaseTemperatureInCelsius();
}

void HeaterTemperatureScreenPresenter::saveButtonPressed() {
    heaterConfigurator->saveTemperatureInCelsius();
}

uint32_t HeaterTemperatureScreenPresenter::getHeaterTemperature() {
    return heaterConfigurator->getTemperatureInCelsius();
}
