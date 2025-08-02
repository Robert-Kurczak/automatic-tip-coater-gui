#include "Ws17143Display.hpp"

#include <array>

namespace ATC {

void Ws17143Display::setWindow(const Rectangle& window) {
    const uint8_t xBytes[] {
        uint8_t(window.xStart_ >> 8),
        uint8_t(window.xStart_ & 0xFF),
        uint8_t(window.xEnd_ >> 8),
        uint8_t(window.xEnd_ & 0xFF)
    };
    const uint8_t yBytes[] {
        uint8_t(window.yStart_ >> 8),
        uint8_t(window.yStart_ & 0xFF),
        uint8_t(window.yEnd_ >> 8),
        uint8_t(window.yEnd_ & 0xFF)
    };

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController_.write(0x2A00 + i, xBytes[i]);
    }

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController_.write(0x2B00 + i, yBytes[i]);
    }
}

void Ws17143Display::initResetLcdPin() {
    pinout_.lcdResetPin_.setOutputMode();
}

void Ws17143Display::resetLcd() {
    pinout_.lcdResetPin_.setLow();
    delayProvider_.delayMiliseconds(50);
    pinout_.lcdResetPin_.setHigh();
    delayProvider_.delayMiliseconds(50);
}

void Ws17143Display::initProprietaryHardwareSettings() {
    // Manufacturer Page 1 Commands Enable
    flexibleMemoryController_.write(0xF000, 0x50);
    flexibleMemoryController_.write(0xF001, 0xAA);
    flexibleMemoryController_.write(0xF002, 0x52);
    flexibleMemoryController_.write(0xF003, 0x08);
    flexibleMemoryController_.write(0xF004, 0x01);

    flexibleMemoryController_.write(0xB000, 0x0D);
    flexibleMemoryController_.write(0xB001, 0x0D);
    flexibleMemoryController_.write(0xB002, 0x0D);

    flexibleMemoryController_.write(0xB100, 0x0D);
    flexibleMemoryController_.write(0xB101, 0x0D);
    flexibleMemoryController_.write(0xB102, 0x0D);

    flexibleMemoryController_.write(0xB200, 0x00);
    flexibleMemoryController_.write(0xB201, 0x00);
    flexibleMemoryController_.write(0xB202, 0x00);

    flexibleMemoryController_.write(0xB300, 0x05);
    flexibleMemoryController_.write(0xB301, 0x05);
    flexibleMemoryController_.write(0xB302, 0x05);

    flexibleMemoryController_.write(0xB500, 0x0B);
    flexibleMemoryController_.write(0xB501, 0x0B);
    flexibleMemoryController_.write(0xB502, 0x0B);

    flexibleMemoryController_.write(0xB600, 0x34);
    flexibleMemoryController_.write(0xB601, 0x34);
    flexibleMemoryController_.write(0xB602, 0x34);

    flexibleMemoryController_.write(0xB701, 0x24);
    flexibleMemoryController_.write(0xB701, 0x24);
    flexibleMemoryController_.write(0xB701, 0x24);

    flexibleMemoryController_.write(0xB800, 0x24);
    flexibleMemoryController_.write(0xB801, 0x24);
    flexibleMemoryController_.write(0xB802, 0x24);

    flexibleMemoryController_.write(0xB900, 0x24);
    flexibleMemoryController_.write(0xB901, 0x24);
    flexibleMemoryController_.write(0xB902, 0x24);

    flexibleMemoryController_.write(0xBA00, 0x34);
    flexibleMemoryController_.write(0xBA01, 0x34);
    flexibleMemoryController_.write(0xBA02, 0x34);

    flexibleMemoryController_.write(0xBC00, 0x00);
    flexibleMemoryController_.write(0xBC01, 0xA3);
    flexibleMemoryController_.write(0xBC02, 0x00);

    flexibleMemoryController_.write(0xBD00, 0x00);
    flexibleMemoryController_.write(0xBD01, 0xA3);
    flexibleMemoryController_.write(0xBD02, 0x00);

    flexibleMemoryController_.write(0xBE00, 0x00);
    flexibleMemoryController_.write(0xBE01, 0x63);

    // Manufacturer Page 0 Commands Enable
    flexibleMemoryController_.write(0xF000, 0x55);
    flexibleMemoryController_.write(0xF001, 0xAA);
    flexibleMemoryController_.write(0xF002, 0x52);
    flexibleMemoryController_.write(0xF003, 0x08);
    flexibleMemoryController_.write(0xF004, 0x00);

    flexibleMemoryController_.write(0x3500, 0x00);
    flexibleMemoryController_.write(0x3600, 0x00);

    flexibleMemoryController_.write(0xB000, 0x08);
    flexibleMemoryController_.write(0xB001, 0x05);
    flexibleMemoryController_.write(0xB002, 0x02);
    flexibleMemoryController_.write(0xB003, 0x05);
    flexibleMemoryController_.write(0xB004, 0x02);

    flexibleMemoryController_.write(0xB600, 0x08);
    flexibleMemoryController_.write(0xB500, 0x50); // 480x800

    flexibleMemoryController_.write(0xB700, 0x00);
    flexibleMemoryController_.write(0xB701, 0x00);

    flexibleMemoryController_.write(0xB800, 0x01);
    flexibleMemoryController_.write(0xB801, 0x05);
    flexibleMemoryController_.write(0xB802, 0x05);
    flexibleMemoryController_.write(0xB803, 0x05);

    flexibleMemoryController_.write(0xBA00, 0x01);

    flexibleMemoryController_.write(0xBC00, 0x00);
    flexibleMemoryController_.write(0xBC01, 0x00);
    flexibleMemoryController_.write(0xBC02, 0x00);

    flexibleMemoryController_.write(0xBD00, 0x01);
    flexibleMemoryController_.write(0xBD01, 0x84);
    flexibleMemoryController_.write(0xBD02, 0x07);
    flexibleMemoryController_.write(0xBD03, 0x31);
    flexibleMemoryController_.write(0xBD04, 0x00);

    flexibleMemoryController_.write(0xCC00, 0x03);
    flexibleMemoryController_.write(0xCC01, 0x00);
    flexibleMemoryController_.write(0xCC02, 0x00);

    flexibleMemoryController_.write(0xFF00, 0xAA);
    flexibleMemoryController_.write(0xFF01, 0x55);
    flexibleMemoryController_.write(0xFF02, 0x25);
    flexibleMemoryController_.write(0xFF03, 0x01);
}

