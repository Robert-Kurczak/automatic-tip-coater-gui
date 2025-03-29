#ifndef XAXISSETTINGSPRESENTER_HPP
#define XAXISSETTINGSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class XAxisSettingsView;

class XAxisSettingsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    XAxisSettingsPresenter(XAxisSettingsView& v);

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

    virtual ~XAxisSettingsPresenter() {}

private:
    XAxisSettingsPresenter();

    XAxisSettingsView& view;
};

#endif // XAXISSETTINGSPRESENTER_HPP
