#ifndef HEATERTEMPERATURESCREENVIEW_HPP
#define HEATERTEMPERATURESCREENVIEW_HPP

#include <gui_generated/heatertemperaturescreen_screen/HeaterTemperatureScreenViewBase.hpp>
#include <gui/heatertemperaturescreen_screen/HeaterTemperatureScreenPresenter.hpp>

class HeaterTemperatureScreenView : public HeaterTemperatureScreenViewBase
{
public:
    HeaterTemperatureScreenView();
    virtual ~HeaterTemperatureScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void resetConfigurator() override;
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    void updateDisplayedValue();
};

#endif // HEATERTEMPERATURESCREENVIEW_HPP
