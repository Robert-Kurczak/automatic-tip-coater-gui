#include "DisplayWs17143.hpp"

#include <array>

// TODO separate DisplayCommands?
// TODO explicitly define register names?
// TODO add rgb to rgb565 conversion
// TODO remove execute function from DisplayCommand struct?
namespace {
struct DisplayCommand {
    const uint16_t reg;
    const uint16_t data;

    void execute(FlexibleMemoryController& fmc) const {
        fmc.writeRegister(reg);
        fmc.writeData(data);
    }
};

const std::array proprietaryInitCommands {
    // Manufacturer Page 1 Commands Enable
    DisplayCommand {.reg = 0xF000, .data = 0x55},
    DisplayCommand {.reg = 0xF001, .data = 0xAA},
    DisplayCommand {.reg = 0xF002, .data = 0x52},
    DisplayCommand {.reg = 0xF003, .data = 0x08},
    DisplayCommand {.reg = 0xF004, .data = 0x01},
    // AVDD: 5.2V
    DisplayCommand {.reg = 0xB000, .data = 0x0D},
    DisplayCommand {.reg = 0xB001, .data = 0x0D},
    DisplayCommand {.reg = 0xB002, .data = 0x0D},
    // AVEE: -5.2V
    DisplayCommand {.reg = 0xB100, .data = 0x0D},
    DisplayCommand {.reg = 0xB101, .data = 0x0D},
    DisplayCommand {.reg = 0xB102, .data = 0x0D},
    // VCL: -2.5V
    DisplayCommand {.reg = 0xB200, .data = 0x00},
    DisplayCommand {.reg = 0xB201, .data = 0x00},
    DisplayCommand {.reg = 0xB202, .data = 0x00},
    // VGH: 15V
    DisplayCommand {.reg = 0xB300, .data = 0x05},
    DisplayCommand {.reg = 0xB301, .data = 0x05},
    DisplayCommand {.reg = 0xB302, .data = 0x05},
    // VGL: -10V
    DisplayCommand {.reg = 0xB500, .data = 0x28},
    DisplayCommand {.reg = 0xB501, .data = 0x28},
    DisplayCommand {.reg = 0xB502, .data = 0x28},
    // VCOM: -1.375V
    DisplayCommand {.reg = 0xB600, .data = 0x05},
    DisplayCommand {.reg = 0xB601, .data = 0x05},
    DisplayCommand {.reg = 0xB602, .data = 0x05},
    // Gamma
    DisplayCommand {.reg = 0xD100, .data = 0x00},
    DisplayCommand {.reg = 0xD101, .data = 0x00},
    DisplayCommand {.reg = 0xD102, .data = 0x00},
    DisplayCommand {.reg = 0xD103, .data = 0x00},
    DisplayCommand {.reg = 0xD104, .data = 0x00},
    DisplayCommand {.reg = 0xD105, .data = 0x00},
    DisplayCommand {.reg = 0xD106, .data = 0x00},
    DisplayCommand {.reg = 0xD107, .data = 0x00},
    DisplayCommand {.reg = 0xD108, .data = 0x00},
    DisplayCommand {.reg = 0xD109, .data = 0x00},
    DisplayCommand {.reg = 0xD10A, .data = 0x00},
    DisplayCommand {.reg = 0xD10B, .data = 0x00},
    DisplayCommand {.reg = 0xD10C, .data = 0x00},
    DisplayCommand {.reg = 0xD10D, .data = 0x00},
    DisplayCommand {.reg = 0xD10E, .data = 0x00},
    DisplayCommand {.reg = 0xD10F, .data = 0x00}
};

const DisplayCommand formatRGB565Command {.reg = 0x3A00, .data = 0x55};
const DisplayCommand exitSleepCommand {.reg = 0x1100, .data = 0x00};
const DisplayCommand enableDisplayCommand {.reg = 2900, .data = 0x00};
}

DisplayWs17143::DisplayWs17143(
    FlexibleMemoryController& flexibleMemoryController_,
    DelayProvider& delayProvider_
) :
    flexibleMemoryController(flexibleMemoryController_),
    delayProvider(delayProvider_) {}

void DisplayWs17143::init() {
    // TODO Add toggling reset pin first

    for (const DisplayCommand& command : proprietaryInitCommands) {
        command.execute(flexibleMemoryController);
    }

    formatRGB565Command.execute(flexibleMemoryController);
    exitSleepCommand.execute(flexibleMemoryController);
    delayProvider.delayMiliseconds(120);

    enableDisplayCommand.execute(flexibleMemoryController);
    delayProvider.delayMiliseconds(10);
}

void DisplayWs17143::setWindow(
    const uint16_t startX,
    const uint16_t endX,
    const uint16_t startY,
    const uint16_t endY
) {
    const uint8_t xBytes[] {
        uint8_t(startX >> 8),
        uint8_t(startX & 0xFF),
        uint8_t(endX >> 8),
        uint8_t(endX & 0xFF)
    };
    const uint8_t yBytes[] {
        uint8_t(startY >> 8),
        uint8_t(startY & 0xFF),
        uint8_t(endY >> 8),
        uint8_t(endY & 0xFF)
    };

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController.writeRegister(0x2A00 + i);
        flexibleMemoryController.writeData(xBytes[i]);
    }

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController.writeRegister(0x2B00 + i);
        flexibleMemoryController.writeData(yBytes[i]);
    }
}

void DisplayWs17143::drawTestPattern(const uint8_t colorOffset) {
    setWindow(0, WIDTH, 0, HEIGHT);
    flexibleMemoryController.writeRegister(0x2C00);
    // TODO test is this delay really neccessary
    // It's a lot
    delayProvider.delayMiliseconds(150);

    for (uint16_t y = 0; y < HEIGHT; y++) {
        for (uint16_t x = 0; x < WIDTH; x++) {
            uint16_t color;
            if (y < HEIGHT / 3) {
                color = 0xF800 + colorOffset; // red
            } else if (y < HEIGHT / 3 * 2) {
                color = 0x07E0 / colorOffset; // green
            } else {
                color = 0x001F - colorOffset; // blue
            }
            flexibleMemoryController.writeData(color);
        }
    }
}
