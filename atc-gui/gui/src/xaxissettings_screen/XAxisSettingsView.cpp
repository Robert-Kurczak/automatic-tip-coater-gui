#include <gui/xaxissettings_screen/XAxisSettingsView.hpp>

XAxisSettingsView::XAxisSettingsView()
{

}

void XAxisSettingsView::setupScreen()
{
    XAxisSettingsViewBase::setupScreen();
}

void XAxisSettingsView::tearDownScreen()
{
    XAxisSettingsViewBase::tearDownScreen();
}

void XAxisSettingsView::increaseStartPositionPressed()
{
    if (startPosition <= maxPosition - positionIncrement)
    {
        startPosition += positionIncrement;
    }

    updateStartPositionValue();
}

void XAxisSettingsView::decreaseStartPositionPressed()
{
    if (startPosition >= positionIncrement)
    {
        startPosition -= positionIncrement;
    }

    updateStartPositionValue();
}

void XAxisSettingsView::applyStartPositionPressed()
{

}

void XAxisSettingsView::updateStartPositionValue()
{
    Unicode::snprintf(
        startPositionTextBuffer,
        STARTPOSITIONTEXT_SIZE,
        "%d",
        startPosition
    );

	startPositionText.invalidate();
}