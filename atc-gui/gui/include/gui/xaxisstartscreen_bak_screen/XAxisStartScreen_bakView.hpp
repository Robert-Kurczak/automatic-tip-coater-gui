#ifndef XAXISSTARTSCREEN_BAKVIEW_HPP
#define XAXISSTARTSCREEN_BAKVIEW_HPP

#include <gui_generated/xaxisstartscreen_bak_screen/XAxisStartScreen_bakViewBase.hpp>
#include <gui/xaxisstartscreen_bak_screen/XAxisStartScreen_bakPresenter.hpp>

class XAxisStartScreen_bakView : public XAxisStartScreen_bakViewBase
{
public:
    XAxisStartScreen_bakView();
    virtual ~XAxisStartScreen_bakView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // XAXISSTARTSCREEN_BAKVIEW_HPP
