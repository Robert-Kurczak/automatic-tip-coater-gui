#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenPresenter.hpp>
#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenView.hpp>

HeaterTemperatureScreenPresenter::HeaterTemperatureScreenPresenter(
    HeaterTemperatureScreenView& v
) :
    view(v) {}

void HeaterTemperatureScreenPresenter::activate() {}

void HeaterTemperatureScreenPresenter::deactivate() {}

void HeaterTemperatureScreenPresenter::increaseButtonPressed() {
    model->increaseHeaterTemperature();
}

void HeaterTemperatureScreenPresenter::decreaseButtonPressed() {
    model->decreaseHeaterTemperature();
}

void HeaterTemperatureScreenPresenter::saveButtonPressed() {
    model->saveHeaterTemperature();
}

uint32_t HeaterTemperatureScreenPresenter::getHeaterTemperature() {
    return model->getHeaterTemperature();
}
