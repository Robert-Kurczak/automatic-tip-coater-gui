#include "Ws17143Display.hpp"

namespace ATC {
using RegisterNumber = IFlexibleMemoryController::RegisterNumber;
using Data = IFlexibleMemoryController::Data;

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
        flexibleMemoryController_.write(
            RegisterNumber {uint16_t(0x2A00 + i)}, Data {xBytes[i]}
        );
    }

    for (uint8_t i = 0; i < 4; i++) {
        flexibleMemoryController_.write(
            RegisterNumber {uint16_t(0x2B00 + i)}, Data {yBytes[i]}
        );
    }
}

void Ws17143Display::initResetLcdPin() {
    pinout_.lcdResetPin_.setOutputMode();
}

void Ws17143Display::resetLcd() {
    pinout_.lcdResetPin_.setLow();
    systemClock_.delayMiliseconds(50);
    pinout_.lcdResetPin_.setHigh();
    systemClock_.delayMiliseconds(50);
}

void Ws17143Display::initProprietaryHardwareSettings() {
    flexibleMemoryController_.write(RegisterNumber {0xF000}, Data {0x50});

    // Manufacturer Page 1 Commands Enable
    flexibleMemoryController_.write(RegisterNumber {0xF000}, Data {0x50});
    flexibleMemoryController_.write(RegisterNumber {0xF001}, Data {0xAA});
    flexibleMemoryController_.write(RegisterNumber {0xF002}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xF003}, Data {0x08});
    flexibleMemoryController_.write(RegisterNumber {0xF004}, Data {0x01});

    flexibleMemoryController_.write(RegisterNumber {0xB000}, Data {0x0D});
    flexibleMemoryController_.write(RegisterNumber {0xB001}, Data {0x0D});
    flexibleMemoryController_.write(RegisterNumber {0xB002}, Data {0x0D});

    flexibleMemoryController_.write(RegisterNumber {0xB100}, Data {0x0D});
    flexibleMemoryController_.write(RegisterNumber {0xB101}, Data {0x0D});
    flexibleMemoryController_.write(RegisterNumber {0xB102}, Data {0x0D});

    flexibleMemoryController_.write(RegisterNumber {0xB200}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xB201}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xB202}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xB300}, Data {0x05});
    flexibleMemoryController_.write(RegisterNumber {0xB301}, Data {0x05});
    flexibleMemoryController_.write(RegisterNumber {0xB302}, Data {0x05});

    flexibleMemoryController_.write(RegisterNumber {0xB500}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xB501}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xB502}, Data {0x0B});

    flexibleMemoryController_.write(RegisterNumber {0xB600}, Data {0x34});
    flexibleMemoryController_.write(RegisterNumber {0xB601}, Data {0x34});
    flexibleMemoryController_.write(RegisterNumber {0xB602}, Data {0x34});

    flexibleMemoryController_.write(RegisterNumber {0xB701}, Data {0x24});
    flexibleMemoryController_.write(RegisterNumber {0xB701}, Data {0x24});
    flexibleMemoryController_.write(RegisterNumber {0xB701}, Data {0x24});

    flexibleMemoryController_.write(RegisterNumber {0xB800}, Data {0x24});
    flexibleMemoryController_.write(RegisterNumber {0xB801}, Data {0x24});
    flexibleMemoryController_.write(RegisterNumber {0xB802}, Data {0x24});

    flexibleMemoryController_.write(RegisterNumber {0xB900}, Data {0x24});
    flexibleMemoryController_.write(RegisterNumber {0xB901}, Data {0x24});
    flexibleMemoryController_.write(RegisterNumber {0xB902}, Data {0x24});

    flexibleMemoryController_.write(RegisterNumber {0xBA00}, Data {0x34});
    flexibleMemoryController_.write(RegisterNumber {0xBA01}, Data {0x34});
    flexibleMemoryController_.write(RegisterNumber {0xBA02}, Data {0x34});

    flexibleMemoryController_.write(RegisterNumber {0xBC00}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xBC01}, Data {0xA3});
    flexibleMemoryController_.write(RegisterNumber {0xBC02}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xBD00}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xBD01}, Data {0xA3});
    flexibleMemoryController_.write(RegisterNumber {0xBD02}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xBE00}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xBE01}, Data {0x63});

    // Manufacturer Page 0 Commands Enable
    flexibleMemoryController_.write(RegisterNumber {0xF000}, Data {0x55});
    flexibleMemoryController_.write(RegisterNumber {0xF001}, Data {0xAA});
    flexibleMemoryController_.write(RegisterNumber {0xF002}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xF003}, Data {0x08});
    flexibleMemoryController_.write(RegisterNumber {0xF004}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0x3500}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0x3600}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xB000}, Data {0x08});
    flexibleMemoryController_.write(RegisterNumber {0xB001}, Data {0x05});
    flexibleMemoryController_.write(RegisterNumber {0xB002}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xB003}, Data {0x05});
    flexibleMemoryController_.write(RegisterNumber {0xB004}, Data {0x02});

    flexibleMemoryController_.write(RegisterNumber {0xB600}, Data {0x08});
    flexibleMemoryController_.write(
        RegisterNumber {0xB500}, Data {0x50}
    ); // 480x800

    flexibleMemoryController_.write(RegisterNumber {0xB700}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xB701}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xB800}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xB801}, Data {0x05});
    flexibleMemoryController_.write(RegisterNumber {0xB802}, Data {0x05});
    flexibleMemoryController_.write(RegisterNumber {0xB803}, Data {0x05});

    flexibleMemoryController_.write(RegisterNumber {0xBA00}, Data {0x01});

    flexibleMemoryController_.write(RegisterNumber {0xBC00}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xBC01}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xBC02}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xBD00}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xBD01}, Data {0x84});
    flexibleMemoryController_.write(RegisterNumber {0xBD02}, Data {0x07});
    flexibleMemoryController_.write(RegisterNumber {0xBD03}, Data {0x31});
    flexibleMemoryController_.write(RegisterNumber {0xBD04}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xCC00}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xCC01}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xCC02}, Data {0x00});

    flexibleMemoryController_.write(RegisterNumber {0xFF00}, Data {0xAA});
    flexibleMemoryController_.write(RegisterNumber {0xFF01}, Data {0x55});
    flexibleMemoryController_.write(RegisterNumber {0xFF02}, Data {0x25});
    flexibleMemoryController_.write(RegisterNumber {0xFF03}, Data {0x01});
}

