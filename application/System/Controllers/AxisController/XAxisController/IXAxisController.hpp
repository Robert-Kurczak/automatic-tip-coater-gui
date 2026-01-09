#pragma once

#include "../IAxisController.hpp"

namespace ATC {
class IXAxisController : public IAxisController {
public:
    virtual void moveToHeaterFrontPosition() = 0;
    [[nodiscard]] virtual bool isAtHeaterFrontPosition() const = 0;
};
}