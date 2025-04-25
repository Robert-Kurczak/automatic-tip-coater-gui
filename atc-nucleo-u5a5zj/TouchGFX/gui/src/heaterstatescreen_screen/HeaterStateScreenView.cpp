#include <gui/heaterstatescreen_screen/HeaterStateScreenView.hpp>

static bool savedStateOn = false;

HeaterStateScreenView::HeaterStateScreenView()
{
    stateOn = savedStateOn;
    heaterStateSelector.setStateOn(stateOn);
}

void HeaterStateScreenView::setupScreen()
{
    HeaterStateScreenViewBase::setupScreen();
}

void HeaterStateScreenView::tearDownScreen()
{
    HeaterStateScreenViewBase::tearDownScreen();
}

void HeaterStateScreenView::stateOffButtonPressed()
{
    stateOn = true;
}

void HeaterStateScreenView::stateOnButtonPressed()
{
    stateOn = false;
}

void HeaterStateScreenView::saveButtonPressed()
{
    savedStateOn = stateOn;
}