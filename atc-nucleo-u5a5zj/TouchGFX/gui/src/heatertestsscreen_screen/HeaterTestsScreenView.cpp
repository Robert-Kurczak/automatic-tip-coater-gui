#include <gui/heatertestsscreen_screen/HeaterTestsScreenView.hpp>

HeaterTestsScreenView::HeaterTestsScreenView() {}

void HeaterTestsScreenView::setupScreen() {
    HeaterTestsScreenViewBase::setupScreen();
}

void HeaterTestsScreenView::tearDownScreen() {
    HeaterTestsScreenViewBase::tearDownScreen();
}

void HeaterTestsScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void HeaterTestsScreenView::showTestResults(
    ATC::HeaterTestResults results
) {
    if (results.temperatureSuccess) {
        heaterTestsResults.setTemperatureSuccess();
    } else {
        heaterTestsResults.setTemperatureError();
    }
}

void HeaterTestsScreenView::startTest() {
    heaterTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void HeaterTestsScreenView::cancelTest() {
    heaterTestsResults.setTemperatureError();

    presenter->cancelButtonPressed();
}
