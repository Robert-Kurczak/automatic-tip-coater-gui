#ifndef ZAXISSPEEDSCREENVIEW_HPP
#define ZAXISSPEEDSCREENVIEW_HPP

#include <gui_generated/zaxisspeedscreen_screen/ZAxisSpeedScreenViewBase.hpp>
#include <gui/zaxisspeedscreen_screen/ZAxisSpeedScreenPresenter.hpp>

class ZAxisSpeedScreenView : public ZAxisSpeedScreenViewBase
{
public:
    ZAxisSpeedScreenView();
    virtual ~ZAxisSpeedScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // ZAXISSPEEDSCREENVIEW_HPP
