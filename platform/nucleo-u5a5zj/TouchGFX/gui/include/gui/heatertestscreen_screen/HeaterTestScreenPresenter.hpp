#ifndef HEATERTESTSSCREENPRESENTER_HPP
#define HEATERTESTSSCREENPRESENTER_HPP

#include "application/System/Tasks/Task/HeaterTestTask/HeaterTestResults.hpp"

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HeaterTestScreenView;

class HeaterTestScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    HeaterTestScreenPresenter(HeaterTestScreenView& v);

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

    virtual ~HeaterTestScreenPresenter() {}

    virtual void handleHeaterTestTaskFinish(
        ATC::HeaterTestResults results
    ) override;

    void startButtonPressed();
    void cancelButtonPressed();

private:
    HeaterTestScreenPresenter();

    HeaterTestScreenView& view;
};

#endif // HEATERTESTSSCREENPRESENTER_HPP
