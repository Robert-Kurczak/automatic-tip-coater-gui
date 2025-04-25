#include <gui/heatertestsscreen_screen/HeaterTestsScreenView.hpp>

HeaterTestsScreenView::HeaterTestsScreenView()
{

}

void HeaterTestsScreenView::setupScreen()
{
    HeaterTestsScreenViewBase::setupScreen();
}

void HeaterTestsScreenView::tearDownScreen()
{
    HeaterTestsScreenViewBase::tearDownScreen();
}

void HeaterTestsScreenView::startTest()
{
    heaterTestsResults.setLoadingIcons();
}

void HeaterTestsScreenView::cancelTest()
{
    heaterTestsResults.setTemperatureError();
}