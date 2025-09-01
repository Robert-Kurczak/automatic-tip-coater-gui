#include <gui/zaxistestscreen_screen/ZAxisTestScreenView.hpp>

ZAxisTestScreenView::ZAxisTestScreenView() {}

void ZAxisTestScreenView::setupScreen() {
    ZAxisTestScreenViewBase::setupScreen();
}

void ZAxisTestScreenView::tearDownScreen() {
    ZAxisTestScreenViewBase::tearDownScreen();
}

void ZAxisTestScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void ZAxisTestScreenView::showTestResults(ATC::AxisTestResults results) {
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

void ZAxisTestScreenView::startTest() {
    axisTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void ZAxisTestScreenView::cancelTest() {
    axisTestsResults.setStartLimitSwitchError();
    axisTestsResults.setEndLimitSwitchError();
    axisTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}