void Ws17143Display::initProprietaryGammaSettings() {
    // Red +
    flexibleMemoryController_.write(RegisterNumber {0xD100}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD101}, Data {0x37});
    flexibleMemoryController_.write(RegisterNumber {0xD102}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD103}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xD104}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD105}, Data {0x7B});
    flexibleMemoryController_.write(RegisterNumber {0xD106}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD107}, Data {0x99});
    flexibleMemoryController_.write(RegisterNumber {0xD108}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD109}, Data {0xB1});
    flexibleMemoryController_.write(RegisterNumber {0xD10A}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD10B}, Data {0xD2});
    flexibleMemoryController_.write(RegisterNumber {0xD10C}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD10D}, Data {0xF6});
    flexibleMemoryController_.write(RegisterNumber {0xD10E}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD10F}, Data {0x27});
    flexibleMemoryController_.write(RegisterNumber {0xD110}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD111}, Data {0x4E});
    flexibleMemoryController_.write(RegisterNumber {0xD112}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD113}, Data {0x8C});
    flexibleMemoryController_.write(RegisterNumber {0xD114}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD115}, Data {0xBE});
    flexibleMemoryController_.write(RegisterNumber {0xD116}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD117}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xD118}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD119}, Data {0x48});
    flexibleMemoryController_.write(RegisterNumber {0xD11A}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD11B}, Data {0x4A});
    flexibleMemoryController_.write(RegisterNumber {0xD11C}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD11D}, Data {0x7E});
    flexibleMemoryController_.write(RegisterNumber {0xD11E}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD11F}, Data {0xBC});
    flexibleMemoryController_.write(RegisterNumber {0xD120}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD121}, Data {0xE1});
    flexibleMemoryController_.write(RegisterNumber {0xD122}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD123}, Data {0x10});
    flexibleMemoryController_.write(RegisterNumber {0xD124}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD125}, Data {0x31});
    flexibleMemoryController_.write(RegisterNumber {0xD126}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD127}, Data {0x5A});
    flexibleMemoryController_.write(RegisterNumber {0xD128}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD129}, Data {0x73});
    flexibleMemoryController_.write(RegisterNumber {0xD12A}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD12B}, Data {0x94});
    flexibleMemoryController_.write(RegisterNumber {0xD12C}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD12D}, Data {0x9F});
    flexibleMemoryController_.write(RegisterNumber {0xD12E}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD12F}, Data {0xB3});
    flexibleMemoryController_.write(RegisterNumber {0xD130}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD131}, Data {0xB9});
    flexibleMemoryController_.write(RegisterNumber {0xD132}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD133}, Data {0xC1});
    // Green +
    flexibleMemoryController_.write(RegisterNumber {0xD200}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD201}, Data {0x37});
    flexibleMemoryController_.write(RegisterNumber {0xD202}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD203}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xD204}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD205}, Data {0x7B});
    flexibleMemoryController_.write(RegisterNumber {0xD206}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD207}, Data {0x99});
    flexibleMemoryController_.write(RegisterNumber {0xD208}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD209}, Data {0xB1});
    flexibleMemoryController_.write(RegisterNumber {0xD20A}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD20B}, Data {0xD2});
    flexibleMemoryController_.write(RegisterNumber {0xD20C}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD20D}, Data {0xF6});
    flexibleMemoryController_.write(RegisterNumber {0xD20E}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD20F}, Data {0x27});
    flexibleMemoryController_.write(RegisterNumber {0xD210}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD211}, Data {0x4E});
    flexibleMemoryController_.write(RegisterNumber {0xD212}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD213}, Data {0x8C});
    flexibleMemoryController_.write(RegisterNumber {0xD214}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD215}, Data {0xBE});
    flexibleMemoryController_.write(RegisterNumber {0xD216}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD217}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xD218}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD219}, Data {0x48});
    flexibleMemoryController_.write(RegisterNumber {0xD21A}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD21B}, Data {0x4A});
    flexibleMemoryController_.write(RegisterNumber {0xD21C}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD21D}, Data {0x7E});
    flexibleMemoryController_.write(RegisterNumber {0xD21E}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD21F}, Data {0xBC});
    flexibleMemoryController_.write(RegisterNumber {0xD220}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD221}, Data {0xE1});
    flexibleMemoryController_.write(RegisterNumber {0xD222}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD223}, Data {0x10});
    flexibleMemoryController_.write(RegisterNumber {0xD224}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD225}, Data {0x31});
    flexibleMemoryController_.write(RegisterNumber {0xD226}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD227}, Data {0x5A});
    flexibleMemoryController_.write(RegisterNumber {0xD228}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD229}, Data {0x73});
    flexibleMemoryController_.write(RegisterNumber {0xD22A}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD22B}, Data {0x94});
    flexibleMemoryController_.write(RegisterNumber {0xD22C}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD22D}, Data {0x9F});
    flexibleMemoryController_.write(RegisterNumber {0xD22E}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD22F}, Data {0xB3});
    flexibleMemoryController_.write(RegisterNumber {0xD230}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD231}, Data {0xB9});
    flexibleMemoryController_.write(RegisterNumber {0xD232}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD233}, Data {0xC1});
    // Blue +
    flexibleMemoryController_.write(RegisterNumber {0xD300}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD301}, Data {0x37});
    flexibleMemoryController_.write(RegisterNumber {0xD302}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD303}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xD304}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD305}, Data {0x7B});
    flexibleMemoryController_.write(RegisterNumber {0xD306}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD307}, Data {0x99});
    flexibleMemoryController_.write(RegisterNumber {0xD308}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD309}, Data {0xB1});
    flexibleMemoryController_.write(RegisterNumber {0xD30A}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD30B}, Data {0xD2});
    flexibleMemoryController_.write(RegisterNumber {0xD30C}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD30D}, Data {0xF6});
    flexibleMemoryController_.write(RegisterNumber {0xD30E}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD30F}, Data {0x27});
    flexibleMemoryController_.write(RegisterNumber {0xD311}, Data {0x4E});
    flexibleMemoryController_.write(RegisterNumber {0xD312}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD313}, Data {0x8C});
    flexibleMemoryController_.write(RegisterNumber {0xD314}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD315}, Data {0xBE});
    flexibleMemoryController_.write(RegisterNumber {0xD316}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD317}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xD318}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD319}, Data {0x48});
    flexibleMemoryController_.write(RegisterNumber {0xD31A}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD31B}, Data {0x4A});
    flexibleMemoryController_.write(RegisterNumber {0xD31C}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD31D}, Data {0x7E});
    flexibleMemoryController_.write(RegisterNumber {0xD31E}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD31F}, Data {0xBC});
    flexibleMemoryController_.write(RegisterNumber {0xD320}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD321}, Data {0xE1});
    flexibleMemoryController_.write(RegisterNumber {0xD322}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD323}, Data {0x10});
    flexibleMemoryController_.write(RegisterNumber {0xD324}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD325}, Data {0x31});
    flexibleMemoryController_.write(RegisterNumber {0xD326}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD327}, Data {0x5A});
    flexibleMemoryController_.write(RegisterNumber {0xD328}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD329}, Data {0x73});
    flexibleMemoryController_.write(RegisterNumber {0xD32A}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD32B}, Data {0x94});
    flexibleMemoryController_.write(RegisterNumber {0xD32C}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD32D}, Data {0x9F});
    flexibleMemoryController_.write(RegisterNumber {0xD32E}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD32F}, Data {0xB3});
    flexibleMemoryController_.write(RegisterNumber {0xD330}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD331}, Data {0xB9});
    flexibleMemoryController_.write(RegisterNumber {0xD332}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD333}, Data {0xC1});
    // Red -
    flexibleMemoryController_.write(RegisterNumber {0xD400}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD401}, Data {0x37});
    flexibleMemoryController_.write(RegisterNumber {0xD402}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD403}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xD404}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD405}, Data {0x7B});
    flexibleMemoryController_.write(RegisterNumber {0xD406}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD407}, Data {0x99});
    flexibleMemoryController_.write(RegisterNumber {0xD408}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD409}, Data {0xB1});
    flexibleMemoryController_.write(RegisterNumber {0xD40A}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD40B}, Data {0xD2});
    flexibleMemoryController_.write(RegisterNumber {0xD40C}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD40D}, Data {0xF6});
    flexibleMemoryController_.write(RegisterNumber {0xD40E}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD40F}, Data {0x27});
    flexibleMemoryController_.write(RegisterNumber {0xD410}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD411}, Data {0x4E});
    flexibleMemoryController_.write(RegisterNumber {0xD412}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD413}, Data {0x8C});
    flexibleMemoryController_.write(RegisterNumber {0xD414}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD415}, Data {0xBE});
    flexibleMemoryController_.write(RegisterNumber {0xD416}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD417}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xD418}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD419}, Data {0x48});
    flexibleMemoryController_.write(RegisterNumber {0xD41A}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD41B}, Data {0x4A});
    flexibleMemoryController_.write(RegisterNumber {0xD41C}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD41D}, Data {0x7E});
    flexibleMemoryController_.write(RegisterNumber {0xD41E}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD41F}, Data {0xBC});
    flexibleMemoryController_.write(RegisterNumber {0xD420}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD421}, Data {0xE1});
    flexibleMemoryController_.write(RegisterNumber {0xD422}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD423}, Data {0x10});
    flexibleMemoryController_.write(RegisterNumber {0xD424}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD425}, Data {0x31});
    flexibleMemoryController_.write(RegisterNumber {0xD426}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD427}, Data {0x5A});
    flexibleMemoryController_.write(RegisterNumber {0xD428}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD429}, Data {0x73});
    flexibleMemoryController_.write(RegisterNumber {0xD42A}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD42B}, Data {0x94});
    flexibleMemoryController_.write(RegisterNumber {0xD42C}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD42D}, Data {0x9F});
    flexibleMemoryController_.write(RegisterNumber {0xD42E}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD42F}, Data {0xB3});
    flexibleMemoryController_.write(RegisterNumber {0xD430}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD431}, Data {0xB9});
    flexibleMemoryController_.write(RegisterNumber {0xD432}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD433}, Data {0xC1});
    // Green -
    flexibleMemoryController_.write(RegisterNumber {0xD500}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD501}, Data {0x37});
    flexibleMemoryController_.write(RegisterNumber {0xD502}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD503}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xD504}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD505}, Data {0x7B});
    flexibleMemoryController_.write(RegisterNumber {0xD506}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD507}, Data {0x99});
    flexibleMemoryController_.write(RegisterNumber {0xD508}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD509}, Data {0xB1});
    flexibleMemoryController_.write(RegisterNumber {0xD50A}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD50B}, Data {0xD2});
    flexibleMemoryController_.write(RegisterNumber {0xD50C}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD50D}, Data {0xF6});
    flexibleMemoryController_.write(RegisterNumber {0xD50E}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD50F}, Data {0x27});
    flexibleMemoryController_.write(RegisterNumber {0xD510}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD511}, Data {0x4E});
    flexibleMemoryController_.write(RegisterNumber {0xD512}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD513}, Data {0x8C});
    flexibleMemoryController_.write(RegisterNumber {0xD514}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD515}, Data {0xBE});
    flexibleMemoryController_.write(RegisterNumber {0xD516}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD517}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xD518}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD519}, Data {0x48});
    flexibleMemoryController_.write(RegisterNumber {0xD51A}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD51B}, Data {0x4A});
    flexibleMemoryController_.write(RegisterNumber {0xD51C}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD51D}, Data {0x7E});
    flexibleMemoryController_.write(RegisterNumber {0xD51E}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD51F}, Data {0xBC});
    flexibleMemoryController_.write(RegisterNumber {0xD520}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD521}, Data {0xE1});
    flexibleMemoryController_.write(RegisterNumber {0xD522}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD523}, Data {0x10});
    flexibleMemoryController_.write(RegisterNumber {0xD524}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD525}, Data {0x31});
    flexibleMemoryController_.write(RegisterNumber {0xD526}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD527}, Data {0x5A});
    flexibleMemoryController_.write(RegisterNumber {0xD528}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD529}, Data {0x73});
    flexibleMemoryController_.write(RegisterNumber {0xD52A}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD52B}, Data {0x94});
    flexibleMemoryController_.write(RegisterNumber {0xD52C}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD52D}, Data {0x9F});
    flexibleMemoryController_.write(RegisterNumber {0xD52E}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD52F}, Data {0xB3});
    flexibleMemoryController_.write(RegisterNumber {0xD530}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD531}, Data {0xB9});
    flexibleMemoryController_.write(RegisterNumber {0xD532}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD533}, Data {0xC1});
    // Blue -
    flexibleMemoryController_.write(RegisterNumber {0xD600}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD601}, Data {0x37});
    flexibleMemoryController_.write(RegisterNumber {0xD602}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD603}, Data {0x52});
    flexibleMemoryController_.write(RegisterNumber {0xD604}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD605}, Data {0x7B});
    flexibleMemoryController_.write(RegisterNumber {0xD606}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD607}, Data {0x99});
    flexibleMemoryController_.write(RegisterNumber {0xD608}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD609}, Data {0xB1});
    flexibleMemoryController_.write(RegisterNumber {0xD60A}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD60B}, Data {0xD2});
    flexibleMemoryController_.write(RegisterNumber {0xD60C}, Data {0x00});
    flexibleMemoryController_.write(RegisterNumber {0xD60D}, Data {0xF6});
    flexibleMemoryController_.write(RegisterNumber {0xD60E}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD60F}, Data {0x27});
    flexibleMemoryController_.write(RegisterNumber {0xD610}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD611}, Data {0x4E});
    flexibleMemoryController_.write(RegisterNumber {0xD612}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD613}, Data {0x8C});
    flexibleMemoryController_.write(RegisterNumber {0xD614}, Data {0x01});
    flexibleMemoryController_.write(RegisterNumber {0xD615}, Data {0xBE});
    flexibleMemoryController_.write(RegisterNumber {0xD616}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD617}, Data {0x0B});
    flexibleMemoryController_.write(RegisterNumber {0xD618}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD619}, Data {0x48});
    flexibleMemoryController_.write(RegisterNumber {0xD61A}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD61B}, Data {0x4A});
    flexibleMemoryController_.write(RegisterNumber {0xD61C}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD61D}, Data {0x7E});
    flexibleMemoryController_.write(RegisterNumber {0xD61E}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD61F}, Data {0xBC});
    flexibleMemoryController_.write(RegisterNumber {0xD620}, Data {0x02});
    flexibleMemoryController_.write(RegisterNumber {0xD621}, Data {0xE1});
    flexibleMemoryController_.write(RegisterNumber {0xD622}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD623}, Data {0x10});
    flexibleMemoryController_.write(RegisterNumber {0xD624}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD625}, Data {0x31});
    flexibleMemoryController_.write(RegisterNumber {0xD626}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD627}, Data {0x5A});
    flexibleMemoryController_.write(RegisterNumber {0xD628}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD629}, Data {0x73});
    flexibleMemoryController_.write(RegisterNumber {0xD62A}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD62B}, Data {0x94});
    flexibleMemoryController_.write(RegisterNumber {0xD62C}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD62D}, Data {0x9F});
    flexibleMemoryController_.write(RegisterNumber {0xD62E}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD62F}, Data {0xB3});
    flexibleMemoryController_.write(RegisterNumber {0xD630}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD631}, Data {0xB9});
    flexibleMemoryController_.write(RegisterNumber {0xD632}, Data {0x03});
    flexibleMemoryController_.write(RegisterNumber {0xD633}, Data {0xC1});
}

