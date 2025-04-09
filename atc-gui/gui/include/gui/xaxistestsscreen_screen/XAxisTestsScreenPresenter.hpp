#ifndef XAXISTESTSSCREENPRESENTER_HPP
#define XAXISTESTSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class XAxisTestsScreenView;

class XAxisTestsScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    XAxisTestsScreenPresenter(XAxisTestsScreenView& v);

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

    virtual ~XAxisTestsScreenPresenter() {}

private:
    XAxisTestsScreenPresenter();

    XAxisTestsScreenView& view;
};

#endif // XAXISTESTSSCREENPRESENTER_HPP
