#pragma once

#include "BoardDevices.hpp"
#include "application/Hardware/Axes/IAxis.hpp"
#include "application/Math/Math.hpp"
#include "application/System/Logger/ILogger.hpp"

#include <functional>
#include <stdint.h>

namespace ATC {
using TaskCallback = std::function<void(bool wasSuccessful)>;

class Board {
private:
    BoardDevices& devices_;
    ILogger& logger_;

public:
    Board(BoardDevices& devices, ILogger& logger);

    void init();
    void tick();

    void startCoatingTask(TaskCallback callback = [](bool) {});
    void startCalibrationTask(TaskCallback callback = [](bool) {});

    void startXAxisTestTask(AxisTestTaskCallback callback);
    void startYAxisTestTask(AxisTestTaskCallback callback);
    void startZAxisTestTask(AxisTestTaskCallback callback);
    void startRotationTestTask(RotatorTestTaskCallback callback);
    void startHeaterTestTask(HeaterTestTaskCallback callback);

    void cancelCurrentTask();

    void increaseXAxisStart();
    void decreaseXAxisStart();
    void saveXAxisStart();
    uint32_t getXAxisStart();

    void increaseXAxisEnd();
    void decreaseXAxisEnd();
    void saveXAxisEnd();
    uint32_t getXAxisEnd();

    void increaseXAxisSpeed();
    void decreaseXAxisSpeed();
    void saveXAxisSpeed();
    uint32_t getXAxisSpeed();

    void increaseYAxisStart();
    void decreaseYAxisStart();
    void saveYAxisStart();
    uint32_t getYAxisStart();

    void increaseYAxisEnd();
    void decreaseYAxisEnd();
    void saveYAxisEnd();
    uint32_t getYAxisEnd();

    void increaseYAxisSpeed();
    void decreaseYAxisSpeed();
    void saveYAxisSpeed();
    uint32_t getYAxisSpeed();

    void increaseZAxisStart();
    void decreaseZAxisStart();
    void saveZAxisStart();
    uint32_t getZAxisStart();

    void increaseZAxisEnd();
    void decreaseZAxisEnd();
    void saveZAxisEnd();
    uint32_t getZAxisEnd();

    void increaseZAxisSpeed();
    void decreaseZAxisSpeed();
    void saveZAxisSpeed();
    uint32_t getZAxisSpeed();

    void increaseRotationSpeed();
    void decreaseRotationSpeed();
    void saveRotationSpeed();
    uint32_t getRotationSpeed();

    void setClockwiseRotation();
    void setCounterClockwiseRotation();
    void saveRotationDirection();
    bool isRotationClockwise();

    void increaseRotationTime();
    void decreaseRotationTime();
    void saveRotationTime();
    uint32_t getRotationTime();

    void setHeaterOn();
    void setHeaterOff();
    void saveHeaterState();
    bool isHeaterOn();

    void increaseHeaterTemperature();
    void decreaseHeaterTemperature();
    void saveHeaterTemperature();
    uint32_t getHeaterTemperature();

    void drawOnDisplay(
        const std::span<const uint16_t>& frameBuffer,
        const Rectangle& window
    );

    Vector2 readTouchScreenPosition();
};
}
