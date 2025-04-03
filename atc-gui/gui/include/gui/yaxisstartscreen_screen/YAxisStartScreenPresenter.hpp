#ifndef YAXISSTARTSCREENPRESENTER_HPP
#define YAXISSTARTSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class YAxisStartScreenView;

class YAxisStartScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    YAxisStartScreenPresenter(YAxisStartScreenView& v);

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

    virtual ~YAxisStartScreenPresenter() {}

private:
    YAxisStartScreenPresenter();

    YAxisStartScreenView& view;
};

#endif // YAXISSTARTSCREENPRESENTER_HPP
