#ifndef SPINDLETESTSSCREENPRESENTER_HPP
#define SPINDLETESTSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SpindleTestScreenView;

class SpindleTestScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    SpindleTestScreenPresenter(SpindleTestScreenView& v);

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

    virtual ~SpindleTestScreenPresenter() {}

    virtual void handleSpindleTestTaskFinish(
        ATC::SpindleTestResults results
    ) override;

    void startButtonPressed();
    void cancelButtonPressed();

private:
    SpindleTestScreenPresenter();

    SpindleTestScreenView& view;
};

#endif // SPINDLETESTSSCREENPRESENTER_HPP
