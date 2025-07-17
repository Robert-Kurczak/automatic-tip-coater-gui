#ifndef ROTATIONTESTSSCREENPRESENTER_HPP
#define ROTATIONTESTSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RotationTestsScreenView;

class RotationTestsScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    RotationTestsScreenPresenter(RotationTestsScreenView& v);

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

    virtual ~RotationTestsScreenPresenter() {}

    void startButtonPressed();
    void cancelButtonPressed();

private:
    RotationTestsScreenPresenter();

    RotationTestsScreenView& view;
};

#endif // ROTATIONTESTSSCREENPRESENTER_HPP
