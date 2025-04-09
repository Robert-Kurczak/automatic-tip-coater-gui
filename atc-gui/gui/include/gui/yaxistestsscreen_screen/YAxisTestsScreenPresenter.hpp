#ifndef YAXISTESTSSCREENPRESENTER_HPP
#define YAXISTESTSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class YAxisTestsScreenView;

class YAxisTestsScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    YAxisTestsScreenPresenter(YAxisTestsScreenView& v);

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

    virtual ~YAxisTestsScreenPresenter() {}

private:
    YAxisTestsScreenPresenter();

    YAxisTestsScreenView& view;
};

#endif // YAXISTESTSSCREENPRESENTER_HPP
