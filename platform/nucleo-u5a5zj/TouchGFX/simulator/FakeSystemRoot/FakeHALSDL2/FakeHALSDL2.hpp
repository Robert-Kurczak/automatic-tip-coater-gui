#pragma once

#include "FakeSystemRoot.hpp"

#include <platform/hal/simulator/sdl2/HALSDL2.hpp>

namespace touchgfx {
class FakeHALSDL2 : public HALSDL2 {
public:
    using HALSDL2::HALSDL2;

    virtual bool sdl_init(int argcount, char** args) override;
    virtual void tick() override;
};
}