#ifndef HEATERTEMPERATURESCREENPRESENTER_HPP
#define HEATERTEMPERATURESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HeaterTemperatureScreenView;

class HeaterTemperatureScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    HeaterTemperatureScreenPresenter(HeaterTemperatureScreenView& v);

    /**
     * The activate function is called automatically when this screen is
     * "switched in" (ie. made active). Initialization logic can be placed
     * here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is
     * "switched out" (ie. made inactive). Teardown functionality can be
     * placed here.
     */
    virtual void deactivate();

    virtual ~HeaterTemperatureScreenPresenter() {}

    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getHeaterTemperature();

private:
    HeaterTemperatureScreenPresenter();

    HeaterTemperatureScreenView& view;
};

#endif // HEATERTEMPERATURESCREENPRESENTER_HPP
