#ifndef HEATERTESTSSCREENPRESENTER_HPP
#define HEATERTESTSSCREENPRESENTER_HPP

#include "application/Hardware/Heater/HeaterTestResults.hpp"

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HeaterTestsScreenView;

class HeaterTestsScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    HeaterTestsScreenPresenter(HeaterTestsScreenView& v);

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

    virtual ~HeaterTestsScreenPresenter() {}

    virtual void handleHeaterTestTaskFinish(
        ATC::HeaterTestResults results
    ) override;

    void startButtonPressed();
    void cancelButtonPressed();

private:
    HeaterTestsScreenPresenter();

    HeaterTestsScreenView& view;
};

#endif // HEATERTESTSSCREENPRESENTER_HPP
