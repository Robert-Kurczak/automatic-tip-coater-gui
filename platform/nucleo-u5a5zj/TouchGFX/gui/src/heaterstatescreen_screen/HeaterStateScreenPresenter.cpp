#include <gui/heaterstatescreen_screen/HeaterStateScreenPresenter.hpp>
#include <gui/heaterstatescreen_screen/HeaterStateScreenView.hpp>

HeaterStateScreenPresenter::HeaterStateScreenPresenter(
    HeaterStateScreenView& v
) :
    view(v) {}

void HeaterStateScreenPresenter::activate() {}

void HeaterStateScreenPresenter::deactivate() {}

void HeaterStateScreenPresenter::resetConfigurator() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.resetBufferedConfig();
}

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

bool HeaterStateScreenPresenter::isHeaterOn() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    return heaterConfigurator.isOn();
}

void HeaterStateScreenPresenter::saveButtonPressed() {
    ATC::IHeaterConfiguratorService& heaterConfigurator =
        model->getSystemApi().configurators.heaterConfigurator;

    heaterConfigurator.turnOn();
}