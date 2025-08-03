#ifndef HEATERSTATESCREENPRESENTER_HPP
#define HEATERSTATESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HeaterStateScreenView;

class HeaterStateScreenPresenter :
    public touchgfx::Presenter,
    public ModelListener {
public:
    HeaterStateScreenPresenter(HeaterStateScreenView& v);

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

    virtual ~HeaterStateScreenPresenter() {}

    void onButtonPressed();
    void offButtonPressed();
    void saveButtonPressed();

    bool isHeaterOn();

private:
    HeaterStateScreenPresenter();

    HeaterStateScreenView& view;
};

#endif // HEATERSTATESCREENPRESENTER_HPP
