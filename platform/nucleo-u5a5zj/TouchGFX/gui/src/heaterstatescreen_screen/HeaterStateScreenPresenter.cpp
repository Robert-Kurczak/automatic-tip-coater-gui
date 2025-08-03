#include <gui/heaterstatescreen_screen/HeaterStateScreenPresenter.hpp>
#include <gui/heaterstatescreen_screen/HeaterStateScreenView.hpp>

HeaterStateScreenPresenter::HeaterStateScreenPresenter(
    HeaterStateScreenView& v
) :
    view(v) {}

void HeaterStateScreenPresenter::activate() {}

void HeaterStateScreenPresenter::deactivate() {}

void HeaterStateScreenPresenter::onButtonPressed() {
    model->setHeaterOff();
}

void HeaterStateScreenPresenter::offButtonPressed() {
    model->setHeaterOn();
}

void HeaterStateScreenPresenter::saveButtonPressed() {
    model->saveHeaterState();
}

bool HeaterStateScreenPresenter::isHeaterOn() {
    return model->isHeaterOn();
}