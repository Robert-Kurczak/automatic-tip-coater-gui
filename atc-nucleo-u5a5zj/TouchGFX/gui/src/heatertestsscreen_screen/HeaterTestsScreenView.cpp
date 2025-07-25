#include <gui/heatertestsscreen_screen/HeaterTestsScreenView.hpp>

HeaterTestsScreenView::HeaterTestsScreenView() {}

void HeaterTestsScreenView::setupScreen() {
    HeaterTestsScreenViewBase::setupScreen();
}

void HeaterTestsScreenView::tearDownScreen() {
    HeaterTestsScreenViewBase::tearDownScreen();
}

void HeaterTestsScreenView::showTestResults(
    ATC::HeaterTestResults results
) {
    if (results.temperatureSuccess) {
        heaterTestsResults.setTemperatureSuccess();
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
