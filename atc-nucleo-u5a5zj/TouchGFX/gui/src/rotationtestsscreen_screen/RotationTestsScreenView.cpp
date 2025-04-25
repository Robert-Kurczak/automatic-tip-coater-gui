#include <gui/rotationtestsscreen_screen/RotationTestsScreenView.hpp>

RotationTestsScreenView::RotationTestsScreenView()
{

}

void RotationTestsScreenView::setupScreen()
{
    RotationTestsScreenViewBase::setupScreen();
}

void RotationTestsScreenView::tearDownScreen()
{
    RotationTestsScreenViewBase::tearDownScreen();
}

void RotationTestsScreenView::startTest()
{
    rotationTestsResults.setLoadingIcons();
}

void RotationTestsScreenView::cancelTest()
{
    rotationTestsResults.setMotorDriverError();
}
