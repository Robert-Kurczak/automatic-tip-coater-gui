#ifndef SETTINGDISPLAY_HPP
#define SETTINGDISPLAY_HPP

#include "application/System/Controllers/PersistentStorageController/PersistentData/AxisPersistentConfig.hpp"

#include <gui_generated/containers/SettingDisplayBase.hpp>

class SettingDisplay : public SettingDisplayBase {
public:
    SettingDisplay();
    virtual ~SettingDisplay() {}

    virtual void initialize();

    void displayXAxisSettings(const ATC::AxisPersistentConfig& config);
    void displayYAxisSettings(const ATC::AxisPersistentConfig& config);
    void displayZAxisSettings(const ATC::AxisPersistentConfig& config);
};

#endif // SETTINGDISPLAY_HPP
