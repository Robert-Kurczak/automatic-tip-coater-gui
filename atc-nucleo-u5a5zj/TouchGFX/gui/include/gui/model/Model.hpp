#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

class ModelListener;

class Model {
public:
    Model();

    void bind(ModelListener* listener) {
        modelListener = listener;
    }

    void tick();

    void startCoatingTask();
    void startCalibrationTask();

    void startXAxisTestTask();
    void startYAxisTestTask();
    void startZAxisTestTask();
    void startHeaterTestTask();
    void startRotationTestTask();

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

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