void Ws17143Display::initProprietaryGammaSettings() {
    // Red +
    flexibleMemoryController_.write(0xD100, 0x00);
    flexibleMemoryController_.write(0xD101, 0x37);
    flexibleMemoryController_.write(0xD102, 0x00);
    flexibleMemoryController_.write(0xD103, 0x52);
    flexibleMemoryController_.write(0xD104, 0x00);
    flexibleMemoryController_.write(0xD105, 0x7B);
    flexibleMemoryController_.write(0xD106, 0x00);
    flexibleMemoryController_.write(0xD107, 0x99);
    flexibleMemoryController_.write(0xD108, 0x00);
    flexibleMemoryController_.write(0xD109, 0xB1);
    flexibleMemoryController_.write(0xD10A, 0x00);
    flexibleMemoryController_.write(0xD10B, 0xD2);
    flexibleMemoryController_.write(0xD10C, 0x00);
    flexibleMemoryController_.write(0xD10D, 0xF6);
    flexibleMemoryController_.write(0xD10E, 0x01);
    flexibleMemoryController_.write(0xD10F, 0x27);
    flexibleMemoryController_.write(0xD110, 0x01);
    flexibleMemoryController_.write(0xD111, 0x4E);
    flexibleMemoryController_.write(0xD112, 0x01);
    flexibleMemoryController_.write(0xD113, 0x8C);
    flexibleMemoryController_.write(0xD114, 0x01);
    flexibleMemoryController_.write(0xD115, 0xBE);
    flexibleMemoryController_.write(0xD116, 0x02);
    flexibleMemoryController_.write(0xD117, 0x0B);
    flexibleMemoryController_.write(0xD118, 0x02);
    flexibleMemoryController_.write(0xD119, 0x48);
    flexibleMemoryController_.write(0xD11A, 0x02);
    flexibleMemoryController_.write(0xD11B, 0x4A);
    flexibleMemoryController_.write(0xD11C, 0x02);
    flexibleMemoryController_.write(0xD11D, 0x7E);
    flexibleMemoryController_.write(0xD11E, 0x02);
    flexibleMemoryController_.write(0xD11F, 0xBC);
    flexibleMemoryController_.write(0xD120, 0x02);
    flexibleMemoryController_.write(0xD121, 0xE1);
    flexibleMemoryController_.write(0xD122, 0x03);
    flexibleMemoryController_.write(0xD123, 0x10);
    flexibleMemoryController_.write(0xD124, 0x03);
    flexibleMemoryController_.write(0xD125, 0x31);
    flexibleMemoryController_.write(0xD126, 0x03);
    flexibleMemoryController_.write(0xD127, 0x5A);
    flexibleMemoryController_.write(0xD128, 0x03);
    flexibleMemoryController_.write(0xD129, 0x73);
    flexibleMemoryController_.write(0xD12A, 0x03);
    flexibleMemoryController_.write(0xD12B, 0x94);
    flexibleMemoryController_.write(0xD12C, 0x03);
    flexibleMemoryController_.write(0xD12D, 0x9F);
    flexibleMemoryController_.write(0xD12E, 0x03);
    flexibleMemoryController_.write(0xD12F, 0xB3);
    flexibleMemoryController_.write(0xD130, 0x03);
    flexibleMemoryController_.write(0xD131, 0xB9);
    flexibleMemoryController_.write(0xD132, 0x03);
    flexibleMemoryController_.write(0xD133, 0xC1);
    // Green +
    flexibleMemoryController_.write(0xD200, 0x00);
    flexibleMemoryController_.write(0xD201, 0x37);
    flexibleMemoryController_.write(0xD202, 0x00);
    flexibleMemoryController_.write(0xD203, 0x52);
    flexibleMemoryController_.write(0xD204, 0x00);
    flexibleMemoryController_.write(0xD205, 0x7B);
    flexibleMemoryController_.write(0xD206, 0x00);
    flexibleMemoryController_.write(0xD207, 0x99);
    flexibleMemoryController_.write(0xD208, 0x00);
    flexibleMemoryController_.write(0xD209, 0xB1);
    flexibleMemoryController_.write(0xD20A, 0x00);
    flexibleMemoryController_.write(0xD20B, 0xD2);
    flexibleMemoryController_.write(0xD20C, 0x00);
    flexibleMemoryController_.write(0xD20D, 0xF6);
    flexibleMemoryController_.write(0xD20E, 0x01);
    flexibleMemoryController_.write(0xD20F, 0x27);
    flexibleMemoryController_.write(0xD210, 0x01);
    flexibleMemoryController_.write(0xD211, 0x4E);
    flexibleMemoryController_.write(0xD212, 0x01);
    flexibleMemoryController_.write(0xD213, 0x8C);
    flexibleMemoryController_.write(0xD214, 0x01);
    flexibleMemoryController_.write(0xD215, 0xBE);
    flexibleMemoryController_.write(0xD216, 0x02);
    flexibleMemoryController_.write(0xD217, 0x0B);
    flexibleMemoryController_.write(0xD218, 0x02);
    flexibleMemoryController_.write(0xD219, 0x48);
    flexibleMemoryController_.write(0xD21A, 0x02);
    flexibleMemoryController_.write(0xD21B, 0x4A);
    flexibleMemoryController_.write(0xD21C, 0x02);
    flexibleMemoryController_.write(0xD21D, 0x7E);
    flexibleMemoryController_.write(0xD21E, 0x02);
    flexibleMemoryController_.write(0xD21F, 0xBC);
    flexibleMemoryController_.write(0xD220, 0x02);
    flexibleMemoryController_.write(0xD221, 0xE1);
    flexibleMemoryController_.write(0xD222, 0x03);
    flexibleMemoryController_.write(0xD223, 0x10);
    flexibleMemoryController_.write(0xD224, 0x03);
    flexibleMemoryController_.write(0xD225, 0x31);
    flexibleMemoryController_.write(0xD226, 0x03);
    flexibleMemoryController_.write(0xD227, 0x5A);
    flexibleMemoryController_.write(0xD228, 0x03);
    flexibleMemoryController_.write(0xD229, 0x73);
    flexibleMemoryController_.write(0xD22A, 0x03);
    flexibleMemoryController_.write(0xD22B, 0x94);
    flexibleMemoryController_.write(0xD22C, 0x03);
    flexibleMemoryController_.write(0xD22D, 0x9F);
    flexibleMemoryController_.write(0xD22E, 0x03);
    flexibleMemoryController_.write(0xD22F, 0xB3);
    flexibleMemoryController_.write(0xD230, 0x03);
    flexibleMemoryController_.write(0xD231, 0xB9);
    flexibleMemoryController_.write(0xD232, 0x03);
    flexibleMemoryController_.write(0xD233, 0xC1);
    // Blue +
    flexibleMemoryController_.write(0xD300, 0x00);
    flexibleMemoryController_.write(0xD301, 0x37);
    flexibleMemoryController_.write(0xD302, 0x00);
    flexibleMemoryController_.write(0xD303, 0x52);
    flexibleMemoryController_.write(0xD304, 0x00);
    flexibleMemoryController_.write(0xD305, 0x7B);
    flexibleMemoryController_.write(0xD306, 0x00);
    flexibleMemoryController_.write(0xD307, 0x99);
    flexibleMemoryController_.write(0xD308, 0x00);
    flexibleMemoryController_.write(0xD309, 0xB1);
    flexibleMemoryController_.write(0xD30A, 0x00);
    flexibleMemoryController_.write(0xD30B, 0xD2);
    flexibleMemoryController_.write(0xD30C, 0x00);
    flexibleMemoryController_.write(0xD30D, 0xF6);
    flexibleMemoryController_.write(0xD30E, 0x01);
    flexibleMemoryController_.write(0xD30F, 0x27);
    flexibleMemoryController_.write(0xD311, 0x4E);
    flexibleMemoryController_.write(0xD312, 0x01);
    flexibleMemoryController_.write(0xD313, 0x8C);
    flexibleMemoryController_.write(0xD314, 0x01);
    flexibleMemoryController_.write(0xD315, 0xBE);
    flexibleMemoryController_.write(0xD316, 0x02);
    flexibleMemoryController_.write(0xD317, 0x0B);
    flexibleMemoryController_.write(0xD318, 0x02);
    flexibleMemoryController_.write(0xD319, 0x48);
    flexibleMemoryController_.write(0xD31A, 0x02);
    flexibleMemoryController_.write(0xD31B, 0x4A);
    flexibleMemoryController_.write(0xD31C, 0x02);
    flexibleMemoryController_.write(0xD31D, 0x7E);
    flexibleMemoryController_.write(0xD31E, 0x02);
    flexibleMemoryController_.write(0xD31F, 0xBC);
    flexibleMemoryController_.write(0xD320, 0x02);
    flexibleMemoryController_.write(0xD321, 0xE1);
    flexibleMemoryController_.write(0xD322, 0x03);
    flexibleMemoryController_.write(0xD323, 0x10);
    flexibleMemoryController_.write(0xD324, 0x03);
    flexibleMemoryController_.write(0xD325, 0x31);
    flexibleMemoryController_.write(0xD326, 0x03);
    flexibleMemoryController_.write(0xD327, 0x5A);
    flexibleMemoryController_.write(0xD328, 0x03);
    flexibleMemoryController_.write(0xD329, 0x73);
    flexibleMemoryController_.write(0xD32A, 0x03);
    flexibleMemoryController_.write(0xD32B, 0x94);
    flexibleMemoryController_.write(0xD32C, 0x03);
    flexibleMemoryController_.write(0xD32D, 0x9F);
    flexibleMemoryController_.write(0xD32E, 0x03);
    flexibleMemoryController_.write(0xD32F, 0xB3);
    flexibleMemoryController_.write(0xD330, 0x03);
    flexibleMemoryController_.write(0xD331, 0xB9);
    flexibleMemoryController_.write(0xD332, 0x03);
    flexibleMemoryController_.write(0xD333, 0xC1);
    // Red -
    flexibleMemoryController_.write(0xD400, 0x00);
    flexibleMemoryController_.write(0xD401, 0x37);
    flexibleMemoryController_.write(0xD402, 0x00);
    flexibleMemoryController_.write(0xD403, 0x52);
    flexibleMemoryController_.write(0xD404, 0x00);
    flexibleMemoryController_.write(0xD405, 0x7B);
    flexibleMemoryController_.write(0xD406, 0x00);
    flexibleMemoryController_.write(0xD407, 0x99);
    flexibleMemoryController_.write(0xD408, 0x00);
    flexibleMemoryController_.write(0xD409, 0xB1);
    flexibleMemoryController_.write(0xD40A, 0x00);
    flexibleMemoryController_.write(0xD40B, 0xD2);
    flexibleMemoryController_.write(0xD40C, 0x00);
    flexibleMemoryController_.write(0xD40D, 0xF6);
    flexibleMemoryController_.write(0xD40E, 0x01);
    flexibleMemoryController_.write(0xD40F, 0x27);
    flexibleMemoryController_.write(0xD410, 0x01);
    flexibleMemoryController_.write(0xD411, 0x4E);
    flexibleMemoryController_.write(0xD412, 0x01);
    flexibleMemoryController_.write(0xD413, 0x8C);
    flexibleMemoryController_.write(0xD414, 0x01);
    flexibleMemoryController_.write(0xD415, 0xBE);
    flexibleMemoryController_.write(0xD416, 0x02);
    flexibleMemoryController_.write(0xD417, 0x0B);
    flexibleMemoryController_.write(0xD418, 0x02);
    flexibleMemoryController_.write(0xD419, 0x48);
    flexibleMemoryController_.write(0xD41A, 0x02);
    flexibleMemoryController_.write(0xD41B, 0x4A);
    flexibleMemoryController_.write(0xD41C, 0x02);
    flexibleMemoryController_.write(0xD41D, 0x7E);
    flexibleMemoryController_.write(0xD41E, 0x02);
    flexibleMemoryController_.write(0xD41F, 0xBC);
    flexibleMemoryController_.write(0xD420, 0x02);
    flexibleMemoryController_.write(0xD421, 0xE1);
    flexibleMemoryController_.write(0xD422, 0x03);
    flexibleMemoryController_.write(0xD423, 0x10);
    flexibleMemoryController_.write(0xD424, 0x03);
    flexibleMemoryController_.write(0xD425, 0x31);
    flexibleMemoryController_.write(0xD426, 0x03);
    flexibleMemoryController_.write(0xD427, 0x5A);
    flexibleMemoryController_.write(0xD428, 0x03);
    flexibleMemoryController_.write(0xD429, 0x73);
    flexibleMemoryController_.write(0xD42A, 0x03);
    flexibleMemoryController_.write(0xD42B, 0x94);
    flexibleMemoryController_.write(0xD42C, 0x03);
    flexibleMemoryController_.write(0xD42D, 0x9F);
    flexibleMemoryController_.write(0xD42E, 0x03);
    flexibleMemoryController_.write(0xD42F, 0xB3);
    flexibleMemoryController_.write(0xD430, 0x03);
    flexibleMemoryController_.write(0xD431, 0xB9);
    flexibleMemoryController_.write(0xD432, 0x03);
    flexibleMemoryController_.write(0xD433, 0xC1);
    // Green -
    flexibleMemoryController_.write(0xD500, 0x00);
    flexibleMemoryController_.write(0xD501, 0x37);
    flexibleMemoryController_.write(0xD502, 0x00);
    flexibleMemoryController_.write(0xD503, 0x52);
    flexibleMemoryController_.write(0xD504, 0x00);
    flexibleMemoryController_.write(0xD505, 0x7B);
    flexibleMemoryController_.write(0xD506, 0x00);
    flexibleMemoryController_.write(0xD507, 0x99);
    flexibleMemoryController_.write(0xD508, 0x00);
    flexibleMemoryController_.write(0xD509, 0xB1);
    flexibleMemoryController_.write(0xD50A, 0x00);
    flexibleMemoryController_.write(0xD50B, 0xD2);
    flexibleMemoryController_.write(0xD50C, 0x00);
    flexibleMemoryController_.write(0xD50D, 0xF6);
    flexibleMemoryController_.write(0xD50E, 0x01);
    flexibleMemoryController_.write(0xD50F, 0x27);
    flexibleMemoryController_.write(0xD510, 0x01);
    flexibleMemoryController_.write(0xD511, 0x4E);
    flexibleMemoryController_.write(0xD512, 0x01);
    flexibleMemoryController_.write(0xD513, 0x8C);
    flexibleMemoryController_.write(0xD514, 0x01);
    flexibleMemoryController_.write(0xD515, 0xBE);
    flexibleMemoryController_.write(0xD516, 0x02);
    flexibleMemoryController_.write(0xD517, 0x0B);
    flexibleMemoryController_.write(0xD518, 0x02);
    flexibleMemoryController_.write(0xD519, 0x48);
    flexibleMemoryController_.write(0xD51A, 0x02);
    flexibleMemoryController_.write(0xD51B, 0x4A);
    flexibleMemoryController_.write(0xD51C, 0x02);
    flexibleMemoryController_.write(0xD51D, 0x7E);
    flexibleMemoryController_.write(0xD51E, 0x02);
    flexibleMemoryController_.write(0xD51F, 0xBC);
    flexibleMemoryController_.write(0xD520, 0x02);
    flexibleMemoryController_.write(0xD521, 0xE1);
    flexibleMemoryController_.write(0xD522, 0x03);
    flexibleMemoryController_.write(0xD523, 0x10);
    flexibleMemoryController_.write(0xD524, 0x03);
    flexibleMemoryController_.write(0xD525, 0x31);
    flexibleMemoryController_.write(0xD526, 0x03);
    flexibleMemoryController_.write(0xD527, 0x5A);
    flexibleMemoryController_.write(0xD528, 0x03);
    flexibleMemoryController_.write(0xD529, 0x73);
    flexibleMemoryController_.write(0xD52A, 0x03);
    flexibleMemoryController_.write(0xD52B, 0x94);
    flexibleMemoryController_.write(0xD52C, 0x03);
    flexibleMemoryController_.write(0xD52D, 0x9F);
    flexibleMemoryController_.write(0xD52E, 0x03);
    flexibleMemoryController_.write(0xD52F, 0xB3);
    flexibleMemoryController_.write(0xD530, 0x03);
    flexibleMemoryController_.write(0xD531, 0xB9);
    flexibleMemoryController_.write(0xD532, 0x03);
    flexibleMemoryController_.write(0xD533, 0xC1);
    // Blue -
    flexibleMemoryController_.write(0xD600, 0x00);
    flexibleMemoryController_.write(0xD601, 0x37);
    flexibleMemoryController_.write(0xD602, 0x00);
    flexibleMemoryController_.write(0xD603, 0x52);
    flexibleMemoryController_.write(0xD604, 0x00);
    flexibleMemoryController_.write(0xD605, 0x7B);
    flexibleMemoryController_.write(0xD606, 0x00);
    flexibleMemoryController_.write(0xD607, 0x99);
    flexibleMemoryController_.write(0xD608, 0x00);
    flexibleMemoryController_.write(0xD609, 0xB1);
    flexibleMemoryController_.write(0xD60A, 0x00);
    flexibleMemoryController_.write(0xD60B, 0xD2);
    flexibleMemoryController_.write(0xD60C, 0x00);
    flexibleMemoryController_.write(0xD60D, 0xF6);
    flexibleMemoryController_.write(0xD60E, 0x01);
    flexibleMemoryController_.write(0xD60F, 0x27);
    flexibleMemoryController_.write(0xD610, 0x01);
    flexibleMemoryController_.write(0xD611, 0x4E);
    flexibleMemoryController_.write(0xD612, 0x01);
    flexibleMemoryController_.write(0xD613, 0x8C);
    flexibleMemoryController_.write(0xD614, 0x01);
    flexibleMemoryController_.write(0xD615, 0xBE);
    flexibleMemoryController_.write(0xD616, 0x02);
    flexibleMemoryController_.write(0xD617, 0x0B);
    flexibleMemoryController_.write(0xD618, 0x02);
    flexibleMemoryController_.write(0xD619, 0x48);
    flexibleMemoryController_.write(0xD61A, 0x02);
    flexibleMemoryController_.write(0xD61B, 0x4A);
    flexibleMemoryController_.write(0xD61C, 0x02);
    flexibleMemoryController_.write(0xD61D, 0x7E);
    flexibleMemoryController_.write(0xD61E, 0x02);
    flexibleMemoryController_.write(0xD61F, 0xBC);
    flexibleMemoryController_.write(0xD620, 0x02);
    flexibleMemoryController_.write(0xD621, 0xE1);
    flexibleMemoryController_.write(0xD622, 0x03);
    flexibleMemoryController_.write(0xD623, 0x10);
    flexibleMemoryController_.write(0xD624, 0x03);
    flexibleMemoryController_.write(0xD625, 0x31);
    flexibleMemoryController_.write(0xD626, 0x03);
    flexibleMemoryController_.write(0xD627, 0x5A);
    flexibleMemoryController_.write(0xD628, 0x03);
    flexibleMemoryController_.write(0xD629, 0x73);
    flexibleMemoryController_.write(0xD62A, 0x03);
    flexibleMemoryController_.write(0xD62B, 0x94);
    flexibleMemoryController_.write(0xD62C, 0x03);
    flexibleMemoryController_.write(0xD62D, 0x9F);
    flexibleMemoryController_.write(0xD62E, 0x03);
    flexibleMemoryController_.write(0xD62F, 0xB3);
    flexibleMemoryController_.write(0xD630, 0x03);
    flexibleMemoryController_.write(0xD631, 0xB9);
    flexibleMemoryController_.write(0xD632, 0x03);
    flexibleMemoryController_.write(0xD633, 0xC1);
}

