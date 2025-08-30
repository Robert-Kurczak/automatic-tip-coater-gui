#include <gui/heaterstatescreen_screen/HeaterStateScreenPresenter.hpp>
#include <gui/heaterstatescreen_screen/HeaterStateScreenView.hpp>

HeaterStateScreenPresenter::HeaterStateScreenPresenter(
    HeaterStateScreenView& v
) :
    view(v) {}

void HeaterStateScreenPresenter::activate() {
    heaterConfigurator =
        &model->getSystemApi().configurators.heaterConfigurator;
}

void HeaterStateScreenPresenter::deactivate() {}

void HeaterStateScreenPresenter::onButtonPressed() {
    heaterConfigurator->turnOff();
}

void HeaterStateScreenPresenter::offButtonPressed() {
    heaterConfigurator->turnOn();
}

void HeaterStateScreenPresenter::saveButtonPressed() {
    // TODO implement or remove
}

bool HeaterStateScreenPresenter::isHeaterOn() {
    return heaterConfigurator->isOn();
}