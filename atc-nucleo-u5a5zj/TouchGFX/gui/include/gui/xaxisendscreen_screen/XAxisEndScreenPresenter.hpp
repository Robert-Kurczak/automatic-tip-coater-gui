#ifndef XAXISENDSCREENPRESENTER_HPP
#define XAXISENDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class XAxisEndScreenView;

class XAxisEndScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    XAxisEndScreenPresenter(XAxisEndScreenView& v);

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

    virtual ~XAxisEndScreenPresenter() {}

    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getXAxisEnd();

private:
    XAxisEndScreenPresenter();

    XAxisEndScreenView& view;
};

#endif // XAXISENDSCREENPRESENTER_HPP
