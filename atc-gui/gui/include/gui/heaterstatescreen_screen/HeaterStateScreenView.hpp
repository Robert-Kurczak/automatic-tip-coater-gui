#ifndef HEATERSTATESCREENVIEW_HPP
#define HEATERSTATESCREENVIEW_HPP

#include <gui_generated/heaterstatescreen_screen/HeaterStateScreenViewBase.hpp>
#include <gui/heaterstatescreen_screen/HeaterStateScreenPresenter.hpp>

class HeaterStateScreenView : public HeaterStateScreenViewBase
{
public:
    HeaterStateScreenView();
    virtual ~HeaterStateScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void stateOffButtonPressed() override;
    virtual void stateOnButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    bool stateOn = false;
};

#endif // HEATERSTATESCREENVIEW_HPP
