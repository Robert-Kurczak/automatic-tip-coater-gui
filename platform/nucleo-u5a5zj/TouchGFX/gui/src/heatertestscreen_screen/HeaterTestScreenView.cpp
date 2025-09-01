#include <gui/heatertestscreen_screen/HeaterTestScreenView.hpp>

HeaterTestScreenView::HeaterTestScreenView() {}

void HeaterTestScreenView::setupScreen() {
    HeaterTestScreenViewBase::setupScreen();
}

void HeaterTestScreenView::tearDownScreen() {
    HeaterTestScreenViewBase::tearDownScreen();
}

void HeaterTestScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void HeaterTestScreenView::showTestResults(
    ATC::HeaterTestResults results
) {
    if (results.temperatureSuccess) {
        heaterTestsResults.setTemperatureSuccess();
    } else {
        heaterTestsResults.setTemperatureError();
    }
}

void HeaterTestScreenView::startTest() {
    heaterTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void HeaterTestScreenView::cancelTest() {
    heaterTestsResults.setTemperatureError();

    presenter->cancelButtonPressed();
}
