#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenView.hpp>

ZAxisTestsScreenView::ZAxisTestsScreenView() {}

void ZAxisTestsScreenView::setupScreen() {
    ZAxisTestsScreenViewBase::setupScreen();
}

void ZAxisTestsScreenView::tearDownScreen() {
    ZAxisTestsScreenViewBase::tearDownScreen();
}

void ZAxisTestsScreenView::showTestResults(
    ATC::ZAxisTestResults results
) {
    if (results.startLimitSwitchSuccess) {
        axisTestsResults.setStartLimitSwitchSuccess();
    } else {
        axisTestsResults.setStartLimitSwitchError();
    }

    if (results.endLimitSwitchSuccess) {
        axisTestsResults.setEndLimitSwitchSuccess();
    } else {
        axisTestsResults.setEndLimitSwitchError();
    }

    if (results.motorDriverSuccess) {
        axisTestsResults.setMotorDriverSuccess();
    } else {
        axisTestsResults.setMotorDriverError();
    }
}

void ZAxisTestsScreenView::startTest() {
    axisTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void ZAxisTestsScreenView::cancelTest() {
    axisTestsResults.setStartLimitSwitchError();
    axisTestsResults.setEndLimitSwitchError();
    axisTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}