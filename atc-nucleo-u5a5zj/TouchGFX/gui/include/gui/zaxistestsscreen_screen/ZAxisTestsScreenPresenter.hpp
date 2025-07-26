#ifndef ZAXISTESTSSCREENPRESENTER_HPP
#define ZAXISTESTSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ZAxisTestsScreenView;

class ZAxisTestsScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    ZAxisTestsScreenPresenter(ZAxisTestsScreenView& v);

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

    virtual ~ZAxisTestsScreenPresenter() {}

    virtual void handleZAxisTestTaskFinish(
        ATC::AxisTestResults results
    ) override;

    void startButtonPressed();
    void cancelButtonPressed();

private:
    ZAxisTestsScreenPresenter();

    ZAxisTestsScreenView& view;
};

#endif // ZAXISTESTSSCREENPRESENTER_HPP
