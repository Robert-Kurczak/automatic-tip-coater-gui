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
    virtual void increaseButtonPressed() override;
    virtual void decreaseButtonPressed() override;
    virtual void saveButtonPressed() override;

private:
    static const uint16_t minTemperature = 0;
    static const uint16_t maxTemperature = 400;
    static const uint8_t temperatureIncrement = 1;

    uint16_t temperature = 0;
};

#endif // HEATERTEMPERATURESCREENVIEW_HPP
