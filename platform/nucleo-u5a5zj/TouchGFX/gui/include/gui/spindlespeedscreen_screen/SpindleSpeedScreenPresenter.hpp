#ifndef SPINDLESPEEDSCREENPRESENTER_HPP
#define SPINDLESPEEDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SpindleSpeedScreenView;

class SpindleSpeedScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    SpindleSpeedScreenPresenter(SpindleSpeedScreenView& v);

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

    virtual ~SpindleSpeedScreenPresenter() {}

    void resetConfigurator();
    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getSpindleSpeedPercent();

private:
    SpindleSpeedScreenPresenter();

    SpindleSpeedScreenView& view;
};

#endif // SPINDLESPEEDSCREENPRESENTER_HPP
