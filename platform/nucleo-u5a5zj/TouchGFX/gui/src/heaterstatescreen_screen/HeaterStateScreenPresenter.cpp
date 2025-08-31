#include <gui/heaterstatescreen_screen/HeaterStateScreenPresenter.hpp>
#include <gui/heaterstatescreen_screen/HeaterStateScreenView.hpp>

HeaterStateScreenPresenter::HeaterStateScreenPresenter(
    HeaterStateScreenView& v
) :
    view(v) {}

void HeaterStateScreenPresenter::activate() {}

void HeaterStateScreenPresenter::deactivate() {}

void HeaterStateScreenPresenter::onButtonPressed() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.turnOff();
}

void HeaterStateScreenPresenter::offButtonPressed() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.turnOn();
}

void HeaterStateScreenPresenter::saveButtonPressed() {
    // TODO implement or remove
}

bool HeaterStateScreenPresenter::isHeaterOn() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    return heaterConfigurator.isOn();
}