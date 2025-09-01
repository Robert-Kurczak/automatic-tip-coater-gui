#include <gui/spindletestsscreen_screen/SpindleTestsScreenView.hpp>

SpindleTestsScreenView::SpindleTestsScreenView() {}

void SpindleTestsScreenView::setupScreen() {
    SpindleTestsScreenViewBase::setupScreen();
}

void SpindleTestsScreenView::tearDownScreen() {
    SpindleTestsScreenViewBase::tearDownScreen();
}

void SpindleTestsScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void SpindleTestsScreenView::showTestResults(
    ATC::SpindleTestResults results
) {
    if (results.motorDriverSuccess) {
        spindleTestsResults.setMotorDriverSuccess();
    } else {
        spindleTestsResults.setMotorDriverError();
    }
}

void SpindleTestsScreenView::startTest() {
    spindleTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void SpindleTestsScreenView::cancelTest() {
    spindleTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}