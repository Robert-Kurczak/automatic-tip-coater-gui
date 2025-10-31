#include "FakeHALSDL2.hpp"

namespace touchgfx {
bool FakeHALSDL2::sdl_init(int argcount, char** args) {
    ATC::TargetSystemRoot::getSystemRoot().init();

    return HALSDL2::sdl_init(argcount, args);
}

void FakeHALSDL2::tick() {
    ATC::TargetSystemRoot::getSystemRoot().tick();

    HALSDL2::tick();
}
}