#ifndef SETTINGDISPLAY_HPP
#define SETTINGDISPLAY_HPP

#include <gui_generated/containers/SettingDisplayBase.hpp>

class SettingDisplay : public SettingDisplayBase
{
public:
    SettingDisplay();
    virtual ~SettingDisplay() {}

    virtual void initialize();
protected:
};

#endif // SETTINGDISPLAY_HPP
