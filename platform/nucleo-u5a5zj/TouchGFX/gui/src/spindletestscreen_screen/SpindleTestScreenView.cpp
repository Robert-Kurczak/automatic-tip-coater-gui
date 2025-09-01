#include <gui/spindletestscreen_screen/SpindleTestScreenView.hpp>

SpindleTestScreenView::SpindleTestScreenView() {}

void SpindleTestScreenView::setupScreen() {
    SpindleTestScreenViewBase::setupScreen();
}

void SpindleTestScreenView::tearDownScreen() {
    SpindleTestScreenViewBase::tearDownScreen();
}

void SpindleTestScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void SpindleTestScreenView::showTestResults(
    ATC::SpindleTestResults results
) {
    if (results.motorDriverSuccess) {
        spindleTestsResults.setMotorDriverSuccess();
    } else {
        spindleTestsResults.setMotorDriverError();
    }
}

void SpindleTestScreenView::startTest() {
    spindleTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void SpindleTestScreenView::cancelTest() {
    spindleTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}