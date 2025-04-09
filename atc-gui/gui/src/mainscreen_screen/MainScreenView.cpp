#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();

    easeInAnimation(startButtonContainer);
    easeInAnimation(calibrateButtonContainer);
    easeInAnimation(settingsButtonContainer);
    easeInAnimation(testsButtonContainer);
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::easeInAnimation(touchgfx::MoveAnimator<touchgfx::Container>& widget)
{
    const int16_t initialX = widget.getX();
    const int16_t initialY = widget.getY();
    const auto progression = touchgfx::EasingEquations::quintEaseOut;

    widget.moveTo(105, 105);
    widget.startMoveAnimation(initialX, initialY, 55, progression, progression);
}
