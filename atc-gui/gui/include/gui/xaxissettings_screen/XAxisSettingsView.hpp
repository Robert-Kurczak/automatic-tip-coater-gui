#ifndef XAXISSETTINGSVIEW_HPP
#define XAXISSETTINGSVIEW_HPP

#include <gui_generated/xaxissettings_screen/XAxisSettingsViewBase.hpp>
#include <gui/xaxissettings_screen/XAxisSettingsPresenter.hpp>

class XAxisSettingsView : public XAxisSettingsViewBase
{
public:
    XAxisSettingsView();
    virtual ~XAxisSettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseStartPositionPressed() override;
    virtual void decreaseStartPositionPressed() override;
    virtual void applyStartPositionPressed() override;

private:
    static const uint16_t minPosition = 0;
    static const uint16_t maxPosition = 65000;
    static const uint8_t positionIncrement = 10;

    static const uint8_t minSpeed = 0;
    static const uint8_t maxSpeed = 255;
    static const uint8_t speedIncrement = 1;

    uint16_t startPosition = 0;
    uint16_t endPosition = 0;
    uint16_t speed = 0;

    void updateStartPositionValue();
};

#endif // XAXISSETTINGSVIEW_HPP
