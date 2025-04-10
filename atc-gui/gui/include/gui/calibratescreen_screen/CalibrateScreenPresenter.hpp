#ifndef CALIBRATESCREENPRESENTER_HPP
#define CALIBRATESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class CalibrateScreenView;

class CalibrateScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    CalibrateScreenPresenter(CalibrateScreenView& v);

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

    virtual ~CalibrateScreenPresenter() {}

private:
    CalibrateScreenPresenter();

    CalibrateScreenView& view;
};

#endif // CALIBRATESCREENPRESENTER_HPP
