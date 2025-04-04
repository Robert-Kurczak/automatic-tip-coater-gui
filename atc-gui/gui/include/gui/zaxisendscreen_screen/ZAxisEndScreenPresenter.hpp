#ifndef ZAXISENDSCREENPRESENTER_HPP
#define ZAXISENDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ZAxisEndScreenView;

class ZAxisEndScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ZAxisEndScreenPresenter(ZAxisEndScreenView& v);

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

    virtual ~ZAxisEndScreenPresenter() {}

private:
    ZAxisEndScreenPresenter();

    ZAxisEndScreenView& view;
};

#endif // ZAXISENDSCREENPRESENTER_HPP
