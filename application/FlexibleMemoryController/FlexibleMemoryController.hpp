#pragma once

#include <stdint.h>

class FlexibleMemoryController {
private:
    volatile uint16_t* registerAddress;
    volatile uint16_t* dataAddress;
    
public:
    FlexibleMemoryController(
        const uintptr_t registerAddress_,
        const uintptr_t dataAddress_
    );
};