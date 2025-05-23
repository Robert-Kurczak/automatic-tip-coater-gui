#include "main.h"

#include "application/FlexibleMemoryController/FlexibleMemoryController.hpp"

#define FMC_BANK1_REG  ((uint16_t *) 0x60000000)
#define FMC_BANK1_DATA ((uint16_t *) 0x60000002)

void LCD_IO_WriteReg(uint16_t Reg)
{
	*FMC_BANK1_REG = Reg;
}

void LCD_IO_WriteData(uint16_t RegValue)
{
	*FMC_BANK1_DATA = RegValue;
}

void LCD_IO_SetWindow(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
    LCD_IO_WriteReg(0x2A00);
    LCD_IO_WriteData(x0 >> 8);
    LCD_IO_WriteReg(0x2A01);
    LCD_IO_WriteData(x0 & 0xFF);
    LCD_IO_WriteReg(0x2A02);
    LCD_IO_WriteData(x1 >> 8);
    LCD_IO_WriteReg(0x2A03);
    LCD_IO_WriteData(x1 & 0xFF);

    LCD_IO_WriteReg(0x2B00);
    LCD_IO_WriteData(y0 >> 8);
    LCD_IO_WriteReg(0x2B01);
    LCD_IO_WriteData(y0 & 0xFF);
    LCD_IO_WriteReg(0x2B02);
    LCD_IO_WriteData(y1 >> 8);
    LCD_IO_WriteReg(0x2B03);
    LCD_IO_WriteData(y1 & 0xFF);
}

void LCD_TestPattern(int i = 0)
{
    LCD_IO_SetWindow(0, 480, 0, 800);
    LCD_IO_WriteReg(0x2C00);
    HAL_Delay(150);

    for (int y = 0; y < 800; y++) {
        for (int x = 0; x < 480; x++) {
            uint16_t color;
            if (y < 800/3)
                color = 0xF800 + i; // red
            else if (y < 800/3 * 2)
                color = 0x07E0 / i; // green
            else
                color = 0x001F - i; // blue
            LCD_IO_WriteData(color);
        }
    }
}

void ATC_Init() {
    // Page 1 enable
    LCD_IO_WriteReg(0xF000); LCD_IO_WriteData(0x55);
    LCD_IO_WriteReg(0xF001); LCD_IO_WriteData(0xAA);
    LCD_IO_WriteReg(0xF002); LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xF003); LCD_IO_WriteData(0x08);
    LCD_IO_WriteReg(0xF004); LCD_IO_WriteData(0x01);

    // AVDD: 5.2V
    LCD_IO_WriteReg(0xB000); LCD_IO_WriteData(0x0D);
    LCD_IO_WriteReg(0xB001); LCD_IO_WriteData(0x0D);
    LCD_IO_WriteReg(0xB002); LCD_IO_WriteData(0x0D);

    // AVEE: -5.2V
    LCD_IO_WriteReg(0xB100); LCD_IO_WriteData(0x0D);
    LCD_IO_WriteReg(0xB101); LCD_IO_WriteData(0x0D);
    LCD_IO_WriteReg(0xB102); LCD_IO_WriteData(0x0D);

    // VCL: -2.5V
    LCD_IO_WriteReg(0xB200); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xB201); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xB202); LCD_IO_WriteData(0x00);

    // VGH: 15V
    LCD_IO_WriteReg(0xB300); LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xB301); LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xB302); LCD_IO_WriteData(0x05);

    // VGL: -10V
    LCD_IO_WriteReg(0xB500); LCD_IO_WriteData(0x28);
    LCD_IO_WriteReg(0xB501); LCD_IO_WriteData(0x28);
    LCD_IO_WriteReg(0xB502); LCD_IO_WriteData(0x28);

    // VCOM: -1.375V
    LCD_IO_WriteReg(0xB600); LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xB601); LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xB602); LCD_IO_WriteData(0x05);

    // Gamma settings
    LCD_IO_WriteReg(0xD100); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD101); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD102); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD103); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD104); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD105); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD106); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD107); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD108); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD109); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD10A); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD10B); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD10C); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD10D); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD10E); LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xD10F); LCD_IO_WriteData(0x00);

    LCD_IO_WriteReg(0x3A00);
    LCD_IO_WriteData(0x55);  // Format RGB565

    // Exit Sleep
    LCD_IO_WriteReg(0x1100);
    HAL_Delay(120);

    // Display ON
    LCD_IO_WriteReg(0x2900);
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
