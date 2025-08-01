#ifndef XAXISSTARTSCREENPRESENTER_HPP
#define XAXISSTARTSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class XAxisStartScreenView;

class XAxisStartScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    XAxisStartScreenPresenter(XAxisStartScreenView& v);

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

    virtual ~XAxisStartScreenPresenter() {}

    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getXAxisStart();

private:
    XAxisStartScreenPresenter();

    XAxisStartScreenView& view;
};

#endif // XAXISSTARTSCREENPRESENTER_HPP
