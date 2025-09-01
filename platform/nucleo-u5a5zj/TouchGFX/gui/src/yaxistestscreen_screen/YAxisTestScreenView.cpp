#include <gui/yaxistestscreen_screen/YAxisTestScreenView.hpp>

YAxisTestScreenView::YAxisTestScreenView() {}

void YAxisTestScreenView::setupScreen() {
    YAxisTestScreenViewBase::setupScreen();
}

void YAxisTestScreenView::tearDownScreen() {
    YAxisTestScreenViewBase::tearDownScreen();
}

void YAxisTestScreenView::resetFooterButtons() {
    startCancelFooter.resetState();
}

void YAxisTestScreenView::showTestResults(ATC::AxisTestResults results) {
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

void YAxisTestScreenView::startTest() {
    axisTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void YAxisTestScreenView::cancelTest() {
    axisTestsResults.setStartLimitSwitchError();
    axisTestsResults.setEndLimitSwitchError();
    axisTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}