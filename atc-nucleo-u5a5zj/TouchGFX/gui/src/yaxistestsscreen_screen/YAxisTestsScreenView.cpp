#include <gui/yaxistestsscreen_screen/YAxisTestsScreenView.hpp>

YAxisTestsScreenView::YAxisTestsScreenView() {}

void YAxisTestsScreenView::setupScreen() {
    YAxisTestsScreenViewBase::setupScreen();
}

void YAxisTestsScreenView::tearDownScreen() {
    YAxisTestsScreenViewBase::tearDownScreen();
}

void YAxisTestsScreenView::startTest() {
    axisTestsResults.setLoadingIcons();

    presenter->startButtonPressed();
}

void YAxisTestsScreenView::cancelTest() {
    axisTestsResults.setStartLimitSwitchError();
    axisTestsResults.setEndLimitSwitchError();
    axisTestsResults.setMotorDriverError();

    presenter->cancelButtonPressed();
}