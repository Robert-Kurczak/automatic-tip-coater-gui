#ifndef YAXISSPEEDSCREENPRESENTER_HPP
#define YAXISSPEEDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class YAxisSpeedScreenView;

class YAxisSpeedScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    YAxisSpeedScreenPresenter(YAxisSpeedScreenView& v);

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

    virtual ~YAxisSpeedScreenPresenter() {}

    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getYAxisSpeed();

private:
    YAxisSpeedScreenPresenter();

    YAxisSpeedScreenView& view;
};

#endif // YAXISSPEEDSCREENPRESENTER_HPP
