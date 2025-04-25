#include <gui/zaxistestsscreen_screen/ZAxisTestsScreenView.hpp>

ZAxisTestsScreenView::ZAxisTestsScreenView()
{

}

void ZAxisTestsScreenView::setupScreen()
{
    ZAxisTestsScreenViewBase::setupScreen();
}

void ZAxisTestsScreenView::tearDownScreen()
{
    ZAxisTestsScreenViewBase::tearDownScreen();
}

void ZAxisTestsScreenView::startTest()
{
    axisTestsResults.setLoadingIcons();
}

void ZAxisTestsScreenView::cancelTest()
{
    axisTestsResults.setStartLimitSwitchError();
    axisTestsResults.setEndLimitSwitchError();
    axisTestsResults.setMotorDriverError();
}