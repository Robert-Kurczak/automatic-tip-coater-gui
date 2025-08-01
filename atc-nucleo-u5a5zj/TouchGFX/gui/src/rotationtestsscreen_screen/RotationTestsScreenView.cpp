#include <gui/rotationtestsscreen_screen/RotationTestsScreenView.hpp>

RotationTestsScreenView::RotationTestsScreenView() {}

void RotationTestsScreenView::setupScreen() {
    RotationTestsScreenViewBase::setupScreen();
}

void RotationTestsScreenView::tearDownScreen() {
    RotationTestsScreenViewBase::tearDownScreen();
}

void RotationTestsScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void RotationTestsScreenView::showTestResults(
    ATC::RotatorTestResults results
) {
    if (results.motorDriverSuccess) {
        rotationTestsResults.setMotorDriverSuccess();
    } else {
        rotationTestsResults.setMotorDriverError();
    }
}

void RotationTestsScreenView::startTest() {
    rotationTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void RotationTestsScreenView::cancelTest() {
    rotationTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}
