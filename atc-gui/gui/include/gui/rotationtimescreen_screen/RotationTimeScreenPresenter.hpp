#ifndef ROTATIONTIMESCREENPRESENTER_HPP
#define ROTATIONTIMESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RotationTimeScreenView;

class RotationTimeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    RotationTimeScreenPresenter(RotationTimeScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~RotationTimeScreenPresenter() {}

private:
    RotationTimeScreenPresenter();

    RotationTimeScreenView& view;
};

#endif // ROTATIONTIMESCREENPRESENTER_HPP
