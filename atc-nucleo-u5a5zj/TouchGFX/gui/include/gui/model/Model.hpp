#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void cancelCurrentTask();

    void startCoatingSequence();
    bool isCoatingSequenceFinished();

    void calibrate();
    bool isCalibrationFinished();

    void increaseXAxisStart();
    void decreaseXAxisStart();
    uint32_t getXAxisStart();

    void increaseXAxisEnd();
    void decreaseXAxisEnd();
    uint32_t getXAxisEnd();

    void increaseXAxisSpeed();
    void decreaseXAxisSpeed();
    uint32_t getXAxisSpeed();

    void increaseYAxisStart();
    void decreaseYAxisStart();
    uint32_t getYAxisStart();

    void increaseYAxisEnd();
    void decreaseYAxisEnd();
    uint32_t getYAxisEnd();

    void increaseYAxisSpeed();
    void decreaseYAxisSpeed();
    uint32_t getYAxisSpeed();

    void increaseZAxisStart();
    void decreaseZAxisStart();
    uint32_t getZAxisStart();

    void increaseZAxisEnd();
    void decreaseZAxisEnd();
    uint32_t getZAxisEnd();

    void increaseZAxisSpeed();
    void decreaseZAxisSpeed();
    uint32_t getZAxisSpeed();

    void increaseRotationSpeed();
    void decreaseRotationSpeed();
    uint32_t getRotationSpeed();

    void setClockwiseRotation();
    void setCounterClockwiseRotation();
    bool isRotationClockwise();

    void testXAxis();
    void testYAxis();
    void testZAxis();
    void testHeater();

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