void Ws17143Display::initRGB565Format() {
    flexibleMemoryController_.write(0x3A00, 0x55);
}

void Ws17143Display::exitSleepState() {
    flexibleMemoryController_.write(0x1100, 0x00);
    delayProvider_.delayMiliseconds(120);
}

void Ws17143Display::enableDisplay() {
    flexibleMemoryController_.write(0x2900, 0x00);
    delayProvider_.delayMiliseconds(10);
}

void Ws17143Display::setAllPixelsOff() {
    flexibleMemoryController_.write(0x2200, 0x00);
}

void Ws17143Display::displayFramebuffer() {
    flexibleMemoryController_.write(0x1300, 0x00);
}

Ws17143Display::Ws17143Display(
    const Ws17143DisplayPinout& pinout,
    FlexibleMemoryController& flexibleMemoryController,
    IDelayProvider& delayProvider
) :
    pinout_(pinout),
    flexibleMemoryController_(flexibleMemoryController),
    delayProvider_(delayProvider) {}

void Ws17143Display::init() {
    initResetLcdPin();
    resetLcd();

    initProprietaryHardwareSettings();
    initProprietaryGammaSettings();
    initRGB565Format();
    exitSleepState();
    enableDisplay();
    setAllPixelsOff();
}

void Ws17143Display::drawTestPattern(const uint8_t colorOffset) {
    setWindow(
        Rectangle {
            .xStart_ = 0,
            .xEnd_ = WIDTH_ - 1,
            .yStart_ = 0,
            .yEnd_ = HEIGHT_ - 1
        }
    );

    flexibleMemoryController_.writeRegister(0x2C00);

    for (uint16_t y = 0; y < HEIGHT_; y++) {
        for (uint16_t x = 0; x < WIDTH_; x++) {
            uint16_t color;
            if (y < HEIGHT_ / 3) {
                color = 0xF800 + colorOffset; // red
            } else if (y < HEIGHT_ / 3 * 2) {
                color = 0x07E0 / colorOffset; // green
            } else {
                color = 0x001F - colorOffset; // blue
            }
            flexibleMemoryController_.writeData(color);
        }
    }
}

void Ws17143Display::draw(
    const std::span<const uint16_t>& frameBuffer,
    const Rectangle& window
) {
    setWindow(window);

    flexibleMemoryController_.writeRegister(0x2C00);

    for (uint16_t y = window.yStart_; y <= window.yEnd_; y++) {
        for (uint16_t x = window.xStart_; x <= window.xEnd_; x++) {
            const uint16_t color = frameBuffer[y * WIDTH_ + x];
            flexibleMemoryController_.writeData(color);
        }
    }

    displayFramebuffer();
}

void Ws17143Display::draw(const std::span<const uint16_t>& framebuffer) {
    const Rectangle fullWindow {
        .xStart_ = 0,
        .xEnd_ = WIDTH_ - 1,
        .yStart_ = 0,
        .yEnd_ = HEIGHT_ - 1
    };

    draw(framebuffer, fullWindow);
}
}