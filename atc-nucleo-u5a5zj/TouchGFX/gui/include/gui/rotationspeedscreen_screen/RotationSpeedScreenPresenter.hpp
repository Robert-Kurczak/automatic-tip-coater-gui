#ifndef ROTATIONSPEEDSCREENPRESENTER_HPP
#define ROTATIONSPEEDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RotationSpeedScreenView;

class RotationSpeedScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    RotationSpeedScreenPresenter(RotationSpeedScreenView& v);

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

    virtual ~RotationSpeedScreenPresenter() {}

    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getRotationSpeed();

private:
    RotationSpeedScreenPresenter();

    RotationSpeedScreenView& view;
};

#endif // ROTATIONSPEEDSCREENPRESENTER_HPP
