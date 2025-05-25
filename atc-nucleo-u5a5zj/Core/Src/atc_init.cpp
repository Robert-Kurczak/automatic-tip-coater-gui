#include "application/DelayProvider/DelayProvider.hpp"
#include "application/DisplayWs17143/DisplayWs17143.hpp"
#include "application/FlexibleMemoryController/FlexibleMemoryController.hpp"
#include "main.h"

FlexibleMemoryController flexibleMemoryController {
    0x60000000,
    0x60000002
};
DelayProvider delayProvider {};
DisplayWs17143 display {flexibleMemoryController, delayProvider};

void LCD_IO_SetWindow(
    uint16_t x0,
    uint16_t x1,
    uint16_t y0,
    uint16_t y1
) {
    flexibleMemoryController.writeRegister(0x2A00);
    flexibleMemoryController.writeData(x0 >> 8);
    flexibleMemoryController.writeRegister(0x2A01);
    flexibleMemoryController.writeData(x0 & 0xFF);
    flexibleMemoryController.writeRegister(0x2A02);
    flexibleMemoryController.writeData(x1 >> 8);
    flexibleMemoryController.writeRegister(0x2A03);
    flexibleMemoryController.writeData(x1 & 0xFF);

    flexibleMemoryController.writeRegister(0x2B00);
    flexibleMemoryController.writeData(y0 >> 8);
    flexibleMemoryController.writeRegister(0x2B01);
    flexibleMemoryController.writeData(y0 & 0xFF);
    flexibleMemoryController.writeRegister(0x2B02);
    flexibleMemoryController.writeData(y1 >> 8);
    flexibleMemoryController.writeRegister(0x2B03);
    flexibleMemoryController.writeData(y1 & 0xFF);
}

void LCD_TestPattern(int i = 0) {
    LCD_IO_SetWindow(0, 480, 0, 800);
    flexibleMemoryController.writeRegister(0x2C00);
    HAL_Delay(150);

    for (int y = 0; y < 800; y++) {
        for (int x = 0; x < 480; x++) {
            uint16_t color;
            if (y < 800 / 3) {
                color = 0xF800 + i; // red
            } else if (y < 800 / 3 * 2) {
                color = 0x07E0 / i; // green
            } else {
                color = 0x001F - i; // blue
            }
            flexibleMemoryController.writeData(color);
        }
    }
}

void ATC_Init() {
    // Page 1 enable
    flexibleMemoryController.writeRegister(0xF000);
    flexibleMemoryController.writeData(0x55);
    flexibleMemoryController.writeRegister(0xF001);
    flexibleMemoryController.writeData(0xAA);
    flexibleMemoryController.writeRegister(0xF002);
    flexibleMemoryController.writeData(0x52);
    flexibleMemoryController.writeRegister(0xF003);
    flexibleMemoryController.writeData(0x08);
    flexibleMemoryController.writeRegister(0xF004);
    flexibleMemoryController.writeData(0x01);

    // AVDD: 5.2V
    flexibleMemoryController.writeRegister(0xB000);
    flexibleMemoryController.writeData(0x0D);
    flexibleMemoryController.writeRegister(0xB001);
    flexibleMemoryController.writeData(0x0D);
    flexibleMemoryController.writeRegister(0xB002);
    flexibleMemoryController.writeData(0x0D);

    // AVEE: -5.2V
    flexibleMemoryController.writeRegister(0xB100);
    flexibleMemoryController.writeData(0x0D);
    flexibleMemoryController.writeRegister(0xB101);
    flexibleMemoryController.writeData(0x0D);
    flexibleMemoryController.writeRegister(0xB102);
    flexibleMemoryController.writeData(0x0D);

    // VCL: -2.5V
    flexibleMemoryController.writeRegister(0xB200);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xB201);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xB202);
    flexibleMemoryController.writeData(0x00);

    // VGH: 15V
    flexibleMemoryController.writeRegister(0xB300);
    flexibleMemoryController.writeData(0x05);
    flexibleMemoryController.writeRegister(0xB301);
    flexibleMemoryController.writeData(0x05);
    flexibleMemoryController.writeRegister(0xB302);
    flexibleMemoryController.writeData(0x05);

    // VGL: -10V
    flexibleMemoryController.writeRegister(0xB500);
    flexibleMemoryController.writeData(0x28);
    flexibleMemoryController.writeRegister(0xB501);
    flexibleMemoryController.writeData(0x28);
    flexibleMemoryController.writeRegister(0xB502);
    flexibleMemoryController.writeData(0x28);

    // VCOM: -1.375V
    flexibleMemoryController.writeRegister(0xB600);
    flexibleMemoryController.writeData(0x05);
    flexibleMemoryController.writeRegister(0xB601);
    flexibleMemoryController.writeData(0x05);
    flexibleMemoryController.writeRegister(0xB602);
    flexibleMemoryController.writeData(0x05);

    // Gamma settings
    flexibleMemoryController.writeRegister(0xD100);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD101);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD102);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD103);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD104);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD105);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD106);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD107);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD108);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD109);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD10A);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD10B);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD10C);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD10D);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD10E);
    flexibleMemoryController.writeData(0x00);
    flexibleMemoryController.writeRegister(0xD10F);
    flexibleMemoryController.writeData(0x00);

    flexibleMemoryController.writeRegister(0x3A00);
    flexibleMemoryController.writeData(0x55); // Format RGB565

    // Exit Sleep
    flexibleMemoryController.writeRegister(0x1100);
    HAL_Delay(120);

    // Display ON
    flexibleMemoryController.writeRegister(0x2900);
    HAL_Delay(20);

    LCD_TestPattern();
}

void ATC_Loop() {
    // LCD_DrawRectangle(0xF800, 50, 50, 150, 150);

    static int i = 0;
    LCD_TestPattern(i % 100);
    HAL_Delay(200);
    i++;
}
