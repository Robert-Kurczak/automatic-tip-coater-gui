#pragma once

#include "BoardDevices.hpp"
#include "application/Math/Math.hpp"

#include <stdint.h>

namespace ATC {
class Board {
private:
    BoardDevices& devices_;

public:
    Board(BoardDevices& devices);

    void init();

    void drawOnDisplay(
        const std::span<const uint16_t>& frameBuffer,
        const Rectangle& window
    );

    Vector2 readTouchScreenPosition();

    void cancelCurrentTask();

    void startCoatingSequence();
    bool isCoatingSequenceFinished();

    void calibrate();
    bool isCalibrationFinished();

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

    void testXAxis();
    void testYAxis();
    void testZAxis();
    void testHeater();
};
}