void Ws17143Display::initRGB565Format() {
    flexibleMemoryController_.write(RegisterNumber {0x3A00}, Data {0x55});
}

void Ws17143Display::exitSleepState() {
    flexibleMemoryController_.write(RegisterNumber {0x1100}, Data {0x00});
    systemClock_.delayMiliseconds(120);
}

void Ws17143Display::enableDisplay() {
    flexibleMemoryController_.write(RegisterNumber {0x2900}, Data {0x00});
    systemClock_.delayMiliseconds(10);
}

void Ws17143Display::setAllPixelsOff() {
    flexibleMemoryController_.write(RegisterNumber {0x2200}, Data {0x00});
}

void Ws17143Display::displayFramebuffer() {
    flexibleMemoryController_.write(RegisterNumber {0x1300}, Data {0x00});
}

Ws17143Display::Ws17143Display(
    const Ws17143DisplayPinout& pinout,
    IFlexibleMemoryController& flexibleMemoryController,
    ISystemClock& systemClock
) :
    pinout_(pinout),
    flexibleMemoryController_(flexibleMemoryController),
    systemClock_(systemClock) {}

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

    flexibleMemoryController_.writeRegister(RegisterNumber {0x2C00});

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
            flexibleMemoryController_.writeData(Data {color});
        }
    }
}

void Ws17143Display::draw(
    const std::span<const uint16_t>& frameBuffer,
    const Rectangle& window
) {
    setWindow(window);

    flexibleMemoryController_.writeRegister(RegisterNumber {0x2C00});

    for (uint16_t y = window.yStart_; y <= window.yEnd_; y++) {
        for (uint16_t x = window.xStart_; x <= window.xEnd_; x++) {
            const uint16_t color = frameBuffer[y * WIDTH_ + x];
            flexibleMemoryController_.writeData(Data {color});
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