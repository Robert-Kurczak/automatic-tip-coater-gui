#ifndef MODEL_HPP
#define MODEL_HPP

#include "TargetSystemRoot.hpp"

#include <stdint.h>

class ModelListener;

class Model {
private:
    ModelListener* modelListener;
    ATC::SystemApi& systemApi_ =
        ATC::TargetSystemRoot::getSystemRoot().getSystemApi();

    void pollCoatingTask();
    void pollCalibrationTask();
    void pollXAxisTestTask();
    void pollYAxisTestTask();
    void pollZAxisTestTask();
    void pollRotatorTestTask();
    void pollHeaterTestTask();

public:
    Model();

    void bind(ModelListener* listener) {
        modelListener = listener;
    }

    void tick();

    ATC::SystemApi& getSystemApi();
};

#endif // MODEL_HPP
