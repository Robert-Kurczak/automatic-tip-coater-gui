#ifndef ROTATIONDIRECTIONSCREENPRESENTER_HPP
#define ROTATIONDIRECTIONSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RotationDirectionScreenView;

class RotationDirectionScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    RotationDirectionScreenPresenter(RotationDirectionScreenView& v);

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

    virtual ~RotationDirectionScreenPresenter() {}

    bool isRotationClockwise();
    void clockwiseButtonPressed();
    void counterClockwiseButtonPressed();
    void saveButtonPressed();

private:
    RotationDirectionScreenPresenter();

    RotationDirectionScreenView& view;
};

#endif // ROTATIONDIRECTIONSCREENPRESENTER_HPP
