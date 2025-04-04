#ifndef ZAXISSPEEDSCREENPRESENTER_HPP
#define ZAXISSPEEDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ZAxisSpeedScreenView;

class ZAxisSpeedScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ZAxisSpeedScreenPresenter(ZAxisSpeedScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ZAxisSpeedScreenPresenter() {}

private:
    ZAxisSpeedScreenPresenter();

    ZAxisSpeedScreenView& view;
};

#endif // ZAXISSPEEDSCREENPRESENTER_HPP
