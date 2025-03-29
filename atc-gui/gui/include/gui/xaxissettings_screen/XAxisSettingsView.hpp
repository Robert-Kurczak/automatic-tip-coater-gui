#ifndef XAXISSETTINGSVIEW_HPP
#define XAXISSETTINGSVIEW_HPP

#include <gui_generated/xaxissettings_screen/XAxisSettingsViewBase.hpp>
#include <gui/xaxissettings_screen/XAxisSettingsPresenter.hpp>

class XAxisSettingsView : public XAxisSettingsViewBase
{
public:
    XAxisSettingsView();
    virtual ~XAxisSettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // XAXISSETTINGSVIEW_HPP
