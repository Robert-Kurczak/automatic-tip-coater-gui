#ifndef XAXISTESTSSCREENPRESENTER_HPP
#define XAXISTESTSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class XAxisTestScreenView;

class XAxisTestScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    XAxisTestScreenPresenter(XAxisTestScreenView& v);

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

    virtual ~XAxisTestScreenPresenter() {}

    virtual void handleXAxisTestTaskFinish(
        ATC::AxisTestResults results
    ) override;

    void startButtonPressed();
    void cancelButtonPressed();

private:
    XAxisTestScreenPresenter();

    XAxisTestScreenView& view;
};

#endif // XAXISTESTSSCREENPRESENTER_HPP
