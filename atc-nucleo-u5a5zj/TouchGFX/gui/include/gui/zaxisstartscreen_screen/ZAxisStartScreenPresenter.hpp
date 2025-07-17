#ifndef ZAXISSTARTSCREENPRESENTER_HPP
#define ZAXISSTARTSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ZAxisStartScreenView;

class ZAxisStartScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    ZAxisStartScreenPresenter(ZAxisStartScreenView& v);

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

    virtual ~ZAxisStartScreenPresenter() {}

    void increaseButtonPressed();
    void decreaseButtonPressed();
    void saveButtonPressed();

    uint32_t getZAxisStart();

private:
    ZAxisStartScreenPresenter();

    ZAxisStartScreenView& view;
};

#endif // ZAXISSTARTSCREENPRESENTER_HPP
