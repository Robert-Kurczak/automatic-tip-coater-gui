#pragma once

namespace ATC {
class ITemperatureSensor {
public:
    ITemperatureSensor() = default;
    ITemperatureSensor(const ITemperatureSensor&) = delete;
    ITemperatureSensor& operator=(const ITemperatureSensor&) = delete;
    ITemperatureSensor(ITemperatureSensor&&) = delete;
    ITemperatureSensor& operator=(ITemperatureSensor&&) = delete;
    virtual ~ITemperatureSensor() = default;

    virtual void init() = 0;

    [[nodiscard]] virtual float getCelsius() = 0;
};
}