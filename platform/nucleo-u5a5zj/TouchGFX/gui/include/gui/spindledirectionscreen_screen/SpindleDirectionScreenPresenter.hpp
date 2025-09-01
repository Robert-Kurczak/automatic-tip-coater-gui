#ifndef SPINDLEDIRECTIONSCREENPRESENTER_HPP
#define SPINDLEDIRECTIONSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SpindleDirectionScreenView;

class SpindleDirectionScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    SpindleDirectionScreenPresenter(SpindleDirectionScreenView& v);

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

    virtual ~SpindleDirectionScreenPresenter() {}

    void clockwiseButtonPressed();
    void counterClockwiseButtonPressed();
    void saveButtonPressed();

    bool isSpindleDirectionClockwise();

private:
    SpindleDirectionScreenPresenter();

    SpindleDirectionScreenView& view;
};

#endif // SPINDLEDIRECTIONSCREENPRESENTER_HPP
