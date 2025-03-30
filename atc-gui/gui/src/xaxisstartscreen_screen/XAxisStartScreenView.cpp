#include <gui/xaxisstartscreen_screen/XAxisStartScreenView.hpp>

XAxisStartScreenView::XAxisStartScreenView()
{

}

void XAxisStartScreenView::setupScreen()
{
    XAxisStartScreenViewBase::setupScreen();
}

void XAxisStartScreenView::tearDownScreen()
{
    XAxisStartScreenViewBase::tearDownScreen();
}

void XAxisStartScreenView::increaseStartPositionPressed()
{
    if (startPosition <= maxPosition - positionIncrement)
    {
        startPosition += positionIncrement;
    }

    updateStartPositionValue();
}

void XAxisStartScreenView::decreaseStartPositionPressed()
{
    if (startPosition >= positionIncrement)
    {
        startPosition -= positionIncrement;
    }

    updateStartPositionValue();
}

void XAxisStartScreenView::applyStartPositionPressed()
{

}

void XAxisStartScreenView::updateStartPositionValue()
{
    Unicode::snprintf(
        startPositionTextBuffer,
        STARTPOSITIONTEXT_SIZE,
        "%d",
        startPosition
    );

	startPositionText.invalidate();
}