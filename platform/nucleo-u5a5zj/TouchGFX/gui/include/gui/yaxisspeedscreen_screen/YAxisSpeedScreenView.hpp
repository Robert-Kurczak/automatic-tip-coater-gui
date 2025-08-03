#ifndef YAXISSPEEDSCREENVIEW_HPP
#define YAXISSPEEDSCREENVIEW_HPP

#include <gui/yaxisspeedscreen_screen/YAxisSpeedScreenPresenter.hpp>
#include <gui_generated/yaxisspeedscreen_screen/YAxisSpeedScreenViewBase.hpp>

class YAxisSpeedScreenView : public YAxisSpeedScreenViewBase {
public:
    YAxisSpeedScreenView();
    virtual ~YAxisSpeedScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // YAXISSPEEDSCREENVIEW_HPP
