#ifndef XAXISSTARTSCREEN_BAKPRESENTER_HPP
#define XAXISSTARTSCREEN_BAKPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class XAxisStartScreen_bakView;

class XAxisStartScreen_bakPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    XAxisStartScreen_bakPresenter(XAxisStartScreen_bakView& v);

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

    virtual ~XAxisStartScreen_bakPresenter() {}

private:
    XAxisStartScreen_bakPresenter();

    XAxisStartScreen_bakView& view;
};

#endif // XAXISSTARTSCREEN_BAKPRESENTER_HPP
