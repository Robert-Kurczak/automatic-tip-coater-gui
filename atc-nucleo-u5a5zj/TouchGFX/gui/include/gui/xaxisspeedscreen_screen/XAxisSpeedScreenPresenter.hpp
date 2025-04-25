#ifndef XAXISSPEEDSCREENPRESENTER_HPP
#define XAXISSPEEDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class XAxisSpeedScreenView;

class XAxisSpeedScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    XAxisSpeedScreenPresenter(XAxisSpeedScreenView& v);

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

    virtual ~XAxisSpeedScreenPresenter() {}

private:
    XAxisSpeedScreenPresenter();

    XAxisSpeedScreenView& view;
};

#endif // XAXISSPEEDSCREENPRESENTER_HPP
