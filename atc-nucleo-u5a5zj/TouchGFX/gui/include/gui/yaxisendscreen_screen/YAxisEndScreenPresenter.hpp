#ifndef YAXISENDSCREENPRESENTER_HPP
#define YAXISENDSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class YAxisEndScreenView;

class YAxisEndScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    YAxisEndScreenPresenter(YAxisEndScreenView& v);

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

    virtual ~YAxisEndScreenPresenter() {}

    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getYAxisEnd();

private:
    YAxisEndScreenPresenter();

    YAxisEndScreenView& view;
};

#endif // YAXISENDSCREENPRESENTER_HPP
